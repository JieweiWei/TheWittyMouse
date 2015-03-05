//
//  Mouse.h
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#ifndef __WittedMouse__Mouse__
#define __WittedMouse__Mouse__

#include "cocos2d.h"

USING_NS_CC;

class Mouse : public Sprite {
public:
    /**
     * Create the mouse
     */
    static Mouse* createMouse();
    virtual bool init();
    /**
     * The running action of the mouse
     */
    void run();
    /**
     * The jump action of the mouse
     */
    void jump();
    /**
     * The fall action of the mouse when the mouse is hit by the calabash
     */
    void fall();
    
    /**
     * Return the IQ value
     */
    static int getIQ();
    
    /**
     * Set the IQ value
     */
    static void setIQ(int IQ_);
    
    /**
     * Return the life value
     */
    static int getLife();
    
    /**
     * Set the life value
     */
    static void setLife(int life_);
    
private:
    static int IQ;
    static int life;
};

#endif /* defined(__WittedMouse__Mouse__) */
