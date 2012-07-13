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


//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azIApplication::azIApplication()
	: m_pRenderer(NULL)
	, m_pVertexBuffer(NULL)
	, m_pInputLayout(NULL)
	, m_pVertexShader(NULL)
	, m_pPixelShader(NULL)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Initialize()
{
    azClassManager::GrabInstance().Initialize();
    azTestObject& rObject = azFactory::GrabInstance().CreateObject<azTestObject>();
    azFactory::GrabInstance().DestroyObject(rObject);


    /*
	m_pRenderer = new azGlRenderer();
	m_pRenderer->Initialize();

	struct azVertex
	{
		azFloat m_fX, m_fY, m_fZ;
		azUInt m_uColor;
	};

	azVertex aVertices[] =
	{
		{-200.f, -100.f, 0.f, 0xFFFF0000},
		{ 200.f, -100.f, 0.f, 0xFF00FF00},
		{-200.f,  100.f, 0.f, 0xFF0000FF},
		{ 200.f,  100.f, 0.f, 0xFFFFFFFF}
	};

	m_pVertexBuffer = &(m_pRenderer->CreateVertexBuffer(4 * sizeof(azVertex), azEBufferType::eStatic));
	m_pVertexBuffer->Fill(aVertices, 4 * sizeof(azVertex));

	m_pInputLayout = &(m_pRenderer->CreateInputLayout());
	m_pInputLayout->AddElement(0, azInputLayoutElement(azESemanticType::ePosition, 0, azEFormatType::eFloat3, sizeof(azVertex), 0));
	m_pInputLayout->AddElement(0, azInputLayoutElement(azESemanticType::eDiffuse, 0, azEFormatType::eColor, sizeof(azVertex), 3*sizeof(azFloat)));

	m_pVertexShader = &(m_pRenderer->CreateVertexShader());
	m_pPixelShader = &(m_pRenderer->CreatePixelShader());

    // Initialize projection matrix
	azMatrix4x4 oProjectionMatrix;
	oProjectionMatrix.BuildOrthoOffCenter(0.f, 0.f, 800.f, 600.f);
	//m_pRenderer->LoadMatrix(azEMatrixType::eProjection, oProjectionMatrix);

	//&(m_pRenderer->CreateTexture());

	azImage oImage;
	oImage.Load();
    */
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Terminate()
{
    /*
	m_pRenderer->DestroyVertexShader(*m_pVertexShader);
	m_pRenderer->DestroyPixelShader(*m_pPixelShader);

	m_pRenderer->DestroyVertexBuffer(*m_pVertexBuffer);
	m_pVertexBuffer = NULL;

	m_pRenderer->DestroyInputLayout(*m_pInputLayout);
	m_pInputLayout = NULL;

	m_pRenderer->Terminate();
	delete m_pRenderer;
	m_pRenderer = NULL;
    */

    azClassManager::GrabInstance().Terminate();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Update()
{
    /*
	azAssert(m_pRenderer != NULL, "Render is NULL");
	m_pRenderer->BeginScene();

	// Temp
	azMatrix4x4 oProjectionMatrix;
	oProjectionMatrix.BuildOrthoOffCenter(0.f, 0.f, 800.f, 600.f);

	 // Translation
    azMatrix4x4 oTranslation;
    oTranslation.BuildFromTranslate(400.f + 100.f * cos(GetTickCount() / 500.0f), 300.f, 0.f);

    // Rotation
    azMatrix4x4 oRotation;
	oRotation.BuildFromRotateZ(GetTickCount() / 1000.0f);

	//m_pRenderer->LoadMatrix(azEMatrixType::eModelView, oRotation * oTranslation);

	m_pRenderer->SetVertexBuffer(0, *m_pVertexBuffer);
	m_pRenderer->SetInputLayout(*m_pInputLayout);
	m_pRenderer->SetVertexShader(*m_pVertexShader);
	m_pRenderer->SetPixelShader(*m_pPixelShader);
	
	m_pVertexShader->SetParameter(azL("a_mModelProjMatrix"), oRotation * oTranslation * oProjectionMatrix);
	
	m_pRenderer->Bind();
	m_pRenderer->DrawPrimitives(azEPrimitiveType::eTriangleStrip, 0, 2);
	
	m_pRenderer->EndScene();
    */
}
