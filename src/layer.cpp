


#include "layer.h"
#include "level.h"

Layer::Layer(){
    terminate = false;
}




// Defining stuff for pause layer

pause::pause() : Layer(){}

void pause::update(float dt, std::vector<Action*> &actions, std::stack<Layer*> &layers)
{
    apply_actions(actions, layers);
}

void pause::apply_actions(std::vector<Action*> &actions, std::stack<Layer*> &layers)
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

void pause::display(){}

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

void Intro::display(){}


// Initial definitions for our virtual functions

void Layer::update(float dt, std::vector<Action*> &actions, std::stack<Layer*> &layers){}
void Layer::display(){}
