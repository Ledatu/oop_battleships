#include "Subject.h"
#include "Observer.h"
#include "../game/GameState.h"

void Subject::addObserver(const std::shared_ptr<Observer>& observer)
{
	observers.push_back(observer);
}

void Subject::notifyObservers(GameState& gameState) {
        for (auto it = observers.begin(); it != observers.end(); ) {
            if (auto obs = it->lock()) {
                obs->updateGameState(gameState);
                ++it;
            } else {
                it = observers.erase(it);
            }
        }
    }


void Subject::notifyObservers(const std::string& message) {
        for (auto it = observers.begin(); it != observers.end(); ) {
            if (auto obs = it->lock()) {
                obs->printMessage(message);
                ++it;
            } else {
                it = observers.erase(it);
            }
        }
    }