#pragma once
#include <string>

inline bool is_pion(std::string& pieceName)
{
    return pieceName == "o" || pieceName == "p";
}

inline bool is_tour(std::string& pieceName)
{
    return pieceName == "t" || pieceName == "r";
}

inline bool is_cavalier(std::string& pieceName)
{
    return pieceName == "j" || pieceName == "h";
}

inline bool is_fou(std::string& pieceName)
{
    return pieceName == "n" || pieceName == "b";
}

inline bool is_dame(std::string& pieceName)
{
    return pieceName == "l" || pieceName == "k";
}

inline bool is_roi(std::string& pieceName)
{
    return pieceName == "w" || pieceName == "q";
}

inline bool is_pion_white(std::string& pieceName)
{
    return pieceName == "o";
}

inline bool is_pion_black(std::string& pieceName)
{
    return pieceName == "p";
}

inline bool is_tour_white(std::string& pieceName)
{
    return pieceName == "t";
}

inline bool is_tour_black(std::string& pieceName)
{
    return pieceName == "r";
}

inline bool is_cavalier_white(std::string& pieceName)
{
    return pieceName == "j";
}

inline bool is_cavalier_black(std::string& pieceName)
{
    return pieceName == "h";
}

inline bool is_fou_white(std::string& pieceName)
{
    return pieceName == "n";
}

inline bool is_fou_black(std::string& pieceName)
{
    return pieceName == "b";
}

inline bool is_dame_white(std::string& pieceName)
{
    return pieceName == "l";
}

inline bool is_dame_black(std::string& pieceName)
{
    return pieceName == "k";
}

inline bool is_roi_white(std::string& pieceName)
{
    return pieceName == "w";
}

inline bool is_roi_black(std::string& pieceName)
{
    return pieceName == "q";
}
