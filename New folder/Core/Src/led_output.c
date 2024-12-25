/*
 * led_output.c
 *
 *  Created on: Dec 26, 2024
 *      Author: ADMIN
 */
#include "main.h"
#include "software_timer.h"
#include "button.h"
#include "lcd_i2c.h"

int g_time = 7;
int y_time = 3;

int g_counter = 0;
int y_counter = 0;
int status_mode = 0;
int status_mode_0 = 0;
int reset_signal = 1;
char digit_buffer[4] = {'0', '0', '0', '0'};

void led_run() {
	if (button_flag[0] == 1) {
		button_flag[0] = 0;
		reset_signal = 1;
		status_mode++;
		if (status_mode >= 4) {
			status_mode = 0;
		}
	}
	if (status_mode == 0) {
		if (reset_signal == 1) {
			reset_signal = 0;
			timer_flag[1] = 1;
			g_counter = g_time;
			y_counter = y_time;
			status_mode_0 = 0;
			HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_RESET);
		}
		if (timer_flag[1] == 1) {
			timer_set(1, 100);
			if (status_mode_0 == 0) {
				if (g_counter >= g_time) {
					HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_RESET);
				}
				digit_buffer[0] = ( (g_counter + y_counter) / 10 ) + '0';
				digit_buffer[1] = ( (g_counter + y_counter) % 10 ) + '0';
				digit_buffer[2] = ( g_counter / 10 ) + '0';
				digit_buffer[3] = ( g_counter % 10 ) + '0';
				if (g_counter > 1) {
					g_counter--;
				} else {
					status_mode_0 = 1;
				}
			} else if (status_mode_0 == 1) {
				if (y_counter >= y_time) {
					HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_SET);
				}
				digit_buffer[0] = ( y_counter / 10 ) + '0';
				digit_buffer[1] = ( y_counter % 10 ) + '0';
				digit_buffer[2] = ( y_counter / 10 ) + '0';
				digit_buffer[3] = ( y_counter % 10 ) + '0';
				if (y_counter > 1) {
					y_counter--;
				} else {
					status_mode_0 = 2;
					g_counter = g_time;
					y_counter = y_time;
				}
			} else if (status_mode_0 == 2) {
				if (g_counter >= g_time) {
					HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_SET);
				}
				digit_buffer[0] = ( g_counter / 10 ) + '0';
				digit_buffer[1] = ( g_counter % 10 ) + '0';
				digit_buffer[2] = ( (g_counter + y_counter) / 10 ) + '0';
				digit_buffer[3] = ( (g_counter + y_counter) % 10 ) + '0';
				if (g_counter > 1) {
					g_counter--;
				} else {
					status_mode_0 = 3;
				}
			} else {
				if (y_counter >= y_time) {
					HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_SET);
				}
				digit_buffer[0] = ( y_counter / 10 ) + '0';
				digit_buffer[1] = ( y_counter % 10 ) + '0';
				digit_buffer[2] = ( y_counter / 10 ) + '0';
				digit_buffer[3] = ( y_counter % 10 ) + '0';
				if (y_counter > 1) {
					y_counter--;
				} else {
					status_mode_0 = 0;
					g_counter = g_time;
					y_counter = y_time;
				}
			}
		}
	} else if (status_mode == 1) {
		if (reset_signal == 1) {
			reset_signal = 0;
			timer_flag[1] = 1;
			g_counter = g_time;
			y_counter = y_time;
			digit_buffer[0] = ( (g_counter + y_counter) / 10 ) + '0';
			digit_buffer[1] = ( (g_counter + y_counter) % 10 ) + '0';
			digit_buffer[2] = ( 0 ) + '0';
			digit_buffer[3] = ( 2 ) + '0';
			HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_RESET);
		}
		if (button_flag[1] == 1) {
			button_flag[1] = 0;
			g_counter++;
			if (g_counter + y_counter >= 100) {
				g_counter = 1;
			}
			digit_buffer[0] = ( (g_counter + y_counter) / 10 ) + '0';
			digit_buffer[1] = ( (g_counter + y_counter) % 10 ) + '0';
		}
		if (button_flag[2] == 1) {
			button_flag[2] = 0;
			g_time = g_counter;
		}
		if (timer_flag[1] == 1) {
			timer_set(1, 25);
			HAL_GPIO_TogglePin(tf0_GPIO_Port, tf0_Pin);
			HAL_GPIO_TogglePin(tf1_GPIO_Port, tf1_Pin);
			HAL_GPIO_TogglePin(tf2_GPIO_Port, tf2_Pin);
			HAL_GPIO_TogglePin(tf3_GPIO_Port, tf3_Pin);
		}
	} else if (status_mode == 2) {
		if (reset_signal == 1) {
			reset_signal = 0;
			timer_flag[1] = 1;
			g_counter = g_time;
			y_counter = y_time;
			digit_buffer[0] = ( y_counter / 10 ) + '0';
			digit_buffer[1] = ( y_counter % 10 ) + '0';
			digit_buffer[2] = ( 0 ) + '0';
			digit_buffer[3] = ( 3 ) + '0';
			HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_RESET);
		}
		if (button_flag[1] == 1) {
			button_flag[1] = 0;
			y_counter++;
			if (g_counter + y_counter >= 100) {
				y_counter = 1;
			}
			digit_buffer[0] = ( y_counter / 10 ) + '0';
			digit_buffer[1] = ( y_counter % 10 ) + '0';
		}
		if (button_flag[2] == 1) {
			button_flag[2] = 0;
			y_time = y_counter;
		}
		if (timer_flag[1] == 1) {
			timer_set(1, 25);
			HAL_GPIO_TogglePin(tf1_GPIO_Port, tf1_Pin);
			HAL_GPIO_TogglePin(tf3_GPIO_Port, tf3_Pin);
		}
	} else {
		if (reset_signal == 1) {
			reset_signal = 0;
			timer_flag[1] = 1;
			g_counter = g_time;
			y_counter = y_time;
			digit_buffer[0] = ( g_counter / 10 ) + '0';
			digit_buffer[1] = ( g_counter % 10 ) + '0';
			digit_buffer[2] = ( 0 ) + '0';
			digit_buffer[3] = ( 4 ) + '0';
			HAL_GPIO_WritePin(tf0_GPIO_Port, tf0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf1_GPIO_Port, tf1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf2_GPIO_Port, tf2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(tf3_GPIO_Port, tf3_Pin, GPIO_PIN_RESET);
		}
		if (button_flag[1] == 1) {
			button_flag[1] = 0;
			g_counter++;
			if (g_counter + y_counter >= 100) {
				g_counter = 1;
			}
			digit_buffer[0] = ( g_counter / 10 ) + '0';
			digit_buffer[1] = ( g_counter % 10 ) + '0';
		}
		if (button_flag[2] == 1) {
			button_flag[2] = 0;
			g_time = g_counter;
		}
		if (timer_flag[1] == 1) {
			timer_set(1, 25);
			HAL_GPIO_TogglePin(tf0_GPIO_Port, tf0_Pin);
			HAL_GPIO_TogglePin(tf2_GPIO_Port, tf2_Pin);
		}
	}
	lcd_goto_XY(0, 0);
	lcd_send_data(digit_buffer[0]);
	lcd_send_data(digit_buffer[1]);
	lcd_goto_XY(0, 14);
	lcd_send_data(digit_buffer[2]);
	lcd_send_data(digit_buffer[3]);
}
