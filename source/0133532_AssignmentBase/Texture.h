#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <iostream>
#include "texture_utils.h"

namespace FumoEngine
{
	class Texture
	{
	public:
		static Texture* createResource(std::string path)
		{
			TextureData textureData = loadTexture(path);
			unsigned int id = textureData.handle;

			if (id > 0)
			{
				Texture* tex = new Texture(path, id, textureData.width, textureData.height);
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

		int getTextureWidth() const {
			return textureWidth;
		}
		int getTextureHeight() const {
			return textureHeight;
		}
	private:
		Texture(std::string path, unsigned int id, int nW, int nH) : name(path), texture_ID(id), textureWidth(nW), textureHeight(nH) { }

		std::string name;
		unsigned int texture_ID;
		unsigned int refCount = 0;

		int textureWidth;
		int textureHeight;

	};
}
