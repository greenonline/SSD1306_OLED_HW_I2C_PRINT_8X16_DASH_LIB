#include "SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB.h"



SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB:: SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB(void) : SSD1306_OLED_HW_I2C_PRINT_8X16_LIB()
{

}

// Draw a vertical dashed line
void SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB::D_DRAW_VERT_DASHED(uint8_t xpos, uint8_t ypos, uint8_t length) {
    uint8_t ypage_start = ypos / 8;                         // determine starting page from pixel position
    uint8_t ypage_end = (ypos + length) / 8;                // determine last page from pixel position
    uint8_t ypages_span = ypage_end - ypage_start;          // how many pages does the line span?

    uint8_t dot_byte_start = 0xFD << (ypos % 8);            // create a byte with dots to represent first page (a column of 8 pixels)
#if defined (__Using_inverted_vertical_line_fix__)
    uint8_t dot_byte_end = 0xBF >> (8 - ((ypos+length) % 8));     // create a byte with dot to represent last page
// Alternative fix
//    uint8_t dot_byte_end = 0xFF << ((ypos+length) % 8 /*- 2*/);     // create a byte with dot to represent last page
//    dot_byte_end = ~dot_byte_end;     // create a byte with dot to represent last page
#else
    uint8_t dot_byte_end = 0xFF >> ((ypos+length) % 8);     // create a byte with dot to represent last page
#endif
    
    if (ypages_span == 0) {                                 // line is 8 pixels or shorter
        D_SETPOS(xpos, ypage_start);
        D_START_DAT();
        D_TX(dot_byte_start&dot_byte_end);
        D_STOP();
    }
    else {                                                  // line is >8 pixels long
        D_SETPOS(xpos, ypage_start);
        D_START_DAT();
        D_TX(dot_byte_start);                               // draw first 8 pixels (first page)
        D_STOP();
        
        if (ypages_span > 1) {                              // if the line >16 pixels long, draw the intermediate pages
            for (uint8_t i = ypage_start + 1; i < ypage_end; i++) {
                D_SETPOS(xpos, i);
                D_START_DAT();
                D_TX(0xFF);
                D_STOP();
            }
        }
        D_SETPOS(xpos, ypage_end);
        D_START_DAT();
        D_TX(dot_byte_end);                                 // draw the last 8 pixels (last page)
        D_STOP();
    }
}
