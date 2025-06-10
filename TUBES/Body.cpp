// Body.cpp
#include "Body.hpp"
#include <GL/glut.h>
#include <cmath>

Body::Body(int initialLength, float segmentSize, Player* player)
    : size(segmentSize), lastHeadPos{player->getX(), 0.0f, player->getZ()}
{
    // Inisialisasi segmen pada (0,0,0)
    segments.resize(initialLength, {player->getX(), 0.0f, player->getZ()});
    // headPath awal dengan satu titik sama dengan lastHeadPos
    headPath.push_back(lastHeadPos);
}

void Body::update(float headX, float headY, float headZ) {
    // Cek jarak tempuh kepala sejak lastHeadPos
    float dx = headX - lastHeadPos.x;
    float dy = headY - lastHeadPos.y;
    float dz = headZ - lastHeadPos.z;
    float dist = std::sqrt(dx*dx + dy*dy + dz*dz);
    // Jika bergerak melebihi size, tambahkan titik path baru
    if (dist+0.5f >= size) {
        lastHeadPos = {headX, headY, headZ};
        headPath.push_back(lastHeadPos);
    }
    
    // Pastikan headPath tidak terlalu panjang: cukup simpan (segments.size()+1) poin terakhir
    size_t maxPoints = segments.size() + 1;
    if (headPath.size() > maxPoints) {
        // hapus poin terlama
        headPath.erase(headPath.begin(), headPath.begin() + (headPath.size() - maxPoints));
    }

    // Setiap segmen mengikuti path: segmen i mengambil headPath dari index (maxPoints - 2 - i)
    // index maxPoints-1 = head saat ini, maxPoints-2 = posisi untuk segmen pertama, dst.
    size_t pathSize = headPath.size();
    for (size_t i = 0; i < segments.size(); ++i) {
        size_t idx = (pathSize - 2 >= i) ? (pathSize - 2 - i) : 0;
        segments[i] = headPath[idx];
    }
}

void Body::grow() {
    // Tambah satu segmen di ekor: ambil posisi segmen terakhir
    Segment tail = segments.empty() ? lastHeadPos : segments.back();
    segments.push_back(tail);
}

void Body::draw() const {
    float half = size * 0.5f;
    for (const auto& seg : segments) {
        glPushMatrix();
        glColor4f(0.5f, 1.0f, 1.0f, 1.0f); // Cyan terang
        glTranslatef(seg.x, seg.y, seg.z);
        glBegin(GL_QUADS);
            // Front face
            glVertex3f(-half, -half,  half);
            glVertex3f( half, -half,  half);
            glVertex3f( half,  half,  half);
            glVertex3f(-half,  half,  half);
            // Back face
            glVertex3f( half, -half, -half);
            glVertex3f(-half, -half, -half);
            glVertex3f(-half,  half, -half);
            glVertex3f( half,  half, -half);
            // Left face
            glVertex3f(-half, -half, -half);
            glVertex3f(-half, -half,  half);
            glVertex3f(-half,  half,  half);
            glVertex3f(-half,  half, -half);
            // Right face
            glVertex3f( half, -half,  half);
            glVertex3f( half, -half, -half);
            glVertex3f( half,  half, -half);
            glVertex3f( half,  half,  half);
            // Top face
            glVertex3f(-half,  half,  half);
            glVertex3f( half,  half,  half);
            glVertex3f( half,  half, -half);
            glVertex3f(-half,  half, -half);
            // Bottom face
            glVertex3f(-half, -half, -half);
            glVertex3f( half, -half, -half);
            glVertex3f( half, -half,  half);
            glVertex3f(-half, -half,  half);
        glEnd();
        glPopMatrix();
    }
}

