#include "Layer.h"

#include "Debug.h"

Layer::~Layer()
{
    while (Objects_.size() > 0)
    {
        delete Objects_.at(0);
        Objects_.erase(Objects_.begin());
    }
}