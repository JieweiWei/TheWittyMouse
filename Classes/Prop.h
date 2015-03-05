//
//  Prop.h
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#ifndef __WittedMouse__Prop__
#define __WittedMouse__Prop__

#include "cocos2d.h"

USING_NS_CC;

/**
 * Attribute for Prop that used by player
 */
enum Attribute {
    FERTILIZER = 1,
    BLOCK,
    MAGNET,
    LEAF = 4,
    SKATEBOARDSHOES,
    DIMENSIONDOOR
};

/**
 * Prop used by player
 */
class Prop : public Sprite {
public:
    bool init();
    
    /**
     * Gert the attribute of the prop
     */
    Attribute getAttribute();
    
    CREATE_FUNC(Prop);
private:
    Attribute attribute;
    Size size;
};

#endif /* defined(__WittedMouse__Prop__) */
