#pragma once
#ifndef _GMDATASET_H
#define _GMDATASET_H

#include <vector>
#include <cstring>
using std::vector;
#include <cstdio>

#define MAX_SIZE  1000

typedef long double wnumber;
struct col {
    col():R(0),G(0),B(0){};
    col(int r, int g, int b);
    void red(int r);
    void green(int g);
    void blue(int b);
    const int& red()const;
    const int& blue()const;
    const int& green()const;
    //non const overloads
    int& red();
    int& blue();
    int& green();

    private:
    int R, G, B;
    };
typedef col wcolor;

typedef struct {
    wcolor forecolor; 
    wcolor backcolor;
    wcolor bordercolor; 
    int    borders;
    } styling;

typedef enum {
    CSTRING,
    IMAGE,
    NUMBER,
    OBJECT,
    EMPTY 
    } data_kind;

class Object{
    public:
    virtual void draw(int x, int y, int w, int h)=0;
};

enum Borders{
    LEFT_BORDER=8,
    TOP_BORDER=4,
    RIGHT_BORDER=2,
    BOTTOM_BORDER=1,
    TOP_BOTTOM_BORDER=5,
    LEFT_RIGHT_BORDER=10
};

struct variable {
    variable();
    variable( wnumber i);
    variable(const char* c);
    variable(Object* v);
    variable(const variable& v);
    variable& operator=(const variable& other);
    ~variable();

    const char* cstring() const;
    void cstring(const char* cst);
    const wnumber& number()const;
    wnumber& number();
    
    void number(wnumber num);
    const Object* object()const;
    void object( Object* img);
    const data_kind type()const;
    data_kind& type();
    
    const styling& style() const;
    void style(const styling& s);

    //non const overloads of accessors
    styling& style();
    char* cstring();
    wnumber nummber();
    Object* object();
    
    private:
    data_kind _type; 
    union { //unonimous union: exports its members
        wnumber _number;
        char* _cstring;
        Object* _object;
    };
    styling _style; 
    };
 typedef variable table_data;   

class dataset; //forward declared so that handler function can be defined
//listerner functions
typedef void(*dataset_handler)(dataset*,void* d);
typedef struct{dataset_handler handler; void* data;} Handlers;


class dataset {
    public:
    //construct
    dataset(int rows, int columns, styling* =0);
    //dataset();
    int _check_rc(int i){return i>MAX_SIZE?MAX_SIZE:i;}
    //adjust or get dimensions / size
    void set_rows(int num);
    void set_cols(int num);
    int rows()const{/*printf("in rows()\n");*/return r;};
    int cols()const{return c;};
    int rows(){return r;};
    int cols(){return c;};

    //lable the header 
    void set_col_header(int col, table_data header);
    void set_row_header(int row, table_data header);
    
    //access or set the data
    void data(int R, int C, table_data d);
    const table_data& col_header(int C)const;
    const table_data& row_header(int R)const;
    const table_data& data(int R, int C)const;
    //non const versions
    table_data& col_header(int C);
    table_data& row_header(int R);
    table_data& data(int R, int C);

    
    //publish
    void add_listener(dataset_handler w, void* vdata=0);
    void remove_listener(dataset_handler w);
    void pause_events();
    void resume_events();
    int is_publishing_events();

    
    void copyfrom(const dataset& other){
    //copies data from other dataset but not listerners
    //not assign it's listerns.
        r = other.r;
        c = other.c;
        _data = other._data;
        _rheaders = other._rheaders;
        _cheaders = other._cheaders;
        sty = other.sty;
        mydef = other.mydef;
        call_listeners();
    };

    private:
    int r, c, publishing;
    vector<Handlers> viewers;
    vector<vector<table_data> > _data;
    vector<table_data> _rheaders;
    vector<table_data> _cheaders;
    styling sty;
    table_data mydef;

    //do callback
    void call_listeners();

};


#endif