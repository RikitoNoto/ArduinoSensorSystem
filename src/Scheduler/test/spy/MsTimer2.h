#ifndef _MS_TIMER2_SPY_H_
#define _MS_TIMER2_SPY_H_

namespace MsTimer2 {

    bool is_started = false;
    unsigned long set_time = 0;
    void (*set_f)() = nullptr;

	void set(unsigned long ms, void (*f)())
    {
        set_time = ms;
        set_f = f;
    }
	void start()
    {
        is_started = true;
    }
	void stop()
    {
        is_started = false;
    }
	void _overflow();

    void setUp(void)
    {
        is_started = false;
        set_time = 0;
        set_f = nullptr;
    }
}


#endif // _MS_TIMER2_SPY_H_