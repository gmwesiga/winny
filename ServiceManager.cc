#include <ServiceManager.H>

using namespace StdSystem::Service;
static void* pthreadServerFunc(void* arg);

static ServiceManager::ServiceConfig config = {"",nullptr};

//starts the service threads
int ServiceManager::start(ServiceManager::ServiceConfig* localSvsName){
    config = localSvsName?*localSvsName:ServiceConfig();    
    pthread_t id;
    pthread_create(&id,nullptr,pthreadServerFunc,nullptr);
}

void* pthreadServerFunc(void* arg){
    do{
       Request r = StdSystem::Bus::receiveRequest();
       if(config.svr)config.svr(r);
    }while(true);
}