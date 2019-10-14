#include <DatabaseServer.h>
#include <thread>
#include <IExtEventSource.h> //for SigDATAREADY

DatabaseServer::DatabaseServer()
//allocate server() program to its thread and begin executing it
:svr(DatabaseServer::server)
{ }


int DatabaseServer::process(RequestInfo rqst){
    //acquire the lock
    {
    std::unique_lock<std::mutex> lock(queueLock);

    //add request to server processing queue
    RequestQueue.push(rqst);

    //release the lock
    }

    //wake up server()
    notEmpty.notify_one();

    return 1;
};


void DatabaseServer::server(){
  
  //shall contain the pop()ed request  
  RequestInfo rqst;
  
  do{  
        //wait untill there is a request in queue
        {
            //to call wait, you need to acquire lock first
            std::unique_lock<std::mutex> lock(queueLock);
            
            //wait for process to add request in queue
            notEmpty.wait(lock);

            //get request
            rqst = RequestQueue.top();
            RequestQueue.pop();   
        
        }  //release lock by exiting scope

            //process
            IDatabaseService::Response res;

            //notify client of response
            rqst.client->handle(SigDATAREADY,&res);

    }while(true);

};
