#ifndef vao_h
#define vao_h

#include <iostream>
#include <vector>

namespace Resources {
	//This class will handle VAO resources and management
	class VAO {
	public:
		//Constructor
		VAO() = delete; //Currently dont' want this to be instantiated. Likely will change.
		
		//Soo 6 parameters IS kinda a lot, buuut ultimately I just went for this. It seems to be the best in terms of performance
		//Since I don't have to do extra function calls to create a VBO/EBO, PLUS since this will end up being
		//abstracted in my model class anyway, it's not a huge deal I think... I don't love this solution, 
		//but it is the most efficient I think, and it won't really be too big of a deal at the end of the day anway.
		static unsigned int createVAO (const float* vertices, const int* verticesAttributeSizes, const int* indices,
				const size_t verticesSize, const size_t verticesAttributeSizesSize, const size_t indicesSize);
	};
}

#endif