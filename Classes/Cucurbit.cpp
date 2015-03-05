//
//  Cucurbit.cpp
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#include "Cucurbit.h"
#include "Util.h"
#include <time.h>

Cucurbit* Cucurbit::createCucurbit() {
    auto cucurbit = new Cucurbit();
    if (cucurbit && cucurbit->init()) {
        cucurbit->autorelease();
        return cucurbit;
    }
    CC_SAFE_DELETE(cucurbit);
    return nullptr;
}

bool Cucurbit::init() {
    if (!Sprite::init())
        return false;
    
    size = Director::getInstance()->getVisibleSize();
    type = 0;
    
    auto typeOfCucurbit = (int)(rand() % 40);
    auto sizeOfCucurbit = (int)(rand() % 5);
    switch(typeOfCucurbit) {
        case 0:
            this->setSpriteFrame("redHuLuBig.png");
            type = 2;
            break;
        default:
        {
            switch(sizeOfCucurbit) {
                case 0:
                    this->setSpriteFrame("greenHuLuBig.png");
                    type = 1;
                    break;
                default:
                    this->setSpriteFrame("yellowHuLuSmall.png");
                    type = 0;
                    break;
            }
        }
            break;
    }
    growTime = 0;
    isCut = false;
    auto width_ = (int)(rand() % (int)(size.width)) + 10;
    this->setAnchorPoint(Vec2(1, 1));
    this->setPosition(Vec2(width_, size.height - size.height / 20));
    this->setScale(0.8, 0.8);
    this->setTag(CUCRBITTAG);
    return true;
}

bool Cucurbit::grow() {
    growTime++;
    if (type == 0 && growTime == 3) {
        this->setSpriteFrame("greenHuLuBig.png");
        type = 1;
        growTime = 0;
    } else if (type == 1 && growTime == 3) {
        this->setSpriteFrame("redHuLuBig.png");
        type = 2;
        growTime = 0;
        return true;
    } else if(type == 2 && growTime == 1){
        growTime = 0;
        return true;
    }
    return false;
}

