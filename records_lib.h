#ifndef RECLIB_H
#define RECLIB_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "gmdataset.h"

using std::map;
using std::string;
using std::vector;

class Component; //forward declaration
class Product;



class Product{
  
  public:
  /* information about product */
  string name();          //every product has a unique name
  bool is_composite();    /*if true, there must be a matching entry to name in components table*/
  double price();
  double cost_price(){return cpx;};
  double selling_price(){return px;};
  int components_count(); 
  
  /*componets that make up a product*/
  void add_component(Component comp);
  Component component(int index);
  void delete_component(string name);
  void clear_components();

  /* set properties */
  void set_name(string _name);
  void set_price (double px);
  void set_cost(double px){cpx=px>0?px:0;}

  /* constructs*/
  Product();
  Product(string name, double px=0.0);
  Product (string name, double selling_px, double cost_px=0):
    product_name(name), px(selling_px), cpx(cost_px), is_compound(false){};

  private:
  string product_name;
  bool is_compound;
  double px, cpx;
  vector<Component> comps;
  /* optimisations additions on 7 dec*/
  int units_purchased;
  int units_sold;
  int units_damaged;
  int units_returned_out;
  int units_returned_in;
};



/*table structure used internally by Product class*/
class Component {
  public:
  Component():count(0),cost_px(0.0),selling_px(0.0){};
  string product_name;
  double cost_px;
  double selling_px;
  int count;
};
typedef vector<Component> componentVector;

#include "load_item.h"

class Product_Table {
  
  public:
  int add(Product& p);
  int Remove(Product p);
  int size();
  Product find_product(string product_name);
  vector<Component> composite_products();
  Product product(int i);
  vector<Product> *data(){return &products;}
  void sort();
  void sort_size();

  private:
  vector<Product> products;
  void add_product_component(Component c);
};


  //algorithms and subroutines
  vector<Component> pack (Product_Table& table, vector<Component> &t);//pack scalars into composites;
  
  vector<Component> decompose (Product_Table& table, vector<Component> &r);
  
  vector<Component> difference (Product_Table& table, vector<Component> &v1,vector<Component> &v2);
  
  vector<Component> add(Product_Table& table, vector<Component> &v1, vector<Component> &v2);

  int num_of_composites(Product_Table& table, string s, vector<Component> &in);
  
  int scalar_components_count(Product_Table& table, string s); //count scalar products that make up product named s;
  
  vector<Component> product_scalar_components(Product_Table& table, string product_name);
  
  void print_comp_list(vector<Component> &v);
  
  int index(vector<Component> r, string comp_name);
  
  void sort_complist_by_count(vector<Component> &t);
  
  void add_component(vector<Component> &comps,Component comp);
  
  vector<load_item> components_to_loadItems(vector<Component> c);
  
  Product_Table * open_ftable(string);
  
  Component loadItem_to_component(load_item itm);
  
  load_item  component_to_loadItem (Component C);
  
  vector<Component> loadItems_to_components(vector<load_item> loaditems);

  void productTable_to_dataset(Product_Table & tb, dataset& ds);
 #endif