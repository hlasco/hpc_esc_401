#ifndef _PARTICLES
#define _PARTICLES

#include <vector>
struct particle {
        float x, y, z; // position 
        float vx, vy, vz; // velocity 
        float ax, ay, az; // acceleration
};

typedef std::vector<particle> particles;

#endif
