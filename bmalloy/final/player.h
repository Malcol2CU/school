#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include "twowaysprite.h"
#include "bulletPool.h"


class Player : public TwoWaySprite {
public:
   Player(const std::string&, const std::string&, const std::string&);
   Player(const Player&);

   virtual void update(Uint32 ticks){ 
      bullets.update(ticks);
      TwoWaySprite::update(ticks);
      stop();
   }
   virtual void draw() const{
      RenderHPBar(600, 1, -300,20, health);
      TwoWaySprite::draw();
      bullets.draw();
      std::cout<< getVelocity() << std::endl;
   }
   virtual bool collidedWith(const Drawable*) const;
   
   void dropHealth(){health -= .25; if (health == 0.0) die();}
   bool isAlive(){return alive;}
   bool isAttacking(){ return false;}
   void processKeyState(const Uint8* keystate, Uint32 ticks );


private:
   Vector2f initialV;
   std::vector<Frame *> idleR, idleL, spinAttack, deathFrames;
   bool movingRight, alive;	
   std::string bulletName;
   BulletPool bullets;
   float minSpeed, health;
   
   void RenderHPBar(int x, int y, int w, int h, float Percent) const;
   void moveLeft();
   void moveRight();
   void attack(int attack);
   void shoot();
   void die();
   void setNumFrames(){numberOfFrames = frames.size();}
   void stop();

   Player& operator=(const Player&) = delete;
};
#endif
