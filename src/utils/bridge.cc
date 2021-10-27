#include "utils/bridge.h"

#include <simulation/game.h>
#include <rlbot/packets.h>

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

void readPacket(Game &game, const rlbot::GameTickPacket &packet) {
    // game info
    game.time = packet->gameInfo()->secondsElapsed();
    game.time_remaining = packet->gameInfo()->gameTimeRemaining();
    game.gravity = {0.0f, 0.0f, packet->gameInfo()->worldGravityZ()};

    if (packet->gameInfo()->isMatchEnded()) {
        game.state = GameState::Ended;
    } else {
        if (packet->gameInfo()->isRoundActive()) {
            if (packet->gameInfo()->isKickoffPause()) {
                game.state = GameState::Kickoff;
            } else {
                game.state = GameState::Active;
            }
        } else {
            game.state = GameState::Inactive;
        }
    }

    // cars
    if (game.cars.size() != packet->players()->Length())
        game.cars.resize(packet->players()->Length());

    for (int i = 0; i < packet->players()->Length(); ++i) {
        auto player = packet->players()->Get(i);
        game.cars[i].position = flatVectorToVec3(player->physics()->location());
        game.cars[i].velocity = flatVectorToVec3(player->physics()->velocity());
        game.cars[i].angular_velocity = flatVectorToVec3(player->physics()->angularVelocity());
        game.cars[i].orientation = flatRotatorToMat3(player->physics()->rotation());

        game.cars[i].boost = player->boost();
        game.cars[i].jumped = player->jumped();
        game.cars[i].double_jumped = player->doubleJumped();
        game.cars[i].on_ground = player->hasWheelContact();
        game.cars[i].supersonic = player->isSupersonic();
        game.cars[i].demolished = player->isDemolished();

        game.cars[i].id = i;
        game.cars[i].team = player->team();

        game.cars[i].time = game.time;

        game.cars[i].hitbox_widths[0] = player->hitbox()->length() * 0.5f;
        game.cars[i].hitbox_widths[1] = player->hitbox()->width() * 0.5f;
        game.cars[i].hitbox_widths[2] = player->hitbox()->height() * 0.5f;

        game.cars[i].hitbox_offset = flatVectorToVec3(player->hitboxOffset());
    }

    // ball
    game.ball.position = flatVectorToVec3(packet->ball()->physics()->location());
    game.ball.velocity = flatVectorToVec3(packet->ball()->physics()->velocity());
    game.ball.angular_velocity = flatVectorToVec3(packet->ball()->physics()->angularVelocity());
    game.ball.time = game.time;

    // boost pads
    if (game.pads.size() != packet->boostPadStates()->Length()) {
        std::cout << "Boost pad info mismatch. Make sure to call readFieldInfo before readPacket!" << std::endl;
    } else {
        for (int i = 0; i < game.pads.size(); ++i) {
            auto boostPad = packet->boostPadStates()->Get(i);
            game.pads[i].state = boostPad->isActive() ? BoostPadState::Available : BoostPadState::Unavailable;
            game.pads[i].timer = boostPad->timer();
        }
    }
}

rlbot::Controller inputToController(const Input &input) {
    rlbot::Controller controller;
    controller.throttle = input.throttle;
    controller.steer = input.steer;
    controller.boost = input.boost;
    controller.handbrake = input.handbrake;
    controller.jump = input.jump;
    controller.pitch = input.pitch;
    controller.yaw = input.yaw;
    controller.roll = input.roll;
    controller.useItem = input.use_item;
    return controller;
}
