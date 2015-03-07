//
//  Prop.h
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#ifndef __WittedMouse__Prop__
#define __WittedMouse__Prop__

#include "cocos2d.h"

USING_NS_CC;

/**
* Attribute for Prop that used by player
*/
enum Attribute {
	FERTILIZER = 1,
	BLOCK,
	MAGNET,
	LEAF = 4,
	SKATEBOARDSHOES,
	DIMENSIONDOOR
};

/**
* Prop used by player
*/
class Prop : public Sprite {
public:
	bool init();

	/**
	* Gert the attribute of the prop
	*/
	Attribute getAttribute();

	/**
	* 气泡跑过屏幕的动作
	*/
	void run();

	/**
	* 气泡破裂的动作并飘到道具栏的动作
	*/
	void burst(Vec2 containerPosition, Size containerSize);

	/**
	* 将自己移除
	*/
	void removeSelf(Prop *p);

	/**
	* 化肥道具的效果动作
	*/
	void  fertilizerEffectAction();
	/**
	* 铲子道具的效果动作
	*/
	void  blockEffectAction();

	/**
	* 磁铁道具的效果动作
	*/
	void  magentEffectAction();

	CC_SYNTHESIZE(bool, isTouch, IsTouch);

	CREATE_FUNC(Prop);
private:
	Attribute attribute;
	Sprite *fridge;
	Size size;
};

#endif /* defined(__WittedMouse__Prop__) */
