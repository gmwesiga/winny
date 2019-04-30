/* handle class */

class product;
struct product_desc;

struct database{
  
  database();
  
  /*connect to db manager get handle */
  bool open(string user_name, string password);
  void close();
  
  /*construct our databases if not exists */
  bool build_database();
  
  
  /*products file*/
  add_product(product& p);
  find_product(product_desc& desc, vector<product>& result);
  int count_products();
  void remove_product(product& p);
  void remove_product(product_desc&)
  
  
};

struct product_desc {
  void name(string s);
  void price(double p);
  void is_compound(bool b);
  
}