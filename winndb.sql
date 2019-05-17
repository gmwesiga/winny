--March 1 2017
--winny sql db definition file for the sqlite database
--author :Gilbert Mwesiga.
--assumptions...


--Product table
CREATE TABLE Products (
    _Idnum  text unique, 
    _name           text not null unique,
    _isComposite    integer not null default 0,
    _costPrice      real not null default 0.0,
    _sellingPrice   real default 0.0 not null,


    _salesCommision real default 0.0,
    _salesDiscountAllowed real default 0.0,
    _toUnitConvertionFactor real default 0.0 not null,

    _sumOfComponets integer not null default 0,
    _unitsPurchased integer not null default 0,
    _unitsSold      integer not null default 0,
    _unitsReturnedOut   integer not null default 0,
    _unitsReturnedIn    integer not null default 0,
    _unitsDamaged       integer not null default 0, --used to writeoff
    _dateCreated        text not null default current_timestamp,
    _datelastModified   text not null default current_timestamp,
    check(_sellingPrice>=_costPrice),
    primary Key(_Idnum)
);

CREATE TRIGGER _computeProductIdnum after INSERT on Products
    begin
        UPDATE Products SET
         _Idnum = printf('PROD%.5d',_rowid_)
        WHERE  rowid = last_insert_rowid();
    end;
    
    --_Idnum will initally be  an auto generated integer on inserts
    -- the trigger then modifies it to a different format,
    --should the trigger fail to excute, we can be sure _Idnum remains unique
    --but in a format that is not what we want
    
    --users shall provide default values for _salesCommission
    --salesDiscountAllowed, and _toUnitCoversionFactors for every product
    --but shall also allow flexiblity of defining them on a per
    --account basis.
    --eg we may want a certain salesman x to earn a certain commission on
    --a product y.
    --conversally the above entries for a product act as defaults...
    --then we create the separate tables to handle the special Account
    --cases.

CREATE TABLE ProductComponents(
    productIdnum text ,--let app handle referencial integrity
    componentIdnum text, --app knows how to handle referencial integrity
    count           integer default 1
   primary key(productIdnum,componentIdnum) 
);


CREATE TABLE Accounts (
    _Idnum text unique not null,
    _name   text not null, --i think this shouldn't be null
    _type   integer not null default 1,
    _size   integer not null default 0,
    _debits integer not null default 0,
    _credits integer not null default 0,
    _openingBalance real not null default 0.0,
    _dateCreated text not null default current_timestamp,
    _dateModified text not null default current_timestamp,
    _lastActivity text not null default current_timestamp,
    _earnsSalary  integer not null default 0,
    _isActive integer not null default 1,
    _isEmployee integer not null default 0,
) ;

CREATE TABLE AccountEntries(
    _Idnum text unique not null,
    _accountIdnum text not null,
    _transactionIdnum text not null,
    _date text default current_timestamp not null,
    _refAccountId text not null,
    _description text not null,
    _type integer not null default 0,
    _amount real not null default 0.0
);--trigger here.. to update accounts table on inserts 

--To be able to assign different discount rates and commssion rates
--to different Client Accounts per product, we shall store those..
--special per client configurations here for such clients. clients not 
--defined in this table default those settings from the products table.
--clients defined here therefore overide those settings in the products table
CREATE TABLE AccountProductConfig (
    _accountIdnum text not null,
    _productIdnum text not null,
    _salesCommision real default 0.0,
    _salesDiscountAllowed real default 0.0,
    _toUnitConvertionFactor real default 0.0 not null,
    primary key (_accountIdnum, _productIdnum)
);

CREATE TABLE Transactions (
    _Idnum text primary key,
    _clientIdnum text unique not null,
    _date text not null default current_timestamp,
    _dateModified text not null default current_timestamp,
    _value real not null default 0.0,
    _type integer not null --eg receipt,cash sale ,etc
);

--a transaction must have ledger book entries
--a transaction can optionally have storebook entries

CREATE TABLE StoreBookEntries(
    _idnum integer primary key,
    _transactionIdnum text not null,
    _productIdnum text not null,
    _type int not null, --1 is sales, 2 purchases, 3 
    units int default 0
);



