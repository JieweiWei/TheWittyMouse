#ifndef _MENUSCEME_H_
#define _MENUSCEME_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Popup.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define BUTTON_CLICK_SCALE 0.9


class MenuScene : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

private:
	/* ����CocosStudio��UI����ӵ���¼� */
	void loadUIAndSetListner();

	/* ��ʼ�������� */
	void initPopup();

	/* ��ť�Ĵ����¼� */
	void singleModeEvent(Ref*, TouchEventType type);
	void showOrHideEvent(Ref* sender, TouchEventType type);
	void showDeveloper(Ref*, TouchEventType type);
	void showHelp(Ref*, TouchEventType type);
	void showSetting(Ref*, TouchEventType type);
	void showInfo(Ref*, TouchEventType type);
	void hidePopup(Ref* sender);

private:
	bool _isShow;
	ListView* _itemList;
	Popup* _popup;
};


#endif // !_MENUSCEME_H_