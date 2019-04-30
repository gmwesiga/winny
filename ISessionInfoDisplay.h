#ifndef _ISESSIONINFODISPLAY_H_
#define _ISESSIONINFODISPLAY_H_

#include "SystemTypes.h"
#include "IUserInterface.h"

class ISessionInfoDisplay : public IUserInterface {
    public:
    virtual void sessionId(string id)=0;
};
#endif
