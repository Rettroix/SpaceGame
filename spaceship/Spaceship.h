#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

// Class to handle the spaceship
class Spaceship : public GameObject
{
private:
  int score;
  Circle2D collisionShape;
  Vector2D m_velocity;		// Velocity of the ship
  Circle2D m_collider;		// Used for collision
  float m_shootDelay;       // Time in seconds before ship can shoot again
  bool m_thrusting;			// Whether ship is currently thrusting
  float m_fuel;         //The ship's fuel
  bool m_landed;
  float m_health;
  Vector2D gravity = Vector2D(0.0f, 1000.0f);
  bool isLanded;
  float m_friction;
  float m_acceleration;
  bool gameOver;
  float bullets;
  int enemyOneCoolDown;
  int m_lives;
  float m_respawnTime;
  bool m_respawnCounting;
  float m_frameTime;

  float health;
  int thrustTime;
public:
  Spaceship();
  void Initialise(Vector2D position);		// Sets to the starting position
  void Update(float frametime);			// Handle input, shooting and movement
  void Draw();
  IShape2D& GetCollisionShape();			// Provides a collision area
  void ProcessCollision(GameObject& other);	// Makes ship explode if hit by an asteroid
  void Explode();							// Deactivates ship and creates an explosion
  void fuelManagement();
  float getFuel();
  float getMaxFuel();

  void Bounce(GameObject &other);
  void Land(GameObject &other);
  float getAngle();
  Vector2D getVelocity();
  float getAcceleration();
  void thrustChange();
  void RotateTo(float angle);
  float getMaxBullets();
  float getBullets();
  float getMaxHealth();
  float getHealth();
  int getScore();
  bool isGameOver();
  void addScore(int ammount);
  Vector2D& getPosition();
};