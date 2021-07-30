#ifndef TIMER_H
#define TIMER_H


class Timer {
    bool clear = false;

public:
    template<typename Function>
    void setTimeout(Function function, int delay);

    template<typename Function>
    void setInterval(Function function, int interval);

    void stop();
};

#endif // TIMER_H
