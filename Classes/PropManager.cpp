//
//  PropManager.cpp
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#include "PropManager.h"
#include "Prop.h"
#include <stdio.h>

bool PropManager::init() {
	if (!Sprite::init())
		return false;

	fertilizers = PropContainer::createPropContainer(FERTILIZER);
	block = PropContainer::createPropContainer(BLOCK);
	magent = PropContainer::createPropContainer(MAGNET);
	this->addChild(fertilizers);
	this->addChild(block);
	this->addChild(magent);

	this->setPosition(0, 0);

	prop = nullptr;
	size = Director::getInstance()->getVisibleSize();

	return true;
}

void PropManager::addProp(Attribute attribute) {
	switch (attribute) {
	case FERTILIZER:
		this->fertilizers->addAProp();
		break;
	case BLOCK:
		this->block->addAProp();
		break;
	default:
		this->magent->addAProp();
		break;
	}
	update();
}

void PropManager::deleteProp(Attribute attribute) {
	switch (attribute) {
	case FERTILIZER:
		this->fertilizers->deleteAProp();
		break;
	case BLOCK:
		this->block->deleteAProp();
		break;
	default:
		this->magent->deleteAProp();
		break;
	}
	update();
}

void PropManager::update() {
	this->fertilizers->updateContainer();
	this->block->updateContainer();
	this->magent->updateContainer();
}

void PropManager::propContainerTouchEvent(Touch *touch, Event *event) {
		auto touchLocation = touch->getLocation();
		auto fertiPosition = fertilizers->getPosition();
		auto fertiSize = fertilizers->getContentSize();
		auto blockPosition = block->getPosition();
		auto blockSize = block->getContentSize();
		auto magentPosition = magent->getPosition();
		auto magentSize = magent->getContentSize();

		PropContainer* container = nullptr;

		if (touchLocation.x >= fertiPosition.x + 2 && touchLocation.x <= fertiPosition.x + fertiSize.width - 2) {
			if (touchLocation.y >= fertiPosition.y + 2 && touchLocation.y <= fertiPosition.y + fertiSize.height - 2) {
				container = fertilizers;
			}
		}
		if (container == nullptr && touchLocation.x >= blockPosition.x + 2 && touchLocation.x <= blockPosition.x + blockSize.width - 2) {
			if (touchLocation.y >= blockPosition.y + 2 && touchLocation.y <= blockPosition.y + blockSize.height - 2) {
				container = block;
			}
		}
		if (container == nullptr && touchLocation.x >= magentPosition.x + 2 && touchLocation.x <= magentPosition.x + magentSize.width - 2) {
			if (touchLocation.y >= magentPosition.y + 2 && touchLocation.y <= magentPosition.y + magentSize.height - 2) {
				container = magent;
			}
		}

		if (container != nullptr) {
			// Container do action
			container->stopAllActions();
			auto sacleTo1 = ScaleTo::create(0.2, 1.1);
			auto sacleTo2 = ScaleTo::create(0.2, 1);
			auto seq = Sequence::create(sacleTo1, sacleTo2, NULL);
			container->runAction(seq);
			
			// Mouse and cucrbit do action

			this->deleteProp(container->getTheAttribute());
		}
}

void PropManager::propTouchEvent(Touch *touch, Event *event) {
	if (prop && prop->getIsTouch() == false) {
		auto touchLocation = touch->getLocation();
		auto propLocation = prop->getPosition();
		auto propSize = prop->getContentSize();
		if (propLocation.x <= touchLocation.x && propLocation.x + propSize.width >= touchLocation.x) {
			if (propLocation.y <= touchLocation.y && propLocation.y + propSize.height >= touchLocation.y) {
				prop->setIsTouch(true);
				this->addProp(prop->getAttribute());
				if (prop->getAttribute() == FERTILIZER) {
					prop->burst(fertilizers->getPosition(), fertilizers->getContentSize());
				}
				else if (prop->getAttribute() == BLOCK) {
					prop->burst(block->getPosition(), block->getContentSize());
				}
				else {
					prop->burst(magent->getPosition(), magent->getContentSize());
				}
				prop = nullptr;
				this->update();
			}
		}
	}
}

void PropManager::propCreator(float dt) {
	prop = Prop::create();
	prop->run();
	this->addChild(prop);
}