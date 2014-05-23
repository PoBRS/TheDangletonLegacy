#include "stdafx.h"
#include "Observer.h"
#include <iostream>
#include <set>

using namespace std;

Observable* Observable::instance = NULL;

Observable* Observable::GetInstance()
{
    if ( instance == NULL ) {
       instance = new Observable();
    }

    return instance;
}

void Observable::AddObserver(Observer& o)
{
    observers.insert(&o);
}

void Observable::RemoveObserver(Observer& o)
{
    observers.erase(&o);
}

void Observable::NotifyObservers()
{
    set<Observer*>::iterator itr;
    for ( itr = observers.begin();
          itr != observers.end(); itr++ )
    (*itr)->Notify();
}

// TEST METHOD TO TRIGGER
// IN THE REAL SCENARIO THIS IS NOT REQUIRED
void Observable::Trigger()
{
    NotifyObservers();
}