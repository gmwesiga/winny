#include <DatabaseServer.h>
#include <thread>
#include <IExtEventSource.h> //for SigDATAREADY
#include <iostream>
#include <pthread.h>

/*23 oct: portability requirements  have necesitated we reimplement the threading
 *        logic with pthreads insted of the c++11 threads library which seems not
 *        to be implemented generaly by most gnu cross compilers. 
 *        The new requirement is that the threading code should be compilable by
 *        any cross compiler*/

StdSystem::RequestId IDatabaseService::RequestInfo::_nextid_ = 0;

//initialisation of pthread locks
pthread_mutex_t DatabaseServer::queueLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  DatabaseServer::notEmpty = PTHREAD_COND_INITIALIZER;
std::queue<IDatabaseService::RequestInfo>   DatabaseServer::RequestQueue;

pthread_mutex_t DatabaseServer::ResponseQueueLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  DatabaseServer::resQueNotEmpty = PTHREAD_COND_INITIALIZER;
std::queue <IDatabaseService::Response*>     DatabaseServer::ResponseQueue;




/*This pthread_thread is a wrapper around the actual our thread function
 *it adapts the server interface to the one required by pthreads.*/
static void* pthreadServerFunc(void* arg){
    DatabaseServer::server();
}


DatabaseServer::DatabaseServer()
//allocate server() program to its thread and begin executing it
//:svr(DatabaseServer::server)
{
    //launch the server thread
    pthread_t id;
    pthread_create(&id,nullptr,pthreadServerFunc,nullptr);
 }


int DatabaseServer::process(RequestInfo rqst){
    //acquire the lock
    pthread_mutex_lock(&queueLock);
    //std::unique_lock<std::mutex> lock(queueLock);
    //std::cout<<"process: lock Acquired \n";
    //add request to server processing queue
    RequestQueue.push(rqst);
    //std::cout<<"request pushed with trigger "<<rqst.triggerEvent<<"\n";
    //release the lock
    pthread_mutex_unlock(&queueLock);

    //wake up server() if queue had been empty
    if(RequestQueue.size()==1)
        //notEmpty.notify_one();
        pthread_cond_signal(&notEmpty);
    //std::cout<<"server notified\n";
    return 1;
};


void DatabaseServer::server(){
    //std::cout<<"server started\n";
    //shall contain the pop()ed request  
    RequestInfo rqst;
    
    do{  
        //wait untill there is a request in queue
            //to call wait, you need to acquire lock first
            //std::unique_lock<std::mutex> lock(queueLock);
            pthread_mutex_lock(&queueLock);
            //wait for process to add request in queue
            if(RequestQueue.size()<=0){
                //std::cout<<"Server found nothing in queue, going to sleep\n";
                //release lock and wait for application layer to add a request
                //notEmpty.wait(lock);
                pthread_cond_wait(&notEmpty,&queueLock);
                if(!RequestQueue.size()) continue; //something else woke us up
                //std::cout<<"Server woken up to process\n";
            }
                //if here, application added request and called us,
                //wait acquired lock for use, so we have lock 
            //get request
            rqst = RequestQueue.front();
            RequestQueue.pop();   
            pthread_mutex_unlock(&queueLock);
          //release lock by 

            //process
            IDatabaseService::Response res;
            doit(rqst);

            //notify client of response
            int notify = 0;
            //{
            //std::unique_lock<std::mutex> lk(ResponseQueueLock);
            pthread_mutex_lock(&ResponseQueueLock);
            ResponseQueue.push((IDatabaseService::Response*)rqst.responseBuffer);
            pthread_mutex_unlock(&ResponseQueueLock);
            //}
            if(ResponseQueue.size()==1)//was previously empty >1 means its already awake
                //resQueNotEmpty.notify_one();
                pthread_cond_signal(&resQueNotEmpty);

    }while(true);

};



void DatabaseServer::doit(RequestInfo request){
//Performs required operation and writes response in request.responseBuffer

    IDatabaseService::Response* response = (IDatabaseService::Response*)request.responseBuffer;
    
    //std::cout<<"processing request in db trigger event sent here is"<<request.triggerEvent<<"\n";
    switch (request.request){

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
    //std::unique_lock<std::mutex> lk(DatabaseServer::ResponseQueueLock);
    pthread_mutex_lock(&ResponseQueueLock);
    r = ResponseQueue.front();
    ResponseQueue.pop();
    pthread_mutex_unlock(&ResponseQueueLock);
    //lk.unlock();
    return r;
};