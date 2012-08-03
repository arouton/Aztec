#include <limits>
#include <iostream>

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3::azVector3(azFloat a_fX, azFloat a_fY, azFloat a_fZ)
	: m_fX(a_fX)
	, m_fY(a_fY)
	, m_fZ(a_fZ)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azVector3::Set(azFloat a_fX, azFloat a_fY, azFloat a_fZ)
{
    m_fX = a_fX;
    m_fY = a_fY;
    m_fZ = a_fZ;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azFloat azVector3::GetLength() const
{
    return std::sqrt(GetLengthSq());
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azFloat azVector3::GetLengthSq() const
{
    return m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azVector3::SelfNormalize()
{
    azFloat fNorm = GetLength();

    if (std::abs(fNorm) > std::numeric_limits<azFloat>::epsilon())
    {
        m_fX /= fNorm;
        m_fY /= fNorm;
        m_fZ /= fNorm;
    }
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azVector3::operator +() const
{
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azVector3::operator -() const
{
    return azVector3(-m_fX, -m_fY, -m_fZ);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azVector3::operator +(const azVector3& a_f3Operand) const
{
    return azVector3(m_fX + a_f3Operand.m_fX, m_fY + a_f3Operand.m_fY, m_fZ + a_f3Operand.m_fZ);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azVector3::operator -(const azVector3& a_f3Operand) const
{
    return azVector3(m_fX - a_f3Operand.m_fX, m_fY - a_f3Operand.m_fY, m_fZ - a_f3Operand.m_fZ);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azVector3& azVector3::operator +=(const azVector3& a_f3Operand)
{
    m_fX += a_f3Operand.m_fX;
    m_fY += a_f3Operand.m_fY;
    m_fZ += a_f3Operand.m_fZ;

    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azVector3::operator *(azFloat a_fOperand) const
{
    return azVector3(m_fX * a_fOperand, m_fY * a_fOperand, m_fZ * a_fOperand);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azVector3::operator /(azFloat a_fOperand) const
{
    return azVector3(m_fX / a_fOperand, m_fY / a_fOperand, m_fZ / a_fOperand);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azVector3& azVector3::operator -=(const azVector3& a_f3Operand)
{
    m_fX -= a_f3Operand.m_fX;
    m_fY -= a_f3Operand.m_fY;
    m_fZ -= a_f3Operand.m_fZ;

    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azVector3& azVector3::operator *=(azFloat a_fOperand)
{
    m_fX *= a_fOperand;
    m_fY *= a_fOperand;
    m_fZ *= a_fOperand;

    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azVector3& azVector3::operator /=(azFloat a_fOperand)
{
    m_fX /= a_fOperand;
    m_fY /= a_fOperand;
    m_fZ /= a_fOperand;

    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline bool azVector3::operator ==(const azVector3& a_f3Operand) const
{
    return ((std::abs(m_fX - a_f3Operand.m_fX) <= std::numeric_limits<azFloat>::epsilon()) &&
            (std::abs(m_fY - a_f3Operand.m_fY) <= std::numeric_limits<azFloat>::epsilon()) &&
            (std::abs(m_fZ - a_f3Operand.m_fZ) <= std::numeric_limits<azFloat>::epsilon()));
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline bool azVector3::operator !=(const azVector3& a_f3Operand) const
{
    return !(rThis == a_f3Operand);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3::operator azFloat*()
{
    return &m_fX;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3::operator const azFloat*() const
{
    return &m_fX;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 operator *(azFloat a_fOperand1, const azVector3& a_f3Operand2)
{
	return a_f3Operand2 * a_fOperand1;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azFloat VectorDot(const azVector3& a_f3Operand1, const azVector3& a_f3Operand2)
{
    return a_f3Operand1.m_fX * a_f3Operand2.m_fX + a_f3Operand1.m_fY * a_f3Operand2.m_fY + a_f3Operand1.m_fZ * a_f3Operand2.m_fZ;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 VectorCross(const azVector3& a_f3Operand1, const azVector3& a_f3Operand2)
{
    return azVector3(a_f3Operand1.m_fY * a_f3Operand2.m_fZ - a_f3Operand1.m_fZ * a_f3Operand2.m_fY, a_f3Operand1.m_fZ * a_f3Operand2.m_fX - a_f3Operand1.m_fX * a_f3Operand2.m_fZ, a_f3Operand1.m_fX * a_f3Operand2.m_fY - a_f3Operand1.m_fY * a_f3Operand2.m_fX);
}
