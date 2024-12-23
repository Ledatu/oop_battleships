#pragma once
#include "../observer/Observer.h"
#include "../game/GameState.h"

template <typename Displayer>
class Output : public Observer
{
private:
	Displayer &displayer;

public:
	Output(Displayer &displayer) : displayer(displayer) {};
	void updateGameState(GameState &gameState) override;
	void printMessage(std::string) override;
	void printMessage(const char *) override;
};

template <typename Displayer>
void Output<Displayer>::updateGameState(GameState &gameState)
{
	
	this->displayer.printString("Ваше поле\n");
	this->displayer.printField(gameState.getUser().getField());
	this->displayer.printString("Поле противника\n");
	this->displayer.printField(gameState.getBot().getField());
	this->displayer.printString("Ваши способности:\n");
	this->displayer.printSkillManager(gameState.getUser().getSkillManager());
}

template <typename Displayer>
void Output<Displayer>::printMessage(std::string message)
{
	this->displayer.printString(message);
}
template <typename Displayer>
void Output<Displayer>::printMessage(const char * message)
{
	this->displayer.printString(message);
}
