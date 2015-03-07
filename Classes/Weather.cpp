#include "Weather.h"

bool Weather::init() {
	if (!Sprite::init())
		return false;
	/*
	this->weatherType = WeatherInfo::getInstance()->getTodayWeather();
	ParticleSystem* emitter;
	
	emitter->setStartSize(10);
	emitter->setEndSize(18);
	

	auto p = emitter->getPosition();
	
	emitter->setLife(3.1);

	switch (weatherType) {
	case rain:
		emitter = ParticleRain::create();
		emitter->setPosition(Vec2(p.x, p.y));
		break;
	case sunny:
		break;
	case cloudy:
		break;
	case windy:
		break;
	default: // default style
		break;	
	}
	emitter->retain();
	this->addChild(emitter);
	*/
	return true;
}