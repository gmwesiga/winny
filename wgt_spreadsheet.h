#pragma once
#ifndef id38D882B7_52D9_4EEB_A7CBEAFA28692654
#define id38D882B7_52D9_4EEB_A7CBEAFA28692654

/**
  wgt_spreadsheet
  is really just a more more frexible easily reusable table
  its goal is to be a table control that doesnt need furthur 
  subclassing just to control its drawing. it can draw anything
  anywhere.
  here is generally what it does.
  its made up of 3 main classes.
    1. view,
    2. datasheet
    3. cell.
  the idear is that the view displays the datasheet. the datasheet
  is a generic collection of cells in a list or matrix form.
  a cell can have any value which is drawn by the view at its position on the screen
  
  so generally to use it, you create a view, then create a datasheet and populate it with 
  data after, attach it to the view and call draw on the view!
  
*/
#include <FL/Enumerations.H>
#include "winny_theme.h"
#include <vector>
#include <string>
using std::vector;


enum cell_type {WINNY_MONEY, WINNY_NUMBER, WINNY_RATIO, WINNY_CSTR, WINNY_IMAGE, WINNY_WGT};

union cell_value
{
  char         *str;
  double       float_num;
  int          int_num;
 // Fl_Widget    *wgt;
};


struct formatter
{ 
  private:
  Fl_Boxtype _box;
  Fl_Color   _color;
  Fl_Font    _font;
  int        _font_size;
  Fl_Color   _font_color;
  //To do: add bold, and italics
  
  public:
  //CONST
  formatter(){
    _box = WINNY_THIN_BORDERBOX;
    _color = DOMWGT_COLOR();
    _font = FL_HELVETICA;
    _font_size = 12;
    _font_color = DOMFONT_COLOR();
  }
  
  void box(Fl_Boxtype b)      { _box = b; }
  Fl_Boxtype box()            {return _box; }
  
  void back_color(Fl_Color c) {_color = c;}
  Fl_Color back_color()       {return _color;}
  
  void font(Fl_Font f)        {_font = f; }
  Fl_Font font()              {return _font; }
  
  int font_size()             {return _font_size; }
  void font_size(int s)       {_font_size = s; }
  
  void font_color(Fl_Color c) {_font_color = c; }
  Fl_Color font_color()       {return _font_color;}
  
};

//const cell_value DEF_CVAL = {0};
struct Cell
{
  //private:
  int R;
  int C;
  cell_type t;  //this type is like a variant type in other languages.
  cell_value val;
  formatter  *sty;
  //public:
  bool show;           //show or hide this cell
  
  // Cell(int r, int c, cell_value v, cell_type t)
    // :R(r),C(c), val(v),t(t),sty(NULL), show(true){}
    
   Cell():R(0),C(0)
   {
    t=WINNY_CSTR;
    val.str="";
    sty = NULL;
    show=true;
  }
    
   formatter *style(){return sty;};
  
   void style(formatter *s){sty=s;}
  
  // void value(cell_value v){val = v;}
  
  // cell_value value(){return val;}
  
   cell_value *value(){return &val;}
  
   cell_type type(){return t;}
  
   void type(cell_type tt){t=tt;}
  
};


// string cell2string(Cell* c)
// {
  
// }


struct datasheet
{
private:
  int                    _rows;
  int                    _cols;
  bool                   cheaders_on;
  bool                   rheaders_on;
  formatter              _style;  //data cell styles
  formatter              _header_style; 
  vector< vector<Cell*> > data;
  vector <Cell*>         rheaders;
  vector <Cell*>         cheaders;
  Cell                  *def_Cell; //default Cell;   
  Cell                  *def_header;
  
  public:
  
  datasheet(int rows, int cols, bool col_headers=false, bool row_headers=false )
  /* constructs a datasheet with rows and cols, 
    if col/row_headers are enabled, the headers are shown,
    you can provide the headers using the row_headers() and col_headers() later
    otherwise, default headers (1, 2,3 ) are drawn
  */
  :_rows(rows),_cols(cols),cheaders_on(col_headers), rheaders_on(row_headers)
  {
    def_Cell = new Cell();
    def_Cell->style( &_style);

    if(rows<1) return;//optimisation. no meaning if we have not atleast one row.
    if(cols<1) return;
    data.resize(rows);
    for(int r=0; r<rows; ++r)
      for(int c=0; c<cols; ++c)
        data[r].push_back(def_Cell);
    
    _header_style.back_color(MENUBAR_COLOR());
    def_header = new Cell();
    def_header->style (&_header_style);
  }
  
  
  
  Cell* cell(int R, int C)   /* reterns a pointer to cell at row r, col c, used to edit  datasheet*/ 
  {
    if(R<=-1) return def_Cell;
    if(C<=-1) return def_Cell;
    
    if(R<_rows && C<_cols)
      return data[R][C];
    return def_Cell;  //hopefull never reached
  }
  
  void cell(int R, int C, Cell* c)   
  {
    if(R<=-1) return ;
    if(C<=-1) return ;
    
    if(R<_rows && C<_cols)
    {
      Cell * cc = new Cell;
      *cc= *c;
      (data[R][C])=cc;
    }    //
    return ;  //hopefull never reached
  }

  
  formatter*
  style(){return &_style;}/*returns address of style object for this datasheet. use it to edit styles for the datasheet*/
   
  void style(formatter *s)
  {
    _style = *s;
    for (int row=0; row<_rows; ++row)
      for (int col=0; col< _cols; ++col)
        (data[row][col])->style(&_style);   //update stylesheet
  }
  
 
 
  Cell *col_header(int C)
  {
    if(!cheaders.size()||C>=_cols)
    { 
      def_header->type(WINNY_NUMBER);
      def_header->value()->int_num = C;
      return def_header;
    }
    return cheaders[C];
  }
  
  
  
 Cell *row_header(int C)
  {
    if(!rheaders.size()||C>=_rows)
    {
      def_header->type(WINNY_NUMBER);
      def_header->value()->int_num = C;
      return def_header;
    }
    return rheaders[C];
  }
  
 int rows() {return _rows;}
 
 int cols() {return _cols;}
  
};

#endif // header
