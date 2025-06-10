// main.cpp
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include <random>
#include "Object.hpp"
#include "Player.hpp"
#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Ground.hpp"
#include "Body.hpp"
#include "Apple.hpp"

float gridSize = 20; 
float spacing = 1.0f;

Ground  ground(gridSize, spacing);
Player player(0.0f+spacing/2, 0, 0.0f+spacing/2 + 0.1f, spacing/2);
Camera camera(2.0f, 3.0f);
Body body(1, 1.0f, &player);
Apple apple(0, gridSize, 0, gridSize, spacing/2, spacing);

int poin = 0;

// Utility: Draw text on screen
void drawString(void* font, const std::string& str, float x, float y) {
    glRasterPos2f(x, y);
    const char* c = str.c_str();
    while (*c) {
        glutBitmapCharacter(font, *c);
        ++c;
    }
}

void checkGameOver(const Body& body, int size, float spacing) {
    float headX = player.getX();
    float headZ = player.getZ();

    // 1) Boundary check
    float worldMinX = 0 - 0.2f;
    float worldMaxX = gridSize * spacing*2 + 0.5f;
    float worldMinZ = 0 - 0.2f;
    float worldMaxZ = gridSize * spacing*2 + 0.5f;

    if (headX < worldMinX || headX > worldMaxX ||
        headZ < worldMinZ || headZ > worldMaxZ)
    {
        std::cout << "Game Over: Snake keluar dari batas ground!\n";
        std::exit(0);
    }

    // 2) Self-collision: head berjarak terlalu dekat ke salah satu segmen
    const auto& segs = body.getSegments();
    for (size_t i = 1; i < segs.size(); ++i) {
        float dx = headX - segs[i].x;
        float dz = headZ - segs[i].z;
        float dist = std::sqrt(dx*dx + dz*dz);

        // threshold ~ setengah block size
        if (dist < spacing * 0.5f) {  
            std::cout << "Game Over: Snake menabrak badan sendiri!\n";
            std::exit(0);
        }
    }
}

// 1. Fungsi inisialisasi OpenGL, panggil sekali di awal (misal di main sebelum glutMainLoop())
void initLighting() {
    // Aktifkan depth test agar shading dan z-buffer bekerja benar
    glEnable(GL_DEPTH_TEST);

    // Aktifkan lighting secara global
    glEnable(GL_LIGHTING);

    // 2. Aktifkan sumber cahaya GL_LIGHT0
    glEnable(GL_LIGHT0);

    // 3. Tentukan properti GL_LIGHT0
    //   a) Position: (x, y, z, w). Jika w=1, ini titik cahaya; w=0 ? directional light.
    GLfloat lightPos[]    = {  20/2,  -1.0f,  20/2,  0.0f };
    //   b) Warna ambient (cahaya latar): area minimum
    GLfloat lightAmbient[]= {  0.8f,   0.8f,   0.8f,   1.0f };
    //   c) Warna diffuse (cahaya utama)
    GLfloat lightDiffuse[]= {  0.1f,   0.1f,   0.8f,   1.0f };
    //   d) Warna specular (cahaya pantulan kilau)
    GLfloat lightSpecular[]= { 0.1f,   0.1f,   0.1f,   1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // 4. Aktifkan color material agar glColor3f(…) memengaruhi material
    glEnable(GL_COLOR_MATERIAL);
    // Gunakan glColor untuk mengubah properti difuse material
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // 5. Agar normal yang di-skala (jika ada scaling pada model) otomatis dinormalisasi
    glEnable(GL_NORMALIZE);
}

void LatarBelakang() {
	// Pembatas
	DrawSquare(spacing, 40+2, spacing, -1, 0, 90); // Contoh koordinat
	DrawSquare(spacing, 40+2, spacing, -1, -1, 0); // Contoh koordinat
	DrawSquare(spacing, 40+2, spacing, -1, gridSize*2+1, 90); // Contoh koordinat
	DrawSquare(spacing, 40+2, spacing, gridSize*2+1, gridSize*2+1, 180); // Contoh koordinat
	
	// Bangunan
	std::random_device rd;  // Seed acak dari perangkat
    std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> distrib(1, 10); // Rentang [1,10]
    int angka = distrib(gen);
    int i = 0;
	while (i <= gridSize*2+2) {
		int angka = distrib(gen);
		BangunanRandom(spacing-0.1f, spacing, spacing+angka, i-1, -3, 0 );
		i += 1.1f;
	}
	i = 0;
	while (i <= gridSize*2+2) {
		int angka = distrib(gen);
		BangunanRandom(spacing-0.1f, spacing, spacing+angka, -3, i-1, 90 );
		i += 1.1f;
	}
	i = 0;
	while (i <= gridSize*2+2) {
		int angka = distrib(gen);
		BangunanRandom(spacing-0.1f, spacing, spacing+angka, i-1, gridSize*2+3, 180 );
		i += 1.1f;
	}
	i = 0;
	while (i <= gridSize*2+2) {
		int angka = distrib(gen);
		BangunanRandom(spacing-0.1f, spacing, spacing+angka, gridSize*2+3, gridSize*2+3-i-1, -90 );
		i += 1.1f;
	}
}

void display() {
	
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	LatarBelakang();
    // Update scene
    player.update(0.1f);
    camera.update(player);
    camera.apply();

	// <<< Tambahkan baris berikut >>>
    body.update(player.getX(), 0.0f, player.getZ());
	
	apple.checkAndHandle(player.getX(), player.getZ(), body, poin);
	
	// Sebelum draw ground/player/body
	apple.draw();
    
    // Draw ground and player
    glColor3f(0.6f, 0.6f, 0.6f);
    ground.draw();
    glColor3f(1.0f, 0.0f, 0.0f);
    player.draw();

	// <<< Gambar body ular setelah player >>>
    body.draw();

    // Prepare HUD: switch to orthographic projection
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Disable depth test and lighting for HUD
    glDisable(GL_DEPTH_TEST);

    // Compose position string
    std::ostringstream oss;
    oss << "Score: " << poin;
    std::string posStr = oss.str();

    // Draw text in top-left corner (with some margin)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawString(GLUT_BITMAP_HELVETICA_18, posStr, 10.0f, h - 20.0f);

    // Restore states
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    // Swap buffers
    glutSwapBuffers();
}

void idle() {

	checkGameOver(body, gridSize, spacing);
	apple.update(0.1f);
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Cube Player with HUD");
	
	initLighting();
	
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);

    std::cout << "Game started. HUD shows player X and Z." << std::endl;

    glutMainLoop();
    return 0;
}

