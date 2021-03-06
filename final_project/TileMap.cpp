/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TileMap.cpp
 * Author: blanca
 * 
 * Created on 19 de abril de 2018, 9:59
 */

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "iostream"
#include "ingame_state.h"

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    
    /*for(int i = 0; i < 256; i++){
        target.draw(_tileSetImagen[i]);
    }*/
    
    for(int i = 0; i < altoMapa; i++){
        for(int j = 0; j< anchoMapa; j++){
            if(_tileMapSprite[capaActiva][i][j] != NULL){
                target.draw(*(_tileMapSprite[capaActiva][i][j]));
            }
        }
    }
}

void TileMap::setCapaActiva(int layer){
    capaActiva=layer;
}


void TileMap::cargarmapa(std::string path){
    numeroCapas=0;
    capaActiva=0;
    
    const char* file = path.c_str();
    
    TiXmlDocument doc;
    doc.LoadFile(file);
    TiXmlElement *map = doc.FirstChildElement("map");
    
    //Recogemos los atributos del mapa
    map->QueryIntAttribute("width", &anchoMapa); //100
    map->QueryIntAttribute("height", &altoMapa); //100
    map->QueryIntAttribute("tilewidth", &anchoTile); //Ancho del tile en px = 32
    map->QueryIntAttribute("tileheight", &altoTile); //Ancho del tile en px = 32
       
    TiXmlElement *layer = map->FirstChildElement("layer");
   
    //Recogemos la imagen del tileset
    TiXmlElement *img = map->FirstChildElement("tileset")->FirstChildElement("image");
    tilesetname = img->Attribute("source");
    //Imprimimos el nombre o ruta del tileset
  
    while(layer != NULL){
        /*if(numeroCapas < 1)*/
        numeroCapas++; //Si tenemos solo una capa entonces numeroCapas es 0 y si son dos capas 1 etc...
        layer = layer->NextSiblingElement("layer");
    }
    
    TiXmlElement *data[numeroCapas];
    data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    _tilemap = new int**[numeroCapas]; 
    //int numeraso = 0;
    // _tilemap = Matriz que contendrá el ID de cada tile.
    //tilemap es un puntero a un array con el numero de capas el cual cada numero del array apunta 
    //a un array [height] que contiene la altura del mapa y cada elemento del array altura
    //apunta al primer ID de cada fila, luego para acceder al resto sumamos una posicion de memoria
    for(int i = 0; i < numeroCapas; i++){
        _tilemap[i] = new int*[altoMapa];
    }
    for(int l = 0; l < numeroCapas; l++){
        for(int y = 0; y < altoMapa; y++){
            _tilemap[l][y] = new int[anchoMapa];
            for(int x = 0; x < anchoMapa; x++){
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
               
                data[l] = data[l]->NextSiblingElement("tile");
             
            }
        }
        if(l==0){
            data[l+1] = map->FirstChildElement("layer");
            data[l+1] = data[l+1]->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        }else if(l==1){
            data[l+1] = map->FirstChildElement("layer");
            data[l+1] = data[l+1]->NextSiblingElement("layer");
            data[l+1] = data[l+1]->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        }
    }
    
    //Recortamos y añadimos el tileset al array
    //Primero sacamos las columnas y la altura del tileset
    img->QueryIntAttribute("width", &anchoImagen);
    img->QueryIntAttribute("height", &altoImagen);
    int columnas = anchoImagen/anchoTile;  //512px/32px;
    int filas = altoImagen/altoTile;    //512px/32px;
    _tileSetImagen = new sf::Sprite[columnas*filas+1];
    int posicion = 0;
    _tileSetTexture.loadFromFile(tilesetname);//Cargamos el tileset 
    //Rellenamos un array unidimensional con cada uno de los Sprites del tileset
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            posicion++;
            _tileSetImagen->setTexture(_tileSetTexture);
            _tileSetImagen[posicion].setTextureRect(sf::IntRect(32*j,32*i,32,32));
        }
    }
    
    
    
    //AQUI TENEMOS DOS VARIABLES tileset y tilesetTexture, la primera tiene los IDS de cada una
    //de las posiciones del mapa y la otra tiene cargadas una tras otra los tiles(imagenes)
    //ahora hay que relacionarlas jejejejejejejejej que guay 
    _tileMapSprite = new sf::Sprite***[numeroCapas];
    
    for(int l = 0; l < numeroCapas; l++){
        _tileMapSprite[l] = new sf::Sprite**[altoMapa];
    }
    for(int l = 0; l < numeroCapas; l++){
        for(int y = 0; y < altoMapa; y++){
            _tileMapSprite[l][y] = new sf::Sprite*[anchoMapa];
            for(int x = 0; x < anchoMapa; x++){
                _tileMapSprite[l][y][x] = new sf::Sprite();
            }
        }
    }
     
    
    for(int l=0; l<numeroCapas; l++){
        for(int y=0; y<altoMapa; y++){
            for(int x=0; x<anchoMapa; x++){
                int gid = _tilemap[l][y][x];
                if(gid >= anchoTile*altoTile){
                    std::cout << "Error, gid at (l,x,y) = (" << l << "," << x << "," << y << "): "
                            << gid << " fuera del rango del tileset ("<<anchoTile*altoTile<<")" << std::endl;
                }
                else if(gid > 0){

                    _tileMapSprite[l][y][x] = new sf::Sprite(_tileSetTexture, _tileSetImagen[gid].getTextureRect());
                    _tileMapSprite[l][y][x]->setPosition(x*anchoTile, y*altoTile);
                   
                }
                else{
                    _tileMapSprite[l][y][x] = NULL;
                }
            }
        }
    }
}
void TileMap::deleteMap()
{
    for(int l = 0; l < numeroCapas; l++)
    {
        for(int y = 0; y < altoMapa; y++)
        {
            delete[] _tilemap[l][y];
        }
        delete[] _tilemap[l];
    }
    delete[] _tilemap;
 
    delete[] _tileSetImagen;

    for(int x = 0; x < numeroCapas; x++)
    {
        for(int y = 0; y < altoMapa; y++)
        {
            for(int j = 0; j < anchoMapa; j++)
            {
                delete _tileMapSprite[x][y][j];
            }
            delete[] _tileMapSprite[x][y];
        }
        delete[] _tileMapSprite[x];
    }
    delete[] _tileMapSprite;
}

