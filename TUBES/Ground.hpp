// Ground.h
#ifndef GROUND_H
#define GROUND_H

// Kelas Ground: grid di bidang XZ
class Ground {
public:
    int gridSize;    // setengah jumlah grid
    float spacing;   // jarak antar garis

    Ground(int size = 10, float space = 1.0f);
    void draw() const;
};

#endif // GROUND_H
