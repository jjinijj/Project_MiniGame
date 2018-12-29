#pragma once
#include "singletonBase.h"
#include "actor.h"
#include <list>

using namespace std;

typedef list<actor*>				lActor;
typedef list<actor*>::iterator		ilActor;
class actorManager : public singletonBase<actorManager>
{
private:
	lActor _actorList;


public:


	void update();


	actor* createActor();
	void removeActor(int uid);

	void hitActor(int attakerId, int victimId);
	const lActor* getActorList() { return &_actorList; }

 };