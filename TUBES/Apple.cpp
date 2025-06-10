// Apple.cpp
#include "Apple.hpp"
#include <GL/glut.h>
#include <cmath>

Apple::Apple(int minX, int maxX, int minZ, int maxZ, float yPos, float size)
    : minX(minX), maxX(maxX), minZ(minZ), maxZ(maxZ), y(yPos), size(size), rotation(0)
{
    // Inisialisasi seed untuk rand
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawn();
}

void Apple::spawn() {
    // Pilih posisi acak di grid integer dalam batas
    int ix = minX + std::rand() % ((maxX - minX) + 1);
    int iz = minZ + std::rand() % ((maxZ - minZ) + 1);
    x = ix * size + size/2;
    z = iz * size + size/2;
}

void Apple::update(float deltaTime) {
    rotation += 0.5f * deltaTime; // misal 45 derajat per detik
    if (rotation >= 360.0f) rotation -= 360.0f;
}

void Apple::draw() const {
    
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotation, 1.0f, 1.0f, 1.0f); // rotasi di sumbu Y
    glColor4f(0.5f, 0.8f, 1.0f, 1.0f);  // RGBA (alpha 0.3 untuk transparan)
    glLineWidth(5.0f); // Lebar garis neon
	    glBegin(GL_LINE_LOOP);
    		
		   	// Sisi depan
		    glVertex3f(0.0f, 0, size);
		    glVertex3f(size, 0, size);
		    glVertex3f(size, size, size);
		    glVertex3f(0.0f, size, size);
		
		    // Sisi belakang
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(0.0f, size, 0.0f);
		    glVertex3f(size, size, 0.0f);
		
		    // Sisi kiri
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(0.0f, 0, size);
		    glVertex3f(0.0f, size, size);
		    glVertex3f(0.0f, size, 0.0f);
		
		    // Sisi kanan
		    glVertex3f(size, 0, size);
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(size, size, 0.0f);
		    glVertex3f(size, size, size);
		
		    // Sisi atas
		    glVertex3f(0.0f, size, size);
		    glVertex3f(size, size, size);
		    glVertex3f(size, size, 0.0f);
		    glVertex3f(0.0f, size, 0.0f);
		
		    // Sisi bawah
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(size, 0, size);
		    glVertex3f(0.0f, 0, size);
    	glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(rotation+45, 1.0f, 1.0f, 1.0f); // rotasi di sumbu Y
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  // RGBA (alpha 0.3 untuk transparan)
	    glBegin(GL_LINE_LOOP);
    		
		   	// Sisi depan
		    glVertex3f(0.0f, 0, size);
		    glVertex3f(size, 0, size);
		    glVertex3f(size, size, size);
		    glVertex3f(0.0f, size, size);
		
		    // Sisi belakang
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(0.0f, size, 0.0f);
		    glVertex3f(size, size, 0.0f);
		
		    // Sisi kiri
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(0.0f, 0, size);
		    glVertex3f(0.0f, size, size);
		    glVertex3f(0.0f, size, 0.0f);
		
		    // Sisi kanan
		    glVertex3f(size, 0, size);
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(size, size, 0.0f);
		    glVertex3f(size, size, size);
		
		    // Sisi atas
		    glVertex3f(0.0f, size, size);
		    glVertex3f(size, size, size);
		    glVertex3f(size, size, 0.0f);
		    glVertex3f(0.0f, size, 0.0f);
		
		    // Sisi bawah
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(size, 0, size);
		    glVertex3f(0.0f, 0, size);
    	glEnd();
    glPopMatrix();
    glLineWidth(1.0f); // Lebar garis neon
}

void Apple::checkAndHandle(float headX, float headZ, Body& body, int& poin) {
    // Cek jarak horizontal (X,Z)
    float dx = headX - x;
    float dz = headZ - z;
    float dist = std::sqrt(dx*dx + dz*dz);
    // Threshold: sekitar ukuran blok
    if (dist < size) {
        // Dimakan: grow body dan respawn apel
        poin = poin + 1;
        body.grow();
        spawn();
    }
}

