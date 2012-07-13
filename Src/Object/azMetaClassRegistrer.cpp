#include "azClassManager.h"
#include "azMetaClass.h"
#include "azClassManager.h"
#include "Memory/azMemoryManager.h"

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClassRegistrer& azMetaClassRegistrer::GrabInstance()
{
    static azMetaClassRegistrer oRegistrer;
    return oRegistrer;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClassRegistrer const& azMetaClassRegistrer::GetInstance()
{
    return GrabInstance();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClass* azMetaClassRegistrer::RegisterMetaClassFiller(azPfnMetaClassFiller a_pfnMetaClassFiller)
{
    m_lMetaClassFillers.push_back(a_pfnMetaClassFiller);
    return NULL;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azMetaClassRegistrer::CreateMetaClasses() const
{
    for (azMetaClassFillers::const_iterator it = m_lMetaClassFillers.begin(); it != m_lMetaClassFillers.end(); it++)
    {
        azPfnMetaClassFiller pfnMetaClassFiller = *it; 
        azMetaClass& rMetaClass = azNew(azMetaClass);
        pfnMetaClassFiller(rMetaClass);
        *(rMetaClass.m_ppHandle) = &rMetaClass;
        azClassManager::GrabInstance().RegisterMetaClass(rMetaClass);
    }
}
