#include <iostream>
#include <vector>
using std::vector;

void insertion_sort(vector<int> &t){
  if (t.size()<2) return;
  for(int i=1; i<t.size(); ++i){
    int key = i;
    while(t[key]>t[key-1]){
      if(!key)break; //don't go beyound zero index;
      int temp = t[key];
      t[key]=t[key-1];
      t[key-1] = temp;
      --key;
    }
  //print vector
  for(int k=0; k<t.size(); ++k){std::cout<<t[k]<<", ";}
  std::cout<<std::endl;
  }
}

main(){

  vector<int>t;
  int i=0;
  while (i<15){
    t.push_back(i*2);++i;
  }
  insertion_sort(t);
  char c;
  std::cin>>c;
}
