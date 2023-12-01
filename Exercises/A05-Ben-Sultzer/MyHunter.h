#pragma once
#include "Hunter.h"
#include "Bullet.h"
#include "Monster.h"

class MyHunter: public Hunter
{
public:

private:
	// MyHunter class inherits from Hunter class
	// Hence, you can use all the variables defined in Hunter Class
	// including vec2 position and float rotation

	// status
	int life;			// current health point
	float reloadTimer;	// count down time to shoot next bullets
	
	// attributes
	int maxLife = 3;
	float speed = 15.0f;
	float bulletSpeed = 30.0f;
	float reloadDuration = 1.0f;
	float radius = 10.0f;

	// colors
	vec3 bulletColor;
	vec3 bodyColor;
	vec3 headColor;
	vec3 shotgunColor;

	// define your variables

/*****************************/
// functions you need to complete
public:
	MyHunter(vec2 _position, int _ID);
	// <summary>
	/// Update the hunter's position and rotation based on the active monsters and hunters in the scene and update the
	/// current hunter's behavior (i.e. staying on-screen and firing a bullet)
	/// </summary>
	/// <param name="_deltaTime">The amount of real time since the last frame</param>
	/// <param name="_monsters">The list of current active monsters in the scene</param>
	/// <param name="_players">The list of current active players (hunters) in the scene</param>
	void update(float _deltaTime, const vector<Monster*> _monsters, const vector<Hunter*> _players) override;
private:
	/// <summary>
	/// Determines whether or not two circles overlap
	/// </summary>
	/// <param name="c1">The center of the first circle</param>
	/// <param name="c2">The center of the second circle</param>
	/// <param name="r1">The radius of the first circle</param>
	/// <param name="r2">The radius of the second circle</param>
	/// <returns>If the circles overlap</returns>
	bool circleCollision(vec2 c1, vec2 c2, float r1, float r2);

/*****************************/

#pragma region ProvidedFuctions

public:
	void collisionDetection(vector<Monster*> _monsters) override;
	
	void draw() override;
	void getDamagePoint(int _damage) override;
	void getScore(int _score) override;

private:
	void fire();
	void drawLifeBar();
	void upgrade(unsigned int _armor, unsigned int _speed, unsigned int _shotgun, unsigned int _bullet);

#pragma endregion ProvidedFuctions
};


