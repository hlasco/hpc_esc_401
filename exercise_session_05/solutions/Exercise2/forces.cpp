#include "particles.h"
#include <cmath>
void forces(particles &plist) {
	int n = plist.size();
	for(int i=0; i<n; ++i) { // We want to calculate the force on all particles
		plist[i].ax = plist[i].ay = plist[i].az = 0; // start with zero acceleration
		for(int j=0; j<n; ++j) { // Depends on all other particles
			if (i==j) continue; // Skip self interaction 
        		auto dx = plist[j].x - plist[i].x;
			auto dy = plist[j].y - plist[i].y;
			auto dz = plist[j].z - plist[i].z;
			auto r = sqrt(dx*dx + dy*dy + dz*dz);
			auto ir3 = 1 / (r*r*r);
			plist[i].ax += dx * ir3;
			plist[i].ay += dy * ir3;
			plist[i].az += dz * ir3;
		} 
	}
}
