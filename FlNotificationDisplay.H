#ifndef _FLSCREEN_H
#define _FLSCREEN_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <string>

class FlNotificationDisplay : public Fl_Group{
    public:
    FlNotificationDisplay();
    void add(std::string message);
    int handle(int e);

    private:
    void restore();
    void minimise();
    Fl_Browser* view;
};
#endif