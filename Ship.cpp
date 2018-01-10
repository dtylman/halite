
/* 
 * File:   Ship.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:40 PM
 */

#include <climits>

#include "Pilot.h"
#include "Vector2.h"
#include "hlt/navigation.hpp"

Pilot::Pilot(const hlt::Ship& halite_ship) : _ship(halite_ship) {

}

Pilot::~Pilot() {
}

const hlt::Ship& Pilot::ship() {
    return _ship;
}

void Pilot::set_ship(const hlt::Ship& halite_ship) {
    _ship = halite_ship;
}

const hlt::Ship* Pilot::find_nearest_enemy(const hlt::Map& map) const {
    double lowest_distance = INT_MAX;
    const hlt::Ship* nearest_ship = NULL;
    for (auto list : map.ships) {
        if (_ship.owner_id != list.first) { //not my ship
            for (auto ship : list.second) {
                if (ship.is_alive()) {
                    double distance = ship.location.get_distance_to(_ship.location);
                    if (lowest_distance > distance) {
                        lowest_distance = distance;
                        nearest_ship = &ship;
                    }
                }
            }
        }
    }
    return nearest_ship;
}

const hlt::Planet* Pilot::can_dock(const hlt::Map& map) const {
    for (const hlt::Planet& planet : map.planets) {
        if (planet.owned) {
            continue;
        }

        if (_ship.can_dock(planet)) {
            return &planet;
        }
    }
    return NULL;
}

const hlt::Planet* Pilot::find_nearest_planet(const hlt::Map& map, bool owned) const {
    const hlt::Planet* nearest_planet = NULL;
    double nearest_distance = INT_MAX;
    for (const hlt::Planet& planet : map.planets) {        
        if (owned && planet.owned) {
            continue;
        }        
        double distance = planet.location.get_distance_to(_ship.location);
        if (nearest_distance>distance){
            nearest_distance = distance;
            nearest_planet = &planet;
        }        
    }
    return nearest_planet;
}

void Pilot::move_towards(const hlt::Map& map, const hlt::Location& location, hlt::Moves& moves) const {
    hlt::possibly<hlt::Move> move = hlt::navigation::navigate_ship_towards_target(map,_ship,
            location,hlt::constants::MAX_SPEED,true,hlt::constants::MAX_NAVIGATION_CORRECTIONS,M_PI / 180.0);
        if (move.second){
            moves.push_back(move.first);
        } else {            
            moves.push_back(hlt::Move::noop());
        }
}


void Pilot::move_to_dock(const hlt::Map& map, hlt::Moves& moves) const {
    const hlt::Planet* planet = can_dock(map);
    if (planet!=NULL){
        moves.push_back(hlt::Move::dock(_ship.entity_id, planet->entity_id));
        return;
    } 
    planet = find_nearest_planet(map,false);
    if (planet!=NULL){
        const hlt::possibly<hlt::Move> move =
                hlt::navigation::navigate_ship_to_dock(map, _ship, *planet, hlt::constants::MAX_SPEED);
        if (move.second) {
            moves.push_back(move.first);
            return;
        }
    }
    //stop 
    moves.push_back(hlt::Move::noop());
}
