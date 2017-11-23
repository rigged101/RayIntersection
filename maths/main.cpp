
#include "BruteRayIntersection.h"
//#include <memory>
//#include <iostream>
//#include "OBJ_Loader.h"
//#include "Maths.h"
//#include <cmath>
//#include <time.h>
//#include <Vector>
//#include <math.h>


float Q_rsqrt(float number);

int SuperRecursive(int _n, int z);


int main()
{
	int temp_x = 0;
	int temp_y = 1;
	// redundant obsolete
	if (temp_x = temp_y)
	{
		/*Maths math;
		Vector3 vec1, vec2, vec3;
		float dotProduct;


		vec1.x = 3.0f;
		vec1.y = 4.0f;
		vec1.z = 0.0f;
		vec3.x = -1.0f;
		vec3.y = 0.0f;
		vec3.z = 0.0f;


		std::cout << "Input Vector3 2 x value" << std::endl;
		std::cin >> vec2.x;

		std::cout << "Input Vector3 2 y value" << std::endl;
		std::cin >> vec2.y;

		std::cout << "input Vector3 2 z value" << std::endl;
		std::cin >> vec2.z;

		vec1 = math.Normalise(vec1);
		vec2 = math.Normalise(vec2);


		dotProduct = math.DotProduct(vec1, vec2);
		float angleRadians = acos(dotProduct);
		float angleDegrees = angleRadians * (180 / math.PI);
		std::cout << "Shortest angle is " << math.ShortestAngle(vec1, vec2);
		std::cout << "antiClockWise Angle is :" << math.AntiClockwiseAngle(vec1, vec2, vec3);
		std::cout << " \n\n Answer is " << dotProduct << std::endl;
		std::cout << "\n\n in radians it is" << angleRadians << std::endl;
		std::cout << "\n\n in degrees it is" << angleDegrees << std::endl;
	*/

	//float a, b, c, f, g, x1, x2;

	//g = 12345675.0f;
	//f = 12345674.7f;
	//a = g - f;
	//b = 2.0f;
	//c = 1.0f;

	//x1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	//x2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);

	//std::cout << "Task 2 values are as following, for positive its :" << x1 << "  and negative X its " << x2 << std:: endl;


	//clock_t start = clock();
	//float calculation = 0;
	//float a = 25.0f;

	//for (int i = 0; i < 100000000; i++)
	//{
	//	calculation = a / 5.0f;
	//}

	//clock_t stop = clock();
	//std::cout << "time = " << (stop - start) / double(CLOCKS_PER_SEC) << "\n\n";

	//start = clock();

	//for (int i = 0; i < 100000000; i++)
	//{
	//	calculation = a * 0.2f;
	//}

	//stop = clock();
	//std::cout << "time = " << (stop - start) / double(CLOCKS_PER_SEC) << "\n\n";

	//start = clock();

	//for (int i = 0; i < 100000000; i++)
	//{
	//	long j;
	//	float x2, y;
	//	const float threehalfs = 1.5F;

	//	x2 = a * 0.5F;
	//	y = a;
	//	j = *(long *)&y;                       // evil floating point bit level hacking
	//	j = 0x5f3759df - (j >> 1);               // what the fuck? 
	//	y = *(float *)&j;
	//	calculation += y * (threehalfs - (x2 * y * y));

	//	//calculation = Q_rsqrt(a);
	//}

	//stop = clock();
	//std::cout << "time todo quake sqrt = " << (stop - start) / double(CLOCKS_PER_SEC) << "quake sqrt is" << calculation << "\n\n";

	//start = clock();

	//for (int i = 0; i < 100000000; i++)
	//{
	//	long j;
	//	float x2, y;

	//	y = a;
	//	j = *(long *)&y;                       // evil floating point bit level hacking
	//	j = 0x1fbd1df5 + (j >> 1);               // what the fuck? 
	//	calculation += *(float *)&j;


	//	//calculation = Q_rsqrt(a);
	//}

	//stop = clock();
	//std::cout << "time todo actual modified quake sqrt = " << (stop - start) / double(CLOCKS_PER_SEC) << "modified quake sqrt is" << 1.0f / calculation << "\n\n";


	//start = clock();

	//for (int i = 0; i < 100000000; i++)
	//{
	//	calculation += 1.0f / sqrt(a);
	//}


	//stop = clock();
	//std::cout << "time todo sqrt = " << (stop - start) / double(CLOCKS_PER_SEC) << "normal sqrt is" << calculation << "\n\n";;

	//Vector3 b1, b2, d1, d2;
	//b1.x = 2;
	//b1.y = 3;
	//b1.z = 4;

	//d1.x = 1;
	//d1.y = 1;
	//d1.z = 1;

	//b2.x = -2;
	//b2.y = -3;
	//b2.z = -4;

	//d2.x = 1;
	//d2.y = 2;
	//d2.z = 3;




	//Maths math;

	//// a11 = d1.x | a12 = b1.x a21 = -b2.y a22 = -b1.y

	//float k1 = b2.x - b1.x;
	//float k2 = b2.y - b1.y;

	//float determinant = (d1.x * -d2.y) - (-d2.x * d1.y);

	//float mu = ((-d2.y * k1) - (-d2.x * k2)) / determinant;
	//float lambda = ((d1.x * k2) - (d1.y* k1)) / determinant;

	//float check1 = b1.z + (mu * d1.z);
	//float check2 = b2.z + (lambda * d2.z);
	//
	//Vector3 j = math.AddVec(b1, (math.MulVec(d1, mu)));
	//Vector3 h = math.AddVec(b2, (math.MulVec(d2, lambda)));

	//std::cout << "the answetr for mu is" << mu << "\n\nthe answer for lambda is: " << lambda << std::endl;
	//std::cout << "check1 is" << check1 << "\n\n check2 is :" << check2 << std::endl;
	//std::cout << "Answer for Vector3 one " << j.x << j.y << j.z << "\n\n Answer for Vector3 two is" << h.x << h.y << h.z << std::endl;
	}


	Vector3 A(1, 0, 1); //cb
	Vector3 B(0, 3, 0); //ab
	Vector3 C(-2, 0, 0);
	Vector3 e(0, 1, 5);
	Vector3 d(0, 0, -1);

	
	Maths math;

	BruteRayIntersection BruteRI;
	BruteRI.Update();


	
	std::cout << "\nProjection is " << math.Projection(A, B) << std::endl;

	Vector3 normal = math.CrossProduct(math.SubVec(B,A), math.SubVec(C,A));
	normal = math.Normalise(normal);

	float k = math.DotProduct(normal, A);

	std::cout << "value of K is" << k << std::endl;

	float t = (k -  math.DotProduct(normal, e)) / math.DotProduct(normal, d);

	Vector3 Q = math.AddVec(e, math.MulVecByFloat(d, t));

	float One = math.DotProduct(math.CrossProduct(math.SubVec(B, A), math.SubVec(Q, A)), normal);
	float Two = math.DotProduct(math.CrossProduct(math.SubVec(C, B), math.SubVec(Q, B)), normal);
	float Three = math.DotProduct(math.CrossProduct(math.SubVec(A, C), math.SubVec(Q, C)), normal);

	if (One >= 0 && Two >= 0 && Three >= 0)
	{
		std::cout << "\n The intersection point Q is inside the triangle" <<  Q << std::endl;
	}
	else
	{
		std::cout << "\n The intersection point Q is not inside the triangle" << Q << std::endl;
	}

	std::cout << "intersection point Q IS :" << Q << "\nNormal is " << normal << "\nt is : " << t << std::endl;






	system("PAUSE");

	return 0;

}


int SuperRecursive(int _n, int z)
{

	if (_n > 0)
	{
	    z += 5 * 5 + 10 * 10 + 15 * 15;
		SuperRecursive(_n - 1, z);
		SuperRecursive(_n - 1, z);
	}
	return z;
}


float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck? 
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
										   //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}