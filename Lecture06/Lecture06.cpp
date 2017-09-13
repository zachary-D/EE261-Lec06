#define PI 3.14159265

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <vector>

using std::string;
using std::cout;
using std::endl;

using std::ofstream;

//Note: General nomenclature: a and b are the horizontal and vertical legs of the triangle (and form the 90* angle), and h is the hypotenuse

int P;	//The perimeter of the triangle (defined later)

double toRadians(double degrees)
{
	return degrees * PI / 180;
}

double toDegrees(double radians)
{
	return radians * 180 / PI;
}

string toString(int input)		//Convert 'input' to a string and return it
{
	string output;
	std::stringstream convert;
	convert << input;
	convert >> output;
	return output;
}

struct rightTriangle
{
	//Knowing the perimieter is 1000, let P = 1000
	//Therefore by combining a^2 + b^2 = h^2 and P = a+b+h we get
	//b = P * (2a-P) / (2 * (a-p) ), and now have the length of b as a fn. of a


	rightTriangle() {}

	rightTriangle(int _a)
	{
		a = _a;
		//Calculate b based on a and the perimiter
		b = (P * ((2 * a) - P)) / (2 * (a - P));

		//Calculate h from a and b
		h = P - (a + b);
	}


	int a;
	int b;
	int h; 

	bool isValid()		//Validates the values of the triangle (no negative sides, perimter adds properly, etc.)
	{
		return (a + b + h == P) &&	//Perimiter = the sum of parts
			(a > 0) &&			//check that the 3 sides are positive
			(b > 0) &&
			(h > 0) &&
			(int)((double)180 - toDegrees(abs(asin((double)b / (double)h)) + abs(acos((double)a / (double)h)))) == 90;
	}

	string print(ofstream &fileOut, bool endLine = true)	//Writes the triangle to the console in text form, as well as returning the data written as a string.  'endLine' determines if endl will be added to the end of the output string
	{
		string output = "a:" + toString(a) + " b:" + toString(b) + " c:" + toString(h);
		cout << output;
		fileOut << output;
		if (endLine) cout << endl; fileOut << endl;
		return output;
	}
};

std::vector<rightTriangle> findTriangles(int perimiter)		//Searches for triangles given 'perimiter'.  Saves triangles validated to 'fileOut'
{
	std::vector<rightTriangle> triangles;

	P = perimiter;
	cout << "Perimiter:" << P << endl;
	
	ofstream fileOut;
	fileOut.open("trianglesFound_P" + toString(perimiter) + ".txt");

	//I is the length of the side the other sides are derived from
	for (int i = 1; i < P; i++)		//Loops over i, increasing by 1 each time, until I>=P
	{
		rightTriangle tri(i);	//Create a triangle with side b = i

		if (tri.isValid())
		{
			triangles.push_back(tri);	//If it is valid, add it to the vector
			tri.print(fileOut);		//And write the info to the console
		}
		else
		{
			//This section is only used for debugging purposes, and we don't need to use it as this is out "final" build

			//Print out a statement as the triangle is invalid

			/*
			cout << "err:";
			tri.print(false);
			cout << " P:" << (tri.a + tri.b + tri.h)
				<< " angle:" << ((double)180 - toDegrees(abs(asin((double)tri.b / (double)tri.h)) + abs(acos((double)tri.a / (double)tri.h)))) << endl;*/
		}
	}
	cout << endl << endl;	//Make some space on the console
	fileOut.close();
	return triangles;
}


int main()
{
	std::vector<rightTriangle> triangles_P1000 = findTriangles(1000);		//Valid triangles with a perimiter of 1000
	std::vector<rightTriangle> triangles_P90000 = findTriangles(90000);		//Valid triangles with a perimiter of 90000
	
	
	cout << "Calculations complete!" << endl;

	std::cin.get();

	return 0;
}