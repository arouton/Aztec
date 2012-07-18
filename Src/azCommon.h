#ifndef __azBase__
#define __azBase__

#ifndef NULL
	#define NULL (0)
#endif // NULL

#define AZ_API 

typedef long azInt;
typedef unsigned long azUInt;
typedef float azFloat;
typedef bool azBool;

typedef unsigned char azUInt8;
typedef char azInt8;
typedef unsigned short azUInt16;
typedef short azInt16;
typedef azUInt azUInt32;
typedef int azInt32;

typedef void* azPtr;
typedef void const* azCPtr;

typedef azUInt8 azByte;
typedef azUInt8 const azCByte;
typedef azUInt8* azBytes;
typedef azUInt8 const* azCBytes;

typedef size_t azSize;


typedef char azCharA;
typedef wchar_t azCharW;

#ifdef _UNICODE
typedef azCharW azChar;
typedef azCharA azOppositeChar;
#else // _UNICODE
typedef azCharA azChar;
typedef azCharW azOppositeChar;
#endif // _UNICODE

typedef azCharA const* azSzA;
typedef azCharW const* azSzW;

#ifdef _UNICODE
typedef azCharW const* azSz;
typedef azCharA const* azOppositeSz;
#else // _UNICODE
typedef azCharA const* azSz;
typedef azCharW const* azOppositeSz;
#endif // _UNICODE

#define azInternConcat(a_Val1, a_Val2) a_Val1##a_Val2
#define azConcat(a_Val1, a_Val2) azInternConcat(a_Val1, a_Val2)
#define azInternConcat3(a_Val1, a_Val2, a_Val3) a_Val1##a_Val2##a_Val3
#define azConcat3(a_Val1, a_Val2, a_Val3) azInternConcat3(a_Val1, a_Val2, a_Val3)
#define azInternConcat4(a_Val1, a_Val2, a_Val3, a_Val4) a_Val1##a_Val2##a_Val3##a_Val4
#define azConcat4(a_Val1, a_Val2, a_Val3, a_Val4) azInternConcat4(a_Val1, a_Val2, a_Val3, a_Val4)

#define azWiden(a_szVal) azInternConcat(L, a_szVal)

#ifdef _UNICODE
#define azL(a_szVal) azConcat(L, a_szVal)
#else // UNICODE
#define azL(a_szVal) a_szVal
#endif // UNICODE

#define azInternStringizeA(a_Val) #a_Val
#define azStringizeA(a_Val) azInternStringizeA(a_Val)

//#if (BUILD_COMPILER == BUILD_COMPILER_MSC)
#define azInternStringizeW(a_Val) L#a_Val
//#else // BUILD_COMPILER
//#define azInternStringizeW(a_Val) azConcat(L, azInternStringizeA(a_Val))
//#endif // BUILD_COMPILER
#define azStringizeW(a_Val) azInternStringizeW(a_Val)

#ifdef _UNICODE
#define azStringize(a_Val) azInternStringizeW(a_Val)
#else // _UNICODE
#define azStringize(a_Val) azInternStringizeA(a_Val)
#endif // _UNICODE


namespace std 
{
    template<class _Elem>
    struct char_traits;
    template<class _Ty>
    class allocator;
    template<class _Elem, class _Traits, class _Ax>
    class basic_string;
}

typedef std::basic_string<azCharA, std::char_traits<azCharA>, std::allocator<azCharA> >
    azStringA;
typedef std::basic_string<azCharW, std::char_traits<azCharW>, std::allocator<azCharW> >
    azStringW;
typedef std::basic_string<azChar, std::char_traits<azChar>, std::allocator<azChar> >
    azString;


void _azAssert(azBool a_bCondition, const azCharA* a_szFormat, ...);
void _azAssert(azBool a_bCondition, const azCharW* a_szFormat, ...);
void _azPrint(const azCharA* a_szFormat, ...);
void _azPrint(const azCharW* a_szFormat, ...);

#define azAssert(a_bCondition, a_szFormat, ...)  _azAssert((a_bCondition), a_szFormat, __VA_ARGS__)
#define azPrint(a_szFormat, ...)  _azPrint(azL(a_szFormat), __VA_ARGS__ )

#define azNoDefault \
	default: \
		{ \
			azAssert(false, "Switch unexpected to fall in default case"); \
		} \
	break

#define azNoDefaultReturn(a_tType) \
	default: \
		{ \
			azAssert(false, "Switch unexpected to fall in default case"); \
			return a_tType(); \
		} \
	break

//template<class t_Declare>
//class AZ_API azEnumeration : public t_Declare
//{
//private:
//	// Internal types
//	typedef azEnumeration<t_Declare> _azEnumeration;
//	typedef t_Declare:azValue _azStore;
//
//public:
//	/// Exposed types
//	typedef typename t_Declare::azValue azValue;
//	static azValue const eValuesCount = t_Declare::eValuesCount;
//
//private:
//	/// Internal value storage
//	_azStore m_eValue;
//};

#endif // __azBase__