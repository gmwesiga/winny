#include <iostream>
#include <ProductDef.H>

using namespace std;

template<class i>
void x2(i b, i e){
    while(b!=e){
        (*b)*=2;
        b++;
    }
};

int main(){
 ProductDef* p;
 string id("Id00");
 int count(1);
try{
 //for(int i=1; i<count; i++)
    p = new ProductDef(id, id);
}catch(string e){
    cout<<e;
    return 0;
};
return 0;
for(ProductDef::table.begin();!ProductDef::table.eof();){
    p= ProductDef::table.getElement();
    cout<<"id "<<p->name()<<endl;
}

}