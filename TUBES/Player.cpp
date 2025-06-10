// Player.cpp
#include "Player.hpp"
#include <GL/glut.h>
#include <cmath>

Player::Player(float startX, float startY, float startZ, float size)
    : x(startX), y(startY), z(startZ),
      halfSize(size), yaw(0), targetYaw(0), rotationSpeed(2.0f) {}

float Player::getX() {
	return x;
}

float Player::getZ() {
	return z;
}

void Player::draw() const {
    glPushMatrix();
    // Pindah ke posisi
    glTranslatef(x, y, z);
    // Rotasi pada sumbu Y
    glRotatef(yaw, 0.0f, 1.0f, 0.0f);
	glColor4f(0.5f, 1.0f, 1.0f, 1.0f); // Cyan terang
    // Gambar kubus
    glBegin(GL_QUADS);
        // Front face
        glVertex3f(-halfSize, 0,  halfSize);
        glVertex3f( halfSize, 0,  halfSize);
        glVertex3f( halfSize,  halfSize,  halfSize);
        glVertex3f(-halfSize,  halfSize,  halfSize);
        // Back face
        glVertex3f( halfSize, 0, -halfSize);
        glVertex3f(-halfSize, 0, -halfSize);
        glVertex3f(-halfSize,  halfSize, -halfSize);
        glVertex3f( halfSize,  halfSize, -halfSize);
        // Left face
        glVertex3f(-halfSize, 0, -halfSize);
        glVertex3f(-halfSize, 0,  halfSize);
        glVertex3f(-halfSize,  halfSize,  halfSize);
        glVertex3f(-halfSize,  halfSize, -halfSize);
        // Right face
        glVertex3f( halfSize, 0,  halfSize);
        glVertex3f( halfSize, 0, -halfSize);
        glVertex3f( halfSize,  halfSize, -halfSize);
        glVertex3f( halfSize,  halfSize,  halfSize);
        // Top face
        glVertex3f(-halfSize,  halfSize,  halfSize);
        glVertex3f( halfSize,  halfSize,  halfSize);
        glVertex3f( halfSize,  halfSize, -halfSize);
        glVertex3f(-halfSize,  halfSize, -halfSize);
        // Bottom face
        glVertex3f(-halfSize, 0, -halfSize);
        glVertex3f( halfSize, 0, -halfSize);
        glVertex3f( halfSize, 0,  halfSize);
        glVertex3f(-halfSize, 0,  halfSize);
    glEnd();
    glPopMatrix();
}

void Player::update(float deltaTime) {
    float distancePerSecond = 0.05f;
    // Hitung selisih sudut ke target
    float delta = targetYaw - yaw;
    if (delta > 180.0f) delta -= 360.0f;
    if (delta < -180.0f) delta += 360.0f;

    // Parameter smoothing
    float smoothing = 0.1f;
    float alpha = 1.0f - std::exp(-smoothing * deltaTime);

    const float turnThreshold = 0.5f; // toleransi sudut (derajat)
    if (std::fabs(delta) > turnThreshold) {
        // Masih berputar: lerp menuju targetYaw
        yaw += delta * alpha;
        // normalisasi yaw
        if (yaw >= 360.0f) yaw -= 360.0f;
        if (yaw < 0.0f)   yaw += 360.0f;
        // Tidak bergerak maju saat berputar
    } else {
        // Sudah menghadap dekat target, set langsung
        yaw = targetYaw;
        // normalisasi yaw
        if (yaw >= 360.0f) yaw -= 360.0f;
        if (yaw < 0.0f)   yaw += 360.0f;
        // Bergerak maju saat tidak berputar
        moveForward(distancePerSecond * deltaTime);
    }
}

void Player::moveForward(float distance) {
    // Gerak maju sesuai arah yaw
    float rad = yaw * std::acos(-1) / 180.0f;
    z -= sinf(rad) * distance;
    x += cosf(rad) * distance;
}

void Player::rotateYaw(float angleDeg) {
    targetYaw  += angleDeg;
    // Jaga dalam [0, 360)
    if (targetYaw  >= 360.0f) targetYaw  -= 360.0f;
    if (targetYaw  < 0.0f)  targetYaw  += 360.0f;
}
