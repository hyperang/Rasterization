#include <iostream>
#include <stdlib.h>

#include "transtest.h"

int main() 
{
	point p1 = point(2.4, 1.0, -5.0, 1.0);
	point p2 = point(-2.4, 1.0, 5.0, 1.0);
	point p3 = point(1.0, 1.0, 3.0, 1.0);
	triangle t1 = triangle(p1, p2, p3);

	matrix4 mati = { vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1) };
	std::cout << mati << std::endl;

	matrix4 mata = { vec4(1, 5, 4, 2), vec4(0, 1, 0, 0), vec4(0, 3, 1, 0), vec4(3, 2, 0, 1) };
	matrix4 matb = { vec4(-1, 0, 1, 0), vec4(2, 1, -1, 2), vec4(7, 0, -1, 0), vec4(1, 5, 2, 1) };

	//matrix4 matc = matrixMulti(mata, matb);
	matrix4 matc = matrixMulti({ mata, matb });

	std::cout << matc << std::endl;

	t1.transform(matc);
	std::cout << t1 << std::endl;

	system("pause");
	return 0;
}