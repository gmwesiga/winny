#ifndef _FLNOTIFICATION_H
#define _FLNOTIFICATION_H

#include "IScreen.h"
#include "IExtEventSource.h"
//#include "ISessionInfoDisplay.h"
#include "INavDisplay.h"
//#include <FlLocalNavDisplay.H>
#include <FlCreateProductDisplay.H>
#include <FlContactsListDisplay.H>
#include <FlCreateContactDisplay.H>
#include <FlNotificationDisplay.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>/*for labels and backgrounds*/
#include <FL/Fl_Button.H> /*For signout buttons*/
#include <FL/Fl_PNG_Image.H>/*For a menu icon*/
#include <FL/Fl_Tree.H>/*For local navigation*/
#include <map>/*dictionary of function screen pointers*/
#include <IApplicationTypes.H>//UIODNames for bind

using namespace StdSystem;

class FlScreen : public IScreen, public Fl_Double_Window{
    public:
    FlScreen();
    const UiStatus status();
    void log(string msg);
    void switchToDisplay(Winny::UserIODevName sn); 
    /*if no pending prompts, switch to screen named sn*/
    
    UIname id(){return "FlWindow";};
    void run();

    /**
     * Run for specified duration or until user requests an operation
     * write out the requested operation in, and the specified arguments 
     * if any
     * 
     * @param[out] ReqOper The operation that was requested by user if
     * any (OCC is positive interger)
     * @param[in:out] ReaOperArgs The arguments to the requested operation
     */
    int run()
    void show();
    void hide();
   // int handle(int e);//override so we can tap the Show/ load event
    void update();
    void Attach(StdSystem::IApplication* app);
    void writeBuff(MemAddress buff);
    void readBuff(MemAddress buff){buff=nullptr;}

/*To handle cases of some child iopages need to communicate with the main/parent Iscreen
  we have added handler here: child iopages can send some custome events to the Iscreen
  or even to the application itself, which then routes them to the Iscreen through handle
  in addition to this interface, The static function screen returns a global reference */
    int handle(sEvent,void *eData=nullptr);
  /**Also to implement aggregation. Flscreen shall pass self to all UI Interfaces it creates*
   */
    
    private:
    IUserInterface* constructDisplay(Winny::UserIODevName n);
    /*Returns right IUserInterface that implements name n, null pointer on failur*/

    void setUpRole(Winny::Role o);
    /*Create appropriate Windows etc*/


    int bind(IUserInterface* dev,Winny::UserIODevName devId);

    IUserInterface* resolve(Winny::UserIODevName devId);
    /*Return address/ value of screen Binded to devId or construct
    / it and bind if not exists. on failure, return null pointer*/

    void addTomenu(IUserInterface* dev,Winny::UserIODevName devId);
    /*Add dev->id to menu*/

    Fl_Box* scrnResizer;
    Fl_Box* titleBgBox;
    Fl_Box* navTitleBgBox;
    Fl_Box* logo;
    Fl_Box* titlebox;
    Fl_Tree* localNav;

    Fl_Menu_Button* switchShopBtn;
    Fl_Button* logOutBtn;
    Fl_Box* shopNameLbl;
    Fl_PNG_Image* _menuicon_;
    Fl_Menu_Button* menuicon;//the hidden menu button that actually has the menue
    Fl_Button* fakemenu; //the visible menueicon button

    FlNotificationDisplay *msgs;

    IUserInterface* current;
    /*address of currently displayed screen. pointer points to element in 
     *the displays map*/

    std::map<Winny::UserIODevName,IUserInterface*> displays;
    /*dictonary/list of all screens currently created in memory*/

   // std::vector<Winny::UserIODevName *> menus;
    /*Stores Winny::UserIODevName of currently created screens*/

    IApplication* _app_;

    IUserInterface *listTransactionDisplayInstance;
    /*This variable is used to track if a listTransactions Display has already been created
      the design is such that only one such display exists, and all references point to it
      initially its false,*/
};

#endif