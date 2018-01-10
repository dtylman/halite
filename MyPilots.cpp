/* 
 * File:   MyShips.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 4:11 PM
 */

#include <algorithm>
#include <csignal>

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
    // add pilots to new ships
    for (const hlt::Ship& ship : map.ships.at(_metadata.player_id)) {
        if (!update_ship(ship)) {
            create_pilot(ship, map);
        }
    }
    
    //remove all pilots for destroyed ships:
    std::vector<Pilot*> dead;
    for (auto pilot : _pilots) {
        hlt::Log::output() << " looking for ship " << pilot->ship().entity_id << std::endl;
        if (!map.entity_exists(pilot->ship().entity_id)) {
            dead.push_back(pilot);
        }
    }
    hlt::Log::output() << "found " << dead.size() << " dead pilots " << std::endl;
    for (auto pilot : dead) {
       delete_pilot(pilot);
    }
}

bool MyPilots::update_ship(const hlt::Ship& ship) {
    for (auto s : _pilots) {
        if (s->ship().entity_id == ship.entity_id) {
            s->update_ship(ship);
            return true;
        }
    }
    return false;
}

void MyPilots::create_pilot(const hlt::Ship& ship, const hlt::Map& map) {
    std::vector<hlt::Planet> planets = EntitySorter::planets_by_distance(ship, map);
    // add target planet for any planet not owned.       
    for (auto planet : planets) {
        if ((!planet.owned) && (!entity_targeted(planet))) {
            _pilots.push_back(new Docker(ship, planet));
            return;
        }
    }    
    // adds killers and kofs
    if ((rand() % 2) == 0) {
        _pilots.push_back(new Kof(ship));
    } else {
        _pilots.push_back(new Killer(ship));
    }
}

void MyPilots::play(const hlt::Map& map, hlt::Moves& moves) {
    for (auto s : _pilots) {        
        s->play(map, moves);
    }
}

void MyPilots::init(const hlt::Metadata& metadata) {
    _instance = new MyPilots(metadata);
}

MyPilots& MyPilots::instance() {
    return *_instance;
}

EntitySorter::EntitySorter(SortType type) : _type(type) {

}

EntitySorter::EntitySorter(SortType type, const hlt::Entity& source) : _type(type) {
    _source = source.location;
}

bool EntitySorter::operator()(const hlt::Entity& entity1, const hlt::Entity& entitiy2) {
    if (_type == Distance) {
        double distance1 = entity1.location.get_distance_to(_source);
        double distance2 = entitiy2.location.get_distance_to(_source);
        return distance1<distance2;
    } else if (_type == Health) {
        return entity1.health < entitiy2.health;
    } else {
        hlt::Log::log("Warning!! sorting by unknown type!!!");
        return entity1.radius < entitiy2.radius;
    }
}

EntitySorter::~EntitySorter() {

}

std::vector<hlt::Planet> EntitySorter::planets_by_distance(const hlt::Entity& source, const hlt::Map& map) {
    std::vector<hlt::Planet> planets = map.planets;
    std::sort(planets.begin(), planets.end(), EntitySorter(SortType::Distance, source));
    return planets;
}

std::vector<hlt::Planet> EntitySorter::planets_by_health(const hlt::Map& map) {
    std::vector<hlt::Planet> planets = map.planets;
    std::sort(planets.begin(), planets.end(), EntitySorter(SortType::Health));
    return planets;
}

bool MyPilots::entity_targeted(const hlt::Entity& entity) const {
    for (Pilot* pilot : _pilots) {
        Docker* docker = dynamic_cast<Docker*> (pilot);
        if (docker != NULL) {
            if (docker->ship().entity_id == entity.entity_id) {
                return true;
            }
        }        
    }
    return false;
}

void MyPilots::delete_pilot(Pilot* pilot) {    
    hlt::Log::output() << "removing pilot " << pilot->ship().entity_id << std::endl;
    _pilots.erase(std::remove(_pilots.begin(), _pilots.end(), pilot));
    delete pilot;
}
