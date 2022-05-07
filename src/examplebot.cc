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

			std::cout << "             _   _   _   _   _   _   _" << std::endl;
			std::cout << "           _/" << (int)tiles[26] << "\\_/" << (int)tiles[25] << "\\_/" << (int)tiles[17] << "\\_/" << (int)tiles[16] << "\\_/" << (int)tiles[15] << "\\_/" << (int)tiles[23] << "\\_/" << (int)tiles[24] << "\\_" << std::endl;
			std::cout << "         _/" << (int)tiles[34] << "\\_/" << (int)tiles[35] << "\\_/" << (int)tiles[36] << "\\_/" << (int)tiles[38] << "\\_/" << (int)tiles[37] << "\\_/" << (int)tiles[33] << "\\_/" << (int)tiles[32] << "\\_/" << (int)tiles[31] << "\\_" << std::endl;
			std::cout << "       _/" << (int)tiles[52] << "\\_/" << (int)tiles[55] << "\\_/" << (int)tiles[61] << "\\_/" << (int)tiles[65] << "\\_/" << (int)tiles[64] << "\\_/" << (int)tiles[39] << "\\_/" << (int)tiles[41] << "\\_/" << (int)tiles[45] << "\\_/" << (int)tiles[44] << "\\_" << std::endl;
			std::cout << "     _/" << (int)tiles[53] << "\\_/" << (int)tiles[56] << "\\_/" << (int)tiles[62] << "\\_/" << (int)tiles[66] << "\\_/" << (int)tiles[70] << "\\_/" << (int)tiles[69] << "\\_/" << (int)tiles[42] << "\\_/" << (int)tiles[46] << "\\_/" << (int)tiles[50] << "\\_/" << (int)tiles[49] << "\\_" << std::endl;
			std::cout << "   _/" << (int)tiles[51] << "\\_/" << (int)tiles[54] << "\\_/" << (int)tiles[57] << "\\_/" << (int)tiles[63] << "\\_/" << (int)tiles[67] << "\\_/" << (int)tiles[68] << "\\_/" << (int)tiles[40] << "\\_/" << (int)tiles[43] << "\\_/" << (int)tiles[47] << "\\_/" << (int)tiles[48] << "\\_/" << (int)tiles[116] << "\\_" << std::endl;
			std::cout << " _/" << (int)tiles[13] << "\\_/" << (int)tiles[71] << "\\_/" << (int)tiles[74] << "\\_/" << (int)tiles[85] << "\\_/" << (int)tiles[127] << "\\_/" << (int)tiles[126] << "\\_/" << (int)tiles[134] << "\\_/" << (int)tiles[133] << "\\_/" << (int)tiles[58] << "\\_/" << (int)tiles[28] << "\\_/" << (int)tiles[117] << "\\_/" << (int)tiles[120] << "\\_" << std::endl;
			std::cout << "/" << (int)tiles[0] << "\\_/" << (int)tiles[14] << "\\_/" << (int)tiles[18] << "\\_/" << (int)tiles[19] << "\\_/" << (int)tiles[20] << "\\_/" << (int)tiles[27] << "\\_/" << (int)tiles[135] << "\\_/" << (int)tiles[139] << "\\_/" << (int)tiles[138] << "\\_/" << (int)tiles[60] << "\\_/" << (int)tiles[30] << "\\_/" << (int)tiles[118] << "\\_/" << (int)tiles[119] << "\\" << std::endl;
			std::cout << "\\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/" << std::endl;
			std::cout << " _   _   _   _   _   _   _   _   _   _   _   _   _" << std::endl;
			std::cout << "/" << (int)tiles[9] << "\\_/" << (int)tiles[72] << "\\_/" << (int)tiles[75] << "\\_/" << (int)tiles[86] << "\\_/" << (int)tiles[128] << "\\_/" << (int)tiles[132] << "\\_/" << (int)tiles[131] << "\\_/" << (int)tiles[22] << "\\_/" << (int)tiles[21] << "\\_/" << (int)tiles[12] << "\\_/" << (int)tiles[11] << "\\_/" << (int)tiles[122] << "\\_/" << (int)tiles[121] << "\\" << std::endl;
			std::cout << "\\_/" << (int)tiles[10] << "\\_/" << (int)tiles[73] << "\\_/" << (int)tiles[76] << "\\_/" << (int)tiles[87] << "\\_/" << (int)tiles[129] << "\\_/" << (int)tiles[130] << "\\_/" << (int)tiles[136] << "\\_/" << (int)tiles[137] << "\\_/" << (int)tiles[59] << "\\_/" << (int)tiles[29] << "\\_/" << (int)tiles[123] << "\\_/" << (int)tiles[125] << "\\_/" << std::endl;
			std::cout << "  \\_/" << (int)tiles[8] << "\\_/" << (int)tiles[94] << "\\_/" << (int)tiles[93] << "\\_/" << (int)tiles[90] << "\\_/" << (int)tiles[88] << "\\_/" << (int)tiles[110] << "\\_/" << (int)tiles[109] << "\\_/" << (int)tiles[106] << "\\_/" << (int)tiles[103] << "\\_/" << (int)tiles[100] << "\\_/" << (int)tiles[124] << "\\_/" << std::endl;
			std::cout << "    \\_/" << (int)tiles[95] << "\\_/" << (int)tiles[99] << "\\_/" << (int)tiles[98] << "\\_/" << (int)tiles[92] << "\\_/" << (int)tiles[111] << "\\_/" << (int)tiles[115] << "\\_/" << (int)tiles[114] << "\\_/" << (int)tiles[108] << "\\_/" << (int)tiles[105] << "\\_/" << (int)tiles[102] << "\\_/" << std::endl;
			std::cout << "      \\_/" << (int)tiles[96] << "\\_/" << (int)tiles[97] << "\\_/" << (int)tiles[91] << "\\_/" << (int)tiles[89] << "\\_/" << (int)tiles[112] << "\\_/" << (int)tiles[113] << "\\_/" << (int)tiles[107] << "\\_/" << (int)tiles[104] << "\\_/" << (int)tiles[101] << "\\_/" << std::endl;
			std::cout << "        \\_/" << (int)tiles[77] << "\\_/" << (int)tiles[78] << "\\_/" << (int)tiles[79] << "\\_/" << (int)tiles[83] << "\\_/" << (int)tiles[84] << "\\_/" << (int)tiles[82] << "\\_/" << (int)tiles[81] << "\\_/" << (int)tiles[80] << "\\_/" << std::endl;
			std::cout << "          \\_/" << (int)tiles[3] << "\\_/" << (int)tiles[2] << "\\_/" << (int)tiles[1] << "\\_/" << (int)tiles[6] << "\\_/" << (int)tiles[7] << "\\_/" << (int)tiles[5] << "\\_/" << (int)tiles[4] << "\\_/" << std::endl;
			std::cout << "            \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/    ball charge: " << state.dropShot.ballCharge << std::endl;

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
