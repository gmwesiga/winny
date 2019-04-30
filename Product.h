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
 #endif