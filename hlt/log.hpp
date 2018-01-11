#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace hlt {
    struct Log {
    private:
        std::ofstream file;
        
        void initialize(const std::string& filename) {
            file.open(filename, std::ios::trunc | std::ios::out);
        }

    public:
        static std::string file_name;
        
        static Log& get() {
            static Log instance{};            
            return instance;
        }

        static void open(const std::string& filename) {
            get().initialize(filename);
            file_name = filename;
        }

        static void log(const std::string& message) {
            get().file << message << std::endl;
        }
        
        static std::ofstream& output() {
            return get().file;
        }                
    };
}
