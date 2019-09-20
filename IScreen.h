#ifndef _IUSERINTERFACE_H_
#define _IUSERINTERFACE_H_

#include <IUserInterface.h>
#include <IApplicationTypes.H>
#include <IApplication.h>

enum class UiStatus {
    INITIALISING_UI,
    CREATING_PRODS,
    BROWSING_PRODS,
    IDLE
};

class IScreen :public IUserInterface {
    public:
    virtual const UiStatus status()=0;
    virtual void log(std::string msg)=0;
    virtual void switchToDisplay(Winny::UserIODevName sn=(Winny::UserIODevName)0)=0; 
    /*if no pending prompts, switch to screen named sn*/

    /*To handle cases of some child iopages need to communicate with the main/parent Iscreen
        we have added handler here: child iopages can send some custome events to the Iscreen
        or even to the application itself, which then routes them to the Iscreen through handle
        in addition to this interface, The static function screen returns a global reference */
    virtual int handle(StdSystem::sEvent,void *eData=nullptr)=0;

    static IScreen* screen();//return  global reference to screen

    virtual ~IScreen(){};
};

#endif