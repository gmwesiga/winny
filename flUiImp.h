//winny interface 
//this file defines the main window and all 
//its dialogs. it defines the UI of the application
//g++ -oWINNY winny.cxx  winny_ui.cxx records_lib.cxx -I/usr/local/include/ -L/usr/local/lib/ -lfltk -lole32 -luuid -lcomctl32 -lgdi32 -std=gnu++11 -static-libgcc -static-libstdc++
//12:11pm 19/january/2016
//Author: © Gilbert Mwesiga. gilbert dot mwesiga at gmail dot com

#pragma once
#ifndef id8976154A_2450_42FA_B209B025FE9E2148
#define id8976154A_2450_42FA_B209B025FE9E2148

#include "wui.h"
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include "dataset_view.h"
#include "loadlist_input.h"
#include "product_view.h"
#include "winny_theme.h"
#include <FL/fl_draw.H>

using namespace winny_ui;
//handle sizing, resizing and positioning
class flUiWindow{
    public:
    //top level windows
    flUiWindow(int w=-1,int h=-1);
    ~flUiWindow();
    Fl_Double_Window*  mainWindow;
    Fl_Double_Window*  logInWindow;
    
    //Top level parts of mainWindow
    Fl_Group*          topMenueBar;
    Fl_Group*          mainPanel;
    Fl_Group*          statusBarPanel;

    // topMenueBar
    Fl_Toggle_Button* homeButton;

    //mainPanel components
    Fl_Group*          lvPanel;
    Fl_Group*          storeBookPanel;
    Fl_Group*          homePanel;

    //lvPanel
    Fl_Group*          lvSidePanel;
    Fl_Input*          lvSearchTextBox;
    Fl_Choice*         lvListSortingOptions;
    Fl_Menu_Button*    lvCreateAccountMenue;
    dataset_view*      lvAccountsList;

    Fl_Group*          lvAccountPanel;
    Fl_Output*         lvAccountNameLabel;
    Fl_Menu_Button*    lvAccountOperationsMenue;
    dataset_view*      lvAccountEntries;

    //homePanel
    dataset_view*      hmTransactionsList;
    dataset_view*      hmStockLevelsList;
    dataset_view*      hmReceivablesList;
    dataset_view*      hmPayablesList;
    Fl_Menu_Button*    hmCreateTransactionMenue;

    //accountProperties:
        Fl_Input*       accountName;
        Fl_Int_Input*   accountObalance;
        dataset_view*   accountProperties;
        Fl_Button*      newAccountDialogOk;
        Fl_Button*      newAccountDialogCancel;

    private:
    Fl_Box*            topMenueBarResizeBox;
    Fl_Box*            hmPanelLeftResizeBox;
    Fl_Box*            hmPanelRightResizeBox;
    //the following controls are used as scaffolding
    //for the homePanel
    Fl_Group*          lvAccPropertiesGroup;
    Fl_Group*          hmTransPanelGroup;
    Fl_Group*          hmStockLevelsGroup;
    Fl_Group*          hmReceivablesGroup;
    Fl_Group*          hmPayablesGroup;   
    Fl_Group*          hmContainer; //contains all groups, and hmPanelRightResizeBox
};


//handle mangling
class flUiImp:public uiImp{
    public:
    flUiImp( );
    void accListFilter(accountListFilter&);
    void accList(accListLineItemVector&);//write only
    void accToDisplay(Account&);
    void statusBarMessage(string&);
    void userLogInCredentials(string& userName, string& password);
    accountListFilter& accListFilter();
    Account& accToCreate();
    transaction* transactionToCreate();
    void transactionList(tListLineItemVector&);
    void minutesBeforeTimeOut(int);
    int minutesBeforeTimeOut();
    void eventHandler(impEventHandle,void*data);
    void activateLedger();
    void run();
    void freeze();
    ~flUiImp(){delete flwindow;}

    //flUimp additions
    void createNewAccount(string _type);  
    
    private:
    //data for program interface
    accountListFilter       accListFltr_;
    accListLineItemVector   accList_;
    Account                 accToDisplay_;
    
    //implementation structures..
    dataset*                 accListView_;
    dataset*                 accEntriesView_;
    dataset*                 _accProperties;

    //styling
    styling                 accEntriesView_style;

    flObject*                 _accName;
    flObject*                 _accOpenBal;
    
    flUiWindow*              flwindow;
    void showHomePanel();
    void intLedgerPanel();
    void showLedgerPanel();
    void redraw();
    void writeLedgerPanel();
    void readLedgerPanel();//reads user Ledger window filter input into accListFltr_
    static void createNewAccount(Fl_Widget* w, void* v);
    int checkAccountSaveOk();
};

#endif // header
