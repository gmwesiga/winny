#ifndef FLLOCALNAVDISPLAY_H
#define FLLOCALNAVDISPLAY_H

#include <FL/Fl_Tree.H>
#include <IUserInterface.h>

using namespace StdSystem;

class FlLocalNavDisplay : public Fl_Tree, public IUserInterface {
    public:
    FlLocalNavDisplay();
    void show();
    void hide();
    void update();
    void addLink(UIname pageName);
    UIname id(){return "NAVLOCAL";};
};

#endif