#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "gmdataset.h"

using std::map;
using std::string;
using std::vector;


class ProductDef{
  public:
    struct Table{
    /*table defines an Internal class for tracking and manipulating products*/
        
        int add(ProductDef*);
        /*add only products with unique ids, return 0 if id already exists.*/
        
        int remove(string id);
        int size();
        ProductDef* find(string productid);/*null pointer returned if not found*/
        
        map<string,int> composites();
        /*id, and count of component composing product for all composites*/

        void sortById();
        void sortByCompCount();/*sort by component Count*/

        private:
        map<string,Product*> tbl;
    };

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
    int addComponent(string id, int num);
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

    void deleteComponent(string id);
    void clearComponents();

    /* set properties */
    void name(string _name);
    void price (double px);
    void cost(double px){cpx=px>0?px:0;}

    private:

     void next();
    /*increment internal pointer to point to next component. 
    if currentComponent before next() was last item in list, eof()is set to true
    test for eof every after next()*/

    static Table table;
    /*class global variable: for table tracking all created productDefs accessed with table()*/
    
    string product_name, _id;
    int is_compound;
    double px, cpx;

    map<string,int> comps;/*id, count*/

    /* optimisations additions on 7 dec*/
    int units_purchased;
    int units_sold;
    int units_damaged;
    int units_returned_out;
    int units_returned_in;
};


struct LineItem {
  string item;
  int count;
  double attr1;/*currently used for rate*/
  double attr2;/*currently used for amount*/

};
//typedef vector<Component> componentVector;

 #endif