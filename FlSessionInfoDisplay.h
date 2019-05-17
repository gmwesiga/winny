#ifndef _ISessionInfoDisplay_h
#define _ISessionInfoDisplay_h

#include "ISessionInfoDisplay.h"
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Output.H>

class FlSessionInfoDisplay : public Fl_Group, public ISessionInfoDisplay {
    public:
    FlSessionInfoDisplay(string sessionId="Unkown User");
    void sessionId(string id);
    void show();
    void hide();
    void update();
    UIname id();

    private:
    Fl_Output* _id;
    ~FlSessionInfoDisplay(){ delete _id;};
};

#endif