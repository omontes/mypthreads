/* 
 * File:   Timer.h
 * Author: oscar
 *
 * Created on September 14, 2015, 10:25 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#define INTERVAL 5000; // 5ms - quantum //
#define START 10; // 1 ms //
#include <signal.h>
#include <sys/time.h>
struct itimerval it;
sigset_t t1, t2;

void lockSignals();
void unlockSignals();
void pauseTimer();
void startTimer();
void setupTimer(struct sigaction act);

#endif	/* TIMER_H */

