#include <iostream>
#include <ProductDef.H>
#include <fstream>
#include <iomanip>
using namespace std;

template<class i>
void x2(i b, i e){
    while(b!=e){
        (*b)*=2;
        b++;
    }
};

ProductDef::Table* open_ftable(string filename){

   std::ifstream in(filename.c_str());
   std::ifstream* input = &in;

  string s; 
  double px, c; 
  ProductDef* p;
  
  while( *input>>s>>px){

    if(s=="x")break;
    p = new ProductDef(s,s);
    p->price(px);

    while (*input>>s>>c){
      if(s=="x")break;//endofRecord, don't add
      p->addElement(s,c);//add
    }
  };

  if(ProductDef::table.size())return &(ProductDef::table);
  return 0;

  //if(input->eof())input->clear(); //prepare for next run;
}


int main(){
 ProductDef* p;
 string id("Id00");
 int count(1);

string foo(id);

try{
 //for(int i=1; i<count; i++)
    open_ftable("productsTable.txt");

}catch(char const* e){
    cout<<e;
    return 0;
};
for(ProductDef::table.begin();!ProductDef::table.eof();){
    p= ProductDef::table.getElement();
    cout<<std::setw(20)<<p->name()<<std::setw(20)<<p->sellingPrice()<<endl;
}/**/
return 0;

}