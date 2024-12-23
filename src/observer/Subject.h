#pragma once
#include <vector>
#include <memory>
// #include "Observer.h"
// #include "../game/GameState.h"

class Observer;
class GameState;

class Subject {
private:
    std::vector<std::weak_ptr<Observer>> observers;

public:
    virtual ~Subject() = default;

    void addObserver(const std::shared_ptr<Observer> &observer);

    void notifyObservers(GameState& gameState);

	void notifyObservers(const std::string& message);
};