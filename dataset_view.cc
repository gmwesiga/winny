#include "dataset_view.h"
#include "winny_theme.h"

char* num2string(double num);

dataset_view::dataset_view(int x, int y, int w, int h, const char* L)
:Fl_Table::Fl_Table(x,y,w,h,L), data_(nullptr)
{
    init_ui();
    color(WGT_COLOR_DOM());
    col_header(ON);
    col_resize(ON);
  NORMAL_FSIZE          = DOMFONT_SIZE();
  backcolor             = DOMWGT_COLOR();
  border_color          = DOMWGT_COLOR();      
  Fl_Align alignment    = FL_ALIGN_LEFT;
  set_winny_button_theme(vscrollbar);
  set_winny_button_theme(hscrollbar);
  vscrollbar->slider(WINNY_THICK_BORDERBOX);
  hscrollbar->slider(WINNY_THICK_BORDERBOX);
  set_selection(0,0,0,0);
  end();
  dsv_select_row =0;

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
	  if(R==dsv_select_row)
	  {  backcolor    = SELECTION_BACKCOLOR();
		 border_color = SELECTION_BORDERCOLOR();
	  }else if(R==select_row)
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
      backcolor             = DOMWGT_COLOR();
      border_color          = DOMWGT_COLOR(); 
      return;

    case CONTEXT_ROW_HEADER:
      draw_data(data_->row_header(R),X,Y,W,H);
      draw_grid(data_->row_header(R).style().borders,X,Y,W,H);
      //reset
      backcolor             = DOMWGT_COLOR();
      border_color          = DOMWGT_COLOR(); 
      return;
  }
};

void dataset_view::draw_data(table_data& dt, int X, int Y, int W, int H)
{
    //dt = const_cast<table_data>(dt); 
    fl_color(backcolor);                        //white background
    fl_font(FL_HELVETICA,NORMAL_FSIZE);         //prepare to draw text
    fl_push_clip(X,Y,W,H);
    switch(dt.type()){
        case NUMBER:
            fl_rectf(X,Y,W,H);
            fl_color(wcolor2flcolor(dt.style().forecolor));                       //text color is black
            fl_draw( num2string(dt.number()), X+10, Y,W-20, H, alignment);//-10 creates a small margin on the left -20 on the right
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
    
    int W = w()-vscrollbar->w();
    W = W/cols();
    ow=w();
    col_width_all(W);
    col_resize_min(W);

    d->add_listener(& dataview_cb, (void*)this);
    data_ = d;

    redraw();

};

void dataset_view::dataview_cb(dataset* d, void* v){
    dataset_view * view = (dataset_view*)v;
    view->cols(d->cols());
    view->rows(d->rows());
    view->redraw();
};


int dataset_view::handle(int e){
//handles events from os 
     TableContext cxt;
      int ret =    Fl_Table::handle(e);
      ResizeFlag   rf ;
      int          R,C;
      int          previous_srow; 
      switch(e)
		{
		  case FL_MOVE:
			cxt = cursor2rowcol(R,C,rf);
            if(cxt!=CONTEXT_CELL)return ret; 
			if(R==select_row ||R==current_row) {return 1;}
			
            select_row = R;
            set_selection(R,0,R,rightcol);//select this row
            redraw_range(toprow,botrow,0,rightcol);
            
            return 1; 
		   
		   case FL_LEAVE: 
            select_row=-1; //hide   
            break;
		   
           case FL_PUSH: 
            cxt = cursor2rowcol(R,C,rf);
            if (cxt!=CONTEXT_CELL)return ret;
            dsv_select_row = R;

            set_selection(R,0,R,rightcol);//select this row
            redraw_range(toprow,botrow,0,rightcol);
            //redraw();

            take_focus();//prepare to use keyboard nav
            if(when()&FL_WHEN_CHANGED ||when()&FL_WHEN_RELEASE ||when()&FL_WHEN_ENTER_KEY)
                do_callback(cxt,R,C);
            return 0;//don't send '
		   
           case FL_KEYDOWN:
            switch(Fl::event_key()){
                case FL_Down:
                case FL_Up:
                case FL_Page_Up:
                case FL_Page_Down:
                case FL_Home:
                case FL_End:
                    //fl::table throws focus on Fl_Up when select_row ==0
                    //so, we want to keep it
                    if(!ret)return 1;
                    
                   set_selection(select_row,0,select_row,rightcol);//select this row 
                   redraw_range(toprow,botrow,0,rightcol);
                   //redraw();
                   // printf("current_row(%d)\n",current_row);
                
                break;

                case FL_Enter:
                case FL_KP_Enter:

                // not using cursor so no need to test for this                
                    //cxt = cursor2rowcol(R,C,rf); 
                    //if (cxt!=CONTEXT_CELL)return ret;  
                
                dsv_select_row = select_row; 
               
                set_selection(select_row,0,select_row,rightcol);//select this row
                redraw_range(toprow,botrow,0,rightcol);
                //redraw();
               
                take_focus();
                if(when()&FL_WHEN_CHANGED ||when()&FL_WHEN_RELEASE ||when()&FL_WHEN_ENTER_KEY)
                    do_callback(cxt,R,C);
                return 1;//don't send '   
             }
			  //redraw(); 
		  default: 
			return ret;
		}
        return ret; 
};

//converts from api to implementation defined color
Fl_Color dataset_view::wcolor2flcolor(const wcolor& w)const{
    return fl_rgb_color(w.red(),w.green(),w.blue());
};


static char* _cstring_ =0;
//converts number to int and stores it in cstring
char* num2string(double num){
    if(_cstring_)delete[]_cstring_; //not optimum 
    char* _cstring_ = new char[20];
    sprintf(_cstring_,"%15.f",num);
    return _cstring_;
}

void dataset_view::col_auto_resize(int val){
    col_auto_resize_ = val;
};

int dataset_view::col_auto_resize(){
    return col_auto_resize_;
};

void dataset_view::resize(int X, int y, int W, int h){

    if(!col_auto_resize_){
            Fl_Table::resize(X,y,W,h);
        return;
    } 

    int W2 = W-vscrollbar->w();//new width

    for(int i=0; i<cols(); i++){
        col_width(i,
        (double)1/cols() *W2);//auto resize to new width
    }

        Fl_Table::resize(X,y,W,h);

}