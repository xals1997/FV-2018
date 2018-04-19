/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor2D.cpp
 * Author: blanca
 * 
 * Created on 27 de marzo de 2018, 10:39
 */

#include "Motor2D.h"
#include "Game.h"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>

Motor2D* Motor2D::pinstance =0;
Motor2D* Motor2D::Instance()
{
    if(pinstance==0){
        pinstance= new Motor2D();
    }
    
    return pinstance;
}

Motor2D::Motor2D()
:window(sf::VideoMode(1280,720), "Ye", sf::Style::Close | sf::Style::Fullscreen | sf::Style::Titlebar)
{
     
}


void Motor2D::dibujar(sf::Sprite a){
    window.draw(a);
  
}

void Motor2D::dibujarTexto(sf::Text t){
 
    window.draw(t);
}

bool Motor2D::openWindow(){
    window.isOpen();
    
}

void Motor2D::clearWindow(){
    
    window.clear();
}

void Motor2D::displayWindow(){
    
    window.display();
    
}

void Motor2D::closeWindow(){
    
    window.close();
    
}







sf::RenderWindow* Motor2D::getWindow()
{
    return &window;
}