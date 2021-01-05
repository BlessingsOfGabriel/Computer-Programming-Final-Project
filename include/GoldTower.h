#ifndef GOLDTOWER_H
#define GOLDTOWER_H

class GoldTower:public Unit{
public:
        ~GoldTower(int);
        bool valid_attack(int posX,int posY);
        bool valid_move(int posX,int posY);
        bool valid_pos(int posX,int posY);

};
#endif
