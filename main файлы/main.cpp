#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <windows.h>

/*  The basketball class - это компьютерная игра, в которой вы выступаете в
    роли капитана и плеймейкера команды Дартмутского колледжа
    В игре используются заданные вероятности для моделирования исходов каждой игры.
    Вы можете выбирать типы бросков, а также оборонительные схемы */

const int ATTACK_TIME = 24;

int startMenu();
void author();
void gameRules();
int choiceDefense();
int jumpBall();
int probabilityHit();
void attackShot(int& shot);
bool playerAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense);
bool opponentAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName);
bool rebound();
void game(int jump, int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName, std::string myTeam);
void score(int scorePlayer, int scoreOpponent);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int scorePlayer{ 0 }, scoreOpponent{ 0 }, shot;
    int startGame = startMenu();
    if (startGame == 4)
    {
        return 0;
    }
    std::cout << "Вашей стартовой защитой будет...";
    int defense = choiceDefense();
    std::string opponentName, myTeam = "Дартмутский колледж";
    std::cout << "Введите название команды противника: ";
    std::cin.ignore();
    std::getline(std::cin, opponentName);
    std::cout << "\n";
    int jump = jumpBall();
    if (jump == 0)
    {
        std::cout << "Судья подкидывает мяч вверх в центральном круге и...\n";
        Sleep(1000);
        std::cout << "Вбрасывание выигрывает команда: " << myTeam << ".\n\n";
    }
    else
    {
        std::cout << "Судья подкидывает мяч вверх в центральном круге и...\n";
        Sleep(1000);
        std::cout << "Вбрасывание выигрывает команда: " << opponentName << ".\n\n";
    }
    game(jump, scorePlayer, scoreOpponent, shot, defense, opponentName, myTeam);
    std::cout << "\nЗвучит свисток, сейчас команды уйдут на перерыв!\nУслышимся после небольшой паузы!\n\n";
    std::system("pause");
    std::system("cls");
    std::cout << "Начинается второй тайм! ПОЕХАЛИ!!!\n\n";
    if (jump == 0)
    {
        jump = 1;
    }
    else
    {
        jump = 0;
    }
    game(jump, scorePlayer, scoreOpponent, shot, defense, opponentName, myTeam);
    std::cout << "Последние секунды матча истекли! Судья дает свисток!\nФинальный счет на табло:\n" << myTeam << ' ' << scorePlayer << ' ' << opponentName << ": " << scoreOpponent << ".\n";
    if (scorePlayer > scoreOpponent)
    {
        std::cout << "Поздравляем команду " << myTeam << " с победой!";
    }
    else if (scorePlayer < scoreOpponent)
    {
        std::cout << "Поздравляем команду " << opponentName << " с победой!";
    }
    else
    {
        std::cout << "Сегодня победитель не выявлен, но в следующий раз победит сильнейший!\n\n";
    }
    std::cout << std::endl;
    std::system("pause");
    return 0;
}

int startMenu()
{
    int startGame{};
    std::cout << "Добро пожаловать в игру \"Баскетбол\"\n";
    std::cout << "1. Правила игры.\n";
    std::cout << "2. Начать игру.\n";
    std::cout << "3. Об авторе.\n";
    std::cout << "4. Выйти из игры.\n\n";
    std::cout << "Для продолжения выберете действие: ";
    std::cin >> startGame;
    std::cout << "\n";
    if (startGame == 1 || startGame == 3)

    {
        while (startGame == 1 || startGame == 3)
        {
            if (startGame == 1)
            {
                gameRules();
                std::cout << "1. Правила игры.\n";
                std::cout << "2. Начать игру.\n";
                std::cout << "3. Об авторе.\n";
                std::cout << "4. Выйти из игры.\n\n";
                std::cout << "Для продолжения выберете действие: ";
                std::cin >> startGame;
                std::cout << "\n";
            }
            else if (startGame == 3)
            {
                author();
                std::cout << "1. Правила игры.\n";
                std::cout << "2. Начать игру.\n";
                std::cout << "3. Об авторе.\n";
                std::cout << "4. Выйти из игры.\n\n";
                std::cout << "Для продолжения выберете действие: ";
                std::cin >> startGame;
                std::cout << "\n";
            }
        }
    }

    return startGame;
}

void author()
{
    std::cout << "Студия разработки игр Dialas представляет.\nАвтор: Медведенко Егор(ник: mee1b).\nВерсия: 1.0.1.\n\n";
}

void gameRules()
{
    // Объясняет ввод с клавиатуры
    std::cout << "Это баскетбольный клуб Дартмутского колледжа. ";
    std::cout << "Ты будешь капитаном и плеймейкером нашей команды.\n";
    std::cout << "Игра длится 2 тайма по 4 минуты. Одна атака длится 24 секунды.\n\n";
    std::cout << "Делайте броски следующим образом:\n";
    std::cout << "1. Дальний (трехочковый) бросок в прыжке;\n2. Средний (двухочковый) бросок в прыжке;\n3. Лэй - апп (два очка);\n4. Комбинация и бросок (два очка);\n\n";//очки, возможно, будут переработаны
    std::cout << "Обе команды будут использовать одну и ту же защиту.\nВыберите схему следующим образом:\n";
    std::cout << "6. Прессинг - эффективная защита (шанс всех бросков снижен на 10%);\n";
    std::cout << "7. Личная опека - отличная защита от средних и ближних бросков (шанс удачного среднего броска и лэй - аппа -10%),\n";
    std::cout << "но открывается огромный простор для дальних бросков и комбинаций (шанс удачного дальнего броска и комбинаций + 15 %);\n";
    std::cout << "8. Зонная защита - отличная защита от дальних бросков и комбинаций (шанс удачного дальнего броска и комбинации -10%),\n";
    std::cout << "но открывается огромный простор для лэй - аппов и средних бросков (шанс удачного лэй - аппа и средних бросков + 15%);\n";
    std::cout << "9. Нет защиты - команда отдыхает в защите (повышается шанс удачной реализации всех бросков +20%);\n";
    std::cout << "Чтобы изменить защиту, просто введите 0 в качестве следующего броска.\n\n";
    std::system("pause");
    std::system("cls");
}

int choiceDefense()
{
    int defense{};
    std::cout << "(Чтобы посмотреть схемы защиты нажмите 1.)";
    std::cin >> defense;
    while (defense == 1)
    {
        std::cout << "6. Прессинг - эффективная защита (шанс всех бросков снижен на 10%);\n";
        std::cout << "7. Личная опека - отличная защита от средних и ближних бросков (шанс удачного среднего броска и лэй - аппа -10%),\n";
        std::cout << "но открывается огромный простор для дальних бросков и комбинаций (шанс удачного дальнего броска и комбинаций + 15 %);\n";
        std::cout << "8. Зонная защита - отличная защита от дальних бросков и комбинаций (шанс удачного дальнего броска и комбинации -10%),\n";
        std::cout << "но открывается огромный простор для лэй - аппов и средних бросков (шанс удачного лэй - аппа и средних бросков + 15%);\n";
        std::cout << "9. Нет защиты - команда отдыхает в защите (повышается шанс удачной реализации всех бросков +20%);\n";
        std::cout << "Какой будет наша защита? ";
        std::cin >> defense;
    }
    while (defense < 6 || defense > 9)
    {
        std::cout << "На тренировках мы не разбирали эти схемы, капитан!\nДавай сыграем то, что мы уже знаем!\n";
        std::cout << "Какой будет наша защита? ";
        std::cin >> defense;
    }

    return defense;
}

int jumpBall()
{
    srand(static_cast<unsigned int>(time(0)));
    if ((rand() % 100 + 1) > 40)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int probabilityHit()
{
    srand(static_cast<unsigned int>(time(0)));
    int hit = (rand() % 100) + 1;

    return hit;
}

void attackShot(int& shot)
{
    std::cout << "Капитан! Какой бросок делаем в этой атаке?(чтобы посмотреть виды бросков нажмите 5): ";
    std::cin >> shot;
    while (shot == 5)
    {
        std::cout << "1. Дальний (трехочковый) бросок в прыжке;\n2. Средний (двухочковый) бросок в прыжке;\n3. Лэй - апп (два очка);\n4. Комбинация и бросок (2 очка)\n\n";
        attackShot(shot);
    }
    while (shot < 0 || shot > 5)
    {
        std::cout << "На тренировках мы не разбирали такие броски, капитан!\nДавай сыграем то, что мы уже знаем!\n";
        std::cout << "Какой бросок делаем в этой атаке? ";
        std::cin >> shot;
    }
}

bool playerAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense)
{
    int hit{ 0 };
    attackShot(shot);
    std::cout << "\n";
    while (shot == 0)
    {
        if (shot == 0)
        {
            std::cout << "\nКапитан, какую схему защиты играем? ";
            defense = choiceDefense();
            attackShot(shot);
        }
    }
    if (shot == 1)
    {
        //Шанс трехочкового 40% - базовый
        std::cout << "Трехочковый бросок!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 70)
            {
                std::cout << "Три очка в корзине!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 45)
            {
                std::cout << "Три очка в корзине!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 70)
            {
                std::cout << "Три очка в корзине!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 40)
            {
                std::cout << "Три очка в корзине!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }

    }
    if (shot == 2)
    {
        //Шанс двухочкового 50% - базовый
        std::cout << "Средний бросок!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 60)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 60)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 35)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 30)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (shot == 3)
    {
        //Шанс лэй - аппа 60% - базовый
        std::cout << "Это же лэй - апп!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 50)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 50)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 25)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 20)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (shot == 4)
    {
        //Шанс комбинации 55% - базовый
        std::cout << "Смотрите, игроки разыгрывают комбинацию!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 65)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 40)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 65)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 35)
            {
                std::cout << "Два очка в корзине!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    std::cout << "\n\n";
    return false;
}

bool opponentAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName)
{
    int hit{ 0 };
    srand(static_cast<unsigned int>(time(0)));
    shot = (rand() % 4) + 1;
    std::cout << opponentName << " в атаке:\n";
    if (shot == 1)
    {
        //Шанс трехочкового 40% - базовый
        std::cout << "Трехочковый бросок!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 70)
            {
                std::cout << "Три очка в корзине!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 45)
            {
                std::cout << "Три очка в корзине!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 70)
            {
                std::cout << "Три очка в корзине!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 40)
            {
                std::cout << "Три очка в корзине!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }

    }
    if (shot == 2)
    {
        //Шанс двухочкового 50% - базовый
        std::cout << "Средний бросок!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 60)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 60)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 35)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 30)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (shot == 3)
    {
        //Шанс лэй - аппа 60% - базовый
        std::cout << "Это же лэй - апп!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 50)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 50)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 25)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 20)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (shot == 4)
    {
        //Шанс комбинации 55% - базовый
        std::cout << "Смотрите, игроки разыгрывают комбинацию!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 65)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 7:
            if (hit > 40)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 8:
            if (hit > 65)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case 9:
            if (hit > 35)
            {
                std::cout << "Два очка в корзине!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    std::cout << "\n\n";
    return false;
}

bool rebound()
{
    srand(static_cast<unsigned int>(time(0)));
    if ((rand() % 100 + 1) > 60)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void game(int jump, int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName, std::string myTeam)
{
    int period{ 0 };
    while (period < 120)
    {
        if (jump == 0)
        {
            if (!playerAttack(scorePlayer, scoreOpponent, shot, defense))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в атаке за командой: " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
            if (!opponentAttack(scorePlayer, scoreOpponent, shot, defense, opponentName))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в атаке за командой: " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                    opponentAttack(scorePlayer, scoreOpponent, shot, defense, opponentName);
                    period += ATTACK_TIME;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
        }
        else if (jump == 1)
        {
            if (!opponentAttack(scorePlayer, scoreOpponent, shot, defense, opponentName))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в защите за командой: " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
            if (!playerAttack(scorePlayer, scoreOpponent, shot, defense))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в защите за командой: " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                    playerAttack(scorePlayer, scoreOpponent, shot, defense);
                    period += ATTACK_TIME;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
        }
    }
}

void score(int scorePlayer, int scoreOpponent)
{
    std::cout << "Счет: " << scorePlayer << ' ' << scoreOpponent << "\n\n";
}