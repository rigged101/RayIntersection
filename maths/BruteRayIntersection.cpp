#include "BruteRayIntersection.h"




BruteRayIntersection::BruteRayIntersection()
{

	//ObjLoader.LoadFile("objFile/typhoon.obj");
	//ObjLoader.LoadFile("objFile/uh60.obj");
	//ObjLoader.LoadFile("objFile/htc-wizard-midpoly.obj");
	//ObjLoader.LoadFile("objFile/lego_people.obj");
	ObjLoader.LoadFile("objFile/humanoid_tri.obj");
	std::cout << "the amount of vertices" << ObjLoader.LoadedVertices.size() << std::endl;

}


BruteRayIntersection::~BruteRayIntersection()
{

}

void BruteRayIntersection::Update()
{
	ObjectVerticeConversion();
	clock_t start = clock();
	RayPointPopulation();
	clock_t stop = clock();

	int average = 10;
	start = clock();

	for (int i = 0; i < average; i++)
	{
		BruteForceRayIntersection();
	}
	stop = clock();
	


	std::cout << "the time for  Matrix bruteforce method is " << (float)(stop - start) / CLOCKS_PER_SEC / average   << std::endl;


	//start = clock();

	//
	//SecondBruteForceRayIntersection();
	//stop = clock();
	//std::cout << "the time for matrix bruteforce method is " << (float)(stop - start) / CLOCKS_PER_SEC  << std::endl;

	//start = clock();

	//ParBruteForceRayIntersection();

	//stop = clock();
	//std::cout << "the time for parallel bruteforce method is " << (float)(stop - start) / CLOCKS_PER_SEC << std::endl;

	//start = clock();

	//BruteForceRayIntersection();

	//stop = clock();
	//std::cout << "the time for bruteforce method is " << (float)(stop - start) / CLOCKS_PER_SEC << std::endl;

	////system("PAUSE");

	//start = clock();

	//BarycentricRayIntersection();

	//stop = clock();
	//std::cout << "the time for baracentric method is " << (float)(stop - start) / CLOCKS_PER_SEC << std::endl;

	
}


void BruteRayIntersection::ObjectVerticeConversion()
{


	for (unsigned int i = 0; i < ObjLoader.LoadedMeshes.size(); i++)
	{
		for (unsigned int j = 0; j < ObjLoader.LoadedMeshes.at(i).Vertices.size(); j++)
		{
			
			tempContainer.x = ObjLoader.LoadedMeshes.at(i).Vertices.at(j).Position.X;
			tempContainer.y = ObjLoader.LoadedMeshes.at(i).Vertices.at(j).Position.Y;
			tempContainer.z = ObjLoader.LoadedMeshes.at(i).Vertices.at(j).Position.Z;
			objVertVecContainer.push_back(tempContainer);
		}
	}

}


void BruteRayIntersection::RayPointPopulation()
{
	for (float i = 0; i < 256; i++)
	{
		for (float j = 0; j < 256; j++)
		{
			rayContainer.push_back(Vector3(0.0f, i, j));
		}
	}
}

void BruteRayIntersection::BruteForceRayIntersection()
{
	Vector3 d(1, 0, 0);
	
	int totalIntersections = 0;
	for (unsigned int i = 0; i < objVertVecContainer.size(); i += 3) // i = A, i + 1 = B , i + 2 = C
	{

		Vector3 tempNormal = math.CrossProduct(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i))
			, math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i))); //15 operations * objVertVecContainer.size()
		tempNormal = math.Normalise(tempNormal); //8 operations * objVertVecContainer.size() // normal of the plane
		float k = math.DotProduct(tempNormal, objVertVecContainer.at(i)); // 5 operations * objVertVecContainer.size()


		
		for (unsigned int j = 0; j < rayContainer.size(); j++) // total size of raycontainer is 65536
		{


			float t =  (k - math.DotProduct(tempNormal, rayContainer.at(j))) / math.DotProduct(tempNormal, d); // 12 operations * rayContainer.size()
			if (t > 0.0f) // 1 operation * rayContainer.size()
			{


				Vector3 Q = math.AddVec(rayContainer.at(j), math.MulVecByFloat(d, t)); // 6 operations * rayContainer.size()

				if (Q.y >= 0.0f)
				{
					float One = math.DotProduct(math.CrossProduct(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)),
						math.SubVec(Q, objVertVecContainer.at(i))), tempNormal); // 20 operations * rayContainer.size()
					float Two = math.DotProduct(math.CrossProduct(math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i + 1)),
						math.SubVec(Q, objVertVecContainer.at(i + 1))), tempNormal); // 20operations * rayContainer.size()
					float Three = math.DotProduct(math.CrossProduct(math.SubVec(objVertVecContainer.at(i), objVertVecContainer.at(i + 2)),
						math.SubVec(Q, objVertVecContainer.at(i + 2))), tempNormal); // 20 operations * rayContainer.size()

					if (One >= 0 && Two >= 0 && Three >= 0) //  6 operations checking all vertices to see if the point is really inside the triangle
					{


						totalIntersections++;
					} // 113 operations
				}

			}
			


		}
	}
	std::cout << "\ntotal intersection points using bruteforce in the the model : " << totalIntersections << std::endl;
}


void BruteRayIntersection::MollerBruteForceRayIntersection()
{
	Vector3 d(1, 0, 0);

	int totalIntersections = 0;
	for (unsigned int i = 0; i < objVertVecContainer.size(); i += 3) // i = A, i + 1 = B , i + 2 = C
	{

		Vector3 edge1 = math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)); // 3 operations
		Vector3 edge2 = math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i)); // 3 operations

		Vector3 h = math.CrossProduct(d, edge2); // 9 operations
		float t = math.DotProduct(edge1, h); // 5 operations

		if (fabs(t) > 0.0000001f) // 1 operation
		{

			for (unsigned int j = 0; j < rayContainer.size(); j++)
			{
				float f = 1.0f / t; // 1 operation

				Vector3 s = math.SubVec(rayContainer.at(j), objVertVecContainer.at(i)); // 3 opertions
				float u = f * (math.DotProduct(s, h)); // 6 operations

				if (u <= 1.0f && u >= 0.0f) // 4 operations
				{
					Vector3 q = math.CrossProduct(s, edge1); // 9 operations
					float v = f * math.DotProduct(d, q); // 6 operations

					if (v >= 0.0f &&  u + v <= 1.0f) // 4 operations
					{
						float m = f * math.DotProduct(edge2, q); // intersection point
						if (m > 0.0000001f) // 1 operation
						{
							totalIntersections++;
						}
					} // total 55 operations

				}

			}
		}
	}
	std::cout << "\ntotal intersection points using bruteforce in the the model : " << totalIntersections << std::endl;
}

void BruteRayIntersection::SecondBruteForceRayIntersection()
{
	Vector3 d(1.0f, 0.0f, 0.0f);
	

	int totalIntersections = 0;
	for (unsigned int i = 0; i < objVertVecContainer.size(); i += 3) // i = A, i + 1 = B , i + 2 = C
	{
		

		Vector3 edge1 = math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)); // 3 operations
		Vector3 edge2 = math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i));// 3 operation
			
		Vector3 normal = math.CrossProduct(edge1, edge2); // 9 operations

		float matrix[3][4];

		if (fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z)) //2 operations
		{
			
			matrix[0][0] = 0.0f;
			matrix[1][0] = 0.0f;
			matrix[2][0] = 1.0f;
			matrix[0][1] = edge2.z / normal.x; //1 operation
			matrix[1][1] = -edge1.z / normal.x; // 1 operations
			matrix[2][1] = normal.y / normal.x; // 1 operations
			matrix[0][2] = -edge2.y / normal.x; // 1 operation
			matrix[1][2] = edge1.y / normal.x; // 1 operation
			matrix[2][2] = normal.z / normal.x; // 1 operation
			matrix[0][3] = math.CrossProduct(objVertVecContainer.at(i + 2), objVertVecContainer.at(i)).x / normal.x; // 10 operations
			matrix[1][3] = -(math.CrossProduct(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)).x / normal.x); // 10 operations
			matrix[2][3] = -(math.DotProduct(objVertVecContainer.at(i), normal) / normal.x); // 6 operations


		}
			
		else if (fabs(normal.y) > fabs(normal.z)) // 1 operation
		{
			
			matrix[0][0] = -(edge2.z / normal.y); // 1 operation
			matrix[1][0] = edge1.z / normal.y; // 1 operation
			matrix[2][0] = normal.x / normal.y; // 1 operation
			matrix[0][1] = 0.0f;
			matrix[1][1] = 0.0f;
			matrix[2][1] = 1.0f;
			matrix[0][2] = edge2.x / normal.y; // 1 operation
			matrix[1][2] = -(edge1.x / normal.y); // 1 operation
			matrix[2][2] = normal.z / normal.y; // 1 operation
			matrix[0][3] = math.CrossProduct(objVertVecContainer.at(i + 2), objVertVecContainer.at(i)).y / normal.y; // 10 operations
			matrix[1][3] = -(math.CrossProduct(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)).y / normal.y); // 10 operations
			matrix[2][3] = -(math.DotProduct(objVertVecContainer.at(i), normal) / normal.y); // 6 oeprations


		}
		else if (fabs(normal.z) > 0.0f) // 1 operation
		{
			

			matrix[0][0] = edge2.y / normal.z; // 1 operation
			matrix[1][0] = -(edge1.y / normal.z); // 1 operation 
			matrix[2][0] = normal.x / normal.z; // 1 operation
			matrix[0][1] = -(edge2.x / normal.z); // 1 operation
			matrix[1][1] = edge1.x / normal.z; // 1 operation
			matrix[2][1] = normal.y / normal.z; // 1 operation
			matrix[0][2] = 0.0;
			matrix[1][2] = 0.0f;
			matrix[2][2] = 1.0f;
			matrix[0][3] = math.CrossProduct(objVertVecContainer.at(i + 2), objVertVecContainer.at(i)).z / normal.z; //10 operations
			matrix[1][3] = -(math.CrossProduct(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)).z / normal.z); // 10 operations
			matrix[2][3] = -(math.DotProduct(objVertVecContainer.at(i), normal) / normal.z); // 6 operations

		}
		else
		{
			matrix[0][0] = 0.0f;
			matrix[1][0] = 0.0f;
			matrix[2][0] = 0.0f;
			matrix[0][1] = 0.0f;
			matrix[1][1] = 0.0f;
			matrix[2][1] = 0.0f;
			matrix[0][2] = 0.0f;
			matrix[1][2] = 0.0f;
			matrix[2][2] = 0.0f;
			matrix[0][3] = 0.0f;
			matrix[1][3] = 0.0f;
			matrix[2][3] = 0.0f;
		}
		


		float rayDirectionTransform =  (matrix[2][0]*d.x) + (matrix[2][1]*d.y) + (matrix[2][2]*d.z); // 5 operations

		
			for (unsigned int j = 0; j < rayContainer.size(); j++)
			{

				float rayOriginPointTransform = (matrix[2][0] * rayContainer.at(j).x) + (matrix[2][1] * rayContainer.at(j).y) + (matrix[2][2] * rayContainer.at(j).z) + matrix[2][3]; // 6 operations
			
				float t = -rayOriginPointTransform / rayDirectionTransform; // 1 operation

				if (t >= 0.0f) // 2operations
				{
					Vector3 intersect(rayContainer.at(j).x + t * d.x, rayContainer.at(j).y + t * d.y, rayContainer.at(j).z + t * d.z); // 6 operations

					float b1 = (matrix[0][0] * intersect.x) + (matrix[0][1] * intersect.y) + (matrix[0][2] * intersect.z) + matrix[0][3]; // 6 operations
					float b2 = (matrix[1][0] * intersect.x) + (matrix[1][1] * intersect.y) + (matrix[1][2] * intersect.z) + matrix[1][3]; // 6 operations


					if (b1 > 0.0f && b2 > 0.0f && b1 + b2 < 1.0f) // 3 operations
					{
						totalIntersections++;
					}
				} // 86 operations



			}
		
		
	
	}
	std::cout << "\ntotal intersection points using bruteforce in the the model : " << totalIntersections << std::endl;
}

void BruteRayIntersection::ParBruteForceRayIntersection()
{
	Vector3 d(1, 0, 0);
	const size_t nloop = 11;
	int totalIntersections = 0;
	for (unsigned int i = 0; i < objVertVecContainer.size(); i += 3) // i = A, i + 1 = B , i + 2 = C
	{

		Vector3 tempNormal = math.CrossProduct(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i))
			, math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i))); //15 operations
		tempNormal = math.Normalise(tempNormal); //8 operations // normal of the plane
		float k = math.DotProduct(tempNormal, objVertVecContainer.at(i)); // 5 operations // constant

		int sizeOfContainer = rayContainer.size();
		
		//for (unsigned int j = 0; j < rayContainer.size(); j++)
		
		Concurrency::parallel_for(0, sizeOfContainer, [&](int j)
		{


			float t = (k - math.DotProduct(tempNormal, rayContainer.at(j))) / math.DotProduct(tempNormal, d); // 12 operations
			if (t > 0)
			{


				Vector3 Q = math.AddVec(rayContainer.at(j), math.MulVecByFloat(d, t)); // 6 operations // intersection


				float One = math.DotProduct(math.CrossProduct(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)),
					math.SubVec(Q, objVertVecContainer.at(i))), tempNormal); // 20 operations
				float Two = math.DotProduct(math.CrossProduct(math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i + 1)),
					math.SubVec(Q, objVertVecContainer.at(i + 1))), tempNormal); // 20operations
				float Three = math.DotProduct(math.CrossProduct(math.SubVec(objVertVecContainer.at(i), objVertVecContainer.at(i + 2)),
					math.SubVec(Q, objVertVecContainer.at(i + 2))), tempNormal); // 20 operations

				if (One >= 0 && Two >= 0 && Three >= 0) //  6 operations  checking all vertices to see if the point is really inside the triangle 
				{



					//std::cout << "\n The intersection point Q " << "(" << Q << ")" << " is inside the triangle\n"
					//	<< "(" << objVertVecContainer.at(i) << "), \n"
					//	<< "(" << objVertVecContainer.at(i + 1) << "), \n"
					//	<< "(" << objVertVecContainer.at(i + 2) << ")" << std::endl;
					//std::cout << "From the ray point: (" << rayContainer.at(j) << ")" << std::endl;

					totalIntersections++;
				} // 112 operations

			}
		});
	}

		
	std::cout << "\ntotal intersection points using bruteforce in the the model : " << totalIntersections << std::endl;
}



void BruteRayIntersection::BarycentricRayIntersection() 
{
	Vector3 d(1, 0, 0);
	int totalIntersections = 0;

	for (unsigned int i = 0; i < objVertVecContainer.size(); i+= 3) // i = A, i + 1 = B , i + 2 = C
	{
	
		Vector3 tempNormal = math.CrossProduct(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i))
			, math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i))); // 12 operations * (objVertVecContainer.size() / 3)
		tempNormal = math.Normalise(tempNormal); // 8 operations * (objVertVecContainer.size() / 3)
		float k = math.DotProduct(tempNormal, objVertVecContainer.at(i));


		Vector3 v = math.SubVec(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)), 
			math.Projection(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i + 2)), math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)))); // 24 operations * (objVertVecContainer.size() / 3)

		Vector3 vb = math.SubVec(math.SubVec(objVertVecContainer.at(i), objVertVecContainer.at(i + 1)),
			math.Projection(math.SubVec(objVertVecContainer.at(i + 2), objVertVecContainer.at(i)), math.SubVec(objVertVecContainer.at(i), objVertVecContainer.at(i + 1)))); // // 24 operations * (objVertVecContainer.size() / 3)

		Vector3 vc = math.SubVec(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i + 2)),
			math.Projection(math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)), math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i + 2)))); // 24 operations * (objVertVecContainer.size() / 3)




		for(unsigned int j = 0; j < rayContainer.size(); j++)
		{

			float t = (k - math.DotProduct(tempNormal, rayContainer.at(j))) / math.DotProduct(tempNormal, d); // 12 operations * rayContainer.size()
			if (t > 0) // 1 operation * rayContainer.size()
			{
				Vector3 Q = math.AddVec(rayContainer.at(j), math.MulVecByFloat(d, t)); // 6 operations * rayContainer.size()



				if (Q.y >= 0.0f) // 1 operation * rayContainer.size()
				{
					float a = 1 - ((math.DotProduct(v, math.SubVec(Q, objVertVecContainer.at(i)))) /
						math.DotProduct(v, math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i)))); // 18 operations * rayContainer.size() 
					float b = 1 - ((math.DotProduct(vb, math.SubVec(Q, objVertVecContainer.at(i + 1)))) /
						math.DotProduct(vb, math.SubVec(objVertVecContainer.at(i), objVertVecContainer.at(i + 1)))); // 18 operations * rayContainer.size()

					float c = 1 - ((math.DotProduct(vc, math.SubVec(Q, objVertVecContainer.at(i + 2)))) /
						math.DotProduct(vc, math.SubVec(objVertVecContainer.at(i + 1), objVertVecContainer.at(i + 2)))); // 18 operations * rayContainer.size()



					if (a <= 1 && a >= 0 && b <= 1 && b >= 0 && c <= 1 && c >= 0) // 12 operations * rayContainer.size() / amount of times the if statement has been true 

					{

						//std::cout << "\n The intersection point Q " << "(" << Q << ")" << " is inside the triangle\n"
						//	<< "(" << objVertVecContainer.at(i) << "), \n"
						//	<< "(" << objVertVecContainer.at(i + 1) << "), \n"
						//	<< "(" << objVertVecContainer.at(i + 2) << ")" << std::endl;
						//std::cout << "From the ray point: (" << rayContainer.at(j) << ")" << std::endl;

						totalIntersections++;
					}
				}
			}



			 // 176 operations
		}

	}
	std::cout << "\ntotal intersection points using Barycentric in the the model : " << totalIntersections << std::endl;
}



