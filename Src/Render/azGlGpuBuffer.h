#ifndef __azGlGpuBuffer__
#define __azGlGpuBuffer__

#include "azCommon.h"

// To remove by wrapping better opengl calls
#include <windows.h>
#include <gl/gl.h>
#include <gl/glext.h>
// To remove

#include "Render/azGlRenderEnums.h"
#include "Render/azGlRenderer.h"
#include "Render/azIGpuBuffer.h"

// \class azGlGpuBuffer
// \brief OpenGL Gpu buffer
template <int t_Type>
class azGlGpuBuffer : public azIGpuBuffer
{
public :
	// \brief Constructor
	azGlGpuBuffer();

	// \brief Virtual destructor
	virtual ~azGlGpuBuffer() {}
	

	// \brief Initialize
	virtual void Initialize(azUInt a_uSize, azEBufferType::Enum a_eBufferType);

	// \brief Terminate
	virtual void Terminate();


	// \brief GetBufferId
	GLuint GetBufferId() const;

private :
	// \brief Lock the buffer
	void* Lock(azUInt a_uOffset, azUInt a_uSize, azELockType::Enum a_eLockType);

	// \brief Unlock the buffer
	void Unlock();


	// Buffer id
	GLuint m_uBufferId;
};

typedef azGlGpuBuffer<GL_ARRAY_BUFFER_ARB> azGlVertexBuffer;
typedef azGlGpuBuffer<GL_ELEMENT_ARRAY_BUFFER_ARB> azGlIndexBuffer;

#include "azGlGpuBuffer.inl"

#endif // __azGlGpuBuffer__
