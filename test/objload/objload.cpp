#include "objload.h"
#include <stdlib.h>

int main()
{
	std::cout << "main began" << std::endl;

	object *cube = new object("../assets/cube.obj");
	auto f = cube->faceslist;

	// std::cout << f.size() << std::endl;
	auto it = f.begin();
	while(it != f.end())
	{
		auto tmp = *it;
		for(auto i : tmp)
		{
			std::cout << i << ' ';
		}
		it++;
		std::cout << std::endl;
	}

	system("pause");
	return 0;
}