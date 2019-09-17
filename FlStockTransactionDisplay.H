#ifndef STOCKTRANSACTIONDISPLAY_H
#define STOCKTRANSACTIONDISPLAY_H

//#include <IExtEventSource.h>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>
#include <IUserInterface.h>

class FlStockTransactionDisplay : public Fl_Group, public IUserInterface{
    public:
    enum Event {
        CREATE,EDIT
    };

    struct Handler {
        UIname id()=0;
        void handler(Event e)=0;
    };

    FlStockTransactionDisplay();//pass window;
    void show();
    void hide();
    void update();   
    UIname id();
    void readBuff(MemAddress buff){buff= nullptr;};
    void writeBuff(MemAddress buff){buff=nullptr;/*should be implemented */};
    void attachHandler(FlStockTransactionDisplay::Handler *h);

    private:

    Handler* hnd;
    Fl_Input *client, 
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