#include <imgui.h>
#include <cstddef>
#include <quick_imgui/quick_imgui.hpp>
#include "app.hpp"

int main()
{
    App mainApp{};

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // mainApp.setFont(io.Fonts->AddFontFromFileTTF("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/CHEQ_TT.TTF", 50.f));

    mainApp.setup_app();

    ImFont* basicFont = io.Fonts->AddFontDefault();

    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Echec Game");

            ImGui::PushFont(basicFont);

            mainApp.update_app();

            ImGui::PopFont();

            ImGui::End();
        }
    );
}
