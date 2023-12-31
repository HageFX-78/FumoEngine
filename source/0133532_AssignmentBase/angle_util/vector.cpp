//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Edited 13/10/2021 @Faris
//  - reworked operator overloads.
//  - added +=, -=, *=, /=, -unary
//  - added instance-based normalized, length and lengthSquared
//  - added Vector4 ctor that takes Vector3 and w.

#include "vector.h"

#include <math.h>

Vector2::Vector2()
	: x(0.0),
	y(0.0)
{
}

Vector2::Vector2(float x, float y)
	: x(x),
	y(y)
{
}

float Vector2::length(const Vector2& vec)
{
	float lenSquared = lengthSquared(vec);
	return (lenSquared != 0.0f) ? sqrt(lenSquared) : 0.0f;
}

float Vector2::lengthSquared(const Vector2& vec)
{
	return vec.x * vec.x +
		vec.y * vec.y;
}

Vector2 Vector2::normalize(const Vector2& vec)
{
	Vector2 ret(0.0f, 0.0f);
	float len = length(vec);
	if (len != 0.0f)
	{
		float invLen = 1.0f / len;
		ret.x = vec.x * invLen;
		ret.y = vec.y * invLen;
	}
	return ret;
}

Vector3::Vector3()
	: x(0.0),
	y(0.0),
	z(0.0)
{
}

Vector3::Vector3(float x, float y, float z)
	: x(x),
	y(y),
	z(z)
{
}

float Vector3::length(const Vector3& vec)
{
	float lenSquared = lengthSquared(vec);
	return (lenSquared != 0.0f) ? sqrt(lenSquared) : 0.0f;
}

float Vector3::lengthSquared(const Vector3& vec)
{
	return vec.x * vec.x +
		vec.y * vec.y +
		vec.z * vec.z;
}

Vector3 Vector3::normalize(const Vector3& vec)
{
	Vector3 ret(0.0f, 0.0f, 0.0f);
	float len = length(vec);
	if (len != 0.0f)
	{
		float invLen = 1.0f / len;
		ret.x = vec.x * invLen;
		ret.y = vec.y * invLen;
		ret.z = vec.z * invLen;
	}
	return ret;
}

void Vector3::normalize()
{
	float len = length();
	float invLen = 1.0f / len;
	x *= invLen;
	y *= invLen;
	z *= invLen;
}

float Vector3::length()
{
	float lenSquared = lengthSquared();
	return (lenSquared != 0.0f) ? sqrt(lenSquared) : 0.0f;
}

float Vector3::lengthSquared()
{
	return x * x + y * y + z * z;
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x +
		a.y * b.y +
		a.z * b.z;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

Vector3 Vector3::operator*(const Vector3& other)
{
	return Vector3(x * other.x,
		y * other.y,
		z * other.z);
}

Vector3 Vector3::operator*(const float& other)
{
	return Vector3(x * other,
		y * other,
		z * other);
}

Vector3 Vector3::operator/(const Vector3& other)
{
	return Vector3(x / other.x,
		y / other.y,
		z / other.z);
}

Vector3 Vector3::operator/(const float& other)
{
	return Vector3(x / other,
		y / other,
		z / other);
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(x + other.x,
		y + other.y,
		z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(x - other.x,
		y - other.y,
		z - other.z);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vector3& Vector3::operator*=(const float& other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vector3& Vector3::operator/=(const float& other)
{
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

Vector4::Vector4()
	: x(0.0f),
	y(0.0f),
	z(0.0f),
	w(0.0f)
{
}

Vector4::Vector4(const Vector3& vec, float w)
	: x(vec.x),
	y(vec.y),
	z(vec.z),
	w(w)
{
}

Vector4::Vector4(float x, float y, float z, float w)
	: x(x),
	y(y),
	z(z),
	w(w)
{
}

float Vector4::length(const Vector4& vec)
{
	float lenSquared = lengthSquared(vec);
	return (lenSquared != 0.0f) ? sqrt(lenSquared) : 0.0f;
}

float Vector4::lengthSquared(const Vector4& vec)
{
	return vec.x * vec.x +
		vec.y * vec.y +
		vec.z * vec.z +
		vec.w * vec.w;
}

Vector4 Vector4::normalize(const Vector4& vec)
{
	Vector4 ret(0.0f, 0.0f, 0.0f, 1.0f);
	if (vec.w != 0.0f)
	{
		float invLen = 1.0f / vec.w;
		ret.x = vec.x * invLen;
		ret.y = vec.y * invLen;
		ret.z = vec.z * invLen;
	}
	return ret;
}

float Vector4::dot(const Vector4& a, const Vector4& b)
{
	return a.x * b.x +
		a.y * b.y +
		a.z * b.z +
		a.w * b.w;
}