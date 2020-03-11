#ifndef SURF_DIALOGUE_HH
#define SURF_DIALOGUE_HH

#include "json.hpp"
#include "label.hh"
#include "object.hh"
#include "clock.hh"
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

        void input();
        void update(float delta);
        void draw();

        bool is_read();
        
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

        bool all_displayed;

        std::vector<std::string> lines;
        std::vector<Label> line_labels;
        json information;

        Clock indicator;
        bool display_indicator;

        std::vector<std::string> split_text(const std::string& text, unsigned w);
};

#endif
