#include "Layer.h"

#include "Debug.h"


Layer::~Layer()
{
    while (Objects_.size() > 0)
    {
        delete Objects_.at(0);
        Objects_.erase(Objects_.begin());
    }
    //delete Texture_;
}



// void Layer::PrintDetails()
// {
//     Log_Line();
//     Debugger<DEBUG_LEVEL>::Log_Console("Printing Details...");
//     Debugger<DEBUG_LEVEL>::Log_Console("Position Count: ", (int)Positions_.size());
//     Debugger<DEBUG_LEVEL>::Log_Console("Indici Count: ", (int)Indices_.size());
//     Log_Line();

//     for (int i = 0; i < (int)Positions_.size(); i++)
//         Debugger<DEBUG_LEVEL>::Log_Console("POS ", i, ": ", Positions_.at(i));

//     for (int i = 0; i < (int)Indices_.size(); i++)
//         Debugger<DEBUG_LEVEL>::Log_Console("IND ", i, ": ", Indices_.at(i));

//     Log_Line();
// }
