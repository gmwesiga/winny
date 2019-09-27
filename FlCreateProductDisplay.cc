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

    bgbox = new Fl_Box(DCX(5),DCY(0),465,416);
    bgbox->box(WINNY_THIN_BORDERBOX);
    bgbox->color(fl_rgb_color(240,240,240));

    prodName = new Fl_Input(DCX(38),DCY(40),388,SLWH,"Name");
    set_winny_input_theme(prodName);//prodName->color(FL_WHITE);
    prodName->align(FL_ALIGN_TOP_LEFT);

    prodDesc = new Fl_Input(DCX(38),DCY(91),388,SLWH,"Description");
    prodDesc->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(prodDesc);//prodDesc->color(FL_WHITE);

    total = new Fl_Input(DCX(272),DCY(198),153,17,"Total");
    set_winny_input_theme(total);//->color(FL_WHITE);
    total->align(FL_ALIGN_LEFT);

    costPrice = new Fl_Input(DCX(39),DCY(368),162,SLWH,"cost Price");
    costPrice->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(costPrice);//->color(FL_WHITE);

    sellingPrice = new Fl_Input(DCX(268),DCY(368),159,SLWH, "Selling Price"); 
    sellingPrice->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(sellingPrice);//->color(FL_WHITE);

    isCompound = new Fl_Check_Button(DCX(39),DCY(143),151,SLWH,"this is a compound product");
    set_winny_button_theme(isCompound);
    isCompound->box(WINNY_NO_BORDERBOX);

    btnAdd = new Fl_Button(DCX(38),DCY(201),45,16, "add");
    set_winny_button_theme(btnAdd);
    btnclear = new Fl_Button(DCX(81),DCY(201),45,16,"clear");
    set_winny_button_theme(btnclear);
    btnClearAll = new Fl_Button(DCX(126),DCY(201),60,16,"clear all");
    set_winny_button_theme(btnClearAll);
    btnSave = new Fl_Button(DMX(5),DMY(MBH),48,20,"save");
    set_winny_button_theme(btnSave);
    btnSave->color(WINNY_BACKGROUND_ACCCOLOR);
    btnSave->labelcolor(FL_WHITE);
    btnSave->box(WINNY_THICK_BORDERBOX);

    btnCancel = new Fl_Button(DMX(53),DMY(MBH),48,20,"clear");
    set_winny_button_theme(btnCancel);

    holrule1 = new Fl_Box(DCX(34),DCY(186),390,1,"Components");
    holrule1->align(FL_ALIGN_TOP_LEFT);
    holrule1->labelsize(WINNY_SUBTITLETEXT_FONTSIZE);
    holrule1->labelfont(WINNY_BOLDFONT);
    holrule1->box(WINNY_TOP_BORDERBOX);

    components  = new dataset_view(DCX(38),DCY(220),390,121);  
    components->box(WINNY_TOP_BORDERBOX);     
   
    holrule2 = new Fl_Box(DCX(38),DCY(127),390,1);
    holrule2->box(WINNY_TOP_BORDERBOX); 

    holrule3 = new Fl_Box(DCX(0),DCY(0),w,1);
    holrule3->box(WINNY_TOP_BORDERBOX); 

    resizer = new Fl_Box(DCX(488),DCY(419),14,1);
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