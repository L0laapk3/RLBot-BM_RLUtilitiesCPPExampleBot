#include "utils/bridge.h"

#include <simulation/game.h>
#include <rlbot/packets.h>

vec3 vec3ToRLU(const RLBotBM::Shared::Vec3& v) {
    return { v.x, v.y, v.z };
}

mat3 quatToRLU(const RLBotBM::Shared::Quat& q) {
    return {
		{ 1 - 2 * (q.y * q.y + q.z * q.z), 2 * (q.x * q.y - q.w * q.z), 2 * (q.x * q.z + q.w * q.y) },
		{ 2 * (q.x * q.y + q.w * q.z), 1 - 2 * (q.x * q.x + q.z * q.z), 2 * (q.y * q.z - q.w * q.x) },
		{ 2 * (q.x * q.z - q.w * q.y), 2 * (q.y * q.z + q.w * q.x), 1 - 2 * (q.x * q.x + q.y * q.y) }
	};
}

vec3 flatVectorToVec3(const rlbot::flat::Vector3 *v) {
    return vec3{v->x(), v->y(), v->z()};
}

mat3 flatRotatorToMat3(const rlbot::flat::Rotator *r) {
    return euler_to_rotation({r->pitch(), r->yaw(), r->roll()});
}

void readFieldInfo(Game &game, const rlbot::FieldInfo &fieldInfo) {
    game.pads.resize(fieldInfo->boostPads()->Length());
    for (int i = 0; i < game.pads.size(); ++i) {
        auto pad = fieldInfo->boostPads()->Get(i);
        game.pads[i].position = flatVectorToVec3(pad->location());
        game.pads[i].type = pad->isFullBoost() ? BoostPadType::Full : BoostPadType::Partial;
    }

    game.goals.resize(fieldInfo->goals()->Length());
    for (int i = 0; i < game.goals.size(); ++i) {
        auto goal = fieldInfo->goals()->Get(i);
        game.goals[i].position = flatVectorToVec3(goal->location());
        game.goals[i].direction = flatVectorToVec3(goal->direction());
        game.goals[i].team = goal->teamNum();
        game.goals[i].width = goal->width();
        game.goals[i].height = goal->height();
        game.goals[i].state = GoalState::Unknown;
    }
}

void readState(Game &game, const RLBotBM::GameState& state) {
    // game info
    game.time = ((float)state.tick) / 120.f;
    game.time_remaining = 300.f - game.time; // todo
    game.gravity = {0.0f, 0.0f, -650.f}; // todo

 	// todo
    // if (packet->gameInfo()->isMatchEnded())
    //     game.state = GameState::Ended;
    // else {
    //     if (packet->gameInfo()->isRoundActive()) {
			if (state.balls[0].position.x == 0 && state.balls[0].position.z == 0)
				game.state = GameState::Kickoff;
			else
				game.state = GameState::Active;
    //     } else {
    //         game.state = GameState::Inactive;
    //     }
    // }

    // cars
    if (game.cars.size() != state.numCars)
        game.cars.resize(state.numCars);

    for (int i = 0; i < state.numCars; ++i) {
		auto& dest = game.cars[i];
        auto& src = state.cars[i];
        dest.position = vec3ToRLU(src.position);
        dest.velocity = vec3ToRLU(src.velocity);
        dest.angular_velocity = vec3ToRLU(src.angularVelocity);
        dest.orientation = quatToRLU(src.orientation);

        dest.boost = src.boost;
        dest.jumped = src.jumped; // todo
        dest.double_jumped = !src.hasFlip;
        dest.on_ground = src.frontLeftWheelContact || src.frontRightWheelContact || src.backLeftWheelContact || src.backRightWheelContact;
        dest.supersonic = src.superSonic;
        dest.demolished = src.demolished;

        dest.id = i;
        dest.team = src.team;

        dest.time = game.time;

        dest.hitbox_widths = vec3ToRLU(src.hitbox) * 0.5f;

        dest.hitbox_offset = vec3ToRLU(src.hitboxOffset);
    }

    // ball
	auto ball = state.balls[0];
    game.ball.position = vec3ToRLU(ball.position);
    game.ball.velocity = vec3ToRLU(ball.velocity);
    game.ball.angular_velocity = vec3ToRLU(ball.angularVelocity);
    game.ball.time = game.time;

	// todo
    // // boost pads
    // if (game.pads.size() != packet->boostPadStates()->Length()) {
    //     std::cout << "Boost pad info mismatch. Make sure to call readFieldInfo before readPacket!" << std::endl;
    // } else {
    //     for (int i = 0; i < game.pads.size(); ++i) {
    //         auto boostPad = packet->boostPadStates()->Get(i);
    //         game.pads[i].state = boostPad->isActive() ? BoostPadState::Available : BoostPadState::Unavailable;
    //         game.pads[i].timer = boostPad->timer();
    //     }
    // }
}

rlbot::Controller inputToController(const Input &input) {
    rlbot::Controller controller;
    controller.throttle = input.throttle;
    controller.steer = input.steer;
    controller.handbrake = input.handbrake;
    controller.jump = input.jump;
    controller.pitch = input.pitch;
    controller.yaw = input.yaw;
    controller.roll = input.roll;
    controller.useItem = input.use_item;
    return controller;
}