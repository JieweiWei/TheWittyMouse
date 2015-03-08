#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "AnimationUtils.h"
#include "I18N.h"
#include "SimpleAudioEngine.h"

Scene* MenuScene::createScene() {
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init() {
	if (!Layer::init()) {
		return false;
	}
	_isBtnListShow = false;
	_isDialogShow = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgmusic.mp3", true);
	loadUIAndSetListner();
	
	return true;
}

void MenuScene::loadUIAndSetListner() {
	auto rootNode = CSLoader::createNode("Menu/MenuScene.csb");
	this->addChild(rootNode);

	auto singleMode = (Button*)(rootNode->getChildByName("beginBtn"));
	singleMode->setTitleText(I18N::getInstance()->getString("singleMode"));
	singleMode->addTouchEventListener(this, toucheventselector(MenuScene::singleModeEvent));

	auto battle = (Button*)(rootNode->getChildByName("battleBtn"));
	battle->setTitleText(I18N::getInstance()->getString("battle"));

	//auto mouse = (Sprite*)(rootNode->getChildByName("mouse"));
	//mouse->runAction(Animate::create(AnimationUtils::createWithName("run", 0.1f, -1)));
	
	_itemList = rootNode->getChildByName("btnList");
	_dialog = rootNode->getChildByName("dialog");

	auto showOrHideBtn = (Button*)(_itemList->getChildByName("showBtn"));
	showOrHideBtn->addTouchEventListener(this, toucheventselector(MenuScene::showOrHideEvent));

	auto helpBtn = (Button*)(_itemList->getChildByName("helpBtn"));
	helpBtn->addTouchEventListener(this, toucheventselector(MenuScene::showHelp));

	auto infoBtn = (Button*)(_itemList->getChildByName("infoBtn"));
	infoBtn->addTouchEventListener(this, toucheventselector(MenuScene::showInfo));

	auto settingBtn = (Button*)(_itemList->getChildByName("settingBtn"));
	settingBtn->addTouchEventListener(this, toucheventselector(MenuScene::showSetting));

	auto developerBtn = (Button*)(_itemList->getChildByName("developerBtn"));
	developerBtn->addTouchEventListener(this, toucheventselector(MenuScene::showDeveloper));

	auto closeDialog = (Button*)(_dialog->getChildByName("closeDialog"));
	closeDialog->addTouchEventListener(this, toucheventselector(MenuScene::closeDialog));
}

void MenuScene::singleModeEvent(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Director::getInstance()->replaceScene(MainScene::createScene());
	}
}

void MenuScene::showOrHideEvent(Ref* sender, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		auto showOrHideBtn = (Button*)sender;
		Point curPoint = _itemList->getPosition();
		_isBtnListShow = !_isBtnListShow;
		MoveBy* moveBy = MoveBy::create(0.35f, Point(0, 245 * (_isBtnListShow ? 1 : -1)));
		showOrHideBtn->setFlippedY(_isBtnListShow);
		_itemList->runAction(moveBy);
	}
}


void MenuScene::showHelp(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("helpTitle"), true);
	}
}

void MenuScene::showInfo(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("infoTitle"), true);
	}
}

void MenuScene::showSetting(Ref* sender, TouchEventType type) {
	auto settingBtn = (Button*)sender;
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("settingTitle"), true);
	}
}

void MenuScene::showDeveloper(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("developerTitle"), true);
	}
}

void MenuScene::closeDialog(Ref* sender, TouchEventType type) {
	auto closeBtn = (Button*)sender;
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		closeBtn->setScale(1);
		toggleDialogAndSetTitle("", false);
	}
	else if (type == TouchEventType::TOUCH_EVENT_BEGAN) {
		closeBtn->setScale(0.9);
	}
	else {
		closeBtn->setScale(1);
	}
}

void MenuScene::toggleDialogAndSetTitle(const char* title, bool _isShow) {
	// _isDialogShow表示dialog的状态,_isShow表示是否想要弹出
	if (_isShow ^ _isDialogShow) {
		_isDialogShow = !_isDialogShow;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		_dialog->runAction(MoveBy::create(0.4f, Point(0, (_isShow ? -1 : 1) * visibleSize.height)));
	}
	Text* titleText = (Text*)_dialog->getChildByName("title")->getChildByName("titleText");
	titleText->setText(title);
}