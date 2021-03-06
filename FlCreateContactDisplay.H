#ifndef CREATECONTACTDISPLAY_H
#define CREATECONTACTTDISPLAY_H

//#include <IExtEventSource.h>
#include<IUserInterface.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>

class FlCreateContactDisplay : public Fl_Group, public IUserInterface {
    public:
    FlCreateContactDisplay();//pass window;
    UIname id();
    void show();
    void hide();
    void update();
    void readBuff(MemAddress buff){buff=nullptr;};
    void writeBuff(MemAddress buff){buff=nullptr;/*should be implemented */};

    private:
    Fl_Input *cName, 
             *cAddress1, 
             *cAddress2, 
             *cPhone1;
    Fl_Check_Button *isCustomer,
            *isEmployee, *isSupplier;
    Fl_Button *btnSave, *btnCancel;
    Fl_Box *holrule1;//like html <HR>
    Fl_Box *resizer;
};

#endif