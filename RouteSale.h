#include "product.h"
//#include "product.cxx";
#include <Fl/Fl_Table.H>
#include <Fl/Fl_Draw.H>
#include <Fl/Fl_Int_Input.H>
#include <Fl/Fl_Choice.H>



static void input_cb(Fl_Widget* w,void * o){
        fprintf(stderr, "in input");
  switch(Fl::event())
  {
 
    case FL_KEYBOARD:
        int ek = Fl::event_key();			// key press in table?
      switch(ek) {

        case 65362://keyup 
        case 65364://keydown     
        case 65361://keyleft
        case 65363:
          w->parent()->handle(Fl::event());
          break;b
      } //fprintf(s
  }
}


class Route_Sale_Editor: public Fl_Table{
  
  public:
  Route_Sale_Editor(int x, int y, int w, int h, 
      Product_Table *product_list,
      vector<Component> *load_out,
      vector<Component> *returns);
      
  
  //read
  vector<Component> load_out(); //get loadout input
  vector<Component> returns(); //get returns input
  vector<Component> discounted_Sales(); //get_discounted sales
  int cash();                //cash entered
  
  
  //write
  void set_sales (vector<Component> sales);
  void set_product_list (vector<Component> product_list);
  //void set_Load_out (vector<Component> load_out);
 
  
  //others
  void callback_();
  int handle(int);
  
  static void cb(Fl_Widget *w, void* data){
    ((Route_Sale_Editor*)data)->callback_();
  };
  
  string titles(int C);//get titles at column c
  
  void draw_cell(TableContext context, int R, int C, int x, int y, int w, int c);
  
  
  private:
  //Fl_Choice product_input;
  Fl_Input input; //input for numbers
  Fl_Choice p_input;
  Fl_Color font_color;
  int font_size;
  Fl_Color bg_color;
  Fl_Align text_align;
  
  
  //data (like our device registers)
  struct internal_store{string item;
                        int taken; 
                        int returns; 
                        string sales_item; 
                        int sales; 
                        int price; 
                        int amount;
                         internal_store();}; //format of output as seen by user
  
  vector<internal_store> _load_out;
  
  vector<Component>_product_list; 
  
  vector<Component> _discounted_sales;

  
//************************************************************************************  
  //all collections have a selection
  struct{int row; int col;} _selection;
  
  
//************************************************************************************  
  //custome push_back to simulate 2 more rows in display
  void push_back(internal_store c)
  { 
    printf("in pushback...\n");
    internal_store d;
    if(_load_out.size()==3 &&_load_out[0].item==""){
      _load_out.clear();  
      _load_out.push_back(c);
      _load_out.push_back(d);
      _load_out.push_back(d);
      printf("first two rows added...\n");
      return;
    }
    
    _load_out.resize(_load_out.size()-2);
    _load_out.push_back(c);
    _load_out.push_back(d);
    _load_out.push_back(d);
    return;
  };
  
  //mapping functions
//******************************************************************************
  void update_rs(int R, int C, const char *val){
    string s(val);
    
    if(s=="(none)") return;
    if (!s.size()&&_load_out.size()>2){
      //delete this blanks
      _load_out.erase(_load_out.begin()+R);
      redraw();
      return;
    }
    internal_store c;
    switch(C){
      case 0: //update _load_out[R].product_name
        //is it first element?
        if(_load_out.size()==3&&_load_out[0].item==""){//is it first entry?
          c.item = val;
          push_back(c);
          rows(_load_out.size()+1);//simulate a new row;
          break;
        }
        
        //is it already there?
        if(R<_load_out.size()-3){
          _load_out[R].item = val;
          break;
        }
        
        //else, just add it
        c.item = val;
        push_back(c);
        rows(_load_out.size()+1);//simulate a new row;
        break;
     
      case 1: //update  _load_out[R].taken
        
        if(R<=_load_out.size()-3){
          _load_out[R].taken= atoi(val);
          break;
        }
        
         //we cannot update taken unless we have an entry already.
        return;//dont do callback

      
      case 2: //update returns items at index R 
        if(R<_load_out.size()-3){
          _load_out[R].returns= atoi(val);
          break;
        }
         //we cannot update taken unless we have an entry already.
        return;//dont do call back;
      
      default: return;
    }
      
     do_callback(callback_context(),callback_row(),callback_col());
  }
  
  
//****************************************************************************  
  string get_rs_value(int R, int C){
    //we can not return what is not there
    if(R>_load_out.size()-1)return ""; 
    
    char s[15];
    int res;
    switch(C){
      case 0: //return _load_out[r].item
        return  _load_out[R].item;
        
      case 1: //return  _load_out[R].count
        res =_load_out[R].taken;
        break;
      
      case 2: //return returns items at index R 
        res = _load_out[R].returns;
        break;
      
      case 3: //return  _load_out[R].count
        return "";
      
      case 4: //return returns items at index R 
        return  _load_out[R].sales_item;
        
        
      case 5: //return returns items at index R 
        res = _load_out[R].sales;
        break;
        
      case 6: //return returns items at index R 
        res = _load_out[R].price;
        break;      
        
      case 7: //return returns items at index R 
        res = _load_out[R].sales*_load_out[R].price;
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
     //  string s;
       char update_str[20];
      if(_selection.col){
        strncpy(update_str,input.value(),19);
      
      }else{//we are deselecting col one? which is a combo
      //  update_str="";
        if(_product_list.size())
            strncpy(update_str,_product_list[p_input.value()].product_name.c_str(),19);
      }
      
      int x,y,w,h;
      find_cell(callback_context(),R, C,x,y,w,h);
      if(C){
      //input.hide();
      update_rs(_selection.row,_selection.col,update_str);
      //printf("rows now: %d\n",_load_out.size());
      input.value(get_rs_value(R,C).c_str());
      input.resize(x,y,w,h);
      
      _selection.row = R;
      _selection.col = C;
      if(!input.visible())input.show();
      //input.position(input.size(),0); //select text for easy navigation
      //input.take_focus();
      input.redraw();
      return;
      }
//            int x,y,w,h;
//      find_cell(callback_context(),R, C,x,y,w,h);
//      if(C){
      //input.hide();
   
      update_rs(_selection.row,_selection.col,update_str);
      //printf("rows now: %d\n",_load_out.size());
      int val =p_input.find_index(get_rs_value(R,C).c_str());
      p_input.value(val!=-1?val:0);
      p_input.resize(x,y,w,h);
      
      _selection.row = R;
      _selection.col = C;
      if(!p_input.visible())p_input.show();
      //input.position(input.size(),0); //select text for easy navigation
      //input.take_focus();
      p_input.redraw();
      
      //synclonisation flags

      fprintf(stderr,"input put in focus \n");
  }
};




//*************************************************************************************
Route_Sale_Editor::internal_store::internal_store():item(""),taken(0),returns(0),sales_item(""),sales(0),price(0),amount(0){};



//**************************************************************************************
Route_Sale_Editor::Route_Sale_Editor(int x, int y, int w, int h, 
      Product_Table *product_list=0,
      vector<Component> *load_out=0,
      vector<Component> *returns=0):Fl_Table(x,y,w,h),input(h-20,h-20,w/6,h/10),p_input(h-20,h-20,w/6,h/10){
        when(FL_WHEN_NOT_CHANGED);
        
        //handle empty 
          vector<Component> c;
        if(!load_out) load_out = &c;
        if(!returns) returns = &c;
        
        Component cc;

        if( !product_list) {_product_list =c;}else{
            cc.product_name="(none)"; //default
            _product_list.push_back(cc);
          for(int i=0; i<product_list->size(); ++i){   
            cc.product_name = product_list->product(i).name();
            cc.count = 2;
            _product_list.push_back(cc);
          }

        }

        //load values;
        //_product_list = *product_list;
        
        //combinix algorithm
          //load out first
          for(int i=0; i<load_out->size(); ++i){
            internal_store data;
            //store taken
            data.item = (*load_out)[i].product_name;
            data.taken = (*load_out)[i].count;
            
            //matching return
            int idx = index(*returns,data.item);
            if(idx!=-1) {
              data.returns = (*returns)[idx].count;
            //highlight for skipping in last step
              (*returns)[idx].count = 0;
              //done
              push_back(data);
              continue;
            } 
          }
        
        //final step
          for(int i=0; i<returns->size(); ++i){
            internal_store data;
            if((*returns)[i].count){
              data.item = (*returns)[i].product_name;
              data.returns = (*returns)[i].count;
              push_back(data);
            }
          }

        _selection.row = 0;
        _selection.col = 0;
      
      
      callback(&cb, this);

      font_color=FL_BLACK;
      font_size=12;
      bg_color=FL_WHITE;
      text_align=FL_ALIGN_LEFT;
      //init input;
      
      cols(8);//6 attributes
      rows(3);//size of input vector with largest elements
      
      //now that we have default rows and cols, create input
      input.box(FL_BORDER_BOX);
      input.callback(&input_cb,this);
      input.when(FL_WHEN_NOT_CHANGED);
      input.textcolor(font_color);
      input.textsize(font_size);
      int ix,iy,iw,ih;
      find_cell(callback_context(),0,0,ix,iy,iw,ih);
      input.resize(ix,iy,iw,ih);
      input.show();
      
       //now that we have default rows and cols, create input
      for(int i=0; i<_product_list.size();++i){
        p_input.add(_product_list[i].product_name.c_str());
      }
      if(p_input.size())p_input.value(1);
      p_input.box(FL_BORDER_BOX);
      p_input.callback(&input_cb,this);
      p_input.when(FL_WHEN_NOT_CHANGED);
      p_input.textcolor(font_color);
      p_input.textsize(font_size);
      p_input.value(0);
      //find_cell(callback_context(),0,0,ix,iy,iw,ih);
      p_input.resize(ix,iy,iw,ih);
      p_input.show();
      
      col_header(1);
      col_width_all(70);
      col_resize(1);
      
      row_resize(1);
      
      end();
      
      internal_store totals;
      _load_out.push_back(totals);//simulate 2 blank rows
      _load_out.push_back(totals);
      _load_out.push_back(totals);
      };
 

void Route_Sale_Editor::callback_(){
  vector<Component> load = load_out();
  vector<Component> ret = returns();
  print_comp_list(load);
  print_comp_list(ret);
  
  //set_sales((p_table())->difference(load,ret));
  if(!p_table())return;//->difference(load,ret)
    printf("table size is..%d \n",(p_table())->size());
    set_sales((p_table())->difference(load,ret));
  redraw();
  printf("in callback, seems we have it;\n");
 
  };

//******************************************************************************************     
int Route_Sale_Editor::handle(int e){
    int retval = Fl_Table::handle(e);
  
  // fprintf(stderr, "in ::handle \n");
  //fprintf(stderr, "conversion done\n");
  
  if(callback_context()==CONTEXT_CELL){
    //printf("context is true");

    switch (e){
     
    case FL_PUSH:
       fprintf(stderr, "in handle");
       //position the input here
       select(callback_row(),callback_col());
      return 1;
    
    case FL_KEYBOARD:
      fprintf(stderr, "in handle");
        int ek = Fl::event_key();			// key press in table?
//      fprintf(stderr,"old pos r%d c%d",tb->selected_row, tb->selected_col);
      //fprintf(stderr," %d \n ",Fl::event_key());
      switch(ek) {

      case 65362://keyup
        if(_selection.row >=1)
          select(_selection.row-1,_selection.col);
        //fprintf(stderr,"new pos r%d c%d",tb->selected_row, tb->selected_col);
        break;
        
      case 65364://keydown
        if(_selection.row <rows()-1)
          select(_selection.row+1,_selection.col);
        break;
      
      case 65361://keyleft
        if( _selection.col >=1)
          select(_selection.row,_selection.col-1);
        break;
      
      case 65363:
         if( _selection.col <cols()-1)
            select(_selection.row,_selection.col+1);
        break;
      } //fprintf(stderr,"new pos r%d c%d",selection_row, tb->selected_col);

    }
    
  }
      if (callback_context()==CONTEXT_RC_RESIZE){

       // col_width_all(70);
         //fprintf(stderr,"resizing \n");
      }
      return retval;
} 

//************************************************************************************************

void Route_Sale_Editor::draw_cell(TableContext cxt, int R, int C, int X, int Y, int W, int H){
        
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
          
          if(R==_selection.row && C==_selection.col ){;return;};
         //  printf("drawcell :row is<%d %d>, selection is %d %d\n", R,C, _selection.row,_selection.col);
            fl_font(FL_HELVETICA, font_size);	// set font for heading to bold
            fl_push_clip(X,Y,W,H);			// clip region for text
            
            fl_draw_box(FL_FLAT_BOX, X,Y,W,H,bg_color);
            fl_color(49);
            fl_rect(X,Y,W,H);
            
            fl_color(font_color);
            //R==9&&C==0?fl_draw("Totals", X,Y,W,H, FL_ALIGN_CENTER):(void)0;
            fl_draw(get_rs_value(R,C).c_str(), X+pad,Y,W,H, text_align);
          fl_pop_clip();
         // fprintf(stderr,"drawing other cell \n");
          return;

  }
}

string Route_Sale_Editor::titles(int c){
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

void Route_Sale_Editor:: set_sales(vector<Component>s){
    if(!_load_out.size())return;//if no loads, sales are meaningless
    
    int item =0;
    for (int i=0; i<_load_out.size(); ++i){
       if((item>=s.size()))break;
        _load_out[i].sales_item = s[i].product_name;
        _load_out[i].sales = s[i].count;
        ++item;
    }
     if(item>=s.size()){
       //delete
       while(item<_load_out.size()){
         _load_out[item].sales_item = "";
         _load_out[item].sales=0;
         _load_out[item].price=0;
         _load_out[item].amount=0;
         ++item;
       }
       return;
     }
    //if you get here, you have more sales items than the largest size of returns and loads 
    internal_store ex;
    while(item<s.size()){
        ex.sales_item = s[item].product_name;
        ex.sales = s[item].count;
        push_back(ex);
      ++item;
    }
    return;
  }
  
vector<Component> Route_Sale_Editor::load_out(){
  vector<Component> r; Component c;
  for(int i=0;i<_load_out.size(); ++i){
    if(_load_out[i].item=="")continue;//skip blanks
    c.product_name = _load_out[i].item;
    c.count =_load_out[i].taken;
    r.push_back(c);
  }
  return r;
}

vector<Component> Route_Sale_Editor::returns(){
  vector<Component> r; Component c;
  for(int i=0;i<_load_out.size(); ++i){
    if(_load_out[i].item=="")continue;//skip blanks
    c.product_name = _load_out[i].item;
    c.count =_load_out[i].returns;
    r.push_back(c);
  }
  return r;
}