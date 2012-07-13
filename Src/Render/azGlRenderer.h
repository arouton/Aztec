#ifndef __azGlRenderer__
#define __azGlRenderer__

#include "azCommon.h"
#include "Render/azIRenderer.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glext.h>
#include <string>

class azIGpuBuffer;
class azIInputLayout;
class azMatrix4x4;

// \class azGlRenderer
// \brief OpenGL renderer
class AZ_API azGlRenderer : public azIRenderer
{
public:
	// \brief Constructor
	azGlRenderer();

	// \brief Virtual destructor
	virtual ~azGlRenderer() {}

	// \brief Initialize
	virtual void Initialize();

	// \brief Terminate
	virtual void Terminate();

	// \brief Begin scene
	virtual void BeginScene();

	// \brief End scene
	virtual void EndScene();


	// \brief Create a vertex buffer impl
	virtual azIGpuBuffer& CreateVertexBuffer(azUInt a_uSize, azEBufferType::Enum a_eBufferType);

	// \brief Create an index buffer impl
	virtual azIGpuBuffer& CreateIndexBuffer(azUInt a_uSize, azEBufferType::Enum a_eBufferType);

	// \brief Create input layout
	virtual azIInputLayout& CreateInputLayout();

	// \brief Create vertex shader
	virtual azIShader& CreateVertexShader() ;

	// \brief Create pixel shader
	virtual azIShader& CreatePixelShader();


	// \brief Load matrix
	virtual void LoadMatrix(azEMatrixType::Enum a_eType, const azMatrix4x4& a_rMatrix);


	// \brief Bind
	virtual void Bind() const;

	// \brief Draw
	virtual void DrawPrimitives(azEPrimitiveType::Enum a_ePrimitiveType, azUInt a_uFirstVertex, azUInt a_uCount) const;


	// GL extensions
	static PFNGLBINDBUFFERARBPROC glBindBufferARB;
	static PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
	static PFNGLGENBUFFERSARBPROC glGenBuffersARB;
	static PFNGLBUFFERDATAARBPROC glBufferDataARB;
	static PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
	static PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;
	static PFNGLMAPBUFFERARBPROC glMapBufferARB;
	static PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;

    static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
    static PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
    static PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	glCompressedTexImage2DARB;
    static PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2DARB;

	static PFNGLVERTEXATTRIBPOINTERNVPROC glVertexAttribPointerARB;
	static PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
	static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;

private:
	// \brief Check extension
	void CheckExtension(azSz a_szExtensionName) const;

	// \brief Load extensions
	void LoadExtensions();

	// Window
	HWND m_hWindow;

	// Device context
	HDC m_hDeviceContext;
	
	// Rendering context
	HGLRC m_hRenderingContext;
	
	// Supported extensions
	std::string m_strExtensions;
};

#endif // __azGlRenderer__
