#ifndef transaction_h
#define transaction_h
/*
*Revised 24/ jan /2017 into file Transaction
*/

#include "gmtime.h"
#include "account.h"
#include <string>
#include "records_lib.h"

namespace Winny {
using std::string;

const string DEFAULT_CLIENT_CODE = "000-000";
const string DEFAULT_CLIENT_NAME = "winny Client";

//Names of standard Accounts that
const string StandardCashAccount = "Cash Account";
const string StandardBankAccount = "Bank Account";
const string StandardPurchasesAccount = "Purchases Account";
const string StandardSalesAccount  = "Sales Account";
const string StandardReturnInwardsAccount = "Return Inwards Account";
const string StandardReturnOutwardsAccount = "Return Outwards Account";
const string StandardShareCapitalAccount = "Share Capital Account";
const string StandardMonoSupprierAccount = "Main Supplier Account";
const string StandardDiscountAllowedAccount = "Discounts Allowed Account";

//names of Standard store stock Movement log/Entry Types
enum stockMovementType{
    StockPurchased=0,
    StockSold,
    StockWrittenOff,
    StockReturnedInwards,
    StockReturnedOutwards,
    StockSentOnRouteSale,
    StockReturnedFromRouteSale,
    StockRecievable
};

//names of Standard transactions
const string CashReceiptTransactionName = "Cash Receipt";
const string CashSaleTransaction = "Cash Sale";
const string RsLoadOutTransactionName = "Delivery Note";
const string RsLoadInTransactionName = "Goods Received Note";
const string RouteSaleTransactionName = "Route Sale";
const string CreditSaleTransactionName = "Invoice Note";

//which account to post into?
struct ledgerEntry {
    entry Entry;
    string accountName;
    account_type accountType;
};
typedef vector<ledgerEntry> ledgerEntryVector;

struct stockBookEntry {
    long transactionId;
    stockMovementType stockMvtType;
    tLineItemVector items;
};
typedef vector<stockBookEntry> stockBookEntryVector;

enum status {open, closed};

class transaction{
// represents any transaction as used in accounting
// this class is an abstract class for all other transactions
  public:
  virtual long number();
  virtual transaction* number(long);
  virtual transaction* clientId(string c_code);     //id to uniquely identify this document
  virtual string clientId();
  virtual string clientName();
  virtual transaction* clientName(string c_name);
  virtual transaction* transactionDate(utils::Time tdate);      //note this takes a timestamp for now 
  virtual utils::Time transactionDate();
  virtual status tStatus();
  void close(); 
  virtual string docType()=0;         // a name of the concrete transaction eg "cash reciept", "sales invoice"
  virtual double value()=0;          // monetary value of the transaction captured by this source document
  virtual ledgerEntryVector& getLedgerEntries()=0;
  virtual stockBookEntryVector& getStockBookEntries()=0;
  virtual transaction* handlerNumber(long num);
  virtual long handlerNumber( ); 
  virtual transaction* clone()=0; //return self
  virtual ~transaction(){};
  
  protected:
    transaction();
    long trans_num_;
    string client_code_;
    string client_name_;
    utils::Time transaction_date_;
    status status_;  
    long handlerNum_;
    ledgerEntryVector ledgerEntries_;
    stockBookEntryVector stockBookEntries_;

    virtual void spost(stockMovementType smt, tLineItemVector& itm);
    virtual void post(entry_type entryType, string accountToPost,
      double amount, account_type typeOfThisAccount,string contraAccName);
};
typedef  vector<transaction*> transactionVector;


enum cash_reason{
  capitalReason,
  invoiceReason,
  prepaymentReason,
  DisposalReason,
  bankWithdrawReason,
  Unspecified
};

class cash_receipt : public transaction
{
  public:
    cash_receipt();
    cash_receipt(utils::Time _date, string _client_code, double cash);  
    cash_receipt(double amt):r(Unspecified),amount(amt){};
    string docType();  
    cash_receipt* value(double val);
    cash_receipt* reason(cash_reason r_){r=r_; return this;};
    cash_reason reason(){return r;};
    transaction* clone();//return self;
    double value();

    ledgerEntryVector& getLedgerEntries();
    stockBookEntryVector& getStockBookEntries();
  private:
    double amount;
    cash_reason r;
};


//this abstract class defines an interface for 
//transactions/ source documents that contain
//a list af line items. eg a cash sale, invoice
//routesale load out, purchase loadin etc
class load_list : public transaction{
  public:
    virtual tLineItemVector& lineItems();
    virtual load_list* insertLineItem(tLineItem);
    virtual load_list* removeLineItem(int itm);
	  virtual load_list* setLineItems(tLineItemVector lv);
  
  protected: 
    tLineItemVector lineItems_;
    load_list():transaction(){};
    load_list(tLineItemVector& list_);
};


//this concrete class represents contents of purchase load
//from the factory / main supplier previously as ordered
class purchaseLoad: public load_list{
  public:
   purchaseLoad();
   purchaseLoad(tLineItemVector);
   double value();
   ledgerEntryVector& getLedgerEntries();
   stockBookEntryVector& getStockBookEntries();
   string docType();
   transaction* clone();//return self;
};


//this concrete class represents contents of return out load
//to the factory / main supplier previously as ordered
class returnOut: public load_list{
   double value();
   ledgerEntryVector& getLedgerEntries();
   stockBookEntryVector& getStockBookEntries();
   string docType();
};


//this concrete class represents contents of returnIn load
// from the market previously sold
class returnIn: public load_list{
   double value();
   ledgerEntryVector& getLedgerEntries();
   stockBookEntryVector& getStockBookEntries();
   string docType();
   transaction* clone();//return self;
};


//this concrete class represents contents of cash sale
/* class cashSale: public load_list{
  public:
   double value();
   ledgerEntryVector& getLedgerEntries();
   stockBookEntryVector& getStockBookEntries();
   string docType();
   transaction* clone();//return self;
};
 */

//this concrete class represents contents of sales Invoice
class salesInvoice: public load_list{
   public:
   salesInvoice();
   salesInvoice(tLineItemVector& itms,double pd=0.0);
   double value();
   salesInvoice* cashPaid(double );
   ledgerEntryVector& getLedgerEntries();
   stockBookEntryVector& getStockBookEntries();
   string docType();
   transaction* clone();//return self;

   private:
   double paid_;
};


//this concrete class represents contents of route sale  loadout
class rsLoadOut: public load_list{
  public:
   rsLoadOut();
   rsLoadOut(tLineItemVector);
   double value();
   ledgerEntryVector& getLedgerEntries();
   stockBookEntryVector& getStockBookEntries();
   string docType();
   transaction* clone();//return self;
};


//this concrete class represents contents of rs loadin
class rsLoadIn: public load_list{
  public:
   rsLoadIn();
   rsLoadIn(tLineItemVector);
   double value();
   ledgerEntryVector& getLedgerEntries();
   stockBookEntryVector& getStockBookEntries();
   string docType();
   transaction* clone();//return self;
};

//this concrete class represents contents of a routesale
typedef tLineItemVector (*diffFunc)(tLineItemVector&,tLineItemVector&);
typedef tLineItemVector (*sumFunc)(tLineItemVector&, tLineItemVector&);
typedef double (*discountFunc)(tLineItemVector&,string CustId);
const double errVal = -9999.999;

class routeSale: public transaction{
  public:
  routeSale();
  routeSale(const routeSale& );
  routeSale& operator=(const routeSale&);
  routeSale(routeSale&& rs);
  routeSale& operator=(routeSale&& rs);

  routeSale* insertTransaction(transaction*);
  //transactionVector& transactions(); 
    //removed because it would lead to unchecked modifications
  transaction& operator[](int index);
  transaction& at(int index);
  int eraseTransaction(int i);
  void setDiffFunction(diffFunc);
  void setSumFunction(sumFunc);
  void setSalesDiscountFunction(discountFunc);

  double value();
  double cashPaid();
  double sales(tLineItemVector* in=0);
  ledgerEntryVector& getLedgerEntries();
  stockBookEntryVector& getStockBookEntries();
  string docType();
  transaction* clone();//return self;
  ~routeSale(); //handle transactionVector

  private:
  diffFunc  df_;
  sumFunc   sf_;
  discountFunc dscf_;
  transactionVector transactions_;
  void sumLoads(tLineItemVector& sumLoadOut,tLineItemVector& sumLoadIn);//sum loadOuts;
};

};//endof winny

 #endif
