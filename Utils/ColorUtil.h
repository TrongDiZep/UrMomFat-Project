#pragma once
#include "../Horion/DrawUtils.h"

struct UIColor {
	int r = 255;
	int g = 255;
	int b = 255;
	int a = 255;
	UIColor(int red, int green, int blue, int alpha = 255) {
		this->r = red;
		this->g = green;
		this->b = blue;
		this->a = alpha;
	}
	MC_Color toMC_Color() {
		return MC_Color((float)this->r / 255.f, (float)this->g / 255.f, (float)this->b / 255.f, (float)this->a / 255.f);
	}
	ImColor toImColor() {
		return ImColor(this->r, this->g, this->b, this->a);
	}
	static UIColor WHITE;
	static UIColor GRAY;
};

class ColorUtil {
private:
	unsigned __int64 lastMS = getCurrentMs();
	inline static unsigned __int64 getCurrentMs() {
		FILETIME f;
		GetSystemTimeAsFileTime(&f);
		(unsigned long long)f.dwHighDateTime;
		unsigned __int64 nano = ((unsigned __int64)f.dwHighDateTime << 32LL) + (unsigned __int64)f.dwLowDateTime;
		return (nano - 116444736000000000LL) / 10000;
	}

public:
	static UIColor getRainbowColor(float seconds, float saturation, float brightness, long index) {
		float currentHue = (((getCurrentMs() + index) % (int)(seconds * 1000)) / (float)(seconds * 1000));
		float red, green, blue = 0.0f;
		Utils::ColorConvertHSVtoRGB(currentHue, saturation, brightness, red, green, blue);

		return UIColor((int)(red * 255.f), (int)(green * 255.f), (int)(blue * 255.f), 255);
	}
};