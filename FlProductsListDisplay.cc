#include <FlProductsListDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>

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
        :Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H){
            begin();
            menuBar = new Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y,MENUBAR_AREA.W,MENUBAR_AREA.H,
            PAGENAME.c_str());
            menuBar->align(FL_ALIGN_TOP_LEFT);
            menuBar->labelcolor(ACCFONTCOLOR);
            menuBar->labelsize(14);

            btnNew = new Fl_Button(233,95,57,19,"New");
            btnNew->color(ACCCOLOR);
            btnNew->labelcolor(FL_WHITE);
            btnNew->box(WINNY_THICK_BORDERBOX);
            btnNew->callback(cbGoToCreateProducts,(void*)this);
            //btnNew->when(btnNew->when()&FL_WHEN_CHANGED);

            filter = new Fl_Menu_Button(341,95,147,19,"Filter by");
            set_winny_button_theme(filter);
            filter->callback(cbFilterProductsList,(void*)this);

            btnActivateToggle = new Fl_Button(494,96,68,19,"Activate");
            set_winny_button_theme(btnActivateToggle);
            btnActivateToggle->callback(cbDeactivateProduct,(void*)this);

            btnEdit = new Fl_Button(567,96,68,19,"Edit");
            set_winny_button_theme(btnEdit);
            btnEdit->callback(cbEditProductDetails,(void*)this);

            searchToken = new Fl_Input(805,96,206,19,"Search Products");
            searchToken->color(FL_WHITE);
            searchToken->box(WINNY_THIN_BORDERBOX);
            searchToken->callback(cbSearchProducts,(void*)this);
            searchToken->when(FL_WHEN_ENTER_KEY_CHANGED);

            menuBarResizer = new Fl_Box(649,100,10,2);
            menuBarResizer->box(WINNY_NO_BORDERBOX);
            menuBar->resizable(menuBarResizer);

            menuBar->end();
            menuBar->box(WINNY_TOP_BORDERBOX);
            prdList = new dataset_view(233,123,776,
            (int)(((double)384/DESIGNSH)*SCRN_HEIGHT));
            prdList->box(WINNY_BOTTOM_BORDERBOX);
            prdList->table_box(WINNY_BOTTOM_BORDERBOX);
            prdList->box(WINNY_TOP_BORDERBOX);
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
static void cbGoToCreateProducts ( Fl_Widget* w, void* o){
    FlProductsListDisplay *me = (FlProductsListDisplay*)o;
    me->raiseEvent(CmdNavigateTo,(void*)NAME_CREATE_PRODUCT_SCREEN);
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