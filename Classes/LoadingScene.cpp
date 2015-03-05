#include "LoadingScene.h"
#include "I18N.h"
#include "AnimationUtils.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "Mouse.h"
#include "JSON\writer.h"
#include "JSON\reader.h"
#include "JSON\value.h"


Scene* LoadingScene::createScene() {
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* loadingTile = Label::createWithTTF(I18N::getInstance()->getString("loadingTitle"), "fonts/huaifang.ttf", 100);
	loadingTile->setColor(Color3B(255, 255, 255));
	loadingTile->setPosition(
		Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - loadingTile->getContentSize().height)
	);
	this->addChild(loadingTile, 1);

	loadRes();
	loadData();

	Sprite* mouse = Sprite::createWithSpriteFrameName("run00.png");
	mouse->setPosition(Point(-100, 150));
	this->addChild(mouse, 1);
	mouse->runAction(Animate::create(AnimationUtils::createWithName("run", 0.1f, -1)));

	MoveTo* moveTo = MoveTo::create(4.0f, Point(winSize.width + 100, 150));
	CallFunc* callFunc = CallFunc::create([]() {
		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	mouse->runAction(Sequence::create(moveTo, callFunc, NULL));
	return true;
}

void LoadingScene::loadRes() {
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("images/mouse.plist", "images/mouse.png");
	frameCache->addSpriteFramesWithFile("images/MainGame.plist", "images/MainGame.png");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bgmusic.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/cut-hulu.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/thunderclap.mp3");
}

void LoadingScene::loadData() {
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile("data/mouse.json");
	if (reader.parse(data, root, false)) {
		Mouse::setIQ(root["IQ"].asInt());
		Mouse::setLife(root["life"].asInt());
	}
	else {
		Mouse::setIQ(INIT_IQ);
		Mouse::setLife(INIT_LIFE);
	}
}