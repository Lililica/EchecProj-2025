#pragma once

#include "app.hpp"
#include "utils.hpp"

enum class pieceColor : std::uint8_t { White,
                                       Black };

class piece {
private:
protected:
    Vec2<int>  m_pos;
    pieceColor m_colorTeam;
    bool       m_isDead;

public:
    piece()                        = default;
    piece(const piece&)            = default;
    piece(piece&&)                 = default;
    piece& operator=(const piece&) = default;
    piece& operator=(piece&&)      = default;
    piece(Vec2<int> pos, pieceColor colorTeam)
        : m_pos(pos)
        , m_colorTeam(colorTeam)
        , m_isDead(false) {
        };

    virtual ~piece() = default;

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
    std::string m_name = "Tour";

protected:
public:
    std::string getName() const { return m_name; }
};

class cavalier : public piece {
private:
    std::string m_name = "Cavalier";

protected:
public:
    std::string getName() const { return m_name; }
};

class fou : public piece {
private:
    std::string m_name = "Fou";

protected:
public:
    std::string getName() const { return m_name; }
};

class dame : public piece {
private:
    std::string m_name = "Dame";

protected:
public:
    std::string getName() const { return m_name; }
};

class roi : public piece {
private:
    std::string m_name = "Roi";

protected:
public:
    std::string getName() const { return m_name; }
};

class pion : public piece {
private:
    std::string m_name = "Pion";

protected:
public:
    std::string getName() const { return m_name; }
};

template<typename T>
struct pieceConteneur {
    std::vector<T> m_piecesListe;
    int            indiceChange;
};