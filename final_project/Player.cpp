#include "Player.h"
#include <iostream>
#include <math.h>  
#include "Motor2D.h"
#include "Sprite.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#define kVel 2

#define kSalto 20

Player::Player() {
    
    sprite=new Sprite();
    x = 200;
    y = 200;
    up = false;
    left = false;
    down = false;
    right = false;

}

void Player::chargingTexture() {
	
	sprite->setSpriteTexture("resources/sprites.png");                              // Y creo el spritesheet a partir de la imagen anterior
        sprite->getSprite()->setTextureRect(sf::IntRect(4,238, 58, 64));
	sprite->getSprite()->setOrigin(58/2,64/2);
	sprite->getSprite()->setPosition(x, y);                               // Lo dispongo en el centro de la pantalla
}


void Player::draw() {
    
    sprite->draw();
}

void Player::input(){
        
   // if(sf::Event::KeyPressed){

                    if(Keyboard::isKeyDPressed()){				
                            
                        right = true;
                    }
                    
                    if(Keyboard::isKeyAPressed()){
                        
                        left=true;
                        
                    }
                    
                    if(Keyboard::isKeyWPressed()){
                        
                        up=true;
                    }
                    
                    if(Keyboard::isKeySPressed()){
                        
                        down=true;
                        
                    }

		//}
	
	
	//else{
	
                    if(!Keyboard::isKeyDPressed()){				
                        std::cout<<"dasdasda"<<std::endl;
                        right = false;
                    }
                    
                    if(!Keyboard::isKeyAPressed()){
                        
                        left=false;
                        
                    }
                    
                    if(!Keyboard::isKeyWPressed()){
                        
                        up=false;
                    }
                    
                    if(!Keyboard::isKeySPressed()){
                        
                        down=false;
                        
                    }
		
	//}  

}



void Player::lookAtMouse(){
    
    sf::Vector2f curPos = sprite->getPosition();
    //(std::cout<<sprite->getPosition().x;
    //std::cout<<sprite->getPosition().y;
    sf::Vector2f position(Mouse::getPosX(), Mouse::getPosY()); 
    const float PI = 3.14159265;
    float dx = curPos.x - position.x;
    float dy = curPos.y - position.y;
    float rotation = (atan2(dy, dx)) * 180 / PI;
    sprite->rotate(rotation-90);

}



void Player::update(){
       lookAtMouse();
        moveChar();
}

// Si pulsamos IZDA, intentamos ir a la IZDA
// Si pulsamos DCHA, intentamos ir a la DCHA
void Player::moveChar(){
    
	if(left){
            moveX();
        
            
        }

             if(right){      
             moveX();
           
             }
        
        
        if(up){
            
            moveY();
            
            
        }
       
            if(down){
                
            moveY();
           
            
            }
        
   
}


void Player::moveX(){
    if(left)
             sprite->moving(-kVel, 0);
    if(right)
            sprite->moving(kVel, 0);
       
}

void Player::moveY(){
    if(up)
             sprite->moving(0, -kVel);
    if(down)
             sprite->moving(0, kVel);
      
}


Sprite* Player::getSprite(){
    return sprite;
}

/*
bool Player::colisionComida(){
   
        if(comida->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
            std::cout<<"Colisiona"<<std::endl;
            return true;
        }
    return false;
  
}

*/