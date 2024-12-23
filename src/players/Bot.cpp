#include "Bot.h"

Bot::Bot(int width, int height, std::vector<int> lengths)
{
	this->field = Field(width, height);
	this->shipManager = ShipManager(lengths);
	this->damage = 1;
}

Bot::~Bot()
{
}

Bot::Bot()
{
}

int randomInt(int min, int max)
{
	int range = max - min + 1;
	return std::rand() % range + min;
}

void Bot::placeShips()
{
	std::vector<Direction> dirs = {Direction::Up, Direction::Left, Direction::Down, Direction::Right};
	int numOfShips = shipManager.GetNumberBattleships();
	int count = 0;
	for (int i = 0; i < numOfShips;)
	{
		count++;
		if (count > 1000)
		{
			std::cout << "Возможно поле маловато, больше кораблей добавить не получается :(" << "\n";
			break;
		}

		Position position;
		Direction direction;
		try
		{
			int x = randomInt(0, field.GetHeight() - 1);
			int y = randomInt(0, field.GetWidth() - 1);
			int dir = randomInt(0, dirs.size() - 1);
			Direction direction = dirs[dir];

			auto &ship = shipManager[i];
			this->field.SetBattleship(x, y, ship, direction);
			// std::cout << field << '\n';

			i++;
		}
		catch (std::exception &e)
		{
			// std::cout << e.what() << "\n";
		}
	}
}

Action Bot::move(Player &player)
{
	auto rand = Randomizer(1, this->field.GetHeight());
	int y = rand.getRandomInt();
	rand = Randomizer(1, this->field.GetWidth());
	int x = rand.getRandomInt();
	auto &field = player.getField();
	int n = rand.getRandomInt();
	field.AttackCell(x, y, this->damage);
	return Action::Attack;
}

Field &Bot::getField()
{
	return this->field;
}

ShipManager &Bot::getShipManager()
{
	return this->shipManager;
}

//  User::useSkill(Player& player)
// {
// 	auto infoHolder = SkillInfoHolder(&this->game.getEnemyShipManager(), &this->game.getEnemyField(), CoordHolder());
// 	auto skill = game.getSkillManager().getSkill(infoHolder);
// 	auto skillResult = skill->use();
// 	this->damage = skillResult.get_damage();
// 	if (skillResult.get_is_battleship_destroyed())
// 	{
// 		this->game.getSkillManager().addSkill();
// 	}
// 	if (skillResult.get_is_battleship_cell())
// 	{
// 		//
// 	}
// }
