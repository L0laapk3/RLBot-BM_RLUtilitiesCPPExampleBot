#include "examplebot.h"

#include <string>
#include <iostream>
#include <linear_algebra/vec.h>
#include <simulation/game.h>
#include <mechanics/drive.h>
#include <simulation/field.h>
#include <utils/bridge.h>
#include <rlutilities.h>
#include <utils/rlurenderer.h>

#include "rlbot/bot.h"
#include "rlbot/color.h"
#include "rlbot/interface.h"
#include "rlbot/statesetting.h"

RLUtilitiesExampleBot::RLUtilitiesExampleBot(int _index, int _team, std::string _name) : Bot(_index, _team, _name) {
    // Initialize RLU with the path to the assets folder, relative to the executable.
    rlu::initialize("assets/");

    // Tell RLU which field mesh and ball parameters to use
    Game::set_mode("soccar");

    // Read field info. Only needs to be called once
    readFieldInfo(game, GetFieldInfo());

    // State setting example
    rlbot::GameState gameState = rlbot::GameState();
    gameState.ballState.physicsState.location = {0, 0, 1000};
    gameState.ballState.physicsState.velocity = {0, 0, 100};
    rlbot::Interface::SetGameState(gameState);
}

RLUtilitiesExampleBot::~RLUtilitiesExampleBot() {
    // Free your allocated memory here.
}


int lastTick = 0;
RLBotBM::ControllerInput RLUtilitiesExampleBot::GetOutput(RLBotBM::GameState& state) {
    readState(game, state);


    // Rendering and ball prediction example
    
	if (state.tick != lastTick) {
		lastTick = state.tick;
        // This renderer will build and send the packet once it goes out of scope.
        RLURenderer renderer(std::to_string(index)); // Use index as the group name so it differs across instances

        renderer.DrawString2D("Hello world!", rlbot::Color::green, {10, 10}, 4, 4);
        renderer.DrawOBB(rlbot::Color::green, game.cars[index].hitbox()); // Render car hitbox

        // Predict the ball for 2 seconds and render the predicted positions
        std::vector<vec3> points;
        Ball copy = game.ball;
        while (copy.time < game.time + 4.f) {
            copy.step(1.f / 120.f);
            points.push_back(copy.position);
        }
        renderer.DrawPolyLine3D(rlbot::Color::red, points);
    }

    // Drive towards the ball
    Drive drive(game.cars[index]);
    drive.target = game.ball.position;
    drive.step(1.0f / 120.0f);

    return inputToController(drive.controls);
}
