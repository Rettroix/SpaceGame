#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "BuildingForeground.h"
#include "BuildingBackground.h"
#include "Explosion.h"



const float BULLETSPEED = 800.0f;
const float TURNSPEED = 3.0f;     // Radians per second
const float ACCELERATION = 1600.0f; // Units per second^2
const float FRICTION = 1.5f;    // Fraction of speed to lose per deltaT
const float SHOOTDELAY = 0.5f;	// Time between each spaceship bullet
const float BASEASTEROIDSIZE = 100.0f;	// Diameter of the basic asteroid
const float SHIPSIZE = 64.0f;			// Diameter of the ship
const Vector2D GRAVITY = Vector2D(0.0f, 400.0f);








///////////////////////////////////////////////////
//===============City================================
///////////////////////////////////////////////////

void City::Initialise(Spaceship *player)
{
  srand(time(NULL));
  //LoadImage(L"BG.png");
  m_pPlayer = player;
  m_imageScale = 9;
  lastIndex = 0; //Make last index equal the first value at first
  userInterface* puserInterface = new userInterface;
  puserInterface->Intialise(m_pPlayer);
  furthestLeft = 0;
  Game::instance.m_objects.AddItem(puserInterface, true);

  spawnBuilding();
  
  spawnBG();
   
  //for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS/2); i++)  
  //{
  //  m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new BuildingForeground;
  //  m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, -470), m_pPlayer);

  //  Game::instance.m_objects.AddItem(m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);
  //}





}


void City::Update(float frameTime)
{

  updateBuildings();

  updateBuildingsBG();

}

IShape2D& City::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}


void City::ProcessCollision(GameObject& other)
{
  //nothing

}

void City::addShipPosition(Vector2D pos)
{
  shipsPosition = pos;
}

void City::spawnBuilding()
{
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    selectedBuilding = static_cast<BuildingType>(rand() % 6 + 1);

    if (selectedBuilding == BuildingType::BUILDING1)
    {
      //building1
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -500, BUILDINGSIDE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pLander[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pLander[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -500, -260, -500, 0);
      Game::instance.m_objects.AddItem(pLander[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -500, BUILDING);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);
    }
    else if (selectedBuilding == BuildingType::BUILDING2)
    {
      //building2
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -200, BUILDINGSIDE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -200, -260, -500, 0);
      Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -500, BUILDING);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::BUILDING3)
    {
      //building3
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -230, BUILDINGSIDE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pLander[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pLander[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -230, -260, -230, 0);
      Game::instance.m_objects.AddItem(pLander[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -230, BUILDING);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::BUILDING4)
    {
      //building4
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -450, BUILDINGSIDE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -450, -260, -300, 0);
      Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -300, BUILDING);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::HOUSE)
    {
      //HOUSE
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -100, BUILDINGSIDE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pLander[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pLander[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -100, -260, -100, 0);
      Game::instance.m_objects.AddItem(pLander[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -100, BUILDING);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::FUELBUILDING)
    {
      //HOUSE
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //fuel box
      pFuelBox[i + (NUMBER_OF_BUILDINGS / 2)] = new FuelBox;
      pFuelBox[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470) + Vector2D(0, -10));
      Game::instance.m_objects.AddItem(pFuelBox[i + (NUMBER_OF_BUILDINGS / 2)], false);


      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -100, BUILDINGSIDE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pLander[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pLander[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -100, -260, -100, 1);
      Game::instance.m_objects.AddItem(pLander[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new CollisionShaper;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -100, BUILDING);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }
    else
    {
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);

    }

    // If the last indexed building is further left than current building
    if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getPosition().XValue) 
    {
      if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[furthestLeft]->getPosition().XValue)
      {
        furthestLeft = lastIndex; //Then the last index building is further left
      }
      else
      {
        furthestLeft = furthestLeft;
      }

    }

    else
    {
      furthestLeft = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeft == 0)
    {
      furthestRight = 20;
    }

    else
    {
      furthestRight = furthestLeft - 1;
    }


    lastIndex = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

}

void City::spawnBG()
{
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    
    
    m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new BuildingBackground;
    m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, 0), m_pPlayer);
    Game::instance.m_objects.AddItem(m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);

    


    if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().XValue)
      {
        furthestLeftBG = lastIndexBG; //Then the last index building is further left 
      }
      else
      {
        furthestLeftBG = furthestLeftBG;
      }

    }

    else
    {
      furthestLeftBG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeftBG == 0)
    {
      furthestRightBG = 20;
    }

    else
    {
      furthestRightBG = furthestLeftBG - 1;
    }


    lastIndexBG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

}

void City::updateBuildings()
{
  lastIndex = 0;
  furthestLeft = 0;

  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {

    if (m_pBuildings[lastIndex]->getPosition().XValue < m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[furthestLeft]->getPosition().XValue)
      {
        furthestLeft = lastIndex; //Then the last index building is further left
      }
      else
      {
        furthestLeft = furthestLeft;
      }

    }

    else
    {
      furthestLeft = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }


    lastIndex = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop

  }
  if (furthestLeft == 0)
  {
    furthestRight = 19;

  }

  else
  {
    furthestRight = furthestLeft - 1;
  }

  middle = (m_pBuildings[furthestLeft]->getPosition().XValue + m_pBuildings[furthestRight]->getPosition().XValue) / 2;

  if (m_pPlayer->getPosition().XValue > middle)
  {
    m_pBuildings[furthestLeft]->changePosition(Vector2D((m_pBuildings[furthestRight]->getPosition().XValue), (m_pBuildings[furthestLeft]->getPosition().YValue)) + Vector2D(700, 0));
  }

  if (m_pPlayer->getPosition().XValue < middle)
  {
    m_pBuildings[furthestRight]->changePosition(Vector2D((m_pBuildings[furthestLeft]->getPosition().XValue), (m_pBuildings[furthestRight]->getPosition().YValue)) - Vector2D(700, 0));
  }

  MyDrawEngine::GetInstance()->WriteInt(700, 220, furthestLeft, MyDrawEngine::WHITE);

}


void City::updateBuildingsBG()
{
  lastIndexBG = 0;
  furthestLeftBG = 0;

  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {

    if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue < m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().XValue)
      {
        furthestLeftBG = lastIndexBG; //Then the last index building is further left
      }
      else
      {
        furthestLeftBG = furthestLeftBG;
      }

    }

    else
    {
      furthestLeftBG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }


    lastIndexBG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop

  }
  if (furthestLeftBG == 0)
  {
    furthestRightBG = 19;

  }

  else
  {
    furthestRightBG = furthestLeftBG - 1;
  }

  middleBG = (m_pBackgroundBuildings[furthestLeftBG]->getPosition().XValue + m_pBackgroundBuildings[furthestRightBG]->getPosition().XValue) / 2;

  if (m_pPlayer->getPosition().XValue > middleBG)
  {
    m_pBackgroundBuildings[furthestLeftBG]->changeInitialPosition(Vector2D((m_pBackgroundBuildings[furthestRightBG]->getInitialPosition().XValue), (m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().YValue)) + Vector2D(4000, 0));
  }

  if (m_pPlayer->getPosition().XValue < middleBG)
  {
    m_pBackgroundBuildings[furthestRightBG]->changeInitialPosition(Vector2D((m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().XValue), (m_pBackgroundBuildings[furthestRightBG]->getInitialPosition().YValue)) - Vector2D(4000, 0));
  }


}


City::City() :GameObject(LEVEL)
{

}





Bullet::Bullet() : GameObject(BULLET)
{

}

void Bullet::Initialise(Vector2D position, Vector2D velocity, float angl)
{
  m_position = position;
  m_velocity = velocity;
  m_timer = 2.0;
  m_animationSpeed = 0;
  m_currentAnimation = 0.0f;
  LoadImage(L"bullet1.png");
  LoadImage(L"bullet2.png");
  LoadImage(L"bullet3.png");
  LoadImage(L"bullet4.png");
  LoadImage(L"bullet5.png");
  LoadImage(L"bullet6.png");
  m_imageScale = SHIPSIZE / 16;
  m_drawDepth = 6;
  m_angle = angl - 1.4;
}

void Bullet::Update(float frametime)
{
  m_animationSpeed = m_animationSpeed + 0.15;
  m_timer -= frametime;
  m_position = m_position + m_velocity*frametime;
  
  if (m_animationSpeed >= 5)
  {
    m_animationSpeed = 5;
    m_imageNumber = 5;
  }
  else
  {
    m_imageNumber = m_animationSpeed;
  }
  
}

  IShape2D& Bullet::GetCollisionShape()
{
  m_collider = m_position;
  return m_collider;
}

void Bullet::ProcessCollision(GameObject& other)
{
  //if (other.GetType() == ASTEROID)
 // {
   // Deactivate();

    // Send message that a bullet has died
    // (The fragment class will need to know)
    //Event evt;
    //evt.position = m_position;
    //evt.pSource = this;
    //evt.type = EVENT_OBJECTDESTROYED;

    //Game::instance.NotifyEvent(evt);
  //}



}


