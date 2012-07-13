#include "azGlRenderer.h"
#include "azMain.h"
#include "Render/azGlGpuBuffer.h"
#include "Render/azGlRenderEnums.h"
#include "Render/azGlInputLayout.h"
#include "Render/azGlShader.h"
#include "Math/azMatrix4x4.h"
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
	m_hWindow = pMainInstance->GetWindow();
	m_hDeviceContext = GetDC(m_hWindow);

	// Choose the best pixel format
	azInt iFormat = ChoosePixelFormat(m_hDeviceContext, &oPixelDescriptor);
	azBool bRet = (0 != SetPixelFormat(m_hDeviceContext, iFormat, &oPixelDescriptor));
	azAssert(bRet, "Couldn't set pixel format");

	// Create the best rendering context
	m_hRenderingContext = wglCreateContext(m_hDeviceContext);
	bRet = (0 != wglMakeCurrent(m_hDeviceContext, m_hRenderingContext));
	azAssert(bRet, "Couldn't create the rendering context");

	// Load GL extensions
	LoadExtensions();

	// Default states
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	if (m_hRenderingContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRenderingContext);
	}

	// Free the device context
	if (m_hWindow && m_hDeviceContext)
	{
		ReleaseDC(m_hWindow, m_hDeviceContext);
	}

	azIRenderer::Terminate();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <class T> inline void LoadExtension(T& a_rpfnProc, azSz a_szExtensionName)
{
	a_rpfnProc = reinterpret_cast<T>(wglGetProcAddress(a_szExtensionName));
	azAssert(a_rpfnProc != NULL, "%s loading failed", a_szExtensionName);
}
#define azLoadExtension(Ext) LoadExtension(Ext, #Ext);

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::CheckExtension(azSz a_szExtensionName) const
{
	bool bRes = m_strExtensions.find(a_szExtensionName) != std::string::npos;
	azAssert(bRes, "%s is not supported", a_szExtensionName);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::LoadExtensions()
{
	m_strExtensions = reinterpret_cast<azSz>(glGetString(GL_EXTENSIONS));

	// Check for basics extensions
	CheckExtension(azL("GL_ARB_vertex_buffer_object"));
	CheckExtension(azL("GL_ARB_multitexture"));

	// Load needed extensions
	azLoadExtension(glBindBufferARB);
	azLoadExtension(glDeleteBuffersARB);
	azLoadExtension(glGenBuffersARB);
	azLoadExtension(glBufferDataARB);
	azLoadExtension(glBufferSubDataARB);
	azLoadExtension(glGetBufferSubDataARB);
	azLoadExtension(glMapBufferARB);
	azLoadExtension(glUnmapBufferARB);
	azLoadExtension(glActiveTextureARB);
	azLoadExtension(glClientActiveTextureARB);
	azLoadExtension(glCompressedTexImage2DARB);
	azLoadExtension(glCompressedTexSubImage2DARB);
	azLoadExtension(glVertexAttribPointerARB);
	azLoadExtension(glEnableVertexAttribArrayARB);
	azLoadExtension(glDisableVertexAttribArrayARB);
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
	SwapBuffers(m_hDeviceContext); 
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIGpuBuffer& azGlRenderer::CreateVertexBuffer(azUInt a_uSize, azEBufferType::Enum a_eBufferType)
{
	azGlVertexBuffer* pBuffer = new azGlVertexBuffer();
	pBuffer->Initialize(a_uSize, a_eBufferType);
	return *pBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIGpuBuffer& azGlRenderer::CreateIndexBuffer(azUInt a_uSize, azEBufferType::Enum a_eBufferType)
{
	azGlIndexBuffer* pBuffer = new azGlIndexBuffer();
	pBuffer->Initialize(a_uSize, a_eBufferType);
	return *pBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIInputLayout& azGlRenderer::CreateInputLayout()
{
	azGlInputLayout* pInputLayout = new azGlInputLayout();
	return *pInputLayout;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIShader& azGlRenderer::CreateVertexShader()
{
	azGlShader* pShader = new azGlShader();

	azSz szFilename = azL("F://Dev//Aztec//Bin//Debug//Shaders//Simple.vcg");
	CGprogram pProgram = cgCreateProgramFromFile(m_pCgContext, CG_SOURCE, szFilename, m_eVertexShaderProfile, azL("main"), NULL);
	pShader->Initialize(pProgram);

	return *pShader;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIShader& azGlRenderer::CreatePixelShader()
{
	azGlShader* pShader = new azGlShader();

	azSz szFilename = azL("F://Dev//Aztec//Bin//Debug//Shaders//Simple.pcg");
	CGprogram pProgram = cgCreateProgramFromFile(m_pCgContext, CG_SOURCE, szFilename, m_ePixelShaderProfile, azL("main"), NULL);
	pShader->Initialize(pProgram);

	return *pShader;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::Bind() const
{
	// Desactivate previous states
	glColor4f(0.f, 0.f, 0.f, 0.f);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	for (int i = 0; i < 4; ++i)
	{
		glActiveTextureARB(GL_TEXTURE0_ARB + i);
		glDisable(GL_TEXTURE_2D);
	}
	cgGLDisableProfile(m_eVertexShaderProfile);
	cgGLUnbindProgram(m_eVertexShaderProfile);
	cgGLDisableProfile(m_ePixelShaderProfile);
	cgGLUnbindProgram(m_ePixelShaderProfile);

    // Send index buffer to API, if any
    const azGlIndexBuffer* pIndexBuffer = static_cast<const azGlIndexBuffer*>(m_pIndexBuffer);
	if (pIndexBuffer)
	{
		glEnableClientState(GL_INDEX_ARRAY);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, pIndexBuffer->GetBufferId());

		// Save index stride
		//m_uIndexBufferStride = uIndexBufferStride;
	}

	// Send vertex buffers to API
	for (azUInt uStream = 0; uStream < 16; uStream++)
	{
		const azGlVertexBuffer* pVertexBuffer = static_cast<const azGlVertexBuffer*>(m_apVertexBuffers[uStream]);
		if (pVertexBuffer)
		{
			// Bind buffer before setting states and pointers
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, pVertexBuffer->GetBufferId());

			// Look at the input layout to setup the different states and pointers
			const azGlInputLayout* pInputLayout = static_cast<const azGlInputLayout*>(m_pInputLayout);
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
						// Texture coordonates
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
	if (m_pVertexShader)
	{
		cgGLBindProgram(m_pVertexShader->GetCgProgram());
		cgGLEnableProfile(m_eVertexShaderProfile);
	}

	if (m_pPixelShader)
	{
		cgGLBindProgram(m_pPixelShader->GetCgProgram());
		cgGLEnableProfile(m_ePixelShaderProfile);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::DrawPrimitives(azEPrimitiveType::Enum a_ePrimitiveType, azUInt a_uFirstVertex, azUInt a_uCount) const
{
	GLenum ePrimitiveType = azGlRenderEnums::GetNativePrimitiveType(a_ePrimitiveType);
	GLsizei uCount = azGlRenderEnums::GetNativePrimitiveVertexCount(a_ePrimitiveType, a_uCount);

	glDrawArrays(ePrimitiveType, a_uFirstVertex, uCount);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlRenderer::LoadMatrix(azEMatrixType::Enum a_eType, const azMatrix4x4& a_rMatrix)
{
    if (a_eType >= azEMatrixType::eTexture0)
	{
        glActiveTextureARB(GL_TEXTURE0_ARB + (a_eType - azEMatrixType::eTexture0));
	}

	glMatrixMode(azGlRenderEnums::GetNativeMatrixType(a_eType));
    glLoadMatrixf(a_rMatrix);
}