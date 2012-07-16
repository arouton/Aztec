#ifndef __azMemoryManagery__
#define __azMemoryManagery__

#include "azCommon.h"
#include "azStackWalker.h"
#include <list>

// \class azMemoryEntry
class azMemoryEntry
{
public:
    void* m_pAddress;
    azCallStack m_oCallStack;
};


// \class azMemoryManager
class azMemoryManager
{
public:
    static azMemoryManager& GrabInstance();

    void* Allocate(azUInt a_uSize);
    void Deallocate(void* pAddress);

    template <class t_Type>
    t_Type& New();
    template <class t_Type>
    void Delete(t_Type& a_rObject);

    void DumpLeaks() const;

private:
    typedef std::list<azMemoryEntry> azEntries;
    azEntries::const_iterator FindEntry(void* a_pAddress) const;
    std::list<azMemoryEntry> m_lEntries;

};

#define azNew(a_tType) azMemoryManager::GrabInstance().New<a_tType>()
#define azDelete(a_rObject) azMemoryManager::GrabInstance().Delete(a_rObject)

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template<class t_Type>
inline t_Type& azMemoryManager::New()
{
    void* pObject = Allocate(sizeof(t_Type));
    azAssert(pObject != NULL, "Allocation failed");
    new(pObject) t_Type;
    return *(t_Type*)(pObject);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template<class t_Type>
inline void azMemoryManager::Delete(t_Type& a_rObject)
{
    a_rObject.~t_Type();
    Deallocate(&a_rObject);
}

#endif // __azMemoryManager__