#ifndef _MS_TIMER2_SPY_H_
#define _MS_TIMER2_SPY_H_

namespace MsTimer2 {

    extern bool is_started;
    extern unsigned long set_time;
    extern void (*set_f)();

	void set(unsigned long ms, void (*f)());
	void start();
	void stop();
	void _overflow();

    void setUp(void);
}


#endif // _MS_TIMER2_SPY_H_