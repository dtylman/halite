#pragma once

#include "map.hpp"
#include "types.hpp"
#include "ship.hpp"
#include "planet.hpp"

namespace hlt {
    class Map {
    public:
        int map_width, map_height;

        std::unordered_map<PlayerId, std::vector<Ship>> ships;
        std::unordered_map<PlayerId, entity_map<unsigned int>> ship_map;

        std::vector<Planet> planets;
        entity_map<unsigned int> planet_map;

        Map(int width, int height);              
        
        bool entity_exists(EntityId id) const;
        bool get_ship_by_id(const EntityId ship_id, Ship& ship) const;
        bool get_planet_by_id(const EntityId planet_id, Planet& planet) const;
        
        size_t count_docking_ships(const PlayerId player_id, const EntityId planet_id) const;
     };
}
