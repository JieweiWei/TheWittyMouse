//
//  Pause.cpp
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#include "Pause.h"
#include "Util.h"
#include "ActionController.h"
#include "MenuScene.h"

bool Pause::init() {
	if (!Layer::init())
		return false;

	// Create pause button
	pauseButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("pause-btn.png"), NULL, NULL,
		CC_CALLBACK_1(Pause::pause, this));
	continueButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("continue.png"), NULL, NULL,
		CC_CALLBACK_1(Pause::pause, this));
	auto menuPause = Menu::create(pauseButton, NULL);
	auto menuContinue = Menu::create(continueButton, NULL);

	auto size = Director::getInstance()->getVisibleSize();
	// Set menu position
	menuPause->setPosition(Vec2(pauseButton->getContentSize().width, size.height / 12));
	menuContinue->setPosition(Vec2(pauseButton->getContentSize().width, size.height / 12));
	continueButton->setVisible(false);
	this->addChild(menuPause);
	this->addChild(menuContinue);
	this->setTag(PAUSETAG);

	popup = Popup::create();
	popup->addTitle(Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "PAUSE"));
	mainSceneMenu = MenuItemImage::create(
		"images/CloseNormal.png",
		"images/CloseSelected.png",
		this,
		menu_selector(Pause::mainMenu));
	popup->addMenuInScreenFringe(0, mainSceneMenu, NULL);

	IQLabel = MenuItemLabel::create(Label::createWithBMFont("fonts/futura-48.fnt",
		String::createWithFormat("IQ: %d", Mouse::getIQ())->getCString()));
	LifeLabel = MenuItemLabel::create(Label::createWithBMFont("fonts/futura-48.fnt",
		String::createWithFormat("Life: %d", Mouse::getLife())->getCString()));
	popup->addLabel(0, IQLabel, LifeLabel, NULL);

	this->addChild(popup);

	Util::setPauseMenuWidth(pauseButton->getContentSize().width);
	return true;
}

void Pause::pause(Ref* sender) {
	this->toggleButton(pauseButton->isVisible());
}

void Pause::resume(Ref* sender) {
	this->toggleButton(pauseButton->isVisible());
}

void Pause::mainMenu(Ref* sender) {
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void Pause::toggleButton(bool flag) {
	// The control of the music and action
	update();
	ActionController::control(flag);
	if (flag) {
		pauseButton->setVisible(false);
		continueButton->setVisible(true);
		popup->display();
	}
	else {
		pauseButton->setVisible(true);
		continueButton->setVisible(false);
		popup->hide();
	}
}

Size Pause::getSizeOfMenu() {
	return pauseButton->getContentSize();
}

void Pause::update() {
	IQLabel->setString(String::createWithFormat("IQ: %d", Mouse::getIQ())->getCString());
	LifeLabel->setString(String::createWithFormat("Life: %d", Mouse::getLife())->getCString());
}