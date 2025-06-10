// Apple.hpp
#pragma once

#include "Body.hpp"
#include <cstdlib>
#include <ctime>

// Kelas Apple: apel yang muncul di area ground dan respawn saat dimakan
class Apple {
public:
    // minX, maxX, minZ, maxZ menentukan batas area ground
    // yPos: ketinggian apel di sumbu Y
    // size: ukuran blok/grid
    Apple(int minX, int maxX, int minZ, int maxZ, float yPos = 0.5f, float size = 1.0f);

    // Gambar apel
    void draw() const;

    // Cek apakah kepala di (headX, headZ) memakan apel
    // Jika benar, panggil grow pada body dan respawn apel
    void checkAndHandle(float headX, float headZ, Body& body, int& poin);

    // Dapatkan posisi apel
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    void update(float deltaTime);
	float rotation;
private:
    int minX, maxX, minZ, maxZ;
    float x, y, z;
    float size;

    // Spawn apel di posisi acak dalam batas
    void spawn();
};
