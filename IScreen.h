#ifndef _IUSERINTERFACE_H_
#define _IUSERINTERFACE_H_

#include "IProductsListDisplay.H"
#include "ISessionInfoDisplay.h"
#include "INavDisplay.h"

enum class UiStatus {
    INITIALISING_UI,
    CREATING_PRODS,
    BROWSING_PRODS,
    IDLE
};

class IScreen :public IUserInterface {
    public:
    virtual const UiStatus status()=0;
    virtual const IProductsListDisplay* productsListDisplay()=0;
    virtual const ISessionInfoDisplay* sessionInfoDisplay()=0;
    virtual const INavDisplay* navDisplay()=0;
    virtual ~IScreen(){};
};

#endif