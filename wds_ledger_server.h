#ifndef WINNY_LEDGER_H
#define WINNY_LEDGER_H
#include "account.h"

namespace winny_DataServer_link {
/*a ledger is a container of all accounts of the business
  as such, it has "persistent" storage semantics  */
typedef ledger_acc_no int

typedef {
    ledger_acc_no accountNumber;
    string accountName;
    account_type  type;
    wnumber amount; 
} ledger_listing_entry

typedef vector<ledger_listing_entry> ledger_listing

class Ledger_server
{
    public:
    //a write operation normally has a name component. this time the name is in the data
    virtual ledger_acc_no create_new_account(string AccountName)=0; 
    
    //get the account Account.name()==AccountName
    virtual Account& get_account_by_name(string AccountName); 
    
    //get the account Account.number()==ledger_acc_no;
    virtual Account& get_account_by_number(ledger_acc_no); 

    //get trial balance
    virtual ledger_listing get_trial_balance();

    //list all accounts specified by argument
    virtual ledger_listing ls_accounts(string name_pattern, int account_type )
    
    virtual bool remove_account(string AccountName);
};

};
#endif