#include "azGlRenderer.h"
#include "azMain.h"
#include "Render/azGlGpuBuffer.h"
#include "Render/azGlRenderEnums.h"
#include "Render/azGlInputLayout.h"
#include "Render/azGlShader.h"
#include "Render/azGlTexture.h"
#include "Math/azMatrix4x4.h"
#include "Memory/azMemoryManager.h"
#include <windows.h>
#include <Cg/cgGL.h>

//----------------------------------------------------------------------------------------------------------------------
// OpenGL extensions
//----------------------------------------------------------------------------------------------------------------------
PFNGLBINDBUFFERARBPROC azGlRenderer::glBindBufferARB;
PFNGLDELETEBUFFERSARBPROC azGlRenderer::glDeleteBuffersARB;
PFNGLGENBUFFERSARBPROC azGlRenderer::glGenBuffersARB;
PFNGLBUFFERDATAARBPROC azGlRenderer::glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC azGlRenderer::glBufferSubDataARB;
PFNGLGETBUFFERSUBDATAARBPROC azGlRenderer::glGetBufferSubDataARB;
PFNGLMAPBUFFERARBPROC azGlRenderer::glMapBufferARB;
PFNGLUNMAPBUFFERARBPROC azGlRenderer::glUnmapBufferARB;

PFNGLACTIVETEXTUREARBPROC azGlRenderer::glActiveTextureARB;
PFNGLCLIENTACTIVETEXTUREARBPROC azGlRenderer::glClientActiveTextureARB;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC azGlRenderer::glCompressedTexImage2DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC azGlRenderer::glCompressedTexSubImage2DARB;

PFNGLVERTEXATTRIBPOINTERNVPROC azGlRenderer::glVertexAttribPointerARB;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC azGlRenderer::glEnableVertexAttribArrayARB;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC azGlRenderer::glDisableVertexAttribArrayARB;

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azGlRenderer::azGlRenderer()
	: azIRenderer()
	, m_hWindow(NULL)
	, m_hDeviceContext(NULL)
	, m_hRenderingContext(NULL)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::Initialize()
{
	azIRenderer::Initialize();

	azMain* pMainInstance = azMain::GetInstance();
	azAssert(pMainInstance != NULL, "Main is missing !");

	// Render parameters
	PIXELFORMATDESCRIPTOR oPixelDescriptor = 
	{ 
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
		1,                               // version number 
		PFD_DRAW_TO_WINDOW |             // support window 
		PFD_SUPPORT_OPENGL |             // support OpenGL 
		PFD_DOUBLEBUFFER,                // double buffered 
		PFD_TYPE_RGBA,                   // RGBA type 
		32,                              // 32-bit color depth 
		0, 0, 0, 0, 0, 0,                // color bits ignored 
		0,                               // no alpha buffer 
		0,                               // shift bit ignored 
		0,                               // no accumulation buffer 
		0, 0, 0, 0,                      // accum bits ignored 
		32,                              // 32-bit z-buffer 
		32,                              // 32-bits stencil buffer 
		0,                               // no auxiliary buffer 
		PFD_MAIN_PLANE,                  // main layer 
		0,                               // reserved 
		0, 0, 0                          // layer masks ignored 
	};

	// Get window and device context handles
	m_hWindow = pMainInstance->GetWindowHandle();
	m_hDeviceContext = GetDC((HWND)m_hWindow);

	// Choose the best pixel format
	azInt iFormat = ChoosePixelFormat((HDC)m_hDeviceContext, &oPixelDescriptor);
	azBool bRet = (0 != SetPixelFormat((HDC)m_hDeviceContext, iFormat, &oPixelDescriptor));
	azAssert(bRet, "Couldn't set pixel format");

	// Create the best rendering context
	m_hRenderingContext = wglCreateContext((HDC)m_hDeviceContext);
	bRet = (0 != wglMakeCurrent((HDC)m_hDeviceContext, (HGLRC)m_hRenderingContext));
	azAssert(bRet, "Couldn't create the rendering context");

	// Load GL extensions
	LoadExtensions();

	// Default states
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.0f);
	glClearStencil(0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);

	// Setup CG   
	m_eVertexShaderProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
    m_ePixelShaderProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    cgGLSetOptimalOptions(m_eVertexShaderProfile);
    cgGLSetOptimalOptions(m_ePixelShaderProfile);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::Terminate()
{
	// Delete the rendering context
	if (m_hRenderingContext != NULL)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext((HGLRC)m_hRenderingContext);
	}

	// Free the device context
	if ((m_hWindow != NULL) && (m_hDeviceContext!= NULL))
	{
		ReleaseDC((HWND)m_hWindow, (HDC)m_hDeviceContext);
	}

	azIRenderer::Terminate();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <class T> inline void LoadExtension(T& a_rpfnProc, azSzA a_szaExtensionName)
{
	a_rpfnProc = reinterpret_cast<T>(wglGetProcAddress(a_szaExtensionName));
	azAssert(a_rpfnProc != NULL, "%s loading failed", a_szaExtensionName);
}
#define azGlLoadExtension(Ext) LoadExtension(Ext, azStringizeA(Ext));

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::CheckExtension(azSzA a_szaExtensionName) const
{
	bool bRes = m_straExtensions.find(a_szaExtensionName) != azString::npos;
	azAssert(bRes, "%s is not supported", a_szaExtensionName);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::LoadExtensions()
{
	m_straExtensions = reinterpret_cast<azSzA>(glGetString(GL_EXTENSIONS));

	// Check for basics extensions
	CheckExtension("GL_ARB_vertex_buffer_object");
	CheckExtension("GL_ARB_multitexture");

	// Load needed extensions
	azGlLoadExtension(glBindBufferARB);
	azGlLoadExtension(glDeleteBuffersARB);
	azGlLoadExtension(glGenBuffersARB);
	azGlLoadExtension(glBufferDataARB);
	azGlLoadExtension(glBufferSubDataARB);
	azGlLoadExtension(glGetBufferSubDataARB);
	azGlLoadExtension(glMapBufferARB);
	azGlLoadExtension(glUnmapBufferARB);
	azGlLoadExtension(glActiveTextureARB);
	azGlLoadExtension(glClientActiveTextureARB);
	azGlLoadExtension(glCompressedTexImage2DARB);
	azGlLoadExtension(glCompressedTexSubImage2DARB);
	azGlLoadExtension(glVertexAttribPointerARB);
	azGlLoadExtension(glEnableVertexAttribArrayARB);
	azGlLoadExtension(glDisableVertexAttribArrayARB);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::BeginScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::EndScene()
{
	SwapBuffers((HDC)m_hDeviceContext); 
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIGpuBuffer& azGlRenderer::CreateVertexBuffer(azUInt a_uSize, azEBufferType::Enum a_eBufferType)
{
	azGlVertexBuffer& rBuffer = azNew(azGlVertexBuffer);
	rBuffer.Initialize(a_uSize, a_eBufferType);
	return rBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIGpuBuffer& azGlRenderer::CreateIndexBuffer(azUInt a_uSize, azEBufferType::Enum a_eBufferType)
{
	azGlIndexBuffer& rBuffer = azNew(azGlIndexBuffer);
	rBuffer.Initialize(a_uSize, a_eBufferType);
	return rBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIInputLayout& azGlRenderer::CreateInputLayout()
{
	azGlInputLayout& rInputLayout = azNew(azGlInputLayout);
    rInputLayout.Initialize();
	return rInputLayout;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIShader& azGlRenderer::CreateVertexShader(azCBytes a_pProgram)
{
	azGlShader& rShader = azNew(azGlShader);

	CGprogram pProgram = cgCreateProgram(m_pCgContext, CG_SOURCE, reinterpret_cast<azSzA>(a_pProgram), m_eVertexShaderProfile, "main", NULL);
	rShader.Initialize(pProgram);

	return rShader;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIShader& azGlRenderer::CreatePixelShader(azCBytes a_pProgram)
{
	azGlShader& rShader = azNew(azGlShader);

	CGprogram pProgram = cgCreateProgram(m_pCgContext, CG_SOURCE, reinterpret_cast<azSzA>(a_pProgram), m_ePixelShaderProfile, "main", NULL);
	rShader.Initialize(pProgram);

	return rShader;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azITexture& azGlRenderer::CreateTexture(azImage const& a_rImage)
{
    azITexture& rTexture = azNew(azGlTexture);
    rTexture.Initialize(a_rImage);
    return rTexture;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::Bind() const
{
	// Disable previous states
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

    // Send index buffer to API, if any
	if (m_pIndexBuffer != NULL)
	{
        const azGlIndexBuffer* pIndexBuffer = static_cast<const azGlIndexBuffer*>(m_pIndexBuffer);
        azAssert(pIndexBuffer != NULL, "");

        glEnableClientState(GL_INDEX_ARRAY);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, pIndexBuffer->GetBufferId());

		// Save index stride
		//m_uIndexBufferStride = uIndexBufferStride;
	}
    else
    {
        glDisableClientState(GL_INDEX_ARRAY);
    }

	// Send vertex buffers to API
	for (azUInt uStream = 0; uStream < 16; uStream++)
	{
        azIGpuBuffer const* pIBuffer = m_apVertexBuffers[uStream];
        if (pIBuffer != NULL)
        {
		    azGlVertexBuffer const* pVertexBuffer = static_cast<azGlVertexBuffer const*>(pIBuffer);
		    azAssert(pVertexBuffer != NULL, "");

		    // Bind buffer before setting states and pointers
		    glBindBufferARB(GL_ARRAY_BUFFER_ARB, pVertexBuffer->GetBufferId());

		    // Look at the input layout to setup the different states and pointers
		    azGlInputLayout const* pInputLayout = static_cast<azGlInputLayout const*>(m_pInputLayout);
            azAssert(pInputLayout != NULL, "");

		    azInputLayoutElements const& rvElements = pInputLayout->GetElements(uStream);
		    for(azInputLayoutElements::const_iterator it = rvElements.begin(); it != rvElements.end(); it++)
		    {
			    azInputLayoutElement const& rElement = *it;
			    GLint iGlSize = azGlRenderEnums::GetNativeFormatSize(rElement.m_eFormatType);
			    GLenum eGlType = azGlRenderEnums::GetNativeFormatType(rElement.m_eFormatType);
			    GLsizei uStride = rElement.m_uStride;
			    azUInt uOffset = rElement.m_uOffset; // + MinVertex * uStride

			    GLenum eGlUsage = azGlRenderEnums::GetNativeSemanticType(rElement.m_eSemanticType);
			    // Generic attributes
			    if (eGlUsage == 0)
			    {
				    GLuint uSemanticsIndex = rElement.m_uSemanticIndex;
				    glEnableVertexAttribArrayARB(uSemanticsIndex);
				    glVertexAttribPointerARB(uSemanticsIndex, iGlSize, eGlType, uStride, (GLvoid*)uOffset);
			    }
			    // Specific attributes
			    else
			    {
				    switch (rElement.m_eSemanticType)
				    {
					    // Position
					    case azESemanticType::ePosition :
					    {
						    glVertexPointer(iGlSize, eGlType, uStride, (GLvoid*)uOffset);
						    break;
					    }
					    // Normal
					    case azESemanticType::eNormal :
					    {
						    glNormalPointer(eGlType, uStride, (GLvoid*)uOffset);
						    break;
					    }
					    // Diffuse color
					    case azESemanticType::eDiffuse :
					    {
						    glColorPointer(iGlSize, eGlType, uStride, (GLvoid*)uOffset);
						    break;
					    }
					    // Texture coordinates
					    case azESemanticType::eTexCoord :
					    {
						    GLuint uSemanticsIndex = rElement.m_uSemanticIndex;
						    glActiveTextureARB(GL_TEXTURE0_ARB + uSemanticsIndex);
						    glEnable(GL_TEXTURE_2D);
						    glClientActiveTextureARB(GL_TEXTURE0_ARB + uSemanticsIndex);
						    glTexCoordPointer(iGlSize, eGlType, uStride, (GLvoid*)uOffset);
						    break;
					    }
				    }
				    glEnableClientState(eGlUsage);
			    }
            }
		}
	}

	// Set shaders
	if (m_pVertexShader != NULL)
	{
		cgGLBindProgram(m_pVertexShader->GetCgProgram());
		cgGLEnableProfile(m_eVertexShaderProfile);
	}
    else
    {
        cgGLDisableProfile(m_eVertexShaderProfile);
        cgGLUnbindProgram(m_eVertexShaderProfile);
    }

	if (m_pPixelShader != NULL)
	{
		cgGLBindProgram(m_pPixelShader->GetCgProgram());
		cgGLEnableProfile(m_ePixelShaderProfile);
	}
    else
    {
        cgGLDisableProfile(m_ePixelShaderProfile);
        cgGLUnbindProgram(m_ePixelShaderProfile);
    }

    // Set texture
    if (m_pTexture != NULL)
    {
        glActiveTextureARB(GL_TEXTURE0_ARB + 0 /*+ Unit*/); // todo : handle more than one unit

        azGlTexture const* pTexture = static_cast<azGlTexture const*>(m_pTexture);
        azAssert(pTexture != NULL, "");
        glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureId());
    }
    else
    {
        glActiveTextureARB(GL_TEXTURE0_ARB + 0 /*+ Unit*/); // todo : handle more than one unit
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::DrawPrimitives(azEPrimitiveType::Enum a_ePrimitiveType, azUInt a_uFirstVertex, azUInt a_uCount) const
{
	GLenum ePrimitiveType = azGlRenderEnums::GetNativePrimitiveType(a_ePrimitiveType);
	GLsizei uCount = azGlRenderEnums::GetNativePrimitiveVertexCount(a_ePrimitiveType, a_uCount);

    if (m_pIndexBuffer == NULL)
    {
    	glDrawArrays(ePrimitiveType, a_uFirstVertex, uCount);
    }
    else
    {
        GLenum eIndexType = (m_uIndexBufferStride == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
        GLvoid* pAddress = ((azByte*)NULL) + a_uFirstVertex * m_uIndexBufferStride;
        glDrawElements(ePrimitiveType, uCount, eIndexType, pAddress);
    }
}


