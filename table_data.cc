#include "gmdataset.h"
//#include <cstdio>

using std::strlen;
using std::strcpy;

//default style:
static styling defaultStyle = {

    wcolor(0, 0, 0),
    wcolor(249, 249, 249),
    wcolor(243, 243, 243),
    0
};


variable::variable():_type(NUMBER), _style(defaultStyle) {};       

//constuct with int
variable::variable( wnumber i){
    _number = i;
    _type = NUMBER;
    style(defaultStyle);
};

//construct with string
variable::variable(const char* c){
    _cstring = new char[strlen(c)+1];
    strcpy(_cstring, c);
    _type = CSTRING;
    style(defaultStyle);
    //printf("table_data const :%s->%s\n",c,cstring());
};

//copy constructor
variable::variable(const variable& v){
    if(v.type()==CSTRING){
        _cstring = new char[strlen(v.cstring())+1];
        strcpy(_cstring, v._cstring);
        _type = CSTRING;
        _style = v._style;
    }
    if(v.type()==NUMBER){
        _number = v._number;
        _type = NUMBER;
        _style = v._style;
    }

    if(v.type()==OBJECT){
        _object = _object; //shallow copy. 
        _type = OBJECT;
        _style = v._style;
    }
}

variable& variable::operator=(const variable& other){
    if (this != &other)  
      {  
        //free existing
        if(_type==CSTRING && _cstring){delete[]_cstring; _cstring = 0;}
        
        if(other.type()==CSTRING){
            _cstring = new char[strlen(other.cstring())+1];
            strcpy(_cstring, other.cstring());
            _type = CSTRING;
            _style = other._style;
        }  
        //numbers
        if(other.type()==NUMBER){
            _number = other._number;
            _type = NUMBER;
           _style = other._style;
         }

         //objects eg Images controls etc.
         if(other.type()==OBJECT){
             _object = other._object;
             _type = OBJECT;
             _style = other._style;  
            //std::printf("variable::operator=(Object:%p:%p)..done\n",other.object(),_object);
         }
      }  
      return *this;  
}

//not implemented should be for image data
variable::variable(Object* v){
    _type = OBJECT;
    _object = v; //point to it, don't copy
    style(defaultStyle);
};

//destructor. free memory
variable::~variable(){
    if (_cstring) delete[] _cstring;
}

// returns string previosly stored with cstring()
const char* variable::cstring()const{
    if (_type==CSTRING) return _cstring;
    return 0;
};
char* variable::cstring(){
    if (_type==CSTRING) return _cstring;
    return 0;
};


//sets string type. not copies and keeps own copy
void variable::cstring(const char* c){
    if(_cstring)delete[]_cstring; //don't leak'

    _cstring = new char[strlen(c)+1];
    strcpy(_cstring, c);
    _type = CSTRING;  
    //keep default style       
};

//gets numeric type previously stored
static wnumber err_ = -1;
const wnumber& variable::number()const{
    if(_type==NUMBER) return _number;
    else return err_;
};

wnumber& variable::number(){
    if(_type==NUMBER) return _number;
    else return err_;
};

//sets numeric type
void variable::number(wnumber num){
    if(_type ==CSTRING && _cstring)delete[]_cstring;
    _number = num;
    _type = NUMBER;
    //keep old style;
};

//image api not implemented
const Object* variable::object()const {
    if(_type==OBJECT)return _object;
    else return 0;};

//image api not implemented
 Object* variable::object() {
    if(_type==OBJECT)return _object;
    else return 0;
 };


void variable::object( Object* o){
     if(_type == CSTRING && _cstring)delete[]_cstring;
    _type = OBJECT;
    _object = o;
    //keep old style
   // std::printf("variable::object(Object:%p:%p)..done\n",o,_object);
    //std::printf("variable::object()%p..done\n",object());
};

//returns type of data currently stored.
const data_kind variable::type()const{
    return _type;
};
data_kind& variable::type(){
    return _type;
};

//returns stylesheet
const styling& variable::style()const{
    return _style;
};

 styling& variable::style(){
    return _style;
};

//sets style to use
void variable::style(const styling&  s){
    _style = s;
};
