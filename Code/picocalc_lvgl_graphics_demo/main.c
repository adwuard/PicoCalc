/**
 * PicoCalc LVGL Graphics Demo
 * 
 * Demo App Uses LVGL to show demos on the PicoCalc.
 * Implements basic keyboard input and display driver. 
 * 
 * Author: HsuahHanLai
 * https://www.hsuanhanlai.com/
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include "lv_port_indev_picocalc_kb.h"
#include "lv_port_disp_picocalc_ILI9488.h"
#include "lvgl/demos/lv_demos.h"


#define ILI9488 1
// #define USE_DEFAULT_DEMO 1

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */


const unsigned int LEDPIN = 25;

int main()
{
    // Initialize standard I/O
    stdio_init_all();

    // Initialize LED
    gpio_init(LEDPIN);
    gpio_set_dir(LEDPIN, GPIO_OUT);

    // Initialize LVGL
    lv_init();

    // Initialize the custom display driver
    lv_port_disp_init();

    // Initialize the keyboard input device (implementation in lv_port_indev_kbd.c)
    lv_port_indev_init();



#ifdef USE_DEFAULT_DEMO
    // Initialize and run LVGL demo
    lv_demo_widgets(); // Replace with the correct demo function if needed
#else
    // Create a screen
    lv_obj_t *screen = lv_obj_create(NULL);

    // Create a status bar at the top
    lv_obj_t *status_bar = lv_obj_create(screen);
    lv_obj_set_size(status_bar, LV_HOR_RES, 25); // Full width, height 20 pixels
    lv_obj_align(status_bar, LV_ALIGN_TOP_MID, 0, 0); // Align at the top

    // Set the style of the status bar
    lv_obj_set_style_bg_color(status_bar, lv_color_hex(0x4287f5), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Add a label to the status bar
    lv_obj_t *status_label = lv_label_create(status_bar);
    lv_label_set_text(status_label, "PicoCalc x Deepseek");
    lv_obj_align(status_label, LV_ALIGN_LEFT_MID, 5, 0); // Align text to the left with some padding

    // Add a WiFi connected logo to the top right of the status bar
    lv_obj_t *wifi_logo = lv_label_create(status_bar);
    lv_label_set_text(wifi_logo, LV_SYMBOL_WIFI); // Use LVGL's built-in WiFi symbol
    lv_obj_align(wifi_logo, LV_ALIGN_RIGHT_MID, -5, 0); // Align to the right with some padding

    // Create a tab view
    lv_obj_t *tabview = lv_tabview_create(screen);
    lv_obj_set_size(tabview, LV_HOR_RES, LV_VER_RES - 20); // Adjust height to leave space for the status bar
    lv_obj_align(tabview, LV_ALIGN_TOP_MID, 0, 20); // Position below the status bar

    // Set the height of the tab buttons
    lv_obj_t *tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_height(tab_btns, 20); // Set tab button height to 20 pixels
    // Add tabs
    
    
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Agent");
    // Create a list for options

    lv_obj_t *list = lv_list_create(tab1);
    lv_obj_set_size(list, LV_HOR_RES - 10, LV_VER_RES - 50); // Adjust size to fit within the tab
    lv_obj_align(list, LV_ALIGN_TOP_MID, 0, 5); // Align the list within the tab

    // Add items to the list
    lv_obj_t *list_btn1 = lv_list_add_btn(list, NULL, "Lawyer Adviser");
    lv_obj_set_style_text_font(list_btn1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT); // Reduce font size
    lv_obj_t *list_btn2 = lv_list_add_btn(list, NULL, "David the Funny Guy");
    lv_obj_set_style_text_font(list_btn2, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT); // Reduce font size

    // Add "Select" and "Edit" buttons for each item
    lv_obj_t *select_btn1 = lv_btn_create(tab1);
    lv_obj_set_size(select_btn1, 60, 25); // Reduce button size
    lv_obj_align_to(select_btn1, list_btn1, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // Reduce horizontal spacing
    lv_obj_t *select_label1 = lv_label_create(select_btn1);
    lv_label_set_text(select_label1, "Select");
    lv_obj_set_style_text_font(select_label1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT); // Reduce font size
    lv_obj_center(select_label1);

    lv_obj_t *edit_btn1 = lv_btn_create(tab1);
    lv_obj_set_size(edit_btn1, 60, 25); // Reduce button size
    lv_obj_align_to(edit_btn1, select_btn1, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // Reduce horizontal spacing
    lv_obj_t *edit_label1 = lv_label_create(edit_btn1);
    lv_label_set_text(edit_label1, "Edit");
    lv_obj_set_style_text_font(edit_label1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT); // Reduce font size
    lv_obj_center(edit_label1);

    lv_obj_t *select_btn2 = lv_btn_create(tab1);
    lv_obj_set_size(select_btn2, 60, 25); // Reduce button size
    lv_obj_align_to(select_btn2, list_btn2, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // Reduce horizontal spacing
    lv_obj_t *select_label2 = lv_label_create(select_btn2);
    lv_label_set_text(select_label2, "Select");
    lv_obj_set_style_text_font(select_label2, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT); // Reduce font size
    lv_obj_center(select_label2);

    lv_obj_t *edit_btn2 = lv_btn_create(tab1);
    lv_obj_set_size(edit_btn2, 60, 25); // Reduce button size
    lv_obj_align_to(edit_btn2, select_btn2, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // Reduce horizontal spacing
    lv_obj_t *edit_label2 = lv_label_create(edit_btn2);
    lv_label_set_text(edit_label2, "Edit");
    lv_obj_set_style_text_font(edit_label2, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT); // Reduce font size
    lv_obj_center(edit_label2);



    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Chat");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Settings");

    // Add content to the tabs if needed
    lv_obj_t *label1 = lv_label_create(tab1);
    lv_label_set_text(label1, "Agent tab content");

    lv_obj_t *label2 = lv_label_create(tab2);
    lv_label_set_text(label2, "Chat tab content");

    lv_obj_t *label3 = lv_label_create(tab3);
    lv_label_set_text(label3, "Settings tab content");


    // Create a text box in the Chat tab
    lv_obj_t *textbox = lv_textarea_create(tab2);
    lv_obj_set_size(textbox, 200, 100); // Set size of the text box
    lv_obj_align(textbox, LV_ALIGN_CENTER, 0, 0); // Center the text box in the Chat tab

    // Create a button
    lv_obj_t *button = lv_btn_create(screen);
    lv_obj_set_size(button, LV_HOR_RES, 20); // Set width to full screen and height to 20 pixels
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, 0); // Align the button at the bottom center

    // Set the button's style to have a blue background
    lv_obj_set_style_bg_color(button, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Add a label to the button
    lv_obj_t *btn_label = lv_label_create(button);
    lv_label_set_text(btn_label, "Send");
    lv_obj_center(btn_label); // Center the label on the button


    // Enable keyboard input for the text box
    lv_textarea_set_placeholder_text(textbox, "Enter text...");
    lv_textarea_set_one_line(textbox, true); // Set to single-line mode

    // Load the screen
    lv_scr_load(screen);
#endif

    // Main loop
    while (1)
    {
        lv_timer_handler();
        lv_tick_inc(5); // Increment LVGL tick by 5 milliseconds
        sleep_ms(1); // Sleep for 5 milliseconds}
    }
}
