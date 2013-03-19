#include "Random.h"

Random::Random(int seed)
{
    _gen = GeneratorType(seed);
    _uniformDist01 = NULL;
}

Random::Random()
{
    std::random_device rd;
    _gen = GeneratorType(rd());
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
        _uniformDist01 = new std::uniform_real_distribution<float>(0.0f, 1.0f);
    return (*_uniformDist01)(_gen);
}

float Random::Interval(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(_gen);
}

int Random::Interval(int min, int max)
{
    std::uniform_int_distribution<> dist(min, max - 1);
    return dist(_gen);
}
