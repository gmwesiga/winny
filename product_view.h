#ifndef product_view_h
#define product_view_h

#include "records_lib.h"
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Output.H>
#include "loadlist_input.h"

char* num2string(double num);
enum which_child
{
    PRODUCT_NAME,
    OTHER_NAME,
    COST_PX,
    SELLING_PX,
    OPENING_UNITS,
    IS_COMPOUND,
    COMPONENTS
};

/** forward declaration*/
class product_view;

/**used internally to pass more userdata than default*/
typedef struct u {
    product_view* pv; 
    which_child who; 
    u(product_view* p, which_child w):pv(p),who(w){};
    } udata;

class product_view :public Fl_Tabs{
    public:
    product_view(int x, int y, int w, int h, char* l=0);
    
    const Product* get_product()const{return &pdt;};
    Product* get_product(){return &pdt;};
    attach_product(const Product* p );
    attach_product_table(Product_Table* tb){
        ptable = tb;
        components->product_list(tb->data());
        };

    private:
    Product pdt;
    Product_Table* ptable;
    Fl_Group *details;
    Fl_Input *product_name;
    Fl_Input *other_name;
    Fl_Float_Input *cost_px;
    Fl_Float_Input *selling_px;
    Fl_Output *opening_units;
    Fl_Radio_Round_Button *is_compound;
    loadlist_input *components;

    udata pn,on,cp,sp,ou,ic,c;

    //handler for change event of parts
    static void product_view_comps_cb(Fl_Widget *, void*);

};

#endif