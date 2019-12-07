#ifndef SURF_DIALOGUE_HH
#define SURF_DIALOGUE_HH

#include "json.hpp"
#include "label.hh"
#include "object.hh"
#include <string>

class Object;
class Resources;

using json = nlohmann::json;

class Dialogue: public Object
{
    public:
        Dialogue(Resources& res, std::string path);
        ~Dialogue();

        void draw();
        void update(float delta);
        
    private:
        Label text;
        json information;
};

#endif
