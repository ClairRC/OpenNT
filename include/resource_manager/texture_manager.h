#ifndef texture_manager_h
#define texture_manager_h

#include <iostream>
#include <unordered_map>

#include "components/texture_component.h"


namespace ResourceManager {
	/*
	* This class is going to be responsible for getting the OpenGL texture IDs.
	* The component class holds the components, this holds the actual textures that 
	* need to be binded.
	* 
	* So the component goes to component manager, then this gets the component for the information and loads it.
	*/

	//TODO: Add uhhh spritsheets for animations. Just gotta figure out how to organize that.
	class TextureManager {
	private:
		//Constructor
		TextureManager();

		//No copy or move constructors because singleton
		TextureManager(const TextureManager& copy) = delete; 
		TextureManager(TextureManager&& move) noexcept = delete;

		//Holds the data that the texture needs
		struct imageData {
			//I'm not sure if I'll ever need these top 3 outside of the initialization,
			//But I will keep them here in case
			int width;
			int height;
			int nrChannels;

			unsigned int id;
		};


		//Map to store which entity has which texture
		//I need to have a better way to allow multiple entities to use the same texture without dealing with this.
		//It's fine though because I tootally get the whole abstraction thing because even if i change the storage
		//And what data I need and the way that I handle it, the systems of this engine don't need to care. That's so cool.
		std::unordered_map<std::string, imageData> textures;
		static TextureManager* instance; //Instance of the class because this is a singleton class
		std::string textureFolderPath; //Path to texture folder
		
	public: 
		~TextureManager(); //Destructor

		static TextureManager* getTextureManager(); //Returns singleton instance
		unsigned int getTexture(Resources::TextureComponent);
		std::string getTextureFolderPath();
		void setTextureFolderPath(std::string path);
	};
}

#endif 