#pragma once
#include <string>
#include <map>
#include <iostream>

class Texture;


class ResourceAllocator
{
public:
	template <typename ResourceType>
	static ResourceType* allocateResource(std::string& path) {

		ResourceType* existingResource = findResource<ResourceType>(path);

		if (existingResource)
		{
			existingResource->increaseRefCount();
			//std::cout << existingResource->getRefCount() << " is ref count for this" << existingResource->getTextureName() << std::endl;
			return existingResource;

		}
		else
		{
			ResourceType* newResrc = ResourceType::createResource(path);
			newResrc->increaseRefCount();
			resourceMap[path] = newResrc;
			//std::cout << resource->getRefCount() << " is ref count for this" << resource->getTextureName() << std::endl;
			return newResrc;
		}
	}

	template <typename ResourceType>
	static void releaseResource(ResourceType* resource) {

		if (resource)
		{
			resource->decreaseRefCount();
			if (resource->getRefCount() <= 0)
			{
				removeResource<ResourceType>(resource);
				delete resource;
			}
		}
	}
private:

	static std::map<std::string, void*> resourceMap;//Template causes some issues in declaring in cpp

	template <typename ResourceType>
	static ResourceType* findResource(std::string& path) {
		auto it = resourceMap.find(path);
		if (it != resourceMap.end()) {
			return static_cast<ResourceType*>(it->second);
		}
		return nullptr;
	}

	template <typename ResourceType>
	static void removeResource(ResourceType* resource) {

		auto it = resourceMap.begin();
		while (it != resourceMap.end()) {
			if (it->second == resource) {
				resourceMap.erase(it++);
				break;
			}
			it++;
		}

	}
};

