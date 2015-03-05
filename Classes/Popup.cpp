//
//  Popup1.cpp
//  WittedMouse
//
//  Created by wc on 15/2/28.
//
//

#include "Popup.h"

bool Popup::init() {
	if (!Sprite::init())
		return false;

	size = Director::getInstance()->getVisibleSize();

	bg = Sprite::create("images/popup.png");
	bg->setScale(1, 0.5);
	bg->setOpacity(120);
	bg->setPosition(size.width / 2, size.height / 2);
	this->addChild(bg);

	title = NULL;

	// 设置当前弹出框大小为 0.1 比例
	this->setScale(0.1, 0.1);

	// 默认隐藏弹出框
	this->hide();

	return true;
}

void Popup::addTitle(Label* label) {

	// 默认显示在弹出框中间上部
	label->setPosition(Vec2(size.width / 2,
		size.height / 2 + (bg->getContentSize().height / 4)
		- label->getContentSize().height));
	
	title = label;

	this->addChild(label);
}


void Popup::addLabel(int alignType, MenuItem* item, ...) {
	va_list args;
	va_start(args, item);

	Menu *ret = Menu::createWithItems(item, args);

	va_end(args);

	ret->setPosition(Vec2(size.width / 2, size.height / 2));
	if (alignType == 0)
		ret->alignItemsVerticallyWithPadding(item->getContentSize().height / 3);
	else
		ret->alignItemsHorizontallyWithPadding(item->getContentSize().width / 3);

	this->addChild(ret);
}

void Popup::addMainMenu(int alignType, Vector<MenuItem*> items) {
	Menu *ret = Menu::createWithArray(items);
	ret->setPosition(Vec2(size.width / 2, size.height / 2));
	if (alignType == 0)
		ret->alignItemsVerticallyWithPadding(items.front()->getContentSize().height / 3);
	else
		ret->alignItemsHorizontallyWithPadding(items.front()->getContentSize().width / 3);
	ret->setTag(MAIN_BODY);
	this->addChild(ret);
}

void Popup::removeMainBody() {
	this->removeChildByTag(MAIN_BODY);
}

void Popup::addNodeInMain(Node* node) {
	node->setTag(MAIN_BODY);
	node->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(node);
}

void Popup::display() {
	auto moveTo = MoveTo::create(0.1, Vec2(0, 0));
	auto scaleTo = ScaleTo::create(0.25, 1);
	auto seq = Sequence::create(moveTo, scaleTo, NULL);
	this->runAction(seq);
}

void Popup::hide() {
	auto moveTo = MoveTo::create(0.1, Vec2(0, -size.height));
	auto scaleTo = ScaleTo::create(0.25, 0.1);
	auto seq = Sequence::create(scaleTo, moveTo, NULL);
	this->runAction(seq);
}

void Popup::addMenuInPopupFringe(int alignType, MenuItem *item, ...) {
	va_list args;
	va_start(args, item);

	Menu *ret = Menu::createWithItems(item, args);

	va_end(args);

	ret->setPosition(size.width / 2 + bg->getContentSize().width / 2 - item->getContentSize().width, size.height / 2);

	if (alignType == 0)
		ret->alignItemsVerticallyWithPadding(item->getContentSize().height / 3);
	else
		ret->alignItemsHorizontallyWithPadding(item->getContentSize().width / 3);

	this->addChild(ret);
}

void Popup::addMenuInScreenFringe(int alignType, MenuItem *item, ...) {
	va_list args;
	va_start(args, item);

	Menu *ret = Menu::createWithItems(item, args);

	va_end(args);

	//ret->setPosition(size.width / 2 - item->getContentSize().width, size.height / 2);
	ret->setPosition(size.width - item->getContentSize().width / 2, size.height / 2);

	if (alignType == 0)
		ret->alignItemsVerticallyWithPadding(item->getContentSize().height / 3);
	else
		ret->alignItemsHorizontallyWithPadding(item->getContentSize().width / 3);

	this->addChild(ret);
}

Label* Popup::getTile() {
	return title;
}

void Popup::setTitle(Label* _title) {
	title = _title;
}

void Popup::setTitleText(std::string titleText) {
	if (title != NULL) {
		title->setString(titleText);
	}
}