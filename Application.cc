#include <Application.H>
//#include <records_lib.h>
#include<FL/fl_ask.H> //todo remove this after production
#include<stdlib.h>
#include<iostream>


#define screen scrn


//Adapter for pthread interface
static void* pthreadAdapterFunc(void* arg){
    Application::processDBResponse();
}


//Constructor optionally sets reference to the UI to be
//used for application data input and output
Application::Application(FlScreen* sn,StdSystem::IDatabaseService* db)
    :userIO(sn),
    databaseIOServer(db)
    //bgworker(Application::processDBResponse)
{
    pthread_t id;
    pthread_create(&id,nullptr,pthreadAdapterFunc,nullptr); 
    //remember to assign self to screen
    if(sn) sn->Attach(this);
    return;
};

//If Constructor did not set the UI to use, uiScreen
//can be used to set it or update it to a new reference
void Application::uiScreen(FlScreen* sn){
    userIO=sn;
    sn->Attach(this);//Attach self to Screen;
}; 

//Handle is the heart of the application. normally on
//startup code subscribes an instance of application object
//to an EventSource/command source object. when a user issues
//a command or an internal timer runs out, the action is 
//captured by the event source object, assigned an appropriate
//eventname/command name and it then calls the 
//application handle to process the event. Handle will typically
//run a switch on the event name and call the appropriate application
//function that implements the event handle behavior.
//a default action is to do nothing but just log the application.
//in future, the default action will be a message on the ui of 
//whether the application implements or doesn't implement the action.

int Application::handle(sEvent cmd,void *eData){
    Winny::UserInputArg *arg;
    IDatabaseService::Response *res;

    switch (cmd) {

        case SigUserIOready:
            curStatus.sessionInfo.currentOpgUnit.name = (char*)"Premium Distributors";//cast constness
            curStatus.sessionInfo.operatingUnits.push_back({(char*)"Global Distributors",(char*)"Gors"});
            curStatus.sessionInfo.operatingUnits.push_back({(char*)"Scan Distributors",(char*)"Scrs"});
            curStatus.sessionInfo.operatingUnits.push_back({(char*)"Scan Distributors",(char*)"Scrs"});
            curStatus.sessionInfo.role.name = (char*)"Admin";
            userIO->writeBuff(&curStatus);
        break;


        case CmdsearchProduct:
        case CmdUpdateProductsList:
        {
            //std::cout<<"preparing request \n";
            arg = (Winny::UserInputArg*)eData;
            IDatabaseService::RequestInfo rqst;
            rqst.client = arg->interface;
            rqst.args = arg->args;
            rqst.request = IDatabaseService::Request::GETL_PRODTS;
            rqst.triggerEvent = arg->event;
            //std::cout<<"trigger Event sent is "<<rqst.client<<"\n";
            rqst.responseBuffer = new IDatabaseService::Response();
            //saveRequest(rqst);
            databaseIOServer->process(rqst);
        }
            break;

        case CmdEditProductDetails:
            userIO->log("CmdEditProductDetails...Delivered");

            break;
        case CmdNavigateTo:
            {//char* data = (char*)eData;
            //userIO->log(string("navigating to ").append(data));
            navigate((Winny::UserIODevName*)eData);}
            break;
/*         case CmdUpdateProductsList:
            userIO->log("***CmdUpdateProductsList...Delivered");
            productListUpdate(eData); */
        break;
        default:
            userIO->log("@@@@unkown Command ...Delivered");
    }
};

void Application::navigate (Winny::UserIODevName* n){
    if(userIO)
        userIO->switchToDisplay(*n);
};

 int Application::productListUpdate(void* o){
    
    userIO->log("Product list has been updated...");
     return 1;
 }


/*void Application::saveRequest(IDatabaseService::RequestInfo req){
    //get the lock
    std::unique_lock<std::mutex> lk(Application::requestsTableLock);
    requestToClient[req.id()] = req;
};


IDatabaseService::RequestInfo Application::getRequest(StdSystem::RequestId i){
    IDatabaseService::RequestInfo r;
    {
        std::unique_lock<std::mutex> lk(Application::requestsTableLock);
        r = requestToClient[i];
    }
    return r;
};



void Application::clearRequest(RequestId id){
    //safely removes an item from the table first locks it 

    std::unique_lock<std::mutex> lk(Application::requestsTableLock);
    requestToClient.erase(id);
};*/


void Application::processDBResponse(){
    //waits untill database worker thread adds responses to response queue
    //wakes up and services them

    do{
        //std::unique_lock<std::mutex> lk(DatabaseServer::ResponseQueueLock);
        pthread_mutex_lock(&DatabaseServer::ResponseQueueLock);
        //sleep if no responses
        if(DatabaseServer::ResponseQueue.size()<=0){
            //std::cout<<"processing thread going to sleep \n";
            //DatabaseServer::resQueNotEmpty.wait(lk);
            pthread_cond_wait(&DatabaseServer::resQueNotEmpty,&DatabaseServer::ResponseQueueLock);
            if(!DatabaseServer::ResponseQueue.size()) continue; //something else woke us up
            //std::cout<<"process thread Walken up  going to work\n";

        }
        //lk.unlock(); 
        pthread_mutex_unlock(&DatabaseServer::ResponseQueueLock);
    
        auto rsp = DatabaseServer::popResponse();
        //auto rqstInfo = Application::getRequest(rsp->requestId);

        int triggerEvent = rsp->request.triggerEvent;
        //std::cout<<"trigger Event returned is "<<rsp->request.client<<"\n";
        
        IUserInterface *userIO = rsp->request.client;
        
        Winny::UserOutputArg output;

        if(triggerEvent == CmdUpdateProductsList){
            //prepare search results output
            output.ok = rsp->ok; 
            output.message = rsp->message;
            output.event = triggerEvent;
            output.args = & (rsp->data);

            //send them to output
            //std::cout<<"Process response ready, locking interface \n";
            Fl::lock();

            userIO->writeBuff(&output);

            Fl::unlock();
            //std::cout<<"processDB done refreshing inteface, unlocked\n";

        }else{
            //std::cout<<"ProcessDB couldn't match this response to a known event \n";
        }

        //ALWAYS REMEMBER TO CLEAN MEMORY
        delete rsp;

    }while (true);
};

#undef screen