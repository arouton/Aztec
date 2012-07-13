#ifndef __azCast__
#define __azCast__

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template <typename t_DstClass, typename t_SrcClass>
inline t_DstClass* azTryChildCast(t_SrcClass& a_rObject)
{
    if(a_rObject.GetMetaClass().IsKindOf<t_DstClass>())
    {
        return reinterpret_cast<t_DstClass*>(&a_rObject);
    }
    else
    {
        return NULL;
    }
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template <typename t_DstClass, typename t_SrcClass>
inline t_DstClass* azTryChildCast(t_SrcClass* a_pObject)
{
    if (a_pObject)
    {
        if(a_pObject->GetMetaClass().IsKindOf<t_DstClass>())
        {
            return reinterpret_cast<t_DstClass*>(a_pObject);
        }
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template <typename t_DstClass, typename t_SrcClass>
inline t_DstClass* azSafeChildCast(t_SrcClass* a_pObject)
{
    if (a_pObject)
    {
        azAssert(a_pObject->GetMetaClass().IsKindOf<t_DstClass>(), "Types mismatch");
        return reinterpret_cast<t_DstClass*>(a_pObject);
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
template <typename t_DstClass, typename t_SrcClass>
inline t_DstClass& azSafeChildCast(t_SrcClass& a_rObject)
{
    azAssert(a_rObject.GetMetaClass().IsKindOf<t_DstClass>(), "Types mismatch");
    return reinterpret_cast<t_DstClass&>(a_rObject);
}

#endif // __azCast__