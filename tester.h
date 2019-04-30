//Widget tester file

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
//#include <FL/Fl_Check_Browser.H>
//#include <stdio.h>
#include <vector>
#include <string>
#include "RouteSale.h"

using std::vector;
using std::string;

int main(){
  //test check brower with items[]={"one", "two", "three"}
    //data: window, checkbrower, items[]
    Fl_Window *window; 
    //Fl_Check_Browser * check_browser;
    
    Component c;
    vector<Component> items; 
      {
        c.product_name = "case"; c.count=200;
        items.push_back(c);
       items.push_back(c);
       items.push_back(c);
       items.push_back(c);//"see you soon"
      };
    //program
      //initialise window
      window = new Fl_Window(50,50, 400,400,"tester");
      //initialise a check_brower
      Route_Sale_Editor* rs = new Route_Sale_Editor(50,60,200,100,items,items,items);
      rs->rows(4);
      rs->cols(6);
      //add items to the check broswer
      //int i{0};
      //while( i<items.size()){check_browser->add(items[i].c_str()); ++i;};
      //insert it into window
      window->end();
      //display window
      window->show();
      //begin window event loop
      return Fl::run();
      
}