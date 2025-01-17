#pragma once

// #include <cstdint>
#include <cstdint>
#include <string>
#include "../utils/utils.hpp"

enum class pieceColor : std::uint8_t { White,
                                       Black };

class piece {
private:
protected:
    Vec2<int>  m_pos;
    pieceColor m_colorTeam;
    bool       m_isDead;

public:
    Vec2<int> getPos() const { return m_pos; };
    void      setPos(Vec2<int> pos) { m_pos = pos; };

    pieceColor getColorTeam() const { return m_colorTeam; };
    void       setColorTeam(pieceColor colorTeam) { m_colorTeam = colorTeam; };

    bool getIsDead() const { return m_isDead; };
    void setIsDead(bool isDead) { m_isDead = isDead; };
};

// class pieceType by inheritance
class tour : public piece {
private:
protected:
public:
    std::string getName() const
    {
        if (m_colorTeam == pieceColor::White)
            return "t";
        else
            return "r";
        return "Tour";
    }
};

class cavalier : public piece {
private:
protected:
public:
    std::string getName() const
    {
        if (m_colorTeam == pieceColor::White)
            return "j";
        else
            return "h";
        return "Cavalier";
    }
};

class fou : public piece {
private:
protected:
public:
    std::string getName() const
    {
        if (m_colorTeam == pieceColor::White)
            return "n";
        else
            return "b";
        return "Fou";
    }
};

class dame : public piece {
private:
protected:
public:
    std::string getName() const
    {
        if (m_colorTeam == pieceColor::White)
            return "l";
        else
            return "k";
        return "Dame";
    }
};

class roi : public piece {
private:
protected:
public:
    std::string getName() const
    {
        if (m_colorTeam == pieceColor::White)
            return "w";
        else
            return "q";
        return "Roi";
    }
};

class pion : public piece {
private:
protected:
public:
    std::string getName() const
    {
        if (m_colorTeam == pieceColor::White)
            return "o";
        else
            return "p";
        return "Pion";
    }
};
