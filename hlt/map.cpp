#include "map.hpp"
#include "log.hpp"

using namespace hlt;

Map::Map(const int width, const int height) : map_width(width), map_height(height) {
}

bool Map::entity_exists(EntityId id) const {
    for (auto sc : ships) {
        for (auto s : sc.second) {
            //        hlt::Log::output() << "Looking for " << id << " found " << s.entity_id << std::endl;
            if (s.entity_id == id) {
                return true;
            }
        }
    }
    for (auto p : planets) {
        //    hlt::Log::output() << "Looking for " << id << " found " << p.entity_id << std::endl;
        if (p.entity_id == id) {
            return true;
        }
    }
    //hlt::Log::output() << "Not found" << std::endl;
    return false;
}

bool Map::get_planet_by_id(const EntityId planet_id, Planet& planet) const {
    for (auto p : planets){
        if (p.entity_id==planet_id){
            planet = p;
            return true;
        }
    }
    return false;
}

bool Map::get_ship_by_id(const EntityId ship_id, Ship& ship) const {
    for (auto sc : ships) {
        for (auto s : sc.second) {
            if (s.entity_id == ship_id) {
                ship = s;
                return true;
            }
        }
    }
    return false;
}

