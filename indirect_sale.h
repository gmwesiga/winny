
struct indirect_sale
{
  void add_loadout_list(vector<load_item> list);
  void add_loadin_list(vector<load_item> list);
  
  vector<load_item> items_sold()
  void product_table(Product_Table & table); // set product table to use for calculating sells
  Product_Table & product_table();// get reference of current product table
  void calculate_sales(Product_Table& table=0);
  double value();
  
  
  private:
    vector<load_item> out;
    vector<load_item>in;
    vector<load_item>sales;
    Product_Table & tbl;   //depends on product table;
    bool data_changed;
  
};


///////////////////////////////////////////////////////////
void indirect_sale::add_loadin_list(vector<load_item> list)
{
  in = list;
  data_changed = 1;
}


////////////////////////////////////////////////////////////
void indirect_sale::add_loadout_list(vector<load_item> list)
{
  out = list;
  data_changed = 1;
}


//////////////////////////////////////////////////////////
vector<load_item> indirect_sale::items_sold()
{
  return sales;
}


/////////////////////////////////////////////////////////
void indirect_sale::product_table(Product_Table& table)
{
  tbl = table;
}


Product_Table::indirect_sale::product_table()
{
  return tbl;
}