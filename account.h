#ifndef WINNY_ACCOUNT_H
#define WINNY_ACCOUNT_H
#include <string>
#include <vector>
#include "gmtime.h"

using std::string;
using std::vector;

namespace winny{

typedef utils::Time Date; 

//There are only 2 types of Entries: 
//a debit entry and a credit entry
enum entry_type {
    DEBIT,CREDIT
};

/*all accounts can be categorised into:
    Assets
    Liabilities
    Incomes & RECIEVABLES
    Capital
    Expenses & PAYABLES
*/
enum account_type {
    ASSET, INCOME, PAYABLE, CAPITAL, RECIEVABLE, EXPENSE 
};

/*A standard T-Account Entry has:-
    @ date field =>date;
    @ reference of account where the double entry was made => ac_no
    a description of the transaction (ommited here)
    @ the amount of the entry =>amount    
    since it has no behaviour, and agile recommends structs for datastructures,
    a struct is appropriate  */
struct entry{
    long transaction_id;
    Date date; 
    int ac_no;
    string ac_name;
    string description;    
    entry_type type;  //which entry is this?
    double amount;
};

/*an account publishes events*/
enum Account_Events{BEFORE_DEBIT, ON_DEBIT, BEFORE_CREDIT, ON_CREDIT, ON_CHANGE};

/*observers of Account get called with arguments of the account object
 they can then query which event with event(); additional event data can be found in
 event_data()
 returning 0 from the callback signals something went wrong, and the previous change may be rolled back.
 */
class Account; //forward declaration 
typedef int(*Account_Handler)(Account*);

class Account{
    public:
    Account* set_name(string n);
    Account* set_number(int n);
    Account* set_type(account_type );

    //info
    account_type type();
    const string& name();
    int number();
    int size(); //number of entries
    int debits(); //how many debit entries in all
    int credits(); //how many credit entries in all
    double balance(); //closing balance right  now
    double balance(const Date& someDate); //closing balance as at someDate
    Date& date_created();
    Date& date_of_last_activity();


    entry& get_entry(int);
    entry& operator[]( int);
    Account* append_entries(entry* ent,int num); //append array of num entries to end
    const entry* entries(); //first entry

    //behaviour
    Account* debit(entry&);
    Account* credit(entry&);

    Account* add_handler(Account_Handler);
    Account* remove_hander();

    Account(string name_, account_type typ);
    //Account() = delete;
    //Account(const Account&);
    //default copy constructor, and assignment are ok

    private:
    string _name;
    int _number;
    account_type _type;
    double _balance;
    int _credits;
    int _debits;
    Date _date_created;
    Date _date_of_la;
    vector<entry> _entries;
    Account_Handler _handler;

    bool entry_is_before(const Date&, entry);
    bool is_debit_type()
    {return _type ==ASSET || _type == RECIEVABLE || _type == EXPENSE;}

};


};//end of namespace utils

#endif