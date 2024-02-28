#include "Timer.h"
#include <chrono>

Timer::Timer() {

}

Timer::~Timer() {

}

void Timer::Start() {
    m_fTime = GetCurrentTime();
    m_fTotalTime = 0.0f;
    m_bPause = false;
    m_fDeltaTime = 0.0f;
    m_iFrameCount = 0;
}

void Timer::Update() {
    if (!m_bPause) {
        float currentTime = GetCurrentTime();
        m_fDeltaTime = currentTime - m_fTime;
        m_fTotalTime += m_fDeltaTime;
        ++m_iFrameCount;
        m_fTime = currentTime;
    }
}

void Timer::Break() {
    m_bPause = true;
    m_fPauseTime = GetCurrentTime();
}

void Timer::Restart() {
    m_bPause = false;
    m_fPauseTime = GetCurrentTime() - m_fPauseTime;
    m_fTime -= m_fPauseTime;
}
float Timer::GetDeltaTime() {
    return m_fDeltaTime;
}
float Timer::CalculFPS() {
    if (m_fTotalTime > 0.0f) {
        return static_cast<float>(m_iFrameCount) / m_fTotalTime;
    } else {
        return 0.0f; // Avoid division by zero
    }
}
float Timer::GetCurrentTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
}
