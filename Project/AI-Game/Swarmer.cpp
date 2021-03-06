#include "Swarmer.h"
#include "Leader.h"
#include "raylib.h"
#include "FormationStateBehav.h"


Swarmer::Swarmer(const Vector2& position, const std::shared_ptr<Behaviour> flockingState, const int health) :
	Agent(position, 200.0f),
	importance(0.0f),
	leader(nullptr),
	health(health),
	maxHealth(health),
	flocking(flockingState)
{
	addTag(Tag::Swarmer);
}

Swarmer::~Swarmer()
{
}


void Swarmer::draw()
{
	// Draw swarmers as black dots that hollow on taking damage
	DrawRing(position, 2.0f*(1.0f - (float)health/maxHealth), 2.5f, 0, 360, 0, BLACK);
}


void Swarmer::enterFlocking(const float& importance, Leader* leader)
{
	// Update importance and leader, and join its swarm
	this->importance = importance;
	this->leader = leader;
	leader->joinSwarm(this);
	// Remove any current behaviours and set current to flocking
	behaviours.clear();
	addBehaviour(flocking);
}

void Swarmer::enterFormation(const float& importance, Agent* leaderObj, const Vector2& offset)
{
	// A swarmer cant enter formation unless it has a ref to a leader
	if (leader == nullptr)
		return;

	// Update importacne
	this->importance = importance;
	// Remove any current behaviours
	behaviours.clear();

	// Add a new formation state to be the current behaviour
	addBehaviour(std::make_shared<FormationStateBehav>(leaderObj, offset));
}


void Swarmer::dealDamage(const int damage)
{
	health -= damage;

	// If health is at 0, kill the swarmer
	if (health <= 0)
	{
		// If this has a leader, remove this from it's swarm
		if (leader != nullptr)
			leader->leaveSwarm(this);
		
		// Delete this swarmer
		delete this;
	}
}