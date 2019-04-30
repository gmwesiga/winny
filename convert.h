#ifndef CONVERT_H
#define CONVERT_H

namespace Convert{
    static char* _cstring_ =0;

    //converts afloat to int and stores it in cstring
    inline char* doubleToCstr(double num)
    {
        if(_cstring_)delete[]_cstring_; //not optimum 
        char* _cstring_ = new char[20];
        sprintf(_cstring_,"%15.2f",num);
        return _cstring_;
    };

    inline char* intToCstr(int num)
    {
        if(_cstring_)delete[]_cstring_; //not optimum 
        char* _cstring_ = new char[20];
        sprintf(_cstring_,"%d",num);
        return _cstring_;
    };

};

#endif