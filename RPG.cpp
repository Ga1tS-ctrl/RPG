#include <iostream>
#include <conio.h>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

// ��������� ��� ��
struct Character {
    string name;
    int health;
    int maxHealth;
    int attack;
    int defense;
    bool hasSword;
    bool hasPotion;
};

// ��������� ��� ������
struct Enemy {
    string name;
    int health;
    int attack;
    int defense;
};


void PrintCharet();
bool SaveGame(const Character& player, const string& filename = "savegame.txt");
bool LoadGame(Character& player, const string& filename = "savegame.txt");
bool SaveExists(const string& filename = "savegame.txt");

void showMenu() {
    cout << "---������� ������� ������---" << endl;
    cout << "1: ����� ����" << endl;
    cout << "2: ����������" << endl;
    cout << "3: �����" << endl;

    if (SaveExists()) {
        cout << "(���� ����������� ����)" << endl;
    }
}

void clearScreen() {
    system("cls");
}

void waitForPress() {
    cout << "������� ����� ������� ��� �����������...";
    _getch();
    cout << endl;
}

Character createCharacter() {
    Character player;
    clearScreen();
    cout << "--- ����� ���� ---" << endl;
    cout << "������� ��� ������ ���������: ";
    cin.ignore();
    getline(cin, player.name);

    player.health = 125;
    player.maxHealth = 125;
    player.attack = 15;
    player.defense = 5;
    player.hasSword = false;
    player.hasPotion = false;

    cout << "����� ����������, " << player.name << "!" << endl;
    cout << "���� ����������� � ���� ������� ������� ������ ����������..." << endl;
    waitForPress();

    return player;
}

void printChapter() {
    clearScreen();
    cout << "--- ����� 1: ������ �� �������� --- " << endl;
    cout << "�� ���������� ����� � ������ ��� ����� ������ ����, ��������� ��������." << endl;
    cout << "������ �������� �������� ������ ���� � �����." << endl;
    cout << "���-�� ����� �������� ����� �����..." << endl;
    cout << "�� ����� �� ������� ��� � ���� ���-�� ������, ������ �� ������� �����... " << endl;
    cout << "� �� ������ ����� � ���������� ��� ���..." << endl;

    waitForPress();
    
}

Enemy createEnemy() {
    Enemy enemy;
    enemy.name = "������������ ����������";
    enemy.health = 40;
    enemy.attack = 14;
    enemy.defense = 5;
    return enemy;
}

Enemy createGoblin() {
    Enemy goblin;
    goblin.name = "������";
    goblin.health = 30;
    goblin.attack = 7;
    goblin.defense = 6;
    return goblin;
}

Enemy createTempleGoblin() {
    Enemy goblin;
    goblin.name = "������";
    goblin.health = 35;
    goblin.attack = 7;
    goblin.defense = 7;
    return goblin;
}

Enemy createTempleCatWoman() {
    Enemy catwoman;
    catwoman.name = "���������� � ������";
    catwoman.health = 55;
    catwoman.attack = 14;
    catwoman.defense = 6;
    return catwoman;
}

Enemy createTempleGoblin1() {
    Enemy goblin1;
    goblin1.name = "������";
    goblin1.health = 35;
    goblin1.attack = 7;
    goblin1.defense = 7;
    return goblin1;
}

Enemy createTempleGoblin2() {
    Enemy goblin2;
    goblin2.name = "������";
    goblin2.health = 35;
    goblin2.attack = 7;
    goblin2.defense = 7;
    return goblin2;
}

Enemy createTempleTheBigCat() {
    Enemy cat;
    cat.name = "������� ���";
    cat.health = 75;
    cat.attack = 11;
    cat.defense = 8;
    return cat;
}

Enemy createTempleGoblin3() {
    Enemy goblin3;
    goblin3.name = "������";
    goblin3.health = 40;
    goblin3.attack = 10;
    goblin3.defense = 7;
    return goblin3;
}

Enemy createTempleOrg() {
    Enemy org;
    org.name = "���";
    org.health = 75;
    org.attack = 11;
    org.defense = 8;
    return org;
}

Enemy createTempleGoblin4() {
    Enemy goblin4;
    goblin4.name = "������";
    goblin4.health = 40;
    goblin4.attack = 10;
    goblin4.defense = 7;
    return goblin4;
}

void showBattleStatus(const Character& player, const Enemy& enemy) {
    cout << "=== ��� ===" << endl;
    cout << player.name << ": " << player.health << "/" << player.maxHealth << " HP" << endl;
    cout << enemy.name << ": " << enemy.health << " HP" << endl;
    cout << "-------------------" << endl;
}

void showBattleMenu() {
    cout << "1: ���������" << endl;
    cout << "2: ����������" << endl;
    cout << "3: ������������ �������" << endl;
    cout << "4: ���������� �������" << endl;
}

int calculateDamage(int attack, int defense) {
    int damage = attack - (defense / 2);
    if (damage < 1) damage = 1;

    int variation = damage * 0.2;
    damage += (rand() % (variation * 2 + 1)) - variation;

    return damage;
}

bool battle(Character& player, Enemy& enemy) {
    srand(time(0));
    bool playerTurn = true;

    while (player.health > 0 && enemy.health > 0) {
        clearScreen();
        showBattleStatus(player, enemy);

        if (playerTurn) {
            int choice;
            cout << "��� ���! �������� ��������:" << endl;
            showBattleMenu();
            cin >> choice;

            switch (choice) {
            case 1: {
                int damage = calculateDamage(player.attack, enemy.defense);
                enemy.health -= damage;
                cout << "�� ������� " << damage << " �����!" << endl;
                break;
            }
            case 2: {
                int bonusDefense = player.defense * 2;
                cout << "�� ���������� � ������! ������ ��������� �� ���� ���." << endl;
                break;
            }
            case 3: {
                if (player.hasPotion) {
                    cout << "�� ������������ ����� �������! +25 HP" << endl;
                    player.health += 25;
                    if (player.health > player.maxHealth) player.health = player.maxHealth;
                    player.hasPotion = false;
                }
                else {
                    cout << "� ��� ��� ���������!" << endl;
                }
                break;
            }
            case 4: {
                cout << "������� ������ ��������! ���� ������� ������." << endl;
                break;
            }
            default:
                cout << "�������� �����!" << endl;
                continue;
            }
        }
        else {
            cout << "��� ����������!" << endl;
            int damage = calculateDamage(enemy.attack, player.defense);
            player.health -= damage;
            cout << enemy.name << " ������� ��� " << damage << " �����!" << endl;
        }

        waitForPress();
        playerTurn = !playerTurn;
    }

    clearScreen();
    if (player.health > 0) {
        cout << "������! �� ������� " << enemy.name << "!" << endl;
        return true;
    }
    else {
        cout << "���������! �� ���� ���������." << endl;
        return false;
    }
}

void findChest(Character& player) {
    clearScreen();
    cout << "����� ������ ��� �������� �� ������ ����������� ���..." << endl;
    cout << "� ����� ������� �������� �� ���� �� ������� �� ������� ������ " << endl;
    cout << "�� ������ ����������� ��� �������..." << endl;

    int attempt;
    int attemptsLeft = 3;
    bool chestOpened = false;

    while (attemptsLeft > 0 && !chestOpened) {
        cout << "� ��� �������� �������: " << attemptsLeft << endl;
        cout << "������� ��� �� 4 ����: ";
        cout << "168-100, 154-100?" << endl;
        cin >> attempt;

        if (attempt == 6854) {
            cout << "����� �������! ������ �����������..." << endl;
            cout << "������ �� ��������:" << endl;
            cout << "- ����� ������� (+20 HP)" << endl;
            cout << "- ������� ����� � �������� �����" << endl;
            player.hasPotion = true;
            chestOpened = true;
        }
        else {
            attemptsLeft--;
            cout << "�������� ���! ����� �� �����������." << endl;
            if (attemptsLeft > 0) {
                cout << "���������� ��� ���." << endl;
            }
        }
        waitForPress();
    }

    if (!chestOpened) {
        cout << "������ �������� ��������. ��������, �� ������� ��� �����..." << endl;
        waitForPress();
    }
}

void templeDoorRiddle() {
    clearScreen();

    cout << "1: ����" << endl;
    cout << "2: ���" << endl;
    cout << "3: �����" << endl;

    int attempts = 3;
    bool doorOpened = false;

    while (attempts > 0 && !doorOpened) {
        int choice;
        cout << endl << "� ��� �������: " << attempts << endl;
        cout << "�������� ����� (1-3): ";
        cin >> choice;

        if (choice == 2) {
            cout << "������ ��� �������� ��������! ����� �������� �����������..." << endl;
            cout << "�� ������� �������!" << endl;
            doorOpened = true;
        }
        else {
            attempts--;
            cout << "������ �� ����������. ����� �������� ��������." << endl;
            if (attempts > 0) {
                cout << "�������� ��� ���." << endl;
            }
            waitForPress();
        }
    }

    if (!doorOpened) {
        cout << "����� ��� � �� ���������. ��������, ����� ����� ������ ����..." << endl;
    }
    else {
        cout << "�� ��������� ����� ����� � ����������� ���� �����������..." << endl;
    }
    waitForPress();
}

void templeTheMysteryChest(Character& player) {
    clearScreen();
    cout << "1: ����� " << endl;
    cout << "2: ����� " << endl;
    cout << "3: ���� " << endl;

    int attempts = 3;
    bool chestOpened = false;
    while (attempts > 0 && !chestOpened) {
        int choice;
        cout << endl << "� ��� �������:" << attempts << endl;
        cout << "�������� ����� (1 - 3) ";
        cin >> choice;
        if (choice == 3) {
            cout << "������ ��������. �� �������� �������!" << endl;
            chestOpened = true;
            cout << "����� �������! ������ �����������..." << endl;
            cout << "������ �� ��������:" << endl;
            cout << "- ����� ������� (+45 HP)" << endl;
            player.hasPotion = true;
        }
        else {
            attempts--;
            cout << "������ �� ��������. " << endl;
            if (attempts > 0) {
                cout << "���������� ��� ���." << endl;
            }
            waitForPress();
        }
    }
}

void templeCrossroads(Character& player) {
    clearScreen();
    cout << "�� ����� ������ � ������� ��������." << endl;
    cout << endl << "���� �������?" << endl;
    cout << "1: ����� ������" << endl;
    cout << "2: ����������� ������" << endl;
    cout << "3: ������ ������" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: // ����� ������ - ����������
        clearScreen();
        cout << "�� ������ ����� ������." << endl;
        cout << "�� ����� �� �������� � ������ �� ���������� � �� ���������� �������� ������. " << endl;
        waitForPress();
        break;

    case 2: // ����������� ������ - ����������� �������
        clearScreen();
        cout << "�� ������ ����� �� ������." << endl;
        cout << "�� ����� �� �������� � ������ �� ���������� �� ���� ����� �� � �� �������." << endl;
        player.health = 0;
        waitForPress();
        break;

    case 3: // ������ ������ - ����������� �������
        clearScreen();
        cout << "�� ������ ����� �������" << endl;
        cout << "�� ����� �� �������� � �� ���� ������ ������������ ������ � �� ����� ��������� �� �������." << endl;
        player.health = 0;
        waitForPress();
        break;

    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeCrossroads(player);
        break;
    }
}

void templeChoice(Character& player) {
    clearScreen();
    cout << "1: ����." << endl;
    cout << "2: �����." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        clearScreen();
        cout << "�� ������ ��������� �����." << endl;
        cout << "�� ������ ������ � �� ������� ��� ���������� �������� ������ � �� ������" << endl;
        player.health = 0;
        waitForPress();
        break;

    case 1:
        clearScreen();
        cout << "�� ������ ���� ����." << endl;
        cout << "�� ��� �� �������� ����� ��� �� ��������." << endl;
        waitForPress();
        break;
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeChoice(player);
    }
}

void templeDeathOrLife(Character& player) {
    clearScreen();
    cout << "1: ������ ����." << endl;
    cout << "2: �����." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        clearScreen();
        cout << "�� ������ ���� � ������ �� ���������." << endl;
        waitForPress();
        break;
    case 2:
        cout << "�� ������ ��� ����� � ������ ������." << endl;
        waitForPress();
        break;
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeDeathOrLife(player);
    }
}

void templeOpenTheLocker(Character& player) {
    clearScreen();
    cout << "1: ���" << endl;
    cout << "2: �����" << endl;
    cout << "3: ������ " << endl;
    cout << "4: ����" << endl;
    cout << "5: ����" << endl;

    int attempts = 3;
    bool chestOpened = false;

    while (attempts > 0 && !chestOpened) {
        int choice;
        cout << endl << "� ��� �������:" << attempts << endl;
        cout << "�������� ����� (1 - 5) ";
        cin >> choice;
        if (choice == 3) {
            cout << "�� ������� ���������� ���, ������� ������" << endl;
            chestOpened = true;
            cout << "� ����� ���� ����� ������� (+55 HP)" << endl;
            player.hasPotion = true;
        }
        else {
            attempts--;
            cout << "�� ������� ������������ ���, ������� �� ��������." << endl;
            if (attempts > 0) {
                cout << "���������� ��� ���!" << endl;
            }
            waitForPress();
        }
    }
}

void temleAccuracy(Character& player) {
    clearScreen();
    cout << "1: ��������, ���������" << endl;
    cout << "2: ������, �� ��������� " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "�� �������� � ������������ ������ ������� � �� ������� ��� �� ����� � �� ������� ���������� ������ � �� ������." << endl;
        waitForPress();
        break;
    case 1:
        cout << "�� ��� �������� ������ ������ ������� � �� ����� ����� ����, �� ������� ������� ������ � ����� ������." << endl;
        waitForPress();
        break;
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        temleAccuracy(player);
    }
}

void findChest1(Character& player) {
    clearScreen();

    int attempt;
    int attemptsLeft = 3;
    bool chestOpened = false;

    while (attemptsLeft > 0 && !chestOpened) {
        cout << "� ��� �������� �������: " << attemptsLeft << endl;
        cout << "������� ��� �� 4 ����: ";
        cout << "6598-6580, 3895-3841?" << endl;
        cin >> attempt;

        if (attempt == 1854) {
            cout << "����� �������! ������ �����������..." << endl;
            cout << "������ �� ��������:" << endl;
            cout << "- ����� ������� (+25 HP)" << endl;
            cout << "- ������ ��������� ��������� � ������ 1." << endl;
            player.hasPotion = true;
            chestOpened = true;
        }
        else {
            attemptsLeft--;
            cout << "�������� ���! ����� �� �����������." << endl;
            if (attemptsLeft > 0) {
                cout << "���������� ��� ���." << endl;
            }
        }
        waitForPress();
    }

    if (!chestOpened) {
        cout << "������ �������� ��������. ��������, �� ������� ��� �����..." << endl;
        waitForPress();
    }
}

void temleYesOrNo(Character& player) {
    clearScreen();
    cout << "�������� �����? " << endl;

    cout << "1: ��." << endl;
    cout << "2: ���." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "�� ������ �� ���������� ����� � ����� ������." << endl;
        waitForPress();
        break;
    case 1:
        cout << "�� ������ �������� �����." << endl;
        waitForPress();
        break;
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        temleYesOrNo(player);
    }
}

void templeANewSword(Character& player) {
    clearScreen();
    cout << "�������� ��������� �������, ��� �� ��������? " << endl;

    cout << "1: ��������" << endl;
    cout << "2: �� ����������" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "�� ������ �� ���������� ��������� ������� � ����� ������." << endl;
        waitForPress();
        break;
    case 1:
        cout << "�� ������ �������� ��������� �������. " << endl;
        cout << "������� ���� ������ � �� �������� � ������." << endl;
        cout << "�� ������� �� � ��� �������� �������� ��������� ��� � �� ������ ��� �����." << endl;
        cout << "1: ����� ����� ���" << endl;
        cout << "2: �������� ������" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "� ������ ��� �������� � �������." << endl;
            player.attack += 20;
            player.hasSword = true;
        }
        break;
    }
}

void templeRunOrGiveUp(Character& player) {
    clearScreen();
    cout << "��� �� ������ ������?" << endl;

    cout << "1: �������." << endl;
    cout << "2: �������." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "�� ������ �������..." << endl;
        cout << "�� ������������ � ������ ������ � ������� ������ � ������ ���������� � ������." << endl;
        cout << "�� ���������� � ������ � ����� ����� ���� �����." << endl;
        cout << "����� �� ����� �� ������ � ������� �� ���� ������ ��������� ��������� ���� �������� ����� 4." << endl;
        cout << "�� ��� ����� � ����� ������..." << endl;
        waitForPress();
        break;
    case 1:
        cout << "�� ������� � ���� ��� ������� � ������� �������� � �� �����������." << endl;
        cout << "�� ���������� � �������, ��� ���� �� ������� ��������� ������." << endl;
        waitForPress();
        break;
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeRunOrGiveUp(player);
    }
}

void templeChoice1(Character& player) {
    clearScreen();
    cout << "1: ����� � ���������. " << endl;
    cout << "2: �������. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "�� ������ ����� � ��������� ����� ���� ��� ��� ���." << endl;
        waitForPress();
        break;
    case 2:
        cout << "�� ������ �� ���� � ��������� � ������ ������� �� ����� �������� ��������� �����. " << endl;
        cout << "� ��� �� ��� ������ �� ������ ��������� � ��� ������� ����������. " << endl;
        cout << "�� �������� � ����� � ����������. " << endl;
        cout << "������ ����� �� ������ ����� ������ ��� ������� �� �������� ���. " << endl;
        player.attack += 10;
        cout << "�� ����� �� ������ � ����������� �� �������� � ������ �� ������� � ����� ������. " << endl;
        cout << "�� ��� � ������� ����, �� �� ������� ��� � ���� ������ ��������� ��������� " << endl;
        cout << "�� ������ ��� ����� � �������� ������ ��������� ���������. " << endl;
        cout << "����� ������ ��� ����� �� ����� � ���� ������ ��������� ��������� ����� 4. " << endl;
        waitForPress();
        break;
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeChoice1(player);
    }
}

void templeChoice2(Character& player) {
    clearScreen();
    cout << "1: �����. " << endl;
    cout << "2: ������� ������ ��������� ��������� � �������. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "�� ������ �������� ����, �� �� �� �������� ��� �� ������� ��� � �� ��� ����. " << endl;
        waitForPress();
        break;
    case 2:
        cout << "�� ��������� ����� ������ ��������� ��������� � �������. " << endl;
        cout << "�� ������ ��������� ��������� ���� �������� ����� 4. " << endl;
        waitForPress();
        break;
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeChoice2(player);
    }
}

void templeTheAltar(Character& player) {
    clearScreen();
    cout << "�� ������� ������... " << endl;
    cout << "��� �� ������ ������? " << endl;
    cout << "1: ����������� � ���������� ��������. " << endl;
    cout << "2: �������� ����. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2: 
        cout << "�� ������ ������ ����. " << endl;
        waitForPress;
        break;
    case 1:
        cout << "�� ������ �������������� �������" << endl;
        cout << "*������ ��������� �������������� �������." << endl;
        cout << "� ��������� �������*  " << endl;

        player.health = 125;

        if (SaveGame(player)) {
            cout << "���� ���������." << endl;
        }
        else {
            cout << "�� ������� ��������� ����!" << endl;
        }
        
        waitForPress;
        break;
        
    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeTheAltar(player);
    }
}

void templeTheAltarOfficial(Character& player) {
    clearScreen();
    cout << "�� ��� � ������� ������..." << endl;    
    cout << "1: ����������� � ���������� ��������. " << endl;
    cout << "2: �������� ����. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "�� ������ ������ ����. " << endl;
        waitForPress;
        break;
    case 1:
        cout << "�� ������ �������������� �������" << endl;

        player.health = 125;

        if (SaveGame(player)) {
            cout << "���� ���������." << endl;
        }
        else {
            cout << "�� ������� ��������� ����!" << endl;
        }

        waitForPress;
        break;

    default:
        cout << "�������� �����! ���������� ��� ���." << endl;
        waitForPress();
        templeTheAltarOfficial(player);
    }
}

void templeEntrance(Character& player) {
    clearScreen();
    cout << "������ �� ����� �� �������, �� ������ ������������ � �����." << endl;
    cout << "�� ����� ����� ��������.." << endl;
    cout << "�� ����� ����� ���� ���������� ������!" << endl;
    cout << "������: ����... �����! �� ��������!" << endl;
    cout << "�� ������������� � ���!" << endl;
    waitForPress();

    // ��� � ��������
    Enemy goblin = createGoblin();
    bool victory = battle(player, goblin);

    if (victory) {
        cout << "�� �������� �������!" << endl;
        cout << "� ����� ������." << endl;
        waitForPress();

        clearScreen();
        cout << "�� ���������� ���� � ����� � �������� �������." << endl;
        cout << "� ��� �� ������� � �����, �� ������ ��������� �����, �� ����� ����� ���� �������� ��� ���� ������." << endl;
        cout << "�� ������������� � ���!" << endl;
        waitForPress();
    }

    // ������ ��� � ��������-������� �����
    Enemy templeGoblin = createTempleGoblin();
    victory = battle(player, templeGoblin);

    if (victory) {
        cout << "�� �������� �������-������ �����!" << endl;
        cout << "�� ������ �� ��������." << endl;
        cout << "�� ����� � ����." << endl;
        cout << "�� ������ 1 �����!" << endl;
        cout << "�������� ����� �����. " << endl;
        cout << "--- ����� 2: � ������ ����� --- " << endl;

        cout << "�� ����� � ����, �� �� �������� �������� �����. " << endl;
        cout << "�� �� �� ����� �������� �������� � �� ����� ������. " << endl;
        cout << "�� ������� ����� ����� ��� � �� ��������� ��� � �������������. " << endl;
        cout << "�� ����� ����� ����� ��������� �����. " << endl;

        cout << " *���� ���� ������ ������� ����� ������� �����*" << endl;
        cout << "��� ������ �������� �������:" << endl;
        cout << "� ������ ��� ��� � ����� ��� ����, � ���� ��� ����, �� � ������ � ������, ��� � �����?" << endl;

        waitForPress();
        templeDoorRiddle();

        cout << "����� �������� ����� �� ����� ������..." << endl;
        cout << "�� ������ ����������� �� ��������, �� ��� �������� �������." << endl;
        cout << "�� ����� �� ���-�� ��������, �� ����� ��� �������. " << endl;
        cout << "�� ��� ��������� ������ ���. ���� ���??" << endl;
        cout << "���: ����-����, ���-��� ����-����, ���-���" << endl;
        cout << "� ����� �� ���� ����� ������� � �����, � ������ ��������..." << endl;
        cout << "���������� � ������: ��� �� ���������� � ��� ������ ����. " << endl;
        cout << "���������� � ������: ��� �� ���� ������ ���� �� �� ����������� ������ ���� �� �������. " << endl;
        cout << "���������� � ������: � ��� ��, ��� ����� ������� ������� ������ �� ����� ������." << endl;
        cout << "��: �����!! ��� ���� ���� �� ����." << endl;
        cout << "���������� � ������: ��� ������, �� ���� ��������� � ����� ������� *�������*" << endl;
        cout << "�� ������������� � ���!" << endl;
        waitForPress();
    }

    Enemy templeCatWoman = createTempleCatWoman();
    victory = battle(player, templeCatWoman);

    if (victory) {
        cout << "����� ������ ��� ����������� � ������ �� ���������� ����." << endl;
        cout << "*����� � �����.*" << endl;
        cout << "��� �������� �����..." << endl;
        cout << "�����: � ������ �� ��!" << endl;
        waitForPress();
        templeTheAltar(player);

        cout << "�� ��� �� ��������� ��������." << endl;
        cout << "��� �� �������, �� � ����� ���� �������� ������" << endl;
        cout << "�� ���� �� ���� ���� �� ����������, � ����� ������������ ����� ������� ����." << endl;
        cout << "�� ���� ����� ��������� ������." << endl;
        cout << "������: �� �� ��������!!" << endl;
        cout << "�� ������������� � ���!" << endl;
        waitForPress();
    }

    Enemy templeGoblin1 = createTempleGoblin1();
    victory = battle(player, templeGoblin1);

    if (victory) {
        cout << "�� ���������� ����.. " << endl;
        cout << "�� ����� �� ������� ������. " << endl;
        cout << "�� ������� ���� �������. " << endl;
        cout << "�� ������ ������ ��� �������. " << endl;
        cout << "*���� ���� ������� ���� ������ ����� ������� ������* " << endl;
        cout << "�� ������� ���� ������� *����� ������� �������� �������*  " << endl;
        cout << "*��� ����� � �����, � ����, � �������, � ����, � ����, � ������, �� ������� � ���� � ��������.*" << endl;

        waitForPress();
        templeTheMysteryChest(player);
    }

    if (victory) {
        templeCrossroads(player);

        cout << "�� ����� �� �������� � ������ �� ���������� � �� ���������� �������� ������. " << endl;
        cout << "� �� ��� �� ���� ����� ������." << endl;
        cout << "�� ������������� � ���!" << endl;
        waitForPress();
    }

    Enemy templeGoblin2 = createTempleGoblin2();
    victory = battle(player, templeGoblin2);

    if (victory) {
        cout << "����� ������ ��� �������� �� ����� ������." << endl;
        cout << "�� ����� ������� �� ��������� ������ �� ����������." << endl;
        cout << "�� ����� � ������� �������." << endl;
        cout << "� �� ���� ��� ������ �������� ���� � ���������� � ������ �������� ����." << endl;
        cout << "� ������� �� ��� ������." << endl;
        cout << "���: � ������ �� �������!!" << endl;
        cout << "�� ������ ��� ��� ��� ����� ���." << endl;
        cout << "�� ������������� � ���!" << endl;
        waitForPress();
    }

    Enemy templeTheBigCat = createTempleTheBigCat();
    victory = battle(player, templeTheBigCat);

    if (victory) {
        cout << "����� ������ ��� ������� ����� �� ������ ��������� ����� ������ �����������." << endl;
        cout << "�� ����� � ���������� �� ���� � ����, �� ������ ��� �� ������� � ��� ����-�� �����." << endl;
        cout << "�� �������� ��������." << endl;

        if (SaveGame(player)) {
            cout << "���� ���������." << endl;
        }
        else {
            cout << "�� ������� ��������� ����!" << endl;
        }

        cout << "�� ���������� �������� ����� ������, �� ������ ���������� � ����� �� ��� ����� ����� �� �������." << endl;
        cout << "�� ������ ��������� ������, ��� �� ������ �����������?" << endl;

        waitForPress();

        templeChoice(player);

        cout << "����� ���� ���� ������, ��� �� ������ ������?" << endl;

        waitForPress();

        templeDeathOrLife(player);
    }

    if (victory) {
        cout << "�� ��� � ������� ��������, �� �� ������� �������� � ����� �� ���." << endl;
        cout << "�� �����, �� ����� ���� �������� �������� ������� ������, �� �� �� ����������." << endl;
        cout << "�� ������������� � ���!" << endl;
        waitForPress();
    }

    Enemy templeGoblin3 = createTempleGoblin3();
    victory = battle(player, templeGoblin3);

    if (victory) {
        cout << "����� ������ �� ����� ������" << endl;
        cout << "�� ����� �� �������� � ������� ����� � ����������." << endl;
        cout << "�� ������� ����� � ���� ��� ������ � �� ������ ��� �������." << endl;
        cout << "����� ��� ������� ����� ������ ������ ���." << endl;

        waitForPress();
        templeOpenTheLocker(player);
    }

    if (victory) {
        cout << "�� ����� �� ���������� � ����� ������." << endl;
        cout << "�� ����� ������ �� ��������." << endl;
        cout << "� �� ���� �� ��������� �� ������." << endl;
        cout << "�� ������������ �� � ����� ����� �������������." << endl;
        cout << "�� ������������ ��� � ��� �������." << endl;
        cout << "� �� ������ ������� ��� �� �������� ������. " << endl;

        waitForPress();
        temleAccuracy(player);
    }

    if (victory) {
        cout << "�� ��� � ������� ����� ����� ����������� ������ ������ � ������� ������� �� ����� ���������, �� �� ���������� � ����� ������� ������ �� ��� ��������." << endl;
        cout << "� �� ���� ����� ������ ��������� ��������� � ������ 3.  " << endl;
        cout << "�� ����� ������ � ������� ������." << endl;
        cout << "� ������ ��� �������." << endl;

        waitForPress();
        findChest1(player);
    }

    if (victory) {
        cout << "�� ����� ������ � ������ �� ������� ������� � ������ ������� ������ � ������� �������." << endl;

        if (SaveGame(player)) {
            cout << "���� ���������." << endl;
        }
        else {
            cout << "�� ������� ��������� ����!" << endl;
        }

        cout << "����� �� ����������� ��� �� ���������� � ���������� ����� ��������� � ������ �� �������" << endl;
        cout << "�� ��������� ��������� � ����� ������." << endl;
        cout << "� ��� ������ �� ����� �� ������� ��������� ���." << endl;
        cout << "�� ������������� � ���!" << endl;

        waitForPress();
    }

    Enemy templeOrg = createTempleOrg();
    victory = battle(player, templeOrg);

    if (victory) {
        cout << "����� ������ ��� ����� �� ����� ������." << endl;
        cout << "�� ��� � ������� �����." << endl;

        waitForPress();
        temleYesOrNo(player);

        cout << "�� ����� � ����� � ������ ���������� ������� � ������ ������ �� �����." << endl;
        waitForPress();
        templeANewSword(player);
    }

    if (victory) {
        cout << "�� ����� �� ������ �� ����� ������ ����������� ����." << endl;
        cout << "�� ��� � ������ �� ���������� ����� �� ����� ����� ����� �����." << endl;

        waitForPress();
        templeRunOrGiveUp(player);

        cout << "�� ������� � ���� ��� ������� � ������� �������� � �� �����������." << endl;
        cout << "�� ���������� � �������, ��� ���� �� ������� ��������� ������." << endl;
        waitForPress();

        cout << "�� ����� ���� �� ������� ������?" << endl;
        waitForPress();
        templeChoice1(player);
    }

    if (victory) {
        cout << "�� ��� ��������� ����� ��� �� ������� � ������� ������� ���� �� ������ ����� ����, �� �� ������� � ���� ������ ��������� ���������, ��� �� ������ ������? " << endl;

        waitForPress();
        templeChoice2(player);

        cout << "�� ����� �� ��������� � ������ ����� ���� �� ��� ���. " << endl;
        cout << "�� ��� ����� � ����� ������. " << endl;
        cout << "�� ��� ����� ���� ���� ������, �� ���������� ��� �� ��� ������, �� ������ ��� ���� ���������. " << endl;
        cout << " �� ������������� � ���! " << endl;
    }

    Enemy templeGoblin4 = createTempleGoblin4();
    victory = battle(player, templeGoblin4);

    if (victory) {
        cout << "����� ������ �� ������ ���������� ����� ��� �� ��������. " << endl;
        cout << "������ ��������� ����� �� ������� � ���������� ����. " << endl;

        if (SaveGame(player)) {
            cout << "���� ���������." << endl;
        }
        else {
            cout << "�� ������� ��������� ����!" << endl;
        }

    }
}


bool SaveGame(const Character& player, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    file << player.name << endl;
    file << player.health << endl;
    file << player.maxHealth << endl;
    file << player.attack << endl;
    file << player.defense << endl;
    file << player.hasSword << endl;
    file << player.hasPotion << endl;

    file.close();
    return true;
}

bool LoadGame(Character& player, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    string line;

    getline(file, player.name);

    getline(file, line);
    player.health = stoi(line);

    getline(file, line);
    player.maxHealth = stoi(line);

    getline(file, line);
    player.attack = stoi(line);

    getline(file, line);
    player.defense = stoi(line);

    getline(file, line);
    player.hasSword = (line == "1");

    getline(file, line);
    player.hasPotion = (line == "1");

    file.close();
    return true;
}

bool SaveExists(const string& filename) {
    ifstream file(filename);
    bool exists = file.good();
    file.close();
    return exists;
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));

    int choice;
    Character player;
    bool gameRunning = true;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            player = createCharacter();
            printChapter();

            clearScreen();
            cout << "�� ���� �� �������� ������ ��� �� �����." << endl;
            cout << "1: ����� ���" << endl;
            cout << "2: ������ ����" << endl;
            cin >> choice;

            if (choice == 1) {
                cout << "�� ����� ��� � ����������� � ���." << endl;
                player.attack += 10;
                player.hasSword = true;
            }
            else {
                cout << "�� ������ �� ����� ��� � ����������� � ���." << endl;
            }
            waitForPress();

            cout << "�� ��� �� ��������� �������� � ���." << endl;
            cout << "�� ����� ���� ���������." << endl;
            cout << "� ��� �� ����� �� ����, �� ���� ��� ��� ���������� �����" << endl;
            waitForPress();

            cout << "�� ����� ��������� � �������������� ������." << endl;
            cout << "� ����� ����� ���� ���������� ���-�� ������� �� ��������." << endl;
            cout << "� ����� ��� ��� ������ ��������..." << endl;
            waitForPress();

            cout << "������������ ����������: � ��� ����� ����� ��� ������ �����?" << endl;
            waitForPress();

            cout << "��: ��-������, � �� ���������, � ��-�����, ��� ���� ���������, ��� ��� �� ����" << endl;
            waitForPress();

            cout << "������������ ����������: �� ��� �� ���� ������ *������* ��� ���� ��������� ��� ����� �� ���� ������" << endl;
            waitForPress();

            cout << "�� ������������� � ���!" << endl;
            waitForPress();

            Enemy enemy = createEnemy();
            bool victory = battle(player, enemy);

            if (victory) {
                cout << "�� �������� ������������ ����������!" << endl;
                waitForPress();

                // ��������� ������ � �����
                findChest(player);

                // ������ ��� ������ �������
                templeEntrance(player);
            }
            else {
                cout << "���� ��������." << endl;
                gameRunning = false;
            }
            waitForPress();
            break;
        }

        case 2: {
            if (SaveExists()) {
                if (LoadGame(player)) {
                    cout << "���� ��������� �������!" << endl;
                    cout << "����� ���������� �������, " << player.name << "!" << endl;
                    waitForPress();

                    templeEntrance(player);
                }
                else {
                    cout << "������ �������� ����!" << endl;
                    waitForPress();
                }
            }
            else {
                cout << "����������� ���� �� �������!" << endl;
                waitForPress();
            }
            break;
        }
        case 3:
            gameRunning = false;
            break;

        default:
            cout << "�������� �����!" << endl;
            break;
        }
    } while (gameRunning);

    cout << "������� �� ����!" << endl;

    return 0;
}