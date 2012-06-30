#include "Random.h"
#include <boost/random.hpp>

Random::Random(int seed /*= clock()*/)
{
    _gen = GeneratorType(seed);
    _uniformDist01 = NULL;
}

Random::~Random()
{
    if (_uniformDist01)
        delete _uniformDist01;
}

float Random::Unit()
{
    if (!_uniformDist01)
        _uniformDist01 = new boost::random::uniform_01<GeneratorType, float>(_gen);
    return (*_uniformDist01)();
}

float Random::Interval(float min, float max)
{
    boost::random::uniform_real_distribution<float> dist(min, max);
    return dist(_gen);
}

int Random::Interval(int min, int max)
{
    boost::random::uniform_int_distribution<> dist(min, max - 1); // uniform_int is [min, max]
    return dist(_gen);
}
