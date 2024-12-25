/*
 * button.c
 *
 *  Created on: Dec 26, 2024
 *      Author: ADMIN
 */
#include "main.h"

#define n0_button 3
#define n0_button_debounce 3
#define duration_hold 200
#define duration_hold_automatic 20
#define button_pressed GPIO_PIN_RESET
#define button_released GPIO_PIN_SET

int button_flag[n0_button] = {0, 0, 0};
GPIO_PinState button_debounce[n0_button][n0_button_debounce] = { {button_released, button_released, button_released},
																 {button_released, button_released, button_released},
																 {button_released, button_released, button_released} };
GPIO_PinState button_buffer[n0_button][2] = { {button_released, button_released},
											  {button_released, button_released},
											  {button_released, button_released} };
int hold_counter[n0_button] = {duration_hold, duration_hold, duration_hold};
int hold_counter_automatic[n0_button] = {1, 1, 1};

void button_run() {
	for (int i = 0; i < n0_button; i++) {
		for (int j = 0; j < n0_button_debounce - 1; j++) {
			button_debounce[i][j] = button_debounce[i][j+1];
		}
		if (i == 0) {
			button_debounce[i][n0_button_debounce - 1] = HAL_GPIO_ReadPin(bt0_GPIO_Port, bt0_Pin);
		} else if (i == 1) {
			button_debounce[i][n0_button_debounce - 1] = HAL_GPIO_ReadPin(bt1_GPIO_Port, bt1_Pin);
		} else {
			button_debounce[i][n0_button_debounce - 1] = HAL_GPIO_ReadPin(bt2_GPIO_Port, bt2_Pin);
		}
		int same_debounce = 1;
		for (int j = 0; j < n0_button_debounce - 1; j++) {
			if (button_debounce[i][j] != button_debounce[i][j+1]) {
				same_debounce = 0;
				break;
			}
		}
		button_buffer[i][0] = button_buffer[i][1];
		if (same_debounce == 1) {
			button_buffer[i][1] = button_debounce[i][0];
		}
		button_flag[i] = 0;
		if (button_buffer[i][1] == button_pressed) {
			if (hold_counter[i] > 1) {
				hold_counter[i]--;
				if (button_buffer[i][0] == button_released) {
					button_flag[i] = 1;
				}
			} else if (hold_counter_automatic[i] > 1) {
				hold_counter_automatic[i]--;
			} else {
				hold_counter_automatic[i] = duration_hold_automatic;
				button_flag[i] = 1;
			}
		} else {
			hold_counter[i] = duration_hold;
			hold_counter_automatic[i] = 1;
		}
	}
}
