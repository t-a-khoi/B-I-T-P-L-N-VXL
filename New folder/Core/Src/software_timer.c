/*
 * software_timer.c
 *
 *  Created on: Dec 26, 2024
 *      Author: ADMIN
 */

#define n0_timer 2

int timer_flag[n0_timer] = {0, 0};
int timer_counter[n0_timer] = {100, 100};

void timer_set(int index, int duration) {
	timer_flag[index] = 0;
	timer_counter[index] = duration;
}

void timer_run() {
	for (int i = 0; i < n0_timer; i++) {
		if (timer_counter[i] > 1) {
			timer_counter[i]--;
		} else {
			timer_flag[i] = 1;
		}
	}
}
