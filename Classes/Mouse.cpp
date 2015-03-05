//
//  Mouse.cpp
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#include "Mouse.h"
#include "Util.h"
#include "AnimationUtils.h"

int Mouse::IQ = 0;
int Mouse::life = 10;

Mouse* Mouse::createMouse() {
    auto mouse = new Mouse();
    if (mouse && mouse->init()) {
        mouse->autorelease();
        return mouse;
    }
    CC_SAFE_DELETE(mouse);
    return nullptr;
}

bool Mouse::init() {
    if(!Sprite::init())
        return false;
    
    auto size = Director::getInstance()->getVisibleSize();
    this->createWithSpriteFrameName("run00.png");
    this->setTag(MOUSETAG);
    this->setPosition(Vec2(size.width / 6, size.height / 4.5));
    
    return true;
}

void Mouse::run() {
    Util::setDif(6);
    auto preAction = this->getActionByTag(MOUSETAG);
    if (!preAction)
        this->stopAction(preAction);
    
	this->runAction(Animate::create(AnimationUtils::createWithName("run", 0.1f, -1)));
}

void Mouse::jump() {
    Util::setDif(8);
    auto preAction = this->getActionByTag(MOUSETAG);
    if (!preAction)
        this->stopAction(preAction);
    
	this->runAction(Animate::create(AnimationUtils::createWithName("jump", 0.1f, -1)));
}

void Mouse::fall() {
    Util::setDif(0);
    auto preAction = this->getActionByTag(MOUSETAG);
    if (!preAction)
        this->stopAction(preAction);
    
	this->runAction(Animate::create(AnimationUtils::createWithName("fall", 0.1f, -1)));
}

int Mouse::getIQ() {
    return IQ;
}

void Mouse::setIQ(int IQ_) {
    IQ = IQ_;
}

int Mouse::getLife() {
    return life;
}

void Mouse::setLife(int life_) {
    life = life_;
}