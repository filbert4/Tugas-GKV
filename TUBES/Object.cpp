#include <GL/glut.h>
#include <cmath>
#include "Object.hpp"

void DrawSquare(float size, float length, float high, float x, float z, float direction) {
    float halfW = size * 0.5f;   // Setengah lebar
    float halfL = length * 0.5f; // Setengah panjang
    float halfH = high * 0.5f;   // Setengah tinggi

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f, 0.8f, 1.0f, 0.5f);  // RGBA (alpha 0.3 untuk transparan)
    glPushMatrix();
    
    glTranslatef(x, 0, z); // Sesuaikan tinggi objek dari ground
    glRotatef(direction, 0.0f, 1.0f, 0.0f); // Rotasi jika diperlukan
	
    glBegin(GL_QUADS);
    
	    // Sisi depan
	    glVertex3f(0.0f, 0, length);
	    glVertex3f(size, 0, length);
	    glVertex3f(size, size, length);
	    glVertex3f(0.0f, size, length);
	
	    // Sisi belakang
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(0.0f, size, 0.0f);
	    glVertex3f(size, size, 0.0f);
	
	    // Sisi kiri
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(0.0f, 0, length);
	    glVertex3f(0.0f, size, length);
	    glVertex3f(0.0f, size, 0.0f);
	
	    // Sisi kanan
	    glVertex3f(size, 0, length);
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(size, size, 0.0f);
	    glVertex3f(size, size, length);
	
	    // Sisi atas
	    glVertex3f(0.0f, size, length);
	    glVertex3f(size, size, length);
	    glVertex3f(size, size, 0.0f);
	    glVertex3f(0.0f, size, 0.0f);
	
	    // Sisi bawah
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(size, 0, length);
	    glVertex3f(0.0f, 0, length);


    glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
	    glTranslatef(x, 0, z); // Sesuaikan tinggi objek dari ground
	    glRotatef(direction, 0.0f, 1.0f, 0.0f); // Rotasi jika diperlukan
	    glLineWidth(3.0f); // Lebar garis neon
	    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan terang
	    glBegin(GL_LINE_LOOP);
    
		   	// Sisi depan
		    glVertex3f(0.0f, 0, length);
		    glVertex3f(size, 0, length);
		    glVertex3f(size, size, length);
		    glVertex3f(0.0f, size, length);
		
		    // Sisi belakang
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(0.0f, size, 0.0f);
		    glVertex3f(size, size, 0.0f);
		
		    // Sisi kiri
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(0.0f, 0, length);
		    glVertex3f(0.0f, size, length);
		    glVertex3f(0.0f, size, 0.0f);
		
		    // Sisi kanan
		    glVertex3f(size, 0, length);
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(size, size, 0.0f);
		    glVertex3f(size, size, length);
		
		    // Sisi atas
		    glVertex3f(0.0f, size, length);
		    glVertex3f(size, size, length);
		    glVertex3f(size, size, 0.0f);
		    glVertex3f(0.0f, size, 0.0f);
		
		    // Sisi bawah
		    glVertex3f(0.0f, 0, 0.0f);
		    glVertex3f(size, 0, 0.0f);
		    glVertex3f(size, 0, length);
		    glVertex3f(0.0f, 0, length);
    	glEnd();
    glPopMatrix();
    // Kembalikan state
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}

void BangunanRandom(float size, float length, float high, float x, float z, float direction) {
    float halfW = size * 0.5f;   // Setengah lebar
    float halfL = length * 0.5f; // Setengah panjang
    float halfH = high * 0.5f;   // Setengah tinggi

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(high/10*0.1f, high/10*0.9f, high/10*0.9f+0.4, 0.3f);  // RGBA (alpha 0.3 untuk transparan)
    glPushMatrix();
    
    glTranslatef(x, -1, z); // Sesuaikan tinggi objek dari ground
    glRotatef(direction, 0.0f, 1.0f, 0.0f); // Rotasi jika diperlukan
	
    glBegin(GL_QUADS);
    
	    // Sisi depan
	    glVertex3f(0.0f, 0, length);
	    glVertex3f(size, 0, length);
	    glVertex3f(size, high, length);
	    glVertex3f(0.0f, high, length);
	
	    // Sisi belakang
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(0.0f, high, 0.0f);
	    glVertex3f(size, high, 0.0f);
	
	    // Sisi kiri
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(0.0f, 0, length);
	    glVertex3f(0.0f, high, length);
	    glVertex3f(0.0f, high, 0.0f);
	
	    // Sisi kanan
	    glVertex3f(size, 0, length);
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(size, high, 0.0f);
	    glVertex3f(size, high, length);
	
	    // Sisi atas
	    glVertex3f(0.0f, high, length);
	    glVertex3f(size, high, length);
	    glVertex3f(size, high, 0.0f);
	    glVertex3f(0.0f, high, 0.0f);
	
	    // Sisi bawah
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(size, 0, length);
	    glVertex3f(0.0f, 0, length);


    glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
	    glTranslatef(x, -1, z); // Sesuaikan tinggi objek dari ground
	    glRotatef(direction, 0.0f, 1.0f, 0.0f); // Rotasi jika diperlukan
	    glLineWidth(5.0f); // Lebar garis neon
	    glColor4f(high/2*0.3f, high/2*1.0f, high /2*1.0f, 0.5f);
	    glBegin(GL_LINE_LOOP);
    
		// Sisi depan
	    glVertex3f(0.0f, 0, length);
	    glVertex3f(size, 0, length);
	    glVertex3f(size, high, length);
	    glVertex3f(0.0f, high, length);
	
	    // Sisi belakang
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(0.0f, high, 0.0f);
	    glVertex3f(size, high, 0.0f);
	
	    // Sisi kiri
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(0.0f, 0, length);
	    glVertex3f(0.0f, high, length);
	    glVertex3f(0.0f, high, 0.0f);
	
	    // Sisi kanan
	    glVertex3f(size, 0, length);
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(size, high, 0.0f);
	    glVertex3f(size, high, length);
	
	    // Sisi atas
	    glVertex3f(0.0f, high, length);
	    glVertex3f(size, high, length);
	    glVertex3f(size, high, 0.0f);
	    glVertex3f(0.0f, high, 0.0f);
	
	    // Sisi bawah
	    glVertex3f(0.0f, 0, 0.0f);
	    glVertex3f(size, 0, 0.0f);
	    glVertex3f(size, 0, length);
	    glVertex3f(0.0f, 0, length);
    	glEnd();
    glPopMatrix();
    // Kembalikan state
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}
