#include <iostream>
#include <conio.h>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>

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

void showMenu() {
    cout << "---������� ������� ������---" << endl;
    cout << "1: ����� ����" << endl;
    cout << "2: ����������" << endl;
    cout << "3: �����" << endl;
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

    player.health = 50;
    player.maxHealth = 90;
    player.attack = 12;
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
    goblin.attack = 11;
    goblin.defense = 6;
    return goblin;
}

Enemy createTempleGoblin() {
    Enemy goblin;
    goblin.name = "������";
    goblin.health = 35;
    goblin.attack = 13;
    goblin.defense = 7;
    return goblin;
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
                    cout << "�� ������������ ����� �������! +20 HP" << endl;
                    player.health += 20;
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
        cout << "�� ��������  �������!" << endl;
        cout << "� ����� ������." << endl;
        waitForPress();

        clearScreen();
        cout << "�� ���������� ���� � ����� � �������� ������." << endl;
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
        cout << "������� ����� �����. " << endl;
        cout << "--- ����� 2: � ������ ����� --- " << endl;

        waitForPress();

    }
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
                player.attack += 7;
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

        case 2:
            cout << "������� ����������� ���� ��� �� �����������." << endl;
            waitForPress();
            break;

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