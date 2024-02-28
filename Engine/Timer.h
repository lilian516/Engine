#pragma once
#include <time.h>
using namespace std;

class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void update();
    void breakTime();
    void restart();
    float getDeltaTime();
    float calculFPS();
    float getCurrentTime();

private:
    float m_fTime;
    float m_fDeltaTime;
    float m_fTotalTime;
    float m_fPauseTime;
    float m_fFps;
    int m_iFrameCount;
    bool m_bPause;



protected:


};
