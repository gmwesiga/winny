#include <iostream>
#include <vector>

using namespace std;

template<class i>
void x2(i b, i e){
    while(b!=e){
        (*b)*=2;
        b++;
    }
};

int main(){
    vector<int> t{1,2,3,4};
    x2(t.begin(),t.end());
    auto o = t.begin();
    while (o!=t.end()){
        cout<<*o<<endl; o++;}
    cout<<"Done";

}