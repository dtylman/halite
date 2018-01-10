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

class DistanceSorter
{
public:
    DistanceSorter(const hlt::Entity& source);
    ~DistanceSorter();
    
    bool operator() (const hlt::Entity& target1, const hlt::Entity& target2);    
private:
    const hlt::Entity& _source;
};


class MyPilots {
public:        
    static MyPilots& instance();
    static void init(const hlt::Metadata& metadata);
    
    void populate(const hlt::Map& map);
    void play(const hlt::Map& map, hlt::Moves& moves);    
    
    bool update_ship(const hlt::Ship& ship);
    void add_ship(const hlt::Ship& ship, const hlt::Map& map);
    
    /// returns true if entity is targeted by any of our ships
    bool entity_targeted(const hlt::Entity& entity) const;
private:        
    static MyPilots* _instance;
    MyPilots(const hlt::Metadata& metadata);    
    ~MyPilots();

    std::vector<Pilot*> _ships;
    const hlt::Metadata& _metadata;    
};


#endif /* MYSHIPS_H */

