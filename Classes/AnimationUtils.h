#ifndef _ANIMATIONUTIL_H_
#define _ANIMATIONUTIL_H_

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtils {
public:
	static Animation* createWithName(const char* name, float delay, int loops);

	static Animation* createWithNameAndNum(const char* name, int num, float delay, int loops);
};

#endif // !_ANIMATIONUTIL_H_