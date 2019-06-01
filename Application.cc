#include <Application.H>
//#include <records_lib.h>
#include<FL/fl_ask.H> //todo remove this after production
#define screen scrn

//Constructor optionally sets reference to the UI to be
//used for application data input and output
Application::Application(FlScreen* sn):userIO(sn){
    return;
};

//If Constructor did not set the UI to use, uiScreen
//can be used to set it or update it to a new reference
void Application::uiScreen(FlScreen* sn){
    userIO=sn;
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
    switch (cmd) {
        case SigUserIOready:
            curStatus.sessionInfo.currentOpgUnit.name = (char*)"Premium Distributors";//cast constness
            curStatus.sessionInfo.operatingUnits.push_back({(char*)"Global Distributors",(char*)"Gors"});
            curStatus.sessionInfo.operatingUnits.push_back({(char*)"Scan Distributors",(char*)"Scrs"});
            curStatus.sessionInfo.operatingUnits.push_back({(char*)"Scan Distributors",(char*)"Scrs"});
            curStatus.sessionInfo.role.name = (char*)"Admin";
            userIO->writeBuffer(&curStatus);
        break;
        case CmdsearchProduct:
            userIO->log("CmdSearchProduct...Delivered");
            break;
        case CmdEditProductDetails:
            userIO->log("CmdEditProductDetails...Delivered");
            break;
        case CmdNavigateTo:
            {//char* data = (char*)eData;
            //userIO->log(string("navigating to ").append(data));
            navigate((Winny::UserIODevName*)eData);}
            break;
        case CmdFilterProductsList:
            userIO->log("CmdFilterProductsList...Delivered");
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
     //do some queries
     //update ((ui*)o)->writeBuffer(p)
     return 1;
 }

#undef screen