#include <vector>
#include "particles.h"
#include "init_conditions.h"
#include "forces.h"

int main(int argc, char *argv[]) {
	int N=20'000; // number of particles
	particles plist; // vector of particles
	ic(plist,N); // initialize starting position/velocity 
	forces(plist); // calculate the forces
	return 0;
}
