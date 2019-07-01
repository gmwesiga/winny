#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <string>
#include <map>

using std::map;
using std::string;


class ProductDef{
  public:
    struct Table{
    /*table defines an Internal class for tracking and manipulating products*/
        
        int add(ProductDef*);
        /*add only products with unique ids, return 0 if id already exists.*/
        
        int remove(string id);
        int size();
        ProductDef* find(string productid);/*null pointer returned if not found*/
        
        /*iterate table elements*/
        ProductDef* getElement();
        void begin();
        int eof();

        void sortById();
        void sortByCompCount();/*sort by component Count*/
        
        Table():_eof(1){};
        Table(const Table &o);
        ~Table(){};

        private:
        map<string,ProductDef*> tbl;
        int _eof;
        map<string,ProductDef*>::iterator cursor;
    };

    /*class global variable: for table tracking all created productDefs accessed with table()*/
    static Table table;

    ProductDef(string id, string name);
    /*Constructor creates table and adds it to internal products table for tracking
     destructor deletes table entry*/
    ~ProductDef();
    /* information about product */
    string name();          //every product has a unique name
    int isComposite();    /*if true, there must be atleast one entry in components table*/
    double price();
    double costPrice(){return cpx;};
    double sellingPrice(){return px;};
 
  
    /*componets that make up a product*/
    int addElement(string id, int num);
    /*id must match a product id in the internal table*/

    int count();
    

    ProductDef* getElement();/*returns null pointer if empty or eof()==true*/
    
    /*Get data of current component selected*/
    int ElementCount();
    string ElementId();

    /*navigate through list of component productDefinitions*/
    void begin(); /*current component = first component in list*/
 
    int eof();
    /*current component == last component. internal cursor can't move anymore,
    call begin()*/

    void deleteElement(string id);
    void clearElements();

    /* set properties */
    void name(string _name);
    void price (double px);
    void cost(double px);

    private:

     void next();
    /*increment internal pointer to point to next component. 
    if currentComponent before next() was last item in list, eof()is set to true
    test for eof every after next()*/

    string product_name, _id;
    int _eof;
    double px, cpx;

    map<string,int> comps;/*id, count*/
    map<string,int>::iterator cursor;

    /* optimisations additions on 7 dec*/
    int units_purchased;
    int units_sold;
    int units_damaged;
    int units_returned_out;
    int units_returned_in;
};


 #endif