/* 
 * File:   Docker.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:32 PM
 */

#include "Docker.h"
#include "log.hpp"
#include "MyPilots.h"

Docker::Docker(const hlt::Ship& ship, const hlt::Planet& target) : Pilot(ship), _target(target) {        
    hlt::Log::output() << "created docker, distance to planet: " << target.location.get_distance_to(ship.location) << std::endl;    
}

Docker::~Docker() {
    hlt::Log::log("docker deleted");
}

void Docker::play(const hlt::Map& map, hlt::Moves& moves) {    
    if (_ship.in_docking_process()){
        return;
    }
    if (_target.owned) {
        MyPilots::instance().delete_pilot(this);
        return;
    }   
    if (_ship.can_dock(_target)){
        moves.push_back(hlt::Move::dock(_ship.entity_id, _target.entity_id));
        return;
    }
    move_towards(map,_target.location,moves);
}

