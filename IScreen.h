#ifndef _IUSERINTERFACE_H_
#define _IUSERINTERFACE_H_

#include "INavDisplay.h"
#include <IApplicationTypes.H>

enum class UiStatus {
    INITIALISING_UI,
    CREATING_PRODS,
    BROWSING_PRODS,
    IDLE
};

class IScreen :public IUserInterface {
    public:
    virtual const UiStatus status()=0;
    virtual void log(string msg)=0;
    virtual void switchToDisplay(Winny::UserIODevName sn=(Winny::UserIODevName)0)=0; 
    /*if no pending prompts, switch to screen named sn*/
    virtual ~IScreen(){};
};

#endif