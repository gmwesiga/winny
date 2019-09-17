#include <FlCashFlowDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>
#include <WinnyUserPrompts.H>
#include <gmtime.h>

using utils::Time;

void getDatecb(Fl_Widget*o, void* d){
    Time t;
    PromptUser::getDate(&t);
    ((Fl_Output*)o)->value(t.to_string().c_str());
};

FlCashFlowDisplay::FlCashFlowDisplay()
:Fl_Group(DCX(0),DCY(0),CONTENT_AREA.W,CONTENT_AREA.H)
{
    begin();
    box(WINNY_NO_BORDERBOX);
    color(WINDOW_COLOR());
    int comMenuY,comMenuWa, comMenuWb,comMenuH;
    comMenuY = 32;
    comMenuWa = 88;
    comMenuWb = 56;
    comMenuH = SLWH;
    optCashFlowType = new Fl_Choice(DCX(195),DCY(comMenuY),comMenuWa, comMenuH,"Type");
   // DCX(2),DCY(comMenuY),98, comMenuH
    optCashFlowType->add("Chronological By Transactions");
    optCashFlowType->add("Semantically");
    optCashFlowType->align(FL_ALIGN_TOP_LEFT);
    set_winny_button_theme(optCashFlowType);
    optCashFlowType->textcolor(WINNY_NORMALTEXT_COLOR);
    optCashFlowType->textsize(WINNY_NORMALTEXT_FONTSIZE);
    optCashFlowType->color(WINNY_BACKGROUND_DOMCOLOR);
    optCashFlowType->value(0);
    optCashFlowType->down_box(WINNY_THICK_BORDERBOX);
    Time t;
    txtBeginDate = new Fl_Output(DCX(2),DCY(comMenuY),98, comMenuH,"Begin Date");
    set_winny_input_theme(txtBeginDate);
    txtBeginDate->value(t.sdate().c_str());
    txtBeginDate->callback(getDatecb);
    txtBeginDate->when(FL_WHEN_NOT_CHANGED|FL_WHEN_ENTER_KEY_ALWAYS);
    txtEndDate = new Fl_Output(DCX(104),DCY(comMenuY),comMenuWa, comMenuH, "End Date");
    set_winny_input_theme(txtEndDate);
    txtEndDate->value(txtBeginDate->value());
    txtEndDate->callback(getDatecb);
    txtEndDate->when(FL_WHEN_NOT_CHANGED|FL_WHEN_ENTER_KEY_ALWAYS);
    btnRefresh = new Fl_Button (DCX(288),DCY(comMenuY),comMenuWb, comMenuH, "Refresh");
    set_winny_button_theme(btnRefresh);
    btnPrint = new Fl_Button (DCX(343),DCY(comMenuY),comMenuWb, comMenuH,"Print");
    set_winny_button_theme(btnPrint);
    btnShare = new Fl_Button(DCX(398),DCY(comMenuY),comMenuWb, comMenuH, "Share");
    set_winny_button_theme(btnShare);
    vwCashFlow = new dataset_view(DCX(1),DCY(65),CONTENT_AREA2.W, CONTENT_AREA2.H);
    vwCashFlow->box(WINNY_TOP_BORDERBOX);
    resizer = new Fl_Box(CONTENT_AREA2.W - 10,319,1,1);
    resizable(resizer);
    end();

}



UIname FlCashFlowDisplay::id(){
    return NAME_CASH_FLOW_SCREEN;
}


void FlCashFlowDisplay::show(){
    Fl_Group::show();
}

void FlCashFlowDisplay::update(){
    return;
}


void FlCashFlowDisplay::hide(){
    Fl_Group::hide();
}



void FlCashFlowDisplay::writeBuff(MemAddress buff){
    buff = nullptr;
}