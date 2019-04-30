#ifndef LOAD_ITEM_H
#define LOAD_ITEM_H

#include <string>
struct load_item{
  public:
  //load_item(args)
  load_item(Product itm, int qty)
    :_rate{itm.price()}, q{qty}, product{itm.name()}
    {};

  //load_item()  
  load_item():_rate{0},q{0},product{""}{};

  //load_item(Component)
  load_item(Component c):_rate(c.cost_px),q(c.count),product(c.product_name){};

  //item(Product)
  void item(Product itm){
      product = itm.name();
      _rate = itm.price();
  };

  //item()get
  string item(){
      return product;
  };

  void item(string s){product = s;};

   //qty(int) 
  void qty(int num){
      q=num;
  }

  //qty()get
  int qty(){return q;};

  //rate()
  double rate(){return _rate;};

  //rate(double)
  void rate(double r){_rate = r;}

  //amount()
  double amount(){return _rate * q;};

      private:
      double _rate;
      int q;
      string product;

};

typedef load_item tLineItem;
//Type Name of Array of LoadItems
typedef vector<load_item> tLineItemVector;
#endif