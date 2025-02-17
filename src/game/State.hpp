#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Enemy;

class State
{
public:
    virtual ~State() = default;

    virtual void handle(Enemy& enemy) = 0;
    virtual string getName() const = 0;


};
#endif // !STATE_HPP

