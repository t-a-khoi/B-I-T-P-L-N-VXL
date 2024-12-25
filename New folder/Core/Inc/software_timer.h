/*
 * software_timer.h
 *
 *  Created on: Dec 26, 2024
 *      Author: ADMIN
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer_flag[];

void timer_set(int index, int duration);
void timer_run();


#endif /* INC_SOFTWARE_TIMER_H_ */
