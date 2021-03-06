#ifndef DEMO_H
#define DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <Arduino.h>
#include <lvgl.h>



/*********************
 *      DEFINES
 *********************/
#define PIN_LEFT  21
#define PIN_RIGHT  3
#define PIN_ENTER  22
#define PIN_MENU    4

#define LV_USE_DEMO1 0
#define LV_USE_DEMO2 0
#define LV_USE_DEMO3 0

#define LV_USE_DEMO5    0
#define LV_USE_DEMO6    0
#define LV_USE_DEMO7    0
#define LV_USE_DEMO8    0
#define LV_USE_DEMO9    1
#define LV_USE_DEMO_TEST 0

#define LV_USE_DEMO_TEST 0


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a demo application
 */
void demo1_create(void);//tab
void demo2_create(void);//simple button,persian font,SYMBOL,color
void demo3_create(void);//calender

void demo5_create(void);//menu
void demo6_create(void);//Mehdi menu
void demo7_create(void);//Table 
void demo8_create(void);//list 
void demo9_create(void);//list 

void demo_test_create(void);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif
