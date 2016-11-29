#include "Spaceship.h"
#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "Building.h"
#include "Explosion.h"
#include "Particles.h"
#include "missile.h"
#include "EnemyOne.h"
#include "playerMissile.h"
const float MAXBULLETS = 50;
const float MAXHEALTH = 100;
const float BULLETSPEED = 2000.0f;
const float TURNSPEED = 3.0f;     // Radians per second
const float ACCELERATION = 5000.0f; // Units per second^2
const float FRICTION = 1.5f;    // Fraction of speed to lose per deltaT
const float SHOOTDELAY = 0.25f;	// Time between each spaceship bullet
const float BASEASTEROIDSIZE = 100.0f;	// Diameter of the basic asteroid
const float SHIPSIZE = 64.0f;			// Diameter of the ship
const float MAXFUEL = 1000;
const float RESPAWNTIME = 3.0f;
//const Vector2D GRAVITY = Vector2D(0.0f, 400.0f);

//////////////////////////////////////////////////
////////////////spaceship/////////////////////////
/////////////////////////////////////////////////
// Set the object's type
Spaceship::Spaceship() : GameObject(SPACESHIP)
{
  m_drawDepth = 6;
}

// Starting position and load the image
void Spaceship::Initialise(Vector2D position)
{
  m_isInvinsible = false;
  gameOver = false;
  srand(time(NULL));
  score = 0;
  bullets = MAXBULLETS;
  m_respawnTime = RESPAWNTIME;
  m_respawnCounting = false;
  m_friction = 1.5f;
  isLanded = false;
  m_position = position;
  m_shootDelay = 0.0f;
  m_angle = 0.0f;
  m_velocity.set(0, 0);
  m_objectSize = Vector2D(256, 256)*m_imageScale;
  m_acceleration = 5000.0f;
  LoadImage(L"ship.png");
  LoadImage(L"invisible.bmp");
  //m_imageScale = SHIPSIZE / 16;	// 64 pixel image file
  m_fuel = MAXFUEL;
  m_lives = 3;
  health = MAXHEALTH;
  m_transparency = 0;
  m_bombCounter = 0;
}


void Spaceship::Update(float frametime)
{
  if (m_angle >= 6.3)
  {
    m_angle = 0;

  }

  if (m_angle <= -6.3)
  {
    m_angle = 0;

  }


  if (health <= 0)
  {
    gameOver = true;
  }
    
  m_frameTime = frametime;
 
  m_position.XValue;

  //explode
  if (m_respawnCounting == true)
  {
    m_invinsibleTime = 3;
    gravity = Vector2D(0.0f, 0.0f);
    m_position = m_position;
    m_respawnTime -= m_frameTime;
  }

  //respawning
  if (m_respawnTime < 0 && !gameOver)
  {
    gravity = Vector2D(0.0f, 1000.0f);
    m_imageNumber = 0;
    m_respawnTime = RESPAWNTIME;
    m_position = Vector2D(m_position.XValue - 600, 400);
    m_fuel = MAXFUEL;
    bullets = MAXBULLETS;
    m_respawnCounting = false;
    m_isInvinsible = true;
  }

  if (m_invinsibleTime > 0 && m_isInvinsible == true)
  {
    m_invinsibleTime -= m_frameTime;
    m_transparency = 0.5;

  }
  else if (m_invinsibleTime < 0)
  {
    m_transparency = 0;
    m_isInvinsible = false;
    m_invinsibleTime = 3;
  }

  // Get input and set acceleration
  MyInputs* pInputs = MyInputs::GetInstance();
  pInputs->SampleKeyboard();
  //global.shipAngle = m_angle;
  thrustChange();
  if (m_fuel > 0 && !m_respawnCounting)
  {
    if (pInputs->KeyPressed(DIK_LEFT))  // Turn left
    {
      m_angle -= TURNSPEED *frametime;
    }
    if (pInputs->KeyPressed(DIK_RIGHT)) // Turn right
    {
      m_angle += TURNSPEED *frametime;
    }
    if (pInputs->KeyPressed(DIK_UP) && m_position.YValue < 1200)    // Thrust
    {
      isLanded = false;
      if (!m_thrusting)		// If not thrusting last frame
      {
        // g_soundFX.StartThrust();	// Start the thrust sound
      }
      m_thrusting = true;			// Remember we are thrusting
      Vector2D acc;
      acc.setBearing(m_angle, m_acceleration);
      m_velocity = m_velocity + acc*frametime;
      m_fuel--;
      

      // Add a fire trail for thrust effect
      Explosion* pExp = new Explosion;
      Vector2D flameDirection;      // The flames move
      flameDirection.setBearing(m_angle + 3.141f, 600);  // Out of the back of the ship
      pExp->Initialise(m_position, flameDirection, 68.0f, 1.0f);
      Game::instance.m_objects.AddItem(pExp, false);		// Add to the engine


    }
    else	// Not thrusting
    {
      if (m_thrusting)		// If  thrusting last frame
      {
        //g_soundFX.StopThrust();	// Stop the thrust sound
      }
      m_acceleration = 2000;
      m_thrusting = false;			// Remember we are thrusting hahg gay
    }

    // Handle shooting
    if (pInputs->KeyPressed(DIK_SPACE) && m_shootDelay<0 && bullets > 0)    // Shoot
    {
      bullets--;
      m_shootDelay = SHOOTDELAY;				// Makes it wait before it can shoot again
      Vector2D pos;
      Vector2D vel;
      pos.setBearing(m_angle, SHIPSIZE / 2);	// Offset the starting location to the front of the ship
      pos = pos + m_position;
      vel.setBearing(m_angle, BULLETSPEED);	// Set the velocity
      vel = vel + Vector2D(m_velocity);					// Include the launching platform's velocity

      Bullet* pBullet = new Bullet;
      pBullet->Initialise(pos, vel, m_angle);			// Intialise
      Game::instance.m_objects.AddItem(pBullet, true);	// Add to the engine
      //g_soundFX.PlayZap();					// PLay zap sound effect
    }

    if (pInputs->KeyPressed(DIK_X) && m_bombCounter == 5 )    // Shoot
    {
      m_bombCounter = 0;
      Vector2D pos;
      Vector2D vel;
      pos.setBearing(m_angle, SHIPSIZE / 2);	// Offset the starting location to the front of the ship
      pos = pos + m_position;
      vel.setBearing(0, BULLETSPEED);	// Set the velocity
      vel = vel + Vector2D(m_velocity);					// Include the launching platform's velocity

      PlayerMissile* pPlayerMissile = new PlayerMissile;
      pPlayerMissile->Initialise(pos, vel, 0.0f, this);			// Intialise
      Game::instance.m_objects.AddItem(pPlayerMissile, true);	// Add to the engine

      Vector2D velTwo;
      velTwo.setBearing(1.5f, BULLETSPEED);	// Set the velocity
      velTwo = velTwo + Vector2D(m_velocity);					// Include the launching platform's velocity

      PlayerMissile* pPlayerMissileTwo = new PlayerMissile;
      pPlayerMissileTwo->Initialise(pos, velTwo, 1.5f, this);			// Intialise
      Game::instance.m_objects.AddItem(pPlayerMissileTwo, true);	// Add to the engine

      Vector2D velThree;
      velThree.setBearing(3.1f, BULLETSPEED);	// Set the velocity
      velThree = velThree + Vector2D(m_velocity);					// Include the launching platform's velocity

      PlayerMissile* pPlayerMissileThree = new PlayerMissile;
      pPlayerMissileThree->Initialise(pos, velThree, 3.1f, this);			// Intialise
      Game::instance.m_objects.AddItem(pPlayerMissileThree, true);	// Add to the engine

      Vector2D velFour;
      velFour.setBearing(4.7f, BULLETSPEED);	// Set the velocity
      velFour = velFour + Vector2D(m_velocity);					// Include the launching platform's velocity

      PlayerMissile* pPlayerMissileFour = new PlayerMissile;
      pPlayerMissileFour->Initialise(pos, velFour, 4.7f, this);			// Intialise
      Game::instance.m_objects.AddItem(pPlayerMissileFour, true);	// Add to the engine
    }
    m_shootDelay -= frametime;					// Cool down the gun so it can shoot again.




  }

  //for landing

  if (!isLanded)
  {
    m_velocity = m_velocity - gravity *frametime;
    
  }
  else
  {
    RotateTo(0);
  }

  //Bomb Counter
  if (m_bombCounter > 5)
  {
    m_bombCounter = 5;
  }

  // Process movement
  m_velocity = m_velocity - m_friction*frametime*m_velocity;
  m_position = m_position + m_velocity*frametime;

  MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue - 300,0 - m_position.YValue + 20));




}

void Spaceship::Draw()
{
  GameObject::Draw();
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->FillCircle(m_position, collisionShape.GetRadius(), 65525);

}

IShape2D& Spaceship::GetCollisionShape()
{
  // Place at the centre of the ship and slightly smaller than the image
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;
}

void Spaceship::ProcessCollision(GameObject& other)
{
  if (other.GetType() == LANDER && !m_respawnCounting)
  {
    Lander *pOtherBuilding = dynamic_cast<Lander*> (&other);

    if (pOtherBuilding->getCollisionReaction() == CollisionType::BOUNCE)
    {

      if (m_acceleration >= 3000)
      {
        Explode();
      }
      else
      {//bounce
        Bounce(other);
      }


      //m_velocity = Vector2D(0.0f, 0.0f);
      //m_angle = 0;
    }

    if (pOtherBuilding->getCollisionReaction() == CollisionType::LANDER &&!m_respawnCounting)
    {
      if (getSpeed() >= 1200)
      {
        Explode();
      }
      else
      {
        Land(other);
      }
      m_velocity = Vector2D(0.0f, 0.0f);
      
    }

  }
  //m_fuel--;
  //HitObject(other);


  if (other.GetType() == ENEMY && !m_respawnCounting && m_isInvinsible == false)
  {
    Explode();
  }



  if (other.GetType() == FLOOR && !m_respawnCounting)
  {
    if (getSpeed() >= 1200)
    {
      Explode();
    }

    else
    {
      isLanded = true;


      m_position.YValue = other.GetPosition().YValue - 1020;
    }

    m_velocity = Vector2D(0.0f, 0.0f);
    m_angle = 0;
    
  }
  //if (other.GetType() == ASTEROID)
  //  Explode();
}

void Spaceship::Explode()
{
  health=health-20;
  //Deactivate();
  m_imageNumber = 1;
  Explosion* pExp = new Explosion;
  //  g_soundFX.PlayExplosion();

  pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 4.5f);

  Game::instance.m_objects.AddItem(pExp, false);

  Particles* pParticles = new Particles;
  pParticles->Initialise(m_position, Vector2D(0, 0), 4.5f, 2.0f);
  Game::instance.m_objects.AddItem(pParticles, false);

  m_respawnCounting = true;

  // g_soundFX.StopThrust();			// In case it is playing
}

void Spaceship::Bounce(GameObject &other)
{
  Lander *pOtherBuildingTwo = dynamic_cast<Lander*> (&other);

  Vector2D normal = collisionShape.CollisionNormal(pOtherBuildingTwo->GetShape());
  normal = normal.unitVector();



  m_velocity = m_velocity - (2*normal*m_velocity)*normal;
  m_health--;


  //m_position = m_position + m_velocity*globalframetime;
  //m_position = m_position - GRAVITY *globalframetime;


}

void Spaceship::Land(GameObject &other)
{
  Lander *pOtherLander = dynamic_cast<Lander*> (&other);
  if (pOtherLander->GetColType() == 1)
  {
    m_fuel = MAXFUEL;
    bullets = MAXBULLETS;
  }

  //landing collision
  isLanded = true;
  

  m_position.YValue = other.GetPosition().YValue + 100;


}

float Spaceship::getFuel()
{
  return m_fuel;
}

float Spaceship::getMaxFuel()
{
  return MAXFUEL;
}
float Spaceship::getAngle()
{
  return m_angle;
}

float Spaceship::getAcceleration()
{
  return m_acceleration;
}

Vector2D Spaceship::getVelocity()
{
  return m_velocity;
}

Vector2D& Spaceship::getPosition()
{
  return m_position;
}

float Spaceship::getMaxBullets()
{
  return MAXBULLETS;
}

float Spaceship::getBullets()
{
  return bullets;
}

float Spaceship::getMaxHealth()
{
  return MAXHEALTH;
}

float Spaceship::getHealth()
{
  return health;
}

float Spaceship::getSpeed()
{
  return m_velocity.magnitude();
}

int Spaceship::getScore()
{
  return score;
}

bool Spaceship::isGameOver()
{
  return gameOver;
}

int Spaceship::getBombCounter()
{
  return m_bombCounter;
}

void Spaceship::fuelManagement()
{


}

void Spaceship::thrustChange()
{
  if (!m_thrusting || isLanded)
  {
    thrustTime = 0;
  }
  else
  {
    thrustTime = thrustTime + 10;
  }

  if (thrustTime < 10)
  {
    m_acceleration = 5000.0f;
  }

  if (thrustTime > 10)
  {
    m_acceleration = 2000.0f;
  }

  if (thrustTime > 200)
  {
    m_acceleration = 1000.0f * (thrustTime / 100);
  }

  if (thrustTime > 500)
  {
    m_acceleration = 5000.0f;
  }

}

void Spaceship::RotateTo(float angle)
{
  // Rotate to the given angle

  if (abs(m_angle) - abs(angle) < 0.05 && abs(m_angle) - abs(angle) > -0.05)
  {
    m_angle = angle;
  }
  else
  {
    if (m_angle > angle)
    {
      m_angle -= 0.1f;
    }
    else if (m_angle < angle)
    {
      m_angle += 0.1f;
    }
  }
}

void Spaceship::addScore(int ammount)
{
  score = score + ammount;
  

}

void Spaceship::incrementBombCounter()
{
  m_bombCounter++;


}