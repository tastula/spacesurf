#ifndef SURF_LEVELINFO_HH
#define SURF_LEVELINFO_HH

#include <fstream>
#include <map>
#include <string>


// Load level information from file to this struct
struct LevelInfo
{
    // Length of the level (seconds)
    unsigned length;
    // Minimum time between spawns (milliseconds)
    unsigned spawn_min;
    // Maximum time between spawns (milliseconds)
    unsigned spawn_max;
};

// Load level information from given path
LevelInfo load_level(std::string path)
{
    std::ifstream infile(path);
    std::string field;
    unsigned value;
    std::map<std::string, unsigned> fields;

    while(infile >> field >> value) fields[field] = value;

    LevelInfo level;
    level.length = fields.count("length") ? fields["length"] : 30;
    level.spawn_min = fields.count("spawn_min") ? fields["spawn_min"] : 300;
    level.spawn_max = fields.count("spawn_max") ? fields["spawn_max"] : 300;
    return level;
}

#endif
