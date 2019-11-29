/****NOTES*****
 * 28 NOVEMBER 2019
 * Implications of switching to a Bus driven
 * The decision to have the winny UI module run as a separate process module (not procedure module)
 * communicating to the rest of winny over a bus has necesitated need to change some aspects of the
 * Winny IUserInterface because the initial design doesn't fit well with the new process module centered
 * design.
 * the original design assumed an application object, a top level UI module, and 3, several mid-level
 * UI objects that implemented individual functionality.
 * the role of the top level UI was to act as afacade and provide the UI interface as required by application
 * eg which roles to show, etc
 * 
 * A challenge was how to pass the application reference to the midlevel UIs,  
*/
#ifndef IUserInterface_h
#define IUserInterface_h
#include <string>
#include <IExtEventSource.h>
#include <IApplication.h>
#include <IApplicationTypes.H>
//#include <IScreen.h>

typedef std::string UIname; // name of IUserInterface Name
#define MemAddress void*

class IUserInterface 
    :  public virtual StdSystem::IExtEventSource 
    ,  public virtual StdSystem::IApplication{ //for composite /aggregation UIs like SCreen that must aggregate multiple UIs into one
    //virtual inheritance solves the diamond inheritance problem
    public:
    /*State a UI can be in*/
    enum State{
        READY_OK,/*UI is ready. Last input operation executed to completion it can be used to print a message*/
        READY_ERROR, /*UI is ready. operation didn't complete well 
        it can be used to decide whether to print an error message to user*/
        READY, /*UI ready UI updating routines should set state to this after finding the ready ok
         or ready error states*/
        BUSY/*UI has raised an command input and is waiting for execution to complete*/
    };

    virtual void show()=0;
    virtual void hide()=0;
    virtual void update()=0;
    
    /*get id is virtual so that IOs that want static names can customise it*/   
    virtual UIname id(){return _id_;};
    void id(UIname s){_id_ =s;};

    virtual void readBuff(MemAddress buff)=0;
    /*readBuff is called by the application to input data from UI
     *buff points to the copied data, depending on how the derived io 
     *object is implemented, readbuff may either allocate space on 
     *the free store and set buff to its address or may expect buff to point to 
     *a objected in caller space to write to */
    virtual void writeBuff(MemAddress buff)=0;
    /*WriteBuff is called by the application to output date into UI
     *buff points to the data to copy, when writeBuff returns, the 
     *data pointed to by buff has been copied into the output object */

    /*raises an Input Event /command to application's handler and set's
     *this input to busy*/
    virtual void raiseEvent(StdSystem::sEvent e, void *eData=nullptr){
        StdSystem::IExtEventSource::notify(e,eData);
        _state_= BUSY;
    };


    /*Clears the Busy state. this should be called by application after handling
     *the raised event so that UI exits the busy(command being processed) state*/
    void ready(IUserInterface::State s=READY_OK, std::string errormsg=""){
        message = errormsg;
        _state_ = s;
        update();// notify user
    };

    /*Returns current state of interface. It can be used by UI drawing function to
     *decide how to redraw the interface during busy ready_eror or ready_ok states
     *and probably to enable or disable some functions.*/
    IUserInterface::State status(){return _state_;};

    virtual void run(){return;};//default is do nothing

    virtual int handle(StdSystem::sEvent,void *eData){ return 1;};
    //for aggregating UIs like Screen

    virtual ~IUserInterface(){};

    private:
    UIname _id_;
    State _state_;
   

   protected:
   std::string message; //last feedback message from application
   Winny::UserInputArg args;
};

#endif

/*Adding raiseEvent to this interface makes 
all ui elements cabable of being event sources
and reliminates need for dublicate code in the 
individual UI objects.

Desided to typedef void* to get an alias that will still
make sense if i choose to change the type to a more type safe
class later based on unions
*/