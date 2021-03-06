/** \file
 * This file contains the definition of the procedures for the operations
 * specified for an IScreen object. The operations are here defined in
 * terms of operations on Fl_Window objects, and the rest as listed below
 */
#include "IScreen.h"

/** 
 * A Screen is an External Event Source since it captures mouse and key-
 * board events
 */
#include "IExtEventSource.h"


#include <FlCreateProductDisplay.H>
#include <FlContactsListDisplay.H>
#include <FlCreateContactDisplay.H>
#include <FlNotificationDisplay.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>          /**< for labels and backgrounds*/
#include <FL/Fl_Button.H>       /**< For signout buttons*/
#include <FL/Fl_PNG_Image.H>    /**< For a menu icon*/
#include <FL/Fl_Tree.H>         /**< For local navigation*/

#include "FlNavDisplay.h"
#include <FlListDisplay.H>
#include <FlOffPremiseSaleUserIO.H>
#include <FlCashFlowDisplay.H>
#include <FlStockTransactionDisplay.H>
#include "winny_theme.h"
#include <FWidgetSizes.H>
#include <FL/fl_ask.H>
#include <WinnyNames.H>
#include <IApplicationTypes.H>
#include <CommBus.H>
#include <pthread.h>
#include <iostream>

#include <map>      /**< dictionary of function screen pointers*/

#include <IApplicationTypes.H>//UIODNames for bind

using namespace StdSystem;

class FlScreen : public IScreen, public Fl_Double_Window{
    public:
    FlScreen();
    const UiStatus status();
    void log(string msg);
    void switchToDisplay(Winny::UserIODevName sn); 
    UIname id(){return "FlWindow";};
    void run();
    int run()
    void show();
    void hide();
    void update();
    void Attach(StdSystem::IApplication* app);
    void writeBuff(MemAddress buff);
    void readBuff(MemAddress buff){buff=nullptr;}
    int handle(sEvent,void *eData=nullptr);
    
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


using Winny::UserInputArg;

#define WBUFSIZE 125 //Screen Titles shouldn't be more than these characters

static void cbGoToPage ( Fl_Widget* w, void* o); 

static IScreen* SCREEN = nullptr;

/**
 * constructor initialises base implementation fl_window with design 
 * specification height and width
 */
FlScreen::FlScreen()
    : 
    Fl_Double_Window(SCRN_WIDTH,SCRN_HEIGHT),
    current(nullptr),
    listTransactionDisplayInstance(nullptr), 
    msgs(nullptr)

{
    SCREEN = this;
    init_ui();
    begin();

    titleBgBox = new Fl_Box(0,DY(70),SCRN_WIDTH,27);
    titleBgBox->box(WINNY_THIN_BORDERBOX);
    titleBgBox->color(fl_rgb_color(251, 251, 251));

    titlebox = new Fl_Box(DX(261),DY(75),CONTENT_AREA2.W,19);
    titlebox->box(FL_NO_BOX);
    titlebox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT |FL_ALIGN_BOTTOM);
    titlebox->labelcolor(WINNY_TITLETEXT_COLOR);
    titlebox->labelsize(WINNY_TITLETEXT_FONTSIZE);
    titlebox->color(titleBgBox->color());
    titlebox->labelfont(WINNY_BOLDFONT);

    logo = new Fl_Box(DX(50),DY(17),113,13,"WINNY BUSINESS");
    logo->labelsize(9);
    logo->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT_TOP);
    logo->labelcolor(WINNY_LINKTEXT_COLOR);
    logo->labelfont(WINNY_BOLDFONT);
    
    shopNameLbl = new Fl_Box(DX(50),DY(29),172,21,"Xyz Test Enterprises");
    shopNameLbl->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT_TOP);
    shopNameLbl->labelsize(11);
    shopNameLbl->labelcolor(WINNY_NORMALTEXT_COLOR);
    shopNameLbl->labelfont(WINNY_BOLDFONT);

    switchShopBtn = new Fl_Menu_Button(DX(882),DY(29),80,21,"Switch Shop");
    switchShopBtn->box(WINNY_NO_BORDERBOX);
    switchShopBtn->color(WINDOW_COLOR());
    switchShopBtn->labelcolor(logo->labelcolor());
    switchShopBtn->labelsize(10);
    switchShopBtn->copy_tooltip("View other Shops connected to your account");
//    switchShopBtn->add("gabbage");

    logOutBtn = new Fl_Button(DX(961),DY(29),49,21,"Log Out");
    logOutBtn->box(switchShopBtn->box());
    logOutBtn->color(switchShopBtn->color());
    logOutBtn->labelcolor(switchShopBtn->labelcolor());
    logOutBtn->labelsize(switchShopBtn->labelsize());

    _menuicon_ = new Fl_PNG_Image("menuicon.png");
    menuicon =  new Fl_Menu_Button(DX(50),DY(75),20,16,"Administrator");//label for testing only
    menuicon->labelfont(WINNY_NORMALFONT);
    menuicon->labelsize(WINNY_NORMALTEXT_FONTSIZE);
    menuicon->labelcolor(WINNY_TITLETEXT_COLOR);
    menuicon->image(_menuicon_);
    menuicon->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT|FL_ALIGN_IMAGE_NEXT_TO_TEXT);
    menuicon->box(FL_NO_BOX);
    menuicon->add("Preferances/Settings");

    localNav = new Fl_Tree(DX(50),DY(97),/*192*/150,432);
    localNav->showroot(0); //remove it
    localNav->usericon(nullptr);
    localNav->connectorstyle(FL_TREE_CONNECTOR_NONE);
    localNav->connectorwidth(0);
    localNav->linespacing(5);
    localNav->selection_color(SELECTION_BACKCOLOR());
    localNav->marginleft(10);
    localNav->selectbox(WINNY_THIN_BORDERBOX);
    localNav->item_labelfgcolor(WINNY_LINKTEXT_COLOR);
    localNav->item_labelsize(WINNY_NORMALTEXT_FONTSIZE);
    localNav->callback(cbGoToPage,(void*)this);

    scrnResizer = new Fl_Box(798,520,44,1);
    resizable((Fl_Widget*)scrnResizer);
    //msgs = new FlNotificationDisplay();
    
    color(WINDOW_COLOR());
    set_winny_window_theme(this);//do this before creating invisible resize box

    end();

    //fl_alert("we are here");
};



IScreen* IScreen::screen(){
    return new FlScreen();
};


void FlScreen::writeBuff(MemAddress buff){
    //write roles, operating unit names
    log ("In FlScreen::WriteBuffer");
    Winny::AppInfo* appState = (Winny::AppInfo*)buff;
   // fl_alert(appState->sessionInfo.currentOpgUnit.name);
    //Current operating Unit
    shopNameLbl->copy_label(appState->sessionInfo.currentOpgUnit.name);
    //Other operating Units;
    for(int i=0; i<appState->sessionInfo.operatingUnits.size(); ++i ){
        log(string("adding...").append(appState->sessionInfo.operatingUnits[i].name));
        switchShopBtn->add(appState->sessionInfo.operatingUnits[i].name,0,0,0,0);
    };
    setUpRole(appState->sessionInfo.role);
    redraw();
     return;   
};




void FlScreen::setUpRole(Winny::Role o){;
    if(o.name=="Admin"){
        //draw all admin menus
        constructDisplay(Winny::UserIODevName::UIOQ_CASH_FLOW);
        constructDisplay(Winny::UserIODevName::UIOQ_STOCK_MVT);
        constructDisplay(Winny::UserIODevName::UIOQ_SEARCH_PRODUCTS);
        constructDisplay(Winny::UserIODevName::UIOQ_SEARCH_CONTACTS);
        constructDisplay(Winny::UserIODevName::UIOQ_SEARCH_TRANSACTIONS);
        constructDisplay(Winny::UserIODevName::UIOQ_CREATE_PRODUCT);
        constructDisplay(Winny::UserIODevName::UIOQ_SEARCH_CONTACTS);
        constructDisplay(Winny::UserIODevName::UIOQ_CREATE_ROLE);
        constructDisplay(Winny::UserIODevName::UI0Q_CREATE_TRANS_SALES_CASH);
        constructDisplay(Winny::UserIODevName::UIOQ_CREATE_TRANS_SALES_REP);
        constructDisplay(Winny::UserIODevName::UIOQ_CREATE_TRANS_SALES_CREDIT);
        constructDisplay(Winny::UserIODevName::UIOQ_CREATE_TRANS_GOODS_DELIVERY);
        constructDisplay(Winny::UserIODevName::UIOQ_CREATE_TRANS_GOODS_RECIEVED);
        constructDisplay(Winny::UserIODevName::UIOQ_CREATE_CONTACT);

    }else{
        //draw role specif menus
    }
    return;
}



IUserInterface* FlScreen::constructDisplay(Winny::UserIODevName n){
    IUserInterface* ret;
    Fl_Group::current(this);
    
    //first reset sizes to design
    int wid(w()); int hei(h()); int xx(x()); int yy(y());
    resize(xx,yy,SCRN_WIDTH,SCRN_HEIGHT);
    //UIname tdn; /*for temporary display name, used by sections of code for storage*/

    switch (n){
        case Winny::UIOQ_SEARCH_PRODUCTS:
             ret = new FlListDisplay();
             ((FlListDisplay*)ret)->id("Product Management / Search");
             ((FlListDisplay*)ret)->sethandler(productListCb);
            break;
        case Winny::UIOQ_CREATE_PRODUCT:
            ret = new FlCreateProductDisplay(
                CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H
            );
            break;

        case Winny::UIOQ_CREATE_TRANS_SALES_REP:
            ret = new FlOffPremiseSaleUserIO(
                CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H);
            break;

        case Winny::UIOQ_CREATE_TRANS_GOODS_RECIEVED:
            
            if(!listTransactionDisplayInstance)
                listTransactionDisplayInstance = new FlStockTransactionDisplay();
            ret = listTransactionDisplayInstance; //only one exists..
            ret->id(NAME_GOODS_RECIEVED_SCREEN);
            break;

        case Winny::UIOQ_CREATE_TRANS_GOODS_DELIVERY:

            if(!listTransactionDisplayInstance)
                listTransactionDisplayInstance = new FlStockTransactionDisplay();
            ret = listTransactionDisplayInstance; //only one exists..
            ret->id(NAME_DELIVERY_SCREEN);
            break;

        case Winny::UIOQ_CREATE_TRANS_SALES_CREDIT:
     
            if(!listTransactionDisplayInstance)
                listTransactionDisplayInstance = new FlStockTransactionDisplay();
            ret = listTransactionDisplayInstance; //only one exists..
            ret->id(NAME_INVOICE_SCREEN);
            break; 

        case Winny::UIOQ_SEARCH_CONTACTS:
             ret = new FlListDisplay();
             ((FlListDisplay*)ret)->id("Contact Management / Search");
             ((FlListDisplay*)ret)->sethandler(nullptr);
            break;

        case Winny::UIOQ_CREATE_CONTACT:
            ret = new FlCreateContactDisplay();
            break;

        case Winny::UIOQ_CASH_FLOW:
            ret = new FlCashFlowDisplay();
            break;

            
        default:
            ret = nullptr;
            break;
    }
    //connect to app
    if (ret){
        log("New Display just created");
        bind(ret,n);
        ret->Attach(this); //subscribe self
        ret->hide();
    }
    //Reset sizes
    resize(xx,yy,wid,hei);
    return ret;
};



int FlScreen::bind(IUserInterface* dev,Winny::UserIODevName devId){
//only used to bind / write mapping
    if(dev){
        displays[devId]=dev;
        addTomenu(dev,devId);
        return 1;
    }
    return 0;
};





void FlScreen::addTomenu(IUserInterface* dev,Winny::UserIODevName devId){
    /*Add dev->id to menu*/
    if(!dev)return;
    Winny::UserIODevName* o;
    o = new Winny::UserIODevName(devId);
   // menus.push_back(o);
    localNav->add(dev->id().c_str());
    localNav->find_item(dev->id().c_str())->user_data((void*)o );
    localNav->redraw();
};



/*Returns the current status of the Screen*/
const UiStatus FlScreen::status(){
    return UiStatus::IDLE;
};



/*Calls the implementation Window object show()*/
static bool raisedAlready=false;
void FlScreen::show(){
    if (!raisedAlready){
       // log("Show Called");
       //fl_alert("About to raise signal");
       args.sourceInterface = this;
       args.event = SigUserIOready;
       args.args = this;
        handle(SigUserIOready,&args);
        raisedAlready = true;
    }
    //application calls writebuffer;
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






IUserInterface* FlScreen::resolve(Winny::UserIODevName devId){
    auto iter = displays.find(devId);
    if(iter != displays.cend())//if exists
        return displays.at(devId);
    //else
    return nullptr;
};




void FlScreen::switchToDisplay(Winny::UserIODevName dname){

    auto iter = resolve(dname);
    if(!iter)//if not exists try creating it
    {
        iter = constructDisplay(dname);
        if(!iter)//not implemented, return, nothing to do
        {
            log("You tried to access a display that is not implemented");
            return;
        }//we get here if we created it, so bind it

    }//we get here if exists and binded
        log("found it");

    //first we check and handle special case displays:
    if( dname==Winny::UIOQ_CREATE_TRANS_SALES_CREDIT)
        listTransactionDisplayInstance->writeBuff(new Winny::salesInvoice());

    //if( (dname==Winny::uio )
      //  listTransactionDisplayInstance->writeBuff(new Winny::cashSale());
        
    if( dname==Winny::UIOQ_CREATE_TRANS_GOODS_RECIEVED )
        listTransactionDisplayInstance->writeBuff(new Winny::rsLoadIn());

    if(  dname==Winny::UIOQ_CREATE_TRANS_GOODS_DELIVERY)
        listTransactionDisplayInstance->writeBuff(new Winny::rsLoadOut());


       if(current)current->hide();
        iter->show();
        current = iter;
        //update title
        //fl_alert(current->id().c_str());
        std::size_t pos = current->id().find_last_of('/'); //position of title in id string
        pos++;
        if(pos>current->id().size())pos = 0;
        titlebox->copy_label(current->id().substr(pos).c_str());
        //redraw();
        return; 
 
};




void FlScreen::Attach(StdSystem::IApplication* app){
    IUserInterface::Attach(app);
    //attach to child windows too if any
    UIname s;
    for(auto ui =displays.begin(); ui != displays.end(); ++ui){
        ui->second->Attach(app);
    };

    //store to attach to child displays created later
    _app_ = app;
    return;
};




void FlScreen::log(string msg){
    if (msgs) msgs->add(msg);
    return;
};




/*static handlers*/

static void cbGoToPage ( Fl_Widget* w, void* o){
/*cbGoToPage is called whenever a user selects a local menu function.
//its evect is to raise a navigation event to the application
//the application uses the string of the page name to find and display
//the page.*/

    Fl_Tree* tree = (Fl_Tree *)w;
    Fl_Tree_Item* itm = tree->callback_item();
    //char path[WBUFSIZE];

    switch (tree->callback_reason())
    {
        case FL_TREE_REASON_SELECTED:
            if(itm->user_data())
                ((IUserInterface*)o)->handle(CmdNavigateTo,itm->user_data());
            break;
    
        default:
            break;
    }
};

static bool isUserInputWake = false; //we can be awakened by other lib events we not interested in 
static void* lastEvtArgs;
static StdSystem::sEvent lastEvt;

 int FlScreen::handle(sEvent e,void *eData){
     isUserInputWake = true;
     lastEvt = e;
     lastEvtArgs = eData;
     return 1;
 };

 //adpter function to lower pthread layer interface
void* pthread_run(void* arg){

    Bus::Message msg;
    Fl::lock();
    
    while(Fl::wait()){
        if(!isUserInputWake)continue;
        Winny::UserInputArg* i = (Winny::UserInputArg*)lastEvtArgs;
        //std::cout<<"Wait returned address is"<<i->sourceInterface<<"\n";
        msg.sourcePort = StdSystem::UIO_PORT;
        msg.message = lastEvtArgs; //IUserInterface::args
        msg.opcode = lastEvt;
        Bus::sendTo(StdSystem::APP_PORT,msg);
        isUserInputWake = false;
    };
    msg.sourcePort = StdSystem::UIO_PORT;
    msg.message = nullptr;
    msg.opcode = SigSHUTDOWN;
    Bus::sendTo(StdSystem::APP_PORT,msg);
}

void FlScreen::run(){
    show();
    pthread_t id;
    pthread_create(&id,nullptr,pthread_run,nullptr);  
    pthread_detach(id);
};

    