//
//  event.cpp
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include <algorithm>
#include <functional>
#include "level.h"
#include "enemyShip.h"
#include "luaObj.h"
#include "lua_binding.h"
#include "lua/lua.hpp"
#include "defs.h"

bool cmp( const EnemyShip *s1, const EnemyShip *s2 ){return (s1)->y < (s2)->y;}

Level::Level(std::string filename, lua_State *L, std::map<std::string, Image*> _images)
{
  currComplete = 0;
  speed = 100;
  images = _images;
  
  load_file(L, filename);

  // Loading the enemy ships
  
  std::string enemy_data = "enemy_stack";
  std::vector<Ship_dat*> ship_dat = lua_get_ships(L, enemy_data);
  
  for(auto shipIt = ship_dat.begin(); shipIt != ship_dat.end(); shipIt++){
    EnemyShip *newEnemy = new EnemyShip((*shipIt)->x, (*shipIt)->y,
					(*shipIt)->speed,(*shipIt)->cool_down_length,
					(*shipIt)->life, images["enemy_image"]);
    future_enemies.push_back(newEnemy);
    delete(*shipIt);
  }
    
  // Sort the  ships by y-value
    
  std::sort(future_enemies.begin(), future_enemies.end(),cmp);
    
  //clean up things
}

//should probably change SCREEN_HEIGHT here
void Level::update(float dt, std::vector<EnemyShip*> &enemies)
{
  currComplete += speed * dt;
  
  //Should update this to pop from the back
  if(!future_enemies.empty()){

    for(auto it = future_enemies.begin();
	((*it)->y - currComplete <= SCREEN_HEIGHT) &&
	  (it != future_enemies.end());){
      
      (*it)->y = SCREEN_HEIGHT + SCREEN_BUFFER - ((*it)->y - currComplete);
      enemies.push_back(*it);
      it = future_enemies.erase(it);
    }
  }
}
    
Level::~Level()
{
}
