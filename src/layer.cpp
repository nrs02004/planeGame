


#include "layer.h"
#include "level.h"

Layer::Layer(){
    terminate = false;
}




// Defining stuff for pause layer

pause_layer::pause_layer() : Layer(){}

void pause_layer::update(float dt, std::vector<Action*> &actions, std::stack<Layer*> &layers)
{
    apply_actions(actions, layers);
}

void pause_layer::apply_actions(std::vector<Action*> &actions, std::stack<Layer*> &layers)
{
    if(!actions.empty())
    {
        for(std::vector<Action*>::iterator it = actions.begin(); it != actions.end(); it++){
            switch((*it)->action_type){
                case CLICK:
                    (*it)->apply();
                    terminate = true;
            }
        }
    }
    actions.clear();
}

void pause_layer::display(){}

// Defining stuff for pause layer

Intro::Intro(lua_State *_L, Ship *_myShip) : Layer()
{
    L = _L;
    myShip = _myShip;
    start_level = false;
    count = 0;
}

void Intro::update(float dt, std::vector<Action*> &actions, std::stack<Layer*> &layers)
{
    apply_actions(actions, layers);
    if( start_level == true ){
      	std::cout << "b";
        std::string filename="level/level1.lua";
	myShip->life = 10; // refilling life
	myShip->exploded = 0;

	/* This is a crap way to do this; fix it! */
	lua_close(L);
	L = luaL_newstate();
	luaL_openlibs(L);

	Ship* myShip = init_ship(L); //Perhaps we should delete this, since we keep reinstantiating?
        Level* Level1 = new Level(filename, L, myShip);
        layers.push(Level1);
	start_level = false;
	count++;
    }
}

void Intro::apply_actions(std::vector<Action*> &actions, std::stack<Layer*> &layers)
{
    if(!actions.empty())
    {
        for(std::vector<Action*>::iterator it = actions.begin(); it != actions.end(); it++){
            switch((*it)->action_type){
                case CLICK:
		  (*it)->apply();
		  start_level = true;
		  std::cout << "a";
            }
        }
    }
    actions.clear();
}


Ship* Intro::init_ship(lua_State *L)
{
  std::string myShip_filename = "objects/myShip.lua";
  load_file(L, myShip_filename);
  myShip_dat myShip_data = lua_get_myShip(L,"ship");

  std::vector<Image*> *ship_images = new std::vector<Image*>;
  ship_images->push_back(images["ship_image"]);
  ship_images->push_back(images["ship_imageL"]);
  ship_images->push_back(images["ship_imageR"]);
  ship_images->push_back(images["ship_imageLL"]);
  ship_images->push_back(images["ship_imageRR"]);

  Ship *myShip = new Ship(240, 190, ship_images, *colors[myShip_data.color_name], myShip_data.accel, myShip_data.max_vel, myShip_data.life, myShip_data.hitboxes);

  // Adding Weapons to Ship

  for(auto it = (myShip_data.weapon_names).begin(); it != (myShip_data.weapon_names).end(); it++){
    myShip->add_weapon(*weapon_list[*it]);
  }

  return myShip;
}

void Intro::display(){}


// Initial definitions for our virtual functions

void Layer::update(float dt, std::vector<Action*> &actions, std::stack<Layer*> &layers){}
void Layer::display(){}
