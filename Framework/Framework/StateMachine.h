#pragma	once

#include <memory>
#include <stack>

#include "State.h"

using namespace std;

typedef unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine() {};
	~StateMachine() {};

	void AddState(StateRef newState, bool isReplacing = true); // the bool is asking if you are replacing the current state that is already in place
	void RemoveState();

	void ProcessStateChanges();

	StateRef &getActiveState();

private:
	stack<StateRef> _states; // unique pointer to a state
	StateRef _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
};
