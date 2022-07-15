#pragma once

#include <SFML/Graphics.hpp>

namespace cal {

	struct Transform {
		sf::Vector2f pos;
		sf::Vector2f scale;
		float rotation;
	};


	class Animation {
		public:
			Transform from;
			Transform to;
			float (*easing)(float);
			float time;
			float duration;
			sf::Clock clock;

			Animation(
				float duration,
				Transform from,
				Transform to,
				float (*easing)(float)
			) {
				this->duration=duration;
				this->from=from;
				this->to=to;
				this->easing=easing;
				this->time=0.0f;
			}

			Transform getCurrentTransform();
			void restart();
	};

};