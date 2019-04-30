#ifndef _FLSCREEN_H
#define _FLSCREEN_H

#include "IScreen.h"
#include "IExtEventSource.h"
#include "ISessionInfoDisplay.h"
#include "INavDisplay.h"
#include <FlLocalNavDisplay.H>
#include <FlCreateProductDisplay.H>
#include <FlContactsListDisplay.H>
#include<FlCreateContactDisplay.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

using namespace StdSystem;

class FlScreen : public IScreen, public Fl_Window, public IExtEventSource{
    public:
    FlScreen();
    const UiStatus status();
    const IProductsListDisplay* productsListDisplay();
    const ISessionInfoDisplay* sessionInfoDisplay();
    const INavDisplay* navDisplay();
    void run();
    void show();
    void hide();
    void update();

    private:
    ISessionInfoDisplay* sessionInfo;
    INavDisplay*         navBar;
    IProductsListDisplay* prodList;

    FlLocalNavDisplay*   lnavBar;
    FlCreateProductDisplay* creatProductTab;
    Fl_Box* scrnResizer;
    FlContactsListDisplay *contactsList;
    FlCreateContactDisplay *creatContactTab;
};

#endif