#ifndef PRODUCT_TABLE_H  
#define PRODUCT_TABLE_H 

#include <string>
#include <vector>

namespace winny_DataServer_link {
  class store_server {
    
    public:
    //recommended interface
    virtual bool create_new_product(Product& p);
    virtual bool remove(string pname);
    virtual int size();
    virtual bool find_product(string product_name, Product& prod);

    virtual vector<Component> get_composite_products();
    virtual bool product(int i, Product& prod);

    virtual ls(string name_pattern, typ)
    virtual vector<Product> &data();
    virtual void sort();
    virtual void sort_size();
  };
};//namespace
#endif