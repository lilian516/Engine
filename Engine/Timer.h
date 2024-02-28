#pragma once
#include <time.h>
using namespace std;

class Timer
{
public:
    Timer();
    ~Timer();
    void Start();
    void Update();
    void Break();
    void Restart();
    float GetDeltaTime();
    float CalculFPS();
    float GetCurrentTime();

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
