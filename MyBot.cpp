#include <unistd.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>

#include "hlt/hlt.hpp"
#include "hlt/navigation.hpp"
#include "Pilot.h"
#include "MyPilots.h"

#define BOT_NAME "shablool"

std::string hlt::Log::file_name;

void signal_handler(int sig) {
    void *array[20];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 20);

    int fd = open(hlt::Log::file_name.c_str(), O_WRONLY | O_APPEND);
    backtrace_symbols_fd(array, size, fd);
    close(fd);
    exit(1);
}

int main() {
    signal(SIGSEGV, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGTERM, signal_handler);

    const hlt::Metadata metadata = hlt::initialize(BOT_NAME);
    MyPilots::init(metadata);
    const hlt::PlayerId player_id = metadata.player_id;
    const hlt::Map& initial_map = metadata.initial_map;

    // We now have 1 full minute to analyze the initial map.
    std::ostringstream initial_map_intelligence;
    initial_map_intelligence
            << "width: " << initial_map.map_width
            << "; height: " << initial_map.map_height
            << "; players: " << initial_map.ship_map.size()
            << "; my ships: " << initial_map.ship_map.at(player_id).size()
            << "; planets: " << initial_map.planets.size();
    hlt::Log::log(initial_map_intelligence.str());

    hlt::Moves moves;

    for (;;) {
        try {
            moves.clear();
            const hlt::Map map = hlt::in::get_map();
            MyPilots::instance().populate(map);
            MyPilots::instance().play(map, moves);

            if (!hlt::out::send_moves(moves)) {
                hlt::Log::log("send_moves failed; exiting");
                break;
            }
            MyPilots::instance().analyze_turn(map);
        } catch (std::exception& ex) {
            hlt::Log::log(ex.what());
        }
    }
}
