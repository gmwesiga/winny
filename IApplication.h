#ifndef IAPPLICATION_H
#define IAPPLICATION_H

namespace StdSystem {
    //an Event name is an int
    typedef int sEvent;

    class IApplication {
        public:
        virtual int handle(sEvent,void *eData)=0;
    };//end of IEventHandler


}//end of namespace
#endif