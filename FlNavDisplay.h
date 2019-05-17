#ifndef _FlNavDisplay_h
#define _FlNavDisplay_h

#include "INavDisplay.h"
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>

class FlNavDisplay : public Fl_Group, public INavDisplay {
    public:
    FlNavDisplay();
    UIname id(){return "winny_1234ffdfg";};
    void show();
    void hide();
    void update();
    void entityName(string id);
    void addNotification(string text, int type);
    void clearNotifications();
    void addResponsibility(string desc);
    void clearResponsibilities();
    void setRoleName(string desc);
    private:
    Fl_PNG_Image * _menuicon_;
    Fl_Box *menuicon;
    ~FlNavDisplay();
};

#endif