#include <iostream>
#include <conio.h>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

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
bool SaveGame(const Character& player, const string& filename = "savegame.txt");
bool LoadGame(Character& player, const string& filename = "savegame.txt");
bool SaveExists(const string& filename = "savegame.txt");

void showMenu() {
    cout << "---Алхимия Вечного Заката---" << endl;
    cout << "1: Новая игра" << endl;
    cout << "2: Продолжить" << endl;
    cout << "3: Выйти" << endl;

    if (SaveExists()) {
        cout << "(Есть сохраненная игра)" << endl;
    }
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

    player.health = 125;
    player.maxHealth = 125;
    player.attack = 15;
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
    goblin.attack = 7;
    goblin.defense = 6;
    return goblin;
}

Enemy createTempleGoblin() {
    Enemy goblin;
    goblin.name = "Гоблин";
    goblin.health = 35;
    goblin.attack = 7;
    goblin.defense = 7;
    return goblin;
}

Enemy createTempleCatWoman() {
    Enemy catwoman;
    catwoman.name = "Незнакомка с кошкой";
    catwoman.health = 55;
    catwoman.attack = 14;
    catwoman.defense = 6;
    return catwoman;
}

Enemy createTempleGoblin1() {
    Enemy goblin1;
    goblin1.name = "Гоблин";
    goblin1.health = 35;
    goblin1.attack = 7;
    goblin1.defense = 7;
    return goblin1;
}

Enemy createTempleGoblin2() {
    Enemy goblin2;
    goblin2.name = "Гоблин";
    goblin2.health = 35;
    goblin2.attack = 7;
    goblin2.defense = 7;
    return goblin2;
}

Enemy createTempleTheBigCat() {
    Enemy cat;
    cat.name = "большой кот";
    cat.health = 75;
    cat.attack = 11;
    cat.defense = 8;
    return cat;
}

Enemy createTempleGoblin3() {
    Enemy goblin3;
    goblin3.name = "Гоблин";
    goblin3.health = 40;
    goblin3.attack = 10;
    goblin3.defense = 7;
    return goblin3;
}

Enemy createTempleOrg() {
    Enemy org;
    org.name = "Орг";
    org.health = 75;
    org.attack = 11;
    org.defense = 8;
    return org;
}

Enemy createTempleGoblin4() {
    Enemy goblin4;
    goblin4.name = "Гоблин";
    goblin4.health = 40;
    goblin4.attack = 10;
    goblin4.defense = 7;
    return goblin4;
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
                    cout << "Вы использовали зелье лечения! +25 HP" << endl;
                    player.health += 25;
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

void templeDoorRiddle() {
    clearScreen();

    cout << "1: Вода" << endl;
    cout << "2: Эхо" << endl;
    cout << "3: Огонь" << endl;

    int attempts = 3;
    bool doorOpened = false;

    while (attempts > 0 && !doorOpened) {
        int choice;
        cout << endl << "У вас попыток: " << attempts << endl;
        cout << "Выберите ответ (1-3): ";
        cin >> choice;

        if (choice == 2) {
            cout << "Символ эхо начинает светится! Дверь медленно открывается..." << endl;
            cout << "Вы угадали загадку!" << endl;
            doorOpened = true;
        }
        else {
            attempts--;
            cout << "Ничего не происходит. Дверь остается закрытой." << endl;
            if (attempts > 0) {
                cout << "Попробуй ещё раз." << endl;
            }
            waitForPress();
        }
    }

    if (!doorOpened) {
        cout << "Дверь так и не открылась. Возможно, нужно найти другой путь..." << endl;
    }
    else {
        cout << "Вы проходите через дверь и продолжаете свое путешествие..." << endl;
    }
    waitForPress();
}

void templeTheMysteryChest(Character& player) {
    clearScreen();
    cout << "1: Корни " << endl;
    cout << "2: Жизнь " << endl;
    cout << "3: Вода " << endl;

    int attempts = 3;
    bool chestOpened = false;
    while (attempts > 0 && !chestOpened) {
        int choice;
        cout << endl << "У вас попыток:" << attempts << endl;
        cout << "Выберите ответ (1 - 3) ";
        cin >> choice;
        if (choice == 3) {
            cout << "Сундук открылся. Вы отгадали загадку!" << endl;
            chestOpened = true;
            cout << "Замок щелкает! Сундук открывается..." << endl;
            cout << "Внутри вы находите:" << endl;
            cout << "- Зелье лечения (+45 HP)" << endl;
            player.hasPotion = true;
        }
        else {
            attempts--;
            cout << "Сундук не открылся. " << endl;
            if (attempts > 0) {
                cout << "Попробуйте ещё раз." << endl;
            }
            waitForPress();
        }
    }
}

void templeCrossroads(Character& player) {
    clearScreen();
    cout << "Вы пошли дальше и увидели развилку." << endl;
    cout << endl << "Куда пойдешь?" << endl;
    cout << "1: Левый проход" << endl;
    cout << "2: Центральный проход" << endl;
    cout << "3: Правый проход" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: // Левый проход - правильный
        clearScreen();
        cout << "Вы решили пойти налево." << endl;
        cout << "Вы пошли по коридору и ничего не подозревая и вы пристально смотрели вперед. " << endl;
        waitForPress();
        break;

    case 2: // Центральный проход - смертельная ловушка
        clearScreen();
        cout << "Вы решили пойти по центру." << endl;
        cout << "Вы пошли по коридору и ничего не подозревая из стен пошел яд и вы погибли." << endl;
        player.health = 0;
        waitForPress();
        break;

    case 3: // Правый проход - смертельная ловушка
        clearScreen();
        cout << "Вы решили пойти направо" << endl;
        cout << "Вы пошли по коридору и из стен начали выстреливать стрелы и не успев увернутся вы погибли." << endl;
        player.health = 0;
        waitForPress();
        break;

    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeCrossroads(player);
        break;
    }
}

void templeChoice(Character& player) {
    clearScreen();
    cout << "1: тихо." << endl;
    cout << "2: шумно." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        clearScreen();
        cout << "Вы решили выбраться шумно." << endl;
        cout << "Вы начали бежать и не увидели как выстрелила ядовитая стрела и вы умерли" << endl;
        player.health = 0;
        waitForPress();
        break;

    case 1:
        clearScreen();
        cout << "Вы решили идти тихо." << endl;
        cout << "Вы шли на цыпочках чтобы вас не заметили." << endl;
        waitForPress();
        break;
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeChoice(player);
    }
}

void templeDeathOrLife(Character& player) {
    clearScreen();
    cout << "1: пройти мимо." << endl;
    cout << "2: убить." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        clearScreen();
        cout << "Вы прошли мимо и ничего не произошло." << endl;
        waitForPress();
        break;
    case 2:
        cout << "Вы решили его убить и прошли дальше." << endl;
        waitForPress();
        break;
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeDeathOrLife(player);
    }
}

void templeOpenTheLocker(Character& player) {
    clearScreen();
    cout << "1: Сид" << endl;
    cout << "2: Кейли" << endl;
    cout << "3: Шепард " << endl;
    cout << "4: Тодд" << endl;
    cout << "5: Юффи" << endl;

    int attempts = 3;
    bool chestOpened = false;

    while (attempts > 0 && !chestOpened) {
        int choice;
        cout << endl << "У вас попыток:" << attempts << endl;
        cout << "Выберите ответ (1 - 5) ";
        cin >> choice;
        if (choice == 3) {
            cout << "Вы выбрали правильное имя, шкафчик открыт" << endl;
            chestOpened = true;
            cout << "В шкафу было зелье лечения (+55 HP)" << endl;
            player.hasPotion = true;
        }
        else {
            attempts--;
            cout << "Вы выбрали неправильное имя, шкафчик не открылся." << endl;
            if (attempts > 0) {
                cout << "Попробуйте ещё раз!" << endl;
            }
            waitForPress();
        }
    }
}

void temleAccuracy(Character& player) {
    clearScreen();
    cout << "1: медленно, аккуратно" << endl;
    cout << "2: быстро, не аккуратно " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "Вы побежали и перепрыгивая каждую ловушку и не заметив яму вы упали и из потолка обстреляли стрелы и вы умерли." << endl;
        waitForPress();
        break;
    case 1:
        cout << "Вы шли медленно обходя каждую ловушку и вы стали перед ямой, вы сделали длинный прыжок и пошли дальше." << endl;
        waitForPress();
        break;
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
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
        cout << "У вас осталось попыток: " << attemptsLeft << endl;
        cout << "Введите код из 4 цифр: ";
        cout << "6598-6580, 3895-3841?" << endl;
        cin >> attempt;

        if (attempt == 1854) {
            cout << "Замок щелкает! Сундук открывается..." << endl;
            cout << "Внутри вы находите:" << endl;
            cout << "- Зелье лечения (+25 HP)" << endl;
            cout << "- листок странными символами и цифрой 1." << endl;
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

void temleYesOrNo(Character& player) {
    clearScreen();
    cout << "Обыскать склад? " << endl;

    cout << "1: да." << endl;
    cout << "2: нет." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "Вы решили не обыскивать склад и пошли дальше." << endl;
        waitForPress();
        break;
    case 1:
        cout << "Вы решили обыскать склад." << endl;
        waitForPress();
        break;
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        temleYesOrNo(player);
    }
}

void templeANewSword(Character& player) {
    clearScreen();
    cout << "Осталась последняя коробка, что вы сделаете? " << endl;

    cout << "1: Обыскать" << endl;
    cout << "2: Не обыскивать" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "Вы решили не обыскивать последнюю коробку и пошли дальше." << endl;
        waitForPress();
        break;
    case 1:
        cout << "Вы решили обыскать последнюю коробку. " << endl;
        cout << "Коробка была длиной и не огромную в ширину." << endl;
        cout << "Вы открыли ее и там оказался идеально скованный меч и вы решили его взять." << endl;
        cout << "1: Взять новый меч" << endl;
        cout << "2: Оставить старый" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "А старый меч оставили в коробке." << endl;
            player.attack += 20;
            player.hasSword = true;
        }
        break;
    }
}

void templeRunOrGiveUp(Character& player) {
    clearScreen();
    cout << "Что вы будете делать?" << endl;

    cout << "1: Сдаться." << endl;
    cout << "2: Убежать." << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "Вы решили убежать..." << endl;
        cout << "Вы развернулись и начали бежать в сторону склада и решили спрятаться в складе." << endl;
        cout << "Вы спрятались в складе и ждали когда орги уйдут." << endl;
        cout << "После вы вышли из склада и увидели на полу листок странными символами было написана цифра 4." << endl;
        cout << "Вы его взяли и пошли дальше..." << endl;
        waitForPress();
        break;
    case 1:
        cout << "Вы сдались и орги вас связали и ударили дубинкой и вы отключились." << endl;
        cout << "Вы проснулись в темнице, без меча вы решайте выбраться отсюда." << endl;
        waitForPress();
        break;
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeRunOrGiveUp(player);
    }
}

void templeChoice1(Character& player) {
    clearScreen();
    cout << "1: Пойти в хранилище. " << endl;
    cout << "2: Сбежать. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Вы решили пойти в хранилище может быть там ваш меч." << endl;
        waitForPress();
        break;
    case 2:
        cout << "Вы решили не идти в хранилище и решили убежать но выход охраняли несколько оргов. " << endl;
        cout << "И как вы без оружия вы решили пробежать и это успешно получилось. " << endl;
        cout << "Вы забежали в склад и спрятались. " << endl;
        cout << "Спустя время вы решили взять старый меч который вы оставили тут. " << endl;
        player.attack += 10;
        cout << "Вы вышли из склада и осмотрелись по сторонам и никого не увидели и пошли дальше. " << endl;
        cout << "Вы шли и увидели орга, но вы увидели что у него листок странными символами " << endl;
        cout << "Вы решили его убить и получить листок странными символами. " << endl;
        cout << "После победы над оргом вы взяли у него листок странными символами цифра 4. " << endl;
        waitForPress();
        break;
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeChoice1(player);
    }
}

void templeChoice2(Character& player) {
    clearScreen();
    cout << "1: убить. " << endl;
    cout << "2: украсть листок странными символами и убежать. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Вы решили задушить орга, но вы не подумали что он сильнее вас и он вас убил. " << endl;
        waitForPress();
        break;
    case 2:
        cout << "Вы аккуратно взяли листок странными символами и убежали. " << endl;
        cout << "На листок странными символами было написана цифра 4. " << endl;
        waitForPress();
        break;
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeChoice2(player);
    }
}

void templeTheAltar(Character& player) {
    clearScreen();
    cout << "Вы увидели алтарь... " << endl;
    cout << "Что вы будите делать? " << endl;
    cout << "1: Сохранитесь и восполните здоровия. " << endl;
    cout << "2: Пройдете мимо. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2: 
        cout << "Вы решили пройти мимо. " << endl;
        waitForPress;
        break;
    case 1:
        cout << "Вы решили воспользоватся алтаром" << endl;
        cout << "*Алтарь полносьтю выстонавливает здорови." << endl;
        cout << "И сохранает прогрес*  " << endl;

        player.health = 125;

        if (SaveGame(player)) {
            cout << "Игра сохранена." << endl;
        }
        else {
            cout << "Не удалось сохранить игру!" << endl;
        }
        
        waitForPress;
        break;
        
    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeTheAltar(player);
    }
}

void templeTheAltarOfficial(Character& player) {
    clearScreen();
    cout << "Вы шли и увидели алтарь..." << endl;    
    cout << "1: Сохранитесь и восполните здоровия. " << endl;
    cout << "2: Пройдете мимо. " << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 2:
        cout << "Вы решили пройти мимо. " << endl;
        waitForPress;
        break;
    case 1:
        cout << "Вы решили воспользоватся алтаром" << endl;

        player.health = 125;

        if (SaveGame(player)) {
            cout << "Игра сохранена." << endl;
        }
        else {
            cout << "Не удалось сохранить игру!" << endl;
        }

        waitForPress;
        break;

    default:
        cout << "Неверный выбор! Попробуйте еще раз." << endl;
        waitForPress();
        templeTheAltarOfficial(player);
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
        cout << "Вы победили гоблина!" << endl;
        cout << "И пошли дальше." << endl;
        waitForPress();

        clearScreen();
        cout << "Вы продолжили путь к храму и наступил рассвет." << endl;
        cout << "И вот вы подошли к храму, вы начали открывать дверь, но вдруг перед вами появился ещё один гоблин." << endl;
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
        cout << "Началась новая глава. " << endl;
        cout << "--- Глава 2: В поиски мечты --- " << endl;

        cout << "Вы вошли в храм, но он выглядел довольно новый. " << endl;
        cout << "Но вы не стали обращать внимание и вы пошли дальше. " << endl;
        cout << "Вы держали перед собой меч и вы аккуратно шли и осматривались. " << endl;
        cout << "Но вдруг перед путем появилась дверь. " << endl;

        cout << " *Надо было решить загадку чтобы открыть дверь*" << endl;
        cout << "Над дверью высечена надпись:" << endl;
        cout << "Я говорю без рта и слышу без ушей, у меня нет тела, но я оживаю с ветром, что я такое?" << endl;

        waitForPress();
        templeDoorRiddle();

        cout << "После открытия двери вы пошли дальше..." << endl;
        cout << "Вы дальше отправились по коридору, он был довольно длинный." << endl;
        cout << "Но вдруг вы что-то услышали, вы сжали меч сильней. " << endl;
        cout << "Но это оказалось просто кот. Стоп кот??" << endl;
        cout << "Кот: Киси-киси, мяу-мяу киси-киси, мяу-мяу" << endl;
        cout << "И вдруг из угла вышла женщина в плаще, и начала говорить..." << endl;
        cout << "Незнакомка с кошкой: Что за незнакомец к нам пришел сюда. " << endl;
        cout << "Незнакомка с кошкой: Зря ты сюда пришел если ты за философским камнем даже не пытайся. " << endl;
        cout << "Незнакомка с кошкой: А это ты, тот самый алхимик который ничего не умеет делать." << endl;
        cout << "Вы: Молчи!! Что тебе надо от меня." << endl;
        cout << "Незнакомка с кошкой: Мне ничего, ну если подраться с тобой немного *хихиихи*" << endl;
        cout << "Вы приготовились к бою!" << endl;
        waitForPress();
    }

    Enemy templeCatWoman = createTempleCatWoman();
    victory = battle(player, templeCatWoman);

    if (victory) {
        cout << "После победы над незнакомкой с кошкой вы продолжили путь." << endl;
        cout << "*Забыв о кошке.*" << endl;
        cout << "Тем временем кошка..." << endl;
        cout << "Кошка: Я отомщу за неё!" << endl;
        waitForPress();
        templeTheAltar(player);

        cout << "Вы шли по пугающему коридору." << endl;
        cout << "Как не странно, но в храме было довольно светло" << endl;
        cout << "По пути не зная куда вы задумались, а вдруг философского камня реально нету." << endl;
        cout << "Но ваши мысли остановил гоблин." << endl;
        cout << "Гоблин: ТЫ НЕ ПРОЙДЕШЬ!!" << endl;
        cout << "Вы приготовились к бою!" << endl;
        waitForPress();
    }

    Enemy templeGoblin1 = createTempleGoblin1();
    victory = battle(player, templeGoblin1);

    if (victory) {
        cout << "Вы продолжили путь.. " << endl;
        cout << "За углом вы увидели сундук. " << endl;
        cout << "На сундуке были символы. " << endl;
        cout << "Вы решили решить эту загадку. " << endl;
        cout << "*Надо было выбрать один символ чтобы открыть сундук* " << endl;
        cout << "На сундуке была надпись *Чтобы открыть отгадать загадку*  " << endl;
        cout << "*Она везде в почве, в небе, в воздухе, в реке, в море, в овощах, во фруктах и даже в человеке.*" << endl;

        waitForPress();
        templeTheMysteryChest(player);
    }

    if (victory) {
        templeCrossroads(player);

        cout << "Вы пошли по коридору и ничего не подозревая и вы пристально смотрели вперед. " << endl;
        cout << "И не зря из угла вышел гоблин." << endl;
        cout << "Вы приготовились к бою!" << endl;
        waitForPress();
    }

    Enemy templeGoblin2 = createTempleGoblin2();
    victory = battle(player, templeGoblin2);

    if (victory) {
        cout << "После победы над гоблином вы пошли дальше." << endl;
        cout << "Вы пошли направо по указателю ничего не подозревая." << endl;
        cout << "Вы вышли в большую комнату." << endl;
        cout << "И из всех дыр начали выходить коты и собираться в одного большого кота." << endl;
        cout << "И главный из них сказал." << endl;
        cout << "Кот: Я отомщу за хозяйку!!" << endl;
        cout << "Вы поняли что это тот самый кот." << endl;
        cout << "Вы приготовились к бою!" << endl;
        waitForPress();
    }

    Enemy templeTheBigCat = createTempleTheBigCat();
    victory = battle(player, templeTheBigCat);

    if (victory) {
        cout << "После победы над большим котом вы решили отдохнуть после такого путешествия." << endl;
        cout << "Но вдруг и проснулись от леща в щеку, вы поняли что вы связаны и вас куда-то тащат." << endl;
        cout << "Вы потеряли сознания." << endl;

        if (SaveGame(player)) {
            cout << "Игра сохранена." << endl;
        }
        else {
            cout << "Не удалось сохранить игру!" << endl;
        }

        cout << "Вы проснулись повешены вверх ногами, вы начали выбираться и упали на пол этого никто не услышал." << endl;
        cout << "Вы решили выбраться отсюда, как вы будете действовать?" << endl;

        waitForPress();

        templeChoice(player);

        cout << "Перед вами есть гоблин, что вы будете делать?" << endl;

        waitForPress();

        templeDeathOrLife(player);
    }

    if (victory) {
        cout << "Вы шли и увидели развилку, но вы увидели табличку и пошли по ней." << endl;
        cout << "Вы вышли, но перед вами появился довольно сильный гоблин, но вы не испугались." << endl;
        cout << "Вы приготовились к бою!" << endl;
        waitForPress();
    }

    Enemy templeGoblin3 = createTempleGoblin3();
    victory = battle(player, templeGoblin3);

    if (victory) {
        cout << "После победы вы пошли дальше" << endl;
        cout << "Вы пошли по коридору и увидели дверь в раздевалку." << endl;
        cout << "Вы увидели шкафы и один был закрыт и вы решили его открыть." << endl;
        cout << "Чтобы его открыть нужно ввести нужное имя." << endl;

        waitForPress();
        templeOpenTheLocker(player);
    }

    if (victory) {
        cout << "Вы вышли из раздевалки и пошли дальше." << endl;
        cout << "Вы пошли дальше по коридору." << endl;
        cout << "И вы чуть не наступили на кнопку." << endl;
        cout << "Вы перепрыгнули ее и стали более внимательными." << endl;
        cout << "Вы перепрыгнули еще и еще ловушку." << endl;
        cout << "И вы решили выбрать как вы пройдете дальше. " << endl;

        waitForPress();
        temleAccuracy(player);
    }

    if (victory) {
        cout << "Вы шли и увидели крысу после переключили взгляд вперед и увидели гоблина он начал атаковать, но вы увернулись и одним сильным ударом вы его победили." << endl;
        cout << "И из него выпал листок странными символами и цифрой 3.  " << endl;
        cout << "Вы пошли дальше и увидели сундук." << endl;
        cout << "И решили его открыть." << endl;

        waitForPress();
        findChest1(player);
    }

    if (victory) {
        cout << "Вы пошли дальше и устали вы увидели комнату и решили закрыть проход и немного поспать." << endl;

        if (SaveGame(player)) {
            cout << "Игра сохранена." << endl;
        }
        else {
            cout << "Не удалось сохранить игру!" << endl;
        }

        cout << "После не длительного сна вы проснулись и посмотрели через баррикады и никого не увидели" << endl;
        cout << "Вы разобрали баррикады и пошли дальше." << endl;
        cout << "И как только вы вышли из потолка выпрыгнул орг." << endl;
        cout << "Вы приготовились к бою!" << endl;

        waitForPress();
    }

    Enemy templeOrg = createTempleOrg();
    victory = battle(player, templeOrg);

    if (victory) {
        cout << "После победы над оргом вы пошли дальше." << endl;
        cout << "Вы шли и увидели склад." << endl;

        waitForPress();
        temleYesOrNo(player);

        cout << "Вы вошли в склад и начали обыскивать коробки и ничего толком не нашли." << endl;
        waitForPress();
        templeANewSword(player);
    }

    if (victory) {
        cout << "Вы вышли из склада вы пошли дальше исследовать храм." << endl;
        cout << "Вы шли и ничего не подозревая вдруг из углов вышла толпа оргов." << endl;

        waitForPress();
        templeRunOrGiveUp(player);

        cout << "Вы сдались и орги вас связали и ударили дубинкой и вы отключились." << endl;
        cout << "Вы проснулись в темнице, без меча вы решайте выбраться отсюда." << endl;
        waitForPress();

        cout << "Вы вышли куда вы пойдете дальше?" << endl;
        waitForPress();
        templeChoice1(player);
    }

    if (victory) {
        cout << "Вы шли аккуратно чтобы вас не поймали и увидели спящего орга вы думали пойти мимо, но вы увидели у него листок странными символами, что вы будете делать? " << endl;

        waitForPress();
        templeChoice2(player);

        cout << "Вы дошли до хранилища и взгляд сразу упал на ваш меч. " << endl;
        cout << "Вы его взяли и пошли дальше. " << endl;
        cout << "Но уже перед вами ждал гоблин, вы задумались что он тут делает, но поняли что надо сражаться. " << endl;
        cout << " Вы приготовились к бою! " << endl;
    }

    Enemy templeGoblin4 = createTempleGoblin4();
    victory = battle(player, templeGoblin4);

    if (victory) {
        cout << "После победы вы решили спрятаться чтобы вас не заметили. " << endl;
        cout << "Спустя несколько минут вы сбежали и продолжили путь. " << endl;

        if (SaveGame(player)) {
            cout << "Игра сохранена." << endl;
        }
        else {
            cout << "Не удалось сохранить игру!" << endl;
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
            cout << "По пути вы находите старый меч на земле." << endl;
            cout << "1: Взять Меч" << endl;
            cout << "2: Пройти мимо" << endl;
            cin >> choice;

            if (choice == 1) {
                cout << "Вы взяли меч и отправились в лес." << endl;
                player.attack += 10;
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

        case 2: {
            if (SaveExists()) {
                if (LoadGame(player)) {
                    cout << "Игра загружена успешно!" << endl;
                    cout << "Добро пожаловать обратно, " << player.name << "!" << endl;
                    waitForPress();

                    templeEntrance(player);
                }
                else {
                    cout << "Ошибка загрузки игры!" << endl;
                    waitForPress();
                }
            }
            else {
                cout << "Сохраненная игра не найдена!" << endl;
                waitForPress();
            }
            break;
        }
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