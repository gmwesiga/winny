#ifndef IUserInterface_h
#define IUserInterface_h

class IUserInterface {
    public:
    virtual void show()=0;
    virtual void hide()=0;
    virtual void update()=0;
    virtual ~IUserInterface(){};
};

#endif