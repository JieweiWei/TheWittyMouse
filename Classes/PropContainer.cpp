//
//  PropContainer.cpp
//  WittedMouse
//
//  Created by wc on 15/2/26.
//
//

#include "PropContainer.h"

bool PropContainer::initPropContainer(Attribute attribute) {
    if (!Sprite::init())
        return false;
    
    auto size = Director::getInstance()->getVisibleSize();
    numLabel = Label::createWithBMFont("fonts/font-issue1343.fnt", "0");
    propNum = 0;
    this->addChild(numLabel);
    switch(attribute) {
        case FERTILIZER:
            this->setSpriteFrame("chemical-fertilizer.png");
            this->setPosition(this->getContentSize().width / 2,
                              size.height / 4.5 + this->getContentSize().height / 2);
            break;
        case BLOCK:
            this->setSpriteFrame("magnet.png");
            this->setPosition(this->getContentSize().width / 2,
                              size.height / 4.5 + 4 * this->getContentSize().height / 2);
            break;
        default:
            this->setSpriteFrame("shovel.png");
            this->setPosition(this->getContentSize().width / 2,
                              size.height / 4.5 + 8 * this->getContentSize().height / 2);
            break;
    }
    numLabel->setPosition(this->getContentSize().width + 20, this->getContentSize().height / 2);
    
    return true;
}

PropContainer *PropContainer::createPropContainer(Attribute attribute) {
    auto container = new PropContainer();
    if (container && container->initPropContainer(attribute)) {
        container->autorelease();
        return container;
    }
    CC_SAFE_DELETE(container);
    return nullptr;
}

void PropContainer::addAProp() {
    propNum++;
}

void PropContainer::deleteAProp() {
    if (propNum > 0)
        propNum--;
}

bool PropContainer::isEmpty() {
    return propNum == 0;
}

void PropContainer::updateContainer() {
    String *propNumString = String::createWithFormat("%d",  propNum);
    numLabel->setString(propNumString->getCString());
}