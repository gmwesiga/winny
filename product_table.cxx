#include "records_lib.h"

class Product; //forward declaration

void Product_Table::add_product_component(Component c)
{
  
  for(int i=0; i<products.size();++i){
    if(c.product_name==products[i].name())return;//if its already in table, ok, ignore
  }
  Product p(c.product_name);        //if not already in table,add it
  products.push_back(p);
  return;
};


//*****************************************************************
int Product_Table::add(Product& p){
  
  //if product already there
  for(int i=0; i<products.size();++i){
    
    if(products[i].name()==p.name()){ //identical product already in table? 
  //edit it
      products[i].set_price(p.price());
      
      //edit components replace old components with new ones
      products[i].clear_components();
      for(int c=0; c<p.components_count();++c){
        add_product_component(p.component(c));
        products[i].add_component(p.component(c));
      }
    return products.size();
    }
  }
   
  //if here, its a new product  
    //add the components first
  for(int i=0;i<p.components_count();++i){
    add_product_component(p.component(i));
  };
    //then add the product
  products.push_back(p);
  return products.size();
}


//****************************************************************
int Product_Table::size(){return products.size();};


//*****************************************************************
Product Product_Table::product(int i){
  //to do 
  //add range checking and return null product if true
  return products[i];
}


void Product_Table::sort()
{                                     //insertion sort to sort pairs basing on count
  if (products.size()<2) return;
  for(int i=1; i<products.size(); ++i){
                                      //printf("in sort for\n");
    int key = i;
    while( products[key].name()<products[key-1].name())
    {
      Product temp = products[key];
      products[key]=products[key-1];
      products[key-1] = temp;
      --key;
                                        //printf("in sort out of while key=%d\n", key);
      if(!key)break;                    //don't go beyound zero index;
    }

  }
};

void Product_Table::sort_size()
{                                     //insertion sort to sort pairs basing on count
  if (products.size()<2) return;
  for(int i=1; i<products.size(); ++i){
                                      //printf("in sort for\n");
    int key = i;
    while( products[key].components_count()>products[key-1].components_count())
    {
      Product temp = products[key];
      products[key]=products[key-1];
      products[key-1] = temp;
      --key;
                                        //printf("in sort out of while key=%d\n", key);
      if(!key)break;                    //don't go beyound zero index;
    }

  }
};

//*******************************************************************
Product Product_Table::find_product(string s){
  for(int i=0; i<products.size(); ++i){
    if(products[i].name()==s){ return products[i];}
  }
  return Product("null");
}

//******************************************************************
vector<Component> Product_Table::composite_products()
{
    vector<Component> v;
    for (int i=0;i<products.size();++i)
    {                                           //iterate through the products sequeance
      if(products[i].is_composite()){                    //if product is composite,
        //to do
        Component c;
        c.product_name = products[i].name();                // name of product
        c.cost_px = products[i].price();
        c.count = scalar_components_count(*this, c.product_name); //sum of scalar component products
        v.push_back(c);                                    //add it to result
      }
    }
    sort_complist_by_count(v);
    return v;
}