#include "azClassManager.h"
#include "azMetaClass.h"
#include "azMetaClassRegistrer.h"
#include "Memory/azMemoryManager.h"

AZ_IMPLEMENT_CLASS(azClassManager, azNoParent)

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azClassManager::StaticConstructor(azMetaClass& a_rMetaClass)
{

}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azClassManager::Initialize()
{
    azMetaClassRegistrer::GrabInstance().CreateMetaClasses();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azClassManager::Terminate()
{
    for (azMetaClasses::iterator it = m_lMetaClasses.begin(); it != m_lMetaClasses.end(); it++)
    {
        azMetaClass& rMetaClass = (*it).GetRef();
        azDelete(rMetaClass);
    }
    m_lMetaClasses.empty();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azClassManager& azClassManager::GrabInstance()
{
    static azClassManager oManager;
    return oManager;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azClassManager const& azClassManager::GetInstance()
{
    return GrabInstance();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azClassManager::RegisterMetaClass(azMetaClass& a_rMetaClass)
{
    m_lMetaClasses.push_back(a_rMetaClass);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azClassManager::UnregisterMetaClass(azMetaClass& a_rMetaClass)
{

}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClass* azClassManager::TryFindMetaClass(azClassId const& a_rClassId)
{
    for (azMetaClasses::iterator it = m_lMetaClasses.begin(); it != m_lMetaClasses.end(); it++)
    {
        azMetaClass& rMetaClass = (*it).GetRef();
        if (rMetaClass.GetClassId() == a_rClassId)
        {
            return &rMetaClass;
        }
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClass const* azClassManager::TryFindMetaClass(azClassId const& a_rClassId) const
{
    for (azMetaClasses::const_iterator it = m_lMetaClasses.begin(); it != m_lMetaClasses.end(); it++)
    {
        azMetaClass const& rMetaClass = (*it).GetRef();
        if (rMetaClass.GetClassId() == a_rClassId)
        {
            return &rMetaClass;
        }
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClass const& azClassManager::FindMetaClass(azClassId const& a_rClassId) const
{
    azMetaClass const* pMetaClass = TryFindMetaClass(a_rClassId);
    azAssert(pMetaClass != NULL, "Could not find metaclass");
    return *pMetaClass;
}