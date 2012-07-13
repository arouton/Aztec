#ifndef __azRenderEnums__
#define __azRenderEnums__

#include "azCommon.h"

// \class azELockType
// \brief Enum lock types
class AZ_API azELockType
{
public:
	enum Enum
	{
		eReadOnly,
		eWriteOnly,
		eReadWrite
	};
};

// \class azEBufferType
// \brief Enum buffer types
class AZ_API azEBufferType
{
public:
	enum Enum
	{
		eStatic,
		eDynamic
	};
};

// \class azESemanticType
// \brief Enum semantic types
class AZ_API azESemanticType
{
public:
	enum Enum
	{
		ePosition,
		eNormal,  
		eDiffuse,   
		eTexCoord
	};
};

// \class azEFormatType
// \brief Enum format types
class AZ_API azEFormatType
{
public:
	enum Enum
	{
		eFloat1,
		eFloat2,
		eFloat3,
		eFloat4,
		eColor  
	};
};

// \class azEPrimitiveType
// \brief Enum primitive types
class AZ_API azEPrimitiveType
{
public:
	enum Enum
	{
        eTriangleList, 
        eTriangleStrip,
        eTriangleFan,  
        eLineList,     
        eLineStrip,    
        ePointList     
    };
};

// \class azEMatrixType
// \brief Enum matrix types
class AZ_API azEMatrixType
{
public:
	enum Enum
	{
        eModelView,
        eProjection,
        eTexture0,
        eTexture1,
        eTexture2,
        eTexture3 
    };
};

// \class azEPixelFormat
// \brief Enum pixel format
class AZ_API azEPixelFormat
{
public:
	enum Enum
	{
        eL8,
        eL8A8,
        eA1R5G5B5,
	    eA4R4G4B4,
	    eR8G8B8,  
	    eA8R8G8B8,
        eDXTC1,   
        eDXTC3,   
        eDXTC5    
    };
};

#endif //__azRenderEnums__