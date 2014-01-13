#include "pebble.h"
#include "math.h"

static Window *window;
static Layer *layer;
static TextLayer *text_layer;
static int day = 1;

const int MINS_IN_HOUR = 60;

static int get_day(void){
  time_t timval=time(NULL);
  struct tm tims=*(localtime(&timval));
  int month = tims.tm_mon + 1;
  int cur_day = tims.tm_mday;

  APP_LOG(APP_LOG_LEVEL_DEBUG, "month: %d", month);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "day: %d", cur_day);
  if(month == 1){
    if(cur_day == 7 || cur_day == 9 || cur_day == 13 || cur_day == 15 || cur_day == 17 || cur_day == 22 || cur_day == 24 || cur_day == 24 || cur_day == 28 || cur_day == 30){
      return 1;
    }
  }
  if(month == 2){
    if(cur_day == 3 || cur_day == 5 || cur_day == 7 || cur_day == 11 || cur_day == 13 || cur_day == 17 || cur_day == 19 || cur_day == 21 || cur_day == 25 || cur_day == 27){
      return 1;
    }
  }
  if(month == 3){
    if(cur_day == 3 || cur_day == 5 || cur_day == 7 || cur_day == 18 || cur_day == 20 || cur_day == 24 || cur_day ==  26 || cur_day == 28){
      return 1;
    }
  }
  return 2;
}

static void highlight_class(int _day, int time1, int time2){
  time_t timval=time(NULL);
  struct tm tims=*(localtime(&timval));
  int cur_time = tims.tm_hour * MINS_IN_HOUR + tims.tm_min;

  if((cur_time > time1 && cur_time < time2) && (_day == 0 || _day == day)){
    text_layer_set_background_color(text_layer, GColorBlack);
    text_layer_set_text_color(text_layer, GColorWhite);
  }else{
    text_layer_set_background_color(text_layer, GColorWhite);
    text_layer_set_text_color(text_layer, GColorBlack);
  }
}

static void update_layer_callback(Layer *layer, GContext* ctx) {
  Layer *window_layer = window_get_root_layer(window);

  GRect bounds = layer_get_frame(layer);

  text_layer = text_layer_create((GRect) { .origin = {0, 10}, .size = { bounds.size.w, 20 } });
  highlight_class(0, 8*MINS_IN_HOUR+50, 9*MINS_IN_HOUR+50);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text(text_layer, "Latin");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  //column 1
  text_layer = text_layer_create((GRect) { .origin = {0, 30}, .size = { bounds.size.w/2, 20 } });
  highlight_class(1, 9*MINS_IN_HOUR+55, 11*MINS_IN_HOUR+20);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text(text_layer, "Env Sci");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  //column 2
  text_layer = text_layer_create((GRect) { .origin = {bounds.size.w - bounds.size.w/2, 30}, .size = { bounds.size.w/2, 20 } });
  highlight_class(2, 9*MINS_IN_HOUR+55, 11*MINS_IN_HOUR+20);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text(text_layer, "Comp Sci");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  //column 1
  text_layer = text_layer_create((GRect) { .origin = {0, 60}, .size = { bounds.size.w/2, 20 } });
  highlight_class(1, 11*MINS_IN_HOUR+25, 13*MINS_IN_HOUR+35);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text(text_layer, "History");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  //column 2
  text_layer = text_layer_create((GRect) { .origin = {bounds.size.w - bounds.size.w/2, 60}, .size = { bounds.size.w/2, 20 } });
  highlight_class(2, 11*MINS_IN_HOUR+25, 13*MINS_IN_HOUR+35);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text(text_layer, "IB Res");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  //column 1
  text_layer = text_layer_create((GRect) { .origin = {0, 90}, .size = { bounds.size.w/2, 20 } });
  highlight_class(1, 13*MINS_IN_HOUR+40, 15*MINS_IN_HOUR+5);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text(text_layer, "English");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  //column 2
  text_layer = text_layer_create((GRect) { .origin = {bounds.size.w - bounds.size.w/2, 90}, .size = { bounds.size.w/2, 20 } });
  highlight_class(2, 13*MINS_IN_HOUR+40, 15*MINS_IN_HOUR+5);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text(text_layer, "Math");
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

}
static TextLayer *timer_text_layer;
static Layer *window_layer;
static GRect bounds;
static time_t timval;
static struct tm tims;
static void setup_update_time(void){
  timval=time(NULL);
  tims=*(localtime(&timval));
  window_layer = window_get_root_layer(window);
  bounds = layer_get_frame(layer);
  timer_text_layer = text_layer_create((GRect) { .origin = {0, 120}, .size = { bounds.size.w, bounds.size.h-120 } });
  text_layer_set_background_color(timer_text_layer, GColorWhite);
  text_layer_set_text_color(timer_text_layer, GColorBlack);
  text_layer_set_text_alignment(timer_text_layer, GTextAlignmentCenter);
  text_layer_set_font(timer_text_layer, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
  text_layer_set_text(timer_text_layer, "-");
  layer_add_child(window_layer, text_layer_get_layer(timer_text_layer));
}

/*static void update_time(void *data){


  //int cur_time = tims.tm_hour * MINS_IN_HOUR + tims.tm_min;
  int i = tims.tm_hour;
  if(i > 12){
    i = i-12;
  }
  static char hour[] = "24";
  snprintf(hour, sizeof(hour), "%d", i);
  i = tims.tm_min;
  static char min[] = "60";
  snprintf(min, sizeof(min), "%d", i);
  i = tims.tm_sec;
  static char sec[] = "60";
  snprintf(sec, sizeof(sec), "%d", i);

  static char str[] = "00:00:00:";
  strcpy(str, hour);
  strcat(str, ":");
  strcat(str, min);
  strcat(str, ":");
  strcat(str, sec);


  text_layer_set_text(timer_text_layer, str);
  timer2 = app_timer_register(1000 , update_time, NULL);
}*/
unsigned int times[8] = { 8*3600+50*60,
                       9*3600+50*60,
                       9*3600+55*60,
                       11*3600+20*60,
                       11*3600+25*60,
                       13*3600+35*60,
                       13*3600+40*60,
                       15*3600+5*60 };


void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  // Need to be static because they're used by the system later.
  static char time_text[] = "00:00:00";
  static char date_text[] = "Xxxxxxxxx 00";

  char *time_format;

 /*static struct tm *target_time;
    target_time->tm_sec = tick_time->tm_sec;
    target_time->tm_min = tick_time->tm_min;
    target_time->tm_hour = tick_time->tm_hour;
    target_time->tm_mon = tick_time->tm_mon;
    target_time->tm_year = tick_time->tm_year;
    target_time->tm_wday = tick_time->tm_wday;
    target_time->tm_yday = tick_time->tm_yday;
    target_time->tm_isdst = tick_time->tm_isdst;

  double diff = target_time - tick_time;
  */

 // tick_time->tm_hour = 4; floor(diff/3600);
  

  int tar_time = 0;
  unsigned int cur_time = (tick_time->tm_hour * 3600) + (tick_time->tm_min * 60) + tick_time->tm_sec;

  for(unsigned int i = 0; i < sizeof(times); i++){
    if(cur_time < times[i]){
      tar_time = times[i];
      break;
    }
  }
  if(cur_time > times[7]){
    tar_time = (24 * 3600);
  }
  
  int diff = floor(tar_time - cur_time);

  tick_time->tm_hour = floor(diff/3600);
  if(cur_time > times[7]){
    tick_time->tm_hour = 7;
  }
  tick_time->tm_min = ((int)floor(diff/60))%60;
  tick_time->tm_sec = diff%60;

  // TODO: Only update the date when it's changed.
  strftime(date_text, sizeof(date_text), "%B %e", tick_time);
  text_layer_set_text(timer_text_layer, date_text);


  
  time_format = "%I:%M:%S";
  if(tick_time->tm_hour == 0){
    time_format = "%M:%S";
  }

  strftime(time_text, sizeof(time_text), time_format, tick_time);

  // Kludge to handle lack of non-padded hour format string
  // for twelve hour clock.
  if (!clock_is_24h_style() && (time_text[0] == '0')) {
    memmove(time_text, &time_text[1], sizeof(time_text) - 1);
  }

  text_layer_set_text(timer_text_layer, time_text);
}

void handle_deinit(void) {
  tick_timer_service_unsubscribe();
  layer_destroy(layer);
  window_destroy(window);
}

void handle_init(void) {
  window = window_create();
  window_stack_push(window, true /* Animated */);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, update_layer_callback);
  layer_add_child(window_layer, layer);

  day = get_day();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "global day: %d", day);
  setup_update_time();

  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
  // TODO: Update display here to avoid blank display on launch?
}
int main(void) {
  handle_init();

  app_event_loop();
  
  handle_deinit();
}
