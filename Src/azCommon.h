#ifndef __azBase__
#define __azBase__

#ifndef NULL
	#define NULL 0
#endif // NULL

typedef long azInt;
typedef unsigned long azUInt;
typedef float azFloat;
typedef char azChar;
typedef unsigned char azUChar;
typedef bool azBool;

typedef unsigned char azUInt8;
typedef char azInt8;
typedef unsigned short azUInt16;
typedef short azInt16;
typedef azUInt azUInt32;
typedef int azInt32;

typedef const char* azSz;
#define azL(a_szString) a_szString

#define AZ_API 

void azAssert(azBool a_bCondition, const azChar* a_szFormat, ...);
void azPrint(const azChar* a_szFormat, ...);

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