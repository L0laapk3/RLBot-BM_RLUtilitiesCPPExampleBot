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
			std::cout << "ball charge: " << state.dropShot.ballCharge << std::endl;
			auto& tiles = state.dropShot.tileDamage;

			std::cout << "                   __    __    __    __    __    __    __" << std::endl;
			std::cout << "                __/" << (int)tiles[26] << " \\__/" << (int)tiles[25] << " \\__/" << (int)tiles[17] << " \\__/" << (int)tiles[16] << " \\__/" << (int)tiles[15] << " \\__/" << (int)tiles[23] << " \\__/" << (int)tiles[24] << " \\__" << std::endl;
			std::cout << "             __/" << (int)tiles[34] << " \\__/" << (int)tiles[35] << " \\__/" << (int)tiles[36] << " \\__/" << (int)tiles[38] << " \\__/" << (int)tiles[37] << " \\__/" << (int)tiles[33] << " \\__/" << (int)tiles[32] << " \\__/" << (int)tiles[31] << " \\__" << std::endl;
			std::cout << "          __/" << (int)tiles[52] << " \\__/" << (int)tiles[55] << " \\__/" << (int)tiles[61] << " \\__/" << (int)tiles[65] << " \\__/" << (int)tiles[64] << " \\__/" << (int)tiles[39] << " \\__/" << (int)tiles[41] << " \\__/" << (int)tiles[45] << " \\__/" << (int)tiles[44] << " \\__" << std::endl;
			std::cout << "       __/" << (int)tiles[53] << " \\__/" << (int)tiles[56] << " \\__/" << (int)tiles[62] << " \\__/" << (int)tiles[66] << " \\__/" << (int)tiles[70] << " \\__/" << (int)tiles[69] << " \\__/" << (int)tiles[42] << " \\__/" << (int)tiles[46] << " \\__/" << (int)tiles[50] << " \\__/" << (int)tiles[49] << " \\__" << std::endl;
			std::cout << "    __/" << (int)tiles[51] << " \\__/" << (int)tiles[54] << " \\__/" << (int)tiles[57] << " \\__/" << (int)tiles[63] << " \\__/" << (int)tiles[67] << " \\__/" << (int)tiles[68] << " \\__/" << (int)tiles[40] << " \\__/" << (int)tiles[43] << " \\__/" << (int)tiles[47] << " \\__/" << (int)tiles[48] << " \\__/" << (int)tiles[116] << " \\__" << std::endl;
			std::cout << " __/" << (int)tiles[13] << " \\__/" << (int)tiles[71] << " \\__/" << (int)tiles[74] << " \\__/" << (int)tiles[85] << " \\__/" << (int)tiles[127] << " \\__/" << (int)tiles[126] << " \\__/" << (int)tiles[134] << " \\__/" << (int)tiles[133] << " \\__/" << (int)tiles[58] << " \\__/" << (int)tiles[28] << " \\__/" << (int)tiles[117] << " \\__/" << (int)tiles[120] << " \\__" << std::endl;
			std::cout << "/" << (int)tiles[0] << " \\__/" << (int)tiles[14] << " \\__/" << (int)tiles[18] << " \\__/" << (int)tiles[19] << " \\__/" << (int)tiles[20] << " \\__/" << (int)tiles[27] << " \\__/" << (int)tiles[135] << " \\__/" << (int)tiles[139] << " \\__/" << (int)tiles[138] << " \\__/" << (int)tiles[60] << " \\__/" << (int)tiles[30] << " \\__/" << (int)tiles[118] << " \\__/" << (int)tiles[119] << " \\" << std::endl;
			std::cout << "\\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/" << std::endl;
			std::cout << " __    __    __    __    __    __    __    __    __    __    __    __    __" << std::endl;
			std::cout << "/" << (int)tiles[9] << " \\__/" << (int)tiles[72] << " \\__/" << (int)tiles[75] << " \\__/" << (int)tiles[86] << " \\__/" << (int)tiles[128] << " \\__/" << (int)tiles[132] << " \\__/" << (int)tiles[131] << " \\__/" << (int)tiles[22] << " \\__/" << (int)tiles[21] << " \\__/" << (int)tiles[12] << " \\__/" << (int)tiles[11] << " \\__/" << (int)tiles[122] << " \\__/" << (int)tiles[121] << " \\" << std::endl;
			std::cout << "\\__/" << (int)tiles[10] << " \\__/" << (int)tiles[73] << " \\__/" << (int)tiles[76] << " \\__/" << (int)tiles[87] << " \\__/" << (int)tiles[129] << " \\__/" << (int)tiles[130] << " \\__/" << (int)tiles[136] << " \\__/" << (int)tiles[137] << " \\__/" << (int)tiles[59] << " \\__/" << (int)tiles[29] << " \\__/" << (int)tiles[123] << " \\__/" << (int)tiles[125] << " \\__/" << std::endl;
			std::cout << "   \\__/" << (int)tiles[8] << " \\__/" << (int)tiles[94] << " \\__/" << (int)tiles[93] << " \\__/" << (int)tiles[90] << " \\__/" << (int)tiles[88] << " \\__/" << (int)tiles[110] << " \\__/" << (int)tiles[109] << " \\__/" << (int)tiles[106] << " \\__/" << (int)tiles[103] << " \\__/" << (int)tiles[100] << " \\__/" << (int)tiles[124] << " \\__/" << std::endl;
			std::cout << "      \\__/" << (int)tiles[95] << " \\__/" << (int)tiles[99] << " \\__/" << (int)tiles[98] << " \\__/" << (int)tiles[92] << " \\__/" << (int)tiles[111] << " \\__/" << (int)tiles[115] << " \\__/" << (int)tiles[114] << " \\__/" << (int)tiles[108] << " \\__/" << (int)tiles[105] << " \\__/" << (int)tiles[102] << " \\__/" << std::endl;
			std::cout << "         \\__/" << (int)tiles[96] << " \\__/" << (int)tiles[97] << " \\__/" << (int)tiles[91] << " \\__/" << (int)tiles[89] << " \\__/" << (int)tiles[112] << " \\__/" << (int)tiles[113] << " \\__/" << (int)tiles[107] << " \\__/" << (int)tiles[104] << " \\__/" << (int)tiles[101] << " \\__/" << std::endl;
			std::cout << "             \\__/" << (int)tiles[77] << " \\__/" << (int)tiles[78] << " \\__/" << (int)tiles[79] << " \\__/" << (int)tiles[83] << " \\__/" << (int)tiles[84] << " \\__/" << (int)tiles[82] << " \\__/" << (int)tiles[81] << " \\__/" << (int)tiles[80] << " \\__/" << std::endl;
			std::cout << "                \\__/" << (int)tiles[3] << " \\__/" << (int)tiles[2] << " \\__/" << (int)tiles[1] << " \\__/" << (int)tiles[6] << " \\__/" << (int)tiles[7] << " \\__/" << (int)tiles[5] << " \\__/" << (int)tiles[4] << " \\__/" << std::endl;
			std::cout << "                   \\__/  \\__/  \\__/  \\__/  \\__/  \\__/  \\__/" << std::endl;

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
