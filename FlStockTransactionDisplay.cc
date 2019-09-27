#include <FlStockTransactionDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>
#include <WinnyUserPrompts.H>
#include <gmtime.h>
#include <IScreen.h>
#include <FL/fl_ask.H>
#include <FL/names.h>
#include <convert.h>

using utils::Time;

/*Implements uiLib callback inteface this is an adapter, 
to adopt our uiLibHandler
to the fltkCallback interface*/
static void fltkCallback(Fl_Widget* w, void* o){
    //if(Fl::event()==FL_DRAG)return;//only interested in clicks and keyboard
    ((FlStockTransactionDisplay*)o)->handleUiLib(w);
};


FlStockTransactionDisplay::FlStockTransactionDisplay():
Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H),
listItems(0,4),record(nullptr)
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

    title = new Fl_Box(DCX(26),DCY(41),422,1);
    title->label(doctype.c_str());
    title->box(WINNY_TOP_BORDERBOX);
    title->labelfont(WINNY_BOLDFONT);
    title->labelcolor(WINNY_SUBTITLETEXT_COLOR);
    title->labelsize(WINNY_TITLETEXT_FONTSIZE);
    title->align(FL_ALIGN_TOP_LEFT);

    client = new Fl_Output(DCX(26),DCY(72),252,SLWH,"Client");
    set_winny_input_theme(client);
    client->callback(fltkCallback, this);

    doctype = "SALES INVOICE";
    transactionId = new Fl_Input(DCX(343),DCY(72),106,SLWH);
    transactionId->label(doctype.c_str());
    transactionId->deactivate();//id is auto generated
    set_winny_input_theme(transactionId);

    transactionDate = new Fl_Output(DCX(343),DCY(103),106,SLWH);
    set_winny_input_theme(transactionDate);
    transactionDate->callback(fltkCallback, this);
    transactionDate->when(FL_WHEN_NOT_CHANGED|FL_WHEN_ENTER_KEY_ALWAYS);

    holrule2 = new Fl_Box(DCX(26),DCY(161),422,1,"Particulars");
    holrule2->box(WINNY_TOP_BORDERBOX);
    holrule2->labelfont(WINNY_BOLDFONT);
    holrule2->align(FL_ALIGN_TOP_LEFT);

    addItemFrame = new Fl_Box(DCX(26),DCY(190),422,59,"Add New");
    addItemFrame->box(WINNY_THIN_BORDERBOX);
    addItemFrame->align(FL_ALIGN_TOP_LEFT);
    addItemFrame->labelfont(WINNY_BOLDFONT);

    productName = new Fl_Output(DCX(41),DCY(215),111,SLWH,"Product");
    set_winny_input_theme(productName);
    productName->callback(fltkCallback, this);

    itemQty = new Fl_Int_Input(DCX(155),DCY(215),40,SLWH,"Qty");
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
    btnAdd->callback(fltkCallback, this);

    btnEdit = new Fl_Button(DCX(27),DCY(259),45,16,"Edit");
    set_winny_button_theme(btnEdit);
    btnEdit->callback(fltkCallback, this);
    btnEdit->deactivate();

    btnclear = new Fl_Button(DCX(71),DCY(259),45,16,"Clear");
    set_winny_button_theme(btnclear);
    btnclear->callback(fltkCallback, this);
    btnclear->deactivate();

    btnClearAll = new Fl_Button(DCX(116),DCY(259),56,16,"Clear All");
    set_winny_button_theme(btnClearAll);
    btnClearAll->callback(fltkCallback, this);
    btnClearAll->when(FL_WHEN_RELEASE_ALWAYS);
    btnClearAll->deactivate();
    btnClearAll->shortcut(FL_ALT+'d');

    items = new dataset_view(DCX(26),DCY(280),420,210);
    items->box(WINNY_TOP_BORDERFRAME);
    //items->table_box(WINNY_TOP_BORDERBOX);
    items->col_auto_resize();
    items->col_header(1);

    amountPaid = new Fl_Input(DCX(26),DCY(512),106,SLWH,"Paid");
    set_winny_input_theme(amountPaid);
    //amountPaid->deactivate();

    transactionAmount = new Fl_Input(DCX(343),DCY(512),106,SLWH,"Amount");
    set_winny_input_theme(transactionAmount);
    transactionAmount->deactivate();

    thePage->end();
    
    begin();
    holrule1 = new Fl_Box(DCX(1),DCY(0),CONTENT_AREA2.W, 1);
    holrule1->box(WINNY_TOP_BORDERBOX);

    btnSave = new Fl_Button(DMX(5),DMY(MBH),48,20,"save");
    set_winny_button_theme(btnSave);
    btnSave->color(WINNY_BACKGROUND_ACCCOLOR);
    btnSave->labelcolor(FL_WHITE);
    btnSave->box(WINNY_THICK_BORDERBOX);
    btnSave->callback(fltkCallback, this);

    btnCancel = new Fl_Button(DMX(53),DMY(MBH),48,20,"clear");
    set_winny_button_theme(btnCancel);
    btnCancel->callback(fltkCallback, this);

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


void FlStockTransactionDisplay::show(){
    Fl_Group::show();
}

void FlStockTransactionDisplay::update(){
    return;
}


void FlStockTransactionDisplay::hide(){
    Fl_Group::hide();
}



void FlStockTransactionDisplay::writeBuff(MemAddress buff){
    //clear
    transactionId->value(nullptr);
    client->value(nullptr);
    listItems.set_rows(0); //reset
    amountPaid->value(nullptr);
    transactionAmount->value(nullptr);

    if(record) delete record;
    record = (Winny::load_list*)buff;

    transactionDate->value(record->transactionDate().sdate().c_str()); //copy date
    doctype =record->docType(); //copy doctype
    FlStockTransactionDisplay::id(doctype);
    title->label(doctype.c_str());
    transactionId->label(doctype.c_str());
    transactionId->value(Convert::doubleToCstr(record->number())); //copy id
    IScreen::screen()->log("doctype is ..."+ doctype);

    double amt=0.0;
    auto itm = record->lineItems().begin();
    while (itm != record->lineItems().end()){
        int lr = listItems.rows(); //get last row
        listItems.set_rows(lr+1); //add extra space
        listItems.data(lr,0,itm->item().c_str());
        listItems.data(lr,1,itm->qty());
        listItems.data(lr,2,itm->rate());
        listItems.data(lr,3,itm->amount());
        amt+=itm->amount();
    }
    transactionAmount->value(Convert::doubleToCstr(record->value()));
    //amountPaid->value(record->value());
    
};

void FlStockTransactionDisplay::handleUiLib(Fl_Widget* w){
    variable s;
    if (w==transactionDate){
        utils::Time t;
        PromptUser::getDate(&t);
        transactionDate->value(t.sdate().c_str());
        record->transactionDate(t);
    }
   
   if (w==client){
       //w->deactivate();//workaround a bug where sometimes dialog events are sent back here
       //fl_alert(fl_eventnames[Fl::event()]);
       PromptUser::getClientId(&s);
       if (s.type()==data_kind::CSTRING){
            client->value(s.cstring());

            record->clientId(s.cstring());
       }
      // w->activate();
       return;
   }

   if (w==productName){
     //  w->deactivate();
       PromptUser::getProductId(&s);
        if (s.type()==data_kind::CSTRING){
            record->clientId(s.cstring());
            productName->value(s.cstring());
            //itemQty->value("0");
            itemQty->take_focus();
            btnAdd->activate();
       }
     //  w->activate();
   }

   if(w==btnAdd){
       //Add Item  to the list
       if(std::strlen( productName->value())){
            int lastrow = listItems.rows(); //get current row count 
            listItems.set_rows(lastrow +1); //increment it
           //fl_alert("btnAdd called");
            listItems.data(lastrow,0,productName->value()); //copy from input to form
            listItems.data(lastrow,1,itemQty->value());
            listItems.data(lastrow,2,itemRate->value());
            //----etc

            //clear form
            productName->value("");//
            itemQty->value("");
            itemRate->value("");
            itemQty->value("");

            btnClearAll->activate();
            btnclear->activate();
            btnEdit->activate();

            //if(btnClearAll->active_r())fl_alert("fuck");

       }
   }

    if ( w==btnClearAll){
        listItems.set_rows(0);

        btnclear->deactivate();
        btnClearAll->deactivate();
        btnEdit->deactivate();
    }

}