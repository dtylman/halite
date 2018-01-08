
/* 
 * File:   Ship.h
 * Author: danny
 *
 * Created on January 8, 2018, 3:40 PM
 */

#ifndef SHIP_H
#define SHIP_H

#include "hlt/ship.hpp"
#include "hlt/map.hpp"
#include "hlt/move.hpp"

class Ship {
public:
    Ship(const hlt::Ship& halite_ship);
    virtual ~Ship();
    
    const hlt::Ship& halite_ship();
    
    virtual void play(const hlt::Map& map, hlt::Moves& moves) = 0;
    
    void set_halite_ship(const hlt::Ship& halite_ship);
protected:
    hlt::Ship _halite_ship;    
};


#endif /* SHIP_H */

