#include "azCast.h"
#include "azMetaClass.h"

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template<class t_Class>
inline t_Class& azFactory::CreateObject()
{
    azCreateParams oDefaultParams;
    return CreateObject<t_Class>(oDefaultParams);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template<class t_Class>
inline t_Class& azFactory::CreateObject(azCreateParams const& a_rCreateParams)
{
    azMetaClass const& rMetaClass = t_Class::MetaClass();
    azIObject& rObject = _CreateObject(rMetaClass, a_rCreateParams);
    return azSafeChildCast<t_Class>(rObject);
}

