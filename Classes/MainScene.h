//
//  MainScene.h
//  WittedMouse
//
//  Created by wc on 15/2/14.
//
//

#ifndef __WittedMouse__MainScene__
#define __WittedMouse__MainScene__

#include "cocos2d.h"
#include "HUDLayer.h"
#include "Mouse.h"
#include "Cucurbit.h"
#include "Prop.h"
#include "PropManager.h"
#include "CucrbitManage.h"

USING_NS_CC;

class MainScene : public Layer {
public:
    virtual bool init();
    static Scene* createScene();
    /**
     * Move the background picture from right to left repeatly
     */
    void moveBackgroundAndCucrbit(float dt);
    
    /**
     * The processor of the cucurbit, which to grow the cucrbit
     */
    void cucurbitProcess(float dt);
    
    /**
     * To add the cucurbit if need
     */
    void addCucurbit(float dt);
    
    /**
     * Initialize the cucrbit in the screen
     */
    void initCucurbit();
    
    /**
     * The processor of event like touch
     */
    void eventProcess();
    
    /**
     * The cucrbit which is incised or grown up and need to fall down
     */
    void cucrbitFallDown(Cucurbit *cucrbit);
    
    /**
     * Remove the cucrbit that is crash with mouse of fall down in the ground
     */
    void removeFallDownCucrbit(float dt);
    
    /**
     * The prop creator
     */
    void propCreator(float dt);
    
    /**
     * Cucrbit touch event
     */
    void cucrbitTouchEvent(Touch *touch, Event *event);
    
    /**
     * Prop touch event
     */
    void propTouchEvent(Touch *touch, Event *event);
    
    static HUDLayer *hudLayer;
    
    ///< The size of the screen
    CC_SYNTHESIZE_READONLY(Size, size, Size);
    
    CREATE_FUNC(MainScene);
private:
    Sprite *bg1, *bg2;
    Mouse *mouse;
    PropManager *propManager;
    CucrbitManage *cucrbitManage;
    
    ///< If there is a cucrbit fall down in one touch
    bool isHold;
};

#endif /* defined(__WittedMouse__MainScene__) */
