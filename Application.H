#ifndef _WINNYAPPLICATION_H
#define _WINNYAPPLICATION_H

#include <IApplication.h>
#include <IUserInterface.h>
#include <FlScreen.h> //testing only to be replaced with Iscreen instead. break dependency
#include <IApplicationTypes.H>
#include <map>

using std::map;

using namespace StdSystem;


class Application : public StdSystem::IApplication {
    
    public:    
        Application(FlScreen *sn=nullptr);
        void uiScreen(FlScreen* sn); //set or get uiScreen

        int handle(sEvent,void *eData=nullptr);
        int productListUpdate(void* o);

        /*Process database responses and refresh UI*/
        static void processDBResponse();
    
    private:
        void navigate (Winny::UserIODevName* n);
        
        //what state application is in..initially Closed.
        Winny::AppInfo curStatus;

        /*Reference to Screen*/
        FlScreen* userIO;

        /*worker thread*/
        //std::thread bgworker;
    
};
 
//To Do
//remember to generalise uiScreen arguments to Interface equivalents to remove
//dependency on flImplementation
#endif