#include "gmdataset.h"
#include <cstdio>

//constructor
dataset::dataset(int rows=0, int columns=0, styling* s)
:r(_check_rc(rows)),c(_check_rc(columns)),
_data(r,vector<table_data>(c,"")),
_cheaders(c, ""),_rheaders(r,"")
{
    //to do: initialise style with user provided parameter
    publishing =1;

    if(s){
        mydef.style(*s);
        for(int i=0; i<r; i++ ){
             _rheaders[i].style(*s);
            for(int j=0; j<c; j++){
                _data[i][j].style(*s);
                if(r)continue;
                _cheaders[j].style(*s);
            }
        }
    }
};

//calls handler functions registered by any subscribers to change events 
//passing instance
void dataset::call_listeners()
{
    //if publishing is off, don't call
    if(!publishing) return; 
    for(int i=0; i<viewers.size();++i)
        if(viewers[i].handler) //don't call null pointer'
            viewers[i].handler(this, viewers[i].data);
};

void dataset::pause_events(){
//turn of event publication
    publishing = 0; 
};

void dataset::resume_events(){
    //resume event publication  
    publishing = 1;
};

int dataset::is_publishing_events(){
    return publishing;
};


//unsubscribes handler from recieving change events.
void dataset::remove_listener(dataset_handler w)
{
    for(int i=0;i<viewers.size(); ++i)
        if(w==viewers[i].handler) 
            viewers.erase(viewers.begin()+i); //remove it
};


void dataset::add_listener(dataset_handler w,void* vdata)
// registers callback function of any event subscriber 
{
    if(w)viewers.push_back({w,vdata});
};


void dataset::data(int R, int C, table_data d)
//sets data on cell R, C
{
    if(R<r && C<c) _data[R][C] = d;
    call_listeners();
};


table_data& dataset::data(int R, int C)
//access element or return default object`
{
    if(R<r && C<c) return _data[R][C];
    return mydef;
};

const table_data& dataset::data(int R, int C) const
//access element or return default object const verson
{
    if(R<r&&C<c) return _data[R][C];
    return mydef;
};

void dataset::set_row_header(int row, table_data header)
//
{
    // if row is not existing, do nothing
    if(row<0 || row>_rheaders.size()) return;
    //otherwise, set it 
    _rheaders[row] = header;
    call_listeners();
};

void dataset::set_col_header(int row, table_data header)
//
{
    // if row is not existing, do nothing
    if(row<0 || row>_cheaders.size()) return;
    //otherwise, set it 
    _cheaders[row] = header;
    call_listeners();
};


const table_data& dataset::col_header(int C)const
//access element or return default object`
{
    if(C<_cheaders.size()) return _cheaders[C];
    return mydef;
};

table_data& dataset::col_header(int C)
//access element or return default object`
{
    if(C<_cheaders.size()) return _cheaders[C];
    return mydef;
};

void dataset::set_rows(int num)
{//resizes the rows
    //printf("in setrows");
    if(num>0){
        _data.resize(num,vector<table_data>(c,mydef));
        _rheaders.resize(num,mydef );
        r=num;
        call_listeners();
    }
    //printf("out of set_rows");
};

void dataset::set_cols(int num)
{//resizes the rows
    if (num>0){
        for(unsigned int i=0; i<_data.size(); ++i){
            _data[i].resize(num, mydef);
        }
        _cheaders.resize(num, mydef);
        c=num;
        call_listeners();
    }
};

const table_data& dataset::row_header(int R)const
//access element or return default object`
{
    if(R<_rheaders.size()) return _rheaders[R];
    return mydef;
};

table_data& dataset::row_header(int R)
//access element or return default object`
{
    if(R<_rheaders.size()) return _rheaders[R];
    return mydef;
};