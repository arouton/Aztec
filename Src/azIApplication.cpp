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

static double g_dOldTime = 0.f;
static azFloat g_fTime = 0.f;

static azUInt g_uFrameCount = 0;
static azFloat g_fAverageDeltaTime = 0.f;

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
		{-1.f, -1.f, -1.f, 0xFFFF0000, 0.f, 0.f},
		{ 1.f, -1.f, -1.f, 0xFF00FF00, 3.f, 0.f},
		{-1.f,  1.f, -1.f, 0xFF0000FF, 0.f, 3.f},
		{ 1.f,  1.f, -1.f, 0xFFFFFFFF, 3.f, 3.f},
        {-1.f, -1.f, 1.f, 0xFFFF0000, 0.f, 0.f},
        { 1.f, -1.f, 1.f, 0xFF00FF00, 3.f, 0.f},
        { 1.f,  1.f, 1.f, 0xFFFFFFFF, 3.f, 3.f},
        {-1.f,  1.f, 1.f, 0xFF0000FF, 0.f, 3.f}
	};

	m_rVertexBuffer = rRenderer.CreateVertexBuffer(8 * sizeof(azVertex), azEBufferType::eStatic);
	m_rVertexBuffer.GetRef().Fill(aVertices, 8 * sizeof(azVertex));

	m_rInputLayout = rRenderer.CreateInputLayout();
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::ePosition, 0, azEFormatType::eFloat3, sizeof(azVertex), 0));
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::eDiffuse, 0, azEFormatType::eColor, sizeof(azVertex), 3*sizeof(azFloat)));
    m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::eTexCoord, 0, azEFormatType::eFloat2, sizeof(azVertex), 3*sizeof(azFloat) + sizeof(azUInt32)));

    azUInt aIndices[] = {3, 2, 6, 7, 4, 2, 0, 3, 1, 6, 5, 4, 1, 0};

    m_rIndexBuffer = rRenderer.CreateIndexBuffer(14 * sizeof(azUInt), azEBufferType::eStatic);
    m_rIndexBuffer.GetRef().Fill(aIndices, 14 * sizeof(azUInt));

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

    LARGE_INTEGER lpPerformanceCount;
    BOOL bRes = QueryPerformanceCounter(&lpPerformanceCount);
    g_dOldTime = double(lpPerformanceCount.QuadPart);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Update()
{
    azIRenderer& rRenderer = m_rRenderer.GetRef();
	rRenderer.BeginScene();

    LARGE_INTEGER lpFrequency;
    BOOL bRes = QueryPerformanceFrequency(&lpFrequency);
    LARGE_INTEGER lpPerformanceCount;
    bRes = QueryPerformanceCounter(&lpPerformanceCount);

    double dNewTime = double(lpPerformanceCount.QuadPart);
    double dWindowsDeltaTime = (dNewTime - g_dOldTime) / double(lpFrequency.QuadPart);
    azFloat fDeltaTime = azFloat(dWindowsDeltaTime);
    g_dOldTime = dNewTime;
    g_fTime += fDeltaTime;

    g_fAverageDeltaTime = (g_uFrameCount * g_fAverageDeltaTime + fDeltaTime) / (g_uFrameCount + 1);
    g_uFrameCount++;

	// Temp
	//azMatrix4x4 oLookAtMatrix;
    //oLookAtMatrix.BuildLookAt(azVector3(0.f, 0.f, 25.f), azVector3(0.f, 0.f, 0.f), azVector3(0.f, 0.f, 1.f));
    azMatrix4x4 oProjectionMatrix;
    //oProjectionMatrix.BuildPerspectiveFOV(90.f, 1.f, 0.1f, 100.f);
    //oProjectionMatrix = oProjectionMatrix * oLookAtMatrix;
    oProjectionMatrix.BuildOrthoOffCenter(-2.f, -2.f, 2.f, 2.f);

    // Translation
    azMatrix4x4 oTranslation;
    oTranslation.BuildFromTranslate(1.f * cos(2.f * 3.14f * 0.1f * g_fTime), 0.f, -1.f);

    // Rotation
    azMatrix4x4 oRotationX;
    oRotationX.BuildFromRotateX(2.f * 3.14f * 0.15f * g_fTime);
    azMatrix4x4 oRotationY;
    oRotationY.BuildFromRotateY(2.f * 3.14f * 0.1f * g_fTime);
    azMatrix4x4 oRotationZ;
    oRotationZ.BuildFromRotateZ(2.f * 3.14f * 0.2f * g_fTime);

	rRenderer.SetVertexBuffer(0, m_rVertexBuffer);
	rRenderer.SetInputLayout(m_rInputLayout);
    rRenderer.SetIndexBuffer(m_rIndexBuffer, 4);
	rRenderer.SetVertexShader(m_rVertexShader);
	rRenderer.SetPixelShader(m_rPixelShader);
    //rRenderer.SetTexture(m_rTexture);
	
	m_rVertexShader.GetRef().SetParameter(azL("a_mModelProjMatrix"), oRotationX * oRotationY * oRotationZ * oTranslation * oProjectionMatrix);
    m_rVertexShader.GetRef().SetParameter(azL("a_fTime"), cos(2.f * 3.14f * 0.25f * g_fTime));
	
	rRenderer.Bind();
	rRenderer.DrawPrimitives(azEPrimitiveType::eTriangleStrip, 0, 12);
	
	rRenderer.EndScene();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Terminate()
{
    azIRenderer& rRenderer = m_rRenderer.GetRef();

    rRenderer.DestroyTexture(m_rTexture);
    rRenderer.DestroyVertexShader(m_rVertexShader);
    rRenderer.DestroyPixelShader(m_rPixelShader);
    rRenderer.DestroyIndexBuffer(m_rIndexBuffer);
    rRenderer.DestroyInputLayout(m_rInputLayout);
    rRenderer.DestroyVertexBuffer(m_rVertexBuffer);

    rRenderer.Terminate();
    azDelete(rRenderer);

    // \todo Registration function
    azClassManager::GrabInstance().Terminate();
    azMemoryManager::GrabInstance().DumpLeaks();
}