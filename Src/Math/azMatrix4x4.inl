//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4::azMatrix4x4(azFloat a_f11, azFloat a_f12, azFloat a_f13, azFloat a_f14,
								  azFloat a_f21, azFloat a_f22, azFloat a_f23, azFloat a_f24,
								  azFloat a_f31, azFloat a_f32, azFloat a_f33, azFloat a_f34,
								  azFloat a_f41, azFloat a_f42, azFloat a_f43, azFloat a_f44)
	: m_f4Row0(a_f11, a_f12, a_f13, a_f14)
	, m_f4Row1(a_f21, a_f22, a_f23, a_f24)
	, m_f4Row2(a_f31, a_f32, a_f33, a_f34)
	, m_f4Row3(a_f41, a_f42, a_f43, a_f44)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4::azMatrix4x4(azVector4 a_f4Row0, azVector4 a_f4Row1, azVector4 a_f4Row2, azVector4 a_f4Row3)
    : m_f4Row0(a_f4Row0)
    , m_f4Row1(a_f4Row1)
    , m_f4Row2(a_f4Row2)
    , m_f4Row3(a_f4Row3)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::SetIdentity()
{
    m_f4Row0.Set(1.f, 0.f, 0.f, 0.f);
    m_f4Row1.Set(0.f, 1.f, 0.f, 0.f);
    m_f4Row2.Set(0.f, 0.f, 1.f, 0.f);
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::GetTranspose() const
{
    return azMatrix4x4(m_f4Row0.m_fX, m_f4Row1.m_fX, m_f4Row2.m_fX, m_f4Row3.m_fX,
        m_f4Row0.m_fY, m_f4Row1.m_fY, m_f4Row2.m_fY, m_f4Row3.m_fY,
        m_f4Row0.m_fZ, m_f4Row1.m_fZ, m_f4Row2.m_fZ, m_f4Row3.m_fZ,
        m_f4Row0.m_fW, m_f4Row1.m_fW, m_f4Row2.m_fW, m_f4Row3.m_fW);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azFloat azMatrix4x4::GetDeterminant() const
{
    //azFloat fA = m_fA22 * (m_fA33 * m_fA44 - m_fA43 * m_fA34) - m_fA32 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) + m_fA42 * (m_fA23 * m_fA34 - m_fA33 * m_fA24);
    //azFloat fB = m_fA12 * (m_fA33 * m_fA44 - m_fA43 * m_fA34) - m_fA32 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA34 - m_fA33 * m_fA14);
    //azFloat fC = m_fA12 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) - m_fA22 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA24 - m_fA23 * m_fA14);
    //azFloat fD = m_fA12 * (m_fA23 * m_fA34 - m_fA33 * m_fA24) - m_fA22 * (m_fA13 * m_fA34 - m_fA33 * m_fA14) + m_fA32 * (m_fA13 * m_fA24 - m_fA23 * m_fA14);

    //return m_fA11 * fA - m_fA21 * fB + m_fA31 * fC - m_fA41 * fD;
    azAssert(false, "Todo");
    return 0.f;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::GetInverse() const
{
    //azMatrix4x4 oRes;
    //azFloat fDet = GetDeterminant();

    //if (std::fabs(fDet) > std::numeric_limits<azFloat>::epsilon())
    //{
    //    oRes.m_fA11 =  (m_fA22 * (m_fA33 * m_fA44 - m_fA34 * m_fA43) - m_fA32 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) + m_fA42 * (m_fA23 * m_fA34 - m_fA33 *  m_fA24)) / fDet;
    //    oRes.m_fA12 = -(m_fA12 * (m_fA33 * m_fA44 - m_fA43 * m_fA34) - m_fA32 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA34 - m_fA33 *  m_fA14)) / fDet;
    //    oRes.m_fA13 =  (m_fA12 * (m_fA23 * m_fA44 - m_fA43 * m_fA24) - m_fA22 * (m_fA13 * m_fA44 - m_fA43 * m_fA14) + m_fA42 * (m_fA13 * m_fA24 - m_fA23 *  m_fA14)) / fDet;
    //    oRes.m_fA14 = -(m_fA12 * (m_fA23 * m_fA34 - m_fA33 * m_fA24) - m_fA22 * (m_fA13 * m_fA34 - m_fA33 * m_fA14) + m_fA32 * (m_fA13 * m_fA24 - m_fA23 *  m_fA14)) / fDet;

    //    oRes.m_fA21 = -(m_fA21 * (m_fA33 * m_fA44 - m_fA34 * m_fA43) - m_fA23 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA24 * (m_fA31 * m_fA43 - m_fA33 *  m_fA41)) / fDet;
    //    oRes.m_fA22 =  (m_fA11 * (m_fA33 * m_fA44 - m_fA34 * m_fA43) - m_fA13 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA14 * (m_fA31 * m_fA43 - m_fA33 *  m_fA41)) / fDet;
    //    oRes.m_fA23 = -(m_fA11 * (m_fA23 * m_fA44 - m_fA24 * m_fA43) - m_fA13 * (m_fA21 * m_fA44 - m_fA24 * m_fA41) + m_fA14 * (m_fA21 * m_fA43 - m_fA23 *  m_fA41)) / fDet;
    //    oRes.m_fA24 =  (m_fA11 * (m_fA23 * m_fA34 - m_fA24 * m_fA33) - m_fA13 * (m_fA21 * m_fA34 - m_fA24 * m_fA31) + m_fA14 * (m_fA21 * m_fA33 - m_fA23 *  m_fA31)) / fDet;

    //    oRes.m_fA31 =  (m_fA21 * (m_fA32 * m_fA44 - m_fA34 * m_fA42) - m_fA22 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA24 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
    //    oRes.m_fA32 = -(m_fA11 * (m_fA32 * m_fA44 - m_fA34 * m_fA42) - m_fA12 * (m_fA31 * m_fA44 - m_fA34 * m_fA41) + m_fA14 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
    //    oRes.m_fA33 =  (m_fA11 * (m_fA22 * m_fA44 - m_fA24 * m_fA42) - m_fA12 * (m_fA21 * m_fA44 - m_fA24 * m_fA41) + m_fA14 * (m_fA21 * m_fA42 - m_fA22 *  m_fA41)) / fDet;
    //    oRes.m_fA34 = -(m_fA11 * (m_fA22 * m_fA34 - m_fA24 * m_fA32) - m_fA12 * (m_fA21 * m_fA34 - m_fA24 * m_fA31) + m_fA14 * (m_fA21 * m_fA32 - m_fA22 *  m_fA31)) / fDet;

    //    oRes.m_fA41 = -(m_fA21 * (m_fA32 * m_fA43 - m_fA33 * m_fA42) - m_fA22 * (m_fA31 * m_fA43 - m_fA33 * m_fA41) + m_fA23 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
    //    oRes.m_fA42 =  (m_fA11 * (m_fA32 * m_fA43 - m_fA33 * m_fA42) - m_fA12 * (m_fA31 * m_fA43 - m_fA33 * m_fA41) + m_fA13 * (m_fA31 * m_fA42 - m_fA32 *  m_fA41)) / fDet;
    //    oRes.m_fA43 = -(m_fA11 * (m_fA22 * m_fA43 - m_fA23 * m_fA42) - m_fA12 * (m_fA21 * m_fA43 - m_fA23 * m_fA41) + m_fA13 * (m_fA21 * m_fA42 - m_fA22 *  m_fA41)) / fDet;
    //    oRes.m_fA44 =  (m_fA11 * (m_fA22 * m_fA33 - m_fA23 * m_fA32) - m_fA12 * (m_fA21 * m_fA33 - m_fA23 * m_fA31) + m_fA13 * (m_fA21 * m_fA32 - m_fA22 *  m_fA31)) / fDet;
    //}

    //return oRes;
    azAssert(false, "Todo");
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromTranslate(azFloat a_fX, azFloat a_fY, azFloat a_fZ)
{
    m_f4Row0.Set(1.f, 0.f, 0.f, a_fX);
    m_f4Row1.Set(0.f, 1.f, 0.f, a_fY);
    m_f4Row2.Set(0.f, 0.f, 1.f, a_fZ);
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromScale(azFloat a_fX, azFloat a_fY, azFloat a_fZ)
{
    m_f4Row0.Set(a_fX, 0.f, 0.f, 0.f);
    m_f4Row1.Set(0.f, a_fY, 0.f, 0.f);
    m_f4Row2.Set(0.f, 0.f, a_fZ, 0.f);
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromRotateX(azFloat a_fAngle)
{
    azFloat fCos = std::cos(a_fAngle);
    azFloat fSin = std::sin(a_fAngle);

    m_f4Row0.Set(1.f, 0.f, 0.f, 0.f);
    m_f4Row1.Set(0.f, fCos, -fSin, 0.f);
    m_f4Row2.Set(0.f, fSin, fCos, 0.f);
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromRotateY(azFloat a_fAngle)
{
    azFloat fCos = std::cos(a_fAngle);
    azFloat fSin = std::sin(a_fAngle);

    m_f4Row0.Set(fCos, 0.f, fSin, 0.f);
    m_f4Row1.Set(0.f, 1.f, 0.f, 0.f);
    m_f4Row2.Set(fSin, 0.f, fCos, 0.f);
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildFromRotateZ(azFloat a_fAngle)
{
    azFloat fCos = std::cos(a_fAngle);
    azFloat fSin = std::sin(a_fAngle);

    m_f4Row0.Set(fCos, -fSin, 0.f, 0.f);
    m_f4Row1.Set(fSin, fCos, 0.f, 0.f);
    m_f4Row2.Set(0.f, 0.f, 1.f, 0.f);
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildOrthoOffCenter(azFloat a_fLeft, azFloat a_fTop, azFloat a_fRight, azFloat a_fBottom, azFloat a_fNear, azFloat a_fFar)
{
    // http://www.songho.ca/opengl/gl_projectionmatrix.html

    m_f4Row0.Set(2.f / (a_fRight - a_fLeft), 0.f, 0.f, -(a_fRight + a_fLeft) / (a_fRight - a_fLeft));
    m_f4Row1.Set(0.f, 2.f / (a_fTop - a_fBottom), 0.f, -(a_fTop + a_fBottom) / (a_fTop - a_fBottom));
	m_f4Row2.Set(0.f, 0.f, -2.f / (a_fFar - a_fNear), -(a_fFar + a_fNear) / (a_fFar - a_fNear));
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildPerspectiveProjection(azFloat a_fLeft, azFloat a_fRight, azFloat a_fBottom, azFloat a_fTop, azFloat a_fNear, azFloat a_fFar)
{
    // http://www.songho.ca/opengl/gl_projectionmatrix.html

    m_f4Row0.Set(2.f * a_fNear / (a_fRight - a_fLeft), 0.0f, (a_fRight + a_fLeft) / (a_fRight - a_fLeft), 0.f);
    m_f4Row1.Set(0.f,  2.f * a_fNear / (a_fTop - a_fBottom), (a_fTop + a_fBottom) / (a_fTop - a_fBottom), 0.f);
    m_f4Row2.Set(0.f, 0.f, -(a_fFar + a_fNear) / (a_fFar - a_fNear), -2.f * a_fNear * a_fFar / (a_fFar - a_fNear));
    m_f4Row3.Set(0.f, 0.f, -1.f, 0.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildPerspectiveFOV(azFloat a_fFovY, azFloat a_fRatio, azFloat a_fNear, azFloat a_fFar)
{
    const azFloat fDegToRad = 3.14159265f / 180.f;

    // Tangent of half a_fFovY
    azFloat fTangent = std::tan(fDegToRad * a_fFovY / 2.f);
    // Half height of near plane
    azFloat fHeight = a_fNear * fTangent;
    // Half width of near plane
    azFloat fWidth = fHeight * a_fRatio;      

    BuildPerspectiveProjection(-fWidth, fWidth, -fHeight, fHeight, a_fNear, a_fFar);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline void azMatrix4x4::BuildLookAt(const azVector3& a_f3From, const azVector3& a_f3To, const azVector3& a_f3Up)
{
    // \todo Handle properly case where (To - From) and Up are collinear

    azVector3 f3ZAxis = a_f3To - a_f3From;
    f3ZAxis.SelfNormalize();

    azVector3 f3XAxis = VectorCross(a_f3Up, f3ZAxis);
    f3XAxis.SelfNormalize();

    azVector3 f3YAxis = VectorCross(f3ZAxis, f3XAxis);

    m_f4Row0.Set(f3XAxis.m_fX, f3XAxis.m_fY, f3XAxis.m_fZ, -VectorDot(f3XAxis, a_f3From));
    m_f4Row1.Set(f3YAxis.m_fX, f3YAxis.m_fY, f3YAxis.m_fZ, -VectorDot(f3YAxis, a_f3From));
    m_f4Row2.Set(f3ZAxis.m_fX, f3ZAxis.m_fY, f3ZAxis.m_fZ, -VectorDot(f3ZAxis, a_f3From));
    m_f4Row3.Set(0.f, 0.f, 0.f, 1.f);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector3 azMatrix4x4::Transform(const azVector3& a_f3Operand, azFloat a_fW) const
{
    azVector4 f4Operand(a_f3Operand.m_fX, a_f3Operand.m_fY, a_f3Operand.m_fZ, a_fW);
    return azVector3(VectorDot(m_f4Row0, f4Operand),
        VectorDot(m_f4Row1, f4Operand),
        VectorDot(m_f4Row2, f4Operand));
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azVector4 azMatrix4x4::Transform(const azVector4& a_f4Operand) const
{
    return azVector4(VectorDot(m_f4Row0, a_f4Operand),
        VectorDot(m_f4Row1, a_f4Operand),
        VectorDot(m_f4Row2, a_f4Operand),
        VectorDot(m_f4Row3, a_f4Operand));
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator +() const
{
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator -() const
{
    return azMatrix4x4(-m_f4Row0, -m_f4Row1, -m_f4Row2, -m_f4Row3);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator +(const azMatrix4x4& a_rOperand) const
{
    return azMatrix4x4(m_f4Row0 + a_rOperand.m_f4Row0,
        m_f4Row1 + a_rOperand.m_f4Row1,
        m_f4Row2 + a_rOperand.m_f4Row2,
        m_f4Row3 + a_rOperand.m_f4Row3);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator -(const azMatrix4x4& a_rOperand) const
{
    return azMatrix4x4(m_f4Row0 - a_rOperand.m_f4Row0,
        m_f4Row1 - a_rOperand.m_f4Row1,
        m_f4Row2 - a_rOperand.m_f4Row2,
        m_f4Row3 - a_rOperand.m_f4Row3);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator +=(const azMatrix4x4& a_rOperand)
{
    m_f4Row0 += a_rOperand.m_f4Row0;
    m_f4Row1 += a_rOperand.m_f4Row1;
    m_f4Row2 += a_rOperand.m_f4Row2;
    m_f4Row3 += a_rOperand.m_f4Row3;
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator -=(const azMatrix4x4& a_rOperand)
{
    m_f4Row0 -= a_rOperand.m_f4Row0;
    m_f4Row1 -= a_rOperand.m_f4Row1;
    m_f4Row2 -= a_rOperand.m_f4Row2;
    m_f4Row3 -= a_rOperand.m_f4Row3;
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator *(const azMatrix4x4& a_rOperand) const
{
    return azMatrix4x4(        
        VectorDot(m_f4Row0, azVector4(a_rOperand.m_f4Row0.m_fX, a_rOperand.m_f4Row1.m_fX, a_rOperand.m_f4Row2.m_fX, a_rOperand.m_f4Row3.m_fX)),
        VectorDot(m_f4Row0, azVector4(a_rOperand.m_f4Row0.m_fY, a_rOperand.m_f4Row1.m_fY, a_rOperand.m_f4Row2.m_fY, a_rOperand.m_f4Row3.m_fY)),
        VectorDot(m_f4Row0, azVector4(a_rOperand.m_f4Row0.m_fZ, a_rOperand.m_f4Row1.m_fZ, a_rOperand.m_f4Row2.m_fZ, a_rOperand.m_f4Row3.m_fZ)),
        VectorDot(m_f4Row0, azVector4(a_rOperand.m_f4Row0.m_fW, a_rOperand.m_f4Row1.m_fW, a_rOperand.m_f4Row2.m_fW, a_rOperand.m_f4Row3.m_fW)),

        VectorDot(m_f4Row1, azVector4(a_rOperand.m_f4Row0.m_fX, a_rOperand.m_f4Row1.m_fX, a_rOperand.m_f4Row2.m_fX, a_rOperand.m_f4Row3.m_fX)),
        VectorDot(m_f4Row1, azVector4(a_rOperand.m_f4Row0.m_fY, a_rOperand.m_f4Row1.m_fY, a_rOperand.m_f4Row2.m_fY, a_rOperand.m_f4Row3.m_fY)),
        VectorDot(m_f4Row1, azVector4(a_rOperand.m_f4Row0.m_fZ, a_rOperand.m_f4Row1.m_fZ, a_rOperand.m_f4Row2.m_fZ, a_rOperand.m_f4Row3.m_fZ)),
        VectorDot(m_f4Row1, azVector4(a_rOperand.m_f4Row0.m_fW, a_rOperand.m_f4Row1.m_fW, a_rOperand.m_f4Row2.m_fW, a_rOperand.m_f4Row3.m_fW)),

        VectorDot(m_f4Row2, azVector4(a_rOperand.m_f4Row0.m_fX, a_rOperand.m_f4Row1.m_fX, a_rOperand.m_f4Row2.m_fX, a_rOperand.m_f4Row3.m_fX)),
        VectorDot(m_f4Row2, azVector4(a_rOperand.m_f4Row0.m_fY, a_rOperand.m_f4Row1.m_fY, a_rOperand.m_f4Row2.m_fY, a_rOperand.m_f4Row3.m_fY)),
        VectorDot(m_f4Row2, azVector4(a_rOperand.m_f4Row0.m_fZ, a_rOperand.m_f4Row1.m_fZ, a_rOperand.m_f4Row2.m_fZ, a_rOperand.m_f4Row3.m_fZ)),
        VectorDot(m_f4Row2, azVector4(a_rOperand.m_f4Row0.m_fW, a_rOperand.m_f4Row1.m_fW, a_rOperand.m_f4Row2.m_fW, a_rOperand.m_f4Row3.m_fW)),

        VectorDot(m_f4Row3, azVector4(a_rOperand.m_f4Row0.m_fX, a_rOperand.m_f4Row1.m_fX, a_rOperand.m_f4Row2.m_fX, a_rOperand.m_f4Row3.m_fX)),
        VectorDot(m_f4Row3, azVector4(a_rOperand.m_f4Row0.m_fY, a_rOperand.m_f4Row1.m_fY, a_rOperand.m_f4Row2.m_fY, a_rOperand.m_f4Row3.m_fY)),
        VectorDot(m_f4Row3, azVector4(a_rOperand.m_f4Row0.m_fZ, a_rOperand.m_f4Row1.m_fZ, a_rOperand.m_f4Row2.m_fZ, a_rOperand.m_f4Row3.m_fZ)),
        VectorDot(m_f4Row3, azVector4(a_rOperand.m_f4Row0.m_fW, a_rOperand.m_f4Row1.m_fW, a_rOperand.m_f4Row2.m_fW, a_rOperand.m_f4Row3.m_fW)) );
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator *(azFloat a_fOperand)
{
    return azMatrix4x4(m_f4Row0 * a_fOperand, m_f4Row1 * a_fOperand, m_f4Row2 * a_fOperand, m_f4Row3 * a_fOperand);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 azMatrix4x4::operator /(azFloat a_fOperand)
{
    return azMatrix4x4(m_f4Row0 / a_fOperand, m_f4Row1 / a_fOperand, m_f4Row2 / a_fOperand, m_f4Row3 / a_fOperand);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator *=(const azMatrix4x4& a_rOperand)
{
    rThis = rThis * a_rOperand;
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator *=(azFloat a_fOperand)
{
    m_f4Row0 *= a_fOperand;
    m_f4Row1 *= a_fOperand;
    m_f4Row2 *= a_fOperand;
    m_f4Row3 *= a_fOperand;
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline const azMatrix4x4& azMatrix4x4::operator /=(azFloat a_fOperand)
{
    m_f4Row0 /= a_fOperand;
    m_f4Row1 /= a_fOperand;
    m_f4Row2 /= a_fOperand;
    m_f4Row3 /= a_fOperand;
    return rThis;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline bool azMatrix4x4::operator ==(const azMatrix4x4& a_rOperand) const
{
    return (a_rOperand.m_f4Row0 == m_f4Row0 &&
            a_rOperand.m_f4Row1 == m_f4Row1 &&
            a_rOperand.m_f4Row2 == m_f4Row2 &&
            a_rOperand.m_f4Row3 == m_f4Row3);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline bool azMatrix4x4::operator !=(const azMatrix4x4& a_rOperand) const
{
    return !(rThis == a_rOperand);
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
    return &m_f4Row0.m_fX;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4::operator azFloat*()
{
    return &m_f4Row0.m_fX;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
inline azMatrix4x4 operator *(azFloat a_fOperand1, const azMatrix4x4& a_rOperand2)
{
    return a_rOperand2 * a_fOperand1;
}


