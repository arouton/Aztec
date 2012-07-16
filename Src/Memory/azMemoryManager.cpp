#include "azMemoryManager.h"
#include <cstdlib>

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMemoryManager& azMemoryManager::GrabInstance()
{
    static azMemoryManager oManager;
    return oManager;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void* azMemoryManager::Allocate(azUInt a_uSize)
{
    void* pAddress = malloc(a_uSize);

    azMemoryEntry oEntry;
    oEntry.m_pAddress = pAddress;
    azStackWalker::GetInstance().BuildCallStack(oEntry.m_oCallStack);
    m_lEntries.push_back(oEntry);

    return pAddress;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azMemoryManager::Deallocate(void* a_pAddress)
{
    azEntries::const_iterator it = FindEntry(a_pAddress);
    free(a_pAddress);
    m_lEntries.erase(it);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMemoryManager::azEntries::const_iterator azMemoryManager::FindEntry(void* a_pAddress) const
{
    for (azEntries::const_iterator it = m_lEntries.begin(); it != m_lEntries.end(); it++)
    {
        azMemoryEntry const& rMemoryEntry = (*it);
        if (rMemoryEntry.m_pAddress == a_pAddress)
        {
            return it;
        }
    }
    azAssert(false, "Cant find entry");
    return m_lEntries.end();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azMemoryManager::DumpLeaks() const
{
    unsigned int uLeakCount = 0;
    for (azEntries::const_iterator it = m_lEntries.begin(); it != m_lEntries.end(); it++)
    {
        azMemoryEntry const& rMemoryEntry = (*it);
        azCallStack const& rCallStack = rMemoryEntry.m_oCallStack;
        azPrint("********************************************************************************");
        azPrint("Leak at address 0x%08X", rMemoryEntry.m_pAddress);
        azPrint("********************************************************************************");
        rCallStack.Dump();
        azPrint("********************************************************************************");
        azPrint("\n");

        uLeakCount++;
    }
    azPrint("********************************************************************************");
    azPrint("Total report of %d leaks", uLeakCount);
    azPrint("********************************************************************************");
    for (azEntries::const_iterator it = m_lEntries.begin(); it != m_lEntries.end(); it++)
    {
        azMemoryEntry const& rMemoryEntry = (*it);
        azPrint("- 0x%08X", rMemoryEntry.m_pAddress);
    }
}
