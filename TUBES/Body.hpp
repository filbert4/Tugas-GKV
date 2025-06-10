// Body.hpp
#pragma once

#include <vector>
#include "Player.hpp"

// Struktur mewakili posisi segmen/kepala
struct Segment {
    float x, y, z;
};

// Kelas Body: mengatur badan ular mengikuti jejak kepala
class Body {
public:
    // initialLength: jumlah segmen awal
    // segmentSize: jarak antar segmen
    Body(int initialLength = 3, float segmentSize = 1.0f, Player* player = nullptr);

	const std::vector<Segment>& getSegments() const { return segments; }

    // Update posisi: simpan head path dan atur tiap segmen mengikuti path
    void update(float headX, float headY, float headZ);

    // Tambah satu segmen di ekor
    void grow();

    // Gambar semua segmen sebagai kubus
    void draw() const;

private:
    std::vector<Segment> segments;      // posisi segmen yang digambar
    std::vector<Segment> headPath;     // jejak posisi kepala
    float size;                     // jarak antar segmen
    Segment lastHeadPos;                // posisi kepala saat node terakhir ditambahkan
};

