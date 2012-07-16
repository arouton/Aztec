#include "azIApplication.h"
#include "Render/azGlRenderer.h"
#include "Render/azIGpuBuffer.h"
#include "Render/azIShader.h"
#include "Render/azIInputLayout.h"
#include "Math/azMatrix4x4.h"

#include "Render/azImage.h"

#include "Object/azClassManager.h"
#include "Object/azTestObject.h"
#include "Object/azFactory.h"
#include "Memory/azMemoryManager.h"

#include "File/azCrtFile.h"

struct azVertex
{
    azFloat m_fX, m_fY, m_fZ;
    azUInt m_uColor;
};

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Initialize()
{
    // \todo Registration function
    azClassManager::GrabInstance().Initialize();
    azTestObject& rObject = azFactory::GrabInstance().CreateObject<azTestObject>();
    azFactory::GrabInstance().DestroyObject(rObject);

	azIRenderer& rRenderer = azNew(azGlRenderer);
    m_rRenderer = rRenderer;
	rRenderer.Initialize();

	azVertex aVertices[] =
	{
		{-200.f, -100.f, 0.f, 0xFFFF0000},
		{ 200.f, -100.f, 0.f, 0xFF00FF00},
		{-200.f,  100.f, 0.f, 0xFF0000FF},
		{ 200.f,  100.f, 0.f, 0xFFFFFFFF}
	};

	m_rVertexBuffer = rRenderer.CreateVertexBuffer(4 * sizeof(azVertex), azEBufferType::eDynamic);
	m_rVertexBuffer.GetRef().Fill(aVertices, 4 * sizeof(azVertex));

	m_rInputLayout = rRenderer.CreateInputLayout();
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::ePosition, 0, azEFormatType::eFloat3, sizeof(azVertex), 0));
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::eDiffuse, 0, azEFormatType::eColor, sizeof(azVertex), 3*sizeof(azFloat)));

    azCrtFile oVertexShaderFile;
    oVertexShaderFile.Open(azFilePath(azL("Shaders\\Simple.vcg")), azFileOpenParams(azEReadWriteMode::eRead));
    oVertexShaderFile.Close();

	m_rVertexShader = rRenderer.CreateVertexShader(azL("Shaders\\Simple.vcg"));
	m_rPixelShader = rRenderer.CreatePixelShader(azL("Shaders\\Simple.vcg"));

    // Initialize projection matrix
	azMatrix4x4 oProjectionMatrix;
	oProjectionMatrix.BuildOrthoOffCenter(0.f, 0.f, 800.f, 600.f);
	//rRenderer.LoadMatrix(azEMatrixType::eProjection, oProjectionMatrix);

	//&(rRenderer.CreateTexture());

	azImage oImage;
	oImage.Load();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Terminate()
{
    azIRenderer& rRenderer = m_rRenderer.GetRef();
    
    rRenderer.DestroyVertexShader(m_rVertexShader.GetRef());
	rRenderer.DestroyPixelShader(m_rPixelShader.GetRef());

	rRenderer.DestroyVertexBuffer(m_rVertexBuffer.GetRef());

	rRenderer.DestroyInputLayout(m_rInputLayout.GetRef());

	rRenderer.Terminate();
	azDelete(rRenderer);

    // \todo Registration function
    azClassManager::GrabInstance().Terminate();
    azMemoryManager::GrabInstance().DumpLeaks();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Update()
{
    azIRenderer& rRenderer = m_rRenderer.GetRef();
	rRenderer.BeginScene();

	// Temp
	azMatrix4x4 oProjectionMatrix;
	oProjectionMatrix.BuildOrthoOffCenter(0.f, 0.f, 800.f, 600.f);

	 // Translation
    azMatrix4x4 oTranslation;
    oTranslation.BuildFromTranslate(400.f + 100.f * cos(GetTickCount() / 500.0f), 300.f, 0.f);

    // Rotation
    azMatrix4x4 oRotation;
	oRotation.BuildFromRotateZ(GetTickCount() / 1000.0f);

	//rRenderer.LoadMatrix(azEMatrixType::eModelView, oRotation * oTranslation);

    azVertex aVertices[] =
    {
        {-200.f + 50.f * cos(GetTickCount() / 500.0f), -100.f, 0.f, 0xFFFF0000},
        { 200.f, -100.f, 0.f, 0xFF00FF00},
        {-200.f,  100.f, 0.f, 0xFF0000FF},
        { 200.f,  100.f, 0.f, 0xFFFFFFFF}
    };
    m_rVertexBuffer.GetRef().Fill(aVertices, 4 * sizeof(azVertex));


	rRenderer.SetVertexBuffer(0, m_rVertexBuffer);
	rRenderer.SetInputLayout(m_rInputLayout);
	rRenderer.SetVertexShader(m_rVertexShader);
	rRenderer.SetPixelShader(m_rPixelShader);
	
	m_rVertexShader.GetRef().SetParameter(azL("a_mModelProjMatrix"), oRotation * oTranslation * oProjectionMatrix);
	
	rRenderer.Bind();
	rRenderer.DrawPrimitives(azEPrimitiveType::eTriangleStrip, 0, 2);
	
	rRenderer.EndScene();
}
