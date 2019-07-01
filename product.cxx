#include <ProductDef.H>
#include <algorithm>
#include <iostream>/*debug with cout*/

ProductDef::Table ProductDef::table = ProductDef::Table();

ProductDef::ProductDef(string id, string name)
/*Constructor creates table and adds it to internal products table for tracking
//destructor deletes table entry*/
:_id(id.c_str()),product_name(name.c_str()),_eof(1)
{
  /*if it doesn't already exist create*/
  if ( (ProductDef::table.find(id))==nullptr){
    ProductDef::table.add(this);
    return;
  }//ok successful
  throw string("Error in ProductDef::ProductDef(string id, string name para Id already exists in table");
};




ProductDef::~ProductDef(){
  ProductDef::table.remove(this->_id);//remove from table
};




string ProductDef::name(){return product_name;};
double ProductDef::price(){return px;};
int ProductDef::count(){return comps.size();};



int ProductDef::isComposite()
/*if true, there must be atleast one entry in components table*/
{
  return comps.size()?1:0;
};




int ProductDef::addElement(string id, int num)
/*id must match a product id in the internal table*/
{
  if(!ProductDef::table.find(id))/*does not exist as a product*/
    return 0;  
  
  /*if its first element, turn off _eof bit
  if(comps.begin()==comps.end()) _eof = 0;*/

  /*add comp. if its already added,
   *just edit the count */
  comps[id]+=num;
  return 1;
};




ProductDef* ProductDef::getElement()
/*returns null pointer if empty or eof()==true*/
{
  if (comps.begin()==comps.end()/*Empty*/ )
   return nullptr;

  if (!_eof){
  
    ProductDef* o = table.find(cursor->first);
    cursor++; 
    if(cursor==comps.end()){/*end of container. will be caught by first if statement*/
      _eof = 1;
    }
    return o;

  }else {/*_eof*/
    return nullptr;
  }
}



/*current component = first component in list*/
void ProductDef::begin(){
  cursor=comps.begin(); 
  /*remain in eof if empty*/
  _eof = comps.begin()!=comps.end()? 0:1;
};




/*Get data of current component selected*/
int ProductDef::ElementCount(){
  return cursor!=comps.end()? cursor->second:0;
};



string ProductDef::ElementId(){
  return cursor!=comps.end()? cursor->first:0;
};




int ProductDef::eof()
/*current component == last component. internal cursor can't move anymore,
call begin()*/
{
  return _eof;
}



void ProductDef::deleteElement(string id){
  auto key = comps.find(id);
  if(key!=comps.end())
    comps.erase(key);
};



void ProductDef::clearElements(){
  comps.clear();
};



/* set properties */
void ProductDef::name(string _name){product_name = _name;};
void ProductDef::price (double p){px = p;}
void ProductDef::cost(double p)  {cpx = p>0?p:0;}


ProductDef::Table::Table(const Table &o){
  tbl = o.tbl;
  _eof =o._eof;
  cursor =o.cursor;
}

int ProductDef::Table::add(ProductDef* o)
/*add only products with unique ids, return 0 if id already exists.*/
{
  if(tbl.find(o->product_name)!=tbl.end())/*aready exists*/
    return 0;
  
  tbl[o->_id]=o;
  return 1;
};        


/*Removes Product of id == id from products table
and frees memory*/
int ProductDef::Table::remove(string id){
  auto o = tbl.find(id);
  if(o!=tbl.end()){
    delete(o->second);
    tbl.erase(o);
    return 1;
  }
  return 0;
};



int ProductDef::Table::size(){
  return tbl.size();
};



ProductDef* ProductDef::Table::find(string productid)
/*null pointer returned if not found*/
{
  auto o = tbl.find(productid);
  if(o!=tbl.end()){
    return o->second;
  }
  return nullptr;
}
        


ProductDef* ProductDef::Table::getElement(){
  
  if (tbl.begin()==tbl.end()/*Empty*/)
   return nullptr;

  if (!_eof){
    ProductDef* o = cursor->second;
    cursor++; 
    if(cursor==tbl.end()){/*end of container. will be caught by first if statement*/
      _eof = 1;
    }
    return o;
  } else{
    return nullptr;
  }

}



void ProductDef::Table::begin(){
  cursor=tbl.begin(); 
  //firstTime = 0;
  /*remain on eof if empty*/
  _eof = tbl.begin()!=tbl.end()? 0:1;
};



int ProductDef::Table::eof(){return _eof;};



//compare by product name
bool cmp(const ProductDef &a, ProductDef &b){
  ProductDef &c = (ProductDef&)a;
  return c.name().compare(b.name())<0?true:false;
};

void ProductDef::Table::sortById(){
  //std::sort(tbl.begin(),tbl.end(),cmp);
  return; //do nothing
};



//compare by components count
bool cmp2(const ProductDef &a, ProductDef &b){
  ProductDef &c = (ProductDef&)a;
  return c.count()>b.count()?true:false;
};
/*sort by component Count large first*/
void ProductDef::Table::sortByCompCount(){
  //std::sort(tbl.begin(),tbl.end(),cmp2);
  return;//do nothing
};
