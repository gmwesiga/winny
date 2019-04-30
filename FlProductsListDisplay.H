#ifndef FPRODUCTSLISTDISPLAY_H
#define FPRODUCTSLISTDISPLAY_H

#include <IProductsListDisplay.H>
#include <IExtEventSource.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>


class FlProductsListDisplay : public IProductsListDisplay , public Fl_Group, public StdSystem::IExtEventSource {
    public:
    FlProductsListDisplay();
    void show();
    void hide();
    void update();
    void AddSortOption(string opt);
    void clearSortOptions();
    string sortOption();
    string searchKey();
    void addToshowList(Product); 
    void clearShowList();
    string selected();
    void run(){return;};

    private:
    Fl_Group       *menuBar;
    Fl_Button      *btnNew, *btnActivateToggle, *btnEdit;
    Fl_Menu_Button *filter;
    Fl_Input       *searchToken;
    dataset_view   *prdList;
    
    Fl_Box         *menuBarResizer;
};

#endif