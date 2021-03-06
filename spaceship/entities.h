//Title     : entities.cpp
//Purpose   : Entites only includes two entities, city - which manages buildings and such,
//            and the player bullets.
//Author    : Elliot Anderson
//Date      : 5/12/16

#pragma once

#include "Lander.h"
#include "GameObject.h"
#include "mysoundengine.h"
#include "Spaceship.h"
#include "Building.h"

#include "BuildingForeground.h"
#include "BuildingBackground.h"
#include "BuildingTypes.h"
#include "collisionShaper.h"
#include <stdlib.h>     
#include <time.h>       

const int NUMBER_OF_BUILDINGS = 20;




//A class which manages the level such as enemies and buildings
class City : public GameObject
{
private:   
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance(); //Calling a pointer to an instance of sound engine

  bool gameStarted; //is the game started
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  int spawnedBuildings[10];
  Vector2D shipsPosition;
  int shipXValue;
  float fship;
  Spaceship *m_pPlayer; //pointer to player
  Building *m_pBuildings[NUMBER_OF_BUILDINGS];  //pointers to buildings
  BuildingForeground *m_pForegroundBuildings[NUMBER_OF_BUILDINGS];  //pointer to foreground buildings
  BuildingBackground *m_pBackgroundBuildings[NUMBER_OF_BUILDINGS];   //pointer to background buildings
  Lander *pCollision[NUMBER_OF_BUILDINGS];
  Lander *pCollisionTop[NUMBER_OF_BUILDINGS];
  Lander *pCollisionRight[NUMBER_OF_BUILDINGS];

  
  int furthestLeft; //Building furthest to the left
  int furthestRight; //Building furthest to the right
  int middle; //middle building
  int lastIndex; //The previously indexed building in the loop

  int furthestLeftBG; //Building furthest to the left BG
  int furthestRightBG; //Building furthest to the right BG
  int middleBG; //middle building
  int lastIndexBG; //The previously indexed building in the loop

  int furthestLeftFG; //Building furthest to the left FG
  int furthestRightFG; //Building furthest to the right FG
  int middleFG; //middle building
  int lastIndexFG; //The previously indexed building in the loop

  int enemyOneCoolDown;   //Enemies can't spawn when this is above 0
  int enemyAmmount;   //how many enemies are spawned
  int maxEnemyAmmount;  //The max ammount of ennemies allowed

  BuildingType selectedBuilding = BuildingType::BUILDING0;
  int randomBuilding;

  bool m_musicPlaying; //is music playing
public:
  
  void Initialise(Spaceship *player);
  void Update(float frameTime);
  void spawnBuilding(); //spawn buildings
  void spawnBG(); //spawn background buildings
  void spawnFG(); //spawn foreground buildings
  void spawnEnemies();  //Spawn enemies
  void updateBuildings(); //Update Buildings
  void updateBuildingsBG(); //Update background buildings
  void updateBuildingsFG(); //Update foreground buildings
  void StopMusic(); //Stop the backgroud music
  IShape2D& GetCollisionShape();  //Get collision shape
  void ProcessCollision(GameObject& other); //Process collisions
  int getMiddlePosition();  //get the middle position of the building array
  void deincrementEnemyAmmount();   //deincrement the ammount of enemies on screen
  void spawnBuildingBlock(int interation); //spawn a building
  void spawnCollisionBlockLeft(int iteration, int pos1, int pos2, int pos3, int pos4, int coltype);     //spawns the collision for the left side of the building
  void spawnCollisionBlockRight(int iteration, int pos1, int pos2, int pos3, int pos4, int coltype);  //spawns the collision for the right side of the building
  void spawnCollisionBlockTop(int iteration, int pos1, int pos2, int pos3, int pos4, int coltype);  //spawns the collision for the top side of the building
  void LoadParticles();
  City();
};




//A bullet shot by the player
class Bullet : public GameObject
{
private:
  Vector2D m_velocity;
  Circle2D collisionShape;
  float m_acceleration;
  float m_timer;  // Lifetime

  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame

  //sound
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
  SoundIndex hit = pSoundEngine->LoadWav(L"hit.wav");
public:
  Bullet();
  void Initialise(Vector2D position, Vector2D velocity, float angl);
  void Update(float frametime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject& other);
  
};


