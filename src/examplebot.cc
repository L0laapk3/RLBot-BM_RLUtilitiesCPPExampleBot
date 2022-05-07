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


float lastCharge = -1.f;
RLBotBM::ControllerInput RLUtilitiesExampleBot::GetOutput(RLBotBM::GameState& state) {
    readState(game, state);

	if (state.dropShot.isDropShot) {
		if (lastCharge != state.dropShot.ballCharge) {
			auto& tiles = state.dropShot.tileDamage;

			std::cout << "                   __ __" << std::endl;
			std::cout << "         BLUE   __/" << (int)tiles[0x77] << " |" << (int)tiles[0x79] << " \\__   ORANGE" << std::endl;
			std::cout << "             __/" << (int)tiles[0x78] << " \\__|__/" << (int)tiles[0x7d] << " \\__" << std::endl;
			std::cout << "          __/" << (int)tiles[0x74] << " \\__/" << (int)tiles[0x76] << " |" << (int)tiles[0x7a] << " \\__/" << (int)tiles[0x7c] << " \\__" << std::endl;
			std::cout << "       __/" << (int)tiles[0x31] << " \\__/" << (int)tiles[0x75] << " \\__|__/" << (int)tiles[0x7b] << " \\__/" << (int)tiles[0x66] << " \\__" << std::endl;
			std::cout << "    __/" << (int)tiles[0x2c] << " \\__/" << (int)tiles[0x30] << " \\__/" << (int)tiles[0x1e] << " |" << (int)tiles[0xb] << " \\__/" << (int)tiles[0x64] << " \\__/" << (int)tiles[0x65] << " \\__" << std::endl;
			std::cout << " __/" << (int)tiles[0x1f] << " \\__/" << (int)tiles[0x32] << " \\__/" << (int)tiles[0x1c] << " \\__|__/" << (int)tiles[0x1d] << " \\__/" << (int)tiles[0x69] << " \\__/" << (int)tiles[0x50] << " \\__" << std::endl;
			std::cout << "/" << (int)tiles[0x18] << " \\__/" << (int)tiles[0x2d] << " \\__/" << (int)tiles[0x2f] << " \\__/" << (int)tiles[0x3c] << " |" << (int)tiles[0xc] << " \\__/" << (int)tiles[0x67] << " \\__/" << (int)tiles[0x68] << " \\__/" << (int)tiles[0x4] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[0x20] << " \\__/" << (int)tiles[0x2e] << " \\__/" << (int)tiles[0x3a] << " \\__|__/" << (int)tiles[0x3b] << " \\__/" << (int)tiles[0x6c] << " \\__/" << (int)tiles[0x51] << " \\__/" << std::endl;
			std::cout << "/" << (int)tiles[0x17] << " \\__/" << (int)tiles[0x29] << " \\__/" << (int)tiles[0x2b] << " \\__/" << (int)tiles[0x8a] << " |" << (int)tiles[0x15] << " \\__/" << (int)tiles[0x6a] << " \\__/" << (int)tiles[0x6b] << " \\__/" << (int)tiles[0x5] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[0x21] << " \\__/" << (int)tiles[0x2a] << " \\__/" << (int)tiles[0x85] << " \\__|__/" << (int)tiles[0x89] << " \\__/" << (int)tiles[0x72] << " \\__/" << (int)tiles[0x52] << " \\__/" << std::endl;
			std::cout << "/" << (int)tiles[0xf] << " \\__/" << (int)tiles[0x27] << " \\__/" << (int)tiles[0x28] << " \\__/" << (int)tiles[0x8b] << " |" << (int)tiles[0x16] << " \\__/" << (int)tiles[0x6d] << " \\__/" << (int)tiles[0x71] << " \\__/" << (int)tiles[0x7] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[0x25] << " \\__/" << (int)tiles[0x45] << " \\__/" << (int)tiles[0x86] << " \\__|__/" << (int)tiles[0x88] << " \\__/" << (int)tiles[0x73] << " \\__/" << (int)tiles[0x54] << " \\__/" << std::endl;
			std::cout << "/" << (int)tiles[0x10] << " \\__/" << (int)tiles[0x40] << " \\__/" << (int)tiles[0x44] << " \\__/" << (int)tiles[0x87] << " |" << (int)tiles[0x83] << " \\__/" << (int)tiles[0x6e] << " \\__/" << (int)tiles[0x70] << " \\__/" << (int)tiles[0x6] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[0x26] << " \\__/" << (int)tiles[0x46] << " \\__/" << (int)tiles[0x7e] << " \\__|__/" << (int)tiles[0x82] << " \\__/" << (int)tiles[0x6f] << " \\__/" << (int)tiles[0x53] << " \\__/" << std::endl;
			std::cout << "/" << (int)tiles[0x11] << " \\__/" << (int)tiles[0x41] << " \\__/" << (int)tiles[0x43] << " \\__/" << (int)tiles[0x1b] << " |" << (int)tiles[0x84] << " \\__/" << (int)tiles[0x58] << " \\__/" << (int)tiles[0x59] << " \\__/" << (int)tiles[0x1] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[0x24] << " \\__/" << (int)tiles[0x42] << " \\__/" << (int)tiles[0x7f] << " \\__|__/" << (int)tiles[0x81] << " \\__/" << (int)tiles[0x5c] << " \\__/" << (int)tiles[0x4f] << " \\__/" << std::endl;
			std::cout << "/" << (int)tiles[0x19] << " \\__/" << (int)tiles[0x3d] << " \\__/" << (int)tiles[0x3f] << " \\__/" << (int)tiles[0x14] << " |" << (int)tiles[0x80] << " \\__/" << (int)tiles[0x5a] << " \\__/" << (int)tiles[0x5b] << " \\__/" << (int)tiles[0x2] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[0x23] << " \\__/" << (int)tiles[0x3e] << " \\__/" << (int)tiles[0x55] << " \\__|__/" << (int)tiles[0x57] << " \\__/" << (int)tiles[0x62] << " \\__/" << (int)tiles[0x4e] << " \\__/" << std::endl;
			std::cout << "/" << (int)tiles[0x1a] << " \\__/" << (int)tiles[0x37] << " \\__/" << (int)tiles[0x39] << " \\__/" << (int)tiles[0x13] << " |" << (int)tiles[0x56] << " \\__/" << (int)tiles[0x5d] << " \\__/" << (int)tiles[0x61] << " \\__/" << (int)tiles[0x3] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[0x22] << " \\__/" << (int)tiles[0x38] << " \\__/" << (int)tiles[0x4a] << " \\__|__/" << (int)tiles[0x4c] << " \\__/" << (int)tiles[0x63] << " \\__/" << (int)tiles[0x4d] << " \\__/" << std::endl;
			std::cout << "   \\__/" << (int)tiles[0x34] << " \\__/" << (int)tiles[0x36] << " \\__/" << (int)tiles[0x12] << " |" << (int)tiles[0x4b] << " \\__/" << (int)tiles[0x5e] << " \\__/" << (int)tiles[0x60] << " \\__/" << std::endl;
			std::cout << "      \\__/" << (int)tiles[0x35] << " \\__/" << (int)tiles[0x47] << " \\__|__/" << (int)tiles[0x49] << " \\__/" << (int)tiles[0x5f] << " \\__/" << std::endl;
			std::cout << "         \\__/" << (int)tiles[0x33] << " \\__/" << (int)tiles[0xe] << " |" << (int)tiles[0x48] << " \\__/" << (int)tiles[0x8] << " \\__/" << std::endl;
			std::cout << "            \\__/" << (int)tiles[0xd] << " \\__|__/" << (int)tiles[0xa] << " \\__/" << std::endl;
			std::cout << "               \\__/" << (int)tiles[0x0] << " |" << (int)tiles[0x9] << " \\__/" << std::endl;
			std::cout << "                  \\__|__/      ball charge: " << state.dropShot.ballCharge << std::endl;

			lastCharge = state.dropShot.ballCharge;
		}
	}


    // Rendering and ball prediction example
    
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

    // Drive towards the ball
    Drive drive(game.cars[index]);
    drive.target = game.ball.position;
    drive.step(1.0f / 120.0f);

    return inputToController(drive.controls);
}
