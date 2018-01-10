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

        const Ship& get_ship(const PlayerId player_id, const EntityId ship_id) const;

        const Planet& get_planet(const EntityId planet_id) const;
        
        bool entity_exists(EntityId id) const;
        bool get_ship_by_id(const EntityId ship_id, Ship& ship) const;
     };
}
