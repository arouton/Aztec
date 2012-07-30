#ifndef __azTimer__
#define __azTimer__

#include "azCommon.h"

// \class azTimer
class azTimer
{
public:
    // \brief Default constructor
    azTimer();

    // \brief Initialize
    void Initialize();

    // \brief Terminate
    void Terminate() {}

    // \brief Update
    void Update();

    // \brief Get the delta time in seconds
    azFloat GetDeltaTime() { return m_fDeltaTime; }

    // \brief Get the time in seconds
    azFloat GetTime() { return m_fTime; }

private:
    azUInt64 m_u64TickerFrequency;
    azUInt64 m_u64FirstTick;
    azUInt64 m_u64PreviousTick;

    azFloat m_fDeltaTime;
    azFloat m_fTime;
};

#endif // __azTimer__