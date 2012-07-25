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
    azFloat m_fU, m_fV;
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
		{-100.f, -100.f, 0.f, 0xFFFF0000, 0.f, 0.f},
		{ 100.f, -100.f, 0.f, 0xFF00FF00, 1.f, 0.f},
		{-100.f,  100.f, 0.f, 0xFF0000FF, 1.f, 1.f},
		{ 100.f,  100.f, 0.f, 0xFFFFFFFF, 0.f, 1.f}
	};

	m_rVertexBuffer = rRenderer.CreateVertexBuffer(4 * sizeof(azVertex), azEBufferType::eStatic);
	m_rVertexBuffer.GetRef().Fill(aVertices, 4 * sizeof(azVertex));

	m_rInputLayout = rRenderer.CreateInputLayout();
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::ePosition, 0, azEFormatType::eFloat3, sizeof(azVertex), 0));
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::eDiffuse, 0, azEFormatType::eColor, sizeof(azVertex), 3*sizeof(azFloat)));
    m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::eTexCoord, 0, azEFormatType::eFloat2, sizeof(azVertex), 3*sizeof(azFloat) + sizeof(azUInt32)));

    azUInt aIndices[] = { 0, 1, 2, 3 };

    m_rIndexBuffer = rRenderer.CreateIndexBuffer(4, azEBufferType::eStatic);
    m_rIndexBuffer.GetRef().Fill(aIndices, 4 * sizeof(azUInt));

    azCrtFile oVertexShaderFile;
    oVertexShaderFile.Open(azFilePath(azL("Shaders\\Simple.vcg")), azFileOpenParams(azEReadWriteMode::eRead, azECreateMode::eOpenExisting));
    oVertexShaderFile.Seek(0, azEFilePosition::eEnd);
    azUInt uVertexShaderSize = oVertexShaderFile.Tell();
    oVertexShaderFile.Seek(0, azEFilePosition::eBeginning);
    azBytes pVertexShaderBuffer = azNewArray(azByte, uVertexShaderSize+1);
    oVertexShaderFile.Read(pVertexShaderBuffer, uVertexShaderSize);
    oVertexShaderFile.Close();
    pVertexShaderBuffer[uVertexShaderSize] = 0;
    m_rVertexShader = rRenderer.CreateVertexShader(pVertexShaderBuffer);
    azDeleteArray(pVertexShaderBuffer, uVertexShaderSize+1);

    azCrtFile oPixelShaderFile;
    oPixelShaderFile.Open(azFilePath(azL("Shaders\\Simple.pcg")), azFileOpenParams(azEReadWriteMode::eRead, azECreateMode::eOpenExisting));
    oPixelShaderFile.Seek(0, azEFilePosition::eEnd);
    azUInt uPixelShaderSize = oPixelShaderFile.Tell();
    oPixelShaderFile.Seek(0, azEFilePosition::eBeginning);
    azBytes pPixelShaderBuffer = azNewArray(azByte, uPixelShaderSize+1);
    oPixelShaderFile.Read(pPixelShaderBuffer, uPixelShaderSize);
    oPixelShaderFile.Close();
    pPixelShaderBuffer[uPixelShaderSize] = 0;
    m_rPixelShader = rRenderer.CreatePixelShader(pPixelShaderBuffer);
    azDeleteArray(pPixelShaderBuffer, uPixelShaderSize+1);

    azImage oImage;
    oImage.Initialize();
    m_rTexture = rRenderer.CreateTexture(oImage);
    oImage.Terminate();

    // Initialize projection matrix
	azMatrix4x4 oProjectionMatrix;
	oProjectionMatrix.BuildOrthoOffCenter(0.f, 0.f, 800.f, 600.f);
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

	rRenderer.SetVertexBuffer(0, m_rVertexBuffer);
	rRenderer.SetInputLayout(m_rInputLayout);
    rRenderer.SetIndexBuffer(m_rIndexBuffer);
	rRenderer.SetVertexShader(m_rVertexShader);
	rRenderer.SetPixelShader(m_rPixelShader);
    rRenderer.SetTexture(m_rTexture);
	
	m_rVertexShader.GetRef().SetParameter(azL("a_mModelProjMatrix"), oRotation * oTranslation * oProjectionMatrix);
    m_rVertexShader.GetRef().SetParameter(azL("a_fTime"), cos((azFloat)GetTickCount()));
	
	rRenderer.Bind();
	rRenderer.DrawPrimitives(azEPrimitiveType::eTriangleStrip, 0, 2);
	
	rRenderer.EndScene();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Terminate()
{
    azIRenderer& rRenderer = m_rRenderer.GetRef();

    rRenderer.DestroyVertexShader(m_rVertexShader);
    rRenderer.DestroyPixelShader(m_rPixelShader);
    rRenderer.DestroyIndexBuffer(m_rIndexBuffer);
    rRenderer.DestroyVertexBuffer(m_rVertexBuffer);
    rRenderer.DestroyInputLayout(m_rInputLayout);
    rRenderer.DestroyTexture(m_rTexture);

    rRenderer.Terminate();
    azDelete(rRenderer);

    // \todo Registration function
    azClassManager::GrabInstance().Terminate();
    azMemoryManager::GrabInstance().DumpLeaks();
}