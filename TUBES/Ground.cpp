// Ground.cpp
#include "Ground.hpp"
#include <GL/gl.h>

Ground::Ground(int size, float space)
    : gridSize(size), spacing(space) {}

void Ground::draw() const {
    glPushMatrix();
    // Geser seluruh grid sehingga petak kiri-bawah menjadi (0,0,0)
    glTranslatef(gridSize * spacing,
                 0.0f,
                 gridSize * spacing);

    glBegin(GL_LINES);
    for(int i = -gridSize; i <= gridSize; ++i) {
        // Garis paralel sumbu Z
        glVertex3f(i * spacing, 0, -gridSize * spacing);
        glVertex3f(i * spacing, 0,  gridSize * spacing);
        // Garis paralel sumbu X
        glVertex3f(-gridSize * spacing, 0, i * spacing);
        glVertex3f( gridSize * spacing, 0, i * spacing);
    }
    glEnd();
    glPopMatrix();
}
