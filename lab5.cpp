﻿#include <iostream>
#include <time.h>

using namespace std;

class Weapon {
protected: 
    float spreadOfDamage = 0;//разброс урона
public:
    string type = "weapon";
    float atackSpeed;
    float atackPower;
    float onRefresh = 0;

    Weapon() {
        spreadOfDamage = 0.1 + float(rand() % 10) / 10;
        atackSpeed = 1 + rand() % 3 + float((rand() % 10) / 10);
        switch (int(atackSpeed) % 3) {
        case 0:
            atackPower = 3 + rand() % 3 + float((rand() % 10) / 10);
            break;
        case 1:
            atackPower = 2 + rand() % 3 + float((rand() % 10) / 10);
            break;
        case 2:
            atackPower = 1 + rand() % 3 + float((rand() % 10) / 10);
            break;
        default:
            atackPower = 1 + rand() % 3 + float((rand() % 10) / 10);
            break;
        }
    }

    Weapon(float atackSpeed, float atackPower) {
        this->spreadOfDamage = 0.1 + float(rand() % 10) / 10;
        this->atackSpeed = atackSpeed;
        this->atackPower = atackPower;
    }

    float GetDamagePerMin() {
        return (spreadOfDamage + atackPower) * 60 / atackSpeed;
    }

    float GetDamage() {
        if (rand()) {
            onRefresh = atackSpeed;
            return atackPower - spreadOfDamage;
        }
        else {
            onRefresh = atackSpeed;
            return atackPower + spreadOfDamage;
        }
    }

    bool CheckOnRefresh() {
        onRefresh--;
        if (onRefresh <= 0) {
            return false;
        }
        else{
            return true;
        }
    }

    void PrintInfo() {
        cout << endl << "Information about this weapon:" << endl
            << "Atack power: " << atackPower << endl
            << "Atack speed: " << atackSpeed << endl
            << "Damage per minute: " << GetDamagePerMin() << endl;
    }
};

class Gun: public Weapon {
public:
    Gun() {
        type = "gun";
        Weapon w = Weapon();
        this->atackPower = w.atackPower;
        this->atackSpeed = w.atackSpeed;
        this->spreadOfDamage = 0.1 + float(rand() % 10) / 10;
        this->onRefresh = 0;
    }
    Gun(float atackSpeed, float atackPower) {
        type = "gun";
        this->spreadOfDamage = 0.1 + float(rand() % 10) / 10;
        this->atackSpeed = atackSpeed;
        this->atackPower = atackPower;
    }
    void PlaySoundAttack() {
        switch(rand() % 3) {
            case 0:
                cout << "Pow!" << endl;
                break;
            case 1:
                cout << "Pew!" << endl;
                break;
            case 2:
                cout << "Bam!" << endl;
                break;
            default:
                cout << "Bang!" << endl;
                break;
        }
    }
};

class Sword: public Weapon {
public:
    Sword() {
        type = "sword";
        Weapon w = Weapon();
        this->atackPower = w.atackPower;
        this->atackSpeed = w.atackSpeed;
        this->spreadOfDamage = 0.1 + float(rand() % 10) / 10;
        this->onRefresh = 0;
    }
    Sword(float atackSpeed, float atackPower) {
        type = "sword";
        this->spreadOfDamage = 0.1 + float(rand() % 10) / 10;
        this->atackSpeed = atackSpeed;
        this->atackPower = atackPower;
    }
    void PlaySoundAttack() {
        if(rand()) cout << "Smash!" << endl;
            else cout << "Crash!" << endl;
    }
};

class Shop {
private: int quantityWeapon = 0;
public:
    Weapon** weapon;
    
    Shop(int N) {
        weapon = new Weapon* [N];
        quantityWeapon = N;
        for (int i = 0; i < N; i++) {
            if (rand()%2 == 0) {
                weapon[i] = new Sword;
            }
            else {
                weapon[i] = new Gun;
            }
        }
    }
    ~Shop() {
        delete(weapon);
    }
    void CheckWeapons() {
        for (int i = 0; i < quantityWeapon; i++) {
            char checkThis = ' ';
            char buyThis = ' ';
            if (weapon[i]->type == "sword") {
                cout << "You take a sword in your hand. Do you want to check the sword?" << endl 
                    << "Y/N ";
                cin >> checkThis;
            }
            else {
                cout << "You take a gun in your hand. Do you want to check the gun?" << endl
                    << "Y/N ";
                cin >> checkThis;
            }

            if (checkThis == 'Y') {
                weapon[i]->PrintInfo();
                cout << endl << "Are you want to buy it?" << endl
                    << "Y/N ";
                cin >> buyThis;
                if (buyThis == 'Y') {
                    cout << endl << "Congratulations on your purchase of the "
                        + weapon[i]->type + "." << endl;
                    i = quantityWeapon;
                }
                cout << endl;
            }
        }
    }
    void CheckWeapons(float chanceToBuy) {
        for (int i = 0; i < quantityWeapon; i++) {
            if (weapon[i]->type == "sword") {
                cout << "You take a sword in your hand. Do you want to check the sword?" << endl;
            }
            else {
                cout << "You take a gun in your hand. Do you want to check the gun?" << endl;
            }

            weapon[i]->PrintInfo();
            cout << endl << "Are you want to buy it?" << endl;
            float checkRand = 0.0 + (rand() % 1001) / 10;
            cout << checkRand << endl;
            if (checkRand <= chanceToBuy) {
                cout << endl << "Congratulations on your purchase of the "
                    + weapon[i]->type + "." << endl;
                i = quantityWeapon;
            }
            cout << endl;
        }
    }
};



int main()
{
    srand(time(0));
    int N;
    cout << "How many weapons to create in a weapon-shop? ";
    cin >> N;

    Shop shop(N);

    cout << endl << "Check weapons aoutomaticaly or no?" << endl << "Y/N ";
    char checkAuto;
    cin >> checkAuto;

    if (checkAuto == 'Y') {
        float chanse;
        cout << endl << "Enter chance to buy ";
        cin >> chanse;
        cout << endl;
        shop.CheckWeapons(chanse);
    }
    else {
        shop.CheckWeapons();
    }
}

