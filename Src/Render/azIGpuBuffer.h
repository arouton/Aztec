#ifndef __azIGpuBuffer__
#define __azIGpuBuffer__

#include "azCommon.h"
#include "Render/azRenderEnums.h"

// \class azIGpuBuffer
// \brief Gpu buffer implementation interface
class AZ_API azIGpuBuffer
{
public :
	// \brief Constructor
	azIGpuBuffer();

	// \brief Virtual destructor
	virtual ~azIGpuBuffer() {}


	// \brief Initialize
	virtual void Initialize(azUInt a_uSize);

	// \brief Terminate
	virtual void Terminate() {}


	// \brief Fill the buffer
	void Fill(const void* a_pData, azUInt a_uSize);


	// \brief Lock the buffer
	virtual void* Lock(azUInt a_uOffset = 0, azUInt a_uSize = 0, azELockType::Enum a_eLockType = azELockType::eWriteOnly) = 0;

	// \brief Unlock the buffer
	virtual void Unlock() = 0;


	// \brief GetBufferId
	azUInt GetBufferId() const;

protected:
	// Buffer size
	azUInt m_uSize;
};

#endif // __azIGpuBuffer__
