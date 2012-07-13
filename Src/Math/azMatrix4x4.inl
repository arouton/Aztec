//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4::azMatrix4x4(azFloat m11, azFloat m12, azFloat m13, azFloat m14,
								  azFloat m21, azFloat m22, azFloat m23, azFloat m24,
								  azFloat m31, azFloat m32, azFloat m33, azFloat m34,
								  azFloat m41, azFloat m42, azFloat m43, azFloat m44)
	: m_fA11(m11), m_fA12(m12), m_fA13(m13), m_fA14(m14)
	, m_fA21(m21), m_fA22(m22), m_fA23(m23), m_fA24(m24)
	, m_fA31(m31), m_fA32(m32), m_fA33(m33), m_fA34(m34)
	, m_fA41(m41), m_fA42(m42), m_fA43(m43), m_fA44(m44)
{

}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::SetIdentity()
{
    m_fA11 = 1.0f; m_fA12 = 0.0f; m_fA13 = 0.0f; m_fA14 = 0.0f;
    m_fA21 = 0.0f; m_fA22 = 1.0f; m_fA23 = 0.0f; m_fA24 = 0.0f;
    m_fA31 = 0.0f; m_fA32 = 0.0f; m_fA33 = 1.0f; m_fA34 = 0.0f;
    m_fA41 = 0.0f; m_fA42 = 0.0f; m_fA43 = 0.0f; m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azFloat azMatrix4x4::GetDeterminant() const
{
    azFloat fA = m_fA22 * (m_fA33 * m_fA44 - m_fA43 * m_fA34) - m_fA32 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) + m_fA42 * (m_fA23 * m_fA34 - m_fA33 * m_fA24);
    azFloat fB = m_fA12 * (m_fA33 * m_fA44 - m_fA43 * m_fA34) - m_fA32 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA34 - m_fA33 * m_fA14);
    azFloat fC = m_fA12 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) - m_fA22 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA24 - m_fA23 * m_fA14);
    azFloat fD = m_fA12 * (m_fA23 * m_fA34 - m_fA33 * m_fA24) - m_fA22 * (m_fA13 * m_fA34 - m_fA33 * m_fA14) + m_fA32 * (m_fA13 * m_fA24 - m_fA23 * m_fA14);

    return m_fA11 * fA - m_fA21 * fB + m_fA31 * fC - m_fA41 * fD;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::GetTranspose() const
{
    return azMatrix4x4(m_fA11, m_fA21, m_fA31, m_fA41,
                    m_fA12, m_fA22, m_fA32, m_fA42,
                    m_fA13, m_fA23, m_fA33, m_fA43,
                    m_fA14, m_fA24, m_fA34, m_fA44);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::GetInverse() const
{
    azMatrix4x4 oRes;
    azFloat fDet = GetDeterminant();

    if (std::fabs(fDet) > std::numeric_limits<azFloat>::epsilon())
    {
        oRes.m_fA11 =  (m_fA22 * (m_fA33 * m_fA44 - m_fA34 * m_fA43) - m_fA32 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) + m_fA42 * (m_fA23 * m_fA34 - m_fA33 *  m_fA24)) / fDet;
        oRes.m_fA12 = -(m_fA12 * (m_fA33 * m_fA44 - m_fA43 * m_fA34) - m_fA32 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA34 - m_fA33 *  m_fA14)) / fDet;
        oRes.m_fA13 =  (m_fA12 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) - m_fA22 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA24 - m_fA23 *  m_fA14)) / fDet;
        oRes.m_fA14 = -(m_fA12 * (m_fA23 * m_fA34 - m_fA33 * m_fA24) - m_fA22 * (m_fA13 * m_fA34 - m_fA33 * m_fA14) + m_fA32 * (m_fA13 * m_fA24 - m_fA23 *  m_fA14)) / fDet;

        oRes.m_fA21 = -(m_fA21 * (m_fA33 * m_fA44 - m_fA34 * m_fA43) - m_fA23 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA24 * (m_fA31 * m_fA43 - m_fA33 *  m_fA41)) / fDet;
        oRes.m_fA22 =  (m_fA11 * (m_fA33 * m_fA44 - m_fA34 * m_fA43) - m_fA13 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA14 * (m_fA31 * m_fA43 - m_fA33 *  m_fA41)) / fDet;
        oRes.m_fA23 = -(m_fA11 * (m_fA23 * m_fA44 - m_fA24 * m_fA43) - m_fA13 * (m_fA21 * m_fA44 - m_fA24 * m_fA41) + m_fA14 * (m_fA21 * m_fA43 - m_fA23 *  m_fA41)) / fDet;
        oRes.m_fA24 =  (m_fA11 * (m_fA23 * m_fA34 - m_fA24 * m_fA33) - m_fA13 * (m_fA21 * m_fA34 - m_fA24 * m_fA31) + m_fA14 * (m_fA21 * m_fA33 - m_fA23 *  m_fA31)) / fDet;

        oRes.m_fA31 =  (m_fA21 * (m_fA32 * m_fA44 - m_fA34 * m_fA42) - m_fA22 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA24 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
        oRes.m_fA32 = -(m_fA11 * (m_fA32 * m_fA44 - m_fA34 * m_fA42) - m_fA12 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA14 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
        oRes.m_fA33 =  (m_fA11 * (m_fA22 * m_fA44 - m_fA24 * m_fA42) - m_fA12 * (m_fA21 * m_fA44 - m_fA24 * m_fA41) + m_fA14 * (m_fA21 * m_fA42 - m_fA22 *  m_fA41)) / fDet;
        oRes.m_fA34 = -(m_fA11 * (m_fA22 * m_fA34 - m_fA24 * m_fA32) - m_fA12 * (m_fA21 * m_fA34 - m_fA24 * m_fA31) + m_fA14 * (m_fA21 * m_fA32 - m_fA22 *  m_fA31)) / fDet;

        oRes.m_fA41 = -(m_fA21 * (m_fA32 * m_fA43 - m_fA33 * m_fA42) - m_fA22 * (m_fA31 * m_fA43 - m_fA33 * m_fA41) + m_fA23 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
        oRes.m_fA42 =  (m_fA11 * (m_fA32 * m_fA43 - m_fA33 * m_fA42) - m_fA12 * (m_fA31 * m_fA43 - m_fA33 * m_fA41) + m_fA13 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
        oRes.m_fA43 = -(m_fA11 * (m_fA22 * m_fA43 - m_fA23 * m_fA42) - m_fA12 * (m_fA21 * m_fA43 - m_fA23 * m_fA41) + m_fA13 * (m_fA21 * m_fA42 - m_fA22 *  m_fA41)) / fDet;
        oRes.m_fA44 =  (m_fA11 * (m_fA22 * m_fA33 - m_fA23 * m_fA32) - m_fA12 * (m_fA21 * m_fA33 - m_fA23 * m_fA31) + m_fA13 * (m_fA21 * m_fA32 - m_fA22 *  m_fA31)) / fDet;
    }

    return oRes;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromTranslate(azFloat a_fX, azFloat a_fY, azFloat a_fZ)
{
    m_fA11 = 1.0f; m_fA12 = 0.0f; m_fA13 = 0.0f; m_fA14 = a_fX;
    m_fA21 = 0.0f; m_fA22 = 1.0f; m_fA23 = 0.0f; m_fA24 = a_fY;
    m_fA31 = 0.0f; m_fA32 = 0.0f; m_fA33 = 1.0f; m_fA34 = a_fZ;
    m_fA41 = 0.0f; m_fA42 = 0.0f; m_fA43 = 0.0f; m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromScale(azFloat a_fX, azFloat a_fY, azFloat a_fZ)
{
    m_fA11 = a_fX; m_fA12 = 0.0f; m_fA13 = 0.0f; m_fA14 = 0.0f;
    m_fA21 = 0.0f; m_fA22 = a_fY; m_fA23 = 0.0f; m_fA24 = 0.0f;
    m_fA31 = 0.0f; m_fA32 = 0.0f; m_fA33 = a_fZ; m_fA34 = 0.0f;
    m_fA41 = 0.0f; m_fA42 = 0.0f; m_fA43 = 0.0f; m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromRotateX(azFloat a_fAngle)
{
    azFloat fCos = std::cos(a_fAngle);
    azFloat fSin = std::sin(a_fAngle);

    m_fA11 = 1.0f;
	m_fA12 = 0.0f;
	m_fA13 = 0.0f;
	m_fA14 = 0.0f;
    
	m_fA21 = 0.0f;
	m_fA22 = fCos; 
	m_fA23 = fSin;
	m_fA24 = 0.0f;
    
	m_fA31 = 0.0f;
	m_fA32 = -fSin;
	m_fA33 = fCos;
	m_fA34 = 0.0f;
    
	m_fA41 = 0.0f;
	m_fA42 = 0.0f;
	m_fA43 = 0.0f;
	m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromRotateY(azFloat a_fAngle)
{
    azFloat fCos = std::cos(a_fAngle);
    azFloat fSin = std::sin(a_fAngle);

    m_fA11 = fCos;
	m_fA12 = 0.0f;
	m_fA13 = -fSin;
	m_fA14 = 0.0f;
    
	m_fA21 = 0.0f;
	m_fA22 = 1.0f;
	m_fA23 = 0.0f;
	m_fA24 = 0.0f;
    
	m_fA31 = fSin;
	m_fA32 = 0.0f;
	m_fA33 = fCos;
	m_fA34 = 0.0f;
    
	m_fA41 = 0.0f;
	m_fA42 = 0.0f;
	m_fA43 = 0.0f;
	m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromRotateZ(azFloat a_fAngle)
{
    azFloat fCos = std::cos(a_fAngle);
    azFloat fSin = std::sin(a_fAngle);

    m_fA11 = fCos;  
	m_fA12 = fSin; 
	m_fA13 = 0.0f;
	m_fA14 = 0.0f;

    m_fA21 = -fSin;
	m_fA22 = fCos;  
	m_fA23 = 0.0f;
	m_fA24 = 0.0f;

    m_fA31 = 0.0f; 
	m_fA32 = 0.0f; 
	m_fA33 = 1.0f; 
	m_fA34 = 0.0f;

    m_fA41 = 0.0f; 
	m_fA42 = 0.0f;
	m_fA43 = 0.0f; 
	m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildOrthoOffCenter(azFloat a_fLeft, azFloat a_fTop, azFloat a_fRight, azFloat a_fBottom)
{
    m_fA11 = 2 / (a_fRight - a_fLeft);
	m_fA12 = 0.0f;               
	m_fA13 = 0.0f; 
	m_fA14 = (a_fLeft + a_fRight) / (a_fLeft - a_fRight);

    m_fA21 = 0.0f;               
	m_fA22 = 2.f / (a_fTop - a_fBottom);
	m_fA23 = 0.0f;
	m_fA24 = (a_fBottom + a_fTop) / (a_fBottom - a_fTop);

    m_fA31 = 0.0f;               
	m_fA32 = 0.0f;               
	m_fA33 = 1.0f; 
	m_fA34 = 0.0f;

    m_fA41 = 0.0f;               
	m_fA42 = 0.0f;              
	m_fA43 = 0.0f; 
	m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildPerspectiveFOV(azFloat a_fFov, azFloat a_fRatio, azFloat a_fNear, azFloat a_fFar)
{
    azFloat fYScale = 1.0f / std::tan(a_fFov / 2);
    azFloat fXScale = fYScale / a_fRatio;
    azFloat fCoeff  = a_fFar / (a_fFar - a_fNear);

    m_fA11 = fXScale; 
	m_fA12 = 0.0f;  
	m_fA13 = 0.0f; 
	m_fA14 = 0.0f;

    m_fA21 = 0.0f;  
	m_fA22 = fYScale; 
	m_fA23 = 0.0f; 
	m_fA24 = 0.0f;

    m_fA31 = 0.0f; 
	m_fA32 = 0.0f; 
	m_fA33 = fCoeff;
	m_fA34 = a_fNear * -fCoeff;

    m_fA41 = 0.0f; 
	m_fA42 = 0.0f; 
	m_fA43 = 1.0f;
	m_fA44 = 0.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildLookAt(const azVector3& a_f3From, const azVector3& a_f3To, const azVector3& a_f3Up)
{
    // \todo Handle properly case where (To - From) and Up are colinear

    azVector3 f3ZAxis = a_f3To - a_f3From;
    f3ZAxis.SelfNormalize();

    azVector3 f3XAxis = VectorCross(a_f3Up, f3ZAxis);
    f3XAxis.SelfNormalize();

    azVector3 f3YAxis = VectorCross(f3ZAxis, f3XAxis);

    m_fA11 = f3YAxis.m_fX;
	m_fA12 = f3YAxis.m_fY; 
	m_fA13 = f3YAxis.m_fZ;
	m_fA14 = -VectorDot(f3YAxis, a_f3From);

    m_fA21 = f3YAxis.m_fX; 
	m_fA22 = f3YAxis.m_fY; 
	m_fA23 = f3YAxis.m_fZ; 
	m_fA24 = -VectorDot(f3YAxis, a_f3From);

    m_fA31 = f3ZAxis.m_fX; 
	m_fA32 = f3ZAxis.m_fY;
	m_fA33 = f3ZAxis.m_fZ; 
	m_fA34 = -VectorDot(f3ZAxis, a_f3From);

    m_fA41 = 0.0f;  
	m_fA42 = 0.0f;  
	m_fA43 = 0.0f;  
	m_fA44 = 1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azMatrix4x4::Transform(const azVector3& a_f3Operand, azFloat a_fW) const
{
    return azVector3(a_f3Operand.m_fX * m_fA11 + a_f3Operand.m_fY * m_fA21 + a_f3Operand.m_fZ * m_fA31 + a_fW * m_fA41,
                     a_f3Operand.m_fX * m_fA12 + a_f3Operand.m_fY * m_fA22 + a_f3Operand.m_fZ * m_fA32 + a_fW * m_fA42,
                     a_f3Operand.m_fX * m_fA13 + a_f3Operand.m_fY * m_fA23 + a_f3Operand.m_fZ * m_fA33 + a_fW * m_fA43);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector4 azMatrix4x4::Transform(const azVector4& a_f4Operand) const
{
    return azVector4(a_f4Operand.m_fX * m_fA11 + a_f4Operand.m_fY * m_fA21 + a_f4Operand.m_fZ * m_fA31 + a_f4Operand.m_fW * m_fA41,
                     a_f4Operand.m_fX * m_fA12 + a_f4Operand.m_fY * m_fA22 + a_f4Operand.m_fZ * m_fA32 + a_f4Operand.m_fW * m_fA42,
                     a_f4Operand.m_fX * m_fA13 + a_f4Operand.m_fY * m_fA23 + a_f4Operand.m_fZ * m_fA33 + a_f4Operand.m_fW * m_fA43,
                     a_f4Operand.m_fX * m_fA14 + a_f4Operand.m_fY * m_fA24 + a_f4Operand.m_fZ * m_fA34 + a_f4Operand.m_fW * m_fA44);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator +() const
{
    return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator -() const
{
    return azMatrix4x4(-m_fA11, -m_fA12, -m_fA13, -m_fA14,
                    -m_fA21, -m_fA22, -m_fA23, -m_fA24,
                    -m_fA31, -m_fA32, -m_fA33, -m_fA34,
                    -m_fA41, -m_fA42, -m_fA43, -m_fA44);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator +(const azMatrix4x4& m) const
{
    return azMatrix4x4(m_fA11 + m.m_fA11, m_fA12 + m.m_fA12, m_fA13 + m.m_fA13, m_fA14 + m.m_fA14,
                    m_fA21 + m.m_fA21, m_fA22 + m.m_fA22, m_fA23 + m.m_fA23, m_fA24 + m.m_fA24,
                    m_fA31 + m.m_fA31, m_fA32 + m.m_fA32, m_fA33 + m.m_fA33, m_fA34 + m.m_fA34,
                    m_fA41 + m.m_fA41, m_fA42 + m.m_fA42, m_fA43 + m.m_fA43, m_fA44 + m.m_fA44);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator -(const azMatrix4x4& m) const
{
    return azMatrix4x4(m_fA11 - m.m_fA11, m_fA12 - m.m_fA12, m_fA13 - m.m_fA13, m_fA14 - m.m_fA14,
                    m_fA21 - m.m_fA21, m_fA22 - m.m_fA22, m_fA23 - m.m_fA23, m_fA24 - m.m_fA24,
                    m_fA31 - m.m_fA31, m_fA32 - m.m_fA32, m_fA33 - m.m_fA33, m_fA34 - m.m_fA34,
                    m_fA41 - m.m_fA41, m_fA42 - m.m_fA42, m_fA43 - m.m_fA43, m_fA44 - m.m_fA44);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator +=(const azMatrix4x4& m)
{
    m_fA11 += m.m_fA11; m_fA12 += m.m_fA12; m_fA13 += m.m_fA13; m_fA14 += m.m_fA14;
    m_fA21 += m.m_fA21; m_fA22 += m.m_fA22; m_fA23 += m.m_fA23; m_fA24 += m.m_fA24;
    m_fA31 += m.m_fA31; m_fA32 += m.m_fA32; m_fA33 += m.m_fA33; m_fA34 += m.m_fA34;
    m_fA41 += m.m_fA41; m_fA42 += m.m_fA42; m_fA43 += m.m_fA43; m_fA44 += m.m_fA44;

    return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator -=(const azMatrix4x4& m)
{
    m_fA11 -= m.m_fA11; m_fA12 -= m.m_fA12; m_fA13 -= m.m_fA13; m_fA14 -= m.m_fA14;
    m_fA21 -= m.m_fA21; m_fA22 -= m.m_fA22; m_fA23 -= m.m_fA23; m_fA24 -= m.m_fA24;
    m_fA31 -= m.m_fA31; m_fA32 -= m.m_fA32; m_fA33 -= m.m_fA33; m_fA34 -= m.m_fA34;
    m_fA41 -= m.m_fA41; m_fA42 -= m.m_fA42; m_fA43 -= m.m_fA43; m_fA44 -= m.m_fA44;

    return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator *(const azMatrix4x4& m) const
{
    return azMatrix4x4(m_fA11 * m.m_fA11 + m_fA21 * m.m_fA12 + m_fA31 * m.m_fA13 + m_fA41 * m.m_fA14,
                    m_fA12 * m.m_fA11 + m_fA22 * m.m_fA12 + m_fA32 * m.m_fA13 + m_fA42 * m.m_fA14,
                    m_fA13 * m.m_fA11 + m_fA23 * m.m_fA12 + m_fA33 * m.m_fA13 + m_fA43 * m.m_fA14,
                    m_fA14 * m.m_fA11 + m_fA24 * m.m_fA12 + m_fA34 * m.m_fA13 + m_fA44 * m.m_fA14,

                    m_fA11 * m.m_fA21 + m_fA21 * m.m_fA22 + m_fA31 * m.m_fA23 + m_fA41 * m.m_fA24,
                    m_fA12 * m.m_fA21 + m_fA22 * m.m_fA22 + m_fA32 * m.m_fA23 + m_fA42 * m.m_fA24,
                    m_fA13 * m.m_fA21 + m_fA23 * m.m_fA22 + m_fA33 * m.m_fA23 + m_fA43 * m.m_fA24,
                    m_fA14 * m.m_fA21 + m_fA24 * m.m_fA22 + m_fA34 * m.m_fA23 + m_fA44 * m.m_fA24,

                    m_fA11 * m.m_fA31 + m_fA21 * m.m_fA32 + m_fA31 * m.m_fA33 + m_fA41 * m.m_fA34,
                    m_fA12 * m.m_fA31 + m_fA22 * m.m_fA32 + m_fA32 * m.m_fA33 + m_fA42 * m.m_fA34,
                    m_fA13 * m.m_fA31 + m_fA23 * m.m_fA32 + m_fA33 * m.m_fA33 + m_fA43 * m.m_fA34,
                    m_fA14 * m.m_fA31 + m_fA24 * m.m_fA32 + m_fA34 * m.m_fA33 + m_fA44 * m.m_fA34,

                    m_fA11 * m.m_fA41 + m_fA21 * m.m_fA42 + m_fA31 * m.m_fA43 + m_fA41 * m.m_fA44,
                    m_fA12 * m.m_fA41 + m_fA22 * m.m_fA42 + m_fA32 * m.m_fA43 + m_fA42 * m.m_fA44,
                    m_fA13 * m.m_fA41 + m_fA23 * m.m_fA42 + m_fA33 * m.m_fA43 + m_fA43 * m.m_fA44,
                    m_fA14 * m.m_fA41 + m_fA24 * m.m_fA42 + m_fA34 * m.m_fA43 + m_fA44 * m.m_fA44);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator *(azFloat a_fOperand)
{
    return azMatrix4x4(m_fA11 * a_fOperand, m_fA12 * a_fOperand, m_fA13 * a_fOperand, m_fA14 * a_fOperand,
                    m_fA21 * a_fOperand, m_fA22 * a_fOperand, m_fA23 * a_fOperand, m_fA24 * a_fOperand,
                    m_fA31 * a_fOperand, m_fA32 * a_fOperand, m_fA33 * a_fOperand, m_fA34 * a_fOperand,
                    m_fA41 * a_fOperand, m_fA42 * a_fOperand, m_fA43 * a_fOperand, m_fA44 * a_fOperand);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator /(azFloat a_fOperand)
{
    return azMatrix4x4(m_fA11 / a_fOperand, m_fA12 / a_fOperand, m_fA13 / a_fOperand, m_fA14 / a_fOperand,
                    m_fA21 / a_fOperand, m_fA22 / a_fOperand, m_fA23 / a_fOperand, m_fA24 / a_fOperand,
                    m_fA31 / a_fOperand, m_fA32 / a_fOperand, m_fA33 / a_fOperand, m_fA34 / a_fOperand,
                    m_fA41 / a_fOperand, m_fA42 / a_fOperand, m_fA43 / a_fOperand, m_fA44 / a_fOperand);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator *=(const azMatrix4x4& m)
{
    *this = *this * m;

    return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator *=(azFloat a_fOperand)
{
    m_fA11 *= a_fOperand; m_fA12 *= a_fOperand; m_fA13 *= a_fOperand; m_fA14 *= a_fOperand;
    m_fA21 *= a_fOperand; m_fA22 *= a_fOperand; m_fA23 *= a_fOperand; m_fA24 *= a_fOperand;
    m_fA31 *= a_fOperand; m_fA32 *= a_fOperand; m_fA33 *= a_fOperand; m_fA34 *= a_fOperand;
    m_fA41 *= a_fOperand; m_fA42 *= a_fOperand; m_fA43 *= a_fOperand; m_fA44 *= a_fOperand;

    return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator /=(azFloat a_fOperand)
{
    m_fA11 /= a_fOperand; m_fA12 /= a_fOperand; m_fA13 /= a_fOperand; m_fA14 /= a_fOperand;
    m_fA21 /= a_fOperand; m_fA22 /= a_fOperand; m_fA23 /= a_fOperand; m_fA24 /= a_fOperand;
    m_fA31 /= a_fOperand; m_fA32 /= a_fOperand; m_fA33 /= a_fOperand; m_fA34 /= a_fOperand;
    m_fA41 /= a_fOperand; m_fA42 /= a_fOperand; m_fA43 /= a_fOperand; m_fA44 /= a_fOperand;

    return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline bool azMatrix4x4::operator ==(const azMatrix4x4& m) const
{
	float fEpsilon = std::numeric_limits<azFloat>::epsilon();
    return ((std::fabs(m_fA11 - m.m_fA11) < fEpsilon) && (std::fabs(m_fA12 - m.m_fA12) < fEpsilon) &&
            (std::fabs(m_fA13 - m.m_fA13) < fEpsilon) && (std::fabs(m_fA14 - m.m_fA14) < fEpsilon) &&
            (std::fabs(m_fA21 - m.m_fA21) < fEpsilon) && (std::fabs(m_fA22 - m.m_fA22) < fEpsilon) &&
            (std::fabs(m_fA23 - m.m_fA23) < fEpsilon) && (std::fabs(m_fA24 - m.m_fA24) < fEpsilon) &&
            (std::fabs(m_fA31 - m.m_fA31) < fEpsilon) && (std::fabs(m_fA32 - m.m_fA32) < fEpsilon) &&
            (std::fabs(m_fA33 - m.m_fA33) < fEpsilon) && (std::fabs(m_fA34 - m.m_fA34) < fEpsilon) &&
            (std::fabs(m_fA41 - m.m_fA41) < fEpsilon) && (std::fabs(m_fA42 - m.m_fA42) < fEpsilon) &&
            (std::fabs(m_fA43 - m.m_fA43) < fEpsilon) && (std::fabs(m_fA44 - m.m_fA44) < fEpsilon));
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline bool azMatrix4x4::operator !=(const azMatrix4x4& m) const
{
    return !(*this == m);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azFloat& azMatrix4x4::operator ()(azUInt a_uColumnIndex, azUInt a_uRowIndex)
{
    return operator azFloat*()[a_uColumnIndex + 4 * a_uRowIndex];
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azFloat& azMatrix4x4::operator ()(azUInt a_uColumnIndex, azUInt a_uRowIndex) const
{
    return operator ()(a_uColumnIndex, a_uRowIndex);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4::operator const azFloat*() const
{
    return &m_fA11;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4::operator azFloat*()
{
    return &m_fA11;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 operator *(azFloat a_fOperand1, const azMatrix4x4& a_rOperand2)
{
    return a_rOperand2 * a_fOperand1;
}


