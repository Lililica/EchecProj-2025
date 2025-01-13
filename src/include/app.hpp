#pragma once
#include <iostream>
#include <vector>
#include "app.hpp"
#include "bouton.hpp"
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "utils.hpp"

enum class screenState : std::uint8_t { Accueil,
                                        Game,
                                        Loading };

class App {
private:
    screenState                    m_state    = screenState::Accueil;
    int                            tailleGrid = 8;
    pieceConteneur<class pion>     m_pions;
    pieceConteneur<class tour>     m_tours;
    pieceConteneur<class cavalier> m_cavaliers;
    pieceConteneur<class fou>      m_fous;
    pieceConteneur<class dame>     m_dames;
    pieceConteneur<class roi>      m_rois;

    void push_piece();

public:
    explicit App(int& n)
        : tailleGrid(n) {

        };
    App(App& app);
    ~App() = default;

    App const& operator=(App& app);
    App        operator=(App app);

    int getTailleGrid() const { return tailleGrid; }

    void setup_app();
    void calcul_content();
    void draw_content();
};