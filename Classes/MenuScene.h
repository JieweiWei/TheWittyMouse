#ifndef _MENUSCEME_H_
#define _MENUSCEME_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class MenuScene : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

private:
	/* ����CocosStudio��UI����ӵ���¼� */
	void loadUIAndSetListner();

	/* ��ť�Ĵ����¼� */
	void singleModeEvent(Ref*, TouchEventType type);
	void showOrHideEvent(Ref* sender, TouchEventType type);

	void showHelp(Ref*, TouchEventType type);
	void showInfo(Ref*, TouchEventType type);
	void showSetting(Ref*, TouchEventType type);
	void showDeveloper(Ref*, TouchEventType type);
	
	void closeDialog(Ref*, TouchEventType type);
	void toggleDialogAndSetTitle(const char* title, bool _isShow);

private:
	bool _isBtnListShow;
	bool _isDialogShow;
	Node* _itemList;
	Node* _dialog;
};


#endif // !_MENUSCEME_H_