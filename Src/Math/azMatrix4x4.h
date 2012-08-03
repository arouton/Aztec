#ifndef __azMAtrix4x4__
#define __azMAtrix4x4__

#include "azCommon.h"
#include "Math/azVector3.h"
#include "Math/azVector4.h"
#include <cmath>

// \class azMatrix4x4
// \brief Matrix
class azMatrix4x4
{
public :
	// \brief Default constructor
	azMatrix4x4(azFloat a_fA11 = 1.0f, azFloat a_fA12 = 0.0f, azFloat a_fA13 = 0.0f, azFloat a_fA14 = 0.0f,
		azFloat a_fA21 = 0.0f, azFloat a_fA22 = 1.0f, azFloat a_fA23 = 0.0f, azFloat a_fA24 = 0.0f,
		azFloat a_fA31 = 0.0f, azFloat a_fA32 = 0.0f, azFloat a_fA33 = 1.0f, azFloat a_fA34 = 0.0f,
		azFloat a_fA41 = 0.0f, azFloat a_fA42 = 0.0f, azFloat a_fA43 = 0.0f, azFloat a_fA44 = 1.0f);

    // \brief Constructor
    azMatrix4x4(azVector4 a_f4Row0, azVector4 a_f4Row1, azVector4 a_f4Row2, azVector4 a_f4Row3);

	// \brief Set matrix to identity
	void SetIdentity();

	// \brief Get transpose matrix
	azMatrix4x4 GetTranspose() const;

    // \brief compute the determinant
    azFloat GetDeterminant() const;

	// \brief Get inverse matrix
	azMatrix4x4 GetInverse() const;


	// \brief Build matrix from a transformation
	void BuildFromTranslate(azFloat a_fX, azFloat a_fY, azFloat a_fZ);

	// \brief Build matrix from a scale
	void BuildFromScale(azFloat a_fX, azFloat a_fY, azFloat a_fZ);

	// \brief Build matrix from a rotation around (0, 0, 0)
	void BuildFromRotateX(azFloat a_fAngle);
	void BuildFromRotateY(azFloat a_fAngle);
	void BuildFromRotateZ(azFloat a_fAngle);
	
	// \brief Build a non-centered ortho matrix
	void BuildOrthoOffCenter(azFloat a_fLeft, azFloat a_fTop, azFloat a_fRight, azFloat a_fBottom, azFloat a_fNear, azFloat a_fFar);

    // \brief Build a general perspective projection matrix
    void BuildPerspectiveProjection(azFloat a_fLeft, azFloat a_fRight, azFloat a_fBottom, azFloat a_fTop, azFloat a_fNear, azFloat a_fFar);

    // \brief Build a frustum-like perspective projection matrix
    void BuildPerspectiveFOV(azFloat a_fFovY, azFloat a_fRatio, azFloat a_fNear, azFloat a_fFar);

	// \brief Build a look at matrix
	void BuildLookAt(const azVector3& a_f3From, const azVector3& a_f3To, const azVector3& a_f3Up);


	// \brief Transform a vector
	azVector3 Transform(const azVector3& a_f3Operand, azFloat a_fW = 1.0f) const;
	azVector4 Transform(const azVector4& a_f4Operand) const;


	// \brief Unary operators + and -
	azMatrix4x4 operator +() const;
	azMatrix4x4 operator -() const;

	// \brief Operators + and - with matrix
	azMatrix4x4 operator +(const azMatrix4x4& a_rOperand) const;
	azMatrix4x4 operator -(const azMatrix4x4& a_rOperand) const;

	// \brief Operators += and -= with matrix
	const azMatrix4x4& operator +=(const azMatrix4x4& a_rOperand);
	const azMatrix4x4& operator -=(const azMatrix4x4& a_rOperand);

	// \brief Operators * and *= with matrix
	azMatrix4x4 operator *(const azMatrix4x4& a_rOperand) const;
	const azMatrix4x4& operator *=(const azMatrix4x4& a_rOperand);

	// \brief Operators * and / with float
	azMatrix4x4 operator *(azFloat a_fOperand);
	azMatrix4x4 operator /(azFloat a_fOperand);

	// \brief Operators *= and /= with float
	const azMatrix4x4& operator *=(azFloat a_fOperand);
	const azMatrix4x4& operator /=(azFloat a_fOperand);

	// \brief Comparison operators
	bool operator ==(const azMatrix4x4& a_rOperand) const;
	bool operator !=(const azMatrix4x4& a_rOperand) const;

	// \brief Indexed access operators
	azFloat& operator ()(azUInt a_uColumnIndex, azUInt a_uRowIndex);
	const azFloat& operator ()(azUInt a_uColumnIndex, azUInt a_uRowIndex) const;

	// \brief Cast to azFloat*
	operator azFloat*();
	operator const azFloat*() const;

    azVector4 m_f4Row0;
    azVector4 m_f4Row1;
    azVector4 m_f4Row2;
    azVector4 m_f4Row3;
};

azMatrix4x4 operator *(azFloat a_fOperand1, const azMatrix4x4& a_rOperand2);

#include "azMatrix4x4.inl"

#endif // __azMatrix4x4__
