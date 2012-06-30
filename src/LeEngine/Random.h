#ifndef RANDOM_H
#define RANDOM_H

#include <boost/random.hpp>
#include <ctime>
#include <iterator>

class Random
{
private:
    typedef boost::random::mt19937 GeneratorType;

    GeneratorType _gen;
    boost::random::uniform_01<GeneratorType, float>* _uniformDist01;

public:
    //! Constructor
    Random(int seed = clock());

    //! Destructor
    ~Random();

    //! Floating point value in the range [0, 1[
    float Unit();

    //! Floating point value in the range [-1, 1[
    float SymmetricUnit() { return Interval(-1.0f, 1.0f); }

    //! Floating point value in the range [min, max[
    float Interval(float min, float max);

    //! Value in the range [min, max[
    int Interval(int min, int max);

    //! Returns a value from <values>.
    //! Probabilities for each element should be defined in <probabilities>
    template<typename T>
    T Distribution(T* values, float* probabilities, int size)
    {
        boost::random::discrete_distribution<int, float> dist(probabilities, probabilities+size);
        int rand = dist(_gen);
        return values[rand];
    }

    //! Returns a value from <values>.
    //! Each element has the same probability of being picked.
    template<typename T>
    T Distribution(T* values, int size)
    {
        int rand = Interval(0, size);
        return values[rand];
    }

    //! Returns a value from the set.
    //! Each element has the same probability of being picked.
    template<class InputIterator>
    typename std::iterator_traits<InputIterator>::value_type
    Distribution(InputIterator begin, InputIterator end)
    {
        // This will work with any container that supports iterators
        // The only requirement is that the iterator must be
        // an input iterator (random or sequential)

        int size = std::distance(begin, end);
        int rand = Interval(0, size);
        std::advance(begin, rand);
        return *begin;
    }
};

#endif // RANDOM_H
