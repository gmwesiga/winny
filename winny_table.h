#pragma once
#ifndef id10929D5A_9303_4F37_AF348C5B82D8BAD7
#define id10929D5A_9303_4F37_AF348C5B82D8BAD7

#include "wgt_spreadsheet.h"
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>
#include <string>
#include <vector>
#include "winny_theme.h"

class winny_table : public Fl_Table
{
private:
  datasheet *_sheet;
  
public:
  winny_table(int x, int y, int w, int h, const char* l=0):Fl_Table(x,y,w,h,l)
  {
    //box(WINNY_THIN_BORDERFRAME);
    color(DOMWGT_COLOR());
    //more style code here
    _sheet = NULL;
    printf("constructor done..\n");
  }
  
  void sheet(datasheet* o) {_sheet = o; rows(o->rows()); cols(o->cols());}
  datasheet* sheet(){return _sheet;}
  
  //int handle(int e)
  //{
  
    //TableContext cxt;
    //int ret =    Fl_Table::handle(e);
    //ResizeFlag   rf ;
    //int          R,C;
    //int          previous_srow; 

    //switch(e)
    //{
      //case FL_MOVE:
        //cxt = cursor2rowcol(R,C,rf);
        //// if( (R==select_row ||R==current_row)) {return 1;}
        
        //// //if select_row or current_row are negative, set them to 0
        //// select_row = select_row<0?0:select_row;
        //// current_row = current_row<0?0:current_row;
        
        //// previous_srow = select_row;
        //// select_row = R;
        //// //if(select_row>=previous_srow){redraw_range(previous_srow,select_row,0,cols()-1);}
        //// //if(select_row<=previous_srow){redraw_range(select_row,previous_srow,0,cols()-1);}
        //// //redraw(); //to do: find out why redraw code above, which should be optimal flickers and leaves part of table undrawn
        //// return 1;
       
       //case FL_LEAVE: select_row=-1;  //hide   
       //case FL_PUSH: take_focus();
       //case FL_KEYDOWN:
           //redraw();
           //return 1;
           
      //default: 
        //return ret; 
    //}
    
  //}
  
  
  void draw_cstr_(char *cstr_, formatter *_style, int X, int Y, int W, int H )
  {
    printf("drawing string..\n");
    //fl_draw_box  (_style->box(), X,Y,W,H,  _style->back_color());
    //fl_color     (_style->font_color());
    //fl_font      (_style->font(), _style->font_size());
    //fl_draw      (cstr_,X,W,W,H,FL_ALIGN_RIGHT);
    printf("done drawing string..\n");
  }
  
  void draw_money(Cell *cell, int X, int Y, int W, int H )
  {
    char as_str[250];
    sprintf(as_str,"%f",cell->value()->float_num);
    draw_cstr_(as_str, cell->style(), X,Y,W,H);
    
  }
  
  
  void draw_int(Cell *cell, int X, int Y, int W, int H )
  {
    
    char as_str[250];
    sprintf(as_str,"%d",cell->value()->int_num);
    printf("in draw_int: val is %s\n", as_str);
    draw_cstr_(as_str, cell->style(), X,Y,W,H);
    
  }
  
  
  void draw_string(Cell *cell, int X, int Y, int W, int H) 
    {  draw_cstr_(cell->value()->str, cell->style(), X,Y,W,H);}
  
  
  void draw_widget(Cell *cell, int X, int y, int W, int H)
    {  return; /*fltk handles drawing the widgets*/  }
    
    
  
  void draw_cell(TableContext context, int R=0, int C=0, int X=0, int Y=0, int W=0, int H=0) override
    { 

      if(!_sheet)return;                                     //return if we don't have data, its useless to draw, 
                                                              //to do:
                                                              //also check for row and col headers.
                                                              printf("in draw row(%d), col(%d)\n", R, C);//return;
      Cell *rc_cell = _sheet->cell(R,C);
      formatter *rc_style = _sheet->cell(R,C)->style();
      
      int border_color                = DOMWGT_COLOR();      
      Fl_Align alignment              = C==T_VALUE? FL_ALIGN_RIGHT:FL_ALIGN_LEFT;
      
      switch (context)
      {
        case CONTEXT_CELL:
          //return;
          if(R==current_row)                                     //if cell is in a selected row
          {  rc_cell->style()->back_color( SELECTION_BACKCOLOR()); // set its back_color to selection color
             border_color = SELECTION_BORDERCOLOR();             // and its border_color to selection border color
          }
          
          else if(R==select_row)                                 //if cell is in a row under the mouse
          {  rc_cell->style()->back_color(SELECTION_BACKCOLOR2());  // set its back_color to hover color
             border_color = SELECTION_BORDERCOLOR();             // and its border_color to border hover color
          }
          
          fl_push_clip(X,Y,W,H);
          
          switch (rc_cell->type())                               //check the the datatype of the matching cell in the datasheet
          {
            case WINNY_MONEY: draw_money(rc_cell,X,Y,W,H); break; 
            case WINNY_NUMBER: draw_int(rc_cell,X,Y,W,H);  break;
            case WINNY_CSTR: draw_string(rc_cell, X,Y,W,H); break;
            //etc  
          } 
          
          //draw borders
          fl_color(border_color);
          fl_line(X,Y, X+W, Y);                       //draw top border
          fl_line(X,Y+H-1, X+W, Y+H-1);               //draw bottom border -1 last pixal disappears
          {                                           //this section is put in braces to create
            int first_col = 0;                        //local scope, otherwise compiler rejects these declarations
            int last_col = cols();
            if(C==first_col)
              { fl_line(X,Y,X,Y+H); }                 // draw left border
            if(C==last_col)
              { fl_line(X+W-1,Y,X+W-1,Y+H); }             //draw right border. if you don't less 1 pix, border is covered by next drawing
          }
          fl_pop_clip();
          return;
          
        case CONTEXT_COL_HEADER:
          //return;
          fl_color(DOMWGT_COLOR());                        //set background to white
          fl_font(FL_HELVETICA,DOMFONT_SIZE());         //set fontface and size
          fl_push_clip(X,Y,W,H);
          fl_rectf(X,Y,W,H);
          fl_color(FONT_COLOR_DOM());                        //set text color to black
          //fl_draw(col_title(C).c_str(), X+10, Y, W-20, H, alignment);
          fl_pop_clip();
      }
    }
    
    
};




#endif // header
