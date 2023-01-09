#include "Object.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Debug.h"

Object::Object(std::string filepath, unsigned int tex_id, float xpos, float ypos, float zpos, float scale)
    :   textureId_(tex_id), m_xpos(xpos), m_ypos(ypos), m_zpos(zpos), m_scale(scale)
{
    Debugger::Log_Console("Constructing Object: ", filepath);
    LoadObjectFromOBJ(filepath);
    UpdatePos();
    PrintAll();
}

Object::~Object()
{
}

//Reads an obj file line by line to fill our vertices, texture vertices, and indices
void Object::LoadObjectFromOBJ(std::string filepath)
{
    std::ifstream inFile (filepath);
    std::string line;

    while( getline(inFile, line) ) 
    {
        //Debugger::Log_Console(line);
        //evaulate line and pull out data into sVec then assign xyz values to our points
        std::string sVec;
        Point point;
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
            m_Points.push_back(point);
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
            m_TexturePoints.push_back(point);
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
                                m_Indices.push_back((unsigned int)std::stoul(sIndici) - 1);
                            if(iIniciIndex == 1)
                                m_TextureIndices.push_back((unsigned int)std::stoul(sIndici) - 1);
                            
                            
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

void Object::UpdatePosition(float xpos, float ypos, float zpos) 
{
    Debugger::Log_Console("Updating OBJECT position: x-", m_xpos, ", y-", m_ypos, ", z-", m_zpos);
    Debugger::Log_Console("Updating OBJECT position: x-", xpos, ", y-", ypos, ", z-", zpos);
    m_xpos += xpos; m_ypos += ypos; m_zpos = zpos;
    Debugger::Log_Console("Updating OBJECT position: x-", m_xpos, ", y-", m_ypos, ", z-", m_zpos);
    UpdatePos();
}


void Object::UpdatePos()
{
    PrintVertices();
    for(int i = 0; i < (int)m_Points.size(); i++)
    { 
        // m_Points.at(i).x = (m_Points.at(i).x *= m_scale) + m_xpos;
        // m_Points.at(i).y = (m_Points.at(i).y *= m_scale) + m_ypos;
        // m_Points.at(i).z = (m_Points.at(i).z *= m_scale) + m_zpos;

        m_Points.at(i).x += m_xpos;
        m_Points.at(i).y += m_ypos;
        m_Points.at(i).z += m_zpos;

        PrintVertices();
    }
    PrintVertices();
}

unsigned int Object::GetVertexBufferData(std::vector<float>& vertex_buffer)
{    
    for (int i = 0; i < (int)m_Points.size(); i++)
    {
        vertex_buffer.push_back(m_Points.at(i).x);
        vertex_buffer.push_back(m_Points.at(i).y);
        vertex_buffer.push_back(m_Points.at(i).z);

        vertex_buffer.push_back(m_TexturePoints.at(i).x);
        vertex_buffer.push_back(m_TexturePoints.at(i).y);

        vertex_buffer.push_back(textureId_);

    }
    return m_Points.size();
    
}

unsigned int Object::GetIndiciBufferData(std::vector<unsigned int>& index_buffer, unsigned int start)
{
    for(int i = 0; i < (int)m_Indices.size(); i++)
        index_buffer.push_back( m_Indices.at(i) + start);

    return m_Indices.size();   
}



//////////////////////////////////////////////////////////////////
//  Debug Helpers
//////////////////////////////////////////////////////////////////

const void Object::PrintAll()
{
    PrintVertices();
    Debugger::Log_Line();
    PrintTextureVertices();
    Debugger::Log_Line();
    PrintIndices();
    Debugger::Log_Line();
    PrintTextureIndices();
}

const void Object::PrintVertices()
{
    Debugger::Log_Console("Position Vertices:");
    for(int i = 0; i < (int)m_Points.size(); i++)
    {
        Debugger::Log_Console("v ", i, ": (",
        m_Points.at(i).x, ",",  
        m_Points.at(i).y, ",",  
        m_Points.at(i).z, ")");
    }
}

const void Object::PrintTextureVertices()
{
    Debugger::Log_Console("Texture Vertices:");
    for(int i = 0; i < (int)m_TexturePoints.size(); i++)
    {
        Debugger::Log_Console("vt ",i, ": (",
        m_TexturePoints.at(i).x, ",",
        m_TexturePoints.at(i).y, ")");  
        
    }
}

const void Object::PrintIndices()
{
    Debugger::Log_Console("Posistion Indicis:");
    for(int i = 0; i < (int)m_Indices.size(); i++)
        Debugger::Log_Console(i, ": ", m_Indices.at(i));
}

const void Object::PrintTextureIndices()
{
    Debugger::Log_Console("Texture Indicis:");
        for(int i = 0; i < (int)m_TextureIndices.size(); i++)
            Debugger::Log_Console(i, ": ", m_TextureIndices.at(i));
}