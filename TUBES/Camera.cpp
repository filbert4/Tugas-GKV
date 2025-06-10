// Camera.cpp
#include "Camera.hpp"
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath> 

Camera::Camera(float dist, float h)
    : distance(dist), height(h), eyeX(0), eyeY(0), eyeZ(0), centerX(0), centerY(0), centerZ(0) {}

void Camera::update(const Player& player) {
    float rad = player.yaw * std::acos(-1) / 180.0f;

    // Hitung posisi kamera di belakang player mengikuti yaw
    eyeX = player.x - cosf(rad) * (distance + 1);
    eyeY = player.y + height;
    eyeZ = player.z + sinf(rad) * (distance+1);
//	eyeX = 10*2;
//    eyeY = 80;
//    eyeZ = 10*2;

    // Fokus tetap ke posisi player (pusat kubus)
    centerX = player.x;
    centerY = player.y + 2;
    centerZ = player.z;
//	centerX = 10*2;
//    centerY = 0;
//    centerZ = 10*2;	
}


void Camera::apply() const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ,
              centerX, centerY, centerZ,
              0.0f, 1.0f, 0.0f);
}
