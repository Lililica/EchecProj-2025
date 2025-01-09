#pragma once
#include <iostream>
#include <vector>
#include "app.hpp"
#include "bouton.hpp"
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "utils.hpp"

enum class screenState : std::uint8_t { Accueil,
                                        Game };

class App {
private:
    screenState                 m_state    = screenState::Accueil;
    int                         tailleGrid = 8;
    std::vector<class pion>     m_pions;
    std::vector<class tour>     m_tours;
    std::vector<class cavalier> m_cavaliers;
    std::vector<class fou>      m_fous;
    std::vector<class dame>     m_dames;
    std::vector<class roi>      m_rois;

public:
    explicit App(int& n)
        : tailleGrid(n) {

        };
    App(App& app);
    ~App() = default;

    App const& operator=(App& app);
    App        operator=(App app);

    void setup_app();
    void calcul_content();
    void draw_content() const;
};