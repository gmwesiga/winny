#include "product.h"
//#include "product.cxx";
#include <Fl/Fl_Table.H>
#include <Fl/Fl_Draw.H>
#include <Fl/Fl_Int_Input.H>
#include <Fl/Fl_Choice.H>

typedef Component Pair;

static void input_cb(Fl_Widget* w,void * o){

}


#define item product_name

class complist_input: public Fl_Table{
  
  public:
  complist_input(int x, int y, int w, int h, 
       Product_Table *product_list);
      

  //read
  vector<Pair>& value(); //get loadout input
  
  //write
  void value (vector<Pair>& value);
  
  //others
  void callback_();
  int _handle(int);
  //int handle(int e);//{Fl_Table::handle(e); printf("in handle...\n"); return 1;};
  
  void resize(int x, int y, int w, int h){ col_width_all((w-6)/2+3); Fl_Table::resize(x,y,w,h);};
  static void cb(Fl_Widget *w, void* data){
    ((complist_input*)data)->callback_();
  };
  
  
  string titles(int C);//get titles at column c
  
   int handle(int e);
    
    // switch(e)
  // {
 
    // case FL_KEYBOARD:
        // int ek = Fl::event_key();			// key press in table?
      // switch(ek) {

        // case 65362://keyup 
        // case 65364://keydown     
        // case 65361://keyleft
        // case 65363:
          // do_callback();
          // break;
      // } printf("forwarded\n");
     
  // }return Fl_Table::handle(e);
 // }
 
 
  void draw_cell(TableContext context, int R, int C, int x, int y, int w, int c);
  
  
  private:
  //Fl_Choice product_input;
  Fl_Input input; //input for numbers
  Fl_Choice p_input;
  Fl_Color font_color;
  int font_size;
  Fl_Color bg_color;
  Fl_Align text_align;
  
  vector<Pair>_data; 
  Product_Table *_product_list;
  
//************************************************************************************  
  //all collections have a selection
  struct{int row; int col;} _selection;
  Fl_Widget * current_input;
  
//************************************************************************************  
  //custome push_back to simulate 2 more rows in display
  void push_back(Pair c)
  { 
    printf("in pushback...\n");
    Pair d;
    if(_data.size()==3 &&_data[0].item==""){ //constructor inserts dummy pairs
      _data.clear();  
      _data.push_back(c);
      _data.push_back(d);
      _data.push_back(d);
      printf("first two rows added...\n");
      return;
    }
    
    _data.resize(_data.size()-2);
    _data.push_back(c);
    _data.push_back(d);
    _data.push_back(d);
    return;
  };
  

  //mapping functions
//******************************************************************************
  void update(int R, int C, const char *val){
    string s(val);
    
    //setting a pair to "none" results in deletion
    if(s=="(none)" &&_data.size()>3 && R<_data.size()-3){
      //delete this blank
      _data.erase(_data.begin()+R);
      redraw();
      return;
    }
   
    //first row can not contain a "none" element;
    if(s=="(none)") return;
    
    Pair c;
    switch(C){
      case 0: //update _data[R].product_name
   
        if(_data.size()==3&&_data[0].item==""){//is it first entry?
          //c.item = val;
          _data[0].item = val;
          //push_back(c);
          rows(_data.size()+1);//simulate a new row;
          break;
        }
        
        //is it already there?
        if(R<_data.size()-2){
          _data[R].item = val;
          break;
        }
        
        //else, just add it
        c.item = val;
        push_back(c);
        rows(_data.size()+1);//simulate a new row;
        break;
     
      case 1: //update  _data[R].taken
        
        if(R<=_data.size()-1){
          _data[R].count= atoi(val);
          break;
        }
        
         //we cannot update taken unless we have an entry already.
        return;//dont do callback

      default: return;
    }
      
     //do_callback(callback_context(),callback_row(),callback_col());
  }
  
  
//****************************************************************************  
  string get_value(int R, int C){
    //we can not return what is not there
    if(R>_data.size()-1)return ""; 
    
    char s[15];
    int res;
    switch(C){
      case 0: //return _data[r].item
        return  _data[R].item;
        
      case 1: //return  _data[R].count
        res =_data[R].count;
        break;
      
      default:
        return "";
    }
    sprintf(s,"%d",res);
    if(res>0){return s;}
    return "";
  }
  
  
//****************************************************************************************  
  void select(int R, int C){
    //check range
    if(R>_data.size()-1|| C>1 ){printf("out of range ...\n"); return;}
    current_input->hide();
     if(R==_selection.row && C==_selection.col){
       if(C){input.take_focus();}else p_input.take_focus();
       return;
     }
     
     //  string s;
       char update_str[20];
      if(_selection.col){
        strncpy(update_str,input.value(),19);
      
      }else{//we are deselecting col one? which is a combo
      //  update_str="";
        if(_product_list->size())
            
            if(!(p_input.value())) strncpy(update_str, "(none)",19); else
            strncpy(update_str,_product_list->product(p_input.value()-1).name().c_str(),19);//-1 accounts for the (none)
      }
      
//      printf("*%s*%d*%d ... combo value is (%d)\n",update_str,R,C,p_input.value());
      
      int x,y,w,h;
      find_cell(callback_context(),R, C,x,y,w,h);
      if(C){
      //input.hide();
      update(_selection.row,_selection.col,update_str);
      //printf("rows now: %d\n",_data.size());
      input.value(get_value(R,C).c_str());
      input.resize(x,y,w,h);
      
      _selection.row = R;
      _selection.col = C;
      p_input.hide();
      current_input = & input;
      if(!input.visible())input.show();
      //input.position(input.size(),0); //select text for easy navigation
      //input.take_focus();
      input.redraw();
      printf("done..\n");
      return;
      }
//            int x,y,w,h;
//      find_cell(callback_context(),R, C,x,y,w,h);
//      if(C){
      //input.hide();
   
      update(_selection.row,_selection.col,update_str);
      //printf("rows now: %d\n",_data.size());
      int val =p_input.find_index(get_value(R,C).c_str());
      p_input.value(val!=-1?val:0);
      p_input.resize(x,y,w,h);
      
      _selection.row = R;
      _selection.col = C;
      current_input = & p_input;
      input.hide();
      p_input.show();
      //input.position(input.size(),0); //select text for easy navigation
      //input.take_focus();
      p_input.redraw();
      
      //synclonisation flags

      fprintf(stderr,"input put in focus \n");
  }
};




//*************************************************************************************
//complist_input::Pair::Pair():item(""),taken(0),returns(0),sales_item(""),sales(0),price(0),amount(0){};



//**************************************************************************************
complist_input::complist_input(int x, int y, int w, int h, 
       Product_Table *product_list=0):Fl_Table(x,y,w,h),input(h-20,h-20,w/6,h/10),p_input(h-20,h-20,w/6,h/10){
        when(FL_WHEN_NOT_CHANGED);
        
        //handle empty 
          vector<Pair> c;
      _product_list = product_list;
     _product_list->sort();

        //load values;
        //_product_list = *product_list;

        _selection.row = 0;
        _selection.col = 0;
        current_input = & p_input;
      
      callback(&cb, this);

      font_color=FL_BLACK;
      font_size=12;
      bg_color=FL_WHITE;
      text_align=FL_ALIGN_LEFT;
      //init input;
      
      cols(2);//6 attributes
      rows(3);//size of input vector with largest elements
      
      //now that we have default rows and cols, create input
      input.box(FL_BORDER_BOX);
      input.callback(&input_cb,this);
      input.when(FL_WHEN_NOT_CHANGED);
      input.textcolor(font_color);
      input.textsize(font_size);
       int ix,iy,iw,ih;
      // find_cell(callback_context(),0,0,ix,iy,iw,ih);
      // input.resize(ix,iy,iw,ih);
      // input.show(); 
      
       //now that we have default rows and cols, create input
       p_input.add("(none)");
      for(int i=0; i<_product_list->size();++i){
        p_input.add(_product_list->product(i).name().c_str());
      }
      if(p_input.size())p_input.value(0);
      p_input.box(FL_BORDER_BOX);
      p_input.callback(&input_cb,this);
      p_input.when(FL_WHEN_NOT_CHANGED);
      p_input.textcolor(font_color);
      p_input.textsize(font_size);
      //find_cell(callback_context(),0,0,ix,iy,iw,ih);
      //p_input.resize(tox,toy,tow/2,row_height(0));
      p_input.show();
      
      col_header(1);
      col_width_all((w-4)/2);
      col_resize(1);
      
      row_resize(1);
      
      
      end();//end table group //very important
      
      Pair totals;
      _data.push_back(totals);//simulate 2 blank rows
      _data.push_back(totals);
      _data.push_back(totals);
      };
 

void complist_input::callback_(){
  
  
  // fprintf(stderr, "in ::handle event is %d (%d,%d)\n", e,callback_row(),callback_row());
  
  if(callback_context()==CONTEXT_CELL){
    //printf("context is true");

    switch (Fl::event()){
     
    case FL_PUSH:
       //position the input here
       select(callback_row(),callback_col());
      return ;
    
    case FL_KEYUP:
        int ek = Fl::event_key();			// key press in table?
        
      switch(ek) {
        
      case FL_Enter:
          printf("enter key...(%d,%d)\n",callback_row(),callback_col());
          select(callback_row(),callback_col());

      case 65362://keyup
          select(callback_row(),callback_col());
          //fprintf(stderr, "KEY UP\n");
        //fprintf(stderr,"new pos r%d c%d",tb->selected_row, tb->selected_col);
        break;
        
      case 65364://keydown
           select(callback_row(),callback_col());
        break;
      
      case 65361://keyleft
         select(callback_row(),callback_col());
        break;
      
      case 65363:

          select(callback_row(),callback_col());
        break;
      } //fprintf(stderr,"new pos r%d c%d",selection_row, tb->selected_col);

    }
    
  }
      if (callback_context()==CONTEXT_RC_RESIZE){

       // col_width_all(70);
         //fprintf(stderr,"resizing \n");
      }
 //     return retval;
} 

//************************************************************************************************

void complist_input::draw_cell(TableContext cxt, int R, int C, int X, int Y, int W, int H){
        
        //COLOR FOR BORDERS
        int pad =5;
        
     switch (cxt){

        case CONTEXT_COL_HEADER:
        //fprintf(stderr,"Headers\n");
            fl_font(FL_HELVETICA, font_size);	// set font for heading to bold
            fl_push_clip(X,Y,W,H);			// clip region for text
            
            fl_draw_box(FL_FLAT_BOX, X,Y,W,H,bg_color);
            fl_color(49);
            fl_rect(X,Y,W,H);
            
            fl_color(FL_BLACK);
            fl_draw(titles(C).c_str(), X+pad,Y,W,H, text_align);

          fl_pop_clip();
         //fprintf(stderr,"done With headers \n");
        return;
        
      case CONTEXT_CELL:
          
          if(R==_selection.row && C==_selection.col ){current_input->show();return;};
         //  printf("drawcell :row is<%d %d>, selection is %d %d\n", R,C, _selection.row,_selection.col);
            fl_font(FL_HELVETICA, font_size);	// set font for heading to bold
            fl_push_clip(X,Y,W,H);			// clip region for text
            
            fl_draw_box(FL_FLAT_BOX, X,Y,W,H,bg_color);
            fl_color(49);
            fl_rect(X,Y,W,H);
            
            fl_color(font_color);
            //R==9&&C==0?fl_draw("Totals", X,Y,W,H, FL_ALIGN_CENTER):(void)0;
            fl_draw(get_value(R,C).c_str(), X+pad,Y,W,H, text_align);
          fl_pop_clip();
         // fprintf(stderr,"drawing other cell \n");
          return;
      
      case CONTEXT_RC_RESIZE:
        //if(R==_selection.row && C==_selection.col ){
           find_cell(cxt,_selection.row, _selection.col,X,Y,W,H);//arguments RCXYWH are all zero, but if we have our own RC, we use findcell()
           current_input->resize(X,Y,W,H); 
           printf("resize(%d,%d,%d,%d)\n",R,C,W,H);
           current_input->show();return;//};
        break;
  }
}

string complist_input::titles(int c){
  switch (c){
    
    case 0:
      return "Product";
    
    case 1:
      return "Load Out";
      
    case 2:
      return "Returns";
      
    case 3:
      return "";
    case 4:
      return "Sales";
     
    case 5: return "Unit Sales";
    
    case 6: return "Price";
    
    case 7: return "Amount";
    
    default:
      return "";
  }
}

void complist_input:: value(vector<Pair>&s){
    _data = s;
  }
  

vector<Pair>& complist_input::value(){
  vector<Pair> r; Pair c;
  for(int i=0;i<_data.size(); ++i){
    if(_data[i].item=="")_data.erase(_data.begin()+i);//skip blanks
    
  }
  _data.resize(_data.size()-2);
  return _data;
}

int complist_input::handle(int e){
  int ret = Fl_Table::handle(e);
  
  int R, C;
  
  if(e== FL_KEYUP){
     
     int ek = Fl::event_key();			// key press in table?
        
      switch(ek) {
        
        case FL_Enter:
          if(!_selection.col){
            
            R = _selection.row; C = _selection.col+1;
          }else{
            R = _selection.row+1; C = 0;
          }
          break;
        case 65362://keyup
          if(_selection.row >=1)
            
            R = _selection.row-1; C = _selection.col;
            fprintf(stderr, "KEY UP\n (%d, %d)",R, R+1);
          //fprintf(stderr,"new pos r%d c%d",tb->selected_row, tb->selected_col);
          break;
          
        case 65364://keydown
          if(_selection.row <rows()-1)
            R = _selection.row+1; C = _selection.col;
          break;
        
        case 65361://keyleft
          if( _selection.col >=1)
            R = _selection.row; C = _selection.col-1;
          break;
        
        case 65363:
           if( _selection.col <cols()-1)
              R = _selection.row; C = _selection.col+1;
          break;
      }
    do_callback(CONTEXT_CELL,R,C);
    current_input->show();//hack for enter key
    return 1;
  }//fprintf
  return ret;
}