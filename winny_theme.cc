#include "winny_theme.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>

//custome box type with thin border.
void winny_thin_border_box(int x, int y, int w, int h, Fl_Color c )
{
  fl_color(c);
  fl_rectf(x,y,w,h);
  fl_color(GRIDLINE_COLOR());
  fl_rect(x,y,w,h); 
}

void winny_thick_border_box(int x, int y, int w, int h, Fl_Color c ){
  fl_color(c);
  fl_rectf(x,y,w,h);
  fl_color(GRIDLINE_COLOR3());
  fl_rect(x,y,w,h);
};


void winny_thin_border_frame(int x, int y, int w, int h, Fl_Color c )
{
  fl_color(GRIDLINE_COLOR());
  fl_rect(x,y,w,h);
};

//NO BORDER BOX
void winny_no_border_box(int x, int y, int w, int h, Fl_Color c )
{
  fl_color(c);
  fl_rectf(x,y,w,h);
  fl_color(GRIDLINE_COLOR());
}

void winny_top_border_box(int x, int y, int w, int h, Fl_Color c )
{
  fl_color(c);
  fl_rectf(x,y,w,h);
  fl_color(GRIDLINE_COLOR());
  fl_line(x,y,x+w, y);
}

void winny_bottom_border_box(int x, int y, int w, int h, Fl_Color c )
{
  fl_color(c);
  fl_rectf(x,y,w,h);
  fl_color(GRIDLINE_COLOR());
  fl_line(x-h,y-h,x-h+w, y-h);
}


static int is_init = 0;
static int bindex =(int) WINNY_THIN_BORDERBOX;//borderindex in array of boxtypes

void init_ui(void){
 if(is_init) return; 
 Fl::set_boxtype(WINNY_THIN_BORDERBOX,winny_thin_border_box, 1,1,2,2);
 Fl::set_boxtype(WINNY_THICK_BORDERBOX,winny_thick_border_box, 1,1,2,2); //NOT IMPLEMENTED REALLY
 Fl::set_boxtype(WINNY_THIN_BORDERBOX,winny_thin_border_box, 1,1,5,5);
 Fl::set_boxtype(WINNY_THICK_BORDERBOX2,winny_thick_border_box, 1,1,2,2);//NOT IMPLEMENTED REALLY
 Fl::set_boxtype(WINNY_THINDOWN_BORDERBOX,winny_thin_border_box, 1,1,2,2);
 Fl::set_boxtype(WINNY_THIN_BORDERFRAME,winny_thin_border_frame, 1,1,2,2);
 Fl::set_boxtype(WINNY_THINDOWN_BORDERFRAME,winny_thin_border_frame, 1,1,2,2);
 Fl::set_boxtype(WINNY_NO_BORDERBOX,winny_no_border_box, 1,1,2,2);
 Fl::set_boxtype(WINNY_TOP_BORDERBOX,winny_top_border_box, 1,1,2,2);
 Fl::set_boxtype(WINNY_BOTTOM_BORDERBOX,winny_bottom_border_box, 1,1,2,2);
 is_init = 1; 
}

void set_winny_input_theme(Fl_Input_*w){
    w->color(DOMWGT_COLOR());
    w->labelcolor(WINNY_NORMALTEXT_COLOR); 
    w->textcolor(WINNY_NORMALTEXT_COLOR); //text color;
    w->labelsize(WINNY_NORMALTEXT_FONTSIZE); 
    w->textsize(WINNY_NORMALTEXT_FONTSIZE+2);   //text size
    w->box(WINNY_THIN_BORDERBOX);
    w->align(FL_ALIGN_TOP_LEFT);
};

void set_winny_window_theme(Fl_Widget*w){

   if(w->color()==FL_BACKGROUND_COLOR || w->color()==FL_BACKGROUND2_COLOR) 
      w->color(WINDOW_COLOR()); //dont update if we have already provided a color
   if(w->labelcolor()==FL_FOREGROUND_COLOR){   
      w->labelcolor(WINNY_NORMALTEXT_COLOR); 
    //w->textcolor(DOMFONT_COLOR()); //text color;
      w->labelsize(WINNY_NORMALTEXT_FONTSIZE); 
   }
   if((int)(w->box())<bindex) //we didn't assign a custome box
      w->box(WINNY_NO_BORDERBOX);
      //w->box(WINNY_THIN_BORDERBOX);//testing

  if(!(w->as_group())){    
    return;
  }else{
    Fl_Group* gw = (Fl_Group*)w;
    for(int i =0; i< gw->children(); i++)
      set_winny_window_theme(gw->child(i));
  }
};

void set_winny_button_theme(Fl_Widget*w){
    w->color(fl_rgb_color(233,233,233));//grey color for all buttons
    w->labelcolor(WINNY_NORMALTEXT_COLOR); 
    //w->textcolor(DOMFONT_COLOR()); //text color;
    w->labelsize(WINNY_NORMALTEXT_FONTSIZE); 
    //w->textsize(DOMFONT_SIZE());   //text size
    w->box(WINNY_THICK_BORDERBOX);
    w->selection_color(SELECTION_BACKCOLOR2());
};

void set_winny_group_theme(Fl_Group*w){
    w->color(WINDOW_COLOR());
    w->labelcolor(WINNY_NORMALTEXT_COLOR); 
    //w->textcolor(DOMFONT_COLOR()); //text color;
    w->labelsize(WINNY_NORMALTEXT_FONTSIZE); 
    //w->textsize(DOMFONT_SIZE());   //text size
    w->box(WINNY_THIN_BORDERBOX);
};

void set_winny_scroll_theme (Fl_Scroll *w){
  w->scrollbar.slider(WINNY_THIN_BORDERFRAME);
  w->scrollbar.color(fl_rgb_color(241,241,249));//very pale blue
  w->hscrollbar.slider(WINNY_THINDOWN_BORDERBOX);
  //w->scrollbar.slider.color(fl_rgb_color(241,241,249));
};