/* 
 * File:   Killer.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:32 PM
 */

#include "Killer.h"
#include "navigation.hpp"
#include "log.hpp"

Killer::Killer(const hlt::Ship& ship, const hlt::Entity& target)  : Pilot(ship), _target(target) {
    hlt::Log::output() << "Killer created, target: " << _target.entity_id << std::endl;
}

Killer::~Killer() {
    log("killer destroyed");
}

void Killer::play(const hlt::Map& map, hlt::Moves& moves) {
    if (_ship.in_docking_process()){
        moves.push_back(hlt::Move::undock(_ship.entity_id));
        return;
    }        
    if (!_target.is_alive()){
        const hlt::Ship* enemy_ship = find_nearest_enemy(map);
        if (enemy_ship==NULL){
            set_idle(moves);
            return;
        }
        _target = *enemy_ship;
    }
    move_to(map,_target.location,moves);    
}


int Killer::target_entity_id() const {
    return _target.entity_id;
}
