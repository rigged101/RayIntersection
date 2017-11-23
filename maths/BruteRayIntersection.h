#pragma once

#include <iostream>
#include "OBJ_Loader.h"
#include "Maths.h"
#include <cmath>
#include <time.h>
#include <Vector>
#include <math.h>
#include <memory>
#include <thread>
#include <mutex>
#include <algorithm>
#include <ppl.h>


class BruteRayIntersection
{
public:


	objl::Loader ObjLoader;
	Maths math;


	std::vector<Vector3> objVertVecContainer;
	std::vector<Vector3> rayContainer;
	Vector3 tempContainer;

	
	void RayPointPopulation();
	void MollerBruteForceRayIntersection();
	void SecondBruteForceRayIntersection();
	void BruteForceRayIntersection(); // brute force method
	void ParBruteForceRayIntersection(); // Parallel brute force method
	void BarycentricRayIntersection(); // barricentric method
	void ObjectVerticeConversion();
	void Update();


	BruteRayIntersection();

	~BruteRayIntersection();
};

