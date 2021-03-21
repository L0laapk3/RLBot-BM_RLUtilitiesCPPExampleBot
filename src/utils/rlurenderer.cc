#include "utils/rlurenderer.h"

rlbot::flat::Vector3 vec3toVector3(const vec3 &v) {
    return {v[0], v[1], v[2]};
}

RLURenderer::RLURenderer(const std::string &name) : scopedRenderer(name) {
}

void RLURenderer::DrawLine3D(rlbot::Color color, const vec3 &start, const vec3 &end) {
    scopedRenderer.DrawLine3D(color, vec3toVector3(start), vec3toVector3(end));
}

void RLURenderer::DrawOBB(rlbot::Color color, const obb &box) {
    vec3 p = box.center;
    vec3 hw = box.half_width;
    mat3 o = box.orientation;
    dot(o, vec3{hw[0], hw[1], hw[2]});
    DrawLine3D(color, p + dot(o, vec3{-hw[0], -hw[1], -hw[2]}), p + dot(o, vec3{hw[0], -hw[1], -hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{-hw[0], -hw[1], hw[2]}), p + dot(o, vec3{hw[0], -hw[1], hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{-hw[0], hw[1], -hw[2]}), p + dot(o, vec3{hw[0], hw[1], -hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{-hw[0], hw[1], hw[2]}), p + dot(o, vec3{hw[0], hw[1], hw[2]}));

    DrawLine3D(color, p + dot(o, vec3{-hw[0], -hw[1], -hw[2]}), p + dot(o, vec3{-hw[0], hw[1], -hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{-hw[0], -hw[1], hw[2]}), p + dot(o, vec3{-hw[0], hw[1], hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{hw[0], -hw[1], -hw[2]}), p + dot(o, vec3{hw[0], hw[1], -hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{hw[0], -hw[1], hw[2]}), p + dot(o, vec3{hw[0], hw[1], hw[2]}));

    DrawLine3D(color, p + dot(o, vec3{-hw[0], -hw[1], -hw[2]}), p + dot(o, vec3{-hw[0], -hw[1], hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{hw[0], -hw[1], -hw[2]}), p + dot(o, vec3{hw[0], -hw[1], hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{-hw[0], hw[1], -hw[2]}), p + dot(o, vec3{-hw[0], hw[1], hw[2]}));
    DrawLine3D(color, p + dot(o, vec3{hw[0], hw[1], -hw[2]}), p + dot(o, vec3{hw[0], hw[1], hw[2]}));
}

void RLURenderer::DrawPolyLine3D(rlbot::Color color, const std::vector<vec3> &vertices) {
    std::vector<const rlbot::flat::Vector3 *> pointers(vertices.size());

    for (size_t i = 0; i < vertices.size(); i++) {
        pointers[i] = new rlbot::flat::Vector3(vec3toVector3(vertices[i]));
    }

    scopedRenderer.DrawPolyLine3D(color, pointers);

    for (auto p : pointers) {
        delete p;
    }
}

void RLURenderer::DrawString2D(const std::string &text, rlbot::Color color, vec2 topLeft, int scaleX, int scaleY) {
    scopedRenderer.DrawString2D(text, color, vec3toVector3(topLeft), scaleX, scaleY);
}

void RLURenderer::DrawString3D(const std::string &text, rlbot::Color color, const vec3 &topLeft, int scaleX, int scaleY) {
    scopedRenderer.DrawString3D(text, color, vec3toVector3(topLeft), scaleX, scaleY);
}

void RLURenderer::DrawRect2D(rlbot::Color color, const vec2 &topLeft, int height, int width, bool filled) {
    scopedRenderer.DrawRect2D(color, vec3toVector3(topLeft), width, height, filled);
}

void RLURenderer::DrawRect3D(rlbot::Color color, const vec3 &topLeft, int height, int width, bool filled, bool centered) {
    scopedRenderer.DrawRect3D(color, vec3toVector3(topLeft), width, height, filled, centered);
}
