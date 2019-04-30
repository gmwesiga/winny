#ifndef source_document_h
#define source_document_h
/*
*Revised 24/ jan /2017 into file Transaction
*/

#include <ctime>
#include <string>
#include <stdio.h>
#include "records_lib.h"
using std::string;

const string DEFAULT_CLIENT_CODE = "000-000";
const string DEFAULT_CLIENT_NAME = "Anonimous";
typedef tm wdate;
const wdate DEFAULT_TRANSACTION_DATE = {0,0,0,1,0,1970,0,0,0}; // 1970-01-01:00:00:00 epoch

const char* DOC_TYPES[] = {"Cash Sale", "Receipt",
					 "Load Out",  "Load In",
					 "Invoice",   "Cheque", 
					 "Generic"};
#define CASH_SALE 0
#define RECEIPT   1
#define LOAD_OUT  2
#define LOAD_IN   3
#define INVOICE   4
#define CHEQUE    5
#define GENERIC   6
#define GENERIC_LOAD  7
					 
class source_document
// represents any source document as used in accounting
// this class is an abstract class for all other source_documents
{
  public:
  enum status                       // a source document can be in any of these states
  {
    SD_OPEN=1,                      //open == it can still be edited, a transaction is still going on
    SD_CLOSED                       //closed == it can nolonger be edited. the transaction is over
  };
  
  void client_id(string c_code)     //id to uniquely identify this document
    { client_code_ = c_code;};
  
  string client_id()
    { return client_code_; };
  
  string client_name()
    { return client_name_; }
  
  void client_name(string c_name)
    { client_name_ = c_name; };
  
  void transaction_date(wdate tdate)      //note this takes a timestamp for now
    { transaction_date_ = tdate; };
    
  wdate transaction_date()
    { return transaction_date_;};

  status doc_status()
    { return status_; }
    
  void close()
    { status_ = SD_CLOSED; }
    
  virtual string doc_type()         // a name of the concrete source_document eg "cash reciept", "sales invoice"
    {return DOC_TYPES[GENERIC]; }
	
  virtual int type_code()
  {return GENERIC; }
  
  virtual double value()          // monetary value of the transaction captured by this source document
    { return 0;}
  
  protected:
    int amount;
    string client_code_;
    string client_name_;
    wdate transaction_date_;
    status status_;
    
    source_document()
      :amount(0.0),
      client_code_(DEFAULT_CLIENT_CODE),
      client_name_(DEFAULT_CLIENT_NAME),
      transaction_date_(DEFAULT_TRANSACTION_DATE),
      status_(SD_OPEN){};
    
    source_document(wdate _date, string _client_code, double cash=0.0)
      :amount(cash),
      client_code_(_client_code),
      client_name_(DEFAULT_CLIENT_NAME),
      transaction_date_(_date),
      status_(SD_OPEN){}
};


class cash_receipt : public source_document
{
  public:
    cash_receipt()
      :source_document(){}
    
    cash_receipt(wdate _date, string _client_code, double cash)
      :source_document(_date,_client_code,cash){}
      
    string doc_type() override
      { return DOC_TYPES[RECEIPT];}
	  
	int type_code() override
	{return RECEIPT;}
      
    void value(double val)
      { amount = val; };
      
    double value()
      { return amount; };
      
  private:
};

class load_list : public source_document
{
  public:
    load_list()
      :source_document(){}
    
    load_list(wdate _date, string _client_code, vector<load_item> list_)
      :source_document(_date,_client_code){product_list = list_; /*printf("\n here assigned: %d\n", product_list.size());*/}
      
    string doc_type() override
      { return DOC_TYPES[GENERIC];}
	  
	int type_code() override
	{return GENERIC_LOAD;}
      
    void value(double val)
      { amount = val; };
      
    double value()
      { return amount; };
      
	vector<load_item> list()
	{return product_list;}
	
	void list(vector<load_item> i)
	{product_list = i;}
  protected:
    vector<load_item> product_list;
};

class load_out: public load_list
{
	public:
	load_out():load_list(){}
	load_out(wdate _date, string _client_code, vector<load_item> list_)
      :load_list(_date,_client_code,list_){}
	  
	load_out( load_list ll){ 
		vector<load_item> temp =  ll.list();
		load_list(ll.transaction_date(),ll.client_id(),temp);
		product_list = temp;
	}
	
	string doc_type() override
	{return DOC_TYPES[LOAD_OUT];}
	
	int type_code() override
	{return LOAD_OUT;}
};


class load_in : public  load_list
{
	public:
	load_in():load_list(){}
	load_in(wdate _date, string _client_code, vector<load_item> list_)
      :load_list(_date,_client_code,list_){}
	  
	load_in( load_list ll){ 
		//first copy (because you don't have a move construct. war story)
		vector<load_item> temp =  ll.list();
		load_list(ll.transaction_date(),ll.client_id(), temp);
		product_list = temp;
	}
	
	string doc_type() override
	{return DOC_TYPES[LOAD_IN];}
	
	int type_code() override
	{return LOAD_IN;}
};

#endif
