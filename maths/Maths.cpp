#include "Maths.h"
#include <cmath>





Maths::Maths()
{

}


Maths::~Maths()
{

}

float Maths::DotProduct(Vector3 _v1, Vector3 _v2)
{
	return (_v1.x * _v2.x) + (_v1.y * _v2.y) + (_v1.z * _v2.z);

}


float Maths::Magnitude(Vector3 _v1)
{

	return sqrt((_v1.x * _v1.x) + (_v1.y * _v1.y) + (_v1.z * _v1.z));

}

Vector3 Maths::Normalise(Vector3 _v1)
{
	Vector3 temp;
	float _length = Magnitude(_v1);

	temp.x = _v1.x / _length;
	temp.y = _v1.y / _length;
	temp.z = _v1.z / _length;

	return temp;

}

Vector3 Maths::CrossProduct(Vector3 _v1, Vector3 _v2)
{

	Vector3 result;

	result.x = (_v1.y * _v2.z) - (_v1.z * _v2.y);
	result.y = (_v1.z * _v2.x) - (_v1.x * _v2.z);
	result.z = (_v1.x * _v2.y) - (_v1.y * _v2.x);

	return result;
	
}

float Maths::TripleProduct(Vector3 _v1, Vector3 _v2, Vector3 _v3)
{
	float result;

	Vector3 crossProduct = CrossProduct(_v1, _v2);

	result = DotProduct(_v3, crossProduct);

	return result;

}

float Maths::ShortestAngle(Vector3 _v1, Vector3 _v2)
{
	float result;

	result = DotProduct(_v1, _v2) / (Magnitude(_v1) * Magnitude(_v2));

	return result;

}

float Maths::AntiClockwiseAngle(Vector3 _v1, Vector3 _v2, Vector3 _viewingVec)
{
	float result;
	result = ShortestAngle(_v1, _v2);

	float tripleProduct = TripleProduct(_v1, _v2, _viewingVec);
	if (tripleProduct < 0)
	{
		result = 360 - result;
	}

	return result;
}

Vector3 Maths::MulVec(Vector3 _v1, float _f)
{
	Vector3 ans;

	ans.x = _v1.x * _f;
	ans.y = _v1.y * _f;
	ans.z = _v1.z * _f;

	return ans;
	
}

Vector3 Maths::Projection(Vector3 _v1, Vector3 _v2) // _v2 is what youre project onto _v1
{
	float tempMagnitude = Magnitude(_v1);
	float temp = DotProduct(_v2, _v1) / (tempMagnitude* tempMagnitude);

	 Vector3 tempProjection = MulVecByFloat(_v1, temp);

	 return tempProjection;
}

Vector3 Maths::AddVec(Vector3 _v1, Vector3 _v2)
{
	Vector3 result;

	result.x = _v1.x + _v2.x;
	result.y = _v1.y + _v2.y;
	result.z = _v1.z + _v2.z;

	return result;


}

Vector3 Maths::SubVec(Vector3 _v1, Vector3 _v2)
{
	Vector3 result;

	result.x = _v1.x - _v2.x;
	result.y = _v1.y - _v2.y;
	result.z = _v1.z - _v2.z;

	return result;


}

Vector3 Maths::MulVecByFloat(Vector3 _v1, float _a)
{
	Vector3 result;

	result.x = _v1.x * _a;
	result.y = _v1.y * _a;
	result.z = _v1.z * _a;

	return result;

}

std::ostream& operator<<(std::ostream& currentOS, Vector3 _v1)
{

	currentOS << _v1.x << ", " << _v1.y << ", " << _v1.z;

	return currentOS;

}

