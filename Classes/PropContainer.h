//
//  PropContainer.h
//  WittedMouse
//
//  Created by wc on 15/2/26.
//
//

#ifndef __WittedMouse__PropContainer__
#define __WittedMouse__PropContainer__

#include "cocos2d.h"
#include "Prop.h"

USING_NS_CC;

class PropContainer : public Sprite {
public:
    bool initPropContainer(Attribute attribute);
    static PropContainer *createPropContainer(Attribute attribute);
    
    /**
     * Add a prop to the prop container
     */
    void addAProp();
    
    /**
     * Delete a prop from the prop container
     */
    void deleteAProp();
    
    /**
     * Is the container empty
     */
    bool isEmpty();
    
    /**
     * Update the container and the prop in the screen
     */
    void updateContainer();
    
    CREATE_FUNC(PropContainer);
    
private:
    int propNum;
    Label* numLabel;
};

#endif /* defined(__WittedMouse__PropContainer__) */
