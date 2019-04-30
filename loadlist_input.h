#pragma once
#ifndef id9E78EBE9_25FD_4D1B_B208F05EA882C2F8
#define id9E78EBE9_25FD_4D1B_B208F05EA882C2F8



//tester.cxx records_lib.cxx -over1 -I/local/include/ -L/local/lib/ -lfltk -lole32 -luuid -lcomctl32 -lgdi32 -std=gnu++11
#include "records_lib.h"
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Int_Input.H>
#include "winny_theme.h"
#include <FL/Fl_Choice.H>

#define TAIL_ROWS       1 
#define ROWS TAIL_ROWS +1 //initial rows
#define COLS            4 //inital cols

 static void input_cb(Fl_Widget *w,void *);

class loadlist_input: public Fl_Table
{
  
  public:
    loadlist_input(int x, int y, int w, int h,const char* l=0);
    //read
    vector<load_item> value(); //get loadout input
    //write
    void value (vector<load_item> value);
    void add_product(Product p);        // products to select from
                                         // vector will give us insert(),[],push_back etc affordances
    void product_list(vector<Product> * list)
    { productlist= *list; 
      if(list)
        for(int i=0; i<list->size(); ++i)
          p_input.add((*list)[i].name().c_str());   
    }
    
    void clear()
    {
      _data.clear();
      load_item totals;
      _data.push_back(totals);  
      rows(ROWS);
      select(0,0);
      //redraw();
    }
  protected:  
    //others
    string titles(int C);//get titles at column c
    void push_back(load_item c);
    //mapping functions for table hit testing
    void update(int R, int C, const char *val);
    string get_value(int R, int C);
    void select(int R, int C);
    string get_input_value(); //get current input value
    
    //Fl_Table re-implementations
    int handle(int e);
    void draw_cell(TableContext context, int R, int C, int x, int y, int w, int h);
    void resize(int x, int y, int w, int h);
    
    vector<Product> productlist;
    double totals;
    
  private:
    //Fl_Choice product_input;
    Fl_Input input; //input for numbers
    Fl_Choice p_input;
    //Fl_Input input2;
    Fl_Color font_color;
    int font_size;
    Fl_Color bg_color;
    Fl_Align text_align;
    
    vector<load_item>_data;     
    struct{int row; int col;} _selection;    //all collections have a selection
    Fl_Widget * current_input;              //current input
  
};

inline print_load(vector<load_item>l)
{
	printf("\n {");
	for (int i=0; i<l.size(); ++i)
	{
		printf("%s:%d, ", l[i].item().c_str(),l[i].qty()) ;
	}
	printf("}\n");
}
#endif // header
