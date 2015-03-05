//
//  PropManager.h
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#ifndef __WittedMouse__PropManager__
#define __WittedMouse__PropManager__

#include "cocos2d.h"
#include "Prop.h"
#include "PropContainer.h"

USING_NS_CC;

class PropManager : public Sprite{
public:
    bool init();
    
    /**
     * Add a prop to the container, which means that the number of the prop increase by one
     */
    void addProp(Attribute attribute);
    
    /**
     * Delete a prop from the container, which means that the number of the prop decrease by one
     */
    void deleteProp(Attribute attribute);
    
    /**
     * Update the number of the prop
     */
    void update();
    
    /**
     * The event processor of screen touch when touch the prop
     */
    void propTouchEvent(Touch *touch, Event *event);
    
    /**
     * Create a prop randomly at intervals
     */
    void propCreator(float dt);
    
    /**
     * Remove the prop in the screen
     */
    void removeProp(Prop *p);
    
    CREATE_FUNC(PropManager);
private:
    ///< The container of three props
    PropContainer *fertilizers;
    PropContainer *block;
    PropContainer *magent;
    Size size;
    Prop *prop;
};

#endif /* defined(__WittedMouse__PropManager__) */