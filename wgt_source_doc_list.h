#ifndef wgt_source_doc_h
#define wgt_source_doc_h
//output widget.
//takes a reference or pointer to a list of source_document 
//displays a list of source_documents on the screen
//allows user to choose/ select any of the source_documents
// selected() returns index of selected document
// g++  wgt_translist_tst.cxx -otable  -I/local/include/ -L/local/lib/ -lfltk -lole32 -luuid -lcomctl32 -lgdi32 -std=gnu++11

#include "source_documents.h"
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>
#include <string>
#include <vector>
#include "winny_theme.h"
//strings:

using std::string;
using std::vector;

static const struct
{string title;  int col_width;} TITLES[6] = 
{{"Document",      100}, 
 {"Client Name",   150},
  {"No.",          50},
  {"Date",         150},
  {"Status",       50}, 
  {"Amount",       100} 
}; //using table to avoid switch

static const int MAX_COLS =6;

static const int 
DOC_TYPE     =0, 
CLIENT_NAME  =1, 
T_NO         =2, 
T_DATE       =3,
T_STATUS     =4, 
T_VALUE      =5;

class source_doc_list : public Fl_Table
{
  public:
    //constructor
    source_doc_list(int x, int y, int w, int h, const char* L=0)
      :Fl_Table(x, y, w, h,L),doc_selected(0),data_(0)
      {
          color(WGT_COLOR_DOM());
          cols(MAX_COLS);
          rows(0);
          col_header(1);
          col_resize(1);
          for(int i=0; i<MAX_COLS; ++i)
            col_width(i,TITLES[i].col_width);
          
          end();
      }
    
	void refresh()
	{
		if(data_) 
        { 
          rows(data_->size());
          redraw();
        }  
	}
	
    void data_source(vector<source_document*> * data )
      { if(data) 
        { data_ = data;
          rows(data->size());
          redraw();
        }  
      }

      
    vector<source_document*> * data_source()
      { return data_; }

	  
	int selected()
	{return current_row>0&&current_row<data_->size() ?
		current_row :0; 
	}
      
    void draw_cell(TableContext context, int R=0, int C=0, int X=0, int Y=0, int W=0, int H=0) override
    {
   
      const int NORMAL_FSIZE          = DOMFONT_SIZE();
      const int FOCUSROW_BACKCOLOR    = FL_BLUE;     //Mouse focus
      const int CURRENTROW_BACKCOLOR  = FL_LIGHT1;
      const int NORMAL_BACKCOLOR      = DOMWGT_COLOR();
      int backcolor                   = NORMAL_BACKCOLOR;
      int border_color                = DOMWGT_COLOR();      
      Fl_Align alignment              = C==T_VALUE? FL_ALIGN_RIGHT:FL_ALIGN_LEFT;
      
      switch (context)
      {
        case CONTEXT_CELL:
          //return;
          if(R==current_row)
          {  backcolor    = SELECTION_BACKCOLOR();
             border_color = SELECTION_BORDERCOLOR();
          }
          
          else if(R==select_row)
          {  backcolor    = SELECTION_BACKCOLOR2();
             border_color = SELECTION_BORDERCOLOR();
          }
          
          fl_color(backcolor);                        //white background
          fl_font(FL_HELVETICA,NORMAL_FSIZE);         //prepare to draw text
          fl_push_clip(X,Y,W,H);
          fl_rectf(X,Y,W,H);
          fl_color(C==DOC_TYPE?FL_BLACK:DOMFONT_COLOR());                        //text color is black
          fl_draw( doc_property(R,C).c_str(), X+10, Y,W-20, H, alignment);//-10 creates a small margin on the left -20 on the right
          
          //draw borders
          fl_color(border_color);
          fl_line(X,Y, X+W, Y);                       //top border
          fl_line(X,Y+H-1, X+W, Y+H-1);               //bottom border -1 last pixal disappears
          {                                           //this section is put in braces to create
            int first_col = 0;                        //local scope, otherwise compiler rejects these declarations
            int last_col = cols();
            if(C==first_col)
              { fl_line(X,Y,X,Y+H); }                 // left border
            if(C==last_col)
              { fl_line(X+W-1,Y,X+W-1,Y+H); }             //right border if you don't less 1 pix, border is covered by next drawing
          }
          fl_pop_clip();
          return;
          
        case CONTEXT_COL_HEADER:
          //return;
          fl_color(backcolor);                        //white background
          fl_font(FL_HELVETICA,NORMAL_FSIZE);         //prepare to draw text
          fl_push_clip(X,Y,W,H);
          fl_rectf(X,Y,W,H);
          fl_color(FONT_COLOR_DOM());                        //text color is black
          fl_draw(col_title(C).c_str(), X+10, Y, W-20, H, alignment);
          fl_pop_clip();
      }
    }

    
    int handle(int e)
    {
    
      TableContext cxt;
      int ret =    Fl_Table::handle(e);
      ResizeFlag   rf ;
      int          R,C;
      int          previous_srow; 
      switch(e)
		{
		  case FL_MOVE:
			cxt = cursor2rowcol(R,C,rf);
			if(R==select_row ||R==current_row) {return 1;}
			previous_srow = select_row;
			select_row = R;
			if(select_row>=previous_srow){redraw_range(previous_srow,select_row,0,cols()-1);}
			if(select_row<=previous_srow){redraw_range(select_row,previous_srow,0,cols()-1);}
			//redraw(); //to do: find out why redraw code above, which should be optimal flickers and leaves part of table undrawn
			return 1;
		   
		   case FL_LEAVE: select_row=-1; //hide   
		   case FL_PUSH: take_focus();
		   case FL_KEYDOWN:
			   redraw();
			   return 1;
			   
		  default: 
			return ret;
		}
      
      // switch(e)
      // {
        // case FL_MOVE:
        // case FL_PUSH:
        // case FL_KEYDOWN:
          // redraw();
          // return 1;
      // }
    }
    
    private:
     vector <source_document*> *data_;
     int doc_selected;
     const string DEFAULT_STRING = " ";
     


     string doc_property(int row=0, int col=0)
     {
       if(!data_ || !data_->size()) 
         return DEFAULT_STRING;
       
       int property = col;
       switch (property)
       {
         case DOC_TYPE:
            return (*data_)[row]->doc_type();
            
         case CLIENT_NAME:
            return (*data_)[row]->client_name();
            
         case T_DATE:
           {char s_time[50];
            std::tm transaction_date_ = (*data_)[row]->transaction_date();
            std::strftime(s_time,sizeof(s_time),"%d/%b/%Y %I:%M%p",&transaction_date_);
            return s_time;
           }  
         case T_VALUE:
          {char value[20];
           sprintf(value,"%15.2f",(*data_)[row]->value());
           return value;
          }
          
         default:
            return DEFAULT_STRING;
       }//end switch
     }//end func
     

     string col_title(int C)
     {
       if(C<MAX_COLS)
        return TITLES[C].title;
     }
};//end class


#endif
