#ifndef _WINNYAPPLICATION_H
#define _WINNYAPPLICATION_H

#include <IApplication.h>
#include <IUserInterface.h>
#include <FlScreen.h> //testing only to be replaced with Iscreen instead. break dependency
#include <IApplicationTypes.H>

using namespace StdSystem;


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

};
//To Do
//remember to generalise uiScreen arguments to Interface equivalents to remove
//dependency on flImplementation
#endif