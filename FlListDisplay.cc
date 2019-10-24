#include <FlListDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>
#include <IApplicationTypes.H> // createNew product screen name
#include <FL/fl_ask.H>
#include <stdlib.h>
using std::printf;

/*The FlListDisplay is a generic list displayer page It accepts
**a query input from the user from a text box, calls a query handler
**and passing it the query and the application object, and itself.
**With this arrangment, the query handler raises a query event/command
**to the application. the appliction handler services the query with matchs
**and returns, the query handler also returns. By switching the query
**handlers or creating diffent fllistDisplay objects with different
**querry handlers, we are able to reuse the functionality of this class
**for many uses
**the application*/

//Fl CallBacks
static void winProc ( Fl_Widget* w, void* o);



FlListDisplay::FlListDisplay()
    :Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H)
    ,output(0,0), cb(nullptr)
    {
        int MBY = MBH;
        int mbh = 20;
        begin();
        box(WINNY_NO_BORDERBOX);
        color(WINDOW_COLOR());
        menuBar = new Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y,MENUBAR_AREA.W,65);
        /*Parent responsible for drawing title*/
        int bh = SLWH;
        int y = 32;
        btnNew = new Fl_Button(
            DMX(5),DMY(MBY),48,mbh,"New(+)");
        set_winny_button_theme(btnNew);
        btnNew->color(ACCCOLOR);
        btnNew->labelcolor(FL_WHITE);
        btnNew->box(WINNY_THICK_BORDERBOX);
        btnNew->callback(winProc,(void*)this);
        //btnNew->when(btnNew->when()&FL_WHEN_CHANGED);

        filter = new Fl_Menu_Button(
            DMX(470),DMY(MBY),80,mbh,"Filter by");
        set_winny_button_theme(filter);
        filter->callback(winProc,(void*)this);

        btnActivateToggle = new Fl_Button(
            DMX(53),DMY(MBY),66,mbh,"Activate");
        set_winny_button_theme(btnActivateToggle);
        btnActivateToggle->callback(winProc,(void*)this);

        btnEdit = new Fl_Button(
            DMX(118),DMY(MBY),65,mbh,"Edit");
        set_winny_button_theme(btnEdit);
        btnEdit->callback(winProc,(void*)this);

        searchToken = new Fl_Input(
            DMX(550),DMY(MBY),196,mbh,"Search ");
        set_winny_input_theme(searchToken);
        //searchToken->color(FL_WHITE);
        //searchToken->alig;
        searchToken->callback(winProc,(void*)this);
        searchToken->when(FL_WHEN_CHANGED);
        searchToken->align(FL_ALIGN_INSIDE);

        menuBarResizer = new Fl_Box(DMX(388),DMY(MBY+mbh+1),10,0);
        menuBarResizer->box(WINNY_NO_BORDERBOX);
        menuBar->resizable(menuBarResizer);

        menuBar->end();
        //menuBar->box(WINNY_TOP_BORDERBOX);
        itemsList = new dataset_view(DCX(0),DCY(0),CONTENT_AREA2.W,
        CONTENT_AREA2.H);
        itemsList->box(WINNY_TOP_BORDERFRAME);
        itemsList->table_box(WINNY_TOP_BORDERFRAME);
        //itemsList->box(WINNY_TOP_BORDERBOX);
        itemsList->row_header(1);
        itemsList->col_auto_resize(1);
        itemsList->attach_dataset(&output);
        resizable((Fl_Widget*)itemsList);
        end();

        queryCond.searchKey = nullptr;
    return;
};

    void FlListDisplay::show(){
        searchToken->take_focus();
        Fl_Group::show();
        update();
        return;
    };
    void FlListDisplay::hide(){
        Fl_Group::hide();
        return;
    };

    void FlListDisplay::update(){
        //if(!cb)return;
        //cb(this,(int)Query::REFRESH);
        Fl_Group::redraw();
    }




void FlListDisplay::writeBuff(MemAddress buff){
    //assumes buff is MemAddress of a struct Query
    //when it returns, it has copied the output member of 
    //the struct into the display, application can free resources
    
    //printf("In writeBuff\n");
    //assume buff is a pointer to a useroutputarg
    Winny::UserOutputArg* bf = (Winny::UserOutputArg*)buff;
    
    if(bf->event == CmdUpdateProductsList){
        //output args of CmdUpdateProductList is dataset

        dataset* results = (dataset*)bf->args;
        output.copyfrom( *results); //wierd copy;
        //printf("size of output.rows() is %d\n", results->rows());
        update();
    }


    //client is responsible to free buff;
};



static Winny::UserIODevName pgname = Winny::UserIODevName::UIOQ_CREATE_PRODUCT;
//is Called Whenever user clicks Create Product Link

static void winProc ( Fl_Widget* w, void* o){
    FlListDisplay *me = (FlListDisplay*)o;
    me->extEventsHandler(w);
};    



 void FlListDisplay::extEventsHandler(Fl_Widget* o){

     if (!cb)return; //Return if no callback set
     //fl_alert("in handler..");
     if(o==btnNew){
         cb(this,(int)CREATE); //callback raises Application specific Create Event
    
     }else if(o==btnEdit){
         cb(this,(int)Query::EDIT);

     }else if(o==searchToken){
         cb(this,(int)Query::SEARCH);
     }
    return;
 }



/*Specialise ListDisplay for to display a products list and call product managment commands*/
void productListCb(IUserInterface *o, int e){

  //Note: specialisers don't need to be passed an application object
  //      IUserInterface is enough as they can use it to raise specific
  //      application events using IUserInterface.raiseEvents. after converting from 
  //      the IUserInterface generic ones.


    FlListDisplay::Query E = (FlListDisplay::Query)e;
    
    //holds name of display for use by CREATE event
    Winny::UserIODevName pname;
    switch(E){
        case FlListDisplay::Query::REFRESH:
        {
            Winny::UserInputArg args;
            args.event = CmdUpdateProductsList;
            //args.sourceInterface = o;
            args.args = nullptr;
            o->raiseEvent(CmdUpdateProductsList,&args);
        }
        break;
        case FlListDisplay::Query::CREATE:
            pname = Winny::UserIODevName::UIOQ_CREATE_PRODUCT;
            o->raiseEvent(CmdNavigateTo,&pname);
        break;
        case FlListDisplay::Query::SEARCH:
        {
            Winny::UserInputArg args;
            args.event = CmdUpdateProductsList;
            args.sourceInterface = o;
            args.args = nullptr;
            o->raiseEvent(CmdUpdateProductsList,&args);
        }
        break;
    }
};




/*Lesson on why you should throw errors instead of ignoring action */