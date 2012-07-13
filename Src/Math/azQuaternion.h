//==========================================================
// Yes::Engine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================

#ifndef QUATERNION_H
#define QUATERNION_H

//==========================================================
// En-têtes
//==========================================================
#include <Maths/Matrix4.h>


namespace Yes
{
    ////////////////////////////////////////////////////////////
    // Classe des quaternions
    ////////////////////////////////////////////////////////////
    class CQuaternion
    {
    public :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        CQuaternion(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f);

        //----------------------------------------------------------
        // Constructeur à partir d'une matrice
        //----------------------------------------------------------
        CQuaternion(const azMatrix4x4& Matrix);

        //----------------------------------------------------------
        // Constructeur à partir d'un axe et d'un angle
        //----------------------------------------------------------
        CQuaternion(const TVector3F& Axis, float Angle);

        //----------------------------------------------------------
        // Met le quaternion à l'identité
        //----------------------------------------------------------
        void Identity();

        //----------------------------------------------------------
        // Normalise le quaternion
        //----------------------------------------------------------
        inline void Normalize();

        //----------------------------------------------------------
        // Renvoie le conjugué
        //----------------------------------------------------------
        CQuaternion Conjugate() const;

        //----------------------------------------------------------
        // Construit une matrice de rotation à partir du quaternion
        //----------------------------------------------------------
        azMatrix4x4 ToMatrix() const;

        //----------------------------------------------------------
        // Construit le quaternion à partir d'une matrice
        //----------------------------------------------------------
        void FromMatrix(const azMatrix4x4& Matrix);

        //----------------------------------------------------------
        // Construit le quaternion à partir d'un axe et d'un angle
        //----------------------------------------------------------
        void FromAxisAngle(const TVector3F& Axis, float Angle);

        //----------------------------------------------------------
        // Transforme le quaternion en axe & angle de rotation
        //----------------------------------------------------------
        void ToAxisAngle(TVector3F& Axis, float& Angle) const;

        //----------------------------------------------------------
        // Construit le quaternion à partir de 3 angles d'Euler
        //----------------------------------------------------------
        void FromEulerAngles(float X, float Y, float Z);

        //----------------------------------------------------------
        // Opérateur de multiplication
        //----------------------------------------------------------
        CQuaternion operator *(const CQuaternion& Quaternion) const;

        //----------------------------------------------------------
        // Opérateur de multiplication - affectation
        //----------------------------------------------------------
        const CQuaternion& operator *=(const CQuaternion& Quaternion);

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        float x; ///< Composante X
        float y; ///< Composante Y
        float z; ///< Composante Z
        float w; ///< Composante W
    };


    //==========================================================
    // Fonctions globales relatives aux quaternions
    //==========================================================
    std::istream& operator >>(std::istream& Stream, CQuaternion& Quaternion);
    std::ostream& operator <<(std::ostream& Stream, const CQuaternion& Quaternion);

    #include "Quaternion.inl"

} // namespace Yes


#endif // QUATERNION_H
