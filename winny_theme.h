#ifndef WINNY_THEME_H
#define WINNY_THEME_H

#include <FL/Enumerations.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Input_.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Scroll.H>

//To do.. new design
//all definitions to use #define macro
//widget themes
inline Fl_Color WGT_COLOR_DOM(){return fl_rgb_color(249,249,249);};//same as below
inline Fl_Color DOMWGT_COLOR(){return WGT_COLOR_DOM();};//light gray 
inline Fl_Color ACCWGT_COLOR(){return fl_rgb_color(110,153,255);};//grey blue

#define DOMCOLOR DOMWGT_COLOR()
#define ACCCOLOR ACCWGT_COLOR()
#define WINNY_BACKGROUND_DOMCOLOR DOMWGT_COLOR()
#define WINNY_BACKGROUND_ACCCOLOR ACCWGT_COLOR()
#define WINNY_BUTTON_COLOR fl_rgb_color(233,233,233)

//font themes;
//inline Fl_Color FONT_COLOR_DOM() { return fl_rgb_color(102,102,102);} //dark gray
inline Fl_Fontsize DOMFONT_SIZE() {return 12;};   
inline Fl_Color DOMFONT_COLOR() { return fl_rgb_color(59,59,59);}//dark drk gray
inline Fl_Color ACCFONT_COLOR(){return fl_rgb_color(61, 122, 184);};
inline Fl_Color ACCFONT_COLOR2(){return fl_rgb_color(204, 102, 0);}; 

#define DOMFONTCOLOR DOMFONT_COLOR()
#define ACCFONTCOLOR ACCFONT_COLOR() 
#define ACCFONTCOLOR2 ACCFONT_COLOR2()

//more specific aliases for font color
#define WINNY_LINKTEXT_COLOR ACCFONT_COLOR()
#define WINNY_NORMALTEXT_COLOR DOMFONT_COLOR()
#define WINNY_MAINTITLETEXT_COLOR  fl_rgb_color(148, 185, 222)
#define WINNY_TITLETEXT_COLOR ACCFONT_COLOR2()
#define WINNY_SUBTITLETEXT_COLOR DOMFONT_COLOR()

#define WINNY_NORMALFONT FL_HELVETICA
#define WINNY_BOLDFONT  FL_HELVETICA_BOLD

#define WINNY_NORMALTEXT_FONTSIZE 11
#define WINNY_TITLETEXT_FONTSIZE 14
#define WINNY_SUBTITLETEXT_FONTSIZE 12


//Selection
 inline Fl_Color SELECTION_BACKCOLOR() {return fl_rgb_color(238,238,246);}//white blue (197,222,252)
 inline Fl_Color SELECTION_BACKCOLOR2() {return fl_rgb_color(242,247,253);}
 inline Fl_Color SELECTION_BORDERCOLOR() {return fl_rgb_color(125,162,206);}
 
//window
inline Fl_Color WINDOW_COLOR(){return fl_rgb_color(247, 247, 247);} 


//main menue:
inline Fl_Color MENUBAR_COLOR(){return fl_rgb_color(233,230,236);}
inline Fl_Color MENU_COLOR() {return fl_rgb_color(251,251,251); }

//GRID LINES
inline Fl_Color GRIDLINE_COLOR(){return fl_rgb_color(192,192,192);}//dark gray
inline Fl_Color GRIDLINE_COLOR2(){return fl_rgb_color(228,240,254);}//pale grayblue
inline Fl_Color GRIDLINE_COLOR3(){return fl_rgb_color(160, 160, 160);}//verydark gray

void set_winny_input_theme(Fl_Input_*w);
void set_winny_button_theme(Fl_Widget*w);
void set_winny_window_theme(Fl_Widget*w);
void set_winny_group_theme(Fl_Group*w);
void set_winny_scroll_theme(Fl_Scroll *w);

void init_ui(void);
void winny_thin_border_box(int x, int y, int w, int h, Fl_Color c );
void winny_thick_border_box(int x, int y, int w, int h, Fl_Color c );
void winny_thin_border_frame(int x, int y, int w, int h, Fl_Color c );
void winny_no_border_box(int x, int y, int w, int h, Fl_Color c );
void winny_bottom_border_box(int x, int y, int w, int h, Fl_Color c );
void winny_top_border_box(int x, int y, int w, int h, Fl_Color c );
void winny_thin_border_frame(int x, int y, int w, int h, Fl_Color c );

  #define WINNY_THIN_BORDERBOX (Fl_Boxtype)(FL_FREE_BOXTYPE)
  #define WINNY_THICK_BORDERBOX (Fl_Boxtype)(WINNY_THIN_BORDERBOX+1) //NOT IMPLEMENTED
  #define WINNY_THINDOWN_BORDERBOX (Fl_Boxtype)(WINNY_THIN_BORDERBOX+2)
  #define WINNY_THICK_BORDERBOX2 (Fl_Boxtype)(WINNY_THIN_BORDERBOX+3)
  #define WINNY_THIN_BORDERFRAME (Fl_Boxtype)(WINNY_THIN_BORDERBOX +4)
  #define WINNY_THINDOWN_BORDERFRAME (Fl_Boxtype)(WINNY_THIN_BORDERBOX +5)
  #define WINNY_NO_BORDERBOX (Fl_Boxtype)(WINNY_THIN_BORDERBOX +6)
  #define WINNY_TOP_BORDERBOX (Fl_Boxtype)(WINNY_THIN_BORDERBOX +7)
  #define WINNY_BOTTOM_BORDERBOX (Fl_Boxtype)(WINNY_THIN_BORDERBOX +8)
  #define WINNY_TOP_BORDERFRAME (Fl_Boxtype)(WINNY_THIN_BORDERBOX +9)

#endif