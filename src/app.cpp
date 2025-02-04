#include "app.hpp"
#include "Render/renderIMGUI.hpp"

void App::setup_app()
{
}
void App::update_app()
{
    _render2D.draw_content(*_currentGame);
}