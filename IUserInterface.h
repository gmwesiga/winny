#ifndef IUserInterface_h
#define IUserInterface_h
#include <string>
#include <IExtEventSource.h>

typedef std::string UIname; // name of IUserInterface Name
typedef MemAddress void*;

class IUserInterface :  public virtual StdSystem::IExtEventSource {
    public:
    virtual void show()=0;
    virtual void hide()=0;
    virtual void update()=0;
    virtual UIname id()=0;
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

Desided to typedef void* to get an alias that will still
make sense if i choose to change the type to a more type safe
class later based on unions
*/