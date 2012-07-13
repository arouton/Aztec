#ifndef __azObjectMacros__
#define __azObjectMacros__

#include "Object/azMetaClassRegistrer.h"
#include "Object/azMetaClass.h"


// \class azConstructorDestructorHelper
template <class t_Class>
class AZ_API azConstructorDestructorHelper
{
public:
    static void Constructor(void* a_pObject)
    {
        // Placement new
        new(a_pObject) t_Class;
    }

    static void Destructor(void* a_pObject)
    {
        // Explicit call to destructor
        ((t_Class*)a_pObject)->t_Class::~t_Class();
    }
};

// \class azNoParent
class AZ_API azNoParent
{
public:
    static azMetaClass* _MetaClassPtr() { return NULL; }
};


#define _AZ_DECLARE_CLASS(a_tClass) \
    private: static azMetaClass* ms_pClass_##a_tClass; \
    public: static void StaticConstructor(azMetaClass& a_rMetaClass); \
	static azMetaClass* _MetaClassPtr() { return ms_pClass_##a_tClass; } \
    static azMetaClass const& MetaClass() \
    { \
        azAssert(ms_pClass_##a_tClass != NULL, "MetaClass is not present"); \
        return *(ms_pClass_##a_tClass); \
    } \
    static void FillMetaClass(azMetaClass& a_rMetaClass);

#define AZ_DECLARE_CLASS(a_tClass) \
    _AZ_DECLARE_CLASS(a_tClass) \
    virtual azMetaClass const& GetMetaClass() const { return a_tClass::MetaClass(); }

#define AZ_DECLARE_SIMPLE_CLASS(a_tClass) \
    _AZ_DECLARE_CLASS(a_tClass) \
    azMetaClass const& GetMetaClass() const { return a_tClass::MetaClass(); }


#define _AZ_IMPLEMENT_CLASS(a_tClass, a_tParentClass) \
    void a_tClass::FillMetaClass(azMetaClass& a_rMetaClass) \
    { \
        a_rMetaClass.m_oClassId = azClassId(azL(#a_tClass)); \
        a_rMetaClass.m_szName = azL(#a_tClass); \
        a_rMetaClass.m_uSize = sizeof(a_tClass); \
        a_rMetaClass.m_pfnConstructor = azConstructorDestructorHelper<a_tClass>::Constructor; \
        a_rMetaClass.m_pfnDestructor = azConstructorDestructorHelper<a_tClass>::Destructor; \
        a_rMetaClass.m_pfnStaticConstructor = StaticConstructor; \
        a_rMetaClass.m_pParentMetaClass = a_tParentClass::_MetaClassPtr(); \
        a_rMetaClass.m_ppHandle = &ms_pClass_##a_tClass; \
    } \
    azMetaClass* a_tClass::ms_pClass_##a_tClass = azMetaClassRegistrer::GrabInstance().RegisterMetaClassFiller(FillMetaClass);

#define AZ_IMPLEMENT_CLASS(a_tClass, a_tParentClass) \
    _AZ_IMPLEMENT_CLASS(a_tClass, a_tParentClass)

#define AZ_IMPLEMENT_SIMPLE_CLASS(a_tClass) \
    _AZ_DECLARE_CLASS(a_tClass, azNoParent)


#endif // __azObjectMacros__     