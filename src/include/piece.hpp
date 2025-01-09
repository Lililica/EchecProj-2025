#pragma once

#include "app.hpp"
#include "utils.hpp"

enum class pieceColor : std::uint8_t { White,
                                       Black };

class piece {
private:
protected:
    Vec2       m_pos;
    pieceColor m_colorTeam;
    bool       m_isDead;

public:
};

// class pieceType by inheritance
class tour : public piece {
private:
protected:
public:
};

class cavalier : public piece {
private:
protected:
public:
};

class fou : public piece {
private:
protected:
public:
};

class dame : public piece {
private:
protected:
public:
};

class roi : public piece {
private:
protected:
public:
};

class pion : public piece {
private:
protected:
public:
};