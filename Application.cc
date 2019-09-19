#include <Application.H>
//#include <records_lib.h>
#include<FL/fl_ask.H> //todo remove this after production
#include<stdlib.h>

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
            userIO->writeBuff(&curStatus);
        break;
        case CmdsearchProduct:
            userIO->log("CmdSearchProduct...Delivered");
            productListUpdate(eData);
            break;
        case CmdEditProductDetails:
            userIO->log("CmdEditProductDetails...Delivered");

            break;
        case CmdNavigateTo:
            {//char* data = (char*)eData;
            //userIO->log(string("navigating to ").append(data));
            navigate((Winny::UserIODevName*)eData);}
            break;
        case CmdUpdateProductsList:
            userIO->log("***CmdUpdateProductsList...Delivered");
            productListUpdate(eData);
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
     IUserInterface* io = (IUserInterface*)o;
     Winny::ProductsListFilter *fltr;
     //io->readBuff(fltr);
     //if (fltr->)

     //update

     /* string*/double s(10);//*std::;
     variable data;

     int rc = 50; int cc = 3;
    Winny::Dataset output(rc,cc);
    // output.resize(rc);
     for (int r=0; r<rc; r++){
         for (int c=0; c<cc; c++){
            data.number(s*rand());
            output.data(r,c,data);
            if(output.data(r,c).number()>300000){
                output.data(r,c).style().forecolor = wcolor(0,125,12);
                
            }
            output.data(r,c).style().borders = Borders::LEFT_RIGHT_BORDER;
            
         }
         output.data(r,0).cstring("some very long long long stupid text");
     }
    Winny::ProductsListParams out;
    out.outPut =& output;
    io->writeBuff(&out);
    userIO->log("What the fuck***");
     return 1;
 }

#undef screen