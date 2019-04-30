#ifndef _INAVDISPLAY_H_
#define _INAVDISPLAY_H_

#include "SystemTypes.h"
#include "IUserInterface.h"

class INavDisplay : public IUserInterface {
    public:
    virtual void entityName(string id)=0;
    virtual void addNotification(string text, int type=0)=0;
    virtual void clearNotifications()=0;
    virtual void addResponsibility(string desc)=0;
    virtual void clearResponsibilities()=0;
    virtual void setRoleName(string desc)=0;
};
#endif
