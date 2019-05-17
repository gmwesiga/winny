#include "FlScreen.h"
#include "FlSessionInfoDisplay.h"
#include "FlNavDisplay.h"
#include <FlProductsListDisplay.H>
#include "winny_theme.h"
#include <FWidgetSizes.H>
#include <FL/fl_ask.H>


//#define SCRN_WIDTH 1077 -47 //-40 hack
//#define SCRN_HEIGHT 511

/*constructor initialises base implementation fl_window with design
 *specification height and width*/
FlScreen::FlScreen(): Fl_Double_Window(SCRN_WIDTH,SCRN_HEIGHT){
    init_ui();
    begin();
    scrnResizer = new Fl_Box(761,424,140,10);
    resizable((Fl_Widget*)scrnResizer);
    
    sessionInfo = new FlSessionInfoDisplay();
    
    navBar = new FlNavDisplay();
    
    lnavBar  = new FlLocalNavDisplay();
    displays[lnavBar->id()] = lnavBar;
    
    prodList = new FlProductsListDisplay();
    displays[prodList->id()]= prodList;
    prodList->hide();
    lnavBar->addLink(prodList->id());
    
    creatProductTab = new FlCreateProductDisplay(this);
    displays[creatProductTab->id()]=creatProductTab;
    creatProductTab->hide();
    lnavBar->addLink(creatProductTab->id());

    contactsList = new FlContactsListDisplay();
    displays[contactsList->id()]= contactsList;
    current = contactsList; //set to last to create
    lnavBar->addLink(contactsList->id());

    /*creatContactTab = new FlCreateContactDisplay();*/

    msgs = new FlNotificationDisplay();
    
    color(WINDOW_COLOR());
    set_winny_window_theme(this);//do this before creating invisible resize box

    log("Hello World");
    log("Loading templates...");
    log("Loading templates...");
    log("Loading templates...");

    end();

};

/*Returns the current status of the Screen*/
const UiStatus FlScreen::status(){
    return UiStatus::IDLE;
};

const IProductsListDisplay* FlScreen::productsListDisplay(){
    return 0;
};


void FlScreen::run(){
    Fl::run();
};

/*Calls the implementation Window object show()*/
void FlScreen::show(){
    Fl_Window::show();
};

/*Calls the implementation window object hide()*/
void FlScreen::hide(){
    Fl_Window::hide();
};

/*calls fl's redraw to reshedule a redraw*/
void FlScreen::update(){
    Fl_Window::redraw();
};

const ISessionInfoDisplay* FlScreen::sessionInfoDisplay(){
    return sessionInfo;
};

const INavDisplay* FlScreen::navDisplay(){
    return 0;
};

void FlScreen::showfDisplay(UIname dname){
    auto iter = displays.find(dname);
    if(iter != displays.cend())//if exists
    {
        current->hide();
        displays.at(dname)->show();
        current = displays.at(dname);
    }
};

void FlScreen::Attach(StdSystem::IApplication* app){
    IUserInterface::Attach(app);
    //attach to child windows too
    UIname s;
    for(auto ui =displays.begin(); ui != displays.end(); ++ui){
        ui->second->Attach(app);
    };
    return;
};

void FlScreen::log(string msg){
    msgs->add(msg);
    return;
};