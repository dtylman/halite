/* 
 * File:   MyShips.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 4:11 PM
 */

#include <algorithm>

#include "MyPilots.h"
#include "Docker.h"
#include "Kof.h"
#include "Killer.h"

MyPilots* MyPilots::_instance = NULL;

MyPilots::MyPilots(const hlt::Metadata& metadata) : _metadata(metadata) {

}

MyPilots::~MyPilots() {
}

void MyPilots::populate(const hlt::Map& map) {
    for (const hlt::Ship& ship : map.ships.at(_metadata.player_id)) {
        if (!update_ship(ship)) {
            add_ship(ship,map);
        }
    }
}

bool MyPilots::update_ship(const hlt::Ship& halite_ship) {
    for (auto s : _ships) {
        if (s->ship().entity_id == halite_ship.entity_id) {
            s->set_ship(halite_ship);
            return true;
        }
    }
    return false;
}

void MyPilots::add_ship(const hlt::Ship& ship, const hlt::Map& map) {
    // add target planet for any planet not owned.    
    std::vector<hlt::Planet> planets = map.planets;
    std::sort(planets.begin(),planets.end(),DistanceSorter(ship));
    for(auto planet : planets){
        if(!planet.owned) {
            _ships.push_back(new Docker(ship,planet));
            return;
        }
    }
    // adds killers and kofs
    if ((rand()%2)==0){
        _ships.push_back(new Killer(ship));    
    } else {
        _ships.push_back(new Kof(ship));
    }
}

void MyPilots::play(const hlt::Map& map, hlt::Moves& moves) {
    for (auto s: _ships){
        s->play(map,moves);        
    }    
}

void MyPilots::init(const hlt::Metadata& metadata) {
    _instance = new MyPilots(metadata);
}

MyPilots& MyPilots::instance() {
    return *_instance;
}

DistanceSorter::DistanceSorter(const hlt::Entity& source) : _source(source) {

}

bool DistanceSorter::operator()(const hlt::Entity& target1, const hlt::Entity& target2) {
    double distance1 = target1.location.get_distance_to(_source.location);
    double distance2 = target2.location.get_distance_to(_source.location);
    return distance1<distance2;
}

DistanceSorter::~DistanceSorter() {

}

bool MyPilots::entity_targeted(const hlt::Entity& entity) const {
    for (auto )
}
