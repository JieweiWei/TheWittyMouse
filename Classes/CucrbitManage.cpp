//
//  CucrbitManage.cpp
//  WittedMouse
//
//  Created by wc on 15/2/26.
//
//

#include "CucrbitManage.h"
#include "GameOver.h"
#include "Util.h"


bool CucrbitManage::init() {
    if (!Sprite::init())
        return false;
    
    cucurbitsToFallDown.clear();
    
    size = Director::getInstance()->getVisibleSize();
    this->setPosition(0, 0);
    return true;
}

void CucrbitManage::moveCucrbit(float dt) {
    float dif;
    if (Util::getDif() == -1)
        dif = 6;
    else
        dif = Util::getDif();
    // Move the cucrbits
    if (cucurbits.size() > 0) {
        Vector<Cucurbit*> tempVector;
        for (int i = 0; i != cucurbits.size(); ++i) {
            auto cucrbit = cucurbits.at(i);
            cucrbit->setPositionX(cucrbit->getPositionX() - dif);
            if (cucrbit->getPositionX() <  -10) {
                cucrbit->removeFromParentAndCleanup(true);
                tempVector.pushBack(cucrbit);
            }
        }
        
        for (auto cucrbit : tempVector) {
            if (!cucrbit->getIsCut())
                cucurbits.eraseObject(cucrbit);
        }
    }
}

void CucrbitManage::cucurbitProcess(float dt) {
    for (auto cucrbit : cucurbits) {
        if (!cucrbit->getIsCut()) {
            if (cucrbit->grow()) {
                cucurbitsToFallDown.pushBack(cucrbit);
                cucrbit->setIsCut(true);
                cucrbitFallDown(cucrbit);
            }
        }
    }
}

void CucrbitManage::initCucurbit() {
    for (int i = 0; i != 4; ++i) {
        auto cucrbit = Cucurbit::createCucurbit();
        this->addChild(cucrbit);
        cucurbits.pushBack(cucrbit);
    }
}

void CucrbitManage::addCucurbit(float dt) {
    if (cucurbits.size() < 8) {
        auto cucrbit = Cucurbit::createCucurbit();
        cucrbit->setPositionX(cucrbit->getPositionX() + (size.width));
        this->addChild(cucrbit);
        cucurbits.pushBack(cucrbit);
    }
}

void CucrbitManage::cucrbitFallDown(Cucurbit *cucrbit) {
    if (cucrbit) {
        auto moveTo = MoveTo::create(1, Vec2(cucrbit->getPositionX(), size.height / 10));
        cucrbit->runAction(moveTo);
    }
}

void CucrbitManage::removeFallDownCucrbit(Mouse* mouse, HUDLayer *hudLayer) {
    if (cucurbitsToFallDown.size() != 0) {
        Vector<Cucurbit*> tempVector;
        for (auto cucrbitTemp : cucurbitsToFallDown) {
            if (cucrbitTemp->getBoundingBox().intersectsRect(mouse->getBoundingBox())) {
                // update iq
                if (cucrbitTemp->getType() < 2) {
                    Mouse::setIQ(Mouse::getIQ() + 1);
                    if (Mouse::getLife() > 1) {
                        Mouse::setLife(Mouse::getLife() - 1);
                    } else {
                        Mouse::setLife(Mouse::getLife() - 1);
                        auto gameOver = (GameOver*)Director::getInstance()->getRunningScene()->getChildByTag(GAMEOVERTAG);
                        gameOver->gameOver();
                    }
                } else {
                    if ( Mouse::getLife() < 10)
                        Mouse::setLife(Mouse::getLife() + 1);
                }
                // HUD layer
                hudLayer->updateIQ();
                
                cucrbitTemp->removeFromParentAndCleanup(true);
                cucurbits.eraseObject(cucrbitTemp);
                tempVector.pushBack(cucrbitTemp);
                
            } else if ((cucrbitTemp->getPositionY() -
                        cucrbitTemp->getContentSize().height) <= size.height / 8) {
                cucrbitTemp->removeFromParentAndCleanup(true);
                cucurbits.eraseObject(cucrbitTemp);
                tempVector.pushBack(cucrbitTemp);
            }
        }
        
        for (auto cucrbitTemp : tempVector) {
            cucurbitsToFallDown.eraseObject(cucrbitTemp);
        }
    }
}

bool CucrbitManage::cucrbitTouchEvent(Touch *touch, Event *event) {
    // Only the first cucrbit that been incised need to fall down
    Vec2 touchLocation = touch->getLocation();
    for (auto cucrbit : cucurbits) {
        Vec2 cucrbitLocation = cucrbit->getPosition();
        Size sizeOfCucrbit = cucrbit->getContentSize();
        if (touchLocation.x >= cucrbitLocation.x && touchLocation.x <= (cucrbitLocation.x + sizeOfCucrbit.width)) {
            if (touchLocation.y <= cucrbitLocation.y && touchLocation.y >=
                (cucrbitLocation.y - sizeOfCucrbit.height / 2)) {
                cucurbitsToFallDown.pushBack(cucrbit);
                cucrbit->setIsCut(true);
                cucrbitFallDown(cucrbit);
                return true;
            }
        }
    }
    return false;
}