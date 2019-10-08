#ifndef _WINNYAPPLICATION_H
#define _WINNYAPPLICATION_H

#include <IApplication.h>
#include <IUserInterface.h>
#include <FlScreen.h> //testing only to be replaced with Iscreen instead. break dependency
#include <IApplicationTypes.H>

using namespace StdSystem;

class IDataBaseIOService;
/*IDatabaseService defines an interface required by Application to service
 *(handle) requests that need retrieval of data. Application requires this 
 *IDtabaseService to have a process that takes a request command token and
 *optionally a argument list.
 *Application also requires that process() returns imediately and performs
 *long work in the background upon completion of which, it calls application's
 *handle and passes the results.*/


class Application : public StdSystem::IApplication {
    
    public:    
    Application(FlScreen *sn=nullptr);
    void uiScreen(FlScreen* sn); //set or get uiScreen
    int handle(sEvent,void *eData=nullptr);
    int productListUpdate(void* o);

    private:
    void navigate (Winny::UserIODevName* n);
    Winny::AppInfo curStatus;//what state application is in..initially Closed.

    FlScreen* userIO;
    IDataBaseIOService *databaseIOServer;

};


class IDatabaseIOService {
    public:
    void process();
};
//To Do
//remember to generalise uiScreen arguments to Interface equivalents to remove
//dependency on flImplementation
#endif