#ifndef CREATEPRODUCTDISPLAY_H
#define CREATEPRODUCTDISPLAY_H

//#include <IExtEventSource.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>
#include <IUserInterface.h>

class FlCreateProductDisplay : public Fl_Group , public IUserInterface{
    public:
    FlCreateProductDisplay(int x, int y, int w, int h);//pass window;
    void show();
    void hide();
    void update();   
    UIname id();

    private:
    Fl_Input *prodName, 
             *total, 
             *costPrice, 
             *sellingPrice, 
             *prodDesc;
    Fl_Check_Button *isCompound;
    Fl_Button *btnAdd;
    Fl_Button *btnclear;
    Fl_Button *btnClearAll, *btnSave, *btnCancel;
    dataset_view *components;
    Fl_Box *holrule1, *holrule2;//like html <HR>
    Fl_Box *resizer;
};

#endif