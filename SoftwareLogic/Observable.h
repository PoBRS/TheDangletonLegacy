#include "Observer.h"
#include <iostream>
#include <set>

using namespace std;
class Observable 
{
public:
	static Observable* GetInstance(void);
	void AddObserver(Observer& _o);
	void RemoveObserver(Observer& _o);
	void NotifyObservers(void);
	void Trigger(void);
protected:
	static Observable* instance;
	set<Observer*> observers;
	Observable(void);
	~Observable(void);
};
