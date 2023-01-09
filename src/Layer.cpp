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
//     Debugger::Log_Line();
//     Debugger::Log_Console("Printing Details...");
//     Debugger::Log_Console("Position Count: ", (int)Positions_.size());
//     Debugger::Log_Console("Indici Count: ", (int)Indices_.size());
//     Debugger::Log_Line();

//     for (int i = 0; i < (int)Positions_.size(); i++)
//         Debugger::Log_Console("POS ", i, ": ", Positions_.at(i));

//     for (int i = 0; i < (int)Indices_.size(); i++)
//         Debugger::Log_Console("IND ", i, ": ", Indices_.at(i));

//     Debugger::Log_Line();
// }
