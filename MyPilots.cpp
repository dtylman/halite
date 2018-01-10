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
#include "Dodger.h"

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
        //hlt::Log::output() << " looking for ship " << pilot->ship().entity_id << std::endl;
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

bool MyPilots::create_docker_pilot(const hlt::Ship& ship, const hlt::Map& map) {
    std::vector<hlt::Planet> planets = EntitySorter::planets_by_distance(ship, map);
    // add target planet for any planet not owned.       
    for (auto planet : planets) {
        if ((!planet.owned) && (!entity_targeted(planet))) {
            _pilots.push_back(new Docker(ship, planet));
            return true;
        }
    }
    return false;
}

template<class T>
unsigned int MyPilots::count_pilots() const {
    unsigned int count = 0;
    for (Pilot* pilot : _pilots) {
        T* p = dynamic_cast<T*> (pilot);
        if (p != NULL) {
            count++;
        }
    }
    return count;
}

bool MyPilots::create_dodger_pilot(const hlt::Ship& ship, const hlt::Map& map) {
    if (count_pilots<Dodger>() > 0) {
        return false;
    }
    _pilots.push_back(new Dodger(ship));
    return true;
}

bool MyPilots::create_killer_pilot(const hlt::Ship& ship, const hlt::Map& map) {
    if (count_pilots<Killer>() > map.planets.size() * 2) {
        return false;
    }
    std::vector<hlt::Planet> planets = EntitySorter::planets_by_health(map);
    for (auto planet : planets) {
        if (planet.owner_id != _metadata.player_id) {
            _pilots.push_back(new Killer(ship, planet));
            return true;
        }
    }
    return false;
}

void MyPilots::create_pilot(const hlt::Ship& ship, const hlt::Map& map) {
    if (create_docker_pilot(ship, map)) {
        return;
    }
    if (create_dodger_pilot(ship, map)) {
        return;
    }
    if (create_killer_pilot(ship, map)) {
        return;
    }
    // default: create kof pilot
    _pilots.push_back(new Kof(ship));
}

void MyPilots::play(const hlt::Map& map, hlt::Moves& moves) {
    for (auto s : _pilots) {
        s->play(map, moves);
    }
}

hlt::possibly<hlt::Planet> MyPilots::best_enemry_planet(const hlt::Map& map) {
    std::vector<hlt::Planet> planets = EntitySorter::planets_by_radius(map);
    for (auto planet : planets) {
        if ((planet.owned) && (planet.owner_id != _metadata.player_id)) { //not my planet 
            return {planet, true};
        }
    }
    return {hlt::Planet(), false};
}

void MyPilots::analyze_turn(const hlt::Map& map) {
    std::vector<Pilot*> idle_pilots;
    for (auto pilot : _pilots) {
        if (pilot->idle()) {
            idle_pilots.push_back(pilot);
        }
    }
    hlt::possibly<hlt::Planet> planet = best_enemry_planet(map);
    if (planet.second) {
        for (auto pilot : idle_pilots) {
            _pilots.push_back(new Docker(pilot->ship(), planet.first));
            delete_pilot(pilot);            
        }
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
    if (_type == DistanceASC) {
        double distance1 = entity1.location.get_distance_to(_source);
        double distance2 = entitiy2.location.get_distance_to(_source);
        return distance1<distance2;
    } else if (_type == HealthASC) {
        return entity1.health < entitiy2.health;
    } else if (_type == RadiusDSC) {
        return entity1.radius > entitiy2.radius;
    } else {
        hlt::Log::log("Warning!! sorting by unknown type!!!");
        return entity1.radius < entitiy2.radius;
    }
}

EntitySorter::~EntitySorter() {

}

std::vector<hlt::Planet> EntitySorter::planets_by_distance(const hlt::Entity& source, const hlt::Map& map) {
    std::vector<hlt::Planet> planets = map.planets;
    std::sort(planets.begin(), planets.end(), EntitySorter(SortType::DistanceASC, source));
    return planets;
}

std::vector<hlt::Planet> EntitySorter::planets_by_health(const hlt::Map& map) {
    std::vector<hlt::Planet> planets = map.planets;
    std::sort(planets.begin(), planets.end(), EntitySorter(SortType::HealthASC));
    return planets;
}

std::vector<hlt::Planet> EntitySorter::planets_by_radius(const hlt::Map& map) {
    std::vector<hlt::Planet> planets = map.planets;
    std::sort(planets.begin(), planets.end(), EntitySorter(SortType::RadiusDSC));
    return planets;
}

bool MyPilots::entity_targeted(const hlt::Entity& entity) const {
    for (Pilot* pilot : _pilots) {
        Docker* docker = dynamic_cast<Docker*> (pilot);
        if (docker != NULL) {
            if (docker->target_entity_id() == (int) entity.entity_id) {
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
