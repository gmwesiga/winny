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
    ,output(nullptr), cb(nullptr)
    {
        begin();
        box(WINNY_NO_BORDERBOX);
        color(WINDOW_COLOR());
        menuBar = new Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y,MENUBAR_AREA.W,65);
        /*Parent responsible for drawing title*/
        int bh = SLWH;
        int y = 32;
        btnNew = new Fl_Button(
            DX(266),DCY(y),48,bh,"New(+)");
        set_winny_button_theme(btnNew);
        btnNew->color(ACCCOLOR);
        btnNew->labelcolor(FL_WHITE);
        btnNew->box(WINNY_THICK_BORDERBOX);
        btnNew->callback(winProc,(void*)this);
        //btnNew->when(btnNew->when()&FL_WHEN_CHANGED);

        filter = new Fl_Menu_Button(
            DX(731),DCY(y),80,bh,"Filter by");
        set_winny_button_theme(filter);
        filter->callback(winProc,(void*)this);

        btnActivateToggle = new Fl_Button(
            DX(314),DCY(y),66,bh,"Activate");
        set_winny_button_theme(btnActivateToggle);
        btnActivateToggle->callback(winProc,(void*)this);

        btnEdit = new Fl_Button(
            DX(379),DCY(y),65,bh,"Edit");
        set_winny_button_theme(btnEdit);
        btnEdit->callback(winProc,(void*)this);

        searchToken = new Fl_Input(
            DX(811),DCY(y),196,bh,"Search ");
        set_winny_input_theme(searchToken);
        //searchToken->color(FL_WHITE);
        //searchToken->alig;
        searchToken->callback(winProc,(void*)this);
        searchToken->when(FL_WHEN_CHANGED);
        searchToken->align(FL_ALIGN_INSIDE);

        menuBarResizer = new Fl_Box(DX(649),DY(100),10,0);
        menuBarResizer->box(WINNY_NO_BORDERBOX);
        menuBar->resizable(menuBarResizer);

        menuBar->end();
        //menuBar->box(WINNY_TOP_BORDERBOX);
        itemsList = new dataset_view(CONTENT_AREA2.X,DCY(65),CONTENT_AREA2.W,
        CONTENT_AREA2.H);
        itemsList->box(WINNY_BOTTOM_BORDERBOX);
        //itemsList->table_box(WINNY_BOTTOM_BORDERBOX);
        itemsList->box(WINNY_TOP_BORDERBOX);
        itemsList->row_header(1);
        itemsList->col_auto_resize(1);
        resizable((Fl_Widget*)itemsList);
        end();

        queryCond.searchKey = nullptr;
    return;
};

    void FlListDisplay::show(){
        Fl_Group::show();
        update();
        return;
    };
    void FlListDisplay::hide(){
        Fl_Group::hide();
        return;
    };

    void FlListDisplay::update(){
        if(!cb)return;
        //cb(this,(int)Query::REFRESH);
        Fl_Group::redraw();
    }




void FlListDisplay::writeBuff(MemAddress buff){
    //assumes buff is MemAddress of a struct Query
    //when it returns, it has copied the output member of 
    //the struct into the display, application can free resources

    using Winny::Query;
    Query* bf = (Query*)buff;
    dataset* output = new dataset(bf->outPut->rows(), bf->outPut->cols());
    for (int r = 0; r<output->rows(); r++){
        for(int c=0; c<output->cols(); c++){
            output->data(r,c,bf->outPut->data(r,c));
        }
    }
    if(!output)return;
    itemsList->attach_dataset(output);
   
};



static Winny::UserIODevName pgname = Winny::UserIODevName::UIOQ_CREATE_PRODUCT;
//is Called Whenever user clicks Create Product Link

static void winProc ( Fl_Widget* w, void* o){
    FlListDisplay *me = (FlListDisplay*)o;
    me->extEventsHandler(w);
};    



 void FlListDisplay::extEventsHandler(Fl_Widget* o){

     if (!cb)return; //Return if no callback set
    
     if(o==this->btnNew){
         cb(this,(int)CREATE); //callback raises Application specific Create Event
    
     }else if(o==this->btnEdit){
         cb(this,(int)Query::EDIT);

     }else if(o==this->searchToken){
         cb(this,(int)Query::SEARCH);
     }
    return;
 }




void productListCb(IUserInterface *o, int e){
    FlListDisplay::Query E = (FlListDisplay::Query)e;
    UIname pname;
    switch(E){
        case FlListDisplay::Query::REFRESH:
            o->raiseEvent(CmdUpdateProductsList,o);
        break;
        case FlListDisplay::Query::CREATE:
            pname = o->id();
            o->raiseEvent(CmdNavigateTo,&pname);
        break;
        case FlListDisplay::Query::SEARCH:
            o->raiseEvent(CmdUpdateProductsList,o);
        break;
    }
};




/*Lesson on why you should throw errors instead of ignoring action */