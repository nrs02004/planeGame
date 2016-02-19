


#include "layer.h"

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


// Initial definitions for our virtual functions

void Layer::update(float dt, std::vector<Action*> &actions, std::stack<Layer*> &layers){}
void Layer::display(){}
