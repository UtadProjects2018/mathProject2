//
//  VECTOR3D.h
//  StereoRendering
//
//  Created by Jose Maria Benito on 09/12/13.
//  Copyright (c) 2013 Jose Maria. All rights reserved.
//

#ifndef StereoRendering_VECTOR3D_h
#define StereoRendering_VECTOR3D_h

#define ABS(x) (x < 0 ? -(x) : (x))
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define TRUE  1
#define FALSE 0
#define ESC 27
#define PI 3.141592653589793238462643
#define DTOR            0.0174532925    // degrees to radians
#define RTOD            57.2957795      // radians to degrees


typedef struct {
    double x,y,z;
} VECTOR3D;


typedef struct {
    double r,g,b;
} COLOUR;

typedef struct {
    VECTOR3D column0;
    VECTOR3D column1;
    VECTOR3D column2;
} MATRIX3;


typedef struct {
    float m[16];
} MATRIX4;

static const COLOUR grey = {0.7,0.7,0.7};
static const COLOUR red = {1,0,0};
static const COLOUR green = {0,1,0};
static const COLOUR blue = {0,0,1};

static const COLOUR darkred = {0.6,0,0};
static const COLOUR darkgreen = {0,0.6,0};

static const VECTOR3D forward = { 0, 0, -1 };
static const VECTOR3D up = { 0, 1, 0 };
static const VECTOR3D vectorYaw = { 0, 1, 0 };
static const VECTOR3D vectorPitch = { 1, 0, 0 };
static const VECTOR3D vectorROLL = { 0, 0, 1 };


VECTOR3D Add(VECTOR3D a, VECTOR3D b)
{
    VECTOR3D ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    ret.z = a.z + b.z;
    return ret;
}


VECTOR3D Substract(VECTOR3D a, VECTOR3D b)
{
    VECTOR3D ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    ret.z = a.z - b.z;
    return ret;
}


VECTOR3D Multiply(VECTOR3D a, VECTOR3D b)
{
    VECTOR3D ret;
    ret.x = a.x * b.x;
    ret.y = a.y * b.y;
    ret.z = a.z * b.z;
    return ret;
}


VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a)
{
    VECTOR3D ret;
    ret.x = a.x * scalar;
    ret.y = a.y * scalar;
    ret.z = a.z * scalar;
    return ret;
}

double Magnitude(VECTOR3D a)
{
    return sqrt((pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

VECTOR3D Normalize(VECTOR3D a)
{
    double magnitude = Magnitude(a);
    VECTOR3D normalizeVector { a.x/magnitude,  a.y/magnitude, a.z /magnitude};
    return normalizeVector;
}


VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b)
{
    /*
     CrossProduct Formula
     cx = ay*bz − az*by
     cy = az*bx − ax*bz
     cz = ax*by − ay*bx
     */
    VECTOR3D crossProduct = {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
    return crossProduct;
}

double DotProduct(VECTOR3D a, VECTOR3D b)
{
    /*
     Dot Product Formula
     a · b = ax × bx + ay × by + az × bz
     */
    return (a.x * b.x) + (a.y * b.y) + + (a.z * b.z);
}

MATRIX3 Transpose(MATRIX3 m)
{
    MATRIX3 result =
    {
        { m.column0.x, m.column1.x, m.column2.x },
        { m.column0.y, m.column1.y, m.column2.y },
        { m.column0.z, m.column1.z, m.column2.z }
    };
    return result;
}

VECTOR3D Transform (MATRIX3 m, VECTOR3D a)
{
    VECTOR3D result =
    {
        DotProduct(m.column0, a),
        DotProduct(m.column1, a),
        DotProduct(m.column2, a)
    };
    return result;
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t)
{
    /*
     A-1 = ATb - ATt (sii A ortogonal)
     */

    MATRIX3 transpose = Transpose(A);
    
    VECTOR3D multiply = MultiplyWithScalar(-1, t);
    
    VECTOR3D transposeMultiply  = Transform(transpose, multiply);
    
    MATRIX4 inverse = {
        static_cast<float>(transpose.column0.x), static_cast<float>(transpose.column0.y), static_cast<float>(transpose.column0.z), 0,
        static_cast<float>(transpose.column1.x), static_cast<float>(transpose.column1.y), static_cast<float>(transpose.column1.z), 0,
        static_cast<float>(transpose.column2.x), static_cast<float>(transpose.column2.y), static_cast<float>(transpose.column2.z), 0,
        static_cast<float>(transposeMultiply.x), static_cast<float>(transposeMultiply.y), static_cast<float>(transposeMultiply.z), 1 };
    return inverse;
}

#endif
