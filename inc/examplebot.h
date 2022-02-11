#pragma once

#include "simulation/game.h"
#include "rlbot/bot.h"

class RLUtilitiesExampleBot : public rlbot::Bot {
    Game game;
public:
    RLUtilitiesExampleBot(int _index, int _team, std::string _name);

    ~RLUtilitiesExampleBot();

    RLBotBM::ControllerInput GetOutput(RLBotBM::GameState& state) override;
};
