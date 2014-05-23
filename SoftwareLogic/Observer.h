#include <iostream>
#include <set>

using namespace std;

// ---------------- Observer interface -----------------
class Observer
{
public:
	virtual void Notify(void) = 0;
};