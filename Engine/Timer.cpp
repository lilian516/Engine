#include "Timer.h"
#include <chrono>

Timer::Timer() {

}

Timer::~Timer() {

}

void Timer::start() {
    m_fTime = getCurrentTime();
    m_fTotalTime = 0.0f;
    m_bPause = false;
    m_fDeltaTime = 0.0f;
    m_iFrameCount = 0;
    m_fDifflTime = 0.0f;
}

void Timer::update() {
    if (!m_bPause) {
        float currentTime = getCurrentTime();
        m_fDeltaTime = currentTime - m_fTime;
        m_fTotalTime += m_fDeltaTime;
        m_fDifflTime += m_fDeltaTime;
        ++m_iFrameCount;
        m_fTime = currentTime;
    }
}

void Timer::breakTime() {
    m_bPause = true;
    m_fPauseTime = getCurrentTime();
}

void Timer::restart() {
    m_bPause = false;
    m_fPauseTime = getCurrentTime() - m_fPauseTime;
    m_fTime -= m_fPauseTime;
}
float Timer::getDeltaTime() {
    return m_fDeltaTime;
}
float Timer::calculFPS() {
    if (m_fTotalTime > 0.0f) {
        return static_cast<float>(m_iFrameCount) / m_fTotalTime;
    } else {
        return 0.0f; // Avoid division by zero
    }
}
float Timer::getCurrentTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
}

