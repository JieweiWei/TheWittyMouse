//
//  Prop.cpp
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#include "Prop.h"
#include "Util.h"
#include "AnimationUtils.h"
#include <stdlib.h>

bool Prop::init() {
	if (!Sprite::init())
		return true;
	isTouch = false;
	// Get the prop randomly
	auto typeOfProp = (int)(rand() % 3);

	switch (typeOfProp) {
	case 0:
		this->setSpriteFrame("chemical-fertilizer-in-air-bladder.png");
		attribute = FERTILIZER;
		break;
	case 1:
		this->setSpriteFrame("magnet-in-air-bladder.png");
		attribute = BLOCK;
		break;
	default:
		this->setSpriteFrame("shovel-in-air-bladder.png");
		attribute = MAGNET;
		break;
	}
	this->setScale(0.5, 0.5);
	size = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Vec2(0, 2 * size.height / 3));
	this->setTag(PROPTAG);

	return true;
}

Attribute Prop::getAttribute() {
	return attribute;
}

void Prop::run() {
	this->stopAllActions();

	ccBezierConfig bezier2;

	bezier2.controlPoint_1 = Vec2((rand() % 5) * (size.width / 8), (rand() % 2 + 1) * size.height / 3);
	bezier2.controlPoint_2 = Vec2((rand() % 5) * size.width / 4, (rand() % 2 + 1) * size.height / 4);
	bezier2.endPosition = Vec2(size.width + this->getContentSize().width + 25, size.height / 2);
	auto bezierTo1 = BezierTo::create(4, bezier2);

	auto rotate = RotateTo::create(4, 720);

	auto actions = Spawn::create(bezierTo1, rotate, NULL);
	auto cf = CallFunc::create(CC_CALLBACK_0(Prop::removeSelf, this, this));
	auto seq = Sequence::create(actions, cf, NULL);
	this->runAction(seq);
}

void Prop::burst(Vec2 containerPosition, Size containerSize) {
	int h = 1;
	switch (attribute) {
	case FERTILIZER:
		this->setSpriteFrame("chemical-fertilizer.png");
		break;
	case BLOCK:
		this->setSpriteFrame("magnet.png");
		h = 3;
		break;
	default:
		this->setSpriteFrame("shovel.png");
		h = 3;
		break;
	}
	this->stopAllActions();

	fridge = Sprite::createWithSpriteFrameName("progress00.png");
	fridge->runAction(Animate::create(AnimationUtils::createWithName("progress", 0.08f, -1)));
	fridge->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(fridge);
	auto sacleTo1 = ScaleTo::create(0.5, 1.1);
	auto moveTo1 = MoveTo::create(0.5, Vec2(size.width / 2, size.height / 2));
	auto actions1 = Spawn::create(moveTo1, sacleTo1, NULL);
	auto moveTo2 = MoveTo::create(0.5, Vec2(containerPosition.x + containerSize.width / 2,
										 containerPosition.y + containerSize.height / 2));
	auto scaleTo2 = ScaleTo::create(0.5, 0.1);
	auto actions2 = Spawn::create(moveTo2, scaleTo2, NULL);
	auto cf = CallFunc::create(CC_CALLBACK_0(Prop::removeSelf, this, this));
	auto seq = Sequence::create(actions1, actions2, cf, NULL);
	this->runAction(seq);
}

void Prop::removeSelf(Prop *p) {
	p->removeFromParentAndCleanup(true);
}

void  Prop::fertilizerEffectAction() {

}

void  Prop::blockEffectAction() {
}

void  Prop::magentEffectAction() {
}
