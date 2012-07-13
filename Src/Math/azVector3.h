#ifndef __azVector3__
#define __azVector3__

#include "azCommon.h"

// \class azVector3
// \brief Vector 3
class azVector3
{
public :

	// \brief Default constructor
	azVector3(azFloat a_fX = 0.f, azFloat a_fY = 0.f, azFloat a_fZ = 0.f);

	// \brief Reset vector
	void Set(azFloat a_fX, azFloat a_fY, azFloat a_fZ);

	// \brief Get norm
	azFloat GetLength() const;

	// \brief Get squared norm
	azFloat GetLengthSq() const;

	// \brief Self normalize
	void SelfNormalize();

	// \brief Unary operators + and -
	azVector3 operator +() const;
	azVector3 operator -() const;

	// \brief Binary operators + and -
	azVector3 operator +(const azVector3& a_f3Operand) const;
	azVector3 operator -(const azVector3& a_f3Operand) const;

	// \brief Operators += and -=
	const azVector3& operator +=(const azVector3& a_f3Operand);
	const azVector3& operator -=(const azVector3& a_f3Operand);

	// \brief Operators * and /
	azVector3 operator * (azFloat a_fOperand) const;
	azVector3 operator / (azFloat a_fOperand) const;

	// \brief Operators *= and /=
	const azVector3& operator *=(azFloat a_fOperand);
	const azVector3& operator /=(azFloat a_fOperand);

	// \brief Compare operators
	bool operator ==(const azVector3& a_f3Operand) const;
	bool operator !=(const azVector3& a_f3Operand) const;

	// \brief Cast operators
	operator azFloat*();
	operator const azFloat*() const;


	// X component
	azFloat m_fX;

	// Y component
	azFloat m_fY;

	// Z component
	azFloat m_fZ;
};


azVector3 operator * (azFloat a_fOperand1, const azVector3& a_f3Operand2);

azFloat VectorDot (const azVector3& a_f3Operand1, const azVector3& a_f3Operand2);
azVector3 VectorCross(const azVector3& a_f3Operand1, const azVector3& a_f3Operand2);


#include "azVector3.inl"


#endif // __azVector3__
