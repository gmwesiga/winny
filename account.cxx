#include "gmtime.h"
#include "account.h"
#include <stdexcept>

namespace winny {
	//makes n the account name
	Account* Account::set_name(string n){
		_name = n;
		return this;
	};
	
	//makes n the account number
	Account* Account::set_number(int n){
		_number = n;
		return this;
	}

	//makes t the account type. t is one of the account_type enums
	Account* Account::set_type(account_type t){
		_type = t;
		return this;
	}

	//returns the account type
	account_type Account::type(){return _type;};	

	//return account name as string
	const string& Account::name(){return _name;};

	//returns the account number as integer;
	int Account::number(){return _number;}

	int Account::size(){return _entries.size();};

	int Account::debits(){return _debits;};

	int Account::credits(){return _credits;};

	double Account::balance(){return _balance;}

	bool entry_is_before(const Date& dd, entry& e){
		return e.date.day_is_before(dd);
	};

	double Account::balance(const Date& somedate){
		return 90000;//todo, implement this.
	};

	Date& Account::date_created(){
		return _date_created;
	};

	Date& Account::date_of_last_activity(){
		return _date_of_la;
	}

//get_entry(arg)
entry& Account::get_entry(int i){
	if(!_entries.size() ||i>_entries.size() ||i<0)
		throw std::out_of_range("Account::operator[int]recieved out of range value");
	return _entries[i];
};

entry& Account::operator[](int i){
	return get_entry(i);
}

	Account* Account::debit(entry& e){
		_entries.push_back(e);
		_balance = is_debit_type()?_balance+e.amount:_balance-e.amount;
		_debits++;
		return this;
	};

	Account* Account::credit(entry& e){
		_entries.push_back(e);
		_balance = is_debit_type()?_balance-e.amount:_balance+e.amount;
		_credits++;
		return this;
	};

	/*sets user callback */
	Account* Account::add_handler(Account_Handler h){
		_handler = h;
	};

	/*sets handler to null*/
	Account* Account::remove_hander(){ _handler = NULL;};

	Account::Account(string name_, account_type typ){
		_name = name_;
		_type = typ;
		_number  = -999;
		_balance = _credits =_debits = 0;
		_date_created = _date_of_la = Date();
		_entries.reserve(10);
		_handler = 0;
	};
};


/*returns printable string of account type/
string actype(utils::Account ac){
	static string c[]={"Asset Account",
				"Income Account",
				"Account Payables",
				"Captital",
				"Account Receivables",
				"Expense" };
	return c[ac.type()];
};

/*print out account object/
printacc(utils::Account ac){
	std::printf("*******************\n");
	std::printf("Ac Name %s\n",ac.name().c_str());
	std::printf("Ac type %s\n", actype(ac).c_str());
	std::printf("created on %s\n",ac.date_created().to_string().c_str());
	printf("*****************************\nentries\n");
	printf("balance %f\n", ac.balance());
}

//test
int main(){
	utils::Time y;
	utils::Time a(2017,12,10);
	a.hours(23)->minutes(30)->seconds(15);
	y.diff(a);
	//std::printf("%s\n", a.to_string().c_str());
	std::printf(" %d", a.day_is_after(y));

	//account tests;

	utils::Account ac("Gilbert Mwesiga",utils::PAYABLE);
	utils::entry e = {utils::Time(),898,utils::DEBIT,1000000};
	ac.debit(e);
	e = {utils::Time(2017,1,12),890,utils::CREDIT,200000};
	ac.credit(e);
	printacc(ac);

	return 0;
}*/