// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include "Player.hpp"

// Kelas Camera: mengatur posisi dan orientasi kamera di belakang player
class Camera {
public:
    // Jarak kamera di belakang player
    float distance;
    // Ketinggian kamera relatif terhadap player
    float height;

    Camera(float dist = 2.0f, float h = 1.0f);

    // Update kamera berdasarkan posisi player
    void update(const Player& player);
    // Terapkan view matrix
    void apply() const;
	
private:
    float eyeX, eyeY, eyeZ;
    float centerX, centerY, centerZ;
};

#endif // CAMERA_H
