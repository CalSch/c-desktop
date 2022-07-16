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
	active=true;
	time=0;
}
void cal::Animation::stop() {
	active=false;
}

void cal::Animation::update(float dt) {
	if (!active) return;
	time+=dt;
	// if (time>duration) {
	// 	time-=dt;
	// 	active=false;
	// }
}

cal::Transform cal::Animation::getCurrentTransform() {
	return cal::lerp(from,to,easing(time/duration));
}