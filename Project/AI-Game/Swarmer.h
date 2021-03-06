#pragma once
#include "Agent.h"
// Forward definition
class Behaviour;
class Leader;


// An AI Agent that act as boids following a Leader, and can enter a formation
class Swarmer :
	public Agent
{
public:
	Swarmer(const Vector2& position, const std::shared_ptr<Behaviour> flockingState, const int health = 5);
	virtual ~Swarmer();


	// Use Agent::update()
	virtual void draw();

	// Enter the flocking state
	void enterFlocking(const float& importance, Leader* leader);
	// Enter the formation state
	void enterFormation(const float& importance, Agent* leaderObj, const Vector2& offset);

	// Returns this boid's importance value
	virtual float getImportance() const { return importance; }
	// Return a pointer to this swarmers leader. nullptr if it doesnt have one
	virtual Leader* getLeader() const { return leader; }
	// Reduces health by 'damage', and if it reaches 0, destroys the swarmer
	virtual void dealDamage(const int damage);

protected:
	// Used by other boids to determine how much this object should impact it's steering forces
	// It is set when transitioning to flocking and formation, and is only used by other agents
	float importance;
	// Pointer to the leader this swarmer is following
	Leader* leader;

	// When the swarmers health reaches 0, its destroyed
	int health;
	const int maxHealth;

private:
	// The flocking state is passed by the spawner
	const std::shared_ptr<Behaviour> flocking;
};