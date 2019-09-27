#ifndef STOCKTRANSACTIONDISPLAY_H
#define STOCKTRANSACTIONDISPLAY_H

//#include <IExtEventSource.h>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>
#include <IUserInterface.h>
#include <transaction.H>

class FlStockTransactionDisplay : public Fl_Group, public IUserInterface{
    public:

    FlStockTransactionDisplay();//pass window;
    void show();
    void hide();
    void update();   
    void readBuff(MemAddress buff){buff= nullptr;};
    void writeBuff(MemAddress buff);
    
    /*Handles uiLib events from Widgets we used to implement this object
     *w is the widget in question*/
    void handleUiLib(Fl_Widget* w);

    private:

    Winny::load_list* record;

    Fl_Input_ *client, 
             *transactionId, 
             *transactionDate, 
             *productName, 
             *itemQty,
             *itemRate,
             *itemValue,
             *transactionAmount,
             *amountPaid;

    Fl_Button *btnAdd,*btnEdit, *btnclear;
    Fl_Button *btnClearAll, *btnSave, *btnCancel;
    dataset_view *items; //Particulars
    Fl_Box *holrule1, *holrule2, *addItemFrame, *bgbox;//like html <HR>
    Fl_Box *resizer, *spacer,*title;/*spacer is a hack to prevent scroll behavior of hidding top space*/
    string doctype;
    Fl_Scroll *thePage;

    dataset listItems;
};

#endif