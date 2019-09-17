#include<FlCreateContactDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>

FlCreateContactDisplay::FlCreateContactDisplay()
:Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y, MENUBAR_AREA.W,MENUBAR_AREA.H+CONTENT_AREA2.H,NAME_CREATE_CONTACT_SCREEN)
{
    box(WINNY_TOP_BORDERBOX);
    align(FL_ALIGN_TOP_LEFT);
    labelfont(WINNY_BOLDFONT);
    labelcolor(WINNY_MAINTITLETEXT_COLOR);

    cName = new Fl_Input(245,144,388,25,"Name");
    set_winny_input_theme(cName);
    cAddress1 = new Fl_Input(246,194,388,25,"Address Line 1");
    set_winny_input_theme(cAddress1);
    cAddress2 = new Fl_Input(246,241,388,25,"Phone Contact");
    set_winny_input_theme(cAddress2);
    cPhone1 = new Fl_Input(247,292,388,25,"Phone");
    set_winny_input_theme(cPhone1);
    isCustomer = new Fl_Check_Button (247,366,100,20,"a customer");
    set_winny_button_theme(isCustomer);
    isEmployee = new Fl_Check_Button(368,366,100,20,"an Employee");
    set_winny_button_theme(isEmployee);
    isSupplier = new Fl_Check_Button(486,366,100,20,"is Supplier");
    set_winny_button_theme(isSupplier);
    btnSave = new Fl_Button(247,413,63,23,"save");
    set_winny_button_theme(btnSave);
    btnCancel = new Fl_Button(317,413,63,23,"cancel");
    set_winny_button_theme(btnCancel);
    holrule1 = new Fl_Box(237,395,773,1);
    holrule1->box(WINNY_TOP_BORDERBOX);
    resizer = new Fl_Box(746,436,6,1);
    resizable(resizer);
};



void FlCreateContactDisplay::show(){
    Fl_Group::show();
};


void FlCreateContactDisplay::hide(){
    Fl_Group::hide();
};


void FlCreateContactDisplay::update(){
    Fl_Group::redraw();
};



UIname FlCreateContactDisplay::id(){
    return "Administrator/New Product";
};