#include <FlCreateProductDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>


FlCreateProductDisplay::FlCreateProductDisplay(Fl_Widget *w)
    :Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y, MENUBAR_AREA.W,MENUBAR_AREA.H+CONTENT_AREA2.H){

    box(WINNY_TOP_BORDERBOX);
    label("Create New Product");
    labelcolor(WINNY_MAINTITLETEXT_COLOR);
    align(FL_ALIGN_TOP_LEFT);
    labelsize(WINNY_TITLETEXT_FONTSIZE);
    labelfont(WINNY_BOLDFONT);
    begin();
    prodName = new Fl_Input(244,151,388,25,"Name");
    set_winny_input_theme(prodName);//prodName->color(FL_WHITE);
    prodName->align(FL_ALIGN_TOP_LEFT);

    prodDesc = new Fl_Input(244,201,388,25,"Description");
    prodDesc->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(prodDesc);//prodDesc->color(FL_WHITE);

    total = new Fl_Input(535,458,101,21,"Total");
    set_winny_input_theme(total);//->color(FL_WHITE);

    costPrice = new Fl_Input(246,504,164,25,"cost Price");
    costPrice->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(costPrice);//->color(FL_WHITE);

    sellingPrice = new Fl_Input(418,504,216,25, "Selling Price"); 
    sellingPrice->align(FL_ALIGN_TOP_LEFT);
    set_winny_input_theme(sellingPrice);//->color(FL_WHITE);

    isCompound = new Fl_Check_Button(244,243,178,37,"this is a compound product");
    set_winny_button_theme(isCompound);
    isCompound->box(WINNY_NO_BORDERBOX);

    btnAdd = new Fl_Button(247,308,45,16, "add");
    set_winny_button_theme(btnAdd);
    btnclear = new Fl_Button(310,308,45,16,"clear");
    set_winny_button_theme(btnclear);
    btnClearAll = new Fl_Button(358,308,60,16,"clear all");
    set_winny_button_theme(btnClearAll);
    btnSave = new Fl_Button(247,557,63,23,"save");
    set_winny_button_theme(btnSave);
    btnSave->color(WINNY_BACKGROUND_ACCCOLOR);
    btnSave->labelcolor(FL_WHITE);
    btnSave->box(WINNY_THICK_BORDERBOX);

    btnCancel = new Fl_Button(317,557,63,23,"clear");
    set_winny_button_theme(btnCancel);

    holrule1 = new Fl_Box(240,297,390,1,"Components");
    holrule1->align(FL_ALIGN_TOP_LEFT);
    holrule1->labelsize(WINNY_SUBTITLETEXT_FONTSIZE);
    holrule1->labelfont(WINNY_BOLDFONT);
    holrule1->box(WINNY_TOP_BORDERBOX);

    components  = new dataset_view(244,330,390,121);       
    holrule2 = new Fl_Box(237,539,773,1);
    holrule2->box(WINNY_THICK_BORDERBOX); 
    resizer = new Fl_Box(680,580,140,1);
    resizable(resizer);
    end();
}