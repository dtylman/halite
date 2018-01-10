/* 
 * File:   MyShips.h
 * Author: danny
 *
 * Created on January 8, 2018, 4:11 PM
 */

#ifndef MYSHIPS_H
#define MYSHIPS_H

#include "Pilot.h"
#include "hlt/hlt.hpp"

class EntitySorter {
public:

    enum SortType {
        Distance, Health
    };
    EntitySorter(SortType type, const hlt::Entity& source);
    EntitySorter(SortType type);
    ~EntitySorter();

    bool operator()(const hlt::Entity& target1, const hlt::Entity& target2);

    static std::vector<hlt::Planet> planets_by_distance(const hlt::Entity& source, const hlt::Map& map);
    static std::vector<hlt::Planet> planets_by_health(const hlt::Map& map);
private:
    SortType _type;
    hlt::Location _source;
};

class MyPilots {
public:
    static MyPilots& instance();
    static void init(const hlt::Metadata& metadata);

    void populate(const hlt::Map& map);
    void play(const hlt::Map& map, hlt::Moves& moves);

private:
    bool update_ship(const hlt::Ship& ship);
    void create_pilot(const hlt::Ship& ship, const hlt::Map& map);
    bool create_docker_pilot(const hlt::Ship& ship, const hlt::Map& map);
    bool create_dodger_pilot(const hlt::Ship& ship, const hlt::Map& map);
    bool create_killer_pilot(const hlt::Ship& ship, const hlt::Map& map);
    void delete_pilot(Pilot* pilot);
    /// returns true if entity is targeted by any of our ships
    bool entity_targeted(const hlt::Entity& entity) const;

    template <class T> unsigned int count_pilots() const ;


    static MyPilots* _instance;
    MyPilots(const hlt::Metadata& metadata);
    ~MyPilots();

    std::vector<Pilot*> _pilots;
    const hlt::Metadata& _metadata;
};


#endif /* MYSHIPS_H */

