#include <SFML/Graphics.hpp>
#include "animation.h"
#include "util.h"

// cal::Animation::Animation(
// 	float duration,
// 	Transform from,
// 	Transform to,
// 	float (*easing)(float)
// ) {
// 	duration=duration;
// 	from=from;
// 	to=to;
// 	easing=easing;
// 	time=0.0f;
// }

void cal::Animation::restart() {
	clock.restart();
}

cal::Transform cal::Animation::getCurrentTransform() {
	time=easing(clock.getElapsedTime().asSeconds()/duration);
	if (time>=1) {
		return to;
	} else if (time<=0) {
		return from;
	}
	return cal::lerp(from,to,time);
}