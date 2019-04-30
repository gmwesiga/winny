#ifndef WUI_H
#define WUI_H

#include <string>
#include "account.h"
#include "transaction.h"

#define account Account //syntactic convinience

using std::string;
using namespace winny;

typedef winny::account_type accountType;

/*This file contains interface declarations used by the main application
/for its ui*/
namespace winny_ui{
    /*events that the application expects from the UI*/
    enum uiEvents{
        onUICreated,
        BeforeMainUILoad,
        onNewLogInRequest,
        onAccountListFilterChanged,
        onAccountCreationRequest,
        onAccountToDisplayChanged,
        onTransactionCreationRequest,
        onProductListFilterChanged,
        onProductCreationRequest,
        onProductToDisplayChanged,
        OnTimeOut //user has taken alot of time without using app
    };

    /*the account list is filtered based on */

    enum accFilterGrouping{
        ASSETS,
        INCOMES,
        PAYABLES,
        RECIEVABLES,
        EXPENSES,
        ALL
    }; //Note, account_type is a subset of this,

    const vector<string> ACC_FILTER_GROUPING={
        "Assets","Incomes","Payables","Receivables","Expenses","All"
    };

    struct accountListFilter{
        string accountNamePattern;  //pattern of name with standard metacharacters *.%
        accFilterGrouping grouping;       //ASSET,PAYABLES,RECIEVABLES, INCOMES etc     
    };

    struct accListLineItem{
        string accountNumber;
        string accountName;
        double balance;
        string sbalance;//balance as string      
    };
    typedef vector<accListLineItem> accListLineItemVector;

    struct tListLineItem{   //t ==transaction
        string transactionNumber;
        string type; //route sale, invoice etc
        double value;
        string sbalue; //value as string;
    };
    typedef vector<tListLineItem> tListLineItemVector;

    class ui;
    class uiImp;
    typedef int (*eventHandle)(void*, ui*, uiEvents);
    typedef int (*impEventHandle)(ui*,uiImp*, uiEvents);

    class ui{
        public:
        ui(uiImp*);

        //setters
        void accListFilter(accountListFilter&);
        void accList(accListLineItemVector&);//write only
        void accToDisplay(Account&);
        void statusBarMessage(string&);
        void transactionList(tListLineItemVector&);//write only

        //getters
        void userLogInCredentials(string& userName, string& password);
        accountListFilter&  accListFilter();
        Account&            accToCreate();
        transaction*        transactionToCreate();
        void minutesBeforeTimeOut(int);
        int minutesBeforeTimeOut();
        void eventHandler(eventHandle, void*data);
        void run();
        void freeze();
        virtual ~ui();
        
        protected:
        uiImp* uiImp_;
        eventHandle handle_;
        void* eventHandleData_;
        uiEvents lastEvent_;
        int publishEvent(uiEvents event);

        private:
        static int uiImp_Handler(ui*, uiImp*, uiEvents);  
    };


    class uiImp{
        public:
        virtual void accListFilter(accountListFilter&)=0;
        virtual void accList(accListLineItemVector&)=0;//write only
        virtual void accToDisplay(Account&)=0;
        virtual void statusBarMessage(string&)=0;
        virtual void userLogInCredentials(string& userName, string& password)=0;
        virtual accountListFilter& accListFilter()=0;
        virtual Account& accToCreate()=0;
        virtual transaction* transactionToCreate()=0;
        virtual void transactionList(tListLineItemVector&)=0;
        virtual void minutesBeforeTimeOut(int)=0;
        virtual int minutesBeforeTimeOut()=0;
        virtual void eventHandler(impEventHandle,void*data)=0;
        virtual void run()=0;
        virtual void freeze()=0;
        virtual ~uiImp(){};
    };

}

#endif