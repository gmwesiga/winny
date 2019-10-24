#include "dataset_view.h"
#include "winny_theme.h"
#include <FL/fl_ask.H>
#include <iostream>
//for formating numbers to string
#include <sstream>
//for formating numbers with commas (set_locale)
#include <locale>

using std::cout;
using std::endl;
char* num2string(wnumber num);

dataset_view::dataset_view(int x, int y, int w, int h, const char* L)
:Fl_Table::Fl_Table(x,y,w,h,L), data_(nullptr)
{
    init_ui();
    color(WINDOW_COLOR());
    col_header(ON);
    col_resize(ON);
  NORMAL_FSIZE          = WINNY_NORMALTEXT_FONTSIZE;
  backcolor             = WINDOW_COLOR();
  border_color          = DOMWGT_COLOR();      
  Fl_Align alignment    = FL_ALIGN_LEFT;
  vscrollbar->color(WINNY_BACKGROUND_DOMCOLOR);
  hscrollbar->color(WINNY_BACKGROUND_DOMCOLOR);
  vscrollbar->slider(WINNY_THIN_BORDERFRAME);
  hscrollbar->slider(WINNY_THIN_BORDERFRAME);
  set_winny_scroll_theme(this->table);
  set_selection(0,0,0,0);
  end();
  doc_selected = dsv_select_row =0;
  when(FL_WHEN_CHANGED);

  gridcolor = wcolor2flcolor(wcolor(0,0,94));

  //printf("dataset_view constructor done");
}



void dataset_view::draw_cell(TableContext context, int R, int C, int X, int Y, int W, int H)
{   
    if(!data_)return;
    drawRow = R; drawCol = C;
    gridcolor = wcolor2flcolor(data_->data(R,C).style().bordercolor);
    border_color = gridcolor;
    backcolor = wcolor2flcolor(data_->data(R,C).style().backcolor);
    //printf("Draw=>R:%d, current_row:%d, select_row:%d \n",R,current_row,select_row);

  switch (context)
  {
	case CONTEXT_CELL:
	  if(R==select_row)
	  {  backcolor    = SELECTION_BACKCOLOR();
		 border_color = SELECTION_BORDERCOLOR();
	  }else if(R==dsv_select_row)
	  {  backcolor    = SELECTION_BACKCOLOR2();
		 border_color = SELECTION_BORDERCOLOR();
	  }else{
          backcolor = wcolor2flcolor(data_->data(R,C).style().backcolor);  
      }
	  draw_data(data_->data(R,C),X,Y,W,H);
      draw_grid(data_->data(R,C).style().borders,X,Y,W,H);
      //reset
      backcolor = DOMWGT_COLOR();
      border_color= DOMWGT_COLOR();      
      alignment= FL_ALIGN_LEFT;
	  return;
	  
	case CONTEXT_COL_HEADER:
	  draw_data(data_->col_header(C),X,Y,W,H);
      draw_grid(data_->col_header(C).style().borders,X,Y,W,H);
      //reset
      backcolor             = WINDOW_COLOR();
      border_color          = DOMWGT_COLOR(); 
      return;

    case CONTEXT_ROW_HEADER:
      draw_data(data_->row_header(R),X,Y,W,H);
      draw_grid(data_->row_header(R).style().borders,X,Y,W,H);
      //reset
      backcolor             = WINDOW_COLOR();
      border_color          = DOMWGT_COLOR(); 
      return;
  }

};

void dataset_view::draw_data(table_data& dt, int X, int Y, int W, int H)
{
    //set the backcolor using backcolor of data itself, that way different cells can be given different colors
    fl_color(backcolor);

    //set the font to use and its size
    fl_font(WINNY_NORMALFONT,WINNY_NORMALTEXT_FONTSIZE);         //prepare to draw text
    fl_push_clip(X,Y,W,H);
    
    //for temprory saving current alignment settings
    int al; 

    //for convertining td->number to str
    std::stringstream ss;

    switch(dt.type()){
        case NUMBER:
            //save current align settings 
            al = alignment;

            //align numbers to right side
            alignment= FL_ALIGN_RIGHT;

            //print debug info
           // fl_alert(num2string(dt.number()));
           //cout<<dt.number()<<" : ";fuck
           
            //format number to string, (cast to long)

            //draw it
            ss << (long long)dt.number();
            fl_rectf(X,Y,W,H);
            fl_color(wcolor2flcolor(dt.style().forecolor));                       //text color is black
            fl_draw(ss.str().c_str(), X+10, Y,W-20, H, alignment);//-10 creates a small margin on the left -20 on the right
           
            //reset alignment
            alignment = al;
            break;
        case CSTRING:
            fl_rectf(X,Y,W,H);
            fl_color(wcolor2flcolor(dt.style().forecolor));                       //text color is black
            fl_draw( dt.cstring(), X+10, Y,W-20, H, alignment);//-10 creates a small margin on the left -20 on the right
            break;
        case OBJECT:
            if(dt.object())
                dt.object()->draw(X,Y,W,H);
            break;
        default:
            break;
    }
    fl_pop_clip();
};


//Draws a border around region specified by X,Y,W,H
//to do: factor this out to several functions instead. draw_tborder(...) draw_bborder(...)

void dataset_view::draw_grid( int grid, int X, int Y, int W, int H){
    //draw borders
    
    int thisIsSelectRow(0);
    if(drawRow==dsv_select_row || drawRow==select_row){
        thisIsSelectRow=1;
    }

    fl_color(gridcolor);

    fl_push_clip(X,Y,W,H);
    
    if(thisIsSelectRow || grid & TOP_BORDER ){ 
        if(thisIsSelectRow)
            fl_color(border_color);
        fl_line(X,Y, X+W, Y);                       //top border
    }  
    if(thisIsSelectRow || grid & BOTTOM_BORDER){ 
        if(thisIsSelectRow)
            fl_color(border_color);
        else    
            fl_color(gridcolor);
        fl_line(X,Y+H-1, X+W, Y+H-1); //bottom border -1 last pixal disappears
    }    
    
    fl_color(gridcolor);
    if(grid & LEFT_BORDER) {
        if(thisIsSelectRow)fl_color(backcolor);
        fl_line(X,Y, X, Y+H);
    }
    if(grid & RIGHT_BORDER){
        if(thisIsSelectRow)fl_color(backcolor); 
        fl_line(X+W,Y, X+W, Y+H-1);
    }    
  
  fl_color(border_color);
    if(thisIsSelectRow && !drawCol) //col 0
        fl_line(X,Y,X,Y+H);  // left border
    if(thisIsSelectRow && drawCol==(cols()-1))
        fl_line(X+W-1,Y,X+W-1,Y+H); //right border if you don't less 1 pix, border is covered by next drawing
    
    fl_pop_clip();   
}


//attaches a dataset to the view
void dataset_view::attach_dataset( dataset* d){
    //set cols and rows
    if(!d) return;
    cols(d->cols());
    rows(d->rows());
    set_selection(0,0,0,cols()?cols()-1:0);

    resize(x(),y(),w(),h());
    redraw();
   /*  int W = w()-vscrollbar->w();
    W = W/cols();
    ow=w();
    col_width_all(W);
    col_resize_min(W);
 */


    d->add_listener(& dataview_cb, (void*)this);
    data_ = d;
    for(int c=0; c<cols(); c++){
        col_width(c,col_auto_width(c));
    }
    col_resize_min(20);
    redraw();

};

void dataset_view::dataview_cb(dataset* d, void* v){
    dataset_view * view = (dataset_view*)v;
    view->cols(d->cols());
    view->rows(d->rows());
    view->redraw();
};


int dataset_view::handle(int e){
   
    int psr = select_row>=0?select_row:0;//previous selected row
    Fl_Table::TableContext ctx;
    int R,C; ResizeFlag rf;
    
     if (e == FL_MOVE ){
		ctx = cursor2rowcol(R,C,rf);
        if(ctx!=CONTEXT_CELL)Fl_Table::handle(e); 
		if(R==select_row ||R==current_row) {Fl_Table::handle(e);}
			
        dsv_select_row= R;
        redraw_range(toprow,botrow,0,rightcol);
        return 1;

     } else if (e == FL_PUSH){
        //user wants to select this row and has clicked on it
        //select it, show you have, and docallback

        //we need these values (the row, col )in order to do callback
        ctx = cursor2rowcol(R,C,rf);
        if(ctx!=CONTEXT_CELL)
            //let Table handle scrollbars, and doing the callback
            return Fl_Table::handle(e);; 

        //the dsvrow is now the select row. since mouse has not moved 
        select_row = dsv_select_row;
        redraw_range(toprow,botrow,0,rightcol);
        
        //also give focus to keyboard if even't happened in data area,
        take_focus();

     }

     if(e== FL_KEYDOWN){
         //user is trying to change selection with keys...
         //if its keydown or up, update hover selection (dsv)
         //if he pressed enter, select the current dsv value as the select row

         int flg = 0;//a flag of whether we do callback on enter key. 
                     //if user presses key more than once, do it once only

         //std::cout<<"dsv was "<<dsv_select_row;
         if( Fl::event_key()== FL_Down)
            dsv_select_row = dsv_select_row>=botrow?botrow: ++dsv_select_row;
            
         else if(Fl::event_key()== FL_Up)
            dsv_select_row = dsv_select_row<=toprow?toprow: --dsv_select_row;
        
         else if(Fl::event_key()== FL_Enter){
            flg = dsv_select_row!=select_row?1:0; //do callback only once
            set_selection(dsv_select_row,0,dsv_select_row,rightcol);//select this row
         }

         else 
            //handle all other keys with default behaviour
            return Fl_Table::handle(e);

        redraw_range(toprow,botrow,0,rightcol);
        //std::cout<<"dsv is now "<<dsv_select_row<<"\n";
        //std::cout<<"selectrow  "<<select_row<<"\n";

        if(flg)do_callback(Fl_Table::TableContext::CONTEXT_CELL,select_row,select_col);

        return 1;
        }

    int ret = Fl_Table::handle(e);
    return ret;

};

//converts from api to implementation defined color
Fl_Color dataset_view::wcolor2flcolor(const wcolor& w)const{
    return fl_rgb_color(w.red(),w.green(),w.blue());
};


//static char* _cstring_ =0;
//converts number to int and stores it in cstring

char* num2string(wnumber num){
    
    std::stringstream ss;
    ss<<num;
    //cout <<(char*)(ss.str().c_str());
    return (char*)(ss.str().c_str());
};


void dataset_view::col_auto_resize(int val){
    col_auto_resize_ = val;
};

int dataset_view::col_auto_resize(){
    return col_auto_resize_;
};



int dataset_view::col_auto_width(int col){
    if(!data_)return 0;
    if(col<0|| col>=cols())return 0;
    int w = 0; int tw, th;
    for(int r=0; r<rows(); r++){
        tw =th = 0; //reset
        fl_font(WINNY_NORMALFONT,WINNY_NORMALTEXT_FONTSIZE);
        switch (data_->data(r,col).type())
        {
        case data_kind::NUMBER :
            fl_measure(num2string(data_->data(r,col).number()),tw, th);
            w= tw>w? tw:w;
            break;
        
        case data_kind::CSTRING:
            fl_measure(data_->data(r,col).cstring(),tw,th);
            w=tw>w?tw:w;
            break;
        default://images etc
            break;
        }
    } 
    return w +40;//add 40 pixels allowance
}

void dataset_view::resize(int X, int y, int W, int h){

    if(!col_auto_resize_){
        int W2 = W-(vscrollbar->w()+2);//new width takes into account width of vscroll
         for(int i=0; i<cols(); i++){
            col_width(i, (double)1/cols() *W2);//auto resize to new width
        }
        Fl_Table::resize(X,y,W,h);
        return;
    } 


    for(int i=0; i<cols(); i++){
        //col_width(i,
        //(double)1/cols() *W2);//auto resize to new width
        col_width(i,col_auto_width(i));
    }

        Fl_Table::resize(X,y,W,h);
        //redraw();

}