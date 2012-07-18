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

    template <class t_Type>
    t_Type* NewArray(azUInt a_uCount);
    template <class t_Type>
    void DeleteArray(t_Type* a_pArray, azUInt a_uCount);

    void DumpLeaks() const;

private:
    typedef std::list<azMemoryEntry> azEntries;
    azEntries::const_iterator FindEntry(void* a_pAddress) const;
    std::list<azMemoryEntry> m_lEntries;

};

#define azNew(a_tType) azMemoryManager::GrabInstance().New<a_tType>()
#define azDelete(a_rObject) azMemoryManager::GrabInstance().Delete(a_rObject)

#define azNewArray(a_tType, a_uCount) azMemoryManager::GrabInstance().NewArray<a_tType>(a_uCount)
#define azDeleteArray(a_pArray, a_uCount) azMemoryManager::GrabInstance().DeleteArray(a_pArray, a_uCount)


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

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template<class t_Type>
inline t_Type* azMemoryManager::NewArray(azUInt a_uCount)
{
    void* pArray = Allocate(a_uCount * sizeof(t_Type));
    azAssert(pArray != NULL, "Allocation failed");
    t_Type* pTypedArray = (t_Type*)(pArray);
    for (azUInt uIndex = 0; uIndex < a_uCount; uIndex++)
    {
        new(&(pTypedArray[uIndex])) t_Type;
    }
    return pTypedArray;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template<class t_Type>
inline void azMemoryManager::DeleteArray(t_Type* a_pArray, azUInt a_uCount)
{
    for (azUInt uIndex = 0; uIndex < a_uCount; uIndex++)
    {
        a_pArray[uIndex].~t_Type();
    }
    Deallocate(a_pArray);
}

#endif // __azMemoryManager__