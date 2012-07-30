#include "azTimer.h"

#ifdef AZ_BUILD_WINDOWS
#include <windows.h>
#endif

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azTimer::azTimer()
    : m_u64TickerFrequency(0ULL)
    , m_u64PreviousTick(0ULL)
    , m_u64FirstTick(0ULL)
    , m_fDeltaTime(0.f)
    , m_fTime(0.f) 
{}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azTimer::Initialize()
{
#ifdef AZ_BUILD_WINDOWS
    LARGE_INTEGER lpFrequency;
    QueryPerformanceFrequency(&lpFrequency);
    m_u64TickerFrequency = (azUInt64)lpFrequency.QuadPart;

    LARGE_INTEGER lpPerformanceCount;
    QueryPerformanceCounter(&lpPerformanceCount);
    m_u64FirstTick = (azUInt64)lpPerformanceCount.QuadPart;
#else
#error "Undefined platform"
#endif

    m_u64PreviousTick = m_u64FirstTick;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azTimer::Update()
{
#ifdef AZ_BUILD_WINDOWS
    LARGE_INTEGER lpPerformanceCount;
    QueryPerformanceCounter(&lpPerformanceCount);
    azUInt64 u64Tick = (azUInt64)lpPerformanceCount.QuadPart;
#else
#error "Undefined platform"
#endif

    azUInt64 u64DeltaTick = u64Tick - m_u64PreviousTick;
    azDouble dDeltaTime = azDouble(u64DeltaTick) / azDouble(m_u64TickerFrequency);
    m_fDeltaTime = (azFloat)dDeltaTime;
    m_u64PreviousTick = u64Tick;

    azUInt64 u64DeltaTickSinceFirstTick = u64Tick - m_u64FirstTick;
    azDouble dTime = azDouble(u64DeltaTickSinceFirstTick) / azDouble(m_u64TickerFrequency);
    m_fTime = (azFloat)dTime;
}
