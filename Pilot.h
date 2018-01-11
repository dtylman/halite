
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
    
    const hlt::Ship& ship() const;
    
    virtual void play(const hlt::Map& map, hlt::Moves& moves) = 0;    
    virtual int target_entity_id() const =0;
    void update_ship(const hlt::Ship& ship);
    bool idle() const;
protected:
    const hlt::Ship* find_nearest_enemy(const hlt::Map& map) const;
    const hlt::Planet* find_nearest_planet(const hlt::Map& map, bool owned) const;    
    void move_to(const hlt::Map& map, const hlt::Location& location, hlt::Moves& moves) ;
    bool move_to_dock(const hlt::Map& map, hlt::Moves& moves) ;    
    void set_idle(hlt::Moves& moves, bool set_idle = true);
    void log(const std::string& message);
    hlt::Ship _ship;       
    bool _idle;
};


#endif /* SHIP_H */

