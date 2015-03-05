//
//  PropManager.cpp
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#include "PropManager.h"
#include "Prop.h"

bool PropManager::init() {
    if (!Sprite::init())
        return false;
    
    fertilizers = PropContainer::createPropContainer(FERTILIZER);
    block = PropContainer::createPropContainer(BLOCK);
    magent = PropContainer::createPropContainer(MAGNET);
    this->addChild(fertilizers);
    this->addChild(block);
    this->addChild(magent);
    
    this->setPosition(0, 0);
    
    prop = nullptr;
    size = Director::getInstance()->getVisibleSize();

    return true;
}

void PropManager::addProp(Attribute attribute) {
    switch (attribute) {
        case FERTILIZER:
            this->fertilizers->addAProp();
            break;
        case BLOCK:
            this->block->addAProp();
            break;
        default:
            this->magent->addAProp();
            break;
    }
    update();
}

void PropManager::deleteProp(Attribute attribute) {
    switch (attribute) {
        case FERTILIZER:
            this->fertilizers->deleteAProp();
            break;
        case BLOCK:
            this->block->deleteAProp();
            break;
        default:
            this->magent->deleteAProp();
            break;
    }
    update();
}

void PropManager::update() {
    this->fertilizers->updateContainer();
    this->block->updateContainer();
    this->magent->updateContainer();
}

void PropManager::propTouchEvent(Touch *touch, Event *event) {
    if (prop) {
        auto touchLocation = touch->getLocation();
        auto propLocation = prop->getPosition();
        auto propSize = prop->getContentSize();
        if (propLocation.x <= touchLocation.x && propLocation.x + propSize.width >= touchLocation.x) {
            if ( propLocation.y <= touchLocation.y && propLocation.y + propSize.height >= touchLocation.y) {
                this->addProp(prop->getAttribute());
                this->update();
                
                this->removeChild(prop, true);
                prop = nullptr;
            }
        }
    }
}

void PropManager::propCreator(float dt) {
    prop = Prop::create();
    auto jumpto = JumpTo::create(3, Vec2(size.width + this->getContentSize().width + 10, size.height / 3), 120, 4);
    auto repeat = RepeatForever::create(
                                        Sequence::create(
                                                         FadeIn::create(2),
                                                         FadeOut::create(2),
                                                         nullptr)
                                        );
    auto cf = CallFunc::create(CC_CALLBACK_0(PropManager::removeProp, this, prop));
    auto seq = Sequence::create(jumpto, repeat, cf, NULL);
    prop->runAction(seq);

    this->addChild(prop);
}

void PropManager::removeProp(Prop *p) {
    if (p && p->getPositionX() >= size.width + this->getContentSize().width + 5) {
        p->removeFromParentAndCleanup(true);
        prop = nullptr;
    }
}