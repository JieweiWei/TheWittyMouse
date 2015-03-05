//
//  GameOver.cpp
//  WittedMouse
//
//  Created by wc on 15/2/27.
//
//

#include "GameOver.h"
#include "MainScene.h"
#include "Mouse.h"
#include "Util.h"
#include "ActionController.h"
#include "LoadingScene.h"
#include "MenuScene.h"
#include <stdlib.h>
#include <stdio.h>

bool GameOver::init() {
	if (!Layer::init())
		return false;

	popup = Popup::create();
	popup->addTitle(Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "Game Over"));
	mainSceneMenu = MenuItemImage::create(
		"images/CloseNormal.png",
		"images/CloseSelected.png",
		this,
		menu_selector(GameOver::mainMenu));
	replayMenu = MenuItemImage::create(
		"images/CloseNormal.png",
		"images/CloseSelected.png",
		this,
		menu_selector(GameOver::replay));
	IQLabel = MenuItemLabel::create(Label::createWithBMFont("fonts/futura-48.fnt",
		String::createWithFormat("IQ: %d", Mouse::getIQ())->getCString()));
	LifeLabel = MenuItemLabel::create(Label::createWithBMFont("fonts/futura-48.fnt",
		String::createWithFormat("Life: %d", Mouse::getLife())->getCString()));

	popup->addMenuInScreenFringe(0, mainSceneMenu, replayMenu, NULL);
	popup->addLabel(0, IQLabel, LifeLabel, NULL);


	this->addChild(popup);
	this->setVisible(false);

	return true;
}

void GameOver::gameOver() {
	auto pause = Director::getInstance()->getRunningScene()->getChildByTag(PAUSETAG);
	pause->setVisible(false);
	this->setVisible(true);
	update();
	ActionController::control(true);
	popup->display();
}

void GameOver::replay(Ref* sender) {
	LoadingScene::loadData();
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void GameOver::mainMenu(Ref* sender) {
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameOver::update() {
	IQLabel->setString(String::createWithFormat("IQ: %d", Mouse::getIQ())->getCString());
	LifeLabel->setString(String::createWithFormat("Life: %d", Mouse::getLife())->getCString());
}