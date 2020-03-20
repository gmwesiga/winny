#ifndef _IUSERINTERFACE_H_
#define _IUSERINTERFACE_H_

#include <IUserInterface.h>
#include <IApplicationTypes.H>
#include <IApplication.h>
#include <dataTypes/Request.H>

enum class UiStatus {
    INITIALISING_UI,
    CREATING_PRODS,
    BROWSING_PRODS,
    IDLE
};

class IScreen :public IUserInterface {
    public:

    /**
     * Run for specified duration or until user requests an operation
     * write out the requested operation in, and the specified arguments 
     * if any
     * 
     * @param[out] ReqOper The operation that was requested by user if
     * any (OCC is positive interger)
     * @param[in:out] ReaOperArgs The arguments to the requested operation
     * @param[in]Duration specifies the duration to try waiting for the
     * request before giving up.
     */
    virtual int runUntilInput(Request* reqst, double duration);

    
    /**
     * Read the Status field of this IScreen
     */
    virtual const UiStatus status()=0;
    
    
    virtual void log(std::string msg)=0;
    
    /**
     * Replace the current slave/Child screen page with the a new new page
     * specified by the name in the arguments
     */
    virtual void switchToDisplay(Winny::UserIODevName sn=(Winny::UserIODevName)0)=0; 
   

    /**
     * To handle cases of some child iopages need to communicate with the 
     * main/parent Iscreen we have added handler here: child iopages can send 
     * some custome events to the Iscreen or even to the application itself, 
     * which then routes them to the Iscreen through handle in addition to
     * this interface, The static function screen returns a global reference
     */
    virtual int handle(StdSystem::sEvent,void *eData=nullptr)=0;


    /// return  global reference to screen
    static IScreen* screen();

    virtual ~IScreen(){};
};

#endif