// GameEngineCpp.cpp : Defines the entry point for the application.
//

#include "GameEngineCpp.h"

using namespace std;
using namespace math;

int main()
{
	Vector3 vec1(4, 4, 4);
	Vector3 vec5 = vec1.normalized();
	vec1 /= 2;
	Vector3 vec2 = Vector3(1, 1, 1);
	Vector3 vec3 = Vector3(5, 5, 5);
	Vector3 vec4 = vec1 + vec2 * 10 - vec3 + 4;
	double distance = Vector3::distance(vec1, *(new Vector3(0, 0, 0)));

	cout << "Vector3(" << vec1.x << ", "
		<< vec1.y << ", " << vec1.z << ")." << endl;
	cout << "Vector3(" << vec2.x << ", "
		<< vec2.y << ", " << vec2.z << ")." << endl;
	cout << "Vector3(" << vec3.x << ", "
		<< vec3.y << ", " << vec3.z << ").\n" << endl;
	cout << "Vector3(" << vec4.x << ", "
		<< vec4.y << ", " << vec4.z << ")." << endl;
	cout << "Vector3(" << vec5.x << ", "
		<< vec5.y << ", " << vec5.z << ")." << endl;
	cout << "distance: " << distance << endl;

	return 0;
}
