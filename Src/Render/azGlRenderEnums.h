#ifndef __azGlRenderEnums__
#define __azGlRenderEnums__

#include "Render/azRenderEnums.h"
#include <windows.h>
#include <gl/gl.h>

class AZ_API azGlRenderEnums
{
public:
	// \brief Get the native buffer type
	static GLenum GetNativeBufferType(azEBufferType::Enum a_eBufferType);

	
	// \brief Get the native lock type
	static GLenum GetNativeLockType(azELockType::Enum a_eLockType);


	// \brief Get native attribute size
	static GLenum GetNativeMatrixType(azEMatrixType::Enum a_eMatrixType);


	// \brief Get native semantic type (GL_VERTEX_ARRAY, GL_NORMAL_ARRAY, GL_COLOR_ARRAY, ...)
	static GLenum GetNativeSemanticType(azESemanticType::Enum a_eSemanticType);


	// \brief Get native attribute type (GL_FLOAT, GL_UNSIGNED_BYTE, ...)
	static GLenum GetNativeFormatType(azEFormatType::Enum a_eFormatType);

	// \brief Get native attribute size
	static GLsizei GetNativeFormatSize(azEFormatType::Enum a_eFormatType);


	// \brief Get the native primitive type (GL_TRIANGLES, GL_TRIANGLES_STRIP, ...)
	static GLenum GetNativePrimitiveType(azEPrimitiveType::Enum a_ePrimitiveType);

	// \brief Get the native primitive vertex count for each primitive type
	static GLsizei GetNativePrimitiveVertexCount(azEPrimitiveType::Enum a_ePrimitiveType, azUInt a_uCount);


	// \brief Get the native pixel format
	static GLenum GetNativePixelFormat(azEPixelFormat::Enum a_ePixelFormat);

	// \brief Get the native pixel internal format
	static GLenum GetNativePixelInternalFormat(azEPixelFormat::Enum a_ePixelFormat);

	// \brief Get the native pixel type
	static GLenum GetNativePixelType(azEPixelFormat::Enum a_ePixelFormat);

	// \brief Get the native bytes per pixel
	static GLuint GetNativeBytesPerPixel(azEPixelFormat::Enum a_ePixelFormat);

	// \brief Is the format compressed
	static bool IsPixelFormatCompressed(azEPixelFormat::Enum a_ePixelFormat);
};

#endif //__azGlRenderEnums__