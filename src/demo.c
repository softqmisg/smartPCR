#include <Arduino.h>
#include <time.h>
#include "demo.h"
extern lv_indev_t *my_indev;
#if LV_USE_DEMO_TEST
lv_obj_t* switch_menu;
static void switch_menu_handler(lv_event_t *e)
{
    lv_obj_t * obj = lv_event_get_target(e);  
    lv_obj_t *label=lv_event_get_user_data(e);  
    if(lv_obj_has_state(obj,LV_STATE_CHECKED))
    {
        lv_label_set_text(label,"checked");
    }
    else{
        lv_label_set_text(label,"unchecked");

    }
}
static void btn_handler(lv_obj_t *e)
{
    if(lv_obj_has_state(switch_menu,LV_STATE_CHECKED))
           lv_obj_clear_state(switch_menu,LV_STATE_CHECKED);
    else
        lv_obj_add_state(switch_menu,LV_STATE_CHECKED);
        lv_event_send(switch_menu,LV_EVENT_CLICKED,0);
}
void  demo_test_create(){


    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(my_indev,g); 

    lv_obj_t *label=lv_label_create(lv_scr_act());
    lv_obj_set_pos(label,100,0);
    switch_menu = lv_switch_create(lv_scr_act());
    lv_obj_add_event_cb(switch_menu,switch_menu_handler,LV_EVENT_CLICKED,label);
    lv_obj_set_pos(switch_menu,100,50);

    lv_obj_t *btn=lv_btn_create(lv_scr_act());
      lv_obj_set_pos(btn,100,100);
    lv_obj_add_event_cb(btn,btn_handler,LV_EVENT_CLICKED,0);
    lv_obj_t *lbl_btn=lv_label_create(btn);
    lv_label_set_text(lbl_btn,"press");
}
#endif
#if LV_USE_DEMO9
LV_FONT_DECLARE(my_symbols);
#define THERMO1 	"\xEF\x9D\xAB"
#define THERMO2 	"\xEF\x9D\xA9"
#define THERMO_3_4 "\xEF\x8B\x88"
static lv_obj_t * chart_one;
static lv_obj_t * chart_two;
static lv_obj_t * chart_three;

static lv_chart_series_t * ser_one;
static lv_chart_series_t * ser_two;
static lv_chart_series_t * ser_three;
void chart_task(lv_timer_t * timer);
void time_date_handler(lv_timer_t *timer);
static double point_one = 0;
static char point_two = 0;
static char point_three = 0;
#define NUMPOINTS_H   240
#define NUMPOINTS_V   150
#define VIEW_TIME   0.4//s //CYCLE in VIEW=0.4*freq
void demo9_create(void){

    static lv_coord_t col_dsc[] = {70, 80, 80,60, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {30, 75, 75,30, LV_GRID_TEMPLATE_LAST};

    lv_obj_t * cont = lv_obj_create(lv_scr_act());
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    lv_obj_set_size(cont, 320, 240);
    lv_obj_center(cont);    
    lv_obj_clear_flag(cont,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(cont,0,0);
    lv_obj_set_style_bg_color(cont, lv_palette_darken(LV_PALETTE_LIGHT_BLUE,0), 0);
    lv_obj_set_style_bg_grad_color(cont, lv_palette_darken(LV_PALETTE_LIGHT_BLUE,1), 0);
    lv_obj_set_style_bg_grad_dir(cont, LV_GRAD_DIR_VER, 0);

    lv_obj_t * obj;
    lv_obj_t *label;

    obj = lv_obj_create(cont);
    lv_obj_set_style_pad_all(obj,0,0);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 4,LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_clear_flag(obj,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1), 0);
    lv_obj_set_style_bg_grad_color(obj, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,3), 0);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, 0); 
        label=lv_label_create(obj);
        lv_label_set_text(label,LV_SYMBOL_WIFI"\t"LV_SYMBOL_BLUETOOTH "\t"LV_SYMBOL_SD_CARD "\t"LV_SYMBOL_GPS "\t"LV_SYMBOL_BATTERY_3);
        lv_obj_center(label);
        lv_obj_set_style_pad_all(label,0,0);

    obj = lv_obj_create(cont);
    lv_obj_set_style_pad_all(obj,0,0);
    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 3, 1,LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_clear_flag(obj,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_palette_lighten(LV_PALETTE_LIGHT_GREEN,1), 0);
    lv_obj_set_style_bg_grad_color(obj, lv_palette_lighten(LV_PALETTE_LIGHT_GREEN,3), 0);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, 0);    
        label=lv_label_create(obj);
        lv_obj_set_style_text_font(label,&my_symbols,0);
        lv_label_set_text(label,THERMO1);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_GREEN,4),0);
        lv_obj_align(label,LV_ALIGN_TOP_RIGHT,0,0);
        label=lv_label_create(obj);
        lv_label_set_text_fmt(label,"%.1f",37.0);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_GREEN,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_28,0);
        lv_obj_center(label);
        label=lv_label_create(obj);
        lv_label_set_text(label,"??C");
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_GREEN,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_14,0);
        lv_obj_align(label,LV_ALIGN_BOTTOM_RIGHT,0,0);
        label=lv_label_create(obj);
        lv_label_set_text_fmt(label,"%.1f",37.5);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_GREEN,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_14,0);
        lv_obj_align(label,LV_ALIGN_TOP_LEFT,0,0);
        label=lv_label_create(obj);
        lv_label_set_text_fmt(label,"%.1f",36.5);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_GREEN,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_14,0);
        lv_obj_align(label,LV_ALIGN_BOTTOM_LEFT,0,0);

    obj = lv_obj_create(cont);
    lv_obj_set_style_pad_all(obj,0,0);
    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 3, 1,LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_clear_flag(obj,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_palette_lighten(LV_PALETTE_RED,1), 0);
    lv_obj_set_style_bg_grad_color(obj, lv_palette_lighten(LV_PALETTE_RED,3), 0);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, 0);  
        label=lv_label_create(obj);
        lv_label_set_text(label,LV_SYMBOL_TINT);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_RED,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_20,0);
        lv_obj_align(label,LV_ALIGN_TOP_RIGHT,0,0);
        label=lv_label_create(obj);
        lv_label_set_text_fmt(label,"%.1f",45.5);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_RED,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_28,0);
        lv_obj_center(label);
        label=lv_label_create(obj);
        lv_label_set_text(label,"\%");
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_RED,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_14,0);
        lv_obj_align(label,LV_ALIGN_BOTTOM_RIGHT,0,0);
        label=lv_label_create(obj);
        lv_label_set_text_fmt(label,"%.1f",65.0);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_RED,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_14,0);
        lv_obj_align(label,LV_ALIGN_TOP_LEFT,0,0);
        label=lv_label_create(obj);
        lv_label_set_text_fmt(label,"%.1f",25.0);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_RED,4),0);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_14,0);
        lv_obj_align(label,LV_ALIGN_BOTTOM_LEFT,0,0);

    obj = lv_obj_create(cont);
    lv_obj_set_style_pad_all(obj,0,0);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 3,LV_GRID_ALIGN_STRETCH, 1, 2);
    lv_obj_set_style_bg_color(obj, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1), 0);
    lv_obj_set_style_bg_grad_color(obj, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,3), 0);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, 0);     
        chart_one = lv_chart_create(obj);
        lv_obj_set_size(chart_one, NUMPOINTS_H, NUMPOINTS_V);//240,150
        lv_obj_set_style_pad_all(chart_one,0,0);
        lv_obj_align(chart_one,  LV_ALIGN_CENTER, 0, 0);
        lv_chart_set_range(chart_one, LV_CHART_AXIS_PRIMARY_Y,-20, 20);
        lv_chart_set_type(chart_one, LV_CHART_TYPE_LINE);
        lv_chart_set_point_count(chart_one, NUMPOINTS_H);
        lv_obj_set_style_opa(chart_one, LV_OPA_70,0);
        lv_chart_set_div_line_count(chart_one,NUMPOINTS_V/20+1,NUMPOINTS_H/10+1);
        lv_obj_set_style_size(chart_one, 0, LV_PART_INDICATOR); /*point indicator*/
        lv_obj_set_style_line_width(chart_one, 3, LV_PART_ITEMS);   /*width the lines*/
        lv_obj_set_style_bg_color(chart_one, lv_palette_darken(LV_PALETTE_BLUE,3), 0);
        lv_obj_set_style_bg_grad_color(chart_one, lv_palette_darken(LV_PALETTE_AMBER,1), 0);
        lv_obj_set_style_bg_grad_dir(chart_one, LV_GRAD_DIR_VER, 0); 


    // obj = lv_obj_create(cont);
    // lv_obj_set_style_pad_all(obj,0,0);
    // lv_obj_clear_flag(obj,LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    // lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 3,LV_GRID_ALIGN_STRETCH, 2, 1);
    //     chart_two = lv_chart_create(obj);
    //     lv_chart_set_type(chart_two, LV_CHART_TYPE_LINE);
    //     lv_obj_align(chart_two,  LV_ALIGN_TOP_MID, 0, 0);
    //     lv_obj_set_style_opa(chart_two, LV_OPA_70,0);
    //     lv_chart_set_range(chart_two, LV_CHART_AXIS_PRIMARY_Y,0, 40);
 
   lv_obj_t *obj_buttom_line = lv_obj_create(cont);
    lv_obj_set_style_pad_all(obj_buttom_line,0,0);
    lv_obj_clear_flag(obj_buttom_line,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(obj_buttom_line, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(obj_buttom_line, LV_GRID_ALIGN_STRETCH, 0, 4,LV_GRID_ALIGN_STRETCH, 3, 1);
    lv_obj_set_style_bg_color(obj_buttom_line, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,3), 0);
    lv_obj_set_style_bg_grad_color(obj_buttom_line, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1), 0);
    lv_obj_set_style_bg_grad_dir(obj_buttom_line, LV_GRAD_DIR_VER, 0); 
        label=lv_label_create(obj_buttom_line);
        // lv_label_set_text(label,"???????????????? 12/11/1400 ");
        lv_obj_set_style_text_align(label,LV_TEXT_ALIGN_RIGHT,0);
        lv_obj_set_align(label,LV_ALIGN_LEFT_MID);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_BLUE,0),0);

        label=lv_label_create(obj_buttom_line);
        // lv_label_set_text(label,"13:42");
        lv_obj_set_style_text_align(label,LV_TEXT_ALIGN_RIGHT,0);
        lv_obj_set_align(label,LV_ALIGN_RIGHT_MID);
        lv_obj_set_style_text_color(label,lv_palette_darken(LV_PALETTE_BLUE,0),0);

	// /*Create a chart one*/
	// chart_one = lv_chart_create(tile2);
	// lv_chart_set_type(chart_one, LV_CHART_TYPE_LINE);
	// lv_obj_set_size(chart_one, 320, 80);
	// lv_obj_align(chart_one,  LV_ALIGN_TOP_MID, 0, 0);
	// lv_obj_set_style_opa(chart_one, LV_OPA_70,0);
	// // lv_obj_set_style_width(chart_one, 4,0);
	// lv_chart_set_range(chart_one, LV_CHART_AXIS_PRIMARY_Y,0, 80);

	// // /*Create a chart two*/
	// chart_two = lv_chart_create(tile2);
	// lv_obj_set_size(chart_two, 320, 80);
	// lv_obj_align(chart_two,  LV_ALIGN_CENTER, 0, 0);
	// lv_chart_set_type(chart_two, LV_CHART_TYPE_LINE);
	// lv_obj_set_style_opa(chart_two, LV_OPA_70,0);
	// // lv_obj_set_style_width(chart_two, 4,0);
    // lv_obj_set_style_line_width(chart_two, 0, LV_PART_ITEMS);   /*Remove the lines*/
	// lv_chart_set_range(chart_two, LV_CHART_AXIS_PRIMARY_Y,0, 80);

	// // /*Create a chart three*/
	// chart_three = lv_chart_create(tile2);
	// lv_obj_set_size(chart_three, 320, 80);
	// lv_obj_align(chart_three,  LV_ALIGN_BOTTOM_MID, 0, 0);
	// lv_chart_set_type(chart_three, LV_CHART_TYPE_LINE);
	// lv_obj_set_style_opa(chart_three, LV_OPA_70,0);
    // lv_obj_set_style_line_width(chart_three, 8, LV_PART_ITEMS);   /*Remove the lines*/
	// lv_chart_set_range(chart_three, LV_CHART_AXIS_PRIMARY_Y,0, 80);

	// /*Create a series three*/
	ser_one = lv_chart_add_series(chart_one, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);      /*Create a series one*/
	// ser_two = lv_chart_add_series(chart_two, lv_palette_main(LV_PALETTE_BLUE),LV_CHART_AXIS_PRIMARY_Y);    /*Create a series two*/
	// ser_three = lv_chart_add_series(chart_three, lv_palette_main(LV_PALETTE_GREEN),LV_CHART_AXIS_PRIMARY_Y); /*Create a series three*/

	// /*Create task for filling the Charts*/
    lv_timer_t * timer =lv_timer_create(chart_task,50,0);
    lv_timer_t *time_date=lv_timer_create(time_date_handler,1000,obj_buttom_line);
}
void time_date_handler(lv_timer_t *timer)
{
    lv_obj_t *obj=timer->user_data;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
//   printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
char wday[30];
    switch (tm.tm_wday)
    {
    case 0:
        /* code */
        lv_snprintf(wday,30,"????????????");
    break;
    case 1:
            lv_snprintf(wday,30,"????????????");
    break;
    case 2:
        lv_snprintf(wday,30,"???? ????????");
    break;
    case 3:
        lv_snprintf(wday,30,"????????????????");
    break;
    case 4:
        lv_snprintf(wday,30,"??????????????");
    break;
    case 5:
        lv_snprintf(wday,30,"????????");
    break;
    case 6:
        lv_snprintf(wday,30,"????????");
    break;

    default:
        break;
    }
    lv_obj_t *label=lv_obj_get_child(obj,0);
    lv_label_set_text_fmt(label,"%s %d-%02d-%02d", wday, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    label=lv_obj_get_child(obj,1);    
    lv_label_set_text_fmt(label,"%02d:%02d:%02d",tm.tm_hour, tm.tm_min, tm.tm_sec);

}

void chart_task(lv_timer_t * timer) //every 0.1s
{
	LV_UNUSED(timer);    /*Unused*/
    double freq=10.0;
    double dt=VIEW_TIME/NUMPOINTS_H;
	/*Summing point one*/
	point_one = point_one + dt;
	if(point_one >= 1/freq){
		point_one = 0;
	}
    
	/*Summing point two*/
	point_two = point_two + 2;
	if(point_two > 40){
		point_two = 0;
	}

	/*Summing point three*/
	point_three = point_three + 4;
	if(point_three > 80){
		point_three = 0;
	}

	lv_chart_set_next_value(chart_one, ser_one,20*sin(2*3.141596*freq*point_one));       /*set point_one to next*/
	// lv_chart_set_next_value(chart_two, ser_two, point_two);       /*set point_two to next*/
	// lv_chart_set_next_value(chart_three, ser_three, point_three); /*set point_three to next*/


}
#endif
#if LV_USE_DEMO8
lv_group_t * g;
lv_obj_t *keyboard;
static void ta_event_cb(lv_event_t * e)
{
     lv_event_code_t code = lv_event_get_code(e);
     lv_obj_t * ta = lv_event_get_target(e);
    // lv_obj_t * kb = lv_event_get_user_data(e);
     const char * txt = lv_textarea_get_text(ta);

    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(keyboard, ta);
        lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(keyboard, NULL);
        lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
    }

     if(code==LV_EVENT_VALUE_CHANGED)
     {
        if(txt[0] >= '0' && txt[0] <= '9' &&
            txt[1] >= '0' && txt[1] <= '9' )
        {
            if(txt[2] != ':')
            {
                lv_textarea_set_cursor_pos(ta, 2);
                lv_textarea_add_char(ta, ':');
            }
            else
            {
                if(txt[3] >= '0' && txt[3] <= '9' &&
                    txt[4] >= '0' && txt[4] <= '9' )
                    {
                        if(txt[5] != ':')
                        {
                            lv_textarea_set_cursor_pos(ta, 5);
                            lv_textarea_add_char(ta, ':');
                        }                        
                    }
            }
        } 
     }
      
}
static void float_btn_event_cb(lv_event_t * e)
{
    
     lv_obj_t *list=lv_event_get_user_data(e);
    int number_of_rows=lv_obj_get_child_cnt(list)-1;
    lv_obj_t *label=lv_list_add_text(list,0);
    lv_label_set_text_fmt(label,"%d",number_of_rows+1);
     lv_obj_set_style_border_width(label,2,0);
    lv_obj_set_style_border_color(label,lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,1),0);
    lv_obj_t *textarea=lv_textarea_create(label);
     lv_obj_set_width(textarea, 90);
    lv_textarea_set_one_line(textarea,true);
    lv_textarea_set_accepted_chars(textarea,"0123456789:");
    lv_textarea_set_max_length(textarea, 8);
    lv_obj_align(textarea, LV_ALIGN_TOP_LEFT,50, 0);
    lv_obj_set_flex_flow(textarea, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(textarea, ta_event_cb, LV_EVENT_ALL, 0);


    lv_obj_t *spinbox2=lv_spinbox_create(label);
    lv_obj_set_width(spinbox2, 80);
    lv_spinbox_set_range(spinbox2, -300, 1000);
    lv_spinbox_set_digit_format(spinbox2, 3, 2);
    lv_spinbox_step_prev(spinbox2);    lv_spinbox_step_prev(spinbox2);
    lv_obj_align(spinbox2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_flex_flow(spinbox2, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_state(lv_obj_get_child(list,number_of_rows+1),LV_STATE_CHECKED);
    lv_obj_scroll_to_view_recursive(list,LV_ANIM_ON);

}
void  demo8_create()
{
    g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(my_indev,g); 



    lv_obj_t *tv = lv_tileview_create(lv_scr_act());


    lv_obj_t * tile1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_LEFT);
    lv_obj_t * list = lv_list_create(tile1);
    lv_obj_set_size(list, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(list,lv_color_black(),0);

    keyboard= lv_keyboard_create(tile1);
    lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(keyboard, LV_OBJ_FLAG_FLOATING);
    // lv_obj_set_size(list, LV_PCT(100), LV_PCT(100));
    lv_keyboard_set_mode(keyboard,LV_KEYBOARD_MODE_NUMBER);

    /*Create floating btn*/
    lv_obj_t * float_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(float_btn, 50, 50);
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_add_event_cb(float_btn, float_btn_event_cb, LV_EVENT_CLICKED,list);
    lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_PLUS, 0);
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);   

    lv_obj_t *header_list=lv_list_add_text(list,"??????????");
    lv_obj_set_style_bg_color(header_list,lv_palette_lighten(LV_PALETTE_YELLOW,2),0);
    lv_obj_t *label=lv_label_create(header_list);
    lv_label_set_text(label,"????????");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT,80, 0);
    label=lv_label_create(header_list);    
    lv_label_set_text(label,"??????");
    lv_obj_align(label, LV_ALIGN_TOP_RIGHT, -20, 0);



}
#endif
#if LV_USE_DEMO7
#define ITEM_CNT 3
static void draw_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    /*If the cells are drawn...*/
    if(dsc->part == LV_PART_ITEMS ) {
        uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);
        if(row == 0) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_AMBER), dsc->rect_dsc->bg_color, LV_OPA_20);
            dsc->rect_dsc->bg_opa = LV_OPA_60;
        }
        if(row>0 && col==1)
        {
            bool chk = lv_table_has_cell_ctrl(obj, row, col, LV_TABLE_CELL_CTRL_CUSTOM_1);

            lv_draw_rect_dsc_t rect_dsc;
            lv_draw_rect_dsc_init(&rect_dsc);
            rect_dsc.bg_color = chk ? lv_theme_get_color_primary(obj) : lv_palette_lighten(LV_PALETTE_GREEN, 2);
            rect_dsc.radius = LV_RADIUS_CIRCLE;

            lv_area_t sw_area;
            sw_area.x1 = dsc->draw_area->x2 - 50;
            sw_area.x2 = sw_area.x1 + 40;
            sw_area.y1 = dsc->draw_area->y1 + lv_area_get_height(dsc->draw_area) / 2 - 10;
            sw_area.y2 = sw_area.y1 + 20;
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &sw_area);

            if(chk) {
                sw_area.x2 -= 2;
                sw_area.x1 = sw_area.x2 - 16;
            } else {
                sw_area.x1 += 2;
                sw_area.x2 = sw_area.x1 + 16;
            }
            sw_area.y1 += 2;
            sw_area.y2 -= 2;
            rect_dsc.bg_color = lv_color_make(0xff,0x32,0x42);
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &sw_area);
        }
    }
}
static void change_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    uint16_t col;
    uint16_t row;
    lv_table_get_selected_cell(obj, &row, &col);
    bool chk = lv_table_has_cell_ctrl(obj, row, 1, LV_TABLE_CELL_CTRL_CUSTOM_1);
    if(chk) lv_table_clear_cell_ctrl(obj, row, 1, LV_TABLE_CELL_CTRL_CUSTOM_1);
    else lv_table_add_cell_ctrl(obj, row, 1, LV_TABLE_CELL_CTRL_CUSTOM_1);
}
static void float_btn_event_cb(lv_event_t * e)
{
     lv_obj_t *table=lv_event_get_user_data(e);
    uint32_t rows= lv_table_get_row_cnt(table);
    lv_table_set_cell_value_fmt(table, rows, 0, "%"LV_PRIu32, rows );
    lv_obj_scroll_to_view_recursive(table, LV_ANIM_ON);
}
void  demo7_create()
{
    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(my_indev,g); 
    lv_obj_t *table=lv_table_create(lv_scr_act());
    lv_obj_add_flag(table,LV_OBJ_FLAG_SCROLLABLE);
    /*Set a smaller height to the table. It'll make it scrollable*/

    lv_obj_set_size(table,LV_SIZE_CONTENT,200);
    lv_table_set_col_width(table, 0, 150);
    // lv_table_set_row_cnt(table, ITEM_CNT); /*Not required but avoids a lot of memory reallocation lv_table_set_set_value*/
    lv_table_set_col_cnt(table, 2);  
    lv_obj_remove_style(table, NULL, LV_PART_ITEMS | LV_STATE_PRESSED);

    lv_table_set_cell_value_fmt(table, 0, 0, "Items" );
    lv_table_set_cell_value_fmt(table, 0, 1, "Checked" );

    for(uint32_t i = 1; i < ITEM_CNT; i++) {
        lv_table_set_cell_value_fmt(table, i, 0, "%"LV_PRIu32, i );
    }
    lv_obj_align(table, LV_ALIGN_CENTER, 0, -20);
    lv_obj_add_event_cb(table, draw_event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_add_event_cb(table, change_event_cb, LV_EVENT_VALUE_CHANGED, NULL);    

    /*Create floating btn*/
    lv_obj_t * float_btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(float_btn, 50, 50);
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_add_event_cb(float_btn, float_btn_event_cb, LV_EVENT_CLICKED,table);
    lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_PLUS, 0);
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);    

}
#endif

#if LV_USE_DEMO6
lv_obj_t *switch_menu;
// lv_obj_t *menu;
lv_obj_t *side_page,*root_page,*sub_home_page,*sub_wifi_page;
lv_group_t * g;
static void switch_menu_handler(lv_event_t * e);
static void anim_width_cb(void *var,int32_t v);
static lv_obj_t *create_root_page(lv_obj_t *parent);
static lv_obj_t *create_side_page(lv_obj_t *parent);
static lv_obj_t *create_sub_home(lv_obj_t *parent);
static lv_obj_t *create_sub_wifi(lv_obj_t *parent);
//======================================================================//
static void switch_menu_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_t *menu=lv_event_get_user_data(e);
    LV_LOG_USER("switch handler %d\n\r",code);
    if(code==LV_EVENT_PRESSED) {
        LV_LOG_USER("LV_EVENT_VALUE_CHANGED \n\r");

        if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
            LV_LOG_USER("LV_STATE_CHECKED \n\r");       
            lv_menu_clear_history(menu); /* Clear history because we will be showing the root page later */
            lv_menu_set_mode_root_back_btn(menu,LV_MENU_ROOT_BACK_BTN_DISABLED);
            lv_menu_set_page(menu, root_page);
            lv_menu_set_sidebar_page(menu, side_page);
            lv_obj_set_width(((lv_menu_t *)menu)->sidebar,110);
            lv_obj_set_width(((lv_menu_t *)menu)->sidebar_header_back_btn,lv_obj_get_style_width(side_page,0));

            // lv_obj_t *btn_back_label=lv_label_create(((lv_menu_t *)menu)->sidebar_header_back_btn);
            // lv_label_set_long_mode(btn_back_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
            // lv_obj_set_flex_grow(btn_back_label, 1);
            // lv_label_set_text(btn_back_label,"????????????"); 

            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, ((lv_menu_t *)menu)->sidebar);
            lv_anim_set_values(&a, 0, lv_obj_get_style_width(((lv_menu_t *)menu)->sidebar,0));
            lv_anim_set_time(&a, 500);
            lv_anim_set_exec_cb(&a, anim_width_cb);
            lv_anim_set_path_cb(&a, lv_anim_path_linear);
            lv_anim_start(&a);            
            // lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
        }else {
            // LV_LOG_USER("LV_STATE_UNCHECKED \n\r"); 
            // lv_anim_t a;
            // lv_anim_init(&a);
            // lv_anim_set_var(&a, ((lv_menu_t *)menu)->sidebar);
            // lv_anim_set_values(&a, lv_obj_get_style_width(((lv_menu_t *)menu)->sidebar,0),0);
            // lv_anim_set_time(&a, 1300);
            // lv_anim_set_exec_cb(&a, anim_width_cb);
            // lv_anim_set_path_cb(&a, lv_anim_path_linear);
            
            // lv_anim_start(&a);  
            lv_menu_set_mode_root_back_btn(menu,LV_MENU_ROOT_BACK_BTN_DISABLED);
            lv_menu_set_sidebar_page(menu, NULL);
            lv_menu_clear_history(menu); /* Clear history because we will be showing the root page later */
            lv_menu_set_page(menu, root_page);

        }    
    }    
}

static void home_btn_handler(lv_event_t *e)
{
    lv_group_focus_next(g);
    lv_group_focus_next(g);
    lv_group_focus_next(g);
    lv_group_focus_next(g);
    lv_group_focus_next(g);

}
static void wifi_btn_handler(lv_event_t *e)
{
    lv_obj_t *menu=lv_event_get_user_data(e);

    lv_group_focus_next(g);
    lv_group_focus_next(g);
    lv_group_focus_next(g);
    lv_group_focus_next(g);

    LV_LOG_USER("%d",lv_obj_get_child_cnt(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu),2)));

}
static void anim_width_cb(void *var,int32_t v)
{
    lv_obj_set_width(var,v);
}
static lv_obj_t *create_sub_home(lv_obj_t *parent)
{
    lv_obj_t *page=lv_menu_page_create(parent,NULL);
    lv_obj_set_style_pad_hor(page, lv_obj_get_style_pad_left(lv_menu_get_main_header(parent), 0), 0);
    lv_menu_separator_create(page);
    lv_obj_t *section = lv_menu_section_create(page);    
    lv_obj_t *btn=lv_btn_create(section);
    lv_obj_t *label=lv_label_create(btn);
    lv_label_set_text(label,"home");

    return page;    
}

static lv_obj_t *create_sub_wifi(lv_obj_t *parent)
{
    lv_obj_t *page=lv_menu_page_create(parent,NULL);
    lv_obj_set_style_pad_hor(page, lv_obj_get_style_pad_left(lv_menu_get_main_header(parent), 0), 0);

    lv_menu_separator_create(page);
    lv_obj_t *section = lv_menu_section_create(page);    
    lv_obj_t *btn=lv_btn_create(section);
    lv_obj_t *label=lv_label_create(btn);
    lv_label_set_text(label,"wifi");

    section = lv_menu_section_create(page);    
    label=lv_label_create(section);
    lv_label_set_text(label,"wifi me");

    section = lv_menu_section_create(page);    
    btn=lv_btn_create(section);
    label=lv_label_create(btn);
    lv_label_set_text(label,"check it");

    return page;    
}

static lv_obj_t *create_root_page(lv_obj_t *parent)
{
    lv_obj_t *page=lv_menu_page_create(parent,NULL);
    lv_obj_set_style_pad_hor(page, lv_obj_get_style_pad_left(lv_menu_get_main_header(parent), 0), 0);
    lv_menu_separator_create(page);
    lv_obj_t *section = lv_menu_section_create(page);    
    lv_obj_t *btn=lv_btn_create(section);
    lv_obj_t *label=lv_label_create(btn);
    lv_label_set_text(label,"test");
    return page;
}
static lv_obj_t *create_side_page(lv_obj_t *parent)
{

    sub_home_page=create_sub_home(parent);
    sub_wifi_page=create_sub_wifi(parent);


    static  lv_style_t btn_focuestyle;
    lv_style_init(&btn_focuestyle);
    lv_style_set_radius(&btn_focuestyle, 3);
    lv_style_set_bg_opa(&btn_focuestyle, LV_OPA_100);
    lv_style_set_bg_color(&btn_focuestyle, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,4));
    lv_style_set_outline_width(&btn_focuestyle, 1);
    lv_style_set_outline_color(&btn_focuestyle, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE,4));
    lv_style_set_pad_all(&btn_focuestyle, 0);
    lv_style_set_text_color(&btn_focuestyle, lv_palette_darken(LV_PALETTE_LIGHT_BLUE,1));

    
   static  lv_style_t btn_pressed;
    lv_style_init(&btn_pressed);
    lv_style_set_radius(&btn_pressed, 3);
    lv_style_set_bg_opa(&btn_pressed, LV_OPA_100);
    lv_style_set_bg_color(&btn_pressed, lv_palette_lighten(LV_PALETTE_GREY,3));
    lv_style_set_outline_width(&btn_pressed, 1);
    lv_style_set_outline_color(&btn_pressed, lv_palette_lighten(LV_PALETTE_GREY,3));
    lv_style_set_pad_all(&btn_focuestyle, 0);
    lv_style_set_text_color(&btn_pressed, lv_color_hex(0x0));

    lv_obj_t *page=lv_menu_page_create(parent,NULL);
    lv_obj_set_style_pad_hor(page, lv_obj_get_style_pad_left(lv_menu_get_main_header(parent), 0), 0);
        lv_obj_t *section1=lv_menu_section_create(page);
            lv_obj_t *con=lv_menu_cont_create(section1);
            lv_obj_set_style_pad_all(con, 0,0);
                lv_obj_t *btn_l=lv_btn_create(con);  
                lv_obj_remove_style_all(btn_l);
                lv_obj_add_style(btn_l,&btn_focuestyle,LV_STATE_FOCUSED);
                lv_obj_add_style(btn_l,&btn_pressed,LV_STATE_PRESSED);
                lv_obj_set_width(btn_l,lv_obj_get_style_width(section1,0));
                lv_menu_set_load_page_event(parent, btn_l, sub_home_page);
                lv_obj_add_event_cb(btn_l,home_btn_handler,LV_EVENT_CLICKED,NULL);
                    con=lv_menu_cont_create(btn_l);
                        lv_obj_t *img =lv_img_create(con);
                        lv_img_set_src(img,LV_SYMBOL_HOME);   
                        lv_obj_set_style_pad_right(img,1,1);
                        lv_obj_t *label = lv_label_create(con);
                        lv_label_set_text(label, "????????");
                        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
                        lv_obj_set_flex_grow(label, 1);

            con=lv_menu_cont_create(section1);
            lv_obj_set_style_pad_all(con, 0,0);
                btn_l=lv_btn_create(con);  
                lv_obj_remove_style_all(btn_l);
                lv_obj_add_style(btn_l,&btn_focuestyle,LV_STATE_FOCUSED);
                lv_obj_add_style(btn_l,&btn_pressed,LV_STATE_PRESSED);
                lv_obj_set_width(btn_l,lv_obj_get_style_width(section1,0));
                lv_menu_set_load_page_event(parent, btn_l, sub_wifi_page);
                lv_obj_add_event_cb(btn_l,wifi_btn_handler,LV_EVENT_CLICKED,parent);
                    con=lv_menu_cont_create(btn_l);
                        img =lv_img_create(con);
                        lv_img_set_src(img,LV_SYMBOL_WIFI);
                        label = lv_label_create(con);
                        lv_label_set_text(label, "WIFI");
                        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
                        lv_obj_set_flex_grow(label, 1);

            con=lv_menu_cont_create(section1);
            lv_obj_set_style_pad_all(con, 0,0);
                btn_l=lv_btn_create(con);  
                lv_obj_remove_style_all(btn_l);
                lv_obj_add_style(btn_l,&btn_focuestyle,LV_STATE_FOCUSED);
                lv_obj_add_style(btn_l,&btn_pressed,LV_STATE_PRESSED);
                lv_obj_set_width(btn_l,lv_obj_get_style_width(section1,0));
                // lv_group_add_obj(g,btn_l);  
                    con=lv_menu_cont_create(btn_l);
                        img =lv_img_create(con);
                        lv_img_set_src(img,LV_SYMBOL_GPS);
                        label = lv_label_create(con);
                        lv_label_set_text(label, "GPS");
                        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
                        lv_obj_set_flex_grow(label, 1);

        con=lv_menu_cont_create(page);
            label = lv_label_create(con);
            lv_label_set_text(label, "Others");
            lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_obj_set_flex_grow(label, 1);

        lv_obj_t *section2=lv_menu_section_create(page);
            con=lv_menu_cont_create(section2);
            lv_obj_set_style_pad_all(con, 0,0);
                btn_l=lv_btn_create(con);  
                lv_obj_remove_style_all(btn_l);
                lv_obj_add_style(btn_l,&btn_focuestyle,LV_STATE_FOCUSED);
                lv_obj_add_style(btn_l,&btn_pressed,LV_STATE_PRESSED);
                lv_obj_set_width(btn_l,lv_obj_get_style_width(section2,0));
                    con=lv_menu_cont_create(btn_l);
                        img =lv_img_create(con);
                        lv_img_set_src(img,LV_SYMBOL_BLUETOOTH);
                        label = lv_label_create(con);
                        lv_label_set_text(label, "BLUETOOTH");
                        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
                        lv_obj_set_flex_grow(label, 1);

            con=lv_menu_cont_create(section2);
            lv_obj_set_style_pad_all(con, 0,0);
                btn_l=lv_btn_create(con);  
                lv_obj_remove_style_all(btn_l);
                lv_obj_add_style(btn_l,&btn_focuestyle,LV_STATE_FOCUSED);
                lv_obj_add_style(btn_l,&btn_pressed,LV_STATE_PRESSED);
                lv_obj_set_width(btn_l,lv_obj_get_style_width(section2,0));
                // lv_group_add_obj(g,btn_l);  
                    con=lv_menu_cont_create(btn_l);
                        img =lv_img_create(con);
                        lv_img_set_src(img,LV_SYMBOL_KEYBOARD);
                        label = lv_label_create(con);
                        lv_label_set_text(label, "KEYBOARD");
                        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
                        lv_obj_set_flex_grow(label, 1);

    return page;
} 

void  demo6_create(){


     g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(my_indev,g); 

    lv_obj_t *menu=lv_menu_create(lv_scr_act());
    lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
    if(lv_color_brightness(bg_color) > 127) {
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 10), 0);
    }else{
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 50), 0);
    }
    lv_menu_set_mode_root_back_btn(menu,LV_MENU_ROOT_BACK_BTN_DISABLED);
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);
    // lv_obj_add_event_cb(menu, back_event_handler, LV_EVENT_CLICKED, 0);

   switch_menu = lv_switch_create(NULL);
    lv_obj_clear_state(switch_menu,LV_STATE_CHECKED);
    lv_obj_add_event_cb(switch_menu,switch_menu_handler,LV_EVENT_PRESSED,menu);
    lv_group_remove_obj(switch_menu);

    side_page=create_side_page(menu);
    root_page=create_root_page(menu);
    // sub_home_page=create_sub_home(menu);
    
    lv_menu_set_sidebar_page(menu,NULL);
    lv_menu_set_page(menu,root_page);
 
    LV_LOG_USER("starting demo\n");


}
#endif

#if LV_USE_DEMO5

enum {
    LV_MENU_ITEM_BUILDER_VARIANT_1,
    LV_MENU_ITEM_BUILDER_VARIANT_2
};
typedef uint8_t lv_menu_builder_variant_t;

static void back_event_handler(lv_event_t * e);
static void switch_handler(lv_event_t * e);
lv_obj_t * root_page;
static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                                        lv_menu_builder_variant_t builder_variant);
static lv_obj_t * create_slider(lv_obj_t * parent,
                                   const char * icon, const char * txt, int32_t min, int32_t max, int32_t val);
static lv_obj_t * create_switch(lv_obj_t * parent,
                                   const char * icon, const char * txt, bool chk);
lv_group_t * g;
void demo5_create(void)
{
     g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(my_indev,g); 

    lv_obj_t * menu = lv_menu_create(lv_scr_act());
    
    lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
    if(lv_color_brightness(bg_color) > 127) {
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 10), 0);
    }else{
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 50), 0);
    }
    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
    lv_obj_add_event_cb(menu, back_event_handler, LV_EVENT_CLICKED, menu);
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);

    lv_obj_t * cont;
    lv_obj_t * section;

    /*Create sub pages*/
    lv_obj_t * sub_mechanics_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_mechanics_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_mechanics_page);
    section = lv_menu_section_create(sub_mechanics_page);
    create_slider(section, LV_SYMBOL_SETTINGS, "Velocity", 0, 150, 120);
    create_slider(section, LV_SYMBOL_SETTINGS, "Acceleration", 0, 150, 50);
    create_slider(section, LV_SYMBOL_SETTINGS, "Weight limit", 0, 150, 80);

    lv_obj_t * sub_sound_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_sound_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_sound_page);
    section = lv_menu_section_create(sub_sound_page);
    create_switch(section, LV_SYMBOL_AUDIO, "Sound", false);

    lv_obj_t * sub_display_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_display_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_display_page);
    section = lv_menu_section_create(sub_display_page);
    create_slider(section, LV_SYMBOL_SETTINGS, "Brightness", 0, 150, 100);

    lv_obj_t * sub_software_info_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_software_info_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    section = lv_menu_section_create(sub_software_info_page);
    create_text(section, NULL, "Version 1.0", LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t * sub_legal_info_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_legal_info_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    section = lv_menu_section_create(sub_legal_info_page);
    for(uint32_t i=0; i<15; i++){
        create_text(section, NULL, "This is a long long long long long long long long long text, if it is long enough it may scroll.", LV_MENU_ITEM_BUILDER_VARIANT_1);
    }

    lv_obj_t * sub_about_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_about_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_about_page);
    section = lv_menu_section_create(sub_about_page);
    cont = create_text(section, NULL, "Software information", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_software_info_page);
    cont = create_text(section, NULL, "Legal information", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_legal_info_page);

    lv_obj_t * sub_menu_mode_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_menu_mode_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_menu_mode_page);
    section = lv_menu_section_create(sub_menu_mode_page);
    cont = create_switch(section, LV_SYMBOL_AUDIO, "Sidebar enable", true);
    lv_obj_add_event_cb(lv_obj_get_child(cont, 2), switch_handler, LV_EVENT_VALUE_CHANGED, menu);
    lv_group_add_obj(g,cont);

    /*Create a root page*/
    root_page = lv_menu_page_create(menu, "Settings");
    lv_obj_set_style_pad_hor(root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

    section = lv_menu_section_create(root_page);
    cont = create_text(section, LV_SYMBOL_SETTINGS, "Mechanics", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_mechanics_page);
    lv_group_add_obj(g,cont);

    cont = create_text(section, LV_SYMBOL_AUDIO, "Sound", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_sound_page);
    lv_group_add_obj(g,cont);
    
    cont = create_text(section, LV_SYMBOL_SETTINGS, "Display", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_display_page);
    lv_group_add_obj(g,cont);
    
    create_text(root_page, NULL, "Others", LV_MENU_ITEM_BUILDER_VARIANT_1);
    
    section = lv_menu_section_create(root_page);
    cont = create_text(section, NULL, "About", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_about_page);
        lv_group_add_obj(g,cont);

    cont = create_text(section, LV_SYMBOL_SETTINGS, "Menu mode", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_menu_mode_page);
    lv_group_add_obj(g,cont);

    lv_menu_set_sidebar_page(menu, root_page);

    // lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
}

static void back_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_t * menu = lv_event_get_user_data(e);

    if(lv_menu_back_btn_is_root(menu, obj)) {
        lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello", "Root back btn click.", NULL, true);
        lv_obj_center(mbox1);
    }
}

static void switch_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * menu = lv_event_get_user_data(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
            lv_menu_set_page(menu, NULL);
            lv_menu_set_sidebar_page(menu, root_page);
            lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
        }else {
            lv_menu_set_sidebar_page(menu, NULL);
            lv_menu_clear_history(menu); /* Clear history because we will be showing the root page later */
            lv_menu_set_page(menu, root_page);
        }
    }
}

static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                                        lv_menu_builder_variant_t builder_variant)
{
    lv_obj_t * obj = lv_menu_cont_create(parent);

    lv_obj_t * img = NULL;
    lv_obj_t * label = NULL;

    if(icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if(txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }

    if(builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }

    return obj;
}

static lv_obj_t * create_slider(lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max, int32_t val)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

    lv_obj_t * slider = lv_slider_create(obj);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_OFF);

    if(icon == NULL) {
        lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    }

    return obj;
}

static lv_obj_t * create_switch(lv_obj_t * parent, const char * icon, const char * txt, bool chk)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t * sw = lv_switch_create(obj);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);

    return obj;
}

#endif 
#if LV_USE_DEMO4
static void calendar_event_handler(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        if(lv_calendar_get_pressed_date(obj, &date)) {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
            lv_group_focus_obj(obj);
        }
    }
}
void demo4_create(){

    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(my_indev,g); 
    
    lv_obj_t *calendar=lv_calendar_create(lv_scr_act());
    lv_obj_set_size(calendar, 320, 185);
    lv_obj_set_pos(calendar,0,0);
    // lv_obj_align(calendar, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(calendar, calendar_event_handler, LV_EVENT_ALL, NULL);

    lv_calendar_set_today_date(calendar, 2021, 02, 23);
    lv_calendar_set_showed_date(calendar, 2021, 02);

    /*Highlight a few days*/
    static lv_calendar_date_t highlighted_days[3];       /*Only its pointer will be saved so should be static*/
    highlighted_days[0].year = 2021;
    highlighted_days[0].month = 02;
    highlighted_days[0].day = 6;

    highlighted_days[1].year = 2021;
    highlighted_days[1].month = 02;
    highlighted_days[1].day = 11;

    highlighted_days[2].year = 2022;
    highlighted_days[2].month = 02;
    highlighted_days[2].day = 22;

    lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);

#if LV_USE_CALENDAR_HEADER_DROPDOWN
    lv_calendar_header_dropdown_create(calendar);
#elif LV_USE_CALENDAR_HEADER_ARROW
    lv_calendar_header_arrow_create(calendar);
#endif
    // lv_calendar_set_showed_date(calendar, 2021, 10);   
    lv_obj_t *btn=lv_btn_create(lv_scr_act());
  // lv_obj_add_event_cb(btn2,event_handler_btn,LV_EVENT_ALL,NULL);
  lv_obj_set_width(btn, 70);
  lv_obj_set_height(btn, 32);
  lv_obj_set_pos(btn, 190, 190);

  lv_obj_t * label2 = lv_label_create(btn);
  lv_label_set_text(label2, "Goodbye");
  lv_obj_set_align(label2,LV_TEXT_ALIGN_CENTER);
}
#endif
#if LV_USE_DEMO3
static void roller_event_handler(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    // LV_LOG_USER("code:%d\n",(int)code);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected month: %s\n", buf);
    }    

}
void demo3_create(){
    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_set_group(my_indev,g);    
    lv_obj_t *my_roll=lv_roller_create(lv_scr_act());
    lv_roller_set_options(my_roll,
                        "January\n"
                        "February\n"
                        "March\n"
                        "April\n"
                        "May\n"
                        "June\n"
                        "July\n"
                        "August\n"
                        "September\n"
                        "October\n"
                        "November\n"
                        "December",
                        LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(my_roll, 4);
    lv_obj_center(my_roll);
    lv_obj_add_event_cb(my_roll, roller_event_handler, LV_EVENT_ALL, NULL);
    lv_group_focus_obj(my_roll);


}
#endif
#if LV_USE_DEMO1
lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *btn3;
lv_obj_t *label;

static void event_handler_btn( lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj=lv_event_get_target(e);
    // Serial.println(code);
    if(code == LV_EVENT_CLICKED) {
        if (obj == btn1)
          lv_label_set_text(label, "Hello");
        else if (obj == btn2)
          lv_label_set_text(label, "Goodbye");
        else if (obj == btn3)
          lv_label_set_text(label, "????????");         
    }
}
void demo1_create()
{
lv_group_t * g = lv_group_create();
  lv_group_set_default(g);
  lv_indev_set_group(my_indev,g);
  /*Create screen objects*/
  lv_obj_t *screenMain = lv_scr_act();
label=lv_label_create(screenMain);
  lv_label_set_recolor(label,true);
  lv_label_set_text(label,  LV_SYMBOL_OK "#00ff00 Apply #" "#0000ff \xef\x87\xab #" "#ff0000 \xef\x8a\x93 #");  //LV_SYMBOL_SD_CARD LV_SYMBOL_BLUETOOTH LV_SYMBOL_BATTERY_EMPTY);
  lv_obj_set_size(label, 240, 40);
  lv_obj_set_pos(label, 40, 150);
  lv_obj_set_style_text_font(label,&lv_font_montserrat_20,0 );
  // lv_obj_set_style_text_color(label,lv_color_hex(0xff0000),0);//LV_PALETTE_YELLOW
  // lv_obj_set_style_text_color(label,lv_palette_main(LV_PALETTE_GREEN),0);

    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_AMBER));
    lv_style_set_border_width(&style, 3);
    lv_style_set_border_opa(&style, LV_OPA_50);
    lv_style_set_border_side(&style, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT); //LV_BORDER_SIDE_FULL

  label = lv_label_create(screenMain);
  lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
  // lv_label_set_text(label, "???????? ????????: this is start");
  // lv_label_set_text(label, "???????? ????????1??????????2:this??????2");
  // lv_label_set_text(label, "?????????? ????????1?????????? 2 :this ?? ????2");
  lv_label_set_text(label, "???????? ???????? 1 ?? ???????? :this is us ?????? 2");
  lv_obj_set_align(label,LV_TEXT_ALIGN_CENTER);
  lv_obj_set_style_base_dir(label, LV_BASE_DIR_AUTO, 0);
  lv_obj_set_size(label, 310, 40);
  lv_obj_set_pos(label, 0, 180);
  lv_obj_set_style_text_font(label, &lv_font_dejavu_16_persian_hebrew, 0);
  lv_obj_add_style(label, &style, 0);

  label = lv_label_create(screenMain);
  lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
  lv_label_set_text(label, "Press a button");
  lv_obj_set_align(label,LV_TEXT_ALIGN_CENTER);
  lv_obj_set_style_base_dir(label, LV_BASE_DIR_AUTO, 0);
  lv_obj_set_style_text_font(label,&lv_font_dejavu_16_persian_hebrew,0 );
  lv_obj_set_size(label, 320, 40);
  lv_obj_set_pos(label, 0, 15);
  

  btn1 = lv_btn_create(screenMain);
  lv_obj_add_event_cb(btn1,event_handler_btn,LV_EVENT_ALL,NULL);
  lv_obj_set_width(btn1, 70);
  lv_obj_set_height(btn1, 32);
  lv_obj_set_pos(btn1, 32, 100);

  lv_obj_t * label1 = lv_label_create(btn1);
  lv_label_set_text(label1, "Hello");
 lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);


  btn2 = lv_btn_create(screenMain);
  lv_obj_add_event_cb(btn2,event_handler_btn,LV_EVENT_ALL,NULL);
  lv_obj_set_width(btn2, 70);
  lv_obj_set_height(btn2, 32);
  lv_obj_set_pos(btn2, 132, 100);

  lv_obj_t * label2 = lv_label_create(btn2);
  lv_label_set_text(label2, "Goodbye");
   lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);


  btn3 = lv_btn_create(screenMain);
  lv_obj_add_event_cb(btn3,event_handler_btn,LV_EVENT_ALL,NULL);
  lv_obj_set_width(btn3, 70);
  lv_obj_set_height(btn3, 32);
  lv_obj_set_pos(btn3, 232, 100);

  lv_obj_t * label3 = lv_label_create(btn3);
  lv_label_set_text(label3, "????????");
//   lv_obj_set_align(label3,LV_TEXT_ALIGN_CENTER);
   lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_base_dir(label3, LV_BASE_DIR_AUTO, 0);
  lv_obj_set_style_text_font(label3,&lv_font_dejavu_16_persian_hebrew,0 );
    
}
#endif
#if LV_USE_DEMO2
static void anim_x_cb(void * var, int32_t v)
{
    lv_obj_set_x((_lv_obj_t *)var, (lv_coord_t)v);
}

static void sw_event_cb(lv_event_t * e)
{
    lv_obj_t * sw = lv_event_get_target(e);
    lv_obj_t * label = (lv_obj_t *)lv_event_get_user_data(e);

    if(lv_obj_has_state(sw, LV_STATE_CHECKED)) {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, label);
        lv_anim_set_values(&a, lv_obj_get_x(label), 100);
        lv_anim_set_time(&a, 500);
        lv_anim_set_exec_cb(&a, anim_x_cb);
        lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
        lv_anim_start(&a);
    } else {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, label);
        lv_anim_set_values(&a, lv_obj_get_x(label), -lv_obj_get_width(label));
        lv_anim_set_time(&a, 500);
        lv_anim_set_exec_cb(&a, anim_x_cb);
        lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
        lv_anim_start(&a);
    }

}

void demo2_create()
{
lv_group_t * g = lv_group_create();
  lv_group_set_default(g);
  lv_indev_set_group(my_indev,g);
  /*Create screen objects*/
  lv_obj_t *screenMain = lv_scr_act();

    lv_obj_t * label = lv_label_create(screenMain);
    lv_label_set_text(label, "Hello animations!");
    lv_obj_set_pos(label, 100, 10);


    lv_obj_t * sw = lv_switch_create(screenMain);
    lv_obj_center(sw);
    lv_obj_add_state(sw, LV_STATE_CHECKED);
    lv_obj_add_event_cb(sw, sw_event_cb, LV_EVENT_VALUE_CHANGED, label);
}
#endif