#include "azIRenderer.h"
#include "Render/azIGpuBuffer.h"
#include "Render/azIInputLayout.h"
#include "Render/azIShader.h"

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIRenderer::azIRenderer()
	: m_pIndexBuffer(NULL)
	, m_uIndexBufferStride(0)
	, m_pInputLayout(NULL)
	, m_pVertexShader(NULL)
	, m_pPixelShader(NULL)
	, m_pCgContext(NULL)
{
	for (azUInt uSlotIndex = 0; uSlotIndex < 16; uSlotIndex++)
	{
		m_apVertexBuffers[uSlotIndex] = NULL;
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::Initialize()
{
	// Set an error callback
	cgSetErrorCallback(&OnCgError);

	// Create Cg context
	m_pCgContext = cgCreateContext();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::Terminate()
{
	// Destroy Cg context
	azAssert(m_pCgContext!=NULL, "Cg context is missing");
	cgDestroyContext(m_pCgContext);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::OnCgError()
{
	azSz szCgErrorMessage = cgGetErrorString(cgGetError());
	azAssert(false, "Cg error : %s", szCgErrorMessage);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::SetVertexBuffer(azUInt a_uSlot, const azIGpuBuffer& a_rBuffer)
{
	m_apVertexBuffers[a_uSlot] = &a_rBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::DestroyVertexBuffer(azIGpuBuffer& a_rBuffer)
{
	a_rBuffer.Terminate();
	delete (&a_rBuffer);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::SetIndexBuffer(const azIGpuBuffer& a_rBuffer)
{
	m_pIndexBuffer = &a_rBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::DestroyIndexBuffer(azIGpuBuffer& a_rBuffer)
{
	a_rBuffer.Terminate();
	delete (&a_rBuffer);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::SetInputLayout(azIInputLayout const& a_rInputLayout)
{
	m_pInputLayout = &a_rInputLayout;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::DestroyInputLayout(azIInputLayout& a_rInputLayout)
{
	a_rInputLayout.Terminate();
	delete (&a_rInputLayout);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::SetVertexShader(azIShader& a_rShader)
{
	m_pVertexShader = &a_rShader;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::DestroyVertexShader(azIShader& a_rShader)
{
	a_rShader.Terminate();
	delete (&a_rShader);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::SetPixelShader(azIShader& a_rShader)
{
	m_pPixelShader = &a_rShader;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIRenderer::DestroyPixelShader(azIShader& a_rShader)
{
	a_rShader.Terminate();
	delete (&a_rShader);
}

