//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <int t_Type>
inline azGlGpuBuffer<t_Type>::azGlGpuBuffer()
	: m_uBufferId(0)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <int t_Type>
inline void azGlGpuBuffer<t_Type>::Initialize(azUInt a_uSize, azEBufferType::Enum a_eBufferType)
{
	azIGpuBuffer::Initialize(a_uSize);

    // Buffer creation
    azGlRenderer::glGenBuffersARB(1, &m_uBufferId);

    // Reserve memory
    azGlRenderer::glBindBufferARB(t_Type, m_uBufferId);

	GLenum eBufferType = azGlRenderEnums::GetNativeBufferType(a_eBufferType);
    azGlRenderer::glBufferDataARB(t_Type, a_uSize, NULL, eBufferType);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <int t_Type>
inline void azGlGpuBuffer<t_Type>::Terminate()
{
    if (m_uBufferId != 0)
	{
        azGlRenderer::glDeleteBuffersARB(1, &m_uBufferId);
	}

	azIGpuBuffer::Terminate();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <int t_Type>
inline GLuint azGlGpuBuffer<t_Type>::GetBufferId() const
{
    return m_uBufferId;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <int t_Type>
inline void* azGlGpuBuffer<t_Type>::Lock(azUInt a_uOffset, azUInt a_uSize, azELockType::Enum a_eLockType)
{
    azGlRenderer::glBindBufferARB(t_Type, m_uBufferId);

    // This code ditches previous data ?
    //azGlRenderer::glBufferDataARB(t_Type, m_uSize, NULL, azGlRenderEnums::GetNativeBufferType(azEBufferType::eDynamic));

	GLenum eLockType = azGlRenderEnums::GetNativeLockType(a_eLockType);
    azUInt8* pBuffer = reinterpret_cast<azUInt8*>(azGlRenderer::glMapBufferARB(t_Type, eLockType));
    azAssert(pBuffer != NULL, "Couldn't lock GpuBUffer");
    
	return pBuffer + a_uOffset;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
template <int t_Type>
inline void azGlGpuBuffer<t_Type>::Unlock()
{
    azGlRenderer::glUnmapBufferARB(t_Type);
}
