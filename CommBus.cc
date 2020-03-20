#include <ServiceTypes.H>
#include <CommBus.H>
#include <thread>
#include <iostream>
#include <pthread.h>
#include <queue>

/*23 oct: portability requirements  have necesitated we reimplement the threading
 *        logic with pthreads insted of the c++11 threads library which seems not
 *        to be implemented generaly by most gnu cross compilers. 
 *        The new requirement is that the threading code should be compilable by
 *        any cross compiler*/

using StdSystem::Service::Response;
using StdSystem::Service::Request;
using StdSystem::Bus;

static std::queue <Request> RequestQueue ;
static pthread_cond_t ReqQueNotEmpty          =  PTHREAD_COND_INITIALIZER;
static pthread_mutex_t ReqQueueLock =  PTHREAD_MUTEX_INITIALIZER;

static std::queue <Response*> ResponseQueue;
static pthread_mutex_t ResQueueLock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t ResQueNotEmpty     = PTHREAD_COND_INITIALIZER;


StdSystem::RequestId Request::_nextid_ = 0;


int Bus::sendRequest(Request rqst){
    //acquire the lock
    pthread_mutex_lock(&ReqQueueLock);
    //std::cout<<"process: lock Acquired \n";
    
    //add request to server processing queue
    RequestQueue.push(rqst);
    //std::cout<<"request pushed with trigger "<<rqst.triggerEvent<<"\n";
    //release the lock
    pthread_mutex_unlock(&ReqQueueLock);

    //wake up server() if queue had been empty
    if(RequestQueue.size()==1)
        //ReqQueueLock.notify_one();
        pthread_cond_signal(&ReqQueNotEmpty);
    //std::cout<<"server notified\n";
    return 1;
};


Request Bus::receiveRequest(){
    //std::cout<<"server started\n";
    
    //shall contain the pop()ed request  
    Request rqst;
    
    //wait untill there is a request in queue
    //std::unique_lock<std::mutex> lock(queueLock);
    pthread_mutex_lock(&ReqQueueLock);
    //wait for process to add request in queue
    while(RequestQueue.size()<=0){
        //std::cout<<"Server found nothing in queue, going to sleep\n";
        //release lock and wait for application thread to add a request
        //ReqQueueLock.wait(lock);
        pthread_cond_wait(&ReqQueNotEmpty,&ReqQueueLock);
    }
    //if here, application added request and called us,
    //wait acquired lock for use, so we have lock 
    //get request
    rqst = RequestQueue.front();
    RequestQueue.pop();   
    pthread_mutex_unlock(&ReqQueueLock);
    //release lock

    return rqst;

};


int Bus::sendResponse(Response *r){
    //acquire the lock
    pthread_mutex_lock(&ResQueueLock);
    //std::cout<<"process: lock Acquired \n";
    
    //add request to server processing queue
    ResponseQueue.push(r);
    //std::cout<<"request pushed with trigger "<<rqst.triggerEvent<<"\n";
    //release the lock
    pthread_mutex_unlock(&ResQueueLock);

    //wake up client if queue had been empty
    if(ResponseQueue.size()==1)
        //ReqQueueLock.notify_one();
        pthread_cond_signal(&ResQueNotEmpty);
    //std::cout<<"server notified\n";
    return 1;
};


/*like putback or unget */
int Bus::echo(Response* r){
    sendResponse(r);
    return 1;
}


Response* Bus::receiveResponse(){
    Response* r;
    pthread_mutex_lock(&ResQueueLock);
    
    while (ResponseQueue.size()<=0){
        pthread_cond_wait(&ResQueNotEmpty,&ResQueueLock);
        //somethinng else wake us up
    }

    r = ResponseQueue.front();
    ResponseQueue.pop();
    pthread_mutex_unlock(&ResQueueLock);
    return r;
};

////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATION OF SEND TO AND RECEIVEAT//

using StdSystem::Bus;
static std::queue <Bus::Message> APP_QUEUE ;
static pthread_cond_t APPQ_NOT_EMP =  PTHREAD_COND_INITIALIZER;
static pthread_mutex_t APPQ_LCK =  PTHREAD_MUTEX_INITIALIZER;

static std::queue <Bus::Message> SVC_QUEUE;
static pthread_mutex_t SVCQ_LCK = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t SVCQ_NOT_EMP = PTHREAD_COND_INITIALIZER;


void selectTargetPort (
    StdSystem::BusPort pt,
    std::queue<Bus::Message>** targetBuff ,
    pthread_mutex_t** targetLock, 
    pthread_cond_t** targetCond 
    ){
    switch (pt)
    {
    case StdSystem::APP_PORT:
        *targetBuff = &APP_QUEUE;
        *targetLock = &APPQ_LCK;
        *targetCond = &APPQ_NOT_EMP;
        break;
    
    case StdSystem::SVC_PORT:
        *targetBuff = &SVC_QUEUE;
        *targetLock = &SVCQ_LCK;
        *targetCond = &SVCQ_NOT_EMP;
    }
};


int Bus::sendTo(BusPort pt, Bus::Message msg)
{
    pthread_mutex_t* targetLock;
    pthread_cond_t*  targetCond;
    std::queue<Bus::Message>* targetBuff;

    //select target port buffer
    selectTargetPort(pt,&targetBuff,&targetLock,&targetCond);

    //acquire the lock
    pthread_mutex_lock(targetLock);
    //std::cout<<"process: lock Acquired \n";
    
    //insert msg to port receive queue
    targetBuff->push(msg);
    //std::cout<<"request pushed with trigger "<<rqst.triggerEvent<<"\n";
    
    //release the lock
    pthread_mutex_unlock(targetLock);

    //wake up server() if queue had been empty
    if(targetBuff->size()==1)
        //ReqQueueLock.notify_one();
        pthread_cond_signal(targetCond);
    //std::cout<<"server notified\n";
    return 1;
};


Bus::Message Bus::receiveAt(StdSystem::BusPort prt){
    
    //shall contain the pop()ed msg  
    Bus::Message msg;
    
    pthread_mutex_t* targetLock;
    pthread_cond_t*  targetCond;
    std::queue<Bus::Message>* targetBuff;

    //select target port buffer
    selectTargetPort(prt,&targetBuff,&targetLock,&targetCond);

    
    //wait untill there is a request in queue
    //std::unique_lock<std::mutex> lock(queueLock);
    pthread_mutex_lock(targetLock);
    
    //wait for process to add request in queue
    while(targetBuff->size()<=0){
        //std::cout<<"Server found nothing in queue, going to sleep\n";
        
        //release lock and wait for producer thread to add a msg
        //.wait(lock);
        pthread_cond_wait(targetCond,targetLock);
    }
    //if here, application added request and called us,
    
    //wait acquired lock for use, so we have lock 
    //get request
    msg = targetBuff->front();
    targetBuff->pop();   
    pthread_mutex_unlock(targetLock);
    //release lock

    return msg;
};