#ifndef __azMetaClass__
#define __azMetaClass__

#include "azCommon.h"
#include "Object/azClassId.h"

// \class azMetaClass
// \brief 
class AZ_API azMetaClass
{
public:
    typedef void (*azPfnConstructor)(void*);
    typedef void (*azPfnDestructor)(void*);
    typedef void (*azPfnStaticConstructor)(azMetaClass& /*a_rMetaClass*/);

    azMetaClass();
    azMetaClass(azMetaClass const& a_rSource);
    azMetaClass const& operator =(azMetaClass const& a_rSource);

    bool IsKindOf(azMetaClass const& a_rMetaClass) const;

    template <class t_Class>
    bool IsKindOf() const { return IsKindOf(t_Class::MetaClass()); }

    azSz GetName() const { return m_szName; }

    azClassId const& GetClassId() const { return m_oClassId; }

//private:
    friend class azFactory;

    azClassId m_oClassId;
    azSz m_szName;
    azUInt m_uSize;
    azPfnConstructor m_pfnConstructor;
    azPfnDestructor m_pfnDestructor;
    azPfnStaticConstructor m_pfnStaticConstructor;
    azMetaClass* m_pParentMetaClass;
    azMetaClass** m_ppHandle;
};

#endif // __azMetaClass__