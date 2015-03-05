//
//  Util.cpp
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#include "Util.h"

float Util::pauseMenuWidth = 0;
float Util::dif = -1;

void Util::setPauseMenuWidth(float pw) {
    pauseMenuWidth = pw;
}

float Util::getPauseMenuWidth() {
    return pauseMenuWidth;
}

float Util::getDif() {
    return dif;
}

void Util::setDif(float dif_) {
    dif = dif_;
}