#pragma once

#include <string>
#include "animation.h"

namespace cal {
	std::string string_format(const std::string fmt, ...);

	float lerp(float a, float b, float t);
	Transform lerp(Transform a, Transform b,float t);
}