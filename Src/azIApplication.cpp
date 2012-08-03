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

#include "azMain.h"

struct azVertex
{
    azFloat m_fX, m_fY, m_fZ;
    azUInt m_uColor;
    //azFloat m_fU, m_fV;
};

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Initialize()
{
    m_oTimer.Initialize();

    // \todo Registration function
    azClassManager::GrabInstance().Initialize();
    azTestObject& rObject = azFactory::GrabInstance().CreateObject<azTestObject>();
    azFactory::GrabInstance().DestroyObject(rObject);

	azIRenderer& rRenderer = azNew(azGlRenderer);
    m_rRenderer = rRenderer;
	rRenderer.Initialize();

    //azVertex aVertices[] =
    //{
    //    {-1.f, -1.f, -1.f, 0xFFFF0000, 0.f, 0.f},
    //    { 1.f, -1.f, -1.f, 0xFF00FF00, 3.f, 0.f},
    //    {-1.f,  1.f, -1.f, 0xFF0000FF, 0.f, 3.f},
    //    { 1.f,  1.f, -1.f, 0xFFFFFFFF, 3.f, 3.f},
    //    {-1.f, -1.f, 1.f, 0xFFFF0000, 0.f, 0.f},
    //    { 1.f, -1.f, 1.f, 0xFF00FF00, 3.f, 0.f},
    //    { 1.f,  1.f, 1.f, 0xFFFFFFFF, 3.f, 3.f},
    //    {-1.f,  1.f, 1.f, 0xFF0000FF, 0.f, 3.f}
    //};
    azVertex aVertices[] =
    {
        { 0.f, 0.f, 0.f, 0xFFFF0000},
        { 1.f, 0.f, 0.f, 0xFFFF0000},
        { 0.f, 0.f, 0.f, 0xFF00FF00},
        { 0.f, 1.f, 0.f, 0xFF00FF00},
        { 0.f, 0.f, 0.f, 0xFF0000FF},
        { 0.f, 0.f, 1.f, 0xFF0000FF},
    };
	m_rVertexBuffer = rRenderer.CreateVertexBuffer(6 * sizeof(azVertex), azEBufferType::eStatic);
	m_rVertexBuffer.GetRef().Fill(aVertices, 6 * sizeof(azVertex));

	m_rInputLayout = rRenderer.CreateInputLayout();
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::ePosition, 0, azEFormatType::eFloat3, sizeof(azVertex), 0));
	m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::eDiffuse, 0, azEFormatType::eColor, sizeof(azVertex), 3*sizeof(azFloat)));
    //m_rInputLayout.GetRef().AddElement(0, azInputLayoutElement(azESemanticType::eTexCoord, 0, azEFormatType::eFloat2, sizeof(azVertex), 3*sizeof(azFloat) + sizeof(azUInt32)));

    //azUInt aIndices[] = {3, 2, 6, 7, 4, 2, 0, 3, 1, 6, 5, 4, 1, 0};
    azUInt aIndices[] = {0, 1, 2, 3, 4, 5};

    m_rIndexBuffer = rRenderer.CreateIndexBuffer(6 * sizeof(azUInt), azEBufferType::eStatic);
    m_rIndexBuffer.GetRef().Fill(aIndices, 6 * sizeof(azUInt));

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
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIApplication::Update()
{
    m_oTimer.Update();
    azFloat fTime = m_oTimer.GetTime();

    azIRenderer& rRenderer = m_rRenderer.GetRef();
	rRenderer.BeginScene();

    {
        azMatrix4x4 oProjectionMatrix;
        //azFloat fLeft = -10.f;
        //azFloat fRight = 12.f;
        //azFloat fBottom = -5.f;
        //azFloat fTop = 7.f;
        //azFloat fNear = 4.f;
        //azFloat fFar = 100.f;
        azFloat fLeft = -10.f;
        azFloat fRight = 10.f;
        azFloat fBottom = -15.f;
        azFloat fTop = 15.f;
        azFloat fNear = 10.f;
        azFloat fFar = 100.f;
        oProjectionMatrix.BuildPerspectiveProjection(fLeft, fRight, fBottom, fTop, fNear, fFar);
        
        azVector4 f4Vector;
        azVector4 f4VectorRes;

        f4Vector.Set(0.f, 0.f, -fNear, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);
        f4VectorRes /= f4VectorRes.m_fW;
        azAssert(f4VectorRes == azVector4(0.f, 0.f, -1.f, 1.f), "UTest failed");

        f4Vector.Set(0.f, 0.f, -fFar, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);
        f4VectorRes /= f4VectorRes.m_fW;
        azAssert(f4VectorRes == azVector4(0.f, 0.f, 1.f, 1.f), "UTest failed");

        f4Vector.Set(0.f, 0.f, fNear, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);

        f4Vector.Set(0.f, 0.f, fFar, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);

        f4Vector.Set(fLeft, fBottom, fNear, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);

        f4Vector.Set(fRight, fTop, fNear, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);

        f4Vector.Set(fLeft, fBottom, fFar, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);

        f4Vector.Set(fRight, fTop, fFar, 1.f);
        f4VectorRes = oProjectionMatrix.Transform(f4Vector);
    }



	// Temp
    azMatrix4x4 oProjectionMatrix;
    oProjectionMatrix.BuildPerspectiveFOV(90.f, 800.f/600.f, 0.1f, 100.f);
    //oProjectionMatrix = oProjectionMatrix * oLookAtMatrix;
    //oProjectionMatrix.BuildOrthoOffCenter(-2.f, 2.f, 2.f, -2.f);

    //// Translation
    azMatrix4x4 oTranslation;
    oTranslation.BuildFromTranslate(azMain::GetInstance()->m_fX, azMain::GetInstance()->m_fY, azMain::GetInstance()->m_fZ - 2.f);
    //oTranslation.BuildFromTranslate(0.f, 0.0f, -2.f);

    azMatrix4x4 oLookAtMatrix;
    //cos(2.f * 3.14f * 0.15f * fTime), sin(2.f * 3.14f * 0.15f * fTime)
    oLookAtMatrix.BuildLookAt(azVector3(0.5f * cos(2.f * 3.14f * 0.15f * fTime), 0.5f * sin(2.f * 3.14f * 0.15f * fTime), 10.f), azVector3(0.f, 0.f, 11.f), azVector3(0.f, 1.f, 0.f));

    //// Rotation
    //azMatrix4x4 oRotationX;
    //oRotationX.BuildFromRotateX(2.f * 3.14f * 0.15f * fTime);
    //azMatrix4x4 oRotationY;
    //oRotationY.BuildFromRotateY(2.f * 3.14f * 0.1f * fTime);
    //azMatrix4x4 oRotationZ;
    //oRotationZ.BuildFromRotateZ(2.f * 3.14f * 0.2f * fTime);
    //azMatrix4x4 oRotation = oTranslation * oRotationX * oRotationY * oRotationZ;

	rRenderer.SetVertexBuffer(0, m_rVertexBuffer);
	rRenderer.SetInputLayout(m_rInputLayout);
    rRenderer.SetIndexBuffer(m_rIndexBuffer, 6);
	rRenderer.SetVertexShader(m_rVertexShader);
	rRenderer.SetPixelShader(m_rPixelShader);
    //rRenderer.SetTexture(m_rTexture);
	
	m_rVertexShader.GetRef().SetParameter(azL("a_mModelProjMatrix"), oProjectionMatrix * oLookAtMatrix);

    azVector4 v(0.f, 0.f, 0.f);
    v = oTranslation.Transform(v);
    v = oProjectionMatrix.Transform(v);


    //m_rVertexShader.GetRef().SetParameter(azL("a_fTime"), cos(2.f * 3.14f * 0.25f * fTime));
	
	rRenderer.Bind();
	rRenderer.DrawPrimitives(azEPrimitiveType::eLineList, 0, 6);
	
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

    m_oTimer.Terminate();

    // \todo Registration function
    azClassManager::GrabInstance().Terminate();
    azMemoryManager::GrabInstance().DumpLeaks();
}