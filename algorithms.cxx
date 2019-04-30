#include "records_lib.h"
#include "gmdataset.h"

// UTILITY FUNCTIONS//

//fills ds with ds representing tb
void productTable_to_dataset(Product_Table & tb, dataset& ds){
  ds.set_rows(tb.size());
  ds.set_cols(10);
  ds.set_col_header(0,table_data("Product"));
  ds.set_col_header(1,table_data("Type"));
  ds.set_col_header(2,table_data("Price"));
  ds.set_col_header(3,table_data("Opening Stock"));
  ds.set_col_header(4,table_data("Purchases"));
  ds.set_col_header(5,table_data("Return Inwards"));
  ds.set_col_header(6,table_data("Total Stock"));
  ds.set_col_header(7,table_data("Return Outwards"));
  ds.set_col_header(8,table_data("Closing Stock"));
  ds.set_col_header(9,table_data("Sales"));
  for (int i=0; i<tb.size(); ++i){
    ds.data(i,0).cstring(tb.product(i).name().c_str());
    ds.data(i,1).cstring(tb.product(i).is_composite()?"Compound":"Simple");
    ds.data(i,2).number(tb.product(i).price());
    ds.data(i,3).number(1000);
    ds.data(i,4).number(1000);
    ds.data(i,5).number(1000);
    ds.data(i,6).number(1000);
    ds.data(i,7).number(1000);
    ds.data(i,8).number(0);
    ds.data(i,9).number(ds.data(i,2).number()*1000);
  }
}


vector<Component> decompose(Product_Table& table,  vector<Component> &t)
{
    vector<Component>in;
                                        //1 ensure all pairs in t are scalar
                                      //printf("\t building scalar table of inputs...\n");
  for(int i=0; i<t.size(); ++i){
                                        //printf("\t\t building %s:%d\n", t[i].product_name.c_str(),t[i].count);
    Product p = table.find_product(t[i].product_name);
    if(!p.is_composite())              //product is scalar? add it
    {
                                    //  printf("\tdone\n");
      add_component(in,t[i]); continue;

    }

                                          //if here, t[i] is composite
    int ct = t[i].count;                  //what is the count?
    vector<Component> v = product_scalar_components(table, t[i].product_name);
    //add them
    for(int ind=0; ind<v.size(); ++ind){
      v[ind].count*=ct;                  //remember to multiply the count
      add_component(in,v[ind]);
    }
  }
  return in;
}



vector<Component>pack(Product_Table& table, vector<Component> &t)

{
  vector<Component>in = decompose(table, t);
                                                  //2 get table of composites;
  vector<Component> comps = table.composite_products();
  vector<Component> result;            // printf("%d\n",in[1].count);
                                                  //3 begining with the biggest composite, //see if it can be composed from in, and how much
  for(int ix=0; ix<comps.size();++ix)              //if true, less,from t, the value equal to this composite,
  {
    int cnt = num_of_composites(table, comps[ix].product_name, in);
    if(!cnt)continue;                     //nothing can be done, no staff //this commposite could not be delived from "input"

   vector<Component> v = product_scalar_components(table, comps[ix].product_name);

    for(int ind=0;ind<v.size();++ind)
    {
      int i =index(in,v[ind].product_name);         //never call index unless sure!
                                                  //printf("\tindex is:%d\n",i);
      in[i].count-=cnt*v[ind].count;               //remove from input, components equal to this composite pair
                                                  //here,input will be updated, less by product_scalar_components(of this)
    }
    Component c;
    c.product_name = comps[ix].product_name;
    c.count =cnt;
    c.cost_px = comps[ix].cost_px;
    result.push_back(c);
                                                  //repeat with next composite
  }
                                                  //4 finally add and remaining balances...
  for(int indx=0; indx<in.size(); ++indx){
    if(in[indx].count){                       //not zero!!! this was casing nasty bug... initially test was >=1
      result.push_back(in[indx]);
    }
  }
  return result;
}




vector<Component>  product_scalar_components(Product_Table& table, string name)
{
  Product p = table.find_product(name);

  vector<Component> r;
                              //base case;
  if(!p.is_composite()){
    Component c;
    c.product_name = p.name();
    c.cost_px = p.price();
    c.count = 1;
    r.push_back(c);
    return r;
  };
                              //caution recursion
  for(int i =0; i<p.components_count(); ++i){
    string pp=p.component(i).product_name;

    vector<Component> rr;
    rr= product_scalar_components(table, pp);

                              //edit count  //finally combine step
    int m = p.component(i).count;

    for (int rc=0; rc<rr.size();++rc){
      rr[rc].count *= m;
                              //finally combine small solutions
      r.push_back(rr[rc]);
    };

  }
}



int scalar_components_count(Product_Table& table , string s)
// given a composite product s, recursively decompose s's components untill
// the component list is made up of an equivalent list of scalar products according
// to table, then sum the list count
{

    int answer(0);
    //get its scalar components
    vector<Component> v = product_scalar_components(table, s);
    //count them
    for(int i=0; i<v.size(); ++i){
      answer +=v[i].count;
    }
    return answer;
}





int num_of_composites(Product_Table& table, string s, vector<Component> &input)
{                                                       //number of composites of type s that can be created from in;
  map<string, int> in;
  for(int i=0;i<input. size();++i)
  {
    in[input[i].product_name]=input[i].count;
                                                      //printf("%s:%d",input[i].product_name.c_str(),input[i].count);
  }
                                                        //printf("\n\ttesting %s;\n", s.c_str()); //return 0;
  vector<Component> v = product_scalar_components(table, s);   // s is composed of v components
  int result = 0;
  for(int i = 0; i<v.size() ; ++i)
  {                                                     //loop through v
    string ss = v[i].product_name;                    //get component details for later processing
    int count = v[i].count;
                                                    //printf(" \tseaching for %s <%d>...",ss.c_str(),count);
    map<string,int>::iterator it = in.find(ss);       // check if this component is in "input"
    if (it== in.end())
    {                                                  //  printf("\t..not found\n");
      return 0;
    }                      // if not in "input" then, we can never compose s, because "input" lacks some of its components
    if(!in[ss])return 0;                  //no count in input
                                        //printf("found\n");
                                          //otherwise
    int new_ans;
    char required;
    if (!i)
    {                              //if its first component// assume
      required=in[ss]<0?required='n':
      required='p';                       //positives
      result= in[ss]/count;               //this is answer (division saves us repeated subraction) , also, divide,by zero, watch it!
                                        //printf ("\t...answer now is %d\n",result);
    }else
    {
      if(required=='n'&&in[ss]>0||required=='p'&&in[ss]<0)return 0;//dont mix positives with negatives
       new_ans = in[ss]/count;

      if(required=='p')
      {      //positives
        result= result>new_ans? new_ans:result;
      }else
      {                   //negative
        result= result>new_ans? result:new_ans;
      }
                                        //printf ("\t...answer(%d) now is %d\n",in[ss]/count,result);
    }
  }
                                          //printf("\t...%d found\n",result);
  return result;
}




vector<Component> difference(Product_Table& table,  vector<Component> &v1, vector<Component> &v2)
{
  vector<Component> a,b,r;
                                          //printf("in defference..\n");
  a=decompose(table, v1);
  b=decompose(table, v2);

  for(int i=0; i<b.size();++i)
  {                                          //iterate list b
    int idx = index(a,b[i].product_name);//
    if(idx==-1)
    {                           //not in list a   // printf("here......\n");
      b[i].count=0-b[i].count;   //negate  // printf("here......%d\n",b[i].count);
      r.push_back(b[i]);
      continue;
    }
    a[idx].count =a[idx].count - b[i].count;
    r.push_back(a[idx]);
    a[idx].count = 0;//!!!!!
  }

  for(int i=0; i<a.size();++i){
    if(a[i].count)r.push_back(a[i]);
  }
  a.clear();
  a=pack(table,r);

  return a;
}//*****************************************************************


vector<Component> add(Product_Table& table, vector<Component> &v1, vector<Component> &v2)
{
  vector<Component> a,b,r;
                                          //printf("in defference..\n");
  a=decompose(table, v1);
  b=decompose(table, v2);

  for(int i=0; i<b.size();++i)
  {
    int idx = index(a,b[i].product_name);//
    if(idx==-1)
    {                           //not in list a   // printf("here......\n");
      //b[i].count=0-b[i].count;   //negate  // printf("here......%d\n",b[i].count);
      r.push_back(b[i]);
      continue;
    }
    a[idx].count =a[idx].count + b[i].count;
    r.push_back(a[idx]);
    a[idx].count = 0;//!!!!!
  }

  for(int i=0; i<a.size();++i){
    if(a[i].count)r.push_back(a[i]);
  }
  a.clear();
  a=pack(table,r);

  return a;

}


Product_Table * open_ftable(string filename){
                                      //printf("\tformat name<space>price\n\t>>>");
   static Product_Table PRODUCT_TABLE;
   if(PRODUCT_TABLE.size())return &PRODUCT_TABLE;

   std::ifstream in(filename.c_str());
   std::ifstream* input = &in;

  string s; double px;
  while( *input>>s>>px){
    Product p;

    if(s=="x")break;
    p.set_name(s); p.set_price(px);
    //*output<<"\t\tDefine a "<<p.name()<<" \n\t\t format: name<space>count\n\t\tcomponent>>>";

    //add components
    Component c;
    while (*input>>c.product_name>>c.count){
      if(c.product_name=="x")break;
      p.add_component(c);
      //*output<<"\t\t"<<p.name()<<"size: "<<p.components_count()
      //<<"\n\t \tcomponent>>>";
    }
    PRODUCT_TABLE.add(p);

    //print out table
    //*output<<"\tNew table size: "<<table.size()<<"\n";
    //print_table();

     // *output  <<"\n\tproduct>>>";
  };
  if(PRODUCT_TABLE.size())return &PRODUCT_TABLE;
  return 0;

  //if(input->eof())input->clear(); //prepare for next run;
}



void add_component(vector<Component> &comps,Component comp)
{
                                //if it is the first component, no need to check, add and return immediately
  if(!comps.size()){
    comps.push_back(comp);
    return;
  }
                                        /*dont add comp if its already added, */
  int i=0;
  while(i<comps.size()){
    if(comp.product_name==comps[i].product_name){  //its a duplicate!!;
      comps[i].count +=comp.count;                 //just edit the count, don't add new
      return;
    }
    ++i;
  }
  comps.push_back(comp);
  return ;
}




void sort_complist_by_count(vector<Component> &t)
{                                   //insertion sort to sort pairs basing on count
  if (t.size()<2) return;
  for(int i=1; i<t.size(); ++i){
    int key = i;
    while(t[key].count>t[key-1].count){
      Component temp = t[key];
      t[key]=t[key-1];
      t[key-1] = temp;
      --key;
       if(!key)break;          //don't go beyound zero index;
    }
  }
}




Component loadItem_to_component(load_item itm)
{
  Component result;
  result.product_name = itm.item();
  result.cost_px = itm.rate();
  result.count = itm.qty();
  return result;
}



load_item  component_to_loadItem (Component C)
{
  return load_item(C);
}



vector<Component> loadItems_to_components(vector<load_item> loaditems)
{
  vector<Component> ans;
  for(int i=0; i<loaditems.size(); ++i)
  {
    ans.push_back(loadItem_to_component(loaditems[i]));
  }
  return ans;
}



vector<load_item> components_to_loadItems(vector<Component> c)
{
  vector<load_item> ans;
  for(int i=0; i<c.size(); ++i)
  {
    ans.push_back(component_to_loadItem(c[i]));
  }
  return ans;
}
