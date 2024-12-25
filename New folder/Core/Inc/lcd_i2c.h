/*
 * lcd_i2c.h
 *
 *  Created on: Dec 26, 2024
 *      Author: ADMIN
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "stm32f1xx_hal.h"

void lcd_init();
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_clear_display();
void lcd_goto_XY(int row, int col);

#endif /* INC_LCD_I2C_H_ */
