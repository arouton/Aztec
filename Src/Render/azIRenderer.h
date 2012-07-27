#ifndef __azIRenderer__
#define __azIRenderer__

#include "azCommon.h"
#include "Render/azRenderEnums.h"
#include <Cg/cg.h>

class azIGpuBuffer;
class azIInputLayout;
class azIShader;
class azITexture;
class azImage;
class azMatrix4x4;

// \class azIRenderer
// \brief Renderer interface
class AZ_API azIRenderer
{
public:
	// \brief Default constructor
	azIRenderer();

	// \brief Virtual destructor
	virtual ~azIRenderer() {}

	// \brief Initialize
	virtual void Initialize();

	// \brief Terminate
	virtual void Terminate();

	// \brief Begin scene
	virtual void BeginScene() = 0;

	// \brief End scene
	virtual void EndScene() = 0;


	// \brief Create a vertex buffer
	virtual azIGpuBuffer& CreateVertexBuffer(azUInt a_uCount, azEBufferType::Enum a_eBufferType = azEBufferType::eStatic) = 0;

	// \brief Destroy a vertex buffer
	void DestroyVertexBuffer(azIGpuBuffer& a_rBuffer);
	
	// \brief Set currently used vertex buffer on requested slot
	void SetVertexBuffer(azUInt a_uSlot, const azIGpuBuffer& a_rBuffer);


	// \brief Create an index buffer
	virtual azIGpuBuffer& CreateIndexBuffer(azUInt a_uCount, azEBufferType::Enum a_eBufferType = azEBufferType::eStatic) = 0;

	// \brief Destroy an index buffer
	void DestroyIndexBuffer(azIGpuBuffer& a_rBuffer);

	// \brief Set the currently used index buffer
	void SetIndexBuffer(const azIGpuBuffer& a_rBuffer, azSize a_uIndexBufferStride);


	// \brief Create input layout
	virtual azIInputLayout& CreateInputLayout() = 0;

	// \brief Destroy input layout
	void DestroyInputLayout(azIInputLayout& a_rInputLayout);

	// \brief Set the currently used input layout
	void SetInputLayout(azIInputLayout const& a_rInputLayout);


	// \brief Create vertex shader
	virtual azIShader& CreateVertexShader(azCBytes a_pProgram) = 0;

	// \brief Destroy vertex shader
	void DestroyVertexShader(azIShader& a_rShader);

	// \brief Set the currently used vertex shader
	void SetVertexShader(azIShader& a_rShader);


	// \brief Create pixel shader
	virtual azIShader& CreatePixelShader(azCBytes a_pProgram) = 0;

	// \brief Destroy pixel shader
	void DestroyPixelShader(azIShader& a_rShader);

	// \brief Set the currently used pixel shader
	void SetPixelShader(azIShader& a_rShader);

	// \brief Create texture
    virtual azITexture& CreateTexture(azImage const& a_rImage) = 0;

    // \brief Destroy texture
    void DestroyTexture(azITexture& a_rTexture);

    // \brief Set the currently used texture (unit 0)
    void SetTexture(azITexture& a_rTexture);

	
	// \brief Bind
	virtual void Bind() const = 0;

	// \brief Draw
	virtual void DrawPrimitives(azEPrimitiveType::Enum a_ePrimitiveType, azUInt a_uFirstVertex, azUInt a_uCount) const = 0;

private:
	// \brief Cg error callback
	static void OnCgError();

protected:
	// Current vertex buffers
	azIGpuBuffer const* m_apVertexBuffers[16];

	// Current index buffer
	azIGpuBuffer const* m_pIndexBuffer;

	// Current index buffer stride
	azUInt m_uIndexBufferStride;

	// Current input layout
	azIInputLayout const* m_pInputLayout;

	// Current vertex shader
	azIShader* m_pVertexShader;

	// Current pixel shader
	azIShader* m_pPixelShader;

    // Current texture
    azITexture* m_pTexture;


	// Cg context
	CGcontext m_pCgContext;

	// Vertex shader profile
	CGprofile m_eVertexShaderProfile;   

	// Pixel shader profile
	CGprofile m_ePixelShaderProfile;
};

#endif // __azIRenderer__
