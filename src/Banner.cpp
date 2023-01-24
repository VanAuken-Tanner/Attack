#include "Banner.h"


//this lines up with the abz_font.png texture sheet
//need space and apostrophe
enum lval{
    a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
    zero,one,two,three,four,five,six,seven,eight,nine,
    period,exclamation,question,comma,
    num_symbols
};

Banner::Banner()
    :   Banner_(TEXTURE_LAYER::MENU),
        Text_(TEXTURE_LAYER::TEXT)
{
    Banner_.Objects_.push_back(new GameObject("res/models/Banner.obj",TEXTURE_LAYER::MENU, {0.0f,0.0f,0.0f}));

}

glm::vec2 Banner::GetTextureCoords(char val)
{

    switch (val)
    {
        case 'a': return (glm::vec2)lval::a * text_coord_offset_;
        case 'b': return (glm::vec2)lval::b * text_coord_offset_;
        case 'c': return (glm::vec2)lval::c * text_coord_offset_;
        case 'd': return (glm::vec2)lval::d * text_coord_offset_;
        case 'e': return (glm::vec2)lval::e * text_coord_offset_;
        case 'f': return (glm::vec2)lval::f * text_coord_offset_;
        case 'g': return (glm::vec2)lval::g * text_coord_offset_;
        case 'h': return (glm::vec2)lval::h * text_coord_offset_;
        case 'i': return (glm::vec2)lval::i * text_coord_offset_;
        case 'j': return (glm::vec2)lval::j * text_coord_offset_;
        case 'k': return (glm::vec2)lval::k * text_coord_offset_;
        case 'l': return (glm::vec2)lval::l * text_coord_offset_;
        case 'm': return (glm::vec2)lval::m * text_coord_offset_;
        case 'n': return (glm::vec2)lval::n * text_coord_offset_;
        case 'o': return (glm::vec2)lval::o * text_coord_offset_;
        case 'p': return (glm::vec2)lval::p * text_coord_offset_;
        case 'q': return (glm::vec2)lval::q * text_coord_offset_;
        case 'r': return (glm::vec2)lval::r * text_coord_offset_;
        case 's': return (glm::vec2)lval::s * text_coord_offset_;
        case 't': return (glm::vec2)lval::t * text_coord_offset_;
        case 'u': return (glm::vec2)lval::u * text_coord_offset_;
        case 'v': return (glm::vec2)lval::v * text_coord_offset_;
        case 'w': return (glm::vec2)lval::w * text_coord_offset_;
        case 'x': return (glm::vec2)lval::x * text_coord_offset_;
        case 'y': return (glm::vec2)lval::y * text_coord_offset_;
        case 'z': return (glm::vec2)lval::z * text_coord_offset_;

        case '0': return (glm::vec2)lval::zero * text_coord_offset_;
        case '1': return (glm::vec2)lval::one * text_coord_offset_;
        case '2': return (glm::vec2)lval::two * text_coord_offset_;
        case '3': return (glm::vec2)lval::three * text_coord_offset_;
        case '4': return (glm::vec2)lval::four * text_coord_offset_;
        case '5': return (glm::vec2)lval::five * text_coord_offset_;
        case '6': return (glm::vec2)lval::six * text_coord_offset_;
        case '7': return (glm::vec2)lval::seven * text_coord_offset_;
        case '8': return (glm::vec2)lval::eight * text_coord_offset_;
        case '9': return (glm::vec2)lval::nine * text_coord_offset_;
        
        case '.': return (glm::vec2)lval::period * text_coord_offset_;
        case '!': return (glm::vec2)lval::exclamation * text_coord_offset_;
        case '?': return (glm::vec2)lval::question * text_coord_offset_;
        case ',': return (glm::vec2)lval::comma * text_coord_offset_;

        
        default:
            LOG_3("Invalid Text Char (", val, ")");
            ASSERT(false);
    }

    return {0.0f,0.0f};
}

void Banner::SetText(std::string& msg)
{
    int num_letters_ = msg.size();
    std::vector<glm::vec3> positions;

    LOG_2("Num letters = ", num_letters_);

    
    glm::vec3 text_pos = text_pos_root_;

    for(int i = 0; i < num_letters_; i ++)
    {
        positions.push_back(text_pos);
        text_pos += text_pos_offset_;
    }

    for(int i = 0; i < (int)positions.size(); i++)
        Text_.Objects_.push_back(new GameObject("res/models/Letter.obj", TEXTURE_LAYER::TEXT, positions.at(i), GetTextureCoords(msg.at(i))));
}

void Banner::UpdateBufferData(std::vector<float>& vertices, std::vector<unsigned int>& inidces, unsigned int& inidicePos)
{
    
    for (int i = 0; i < (int)Banner_.Objects_.size(); i++)
    {
        Banner_.Objects_.at(i)->GetIndiciBufferData(inidces, inidicePos);
        inidicePos = Banner_.Objects_.at(i)->GetVertexBufferData(vertices);
    }

    for (int i = 0; i < (int)Text_.Objects_.size(); i++)
    {
        Text_.Objects_.at(i)->GetIndiciBufferData(inidces, inidicePos);
        inidicePos += Text_.Objects_.at(i)->GetVertexBufferData(vertices);
    }


}



// float offset_ = 16;

 


// float GetOffsetForChar(char get)
// {
//     
// }

// void GetTextOffset()
// {
//     std::string msg = "i love you abby";
//     std::vector<int> letter_offests;
//     for(int i = 0; i < msg.size(); i++)
//         letter_offests.push_back(GetOffsetForChar(msg.at(i)));
// }
