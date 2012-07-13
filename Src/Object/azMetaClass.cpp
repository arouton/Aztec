#include "azMetaClass.h"
#include "Toolkit/azRef.h"

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClass::azMetaClass()
    : m_oClassId()
    , m_uSize(0)
    , m_pfnConstructor(NULL)
    , m_pfnDestructor(NULL)
    , m_pParentMetaClass(NULL)
{}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClass::azMetaClass(azMetaClass const& a_rSource)
    : m_oClassId(a_rSource.m_oClassId)
    , m_uSize(a_rSource.m_uSize)
    , m_pfnConstructor(a_rSource.m_pfnConstructor)
    , m_pfnDestructor(a_rSource.m_pfnDestructor)
{}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azMetaClass const& azMetaClass::operator =(azMetaClass const& a_rSource)
{
    m_oClassId = a_rSource.m_oClassId;
    m_uSize = a_rSource.m_uSize;
    m_pfnConstructor = a_rSource.m_pfnConstructor;
    m_pfnDestructor = a_rSource.m_pfnDestructor;
    return *this;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
bool azMetaClass::IsKindOf(azMetaClass const& a_rMetaClass) const
{
    azMetaClass const* pMetaClass = this;
    while (pMetaClass)
    {
        azMetaClass const& rMetaClass = *pMetaClass;
        if (IsSameInstance(rMetaClass, a_rMetaClass))
        {
            return true;
        }
        pMetaClass = rMetaClass.m_pParentMetaClass;
    }
    return false;
}