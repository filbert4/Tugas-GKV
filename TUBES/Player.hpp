// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
public:
    Player(float startX, float startY, float startZ, float size);
    void draw() const;
    void update(float deltaTime);
    void moveForward(float distance);
    void rotateYaw(float angleDeg);
	float getX();
	float getZ();
	float yaw;
	float x, y, z;
    float halfSize;
    float targetYaw;
    float rotationSpeed;
    bool isRotating;
private:
    
    
};

#endif // PLAYER_HPP
