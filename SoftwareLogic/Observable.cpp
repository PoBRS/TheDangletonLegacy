#include "stdafx.h"
#include "Observable.h"

Observable* Observable::instance = NULL;

Observable::Observable(void)
{

}

Observable* Observable::GetInstance(void)
{
    if ( instance == NULL ) {
       instance = new Observable();
    }

    return instance;
}
Observable::~Observable(void)
{
	delete instance;
}

void Observable::AddObserver(Observer& _o)
{
    observers.insert(&_o);
}

void Observable::RemoveObserver(Observer& _o)
{
    observers.erase(&_o);
}

void Observable::NotifyObservers(void)
{
    set<Observer*>::iterator itr;
    for ( itr = observers.begin();
          itr != observers.end(); itr++ )
    (*itr)->Notify();
}

// TEST METHOD TO TRIGGER
// IN THE REAL SCENARIO THIS IS NOT REQUIRED
void Observable::Trigger(void)
{
    NotifyObservers();
}