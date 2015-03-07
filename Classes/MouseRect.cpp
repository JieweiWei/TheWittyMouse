//
//  MouseRect.cpp
//  WriteMouseTest
//
//  Created by wc on 15/3/4.
//
//

#include "MouseRect.h"


bool MouseRect::init() {
    if (!Sprite::init())
        return false;
    
    auto rect = Rect();
    auto size = Director::getInstance()->getVisibleSize();
    auto mouse = Sprite::createWithSpriteFrameName("run00.png");
    auto mouseSize = mouse->getContentSize();
    rect.setRect(size.width / 6, size.height / 4.5, mouseSize.width * 2, mouseSize.height * 2);
    this->setPosition(size.width / 4, size.height / 3);
    this->setVisible(false);
    this->setTextureRect(rect);
    
    return true;
}

vector<double> MouseRect::findCrash(Vector<Cucurbit*> cucurbitsToFallDown) {
    vector<double> result(3);
    for (auto cucrbit : cucurbitsToFallDown) {
        if (this->getBoundingBox().intersectsRect(cucrbit->getBoundingBox())) {
            result[0] = 1;
            datas.push_back(vector<double>{1, 0, 0, 1, 0});
            net.Training(datas);
            auto res = net.getOneByInput(vector<double>{1, 0, 0, 1, 0});
            result[1] = res[0];
            result[2] = res[1];
            return result;
        }
    }
    result[0] = 0;
    return result;
}

void MouseRect::addData(vector<double> &data) {
    datas.push_back(data);
}