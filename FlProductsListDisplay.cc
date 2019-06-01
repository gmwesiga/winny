#include <FlProductsListDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>
#include <IApplicationTypes.H> // createNew product screen name

//Fl CallBacks
static void cbGoToCreateProducts ( Fl_Widget* w, void* o);
static void cbFilterProductsList ( Fl_Widget* w, void* o);
static void cbDeactivateProduct ( Fl_Widget* w, void* o);
static void cbEditProductDetails(Fl_Widget* w, void* o);
static void cbSearchProducts(Fl_Widget* w, void* o);

static const UIname PAGENAME(NAME_SEARCH_PRODUCT_SCREEN); 

//return name of this function page
UIname FlProductsListDisplay::id(){return PAGENAME;};

    FlProductsListDisplay::FlProductsListDisplay()
        :Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H-MENUBAR_AREA.H){
            begin();
            box(WINNY_NO_BORDERBOX);
            color(WINDOW_COLOR());
            menuBar = new Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y,MENUBAR_AREA.W,MENUBAR_AREA.H);
            /*Parent responsible for drawing title*/
            
            btnNew = new Fl_Button(
                DX(266),DY(106),48,15,"new");
            set_winny_button_theme(btnNew);
            btnNew->color(ACCCOLOR);
            btnNew->labelcolor(FL_WHITE);
            btnNew->box(WINNY_THICK_BORDERBOX);
            btnNew->callback(cbGoToCreateProducts,(void*)this);
            //btnNew->when(btnNew->when()&FL_WHEN_CHANGED);

            filter = new Fl_Menu_Button(
                DX(326),DY(106),80,15,"Filter by");
            set_winny_button_theme(filter);
            filter->callback(cbFilterProductsList,(void*)this);

            btnActivateToggle = new Fl_Button(
                DX(412),DY(106),66,16,"Activate");
            set_winny_button_theme(btnActivateToggle);
            btnActivateToggle->callback(cbDeactivateProduct,(void*)this);

            btnEdit = new Fl_Button(
                DX(484),DY(106),65,16,"Edit");
            set_winny_button_theme(btnEdit);
            btnEdit->callback(cbEditProductDetails,(void*)this);

            searchToken = new Fl_Input(
                DX(811),DY(101),196,22,"Search Products");
            set_winny_input_theme(searchToken);
            //searchToken->color(FL_WHITE);
            //searchToken->alig;
            searchToken->callback(cbSearchProducts,(void*)this);
            searchToken->when(FL_WHEN_ENTER_KEY_CHANGED);

            menuBarResizer = new Fl_Box(DX(649),DY(100),10,0);
            menuBarResizer->box(WINNY_NO_BORDERBOX);
            menuBar->resizable(menuBarResizer);

            menuBar->end();
            //menuBar->box(WINNY_TOP_BORDERBOX);
            prdList = new dataset_view(CONTENT_AREA2.X,CONTENT_AREA2.Y,CONTENT_AREA2.W,
            CONTENT_AREA2.H);
            prdList->box(WINNY_BOTTOM_BORDERBOX);
            //prdList->table_box(WINNY_BOTTOM_BORDERBOX);
            //prdList->box(WINNY_TOP_BORDERBOX);
            resizable((Fl_Widget*)prdList);
            end();
        return;
    };

    void FlProductsListDisplay::show(){
        Fl_Group::show();
        update();
        return;
    };
    void FlProductsListDisplay::hide(){
        Fl_Group::hide();
        return;
    };

    void FlProductsListDisplay::update(){
        Fl_Group::redraw();
    }

    void FlProductsListDisplay::AddSortOption(string opt){
        filter->add(opt.c_str());
        return;
    };
    void FlProductsListDisplay::clearSortOptions(){
        filter->clear();
        return;
    };
    string FlProductsListDisplay::sortOption(){

       // return filter->mvalue()->;
    };
    string FlProductsListDisplay::searchKey(){
        return "";
    };
    void FlProductsListDisplay::addToshowList(Product){
        return;
    }; 
    void FlProductsListDisplay::clearShowList(){
        return;
    };
    string FlProductsListDisplay::selected(){
        return "";
    };

//is Called Whenever user clicks Create Product Link
static Winny::UserIODevName pgname = Winny::UserIODevName::UIOQ_CREATE_PRODUCT;

static void cbGoToCreateProducts ( Fl_Widget* w, void* o){
    FlProductsListDisplay *me = (FlProductsListDisplay*)o;
    me->raiseEvent(CmdNavigateTo,(void*)&pgname);
};    

//Called Whenever user Clicks Filter Button on UI
static void cbFilterProductsList ( Fl_Widget* w, void* o){
    FlProductsListDisplay *me = (FlProductsListDisplay*)o;
    me->raiseEvent(CmdFilterProductsList);
//To do: update decide second optional variable of CmdFilterProductsList
};

//Called Whenever user clicks deactivate on a product
static void cbDeactivateProduct ( Fl_Widget* w, void* o){
    FlProductsListDisplay *me = (FlProductsListDisplay*)o;
    me->raiseEvent(CmdDeactivateProduct);
};

//Called Whenever user clicks Edit on a product
static void cbEditProductDetails(Fl_Widget* w, void* o){
    FlProductsListDisplay *me = (FlProductsListDisplay*)o;
    //return;
    me->raiseEvent(CmdEditProductDetails); 
};

static void cbSearchProducts(Fl_Widget* w, void* o){
    FlProductsListDisplay *me = (FlProductsListDisplay*)o;
    me->raiseEvent(CmdsearchProduct); 
};