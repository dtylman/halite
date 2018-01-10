
/* 
 * File:   Ship.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:40 PM
 */

#include "Pilot.h"
#include "hlt/navigation.hpp"
#include "MyPilots.h"
#include <climits>
#include <typeinfo>

Pilot::Pilot(const hlt::Ship& halite_ship) : _ship(halite_ship) {

}

Pilot::~Pilot() {
}

const hlt::Ship& Pilot::ship() const {
    return _ship;
}

void Pilot::update_ship(const hlt::Ship& halite_ship) {
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
   // hlt::Log::output() << "nearest enemy " << nearest_ship->entity_id << " distance " << lowest_distance << std::endl;
    return nearest_ship;
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
   // hlt::Log::output() << "nearest planet " << nearest_planet->entity_id << " distance " << nearest_distance << std::endl;
    return nearest_planet;
}

void Pilot::move_to(const hlt::Map& map, const hlt::Location& location, hlt::Moves& moves) const {
     const hlt::possibly<hlt::Move> move = hlt::navigation::navigate_ship_towards_target(map,
            _ship,location,hlt::constants::MAX_SPEED,true,
            hlt::constants::MAX_NAVIGATION_CORRECTIONS,M_PI / 180.0);
     if (move.second){
         moves.push_back(move.first);
     }
     //stop 
    moves.push_back(hlt::Move::noop());
}

bool Pilot::move_to_dock(const hlt::Map& map, hlt::Moves& moves) const {
    const hlt::Planet* planet = find_nearest_planet(map, false);
    if (planet!=NULL){
        if (_ship.can_dock(*planet)){
            moves.push_back(hlt::Move::dock(_ship.entity_id, planet->entity_id));
            return true;
        }
        const double distance = _ship.location.get_distance_to(planet->location);
        int thurst = hlt::constants::MAX_SPEED;
        if (distance>=thurst){
            thurst = distance; // avoid collision with planets
        }
        const hlt::possibly<hlt::Move> move =
                hlt::navigation::navigate_ship_to_dock(map, _ship, *planet, thurst);
        if (move.second) {
            moves.push_back(move.first);
            return true;
        }
    }
    return false;    
}

void Pilot::log(const std::string& message) {
    hlt::Log::output() << typeid(*this).name() << ", ship " << _ship.entity_id << ": " << message << std::endl;
}

bool Pilot::has_target() const {
    return (target_entity_id() >= 0);
}
