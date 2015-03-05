//
//  Prop.cpp
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#include "Prop.h"
#include "Util.h"

bool Prop::init() {
    if (!Sprite::init())
        return true;
    
    // Get the prop randomly
    auto typeOfProp = (int)(rand() % 3);
    
    switch(typeOfProp) {
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
    this->setScale(1, 1);
    size = Director::getInstance()->getVisibleSize();
    this->setAnchorPoint(Vec2(1, 0));
    this->setPosition(Vec2(0, size.height / 3));
    this->setTag(PROPTAG);
    
    return true;
}

Attribute Prop::getAttribute() {
    return attribute;
}

