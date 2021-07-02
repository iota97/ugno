#include "Random.h"

static unsigned long next_ = 1;

unsigned int generaRandom() {
	next_ = (next_*1103515245 + 12345) % 32768;
	return next_;
}

void setRandomSeed(unsigned int seed) {
	next_ = seed % 32768;
}

unsigned int getRandomSeed() {
	return next_;
}
