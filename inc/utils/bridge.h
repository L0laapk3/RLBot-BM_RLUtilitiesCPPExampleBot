#pragma once

#include <simulation/game.h>
#include <rlbot/packets.h>

vec3 flatVectorToVec3(const rlbot::flat::Vector3 *v);

mat3 flatRotatorToMat3(const rlbot::flat::Rotator *r);

void readFieldInfo(Game &game, const rlbot::FieldInfo &fieldInfo);

void readPacket(Game &game, const rlbot::GameTickPacket &packet);

rlbot::Controller inputToController(const Input & input);