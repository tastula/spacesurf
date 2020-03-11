#ifndef SURF_DIALOGUE_HH
#define SURF_DIALOGUE_HH

#include "json.hpp"
#include "label.hh"
#include "object.hh"
#include <string>
#include <vector>

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
        int border_outer;
        int border_inner;
        int dia_w;
        int dia_h;
        int dia_x;
        int dia_y;
        int back_w;
        int back_h;
        int back_x;
        int back_y;
        int text_w;

        std::vector<std::string> lines;
        std::vector<Label> line_labels;
        json information;

        std::vector<std::string> split_text(const std::string& text, unsigned w);
};

#endif
