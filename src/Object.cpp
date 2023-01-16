#include "Object.h"

#include <iostream>
#include <fstream>
#include <sstream>



Object::Object(std::string filepath, unsigned int tex_id, glm::vec3 position)
    :   ObjFilepath_(filepath), textureId_(tex_id), Position_(position)
{
    Debugger<DEBUG_LEVEL>::Log_Console("Constructing Object: ", filepath);
    LoadObjectFromOBJ(filepath);
    PrintAll();
}

Object::~Object()
{
}

unsigned int Object::GetVertexBufferData(std::vector<float>& vertex_buffer)
{    
    for (int i = 0; i < (int)Vertices_.size(); i++)
    {
        vertex_buffer.push_back(Vertices_.at(i).x + Position_.x);
        vertex_buffer.push_back(Vertices_.at(i).y + Position_.y);
        vertex_buffer.push_back(Vertices_.at(i).z + Position_.z);

        vertex_buffer.push_back(TextureVerticies_.at(i).x);
        vertex_buffer.push_back(TextureVerticies_.at(i).y);

        vertex_buffer.push_back(textureId_);

    }
    return Vertices_.size();
    
}

unsigned int Object::GetIndiciBufferData(std::vector<unsigned int>& index_buffer, unsigned int start)
{
    for(int i = 0; i < (int)Indices_.size(); i++)
        index_buffer.push_back( Indices_.at(i) + start);

    return Indices_.size();   
}

//Reads an obj file line by line to fill our vertices, texture vertices, and indices
void Object::LoadObjectFromOBJ(std::string& filepath)
{

    std::ifstream inFile (filepath);
    std::string line;

    while( getline(inFile, line) ) 
    {
        //Debugger<DEBUG_LEVEL>::Log_Console(line);
        //evaulate line and pull out data into sVec then assign xyz values to our points
        std::string sVec;
        glm::vec3 point;
        int xyz = 0;

        std::string start;
        start += line.at(0);
        start += line.at(1);
        if(start == "v ")
        {
            int iter = 2;//start at the 3rd char (v ) will always be first... right
            for(; iter < (int)line.length(); iter++)
            {
                //note - looks like the line ends with a ' '
                if(line.at(iter) == ' ' || iter == (int)line.length() - 1)
                {
                    if (iter == (int)line.length() - 1)
                        sVec += line.at(iter);

                    if(xyz == 0)
                        point.x = std::stof(sVec);
                    else if(xyz == 1)
                        point.y = std::stof(sVec);
                    else
                        point.z = std::stof(sVec);

                    xyz == 2 ? xyz = 0 : xyz++;
                    sVec = "";
                }  
                else
                    sVec += line.at(iter);
            }
            //done with the line add our point to our points
            Vertices_.push_back(point);
        }
        else if(start == "vt")
        {
            int iter = 3;//start at the 4th char (vt ) will always be first... right
            xyz = 0;
            sVec = "";

            for(; iter < (int)line.length(); iter++)
            {
                //note - looks like the line ends with a ' '
                if(line.at(iter) == ' ' || iter == (int)line.length() - 1)
                {
                    if (iter == (int)line.length() - 1)
                        sVec += line.at(iter);

                    if(xyz == 0)
                        point.x = std::stof(sVec);
                    else if(xyz == 1)
                        point.y = std::stof(sVec);
                    
                    (xyz == 1) ? xyz = 0 : xyz++;
                    sVec = "";
                }  
                else
                    sVec += line.at(iter);
            }
            //done with the line add our point to the
            TextureVerticies_.push_back(point);
        }
        else if(start == "f ")
        {
            int iter = 2;//start at the 3rd char (f ) will always be first... right
            std::string sIndiciTuple;
            bool bGotFirst = false;//INDICIS COME IN TUPLES WE ONLY WANT FIRST & SECOND VAL ATM
            for(; iter < (int)line.length() || bGotFirst; iter++)
            {
                if (iter == (int)line.length() - 1 || line.at(iter) == ' ')
                {
                    if(iter == (int)line.length() - 1)
                        sIndiciTuple += line.at(iter);

                    std::string sIndici;
                    int iIniciIndex = 0;//0 = vetex index, 1 = texture vertex index, 2 = vertex normal index
                    for(int i = 0; i < (int)sIndiciTuple.size(); i++)
                    {
                        if(sIndiciTuple.at(i) == '/' || i == (int)sIndiciTuple.size() - 1)
                        {
                            if(iIniciIndex == 0)
                                Indices_.push_back((unsigned int)std::stoul(sIndici) - 1);
                            if(iIniciIndex == 1)
                                TextureIndices_.push_back((unsigned int)std::stoul(sIndici) - 1);
                            
                            
                            sIndici = "";
                            iIniciIndex++;
                            if(iIniciIndex == 3)
                            {
                                iIniciIndex = 0;
                                sIndiciTuple = "";
                            }
                        }
                        else
                            sIndici += sIndiciTuple.at(i);   
                    }
                }
                else
                    sIndiciTuple += line.at(iter);
                
            }
        }
    }    
}

//////////////////////////////////////////////////////////////////
//  Debug Helpers
//////////////////////////////////////////////////////////////////

const void Object::PrintAll()
{
    PrintVertices();
    Debugger<DEBUG_LEVEL>::Log_Line();
    PrintTextureVertices();
    Debugger<DEBUG_LEVEL>::Log_Line();
    PrintIndices();
    Debugger<DEBUG_LEVEL>::Log_Line();
    PrintTextureIndices();
}

const void Object::PrintVertices()
{
    Debugger<DEBUG_LEVEL>::Log_Console("Position Vertices:");
    for(int i = 0; i < (int)Vertices_.size(); i++)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("v ", i, ": (",
        Vertices_.at(i).x, ",",  
        Vertices_.at(i).y, ",",  
        Vertices_.at(i).z, ")");
    }
}

const void Object::PrintTextureVertices()
{
    Debugger<DEBUG_LEVEL>::Log_Console("Texture Vertices:");
    for(int i = 0; i < (int)TextureVerticies_.size(); i++)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("vt ",i, ": (",
        TextureVerticies_.at(i).x, ",",
        TextureVerticies_.at(i).y, ")");   
    }
}

const void Object::PrintIndices()
{
    Debugger<DEBUG_LEVEL>::Log_Console("Posistion Indicis:");
    for(int i = 0; i < (int)Indices_.size(); i++)
        Debugger<DEBUG_LEVEL>::Log_Console(i, ": ", Indices_.at(i));
}

const void Object::PrintTextureIndices()
{
    Debugger<DEBUG_LEVEL>::Log_Console("Texture Indicis:");
        for(int i = 0; i < (int)TextureIndices_.size(); i++)
            Debugger<DEBUG_LEVEL>::Log_Console(i, ": ", TextureIndices_.at(i));
}