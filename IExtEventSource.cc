#include "IExtEventSource.h"
//#include <FL/fl_ask.H>

using namespace StdSystem;

/* default constructor
 * sets handle to application to null pointer
 */
IExtEventSource::IExtEventSource():application(0){};

/*Attach is called by higher level code probally by init
 *function to subscribe an iapplication to an ieventsource controller's events
 */
void IExtEventSource::Attach(IApplication* app){
    application = app;
};


/*clients can call detach to unsubscribe an IApplication from ieventsource's events*/
 void IExtEventSource::Dettach(){
     application = 0;
 };


 /*notify() takes an event msg and calls the subscribed IApplication passing the event message
  *Concrete classes of ExtEventSource have no access to the subscribed
  *application. so they must call notify(sEvent), to publish their events
  *to subscribers.
  */
  void IExtEventSource::notify(sEvent e, void *eData){
      
      if (this->application) //fl_alert("in IxtEventSource::notify, application set");
      //return;
        this->application->handle(e,eData);

  };