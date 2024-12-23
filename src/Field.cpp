#include "Field.h"

Field::Field(int width, int height)
{
	this->field = std::vector(height, std::vector<FieldCell>(width, FieldCell()));
	this->width = width;
	this->height = height;
	this->double_damage_flag = false;
}

Pos Field::GetTailPos(int x, int y, Battleship &battleship)
{
	auto direction = battleship.GetDirection();
	auto length = battleship.GetLength();
	int x_tail = (direction == Direction::Right) ? x + int(length) - 1 : (direction == Direction::Left) ? x - int(length) + 1
																										: x;
	int y_tail = (direction == Direction::Up) ? y + int(length) - 1 : (direction == Direction::Down) ? y - int(length) + 1
																									 : y;
	return {x_tail, y_tail};
}

Field::Field(Field &&other) : width(other.width), height(other.height), field(std::move(other.field))
{
	other.width = 0;
	other.height = 0;
	other.field.clear();
}

Field &Field::operator=(Field &&other)
{
	if (this != &other)
	{
		width = other.width;
		height = other.height;
		field = std::move(other.field);
		other.width = 0;
		other.height = 0;
	}
	return *this;
}
const bool Field::CheckPos(int x, int y)
{
	int field_width = this->GetWidth();
	int field_heigth = this->GetHeight();
	if (x >= field_width || x < 0 || y >= field_heigth || y < 0)
		return false;
	return true;
}

Field::Field(const Field &other) : height(other.height), width(other.width), field(other.field) {}

Field &Field::operator=(const Field &other)
{
	if (this != &other)
	{
		height = other.height;
		width = other.width;
		field = other.field;
	}
	return *this;
}

const bool Field::CheckPosBattleship(Battleship &battleship, int x, int y)
{
	Pos pos_tail = this->GetTailPos(x, y, battleship);
	if (this->CheckPos(x, y) && this->CheckPos(pos_tail.x, pos_tail.y))
	{
		return true;
	}
	return false;
}

int Field::GetWidth()
{
	return width;
}
int Field::GetHeight()
{
	return height;
}

int clamp(int val, int lbd, int rbd)
{
	if (val < lbd)
		val = lbd;
	else if (val > rbd)
		val = rbd;
	return val;
}

void Field::SetBattleship(int x, int y, Battleship &ship, Direction direction)
{
	int length = ship.GetLength();

	int boundingBoxX1 = x - 1;
	int boundingBoxX2 = x + 1;
	int boundingBoxY1 = y - 1;
	int boundingBoxY2 = y + 1;

	switch (direction)
	{
	case Left:
		boundingBoxX1 -= length - 1;
		break;

	case Up:
		boundingBoxY1 -= length - 1;
		break;

	case Right:
		boundingBoxX2 += length - 1;
		break;

	case Down:
		boundingBoxY2 += length - 1;
		break;
	}

	for (int i = clamp(boundingBoxY1, 0, height - 1); i <= clamp(boundingBoxY2, 0, height - 1); i++)
	{
		for (int j = clamp(boundingBoxX1, 0, width - 1); j <= clamp(boundingBoxX2, 0, width - 1); j++)
		{
			if (field[i][j].isBattleshipCell())
			{
				throw ShipNearAnotherException();
			}
		}
	}

	boundingBoxX1 += 1;
	boundingBoxX2 -= 1;
	boundingBoxY1 += 1;
	boundingBoxY2 -= 1;

	if (boundingBoxX1 < 0 || boundingBoxX2 >= width || boundingBoxY1 < 0 || boundingBoxY2 >= height)
	{
		throw OutOfBondsException();
	}

	// std::cout << "boundingBox: " << "(" << boundingBoxX1 << ", " << boundingBoxY1 << ") (" << boundingBoxX2 << ", " << boundingBoxY2 << ")\n";

	int shipIndex = 0;
	for (int i = boundingBoxY1; i <= boundingBoxY2; i++)
	{
		for (int j = boundingBoxX1; j <= boundingBoxX2; j++)
		{
			BattleshipCell &shipsell = ship[shipIndex];
			field[i][j].setBattleshipCell(shipsell);
			shipIndex++;
		}
	}

	ship.setPosition({x, y});
	ship.setDirection(direction);
}

bool Field::AttackCell(int x, int y, int damage)
{
	if (!this->CheckPos(x, y))
	{
		throw OutOfBondsException();
	}
	auto cell = &field[y][x];
	cell->OpenCellState();
	if (!cell->isBattleshipCell())
		return false;

	bool isDestroyed = false;
	int curentDamage = 1;

	isDestroyed = cell->AttackCell(damage);
	return isDestroyed;
}

std::vector<FieldCell> &Field::operator[](int index)
{
	return field[index];
}

void Field::row_to_string(const std::vector<std::string> &row, const std::vector<size_t> &widths, std::stringstream &ss)
{
	ss << "|";
	for (size_t i = 0; i < row.size(); i++)
	{
		ss << ' ';
		ss.width(widths[i]);
		ss << row[i] << " |";
	}
	ss << '\n';
}

void Field::break_of_cells(const std::vector<size_t> &widths, std::stringstream &ss)
{
	const size_t margin = 1;
	ss.put('+').fill('-');
	for (size_t w : widths)
	{
		ss.width(w + 2 * margin);
		ss << '-' << '+';
	}
	ss.put('\n').fill(' ');
}

std::string Field::to_string()
{
	std::vector<std::string> field_headers = {""};
	std::stringstream ss;
	ss.setf(std::ios::left, std::ios::adjustfield);
	for (int i = 0; i < GetHeight(); i++)
	{
		for (int j = 0; j < GetWidth(); j++)
		{
			ss << field[i][j] << " ";
		}
		ss << "\n";
	}
	return ss.str();
}

std::ostream &operator<<(std::ostream &os, Field &field)
{
	for (int i = 0; i < field.GetHeight(); i++)
	{
		for (int j = 0; j < field.GetWidth(); j++)
		{
			os << field.field[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}

void Field::OpenField()
{
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			field[y][x].OpenCellState();
		}
	}
}

void Field::SetDoubleDamageFlag()
{
	this->double_damage_flag = true;
}

void Field::update()
{
}