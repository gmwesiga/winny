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
#define CmdNavigateTo          0 //0-49 reserved for client related events live navigation
#define SigUserIOready         1
#define CmdUpdateProductsList  50
#define CmdDeactivateProduct   51
#define CmdEditProductDetails  52
#define CmdsearchProduct       53
}
#endif