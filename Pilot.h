
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

class Pilot {
public:
    Pilot(const hlt::Ship& ship);
    virtual ~Pilot();
    
    const hlt::Ship& ship();
    
    virtual void play(const hlt::Map& map, hlt::Moves& moves) = 0;
    
    void set_ship(const hlt::Ship& ship);
protected:
    const hlt::Ship* find_nearest_enemy(const hlt::Map& map) const;
    const hlt::Planet* find_nearest_planet(const hlt::Map& map, bool owned) const;
    const hlt::Planet* find_planet_todock(const hlt::Map& map) const;
    void move_towards(const hlt::Map& map, const hlt::Location& location, hlt::Moves& moves) const;
    void move_to_dock(const hlt::Map& map, hlt::Moves& moves) const;
    hlt::Ship _ship;    
};


#endif /* SHIP_H */

