#include "FlScreen.h"
#include "FlSessionInfoDisplay.h"
#include "FlNavDisplay.h"
#include <FlProductsListDisplay.H>
#include "winny_theme.h"
#include <FWidgetSizes.H>


//#define SCRN_WIDTH 1077 -47 //-40 hack
//#define SCRN_HEIGHT 511

/*constructor initialises base implementation fl_window with design
 *specification height and width*/
FlScreen::FlScreen(): Fl_Window(SCRN_WIDTH,SCRN_HEIGHT){
    init_ui();
    begin();
    sessionInfo = new FlSessionInfoDisplay();
    navBar = new FlNavDisplay();
    prodList = new FlProductsListDisplay();
    //prodList->deactivate();
    prodList->hide();//testing
    lnavBar  = new FlLocalNavDisplay();
    creatProductTab = new FlCreateProductDisplay(this);
    creatProductTab->hide();

    //contactsList = new FlContactsListDisplay();
    creatContactTab = new FlCreateContactDisplay();
    color(WINDOW_COLOR());
    set_winny_window_theme(this);//do this before creating invisible resize box
    scrnResizer = new Fl_Box(761,424,140,10);
    resizable((Fl_Widget*)scrnResizer);
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
