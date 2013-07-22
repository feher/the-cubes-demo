#include "frametimer.h"

#include <GLFW/glfw3.h> // glfw*

#include <iomanip>

using namespace std;

FrameTimer::FrameTimer()
    : m_interval(1.0),
      m_baseTime(glfwGetTime()),
      m_msPerFrame(0),
      m_frames(0) {
}

bool FrameTimer::tick() {
    ++m_frames;
    auto t = glfwGetTime();
    if (t - m_baseTime >= m_interval) {
        m_msPerFrame =  1000 * (t - m_baseTime) / m_frames;
        m_baseTime = t;
        m_frames = 0;
        return true;
    }
    return false;
}

void FrameTimer::print(ostream& stream) const {
    stream << std::fixed << std::setw(7) << std::setprecision(3)
           << m_msPerFrame << " ms/frame, "
           << std::fixed << std::setw(8) << std::setprecision(3)
           << 1000/m_msPerFrame << " frames/sec" << endl;
}
