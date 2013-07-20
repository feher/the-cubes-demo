#ifndef FRAME_TIMER_H
#define FRAME_TIMER_H

#include <ostream>

class FrameTimer {
public:
    explicit FrameTimer();

    inline void setInterval(unsigned int millisecs);

    bool tick();
    void print(std::ostream& stream) const;
    inline void tickAndPrint(std::ostream& stream);

    inline double msPerFrame() const;

private:
    double m_interval;
    double m_baseTime;
    double m_msPerFrame;
    unsigned int m_frames;
};

void FrameTimer::setInterval(unsigned int millisecs) {
    m_interval = double(millisecs) / 1000.0;
}

void FrameTimer::tickAndPrint(std::ostream& stream) {
    if (tick()) {
        print(stream);
    }
}

double FrameTimer::msPerFrame() const {
    return m_msPerFrame;
}

#endif
