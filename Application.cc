#include <Application.H>
#include<FL/fl_ask.H> //todo remove this after production
#define screen scrn

//Constructor optionally sets reference to the UI to be
//used for application data input and output
Application::Application(FlScreen* sn):scrn(sn){
    return;
};

//If Constructor did not set the UI to use, uiScreen
//can be used to set it or update it to a new reference
void Application::uiScreen(FlScreen* sn){
    screen=sn;
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
        case CmdsearchProduct:
            screen->log("CmdSearchProduct...Delivered");
            break;
        case CmdEditProductDetails:
            screen->log("CmdEditProductDetails...Delivered");
            break;
        case CmdNavigateTo:
            {char* data = (char*)eData;
            screen->log(string("navigating to ").append(data));
            navigate((UIname)data);}
            break;
        case CmdFilterProductsList:
            screen->log("CmdFilterProductsList...Delivered");
        break;
        default:
            screen->log("@@@@unkown Command ...Delivered");
    }
};

void Application::navigate (UIname n){
    if(scrn)
        screen->showfDisplay(n);
};

#undef screen