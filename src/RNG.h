#include <random>

class RNG
{
public:
    static inline int GetRandInt(int min, int max)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [1, 6]

        
        return dist(rng);
    }

    static inline int GetRandFloat(float min, float max)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<float> dist(min, max);

        return dist(rng);
    }
};