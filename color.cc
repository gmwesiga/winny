#include "gmdataset.h"

col::col(int r, int g, int b)
 {
     R = r>255||r<0?0:r;
     G = g>255||g<0?0:g;
     B = b>255||b<0?0:b;
 } 

void col::red(int r){R = r>255||r<0?0:r;};
void col::green(int g){G = g>255||g<0?0:g;};
void col::blue(int b){B = b>255||b<0?0:b;};
const int& col::red()const{return R;};
const int& col::blue()const{return B;};
const int& col::green()const{return G;};
int& col::red(){return R;};
int& col::blue(){return B;};
int& col::green(){return G;};

