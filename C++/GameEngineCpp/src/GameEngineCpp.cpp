// GameEngineCpp.cpp : Defines the entry point for the application.
//
#include <numbers>
#include "GameEngineCpp.h"

using namespace std;
using namespace GameEngine::Math;

int main()
{
	Vector3 vec1(0, 0, 4);
	double angle = std::numbers::pi / 2;
	Vector3 vec2 = Matrix3x3::Rotate(angle, 0, angle) * vec1;

	cout << "Vector3(" << vec1.x << ", "
		<< vec1.y << ", " << vec1.z << ")." << endl;
	cout << "Vector3(" << vec2.x << ", "
		<< vec2.y << ", " << vec2.z << ")." << endl;

	return 0;
}
