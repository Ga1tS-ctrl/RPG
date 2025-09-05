#include <iostream>
#include <conio.h>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Структура для гг
struct Character {
    string name;
    int health;
    int maxHealth;
    int attack;
    int defense;
    bool hasSword;
    bool hasPotion;
};

// Структура для врагов
struct Enemy {
    string name;
    int health;
    int attack;
    int defense;
};

void PrintCharet();  

void showMenu() {
    cout << "---Алхимия Вечного Заката---" << endl;
    cout << "1: Новая игра" << endl;
    cout << "2: Продолжить" << endl;
    cout << "3: Выйти" << endl;
}

void clearScreen() {
    system("cls");
}

void waitForPress() {
    cout << "Нажмите любую клавишу для продолжения...";
    _getch();
    cout << endl;
}

Character createCharacter() {
    Character player;
    clearScreen();
    cout << "--- НОВАЯ ИГРА ---" << endl;
    cout << "Введите имя вашего персонажа: ";
    cin.ignore();
    getline(cin, player.name);

    player.health = 50;
    player.maxHealth = 90;
    player.attack = 12;
    player.defense = 5;
    player.hasSword = false;
    player.hasPotion = false;

    cout << "Добро пожаловать, " << player.name << "!" << endl;
    cout << "Ваше путешествие в мире Алхимии Вечного Заката начинается..." << endl;
    waitForPress();

    return player;
}

void printChapter() {
    clearScreen();
    cout << "--- Глава 1: Выжить до рассвета --- " << endl;
    cout << "Вы открываете глаза и видите над собой темное небо, усыпанное звездами." << endl;
    cout << "Воздух наполнен ароматом редких трав и магии." << endl;
    cout << "Где-то вдали слытится шепот духов..." << endl;
    cout << "Но вдруг вы слышите как в лесу кто-то кричит, похоже на женский голос... " << endl;
    cout << "И вы решили пойти и посмотреть кто там..." << endl;

    waitForPress();
}

Enemy createEnemy() {
    Enemy enemy;
    enemy.name = "Таинственная незнакомка";
    enemy.health = 40;
    enemy.attack = 14;
    enemy.defense = 5;
    return enemy;
}

Enemy createGoblin() {
    Enemy goblin;
    goblin.name = "Гоблин";
    goblin.health = 30;
    goblin.attack = 11;
    goblin.defense = 6;
    return goblin;
}

Enemy createTempleGoblin() {
    Enemy goblin;
    goblin.name = "Гоблин";
    goblin.health = 35;
    goblin.attack = 13;
    goblin.defense = 7;
    return goblin;
}

void showBattleStatus(const Character& player, const Enemy& enemy) {
    cout << "=== БОЙ ===" << endl;
    cout << player.name << ": " << player.health << "/" << player.maxHealth << " HP" << endl;
    cout << enemy.name << ": " << enemy.health << " HP" << endl;
    cout << "-------------------" << endl;
}

void showBattleMenu() {
    cout << "1: Атаковать" << endl;
    cout << "2: Защищаться" << endl;
    cout << "3: Использовать предмет" << endl;
    cout << "4: Попытаться убежать" << endl;
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
            cout << "Ваш ход! Выберите действие:" << endl;
            showBattleMenu();
            cin >> choice;

            switch (choice) {
            case 1: {
                int damage = calculateDamage(player.attack, enemy.defense);
                enemy.health -= damage;
                cout << "Вы нанесли " << damage << " урона!" << endl;
                break;
            }
            case 2: {
                int bonusDefense = player.defense * 2;
                cout << "Вы готовитесь к защите! Защита увеличена на этот ход." << endl;
                break;
            }
            case 3: {
                if (player.hasPotion) {
                    cout << "Вы использовали зелье лечения! +20 HP" << endl;
                    player.health += 20;
                    if (player.health > player.maxHealth) player.health = player.maxHealth;
                    player.hasPotion = false;
                }
                else {
                    cout << "У вас нет предметов!" << endl;
                }
                break;
            }
            case 4: {
                cout << "Попытка побега неудачна! Враг слишком близко." << endl;
                break;
            }
            default:
                cout << "Неверный выбор!" << endl;
                continue;
            }
        }
        else {
            cout << "Ход противника!" << endl;
            int damage = calculateDamage(enemy.attack, player.defense);
            player.health -= damage;
            cout << enemy.name << " наносит вам " << damage << " урона!" << endl;
        }

        waitForPress();
        playerTurn = !playerTurn;
    }

    clearScreen();
    if (player.health > 0) {
        cout << "ПОБЕДА! Вы одолели " << enemy.name << "!" << endl;
        return true;
    }
    else {
        cout << "ПОРАЖЕНИЕ! Вы были побеждены." << endl;
        return false;
    }
}

void findChest(Character& player) {
    clearScreen();
    cout << "После победы над монстром вы решили исследовать лес..." << endl;
    cout << "И после немного плутания по лесу вы увидели за деревом сундук " << endl;
    cout << "Вы решили попробовать его открыть..." << endl;

    int attempt;
    int attemptsLeft = 3;
    bool chestOpened = false;

    while (attemptsLeft > 0 && !chestOpened) {
        cout << "У вас осталось попыток: " << attemptsLeft << endl;
        cout << "Введите код из 4 цифр: ";
        cout << "168-100, 154-100?" << endl;
        cin >> attempt;

        if (attempt == 6854) {
            cout << "Замок щелкает! Сундук открывается..." << endl;
            cout << "Внутри вы находите:" << endl;
            cout << "- Зелье лечения (+20 HP)" << endl;
            cout << "- Древнюю карту с отметкой храма" << endl;
            player.hasPotion = true;
            chestOpened = true;
        }
        else {
            attemptsLeft--;
            cout << "Неверный код! Замок не открывается." << endl;
            if (attemptsLeft > 0) {
                cout << "Попробуйте еще раз." << endl;
            }
        }
        waitForPress();
    }

    if (!chestOpened) {
        cout << "Сундук остается закрытым. Возможно, вы найдете код позже..." << endl;
        waitForPress();
    }
}

void templeEntrance(Character& player) {
    clearScreen();
    cout << "Следуя по карте из сундука, вы начали направляться к храму." << endl;
    cout << "На улице почти светлело.." << endl;
    cout << "Но вдруг перед вами появляется гоблин!" << endl;
    cout << "Гоблин: Гррр... Чужак! Не пройдешь!" << endl;
    cout << "Вы приготовились к бою!" << endl;
    waitForPress();

    // Бой с гоблином
    Enemy goblin = createGoblin();
    bool victory = battle(player, goblin);

    if (victory) {
        cout << "Вы победили  гоблина!" << endl;
        cout << "И пошли дальше." << endl;
        waitForPress();

        clearScreen();
        cout << "Вы продолжили путь к храму и наступил расвет." << endl;
        cout << "И вот вы подошли к храму, вы начили открывать дверь, но вдруг перед вами пояаился ещё один гоблин." << endl;
        cout << "Вы приготовились к бою!" << endl;

        waitForPress();
    }

    // Второй бой с гоблином-стражем храма
    Enemy templeGoblin = createTempleGoblin();
    victory = battle(player, templeGoblin);

    if (victory) {
        cout << "Вы победили гоблина-стража храма!" << endl;
        cout << "Вы дожили до рассвета." << endl;
        cout << "Вы пошли в храм." << endl;
        cout << "Вы прошли 1 главу!" << endl;
        cout << "Нчалась новая глава. " << endl;
        cout << "--- Глава 2: В пойски мечты --- " << endl;

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
            cout << "По пути вы находите старый меч на земле." << endl;
            cout << "1: Взять Меч" << endl;
            cout << "2: Пройти мимо" << endl;
            cin >> choice;

            if (choice == 1) {
                cout << "Вы взяли меч и отправились в лес." << endl;
                player.attack += 7;
                player.hasSword = true;
            }
            else {
                cout << "Вы решили не брать меч и отправились в лес." << endl;
            }
            waitForPress();

            cout << "Вы шли по освежённой тропинке в лес." << endl;
            cout << "На улице было прохладно." << endl;
            cout << "И вот вы дошли до леса, из леса все ещё доносились крики" << endl;
            waitForPress();

            cout << "Вы идете аккуратно и осматриваетесь вокруг." << endl;
            cout << "И вдруг перед вами появляется что-то похожее на человека." << endl;
            cout << "И вдруг она вам начала говорить..." << endl;
            waitForPress();

            cout << "Таинственная незнакомка: И что такой малыш тут делает здесь?" << endl;
            waitForPress();

            cout << "Вы: Во-первых, я не маленький, а во-торых, мне было интересно, что это за крик" << endl;
            waitForPress();

            cout << "Таинственная незнакомка: Ну зря ты сюда пришел *хихихи* это твой последний раз когда ты меня видишь" << endl;
            waitForPress();

            cout << "Вы приготовились к бою!" << endl;
            waitForPress();

            Enemy enemy = createEnemy();
            bool victory = battle(player, enemy);

            if (victory) {
                cout << "Вы победили Таинственную незнакомку!" << endl;
                waitForPress();

                // Добавляем сундук с кодом
                findChest(player);

                // Первый бой против гоблина
                templeEntrance(player);
            }
            else {
                cout << "Игра окончена." << endl;
                gameRunning = false;
            }
            waitForPress();
            break;
        }

        case 2:
            cout << "Функция продолжения игры еще не реализована." << endl;
            waitForPress();
            break;

        case 3:
            gameRunning = false;
            break;

        default:
            cout << "Неверный выбор!" << endl;
            break;
        }
    } while (gameRunning);

    cout << "Спасибо за игру!" << endl;

    return 0;
}