#include <Application.H>
//#include <records_lib.h>
#include<FL/fl_ask.H> //todo remove this after production
#include<stdlib.h>
#include<iostream>
#include<ServiceTypes.H>
#include<CommBus.H>

using StdSystem::Service::Request;
using StdSystem::Service::Response;
using StdSystem::Service::Operation;

#define screen scrn


//Adapter for pthread interface
static void* pthreadAdapterFunc(void* arg){
    Application::processDBResponse();
}


//Constructor optionally sets reference to the UI to be
//used for application data input and output
Application::Application(FlScreen* sn)
    :userIO(sn)
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
    Winny::UserInputArg *arg= (Winny::UserInputArg*)eData;

    switch (arg->event) {

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
            Request rqst;
            rqst.client = arg->sourceInterface;
            rqst.args = arg->args;
            rqst.operation = Operation::GETL_PRODTS;
            rqst.triggerEvent = arg->event;
            //std::cout<<"trigger Event sent is "<<rqst.client<<"\n";
            rqst.responseBuffer = new Response();
            //saveRequest(rqst);
            StdSystem::Bus::sendRequest(rqst);
        }
            break;

        case CmdEditProductDetails:
            userIO->log("CmdEditProductDetails...Delivered");

            break;
        case CmdNavigateTo:
            {//char* data = (char*)eData;
            //userIO->log(string("navigating to ").append(data));
            navigate((Winny::UserIODevName*)arg->args);}
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





void Application::processDBResponse(){
    //waits untill database worker thread adds responses to response queue
    //wakes up and services them

    do{
        //auto rsp = StdSystem::Bus::receiveResponse();
        //auto rqstInfo = Application::getRequest(rsp->requestId);
        auto msg = StdSystem::Bus::receiveAt(APP_PORT);
        Response* rsp = (Response*)msg.message;
        
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