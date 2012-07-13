#ifndef __azRef__
#define __azRef__

#include "azCommon.h"

static size_t const c_sInvalidValue = ~((size_t)0);
#define azInvalidPointer(a_tType) reinterpret_cast<a_tType*>(c_sInvalidValue)

static azSz const c_szInvalidReferenceMessage = azL("Invalid reference (the internal pointer is invalid)");

// \class azRef
// \brief Pointer wrapped in a reference-accessed class
template <typename t_Object>
class AZ_API azRef
{
public:
    // Default constructor
    azRef(): m_pObject(azInvalidPointer(t_Object)) {}

    // Copy constructor
    azRef(azRef<t_Object> const& a_rRef);

    // Template-copy constructor
    template <typename t_OtherObject>
    azRef(azRef<t_OtherObject> const& a_rRef);

    // Value constructor
    azRef(t_Object& a_rObject): m_pObject(&a_rObject) {}

    // Destructor
    ~azRef();

    // Copy operator from azRef
    void operator = (azRef<t_Object> const& a_rRef);

    // Template-copy operator from azRef
    template <typename t_OtherObject>
    void operator = (azRef<t_OtherObject> const& a_rRef);

    // Assignment operator
    void operator = (t_Object& a_rObject) { m_pObject = &a_rObject; }

    // Cast operator
    operator t_Object& () const;

    // Return a reference to the object
    t_Object& GetRef() const;

    // Invalidate reference. Set the internal pointer to an explicit invalid value
    void SetInvalid() { m_pObject = azInvalidPointer(t_Object); }

    // Return 'true' is pointer is invalid
    bool IsInvalid() const { return m_pObject == azInvalidPointer(t_Object); }

    // Return 'true' is pointer is valid
    bool IsValid() const { return m_pObject != azInvalidPointer(t_Object); }

    // Memory address equality test operator
    bool IsSameInstance(t_Object const& a_rObject) const;

    // Memory address equality test operator
    bool IsSameInstance(azRef<t_Object> const& a_rRef) const;

    // Memory address comparison operator. Used for sort, maps, ...
    bool operator < (azRef<t_Object> const& a_rObject) const;

private:
    // Forbidden equality test operator
    // This operator is hidden because its behavior is unclear (should we compare or call the operator == upon pointed objects?)
    bool operator == (t_Object const& a_rObject) const { return false; }

    // Equality test operator, see above
    bool operator == (azRef<t_Object> const& a_rRef) const { return false; }

    // The pointer to the object
    t_Object* m_pObject;

    template <typename t_OtherObject>
    friend class azRef;
};

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline azRef<t_Object>::azRef(azRef<t_Object> const& a_rRef)
{
    m_pObject = a_rRef.m_pObject;

}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
template <typename t_OtherObject>
inline azRef<t_Object>::azRef(azRef<t_OtherObject> const& a_rRef)
{
    m_pObject = a_rRef.m_pObject;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline azRef<t_Object>::~azRef()
{
#ifdef AZ_REF_RESET
    m_pObject = NULL;
#endif // AZ_REF_RESET
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline void azRef<t_Object>::operator = (azRef<t_Object> const& a_rRef)
{
    m_pObject = a_rRef.m_pObject;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
template <typename t_OtherObject>
inline void azRef<t_Object>::operator = (azRef<t_OtherObject> const& a_rRef)
{
    m_pObject = a_rRef.m_pObject;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline azRef<t_Object>::operator t_Object& () const
{
    azAssert(IsInvalid() == false, c_szInvalidReferenceMessage);	
    return *m_pObject;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline t_Object& azRef<t_Object>::GetRef() const
{
    azAssert(IsInvalid() == false, c_szInvalidReferenceMessage);	
    return *m_pObject;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline bool azRef<t_Object>::IsSameInstance(t_Object const& a_rObject) const
{
    return (m_pObject == &a_rObject);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline bool azRef<t_Object>::IsSameInstance(azRef<t_Object> const& a_rRef) const
{
    return (m_pObject == a_rRef.m_pObject);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline bool azRef<t_Object>::operator < (azRef<t_Object> const& a_rObject) const
{
    return ((size_t)m_pObject) < ((size_t)a_rObject.m_pObject);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object>
inline azRef<t_Object> GetRef(t_Object& a_rObject)
{
    return azRef<t_Object>(a_rObject);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <typename t_Object1, typename t_Object2>
inline bool IsSameInstance(t_Object1& a_rObject1, t_Object2& a_rObject2)
{
    return ((&a_rObject1) == (&a_rObject2));
}

#endif // __azRef__
