#ifndef vao_manager_h
#define vao_manager_h

#include <iostream>

/*
* Debatably this is the class that will need the most work once I expand this.
* Currently, my plan is to only really support 2.5D-ish games, meaning that the vertex data for
* each entity is going to be, pretty unilaterally, just a square with a texture. However, once I have
* it so that I can import 3D models that have more complex vertex data, I'm going to have to decide
* what the best way to organize the data/VAOs will be. I could sit here and write about my personal woes
* over the whole thing till the cows come home, but it HAS been the single biggest hurdle for me as
* far as resource management goes. At least with my other resources, I know how I WOULD organize it all
* given the time, or at least where to start, but the way the GPU stores data and the whole
* idea of reducing bind calls to the GPU is just so confusing!!!
* I think ideally I'd either keep 1 big VBO or maybe subsets of VBOs to reduce draw calls, but honestly,
* that's the kinda thing that I'll really look into once I try to make a more robust engine. For now I'll go for the
* easier path since that's all that I need for this particular project.
*/

namespace ResourceManager {
	//This is the class that handles managing VAOs
	//The VAO basically defines the structure of the data that we send to the GPU
	//So when we bind a VAO, the GPU knows which section of data to look at for the
	//vertex data, and how that data is ordered, and the size of it, and all that, which it passes
	//to the shaders

	//I think ideally, I'd have it so that when I render something, it would just go through each
	//VAO and render the VAO, and if there is none, then the VAO manager creates it. 
	//Then I'd also have the VAOs be sorted so that it would reduce bind calls, and all that
	//However, since for THIS engine at THIS time, I'm only going to have 2D textures, 
	//the VAO will be the exact same, so I'm going to go with that for now.
	//For now, this class is primarily just for scalability since all this could be done in the render system
	//with minimal performance impact

	class VAOManager {
	private:
		VAOManager();
	
		//No copy and move constructor for singleton
		VAOManager(const VAOManager& copy) = delete;
		VAOManager(VAOManager&& move) = delete;

		static VAOManager* instance;

		//VAO that gets used for every texture. Will improve this
		//Will replace this with a VAO map that gets queried in the getVAO function. Eventually.
		static unsigned int commonVAO; 

	public:
		~VAOManager();

		static VAOManager* getVAOManager();
		unsigned int getVAO();

		//Here is where I'd put a function to create a VAO for a given entity!! :)
	};
}

#endif