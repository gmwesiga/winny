#ifndef _FLNOTIFICATION_H
#define _FLNOTIFICATION_H

#include "IScreen.h"
#include "IExtEventSource.h"
#include "ISessionInfoDisplay.h"
#include "INavDisplay.h"
#include <FlLocalNavDisplay.H>
#include <FlCreateProductDisplay.H>
#include <FlContactsListDisplay.H>
#include <FlCreateContactDisplay.H>
#include <FlNotificationDisplay.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <map>

using namespace StdSystem;

class FlScreen : public IScreen, public Fl_Double_Window{
    public:
    FlScreen();
    const UiStatus status();
    const IProductsListDisplay* productsListDisplay();
    const ISessionInfoDisplay* sessionInfoDisplay();
    const INavDisplay* navDisplay();
    void log(string msg);
    void showfDisplay(UIname sn);
    UIname id(){return "FlWindow";};
    void run();
    void show();
    void hide();
    void update();
    void Attach(StdSystem::IApplication* app);

    private:
    ISessionInfoDisplay* sessionInfo;
    INavDisplay*         navBar;
    IProductsListDisplay* prodList;

    FlLocalNavDisplay*   lnavBar;
    FlCreateProductDisplay* creatProductTab;
    Fl_Box* scrnResizer;
    FlContactsListDisplay *contactsList;
    FlCreateContactDisplay *creatContactTab;
    FlNotificationDisplay *msgs;

    IUserInterface* current;

    std::map<std::string,IUserInterface*> displays;
};

#endif