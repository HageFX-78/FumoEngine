#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <iostream>
#include "texture_utils.h"

class Texture
{
public:
	static Texture* createResource(std::string path)
	{
		unsigned int id = loadTexture(path);

		if (id > 0)
		{
			Texture* tex = new Texture(path, id);
			return tex;
		}

		return 0;
	}

	void bind()
	{
		glBindTexture(GL_TEXTURE_2D, texture_ID);
	}

	void increaseRefCount() { refCount++; }
	void decreaseRefCount() { refCount--; }

	const int getRefCount() const {
		return refCount;
	}

	std::string getTextureName() const {
		return name;
	}
private:
	Texture(std::string path, unsigned int id) : name(path), texture_ID(id) { }

	std::string name;
	unsigned int texture_ID;
	unsigned int refCount = 0;
};