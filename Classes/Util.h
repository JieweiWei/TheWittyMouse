//
//  Util.h
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#ifndef __WittedMouse__Util__
#define __WittedMouse__Util__

#include "cocos2d.h"

USING_NS_CC;

#define GAMELAYERTAG 8
#define GAMETAG 9
#define MOUSETAG 10
#define CUCRBITTAG 11
#define PAUSETAG 12
#define PROPTAG 13
#define GAMEOVERTAG 14

class Util {
public:
    static void setPauseMenuWidth(float pw);
    static float getPauseMenuWidth();
    static float getDif();
    static void setDif(float dif_);
private:
    static float pauseMenuWidth;
    static float dif;
};

#endif /* defined(__WittedMouse__Util__) */
