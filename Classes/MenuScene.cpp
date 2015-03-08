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
	_isShow = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgmusic.mp3", true);
	loadUIAndSetListner();
	//initPopup();
	
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

	auto showOrHideBtn = (Button*)(_itemList->getChildByName("showBtn"));
	showOrHideBtn->addTouchEventListener(this, toucheventselector(MenuScene::showOrHideEvent));

	/*
	auto developerBtn = (Button*)(_itemList->getChildByName("developer"));
	developerBtn->addTouchEventListener(this, toucheventselector(MenuScene::showDeveloper));

	auto helpBtn = (Button*)(_itemList->getChildByName("help"));
	helpBtn->addTouchEventListener(this, toucheventselector(MenuScene::showHelp));*/

	//auto settingBtn = (Button*)(_itemList->getChildByName("setting"));
	//settingBtn->addTouchEventListener(this, toucheventselector(MenuScene::showSetting));

	/*
	auto infoBtn = (Button*)(_itemList->getChildByName("info"));
	infoBtn->addTouchEventListener(this, toucheventselector(MenuScene::showInfo));*/
}

void MenuScene::initPopup() {
	_popup = Popup::create();
	auto hidePopup = MenuItemImage::create(
		"images/CloseNormal.png",
		"images/CloseSelected.png",
		this,
		menu_selector(MenuScene::hidePopup)
	);
	_popup->addMenuInScreenFringe(0, hidePopup, NULL);
	Label* title = Label::createWithTTF("", "fonts/tangkuijian.ttf", 40.f);
	title->setColor(Color3B(0, 0, 0));
	_popup->addTitle(title);
	this->addChild(_popup);
}

void MenuScene::singleModeEvent(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Director::getInstance()->replaceScene(MainScene::createScene());
	}
}

void MenuScene::showOrHideEvent(Ref* sender, TouchEventType type) {
	auto showOrHideBtn = (Button*)sender;
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		showOrHideBtn->setScale(1);
		Point curPoint = _itemList->getPosition();
		_isShow = !_isShow;
		MoveBy* moveBy = MoveBy::create(0.35f, Point(0, 245 * (_isShow ? 1 : -1)));
		showOrHideBtn->setFlippedY(_isShow);
		_itemList->runAction(moveBy);
	}
	else if (type == TouchEventType::TOUCH_EVENT_BEGAN) {
		showOrHideBtn->setScale(BUTTON_CLICK_SCALE);
	}
}

void MenuScene::showDeveloper(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		_popup->setTitleText(I18N::getInstance()->getString("developerTitle"));
		_popup->removeMainBody();
		Vector<MenuItem*> items;
		Label* label;
		int num = Value(I18N::getInstance()->getString("developerNum")).asInt();
		for (int i = 0; i < num; ++i) {
			label = Label::createWithTTF(I18N::getInstance()->getString("developer"+Value(i).asString()), "fonts/tangkuijian.ttf", 30.f);
			label->setColor(Color3B(0, 0, 0));
			items.pushBack(MenuItemLabel::create(label));
		}
		_popup->addMainMenu(0, items);
		_popup->display();
	}
}

void MenuScene::showHelp(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		_popup->setTitleText(I18N::getInstance()->getString("helpTitle"));
		_popup->removeMainBody();
		auto rootNode = CSLoader::createNode("help.csb");
		auto helpMain = rootNode->getChildByName("helpStep");
		_popup->addNodeInMain(helpMain);
		_popup->display();
	}
}

void MenuScene::showSetting(Ref* sender, TouchEventType type) {
	auto settingBtn = (Button*)sender;
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		settingBtn->setScale(1);
		/*
		_popup->setTitleText(I18N::getInstance()->getString("settingTitle"));
		_popup->removeMainBody();
		auto rootNode = CSLoader::createNode("setting.csb");
		auto settingMain = rootNode->getChildByName("settingMain");
		
		auto musicTitle = (Text*)settingMain->getChildByName("musicTitle");
		musicTitle->setText(I18N::getInstance()->getString("musicTitle"));
		auto soundTitle = (Text*)settingMain->getChildByName("soundTitle");
		soundTitle->setText(I18N::getInstance()->getString("soundTitle"));
		auto languageTitle = (Text*)settingMain->getChildByName("languageTitle");
		languageTitle->setText(I18N::getInstance()->getString("languageTitle"));

		auto musicSelect = (CheckBox*)settingMain->getChildByName("musicSelect");
		

		_popup->addNodeInMain(settingMain);
		_popup->display();*/
	}
	else if (type == TouchEventType::TOUCH_EVENT_BEGAN) {
		settingBtn->setScale(BUTTON_CLICK_SCALE);
	}
}

void MenuScene::showInfo(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		_popup->setTitleText(I18N::getInstance()->getString("infoTitle"));
		_popup->removeMainBody();
		_popup->display();
	}
}

void MenuScene::hidePopup(Ref* sender) {
	_popup->hide();
}