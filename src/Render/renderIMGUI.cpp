#include "renderIMGUI.hpp"
#include "Game/Piece/piece.hpp"
#include "Game/game.hpp"
#include <imgui.h>

void RenderImGui::draw_content(Game &currentGame) const {
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,
                      ImVec2(parameter.spaceCase, parameter.spaceCase));

  if (currentGame.is_selected_piece()) {
    ImGui::PushFont(this->DefaultFont);
    ImGui::Begin("Choose your view");
    ImGui::Text("Clic the button to change the view");

    ImGui::NewLine();
    if (currentGame.get_first_view()->isFirstPerson) {
      if (ImGui::Button("Go back to the global camera", ImVec2(200, 0))) {
        currentGame.get_first_view()->isFirstPerson = false;
      }
    } else {
      if (ImGui::Button("Go to the first person camera", ImVec2(200, 0))) {
        currentGame.get_first_view()->isFirstPerson = true;
      }
    }
    ImGui::End();
    ImGui::PopFont();
  }

  for (int y{0}; y < currentGame.getGridSize(); ++y) {
    for (int x{0}; x < currentGame.getGridSize(); ++x) {
      Piece *piece = currentGame.get_piece(x, y);

      if (x != 0)
        ImGui::SameLine();

      int id = y * currentGame.getGridSize() + x;

      ImGui::PushID(id);
      ImGui::PushFont(this->ChessFont);

      std::string pieceName = piece ? piece->name_for_imgui() : " ";

      bool has_pushed_border = false;
      if (currentGame.is_selected_piece() &&
          currentGame.get_pos_selected_piece() == std::make_pair(x, y)) {
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.0f);
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        has_pushed_border = true;
      }

      if (currentGame.is_selected_piece() && !has_pushed_border) {
        auto possible_pos = currentGame.get_possible_pos();
        if (std::find(possible_pos.begin(), possible_pos.end(),
                      std::pair<int, int>{x, y}) != possible_pos.end()) {
          ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.0f);
          ImGui::PushStyleColor(ImGuiCol_Border,
                                ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
          has_pushed_border = true;
        }
        auto possible_attack = currentGame.get_attack_possible();
        if (std::find(possible_attack.begin(), possible_attack.end(),
                      std::pair<int, int>{x, y}) != possible_attack.end()) {
          ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.0f);
          ImGui::PushStyleColor(ImGuiCol_Border,
                                ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
          has_pushed_border = true;
        }
      }

      if (ImGui::Button(pieceName.c_str(),
                        ImVec2{parameter.tailleCase, parameter.tailleCase})) {
        if (piece && !currentGame.is_selected_piece() &&
            piece->get_color() == (currentGame.is_white_turn()
                                       ? PieceColor::WHITE
                                       : PieceColor::BLACK)) {
          currentGame.select_piece(piece);
        } else if (currentGame.is_selected_piece()) {

          currentGame.move_piece(x, y);
        }
      }

      if (has_pushed_border) {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
      }

      ImGui::PopFont();
      ImGui::PopID();
    }
  }
  ImGui::PopStyleVar();
}
