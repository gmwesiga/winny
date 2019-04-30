#ifndef FCONTACTSLISTDISPLAY_H
#define FCONTACTSLISTDISPLAY_H

//#include <IContactsListDisplay.H>
//#include <IExtEventSource.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>


class FlContactsListDisplay :  public Fl_Group {
    public:
    FlContactsListDisplay();

    private:
    Fl_Group       *menuBar;
    Fl_Button      *btnNew, *btnActivateToggle, *btnEdit;
    Fl_Menu_Button *filter;
    Fl_Input       *searchToken;
    dataset_view   *wList;
    
    Fl_Box         *menuBarResizer;
};

#endif