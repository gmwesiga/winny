#include <FlProductsListDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>
#include <IApplicationTypes.H> // createNew product screen name
#include <FL/fl_ask.H>
//#include <stdio.h>
#include <stdlib.h>
using std::printf;

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
    :Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H-MENUBAR_AREA.H)
    ,output(nullptr)
    {
        begin();
        box(WINNY_NO_BORDERBOX);
        color(WINDOW_COLOR());
        menuBar = new Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y,MENUBAR_AREA.W,65);
        /*Parent responsible for drawing title*/
        int bh = 20;
        int y = 32;
        btnNew = new Fl_Button(
            DX(266),DCY(y),48,bh,"New(+)");
        set_winny_button_theme(btnNew);
        btnNew->color(ACCCOLOR);
        btnNew->labelcolor(FL_WHITE);
        btnNew->box(WINNY_THICK_BORDERBOX);
        btnNew->callback(cbGoToCreateProducts,(void*)this);
        //btnNew->when(btnNew->when()&FL_WHEN_CHANGED);

        filter = new Fl_Menu_Button(
            DX(731),DCY(y),80,bh,"Filter by");
        set_winny_button_theme(filter);
        filter->callback(cbFilterProductsList,(void*)this);

        btnActivateToggle = new Fl_Button(
            DX(314),DCY(y),66,bh,"Activate");
        set_winny_button_theme(btnActivateToggle);
        btnActivateToggle->callback(cbDeactivateProduct,(void*)this);

        btnEdit = new Fl_Button(
            DX(379),DCY(y),65,bh,"Edit");
        set_winny_button_theme(btnEdit);
        btnEdit->callback(cbEditProductDetails,(void*)this);

        searchToken = new Fl_Input(
            DX(811),DCY(y),196,bh,"Search Products");
        set_winny_input_theme(searchToken);
        //searchToken->color(FL_WHITE);
        //searchToken->alig;
        searchToken->callback(cbSearchProducts,(void*)this);
        searchToken->when(FL_WHEN_CHANGED);
        searchToken->align(FL_ALIGN_INSIDE);

        menuBarResizer = new Fl_Box(DX(649),DY(100),10,0);
        menuBarResizer->box(WINNY_NO_BORDERBOX);
        menuBar->resizable(menuBarResizer);

        menuBar->end();
        //menuBar->box(WINNY_TOP_BORDERBOX);
        prdList = new dataset_view(CONTENT_AREA2.X,DCY(65),CONTENT_AREA2.W,
        CONTENT_AREA2.H-30);
        prdList->box(WINNY_BOTTOM_BORDERBOX);
        //prdList->table_box(WINNY_BOTTOM_BORDERBOX);
        prdList->box(WINNY_TOP_BORDERBOX);
        prdList->row_header(1);
        prdList->col_auto_resize(1);
        resizable((Fl_Widget*)prdList);
        end();

        fltrParams.isComposite = false;
        fltrParams.searchKey = nullptr;
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
        raiseEvent(CmdUpdateProductsList,this);
        Fl_Group::redraw();
    }

/* dataset* convertToUIdataset(Winny::Dataset *dts){
    using Winny::ObjType;
    if(dts==nullptr)return nullptr;
    int rows = dts->size();
    int cols = rows? (*(dts->begin())).size():0;
    if(!rows || !cols) return nullptr; //no data nothing to do
    dataset* output = new dataset(rows,cols);

    table_data o; double* d; char* s; int r, c; 
    r = c =0; //internal datasetview is index accessed (zero based)
    for(auto rw = dts->begin(); rw!=dts->end(); rw++, r++){
        c=0; //reset c see note:
        output->set_row_header(r,table_data(r));
        for(auto cell = (*rw).begin(); cell!=(*rw).end(); ++cell, c++){
            
            switch((*cell).type){
                case ObjType::NUMBER:
                    d = (double*)(*cell).object;
                    o.number((*d)*rand());
                    break;
                case ObjType::STRING:
                    s = (char*)(*cell).object;
                    o.cstring(s);
                    break;
                default:
                    break;
            }
            o.style().borders=Borders::LEFT_RIGHT_BORDER;
            output->data(r,c,o);
        }
    }
    return output;
} */


void FlProductsListDisplay::writeBuff(MemAddress buff){
    //assumes buff is MemAddress of a struct ProductsListParams
    //when it returns, it has copied the output member of 
    //the struct into the display, application can free resources

    using Winny::ProductsListParams;
    ProductsListParams* bf = (ProductsListParams*)buff;
    dataset* output = new dataset(bf->outPut->rows(), bf->outPut->cols());
    for (int r = 0; r<output->rows(); r++){
        for(int c=0; c<output->cols(); c++){
            output->data(r,c,bf->outPut->data(r,c));
        }
    }
    if(!output)return;
    prdList->attach_dataset(output);
   
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
    me->raiseEvent(CmdUpdateProductsList);
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
    me->raiseEvent(CmdsearchProduct,me); 
};


/*Lesson on why you should throw errors instead of ignoring action */