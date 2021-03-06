#ifndef IEXTEVENTSOURCE_H
#define IEXTEVENTSOURCE_H

#include "IApplication.h" //Requires application.handle();

namespace StdSystem {

    class IExtEventSource{
        public:
        virtual void Attach(IApplication* app);
        void Dettach();
        virtual void run()=0;
        
        protected:
        IExtEventSource();
        /*We want IEXtEventSource to solely be responsible for
         *calling the EventHandler application, and not Concrete 
         *Implementers. Instead concrete Implementors call base notify()
         *for this reason, the handle to the EventHandler is private
         */
        void notify(sEvent e, void *eData=nullptr);

        private:
        //No need for distructor for data. It belongs to client;
        
        //data
        IApplication* application;
    };


/**
 * A user command is represented with a short int, each command has
 * a unique short assigned to it as defined by the following table
 */
#define USERCMD short

/**
 * This is the list of all user commands and their numeric codes
 */

#define CmdNavigateTo          0 //0-49 reserved for client related events live navigation
#define SigUserIOready         1
#define CmdUpdateProductsList  50
#define CmdDeactivateProduct   51
#define CmdEditProductDetails  52
#define CmdsearchProduct       53

/*The following commands are generated by a databaseIO service to inform that datarequests are ready*/
#define SigDATAREADY           100
#define SigSHUTDOWN            200
}
#endif