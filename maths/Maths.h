#pragma once
#include <iostream>


struct Vector3
{
	Vector3() 
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float x;
	float y;
	float z;
};

class Maths
{
public:


	const double PI = 3.14159265359;

	Vector3 Projection(Vector3 _v1, Vector3 _v2);
	Vector3 AddVec(Vector3 _v1, Vector3 _v2);
	Vector3 SubVec(Vector3 _v1, Vector3 _v2);
	Vector3 MulVec(Vector3 _v1, float _f);
	Vector3 MulVecByFloat(Vector3 _v1, float _a);
	float DotProduct(Vector3 _v1, Vector3 _v2);
	float Magnitude(Vector3 _v1);
	Vector3 Normalise(Vector3 _v1);
	Vector3 CrossProduct(Vector3 _v1, Vector3 _v2);
	float TripleProduct(Vector3 _v1, Vector3 _v2, Vector3 _v3);
	float ShortestAngle(Vector3 _v1, Vector3 _v2);
	float AntiClockwiseAngle(Vector3 _v1, Vector3 _v2, Vector3 _viewingVec);


	friend std::ostream& operator<<(std::ostream& currentOS, Vector3 _v1);

	


	Maths();

	~Maths();
};

