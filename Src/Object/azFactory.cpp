#include "azFactory.h"
#include "azIObject.h"
#include "azClassManager.h"
#include "Memory/azMemoryManager.h"
#include <cstring>


//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azFactory& azFactory::GrabInstance()
{
    static azFactory oFactory;
    return oFactory;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azFactory const& azFactory::GetInstance()
{
	return GrabInstance();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azIObject& azFactory::CreateObject(azClassId const& a_rClassId)
{
	azCreateParams oDefaultParams;
	return CreateObject(a_rClassId, oDefaultParams);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azIObject& azFactory::CreateObject(azClassId const& a_rClassId, azCreateParams const& a_rCreateParams)
{
	azMetaClass const& rMetaClass = azClassManager::GetInstance().FindMetaClass(a_rClassId);
	return _CreateObject(rMetaClass, a_rCreateParams);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azIObject& azFactory::_CreateObject(azMetaClass const& a_rMetaClass, azCreateParams const& a_rCreateParams)
{
	void* pObject = azMemoryManager::GrabInstance().Allocate(a_rMetaClass.m_uSize);
	azAssert(pObject != NULL, "Could not create object");
	a_rMetaClass.m_pfnConstructor(pObject);

	azIObject* pIObject = static_cast<azIObject*>(pObject);
	azAssert(pIObject != NULL, "Could not create object");

	pIObject->Create(a_rCreateParams);
	pIObject->Initialize();

	return (*pIObject);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azFactory::DestroyObject(azIObject& a_rObject)
{
	a_rObject.Terminate();
	a_rObject.Destroy();
    azMetaClass const& rMetaClass = a_rObject.GetMetaClass();
    rMetaClass.m_pfnDestructor(&a_rObject);
	azMemoryManager::GrabInstance().Deallocate(&a_rObject);
}
