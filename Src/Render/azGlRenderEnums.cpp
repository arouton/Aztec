#include "azGlRenderEnums.h"
#include <gl/glext.h>

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativeBufferType(azEBufferType::Enum a_eBufferType)
{
    switch(a_eBufferType)
    {
        case azEBufferType::eStatic :
        {
    	    return GL_STATIC_DRAW_ARB;
        }
        case azEBufferType::eDynamic :
        {
            return GL_STREAM_DRAW_ARB;
        }
        azNoDefaultReturn(GLenum);
    }
}
	
//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativeLockType(azELockType::Enum a_eLockType)
{
	// \todo
	return GL_WRITE_ONLY_ARB;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativeMatrixType(azEMatrixType::Enum a_eMatrixType)
{
	switch (a_eMatrixType)
	{
		case azEMatrixType::eModelView :
		{
			return GL_MODELVIEW;
		}
		case azEMatrixType::eProjection :
		{
			return GL_PROJECTION;
		}
		case azEMatrixType::eTexture0 :
		case azEMatrixType::eTexture1 :
		case azEMatrixType::eTexture2 :
		case azEMatrixType::eTexture3 :
		{
			return GL_TEXTURE;
		}
		azNoDefaultReturn(GLenum);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativeSemanticType(azESemanticType::Enum a_eSemanticType)
{
	switch(a_eSemanticType)
	{
		case azESemanticType::ePosition :
		{
			return GL_VERTEX_ARRAY;
		}
		case azESemanticType::eNormal :
		{
			return GL_NORMAL_ARRAY;
		}
		case azESemanticType::eDiffuse :
		{
			return GL_COLOR_ARRAY;
		}
		case azESemanticType::eTexCoord :
		{
			return GL_TEXTURE_COORD_ARRAY;
		}
		default :
		{
			// Generic semantic type
			return 0;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativeFormatType(azEFormatType::Enum a_eFormatType)
{
	switch(a_eFormatType)
	{
		case azEFormatType::eFloat1 :
		case azEFormatType::eFloat2 :
		case azEFormatType::eFloat3 :
		case azEFormatType::eFloat4 :
		{
			return GL_FLOAT;
		}
		case azEFormatType::eColor :
		{
			return GL_UNSIGNED_BYTE;
		}
		azNoDefaultReturn(GLenum);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLsizei azGlRenderEnums::GetNativeFormatSize(azEFormatType::Enum a_eFormatType)
{
	switch(a_eFormatType)
	{
		case azEFormatType::eFloat1 :
		{
			return 1;
		}
		case azEFormatType::eFloat2 :
		{
			return 2;
		}
		case azEFormatType::eFloat3 :
		{
			return 3;
		}
		case azEFormatType::eFloat4 :
		{
			return 4;
		}
		case azEFormatType::eColor :
		{
			return 4;
		}
		azNoDefaultReturn(GLsizei);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativePrimitiveType(azEPrimitiveType::Enum a_ePrimitiveType)
{
	switch(a_ePrimitiveType)
	{
		case azEPrimitiveType::eTriangleList :
		{
			return GL_TRIANGLES;
		}
		case azEPrimitiveType::eTriangleStrip :
		{
			return GL_TRIANGLE_STRIP;
		}
		case azEPrimitiveType::eTriangleFan :
		{
			return GL_TRIANGLE_FAN;
		}
		case azEPrimitiveType::eLineList :
		{
			return GL_LINES;
		}
		case azEPrimitiveType::eLineStrip :
		{
			return GL_LINE_STRIP;
		}
		case azEPrimitiveType::ePointList :
		{
			return GL_POINTS;
		}
		azNoDefaultReturn(GLenum);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLsizei azGlRenderEnums::GetNativePrimitiveVertexCount(azEPrimitiveType::Enum a_ePrimitiveType, azUInt a_uVertexCount)
{
	switch(a_ePrimitiveType)
	{
		case azEPrimitiveType::eTriangleList :
		{
			return a_uVertexCount * 3;
		}
		case azEPrimitiveType::eTriangleStrip :
		{
			return a_uVertexCount + 2;
		}
		case azEPrimitiveType::eTriangleFan :
		{
			return a_uVertexCount + 1;
		}
		case azEPrimitiveType::eLineList :
		{
			return a_uVertexCount * 2;
		}
		case azEPrimitiveType::eLineStrip :
		{
			return a_uVertexCount + 1;
		}
		case azEPrimitiveType::ePointList :
		{
			return a_uVertexCount;
		}
		azNoDefaultReturn(GLsizei);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativePixelFormat(azEPixelFormat::Enum a_ePixelFormat)
{
	switch(a_ePixelFormat)
	{
		case azEPixelFormat::eL8 :
		{
			return GL_LUMINANCE;
		}
		case azEPixelFormat::eL8A8 :
		{
			return GL_LUMINANCE_ALPHA;
		}
		case azEPixelFormat::eA1R5G5B5 :
		{
			return GL_BGRA;
		}
		case azEPixelFormat::eA4R4G4B4 :
		{
			return GL_BGRA;
		}
		case azEPixelFormat::eR8G8B8 :
		{
			return GL_BGR;
		}
		case azEPixelFormat::eA8R8G8B8 :
		{
			return GL_BGRA;
		}
		case azEPixelFormat::eDXTC1 :
		{
			return GL_BGR;
		}
		case azEPixelFormat::eDXTC3 :
		{
			return GL_BGRA;
		}
		case azEPixelFormat::eDXTC5 :
		{
			return GL_BGRA;
		}
		azNoDefaultReturn(GLenum);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativePixelInternalFormat(azEPixelFormat::Enum a_ePixelFormat)
{
	switch(a_ePixelFormat)
	{
		case azEPixelFormat::eL8 :
		{
			return GL_LUMINANCE8;
		}
		case azEPixelFormat::eL8A8 :
		{
			return GL_LUMINANCE8_ALPHA8;
		}
		case azEPixelFormat::eA1R5G5B5 :
		{
			return GL_RGB5_A1;
		}
		case azEPixelFormat::eA4R4G4B4 :
		{
			return GL_RGBA4;
		}
		case azEPixelFormat::eR8G8B8 :
		{
			return GL_RGB8;
		}
		case azEPixelFormat::eA8R8G8B8 :
		{
			return GL_RGBA8;
		}
		case azEPixelFormat::eDXTC1 :
		{
			return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		}
		case azEPixelFormat::eDXTC3 :
		{
			return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		}
		case azEPixelFormat::eDXTC5 :
		{
			return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		}
		azNoDefaultReturn(GLenum);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLenum azGlRenderEnums::GetNativePixelType(azEPixelFormat::Enum a_ePixelFormat)
{
	switch(a_ePixelFormat)
	{
		case azEPixelFormat::eL8 :
		{
			return GL_UNSIGNED_BYTE;
		}
		case azEPixelFormat::eL8A8 :
		{
			return GL_UNSIGNED_BYTE;
		}
		case azEPixelFormat::eA1R5G5B5 :
		{
			return GL_UNSIGNED_SHORT_1_5_5_5_REV;
		}
		case azEPixelFormat::eA4R4G4B4 :
		{
			return GL_UNSIGNED_SHORT_4_4_4_4_REV;
		}
		case azEPixelFormat::eR8G8B8 :
		{
			return GL_UNSIGNED_BYTE;
		}
		case azEPixelFormat::eA8R8G8B8 :
		{
			return GL_UNSIGNED_BYTE;
		}
		case azEPixelFormat::eDXTC1 :
		{
			return 0;
		}
		case azEPixelFormat::eDXTC3 :
		{
			return 0;
		}
		case azEPixelFormat::eDXTC5 :
		{
			return 0;
		}
		azNoDefaultReturn(GLenum);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLuint azGlRenderEnums::GetNativeBytesPerPixel(azEPixelFormat::Enum a_ePixelFormat)
{
	switch(a_ePixelFormat)
	{
		case azEPixelFormat::eL8 :
		{
			return 1;
		}
		case azEPixelFormat::eL8A8 :
		{
			return 2;
		}
		case azEPixelFormat::eA1R5G5B5 :
		{
			return 2;
		}
		case azEPixelFormat::eA4R4G4B4 :
		{
			return 2;
		}
		case azEPixelFormat::eR8G8B8 :
		{
			return 3;
		}
		case azEPixelFormat::eA8R8G8B8 :
		{
			return 4;
		}
		case azEPixelFormat::eDXTC1 :
		{
			return 1;
		}
		case azEPixelFormat::eDXTC3 :
		{
			return 2;
		}
		case azEPixelFormat::eDXTC5 :
		{
			return 2;
		}
		azNoDefaultReturn(GLuint);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
bool azGlRenderEnums::IsPixelFormatCompressed(azEPixelFormat::Enum a_ePixelFormat)
{
	switch(a_ePixelFormat)
	{
		case azEPixelFormat::eDXTC1 :
		case azEPixelFormat::eDXTC3 :
		case azEPixelFormat::eDXTC5 :
		{
			return true;
		}
		default :
		{
			return false;
		}
	}
}
