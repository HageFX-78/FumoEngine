#pragma once

namespace FumoEngine
{
	/// <summary>
	/// Payload struct type to hold new viewport x y coords and width and height of window.<br>
	/// Viewport x y is depreceated but remains available as an option. Setting viewport with aspect ratio will resize the content itself based
	/// on the width an height of the window.
	/// </summary>
	struct ViewportSizeData {
		int vpx;
		int vpy;
		int width;
		int height;
	};

	/// <summary>
	/// A small class that allows for storing payload in a single void pointer and retrieving it.
	/// </summary>
	class WindowEventData {
	public:
		WindowEventData(void* payload) : payload(payload) {}

		void* getPayload() const {
			return payload;
		}

	private:
		void* payload;
	};
}


