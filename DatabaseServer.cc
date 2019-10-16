#include <DatabaseServer.h>
#include <thread>
#include <IExtEventSource.h> //for SigDATAREADY
#include <iostream>


DatabaseServer::DatabaseServer()
//allocate server() program to its thread and begin executing it
:svr(DatabaseServer::server)
{ }


int DatabaseServer::process(RequestInfo rqst){
    //acquire the lock
    {
    std::unique_lock<std::mutex> lock(queueLock);
    //std::cout<<"process: lock Acquired \n";
    //add request to server processing queue
    RequestQueue.push(rqst);
    //std::cout<<"request pushed with trigger "<<rqst.triggerEvent<<"\n";
    //release the lock
    }

    //wake up server() if queue had been empty
    if(RequestQueue.size()==1)
        notEmpty.notify_one();
    //std::cout<<"server notified\n";
    return 1;
};


void DatabaseServer::server(){
    //std::cout<<"server started\n";
    //shall contain the pop()ed request  
    RequestInfo rqst;
    
    do{  
            //wait untill there is a request in queue
            {
                //to call wait, you need to acquire lock first
                std::unique_lock<std::mutex> lock(queueLock);
                
                //wait for process to add request in queue
                if(RequestQueue.size()<=0){
                    //std::cout<<"Server found nothing in queue, going to sleep\n";
                    //release lock and wait for application layer to add a request
                    notEmpty.wait(lock);
                }
                    //if here, application added request and called us,
                    //wait acquired lock for use, so we have lock 
                    //std::cout<<"Server woken up to process\n";
                //get request
                rqst = RequestQueue.front();
                RequestQueue.pop();   
            
            }  //release lock by exiting scope

                //process
                IDatabaseService::Response res;
                doit(rqst);

                //notify client of response
                {
                std::unique_lock<std::mutex> lk(ResponseQueueLock);
                ResponseQueue.push((IDatabaseService::Response*)rqst.responseBuffer);
                }
                if(ResponseQueue.size()==1)//was previously empty
                    resQueNotEmpty.notify_one();

        }while(true);

};



void DatabaseServer::doit(RequestInfo request){
    //Performs required operation and writes response in request.responseBuffer

    
    IDatabaseService::Response* response = (IDatabaseService::Response*)request.responseBuffer;
    
    //std::cout<<"processing request in db trigger event sent here is"<<request.triggerEvent<<"\n";
    switch (request.request)
    {
    case IDatabaseService::Request::GETL_PRODTS:
       {
        //sizes of our dataset response //lets use response and request terms
        int rc = 50; int cc = 10; 

        //resize response
        response->data.set_rows(rc);
        response->data.set_cols(cc);

        //populate it with some garbage data for now
        for (int r=0; r<rc; r++){
            for (int c=0; c<cc; c++){
                 response->data.data(r,c,(c+r)*rand());
                if(response->data.data(r,c).number()>300000){
                    response->data.data(r,c).style().forecolor = wcolor(0,125,12);   
                }
                response->data.data(r,c).style().borders = Borders::LEFT_RIGHT_BORDER;
                
            }
        }   
        response->ok = 1;
        response->requestId = request.id();
        response->message= variable("Search executed successfully");
        response->request = request;

       }
    break;
    
    default:
        break;
    }
}


IDatabaseService::Response* DatabaseServer::popResponse(){
    IDatabaseService::Response* r;
    std::unique_lock<std::mutex> lk(DatabaseServer::ResponseQueueLock);
    r = ResponseQueue.front();
    ResponseQueue.pop();
    lk.unlock();
    return r;
};