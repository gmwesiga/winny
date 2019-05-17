#ifndef IUserInterface_h
#define IUserInterface_h
#include <string>
#include <IExtEventSource.h>

typedef std::string UIname; // name of IUserInterface Name

class IUserInterface :  public virtual StdSystem::IExtEventSource {
    public:
    virtual void show()=0;
    virtual void hide()=0;
    virtual void update()=0;
    virtual UIname id()=0;

    virtual void raiseEvent(StdSystem::sEvent e, void *eData=nullptr){
        StdSystem::IExtEventSource::notify(e,eData);
    };

    virtual void run(){return;};//default is do nothing

    virtual ~IUserInterface(){};
};

#endif

/*Adding raiseEvent to this interface makes 
all ui elements cabable of being event sources
and reliminates need for dublicate code in the 
individual UI objects.
*/