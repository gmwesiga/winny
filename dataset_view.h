#pragma once
#ifndef dataset_view_h
#define dataset_view_h

//output widget.
//takes a reference or pointer to a dataset 


#include <FL/Fl_Widget.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>
#include <string>
#include <vector>
#include "winny_theme.h"
#include "gmdataset.h"

using std::string;
using std::vector;
#define ON 1
#define OFF 0

class dataset;
class dataset_view : public Fl_Table
{
  public:
    //constructor
    dataset_view(int x, int y, int w, int h, const char* L=0);    
	  void refresh(){
      redraw();
    };
    
    dataset *get_dataset()const { return data_; }
    void attach_dataset( dataset* d);
    int selected()const{return dsv_select_row;};    
    
    void draw_cell(TableContext context, int R=0, int C=0, int X=0, int Y=0, int W=0, int H=0) override;
    int handle(int e) override;
    void resize(int, int, int, int);

    static void dataview_cb(dataset* d,void* v);
    void col_auto_resize(int);
    int col_auto_resize();
    int col_auto_width(int col);
    //computes the width that will fit the largest data Cell in column col

 private:
     dataset* data_;
     int doc_selected;
     int dsv_select_row;

     //drawing functions 
     int drawRow, drawCol;// save augs R and C of draw_cell to be used by these functions
     int backcolor, border_color, NORMAL_FSIZE, alignment; //used by drawing routines
     
     Fl_Color gridcolor;
     int col_auto_resize_;
     int ow;//old width;

     void draw_grid(int grid, int, int, int, int);
     void draw_borders( int x, int y, int w, int h);
     void draw_data(table_data& dt, int x, int y, int w, int h);
     
     Fl_Color wcolor2flcolor(const wcolor& w)const;     
};//end class


class flObject:public Object{
  public:
    flObject(Fl_Widget* w):_flobject(w){
      w->redraw();
    };
    void draw(int x, int y, int w, int h)
    { 
      if(!_flobject)return;

      _flobject->resize(x,y,w,h);

      Fl_Widget* focused = Fl::focus();
      Fl_Widget* belowMouse = Fl::belowmouse();
      
      _flobject->hide();
      if(!_flobject->visible()){
        _flobject->show();
        focused->take_focus();
        Fl::belowmouse(belowMouse);
      }
      //the following line causes a bug in the program
      //i don't know why? it took me 1 and half days 
      //to find this out' 
      //_flobject->redraw(); 
      
    };

  private:
    Fl_Widget* _flobject;
};

#endif