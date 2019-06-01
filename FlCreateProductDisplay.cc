#include <FlCreateProductDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>

static const UIname PAGENAME(NAME_CREATE_PRODUCT_SCREEN); 

FlCreateProductDisplay::FlCreateProductDisplay(int x, int y, int w, int h)
    :Fl_Group(x, y, w, h){

    begin();
    box(WINNY_NO_BORDERBOX);
     color(WINDOW_COLOR());
    prodName = new Fl_Input(DCX(5),DCY(63),358,25,"Name");
    set_winny_input_theme(prodName);//prodName->color(FL_WHITE);
    prodName->align(FL_ALIGN_TOP_LEFT);

    prodDesc = new Fl_Input(DCX(5),DCY(113),358,25,"Description");
    prodDesc->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(prodDesc);//prodDesc->color(FL_WHITE);

    total = new Fl_Input(DCX(294),DCY(339),101,20,"Total");
    set_winny_input_theme(total);//->color(FL_WHITE);

    costPrice = new Fl_Input(DCX(369),DCY(63),131,20,"cost Price");
    costPrice->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(costPrice);//->color(FL_WHITE);

    sellingPrice = new Fl_Input(DCX(503),DCY(63),131,20, "Selling Price"); 
    sellingPrice->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(sellingPrice);//->color(FL_WHITE);

    isCompound = new Fl_Check_Button(DCX(370),DCY(113),178,20,"this is a compound product");
    set_winny_button_theme(isCompound);
    isCompound->box(WINNY_NO_BORDERBOX);

    btnAdd = new Fl_Button(DCX(8),DCY(195),45,16, "add");
    set_winny_button_theme(btnAdd);
    btnclear = new Fl_Button(DCX(71),DCY(195),45,16,"clear");
    set_winny_button_theme(btnclear);
    btnClearAll = new Fl_Button(DCX(119),DCY(195),60,16,"clear all");
    set_winny_button_theme(btnClearAll);
    btnSave = new Fl_Button(DCX(5),DCY(5),48,20,"save");
    set_winny_button_theme(btnSave);
    btnSave->color(WINNY_BACKGROUND_ACCCOLOR);
    btnSave->labelcolor(FL_WHITE);
    btnSave->box(WINNY_THICK_BORDERBOX);

    btnCancel = new Fl_Button(DCX(707),DCY(5),48,20,"clear");
    set_winny_button_theme(btnCancel);

    holrule1 = new Fl_Box(DCX(0),DCY(158),w,1,"Components");
    holrule1->align(FL_ALIGN_BOTTOM_LEFT);
    holrule1->labelsize(WINNY_SUBTITLETEXT_FONTSIZE);
    holrule1->labelfont(WINNY_BOLDFONT);
    holrule1->box(WINNY_TOP_BORDERBOX);

    components  = new dataset_view(DCX(5),DCY(217),390,121);  
    components->box(WINNY_TOP_BORDERBOX);     
    holrule2 = new Fl_Box(DCX(0),DCY(773),w,1);
    holrule2->box(WINNY_THICK_BORDERBOX); 
    resizer = new Fl_Box(DCX(647),DCY(397),39,1);
    resizable(resizer);
    end();
};

void FlCreateProductDisplay::show(){
    Fl_Group::show();
};
void FlCreateProductDisplay::hide(){
    Fl_Group::hide();
};
void FlCreateProductDisplay::update(){
    Fl_Group::redraw();
};  

UIname FlCreateProductDisplay::id(){
    return PAGENAME;
};