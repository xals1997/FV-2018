#include "Sprite.h"
#include "Clock.h"
#include "Bala.h"

#ifndef BOSS_H
#define BOSS_H

class Boss {
public:
    Boss();
    Boss(const Boss& orig);
    virtual ~Boss();
    
    Sprite* getSprite();
    void draw();
    void update();
    void setPosition(float x, float y);
    
    float getPositionX();
    float getPositionY(); 
    float getLastPositionX();
     float getLastPositionY();
     
private:
    Sprite* sprite;
    int x,y,lastx,lasty,rotationx, rotationy;
    Clock time,timeshoot;
    std::vector<Bala*> balasArray;
};

#endif /* BOSS_H */

