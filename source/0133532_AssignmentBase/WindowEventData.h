#pragma once

struct ViewportSizeData {
	int vpx;
	int vpy;
	int width;
	int height;
};

class WindowEventData {
public:
	WindowEventData(void* payload) : payload(payload) {}

	void* getPayload() const {
		return payload;
	}

private:
	void* payload;
};

