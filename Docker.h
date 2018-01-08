/* 
 * File:   Docker.h
 * Author: danny
 *
 * Created on January 8, 2018, 3:32 PM
 */

#ifndef DOCKER_H
#define DOCKER_H

#include "Ship.h"


class Docker : public Ship{
public:
    Docker(const hlt::Ship& hltShip);    
    virtual ~Docker();
private:

};

#endif /* DOCKER_H */

