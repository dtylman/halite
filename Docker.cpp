/* 
 * File:   Docker.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:32 PM
 */

#include "Docker.h"
#include "log.hpp"
#include "MyPilots.h"
#include "navigation.hpp"

Docker::Docker(const hlt::Ship& ship, const hlt::Planet& target) : Pilot(ship), _target(target) {
    hlt::Log::output() << "created docker: ship: "
            << ship.entity_id << ", distance to planet: " << target.location.get_distance_to(ship.location) << std::endl;
}

Docker::~Docker() {
    log("docker deleted");
}

void Docker::play(const hlt::Map& map, hlt::Moves& moves) {
    if (_ship.in_docking_process()) {
        return;
    }

    // if some other ship is docking, kill it!
    if (_target.owned && _target.owner_id != _ship.owner_id) { //not mine
        std::vector<hlt::EntityId> docked_ships = map.get_planet(_target.entity_id).docked_ships;
        for (auto ship_id : docked_ships) {
            hlt::Ship enemy_ship;
            if (map.get_ship_by_id(ship_id, enemy_ship)) {
                if (enemy_ship.owner_id != _ship.owner_id) { // just making sure
                    move_to(map, enemy_ship.location, moves); //try to kill other ship;
                    return;
                }
            }
        }
    }

    if (_ship.can_dock(_target)) {
        moves.push_back(hlt::Move::dock(_ship.entity_id, _target.entity_id));
        return;
    }
    hlt::possibly<hlt::Move> move = hlt::navigation::navigate_ship_to_dock(map, _ship, _target, hlt::constants::MAX_SPEED);
    if (move.second) {
        moves.push_back(move.first);
        return;
    }
    stop_moving(moves);
}

//bool Docker::can_play(const hlt::Map& map) {
//    return (_target.owner_id==_ship.owner_id || !_target.owned);
//}

int Docker::target_entity_id() const {
    return _target.entity_id;
}
