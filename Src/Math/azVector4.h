#ifndef __azVector4__
#define __azVector4__

#include "azCommon.h"

// \class azVector4
// \brief Vector 4
class azVector4
{
public :
	// \brief Default constructor
	azVector4(azFloat a_fX = 0.f, azFloat a_fY = 0.f, azFloat a_fZ = 0.f, azFloat a_fW = 1.f);

	// \brief Reset the vector
	void Set(azFloat a_fX, azFloat a_fY, azFloat a_fZ, azFloat a_fW);

	// \brief Get vector norm
	azFloat GetLength() const;

	// \brief Get vector squared norm
	azFloat GetLengthSq() const;

	// \brief Self normalize
	void SelfNormalize();

	// \brief Unary operators + and -
	azVector4 operator +() const;
	azVector4 operator -() const;

	// \brief Binary operators + and -
	azVector4 operator +(const azVector4& a_f4Operand) const;
	azVector4 operator -(const azVector4& a_f4Operand) const;

	// \brief Operators += and -=
	const azVector4& operator +=(const azVector4& a_f4Operand);
	const azVector4& operator -=(const azVector4& a_f4Operand);

	// \brief Operators * and /
	azVector4 operator *(azFloat a_fOperand) const;
	azVector4 operator /(azFloat a_fOperand) const;

	// \brief Operators *= and /=
	const azVector4& operator *=(azFloat a_fOperand);
	const azVector4& operator /=(azFloat a_fOperand);

	// \brief Compare operators
	bool operator ==(const azVector4& a_f4Operand) const;
	bool operator !=(const azVector4& a_f4Operand) const;

    // \brief Cast operators
	operator azFloat*();
	operator const azFloat*() const;

	// X component
	azFloat m_fX;

	// Y component
	azFloat m_fY;

	// Z component
	azFloat m_fZ;

	// W component
	azFloat m_fW;
};


azVector4 operator *(azFloat a_fOperand1, const azVector4& a_f4Operand2);

azFloat VectorDot(const azVector4& a_f4Operand1, const azVector4& a_f4Operand2);
azVector4 VectorCross(const azVector4& a_f4Operand1, const azVector4& a_f4Operand2);

#include "azVector4.inl"


#endif // __axVector4__
