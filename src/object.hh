#ifndef SURF_OBJECT_HH
#define SURF_OBJECT_HH

class Resources;

class Object
{
    public:
        Object(Resources &res);
        virtual ~Object();

        void add_position(float dx, float dy, float dz = 0);
        void add_velocity(float dx, float dy);
        void set_position(float nx, float ny, float nz = 0);
        void set_velocity(float nx, float ny);

        float get_px();
        float get_py();
        float get_vx();
        float get_vy();
        int get_w();
        int get_h();

    protected:
        Resources& res;
        float px;
        float py;
        float pz;
        float vx;
        float vy;
        int w;
        int h;
};

#endif // SURF_OBJECT_HH
