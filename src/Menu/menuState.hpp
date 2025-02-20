#pragma once

#include <cstdint>

enum class MenuState : std::uint8_t { HOME,
                                      IN_GAME,
                                      PAUSE,
                                      PARAMETER };