#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
// Forward definition
class Behaviour;


class Agent :
	public GameObject
{
public:
	Agent(const Vector2& position, const float maxSpeed = 150.0f, const float friction = 0.4f);
	virtual ~Agent();


	// Add a behaviour to the agent
	void addBehaviour(const std::shared_ptr<Behaviour> behaviour);

	
	// Run the attached behaviours and any other logic the agent has
	virtual void update(const float& deltaTime);
	// Display the agent
	virtual void draw();


	// Get the current velocity of the agent
	Vector2 getVel() const { return velocity; }
	float getMaxSpeed() const { return maxSpeed; }
	float getFriction() const { return friction; }

protected:
	// Called by update to determine weather to move or not. Base function sets both to false
	virtual void collisionDetection(const float deltaTime, bool& outCollidedX, bool& outCollidedY)
	{
		outCollidedX = false;
		outCollidedY = false;
	}


	// shared_ptr is used so multiple agents can use the same behaviour
	std::vector<std::shared_ptr<Behaviour>> behaviours;

	Vector2 velocity;
	const float maxSpeed;
	const float friction;

	// Used for drawing
	float lastAngle = 0.0f;
};