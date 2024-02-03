#include "stdio.h"

enum {
    SWORD,
    DAGGER,
    STAFF
}WEAPON_CHOICE;

typedef struct {
    unsigned int BaseAttackPower;
} Weapon;

typedef struct {
    char* Name;
    unsigned int Level;
    unsigned int Health;
    unsigned int Mana;
    unsigned int Strength;
    unsigned int Agility;
    unsigned int Intelligence;
    unsigned int AttackPower;
} Character;

int main(void) {
    Character player1, player2;
    player1.Name = "Terminator";
    player1.Level = 1;
    player1.Health = 100;
    player1.Mana = 100;
    player1.Strength = 1;
    player1.Agility = 1;
    player1.Intelligence = 1;

    player2.Name = "Sharon Stone";
    player2.Level = 1;
    player2.Health = 100;
    player2.Mana = 100;
    player2.Strength = 1;
    player2.Agility = 1;
    player2.Intelligence = 1;