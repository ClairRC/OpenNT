#include "resource_manager/texture_manager.h"

#include <glad/glad.h>

#include "resource_manager/component_manager.h"

//Define STB_Image
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "stb_image/stb_image.h" //Library for getting image data

//This garbage is not even remotely done or well organized.
//Woopsie daisy!
namespace ResourceManager {
	TextureManager* TextureManager::instance = nullptr;

	TextureManager::TextureManager() { }

	TextureManager::~TextureManager() {
		if (instance != nullptr)
			delete instance;
	}

	TextureManager* TextureManager::getTextureManager() {
		if (instance == nullptr)
			instance = new TextureManager;

		return instance;
	}

	//Returns texture id
	unsigned int TextureManager::getTexture(Resources::TextureComponent comp) {
		//This takes in the COMPONENT because the component has the information for the 
		//texture, so this DOESN'T just take the entity id. i NEEDDDD to have better separation or whatever

		//If the entity has a texture, return it. Otherwise, make one
		if (this->textures.count(comp.name) > 0) {
			return this->textures[comp.name].id;
		}

		//Texture data
		stbi_set_flip_vertically_on_load(true);

		unsigned int textureID;
		int width;
		int height;
		int nrChannels;

		unsigned char* data = stbi_load((this->getTextureFolderPath() + "/" + comp.name).data(), &width, &height, &nrChannels, 4);

		//Send data to GPU and get textureID
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data); //Free data 

		//Put data into the map
		this->textures[comp.name] = TextureManager::imageData{ width, height, nrChannels, textureID };

		return textureID;
	}

	//Returns string containing the path to the texture folder
	std::string TextureManager::getTextureFolderPath() {
		return this->textureFolderPath;
	}

	//Sets the path to the texture folder
	void TextureManager::setTextureFolderPath(std::string path) {
		this->textureFolderPath = path;
	}
}