#pragma once
#include <string>
#include <map>
#include <iostream>

namespace FumoEngine
{
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
				std::cout << "<T> [" << path << "] has " << existingResource->getRefCount() << " ref counts" << std::endl;
				return existingResource;

			}
			else
			{
				ResourceType* newResrc = ResourceType::createResource(path);
				newResrc->increaseRefCount();
				std::cout << "<T> [" << path << "] has been initialized with " << newResrc->getRefCount() << " ref counts" << std::endl;
				resourceMap[path] = newResrc;
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
}


