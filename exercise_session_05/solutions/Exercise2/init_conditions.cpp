#include <random>
#include "particles.h"
// Initial conditions
void ic(particles &plist, int n) {
	std::random_device rd; //Will be used to obtain a seed for the random number engine 
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd() 
	std::uniform_real_distribution<float> dis(0.0, 1.0);

	plist.clear(); // Remove all particles 
	plist.reserve(n); // Make room for "n" particle 
	for( auto i=0; i<n; ++i) {
		particle p { dis(gen),dis(gen),dis(gen),0,0,0,0,0,0 };
		plist.push_back(p); 
	}
}
