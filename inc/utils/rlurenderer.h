#pragma once

#include "linear_algebra/vec.h"
#include "simulation/geometry.h"

#include "misc/rlu_dll.h"

#include "rlbot/color.h"
#include "rlbot/scopedrenderer.h"

#include <vector>

class RLURenderer {
public:
    RLURenderer(const std::string &name);

    void DrawLine3D(rlbot::Color color, const vec3 &start, const vec3 &end);

    void DrawOBB(rlbot::Color color, const obb &box);

    void DrawPolyLine3D(rlbot::Color color, const std::vector<vec3> &vertices);

    void DrawString2D(const std::string &text, rlbot::Color color, vec2 topLeft, int scaleX, int scaleY);

    void DrawString3D(const std::string &text, rlbot::Color color, const vec3 &topLeft, int scaleX, int scaleY);

    void DrawRect2D(rlbot::Color color, const vec2 &topLeft, int height, int width, bool filled);

    void DrawRect3D(rlbot::Color color, const vec3 &topLeft, int height, int width, bool filled, bool centered = false);

private:
    rlbot::ScopedRenderer scopedRenderer;
};