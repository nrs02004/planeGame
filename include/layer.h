#ifndef __airplaneGame__layer__
#define __airplaneGame__layer__

#include <iostream>
#include "action.h"
#include <vector>
#include <string>
#include <stack>
#include "image.h"

class Layer
{
public:
    Layer();
    virtual void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    virtual void display();
    
    bool terminate;
};

class pause : public Layer
{
public:
    pause();
    void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    void display();
    void apply_actions(std::vector<Action*> &, std::stack<Layer*> &);
};

#endif /* defined(__airplaneGame__layer__) */
