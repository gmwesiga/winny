#include "transaction.h"
#include "convert.h"
//#include "records_lib.h"//to test routesale  and get difference()
using namespace winny;

//transaction
transaction::transaction()
    : handlerNum_(0),
      status_(open),
      trans_num_(0){};

//number(set)
transaction *transaction::number(long i)
{
    trans_num_ = i;
    return this;
}

//number()get
long transaction::number()
{
    return trans_num_;
}

//clientId(set)
transaction *transaction::clientId(string c_code)
{
    client_code_ = c_code;
    return this;
};

//clientId()
string transaction::clientId()
{
    return client_code_;
};

//clientName()
string transaction::clientName()
{
    return client_name_;
}

//clientName(set)
transaction *transaction::clientName(string c_name)
{
    client_name_ = c_name;
    return this;
};

//transactionDate(set)
transaction *transaction::transactionDate(utils::Time tdate) //note this takes a timestamp for now
{
    transaction_date_ = tdate;
    return this;
};

//transactionDate()get
utils::Time transaction::transactionDate()
{
    return transaction_date_;
};

//tStatus()get
status transaction::tStatus()
{
    return status_;
}

//close()void
void transaction::close()
{
    status_ = open;
};

//handlerNumber(set)
transaction *transaction::handlerNumber(long num)
{
    handlerNum_ = num;
    return this;
};

//handlerNumber()get
long transaction::handlerNumber()
{
    return handlerNum_;
};


//post
void transaction::post(entry_type entryType, string accountToPost,
        double amount, account_type typeOfThisAccount,
        string contraAccName){
    ledgerEntry _entry_;
    _entry_.accountName =accountToPost;
    _entry_.accountType = typeOfThisAccount;
    _entry_.Entry.date = transaction_date_;
    _entry_.Entry.transaction_id = number();
    _entry_.Entry.ac_name = contraAccName;
    _entry_.Entry.type = entryType;
    _entry_.Entry.amount = amount;
    ledgerEntries_.push_back(_entry_);
};

//spost
 void transaction::spost(stockMovementType smt, tLineItemVector& itms){
     stockBookEntry ste;
     ste.transactionId = number();
     ste.stockMvtType = smt;
     ste.items = itms;
     stockBookEntries_.push_back(ste);
 };


/*******************************************
/implementation of cashReciept
/*******************************************/

//cash_recept()
cash_receipt::cash_receipt() : transaction(), amount(0),r(invoiceReason) {}

//cash_receipt(args)
cash_receipt::cash_receipt(utils::Time _date, string _client_code, double cash)
    : transaction()
{
    r = invoiceReason;
    transaction_date_ = _date;
    client_code_ = _client_code;
    amount = cash;
}

//docType()get
string cash_receipt::docType()
{
    return CashReceiptTransactionName;
}

//value(set)
cash_receipt *cash_receipt::value(double val)
{
    amount = val;
};

//value()get
double cash_receipt::value()
{
    return amount;
};

//getLedgerPostingEntries()
ledgerEntryVector& cash_receipt::getLedgerEntries()
{
    ledgerEntries_.clear();
    //credit
    account_type typ;
    ledgerEntry _credit;
    switch (r)
    {
    case capitalReason:
        _credit.accountName = StandardShareCapitalAccount;
        typ = CAPITAL;
        break;
    case invoiceReason:
    case prepaymentReason:
        _credit.accountName = clientName();
        typ = RECIEVABLE;
        break;
    case DisposalReason:
        _credit.accountName = ""; //todo
        typ = ASSET;
        break;
    case bankWithdrawReason:
        _credit.accountName = StandardBankAccount;
        typ = ASSET;
        break;
    };
    _credit.accountType = typ;
    _credit.Entry.date = transaction_date_;
    _credit.Entry.transaction_id = number();
    _credit.Entry.ac_name = StandardCashAccount;
    _credit.Entry.type = CREDIT;
    _credit.Entry.amount = value();
    ledgerEntries_.push_back(_credit);

    //debit Cash
    ledgerEntry _debit;
    _debit.accountName = StandardCashAccount;
    _debit.accountType = ASSET;
    _debit.Entry.date = transaction_date_;
    _debit.Entry.transaction_id = number();
    _debit.Entry.ac_name = _credit.accountName;
    _debit.Entry.type = DEBIT;
    _debit.Entry.amount = value();
    ledgerEntries_.push_back(_debit);
    return ledgerEntries_;
};

//stockBookEntryVector()get
stockBookEntryVector& cash_receipt::getStockBookEntries()
{
    //return nothing..
    return stockBookEntries_;
};

//clone()
transaction* cash_receipt::clone(){
    return (transaction*)new cash_receipt(*this);
};





/************************************
/implementation of salesInvoice
/************************************/
salesInvoice::salesInvoice():load_list(),paid_(0.0){};

//constructor(args)
salesInvoice::salesInvoice(tLineItemVector& itms, double pd)
:load_list(itms),paid_(pd){};

//value()
double salesInvoice::value(){
    double val=0;
    for(int i=0; i< lineItems_.size(); i++){
        val+=lineItems_[i].amount();
    }
    return val-paid_;
}

//cashPaid()
salesInvoice* salesInvoice::cashPaid(double pd){
    paid_ = pd;
    return this;
};

//getLedgerEntries()
ledgerEntryVector& salesInvoice::getLedgerEntries(){
    ledgerEntries_.clear();

    if(paid_)//some cash was paid?
        post(DEBIT,StandardCashAccount,paid_,ASSET,StandardSalesAccount);
    post(DEBIT,clientName(),value(),RECIEVABLE,StandardSalesAccount);
    
    double sales = 0.0;
    for(int i=0; i<lineItems_.size(); i++){
        sales+= lineItems_[i].amount();
    }
    post(CREDIT,StandardSalesAccount,sales,INCOME,clientName());
    return ledgerEntries_;
}

//getStockBookEntries()
stockBookEntryVector& salesInvoice::getStockBookEntries(){
    stockBookEntries_.clear();
    spost(StockSold,lineItems_);
    return stockBookEntries_;
}

//docType()
string salesInvoice::docType(){
    return CreditSaleTransactionName;
}

//clone()
transaction* salesInvoice::clone(){
    return new salesInvoice(*this);
}



/*********************************
/implementation of Load_list class 
***********************************/

//lineItems()get
tLineItemVector& load_list::lineItems(){
    return lineItems_;
};

//insertLineItem(t)
load_list* load_list::insertLineItem(tLineItem x){
    lineItems_.push_back(x);
    return this;
};

//removeLineItem(i)
load_list* load_list::removeLineItem(int itm){
    if (itm>=lineItems_.size())return this;
    lineItems_.erase(lineItems_.begin()+itm);
    return this;
};

//setLineItems(tLineItemVector)
load_list* load_list::setLineItems(tLineItemVector lv){
    for(int i=0; i<lv.size(); i++){
        lineItems_.push_back(lv[i]);
    }
    return this;
};

//load_list(tLineItemVector);
load_list::load_list(tLineItemVector& list_){
    lineItems_ = list_;
};


//////implementation of purchaseLoad////////////
////////////////////////////////////////////////

//value()get
double purchaseLoad::value(){
    double val=0.0;
    for(int i=0; i<lineItems_.size(); i++){
        val += lineItems_[i].amount();
    }
    return val;
};

//getLedgerEntries()get
ledgerEntryVector& purchaseLoad::getLedgerEntries(){
    ledgerEntries_.clear();
    //debit purchases
    ledgerEntry _debit;
    _debit.accountName = StandardPurchasesAccount;
    _debit.accountType = ASSET;
    _debit.Entry.date = transaction_date_;
    _debit.Entry.transaction_id = number();
    _debit.Entry.ac_name = StandardMonoSupprierAccount;
    _debit.Entry.type = DEBIT;
    _debit.Entry.amount = value();
    ledgerEntries_.push_back(_debit);
    //credit
    //debit Cash
    ledgerEntry _credit;
    _credit.accountName = StandardMonoSupprierAccount;
    _credit.accountType = PAYABLE;
    _credit.Entry.date = transaction_date_;
    _credit.Entry.transaction_id = number();
    _credit.Entry.ac_name = StandardPurchasesAccount;
    _credit.Entry.type = CREDIT;
    _credit.Entry.amount = value();
    ledgerEntries_.push_back(_credit);
    return ledgerEntries_;
};

//getStockBookEntries
 stockBookEntryVector& purchaseLoad::getStockBookEntries(){
     stockBookEntries_.clear();
     stockBookEntry ste;
     ste.stockMvtType = StockPurchased;
     ste.items = lineItems_;
     stockBookEntries_.push_back(ste);
     return stockBookEntries_;
 };

//docType()get
string purchaseLoad::docType(){
    return StandardPurchasesAccount;
}

//constructor()
purchaseLoad::purchaseLoad():load_list(){};

//constructor(tLineItemVector);
purchaseLoad::purchaseLoad(tLineItemVector v):load_list(v){};

//copy self and return
transaction* purchaseLoad::clone(){
    return (transaction*) new purchaseLoad(*this);
};






/*******************************************************
/implementation of rsLoadOut
/******************************************************/
//rsLoadOut()
rsLoadOut::rsLoadOut():load_list(){};

//rsLoadOut(args)
rsLoadOut::rsLoadOut(tLineItemVector t):load_list(t){};

//value()
double rsLoadOut::value(){
  double val=0.0;
    for(int i=0; i<lineItems_.size(); i++){
        val += lineItems_[i].amount();
    }
    return val;
}

//getLedgerEntries
ledgerEntryVector& rsLoadOut::getLedgerEntries(){
    return ledgerEntries_; //nothing to return
};

//getStockBookEntries()
stockBookEntryVector& rsLoadOut::getStockBookEntries(){
     stockBookEntries_.clear();
     stockBookEntry ste;
     ste.stockMvtType = StockSentOnRouteSale;
     ste.items = lineItems_;
     stockBookEntries_.push_back(ste);
     return stockBookEntries_;    
};

//docType()
string rsLoadOut::docType(){
    return RsLoadOutTransactionName;
}

//clone();
transaction* rsLoadOut::clone(){
    return (transaction*) new rsLoadOut(*this);
}






/*******************************************************
/implementation of rsLoadIn
/*******************************************************/

//rsLoadIn()
rsLoadIn::rsLoadIn():load_list(){};

//rsLoadIn(args)
rsLoadIn::rsLoadIn(tLineItemVector t):load_list(t){};

//value()
double rsLoadIn::value(){
  double val=0.0;
    for(int i=0; i<lineItems_.size(); i++){
        val += lineItems_[i].amount();
    }
    return val;
}

//getLedgerEntries
ledgerEntryVector& rsLoadIn::getLedgerEntries(){
    return ledgerEntries_; //nothing to return
};

//getStockBookEntries()
stockBookEntryVector& rsLoadIn::getStockBookEntries(){
     stockBookEntries_.clear();
     stockBookEntry ste;
     ste.stockMvtType = StockReturnedFromRouteSale;
     ste.items = lineItems_;
     stockBookEntries_.push_back(ste);
     return stockBookEntries_;    
};

//docType()
string rsLoadIn::docType(){
    return RsLoadInTransactionName;
}

//clone()
transaction* rsLoadIn::clone(){
    return new rsLoadIn(*this);
}




/*******************************************************
//implementation of RouteSale
/*******************************************************/
routeSale::routeSale():
    transaction(),
    df_(nullptr),
    sf_(nullptr),
    dscf_(nullptr){};

routeSale::routeSale(const routeSale& rs):transaction(rs){
    df_ = rs.df_;
    sf_ = rs.sf_;
    dscf_ = rs.dscf_;
    
    for(int i=0; i< transactions_.size(); i++){
        delete transactions_[i];
    }
    transactions_.clear();

    transaction* t=0;
    for(int i=0;   i < rs.transactions_.size(); i++){
        t = rs.transactions_[i]->clone();
        transactions_.push_back(t);
    }
};

//copy assigment
routeSale& routeSale::operator=(const routeSale& rs){
    if(this ==& rs) //self assigment
        return *this;//all done
    transaction::operator=(rs);
    df_ = rs.df_;
    sf_ = rs.sf_;
    dscf_ = rs.dscf_;

    for(int i=0; i< transactions_.size(); i++){
        delete transactions_[i];
    }
    transactions_.clear();
    
    transaction* t=0;
    for(int i=0;   i < rs.transactions_.size(); i++){
        t = rs.transactions_[i]->clone();
        transactions_.push_back(t);
    }
    return *this;
}

//move constructor
routeSale::routeSale(routeSale&& rs):transaction(rs){ //move parent
    df_ = rs.df_;
    sf_ = rs.sf_;
    dscf_ = rs.dscf_;

    for(int i=0; i< transactions_.size(); i++){
        delete transactions_[i];
    }
    transactions_.clear();
    
    transactions_ = rs.transactions_;//steal

    for(int i=0;   i < rs.transactions_.size(); i++){
        delete rs.transactions_[i];
    }
}

//move assignment
routeSale& routeSale::operator=(routeSale&& rs){
    transaction::operator=(rs); //move parent
    df_ = rs.df_;
    sf_ = rs.sf_;
    dscf_ = rs.dscf_;

    for(int i=0; i< transactions_.size(); i++){
        delete transactions_[i];
    }
    transactions_.clear();
    
    transactions_ = rs.transactions_;//steal

    for(int i=0;   i < rs.transactions_.size(); i++){
        delete rs.transactions_[i];
    }
    return *this;
};

//insertTransaction
routeSale* routeSale::insertTransaction(transaction* trans){
    /*requirement
    /should ask trans for a copy of self itself by calling trans' clone().
    /there by, the copy is managed internally since trans won't
    /keep track of it.
    /this method is the reason clone was added to transaction's interface
    
    /assumptions.
    /trans has implemented clone() which returns a copy of self
    /trans can be null or a reference to this. in such cases, do nothing

    /implementation
    /based on the clone() pattern.*/
    if(!trans || //blank
        trans ==this) //self
        return this; //nothing to don
     //get clone and store it
     transactions_.push_back(trans->clone());
     return this;
};

//operator[]
transaction& routeSale::operator[](int index){
    if(index<0||index>=transactions_.size())
        return *this;//really?
    return *(transactions_[index]);
}

//at()
transaction& routeSale::at(int index){
    return (this->operator[](index));
}

//removeTransaction
int routeSale::eraseTransaction(int i){
    //returns new size()
    if(i<0||i>=transactions_.size())
        return transactions_.size();
    transactions_.erase(transactions_.begin()+i);
    return transactions_.size();
}

//setDiffFunction
void routeSale::setDiffFunction(diffFunc fn){
    df_ = fn;
}

//setsumFunction()
void routeSale::setSumFunction(sumFunc fn){
    sf_ = fn;
}

//setSalesDiscountFunc()
void routeSale::setSalesDiscountFunction(discountFunc fn){
    dscf_ = fn;
}


//value()
double routeSale::value(){
    //this routine depends on the docType property to identify
    //loadOuts and loadIns it assumes the doctype returns
    //the standard Transaction Name Constants to distinguish
    //the different transactions.
    //assumes that transaction objects return one of these constants.
    //in their docType() interface

    //we cant do anything without the summing and 
    //subracting functions
    if(!df_&& !sf_){
        return errVal;
    }

    tLineItemVector rsale;
    double val = sales(&rsale);

    //remove discount if applicable 
    if(dscf_){
        return val-(dscf_(rsale,clientName()));
    }else{
        return val;
    } 
        
}

//sales(args) ->value()
double routeSale::sales(tLineItemVector* sold){
    if(!df_)return 0.0;
    tLineItemVector loadout;
    tLineItemVector loadin;
    tLineItemVector _sales;

    //store internally if user didn't request for lineItems'
    tLineItemVector&  salesRef = sold?*sold:_sales;
    //addup the loadouts and loadin
    sumLoads(loadout,loadin);

    //calculate items sold
    salesRef = df_(loadout, loadin);
    //get their value()
    double val=0.0;
    for(int i=0; i<salesRef.size(); i++){
        val += salesRef[i].amount();
    }
    return val;    
}


//sumLoads()
void routeSale::sumLoads(tLineItemVector& sumLoadOut, tLineItemVector& sumLoadIn){
    transactionVector& allTrans = transactions_;//alias. just to typeless
    load_list* myTrans;

    for(int i=0; i < allTrans.size(); i++){
        if(!allTrans[i])continue; //nothing to do;
        if(allTrans[i]->docType()==RsLoadOutTransactionName){
            myTrans = (load_list*)(allTrans[i]);         //cast to get lineItems()
            sumLoadOut = sf_(sumLoadOut,myTrans->lineItems()); //sum
        }
        if(allTrans[i]->docType()==RsLoadInTransactionName){
            myTrans = (load_list*)(allTrans[i]);
            sumLoadIn = sf_(sumLoadIn,myTrans->lineItems());
        }
    };
}

//getLedgerEntries();
ledgerEntryVector& routeSale::getLedgerEntries(){
    ledgerEntries_.clear();
    transactionVector& allTrans = transactions_;//alias

    tLineItemVector itemSold;
    double _sales = sales(&itemSold);
    string salesAcc = StandardSalesAccount;
    string cashAcc  = StandardCashAccount;
    post(CREDIT,salesAcc,_sales,INCOME,cashAcc);
    
    //compute discount;

    double _discount = dscf_? dscf_(itemSold,clientName()) : 0.0;

    if(_discount){
        //post it
        post(DEBIT,StandardDiscountAllowedAccount,_discount,EXPENSE,salesAcc);
        _sales -= _discount; //update;
    }
   //debit respective accounts.
    //do we have cash?

    double cashpaid =  cashPaid();
    if(cashpaid == _sales){ //fully paid?
        post(DEBIT,cashAcc,cashpaid,ASSET,salesAcc);
    
    }else if(cashpaid < _sales){
        if((long)cashpaid) {//if something was paid
            post(DEBIT,cashAcc,cashpaid,ASSET,salesAcc);
        }
        //do we have invoices?
        double sumOfInvoices = 0.0;
        for(int i=0; i< allTrans.size(); i++){
            if(allTrans[i]->docType()==CreditSaleTransactionName){
                //post it
                post(DEBIT,allTrans[i]->clientName(),
                    allTrans[i]->value(),RECIEVABLE,salesAcc);
                sumOfInvoices +=allTrans[i]->value();
            };
        };
        //do we still have a gap? its a shortage
        if(_sales > (sumOfInvoices+cashpaid)){
            //post shortage
            post(DEBIT,clientName(),_sales-(sumOfInvoices+cashpaid),
                PAYABLE,salesAcc);
        }
        //do we have an excess?
        if(_sales <(sumOfInvoices+cashpaid)){
            //post excess
            post(CREDIT,clientName(),(sumOfInvoices+cashpaid)-_sales,
            PAYABLE,salesAcc);
        }
    
    }else if(cashpaid > _sales){
        //lets assume the difference is a payment of previous shortage...
        post(CREDIT,clientName(),cashpaid-_sales,PAYABLE,cashAcc);
        post(DEBIT,cashAcc,cashpaid-_sales,ASSET,clientName());
        //to do
        //handle cashPaid >sales and invoices available too! 
    }


    return ledgerEntries_;
};


//cashPaid
double routeSale::cashPaid(){
    //assumes all receipts belong to this routesale, ie..
    //previous invoice settlement receipts are not in this transaction
    
    transactionVector& allTrans = transactions_;//alias. just to typeless
    double cash;

    for(int i=0; i < allTrans.size(); i++){
        if(!allTrans[i])continue; //nothing to do;
        if(allTrans[i]->docType()==CashReceiptTransactionName){
            cash += allTrans[i]->value(); 
        }
    }
    return cash;    
}

//getStockBookEntries()
stockBookEntryVector& routeSale::getStockBookEntries(){
    stockBookEntries_.clear();
    transactionVector& allTrans = transactions_;//alias

    for(int i=0; i<allTrans.size(); i++){
        if(!allTrans[i])continue;
        stockBookEntryVector entrys(allTrans[i]->getStockBookEntries());
        for(int j=0; j<entrys.size(); j++){
            //invoice sales are already part of our sales
            if(allTrans[i]->docType()==CreditSaleTransactionName){
                entrys[j].stockMvtType = StockRecievable;
            }
            stockBookEntries_.push_back(entrys[j]);
        }
    }

    //now, compute and include sales entries
    tLineItemVector sls;
    sales(&sls);
    spost(StockSold,sls);
    return stockBookEntries_;
};

//docType
string routeSale::docType(){
    return RouteSaleTransactionName;
};


//clone()
transaction* routeSale::clone(){
    return new routeSale(*this);
}

//destructor
routeSale::~routeSale(){
    for(int i=0; i<transactions_.size(); i++){
       delete transactions_[i];
    }
}



