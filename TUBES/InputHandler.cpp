#include "InputHandler.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include <ctime> // untuk clock()

extern Player player;
extern Camera camera;

const float moveSpeed = 0.1f;
const float turnSpeed = 90; // derajat per tekan

void keyboard(int key, int x, int y) {
    static clock_t lastInputTime = 0;
    clock_t now = clock();
    double elapsed = double(now - lastInputTime) / CLOCKS_PER_SEC;
 	
    if (elapsed < 0.6f)
        return;

    lastInputTime = now;

    switch (key) {
        case GLUT_KEY_LEFT:
            player.rotateYaw(turnSpeed);
            break;
        case GLUT_KEY_RIGHT:
            player.rotateYaw(-turnSpeed);
            break;
    }
}
