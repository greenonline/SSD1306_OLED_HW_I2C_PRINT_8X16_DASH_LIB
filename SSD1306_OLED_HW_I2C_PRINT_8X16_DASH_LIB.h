#ifndef SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB_h
#define SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB_h
#include <SSD1306_OLED_HW_I2C_PRINT_8X16_LIB.h>

class SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB : public SSD1306_OLED_HW_I2C_PRINT_8X16_LIB {

  public:

    SSD1306_OLED_HW_I2C_PRINT_8X16_DASH_LIB(void);

    void D_DRAW_VERT_DASHED(uint8_t xpos, uint8_t ypos, uint8_t length);




  private:



};
#endif