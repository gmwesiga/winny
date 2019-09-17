#ifndef FLOFFPREMISESALEUSERIO_H
#define FLOFFPREMISESALEUSERIO_H

#include <IUserInterface.h>
//#include <IExtEventSource.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>

struct FlOffPremiseSaleUserIO : public Fl_Group, public IUserInterface {
    FlOffPremiseSaleUserIO(int x, int y, int w, int h);
    void show();
    void hide();
    void update();
    void readBuff(MemAddress buff);//filter to products list
    void writeBuff(MemAddress buff);//matches
    UIname id();

    private:
    Fl_Button* btnSave;
    Fl_Button* btnCancel;
    Fl_Input*  salesRepName;
    Fl_Input*  salesDate;
    Fl_Input*  transId;
    Fl_Input*  cashRecieved;
    Fl_Input*  salesAmount;//enter sales reciepts in documents
    Fl_Input*  recievableAmount;
    Fl_Box   *bgbox ,*hr1, *hr2, *hr3, *hr4, *resizer;

    dataset_view *Documents;
    dataset_view *Sales; 

};

#endif