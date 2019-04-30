#include "records_lib.h"
//#include <stdio.h>
// #include <fstream>

// void print_comp_list(vector<Component> &v){
  // printf("\n size is:%d",v.size());
  // for(int i=0;i<v.size(); ++i){
    // printf("\n<%s:%d>\n",v[i].product_name.c_str(), v[i].count);
  // }
  // printf("done..\n");
// }

int index(vector<Component> r, string comp_name){
  if(!r.size()) return-1;
  int i=0;
  while(i<r.size()){
   if( r[i].product_name==comp_name){return i;};
   ++i;
  }
  return -1;
}


/*constructors */
Product::Product():product_name("un named"),is_compound(0),px(0){
}

Product::Product(string name,double price):product_name(name),is_compound(0),px(price){};

/*information about the product*/
string Product::name(){return product_name;};

bool Product::is_composite(){return is_compound;};

double Product::price(){return px;};


//***************************************************************
void Product::set_name(string s){product_name=s;};


//***************************************************************
void Product::set_price(double d){px=d;return;};


//****************************************************************
int Product::components_count(){return is_compound?comps.size():0;};


//*****************************************************************
void Product::add_component(Component comp){
  //if it is the first component, no need to check, add and return immediately
  if(!is_compound){
    comps.push_back(comp);
    is_compound=!is_compound;
    return;
  }

  /*dont add comp if its already added, */
  int i=0;
  while(i<comps.size()){
    if(comp.product_name==comps[i].product_name){
      //its a duplicate!!;
      comps[i].count =comp.count; //just edit the count, don't add new
      return;
    }
    ++i;
  }
  comps.push_back(comp);
  return ;
};

//****************************************************************
Component Product::component(int i){
  //uncheked
  if( i>=0 && i<comps.size())return comps[i];
  ;//otherwise, out of range access, exit prog
   Component c;
   c.product_name ="Null";
   c.count=0;
   return c; //null product;
}


//*********************************************************************
void Product::clear_components(){comps.clear(); is_compound= is_compound?!is_compound:is_compound;};

