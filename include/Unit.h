#ifndef UNIT_H
#define UNIT_H
#include "Obj.h"
class Unit: public Obj{
public:
	Unit(int faction)
	~Unit();
	void heal();
	void move(int posX,int posY);
	virtual bool valid_move(int posX, int posY);
	virtual bool valid_attack(int posX, int posY);
	virtual bool valid_pos(int posX,int posY);
	void attack(Unit& target);

protected:
	int _max_health;
	int _health;
	int _damage;
	int _heal_value;
	int _max_move;
	int _move;
	int _faction;
	int _xpos;
	int _ypos;
    std::string _name;
};
#endif
