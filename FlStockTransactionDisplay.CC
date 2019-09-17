#include <FlStockTransactionDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>
#include <WinnyUserPrompts.H>
#include <gmtime.h>

using utils::Time;

static void getDatecb(Fl_Widget*o, void* d){
    Time t;
    PromptUser::getDate(&t);
    ((Fl_Input_*)o)->value(t.to_string().c_str());
};

FlStockTransactionDisplay::FlStockTransactionDisplay():
Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H),
listItems(0,4)
{
    begin();
    thePage = new Fl_Scroll(DCX(0),DCY(0),CONTENT_AREA.W,CONTENT_AREA2.H);
    set_winny_scroll_theme(thePage);
    thePage->begin();
    thePage->box(WINNY_NO_BORDERBOX);
    thePage->color(WINDOW_COLOR());
    int comMenuY,comMenuWa, comMenuWb,comMenuH;
    comMenuY = 32;
    comMenuWa = 88;
    comMenuWb = 56;
    comMenuH = SLWH;

    bgbox = new Fl_Box(DCX(5),DCY(0),467,572);
    bgbox->box(WINNY_THIN_BORDERBOX);
    bgbox->color(fl_rgb_color(240,240,240));

    title = new Fl_Box(DCX(26),DCY(41),422,1,doctype.c_str());
    title->box(WINNY_TOP_BORDERBOX);
    title->labelfont(WINNY_BOLDFONT);
    title->labelcolor(WINNY_SUBTITLETEXT_COLOR);
    title->labelsize(WINNY_TITLETEXT_FONTSIZE);
    title->align(FL_ALIGN_TOP_LEFT);

    client = new Fl_Input(DCX(26),DCY(72),252,SLWH,"Client");
    set_winny_input_theme(client);

    doctype = "SALES INVOICE";
    transactionId = new Fl_Input(DCX(343),DCY(72),106,SLWH,doctype.c_str());
    transactionId->deactivate();//id is auto generated
    set_winny_input_theme(transactionId);

    transactionDate = new Fl_Input(DCX(343),DCY(103),106,SLWH);
    set_winny_input_theme(transactionDate);

    holrule2 = new Fl_Box(DCX(26),DCY(161),422,1,"Particulars");
    holrule2->box(WINNY_TOP_BORDERBOX);
    holrule2->align(FL_ALIGN_TOP_LEFT);

    addItemFrame = new Fl_Box(DCX(26),DCY(190),422,59,"Add New");
    addItemFrame->box(WINNY_THIN_BORDERFRAME);
    addItemFrame->align(FL_ALIGN_TOP_LEFT);

    productName = new Fl_Input(DCX(41),DCY(215),111,SLWH,"Product");
    set_winny_input_theme(productName);

    itemQty = new Fl_Input(DCX(155),DCY(215),40,SLWH,"Qty");
    set_winny_input_theme(itemQty);

    itemRate = new Fl_Input(DCX(198),DCY(215),78,SLWH,"Rate");
    itemRate->deactivate();
    set_winny_input_theme(itemRate);

    itemValue = new Fl_Input(DCX(281),DCY(215),109,SLWH,"Amount");
    itemValue->deactivate();
    set_winny_input_theme(itemValue);

    btnAdd = new Fl_Button(DCX(396),DCY(215),34,23,"Add");
    set_winny_button_theme(btnAdd);
    btnAdd->deactivate();

    btnEdit = new Fl_Button(DCX(27),DCY(259),45,16,"Edit");
    set_winny_button_theme(btnEdit);

    btnclear = new Fl_Button(DCX(71),DCY(259),45,16,"Clear");
    set_winny_button_theme(btnclear);

    btnClearAll = new Fl_Button(DCX(116),DCY(259),56,16,"Clear All");
    set_winny_button_theme(btnClearAll);

    items = new dataset_view(DCX(26),DCY(280),420,210);
    items->box(WINNY_TOP_BORDERBOX);

    amountPaid = new Fl_Input(DCX(26),DCY(512),106,SLWH,"Paid");
    set_winny_input_theme(amountPaid);
    amountPaid->deactivate();

    transactionAmount = new Fl_Input(DCX(343),DCY(512),106,SLWH,"Amount");
    set_winny_input_theme(transactionAmount);

    thePage->end();
    
    begin();
    holrule1 = new Fl_Box(DCX(1),DCY(0),CONTENT_AREA2.W, 1);
    holrule1->box(WINNY_TOP_BORDERBOX);

    btnSave = new Fl_Button(DMX(5),DMY(MBH),48,20,"save");
    set_winny_button_theme(btnSave);
    btnSave->color(WINNY_BACKGROUND_ACCCOLOR);
    btnSave->labelcolor(FL_WHITE);
    btnSave->box(WINNY_THICK_BORDERBOX);

    btnCancel = new Fl_Button(DMX(53),DMY(MBH),48,20,"clear");
    set_winny_button_theme(btnCancel);


   // spacer = new Fl_Box(DCX(1),DCY(1),1,1);

    resizer = new Fl_Box(CONTENT_AREA2.W - 10,319,1,1);
    resizable(resizer);
    
    set_winny_window_theme(this);

    end();

    listItems.set_col_header(0,"Product");
    listItems.set_col_header(1,"Qty");
    listItems.set_col_header(2,"Rate");
    listItems.set_col_header(3,"Amount");

    items->attach_dataset(&listItems);

}



UIname FlStockTransactionDisplay::id(){
    return "Transactions/ Enter an Invoice";
}


void FlStockTransactionDisplay::show(){
    Fl_Group::show();
}

void FlStockTransactionDisplay::update(){
    return;
}


void FlStockTransactionDisplay::hide(){
    Fl_Group::hide();
}
