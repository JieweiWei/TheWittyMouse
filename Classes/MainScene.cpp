//
//  MainScene.cpp
//  WittedMouse
//
//  Created by wc on 15/2/14.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Pause.h"
#include "Util.h"
#include "GameOver.h"
#include "CloudManager.h"
#include "Weather.h"

HUDLayer* MainScene::hudLayer = nullptr;

bool MainScene::init() {
	if (!Layer::init())
		return false;

	size = Director::getInstance()->getVisibleSize();

	///< Play the background music
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgmusic.mp3", true);

	createBackground();
	createCloud();
	createMouse();
	createProp();
	createCucrbit();

	eventProcess();
	initCucurbit();

	scheduleProcess();

	auto wea = Weather::create();
	this->addChild(wea);

	isHold = false;

	return true;
}

Scene* MainScene::createScene() {
	auto scene = Scene::create();
	auto pause = Pause::create();
	auto gameOver = GameOver::create();
	hudLayer = HUDLayer::create();
	auto mainGame = MainScene::create();
	scene->setTag(GAMELAYERTAG);
	mainGame->setTag(GAMETAG);
	gameOver->setTag(GAMEOVERTAG);
	scene->addChild(mainGame);
	scene->addChild(hudLayer);
	scene->addChild(pause);
	scene->addChild(gameOver);

	return scene;
}

void MainScene::moveBackgroundAndCucrbit(float dt) {
	// Move background
	float dif;
	if (Util::getDif() == -1)
		dif = 6;
	else
		dif = Util::getDif();

	bg1->setPosition(Vec2(bg1->getPositionX() - dif, bg1->getPositionY()));
	bg2->setPosition(Vec2(bg2->getPositionX() - dif, bg2->getPositionY()));

	if (bg2->getPositionX() < 0) {
		float temp = bg2->getPositionX() + size.width;
		bg1->setPosition(Vec2(temp - 2, bg1->getPositionY()));
	}

	if (bg1->getPositionX() < 0) {
		float temp = bg1->getPositionX() + size.width;
		bg2->setPosition(Vec2(temp - 2, bg2->getPositionY()));
	}

	// Move the cucrbits
	cucrbitManage->moveCucrbit(dt);
}

void MainScene::eventProcess() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *event) {
		propContainerTouchEvent(touch, event);
		return true;
	};

	listener->onTouchMoved = [=](Touch *touch, Event *event) {
		cucrbitTouchEvent(touch, event);
		propTouchEvent(touch, event);
	};

	listener->onTouchEnded = [=](Touch *touch, Event *event) {
		isHold = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainScene::cucurbitProcess(float dt) {
	cucrbitManage->cucurbitProcess(dt);
}

void MainScene::initCucurbit() {
	cucrbitManage->initCucurbit();
}

void MainScene::addCucurbit(float dt) {
	cucrbitManage->addCucurbit(dt);
}

void MainScene::cucrbitFallDown(Cucurbit *cucrbit) {
	cucrbitManage->cucrbitFallDown(cucrbit);
}

void MainScene::removeFallDownCucrbit(float dt) {
	cucrbitManage->removeFallDownCucrbit(mouse, hudLayer);
}

void MainScene::propCreator(float dt) {
	propManager->propCreator(dt);
}

void MainScene::cucrbitTouchEvent(Touch *touch, Event *event) {
	if (isHold == false) {
		// Only the first cucrbit that been incised need to fall down
		isHold = cucrbitManage->cucrbitTouchEvent(touch, event);
	}
}

void MainScene::propTouchEvent(Touch *touch, Event *event) {
	propManager->propTouchEvent(touch, event);
}

void MainScene::propContainerTouchEvent(Touch *touch, Event *event) {
	propManager->propContainerTouchEvent(touch, event);
}

void MainScene::cloudCreater(float dt) {
	cloudManager->createCloud();
}

void MainScene::createBackground() {
	///< Set the background
	bg1 = Sprite::createWithSpriteFrameName("background.png");
	bg2 = Sprite::createWithSpriteFrameName("background.png");

	///< Set the scaling
	auto sx = size.width / bg1->getContentSize().width;
	auto sy = size.height / bg1->getContentSize().height;
	bg1->setScale(sx, sy);
	bg1->setAnchorPoint(Vec2(0, 0));
	///< Set the position
	bg1->setPosition(Vec2(0, 0));

	sx = size.width / bg2->getContentSize().width;
	sy = size.height / bg2->getContentSize().height;
	bg2->setScale(sx, sy);
	bg2->setAnchorPoint(Vec2(0, 0));
	bg2->setPosition(Vec2(size.width - 2, 0));

	this->addChild(bg1);
	this->addChild(bg2);
}
void MainScene::createCloud() {
	///< add cloud Manager
	cloudManager = CloudManager::create();
	cloudManager->createCloud();
	this->addChild(cloudManager);
}

void MainScene::createProp() {
	///< Add prop manager
	propManager = PropManager::create();
	this->addChild(propManager);
}

void MainScene::createMouse() {
	///< Add mouse to the main scene
	mouse = Mouse::createMouse();
	mouse->run();
	this->addChild(mouse);
}

void MainScene::createCucrbit() {
	///< Add cucrbit manager
	cucrbitManage = CucrbitManage::create();
	this->addChild(cucrbitManage);
}

void MainScene::scheduleProcess() {
	schedule(schedule_selector(MainScene::moveBackgroundAndCucrbit));
	schedule(schedule_selector(MainScene::cucurbitProcess), 2);
	schedule(schedule_selector(MainScene::addCucurbit), 2);
	schedule(schedule_selector(MainScene::removeFallDownCucrbit));
	schedule(schedule_selector(MainScene::propCreator), 4);
	schedule(schedule_selector(MainScene::cloudCreater), 4);
}