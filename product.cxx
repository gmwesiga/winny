#include <ProductDef.H>


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
ProductDef::ProductDef(string id, string name)
/*Constructor creates table and adds it to internal products table for tracking
//destructor deletes table entry*/
:product_name(name),_id(id)
{
  /*if it doesn't already exist create*/
  if (! ProductDef::table.find(id)){
    ProductDef::table.add(this);
  }
  throw "Error in roductDef::ProductDef(string id, string name para Id already exists in table";
};

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

