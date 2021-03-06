#include "IA.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Colisionator.h"
#ifndef IAACTIVA_H
#define IAACTIVA_H

class IAActiva : public IA {
public:
    IAActiva();
    IAActiva(const IAActiva& orig);
    virtual ~IAActiva();
    void elegirComportamiento(Sprite* &s);
    void setVelocidad(float);
    void moverse(std::vector<Food*> f,Sprite* &s);
    void perseguir(Sprite* s, float time);
    bool checkColisionMap(int x, int y, Sprite* enemy);
    //bool checkColisionEnemy(int x, int y, Sprite* enemy);
    void simpleColision(Sprite* enemy);
    int getType();
    
private:
   int kVel;
   Clock t_ataque;
   Colisionator collision;
   int tipo;
   int rand_decision;
};

#endif /* IAACTIVA_H */

