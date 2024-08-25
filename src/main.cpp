#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <windows.h>


bool testingEnabled{};

enum Shots
{
    THREE_POINT_SHOT = 1,
    MEDIUM_SHOT = 2,
    LAY_UP_SHOT = 3,
    COMBINATIONT_SHOT = 4,
    RULES_SHOT = 5,
    DIRTY_SHOT = 6,
    HAND_GOD_SHOT = 7
};

enum defense
{
    CHOICE_DEFENSE = 0,
    PRESSING = 1,
    PERSONAL_DEFENSE = 2,
    ZONE_DEFENSE = 3,
    NONE_DEFENSE = 4,
    RULES_DEFENSE = 5
};

enum playerHints
{
    EXPERT = 1,
    AMATEUR = 2,
    NOOB = 3
};

enum spirit
{
    MAX_SPIRIT = 20,
    MIN_SPIRIT = -20,
    DIRTY_SPIRIT = -10,
    GOD_SPIRIT = 10,
    MORE_POINT = 5,
    MORE_PLAYER = 1,
    MORE_OPPONENT = -1
};

enum posessionBall
{
    PLAYER_BALL = 0,
    OPPONENT_BALL = 1,
    PROCENT_BALL_PLAYER = 40

};

enum situationShow
{
    FIRST_STORY = 1,
    SECOND_STORY = 2,
    THIRD_STORY = 3
};

enum testing
{
    TEST = 1,
    UNTEST = 2
};

namespace menu
{
    int startGame{};
    int jump{};
    int hint{};
    const int RULES_GAME{ 1 };
    const int AUTHOR_GAME{ 3 };
    const int EXIT_GAME{ 4 };
    std::string rules{};
    std::string rulesShot{};
    std::string rulesDefense{};
}

namespace engine
{
    const int ATTACK_TIME{ 24 };
    const int THREE_POINT{ 3 };
    const int TWO_POINT{ 2 };
    const int FREE_THROW_POINT{ 1 };
    const int THREE_POINT_AND_PRESSING{ 70 };
    const int THREE_POINT_AND_PERSONAL_DEFENSE{ 45 };
    const int THREE_POINT_AND_ZONE_DEFENSE{ 70 };
    const int THREE_POINT_AND_NONE_DEFENSE{ 40 };
    const int MEDIUM_SHOT_AND_PRESSING{ 60 };
    const int MEDIUM_SHOT_AND_PERSONAL_DEFENSE{ 60 };
    const int MEDIUM_SHOT_AND_ZONE_DEFENSE{ 35 };
    const int MEDIUM_SHOT_AND_NONE_DEFENSE{ 30 };
    const int LAY_UP_AND_PRESSING{ 50 };
    const int LAY_UP_AND_PERSONAL_DEFENSE{ 50 };
    const int LAY_UP_AND_ZONE_DEFENSE{ 25 };
    const int LAY_UP_AND_NONE_DEFENSE{ 20 };
    const int COMBINATION_AND_PRESSING{ 65 };
    const int COMBINATION_AND_PERSONAL_DEFENSE{ 40 };
    const int COMBINATION_AND_ZONE_DEFENSE{ 65 };
    const int COMBINATION_AND_NONE_DEFENSE{ 35 };
    const int PROCENT_REBOUND{ 80 };
    const int PERIOD_FINISH{ 120 };
    const int PERIOD_START{ 0 };
    int probalityJump{};
    int probalityRebound{};
    int period{};
    int testingChoice{};
}

namespace history
{
    const int PROBALITY_WIN{ 50 }; // 50% шанс победы в событии
    const int ADD_SPIRIT_VICTORY{ 10 };
    const int REM_SPIRIT_FAIL{ -10 };
    const int NONE_RISC_SPIRIT{ -5 };
}

struct Situation
{
    int probalityVictory{};
    int playerChoice{};
    const int ACTION{ 1 };
    const int UNACTION{ 2 };
    std::string scene{};
    std::string riscNone{};
    std::string riscVictory{};
    std::string riscFail{};
};

struct Opponent
{
    int score{};
    int hit{};
    int shot{};
    std::string name{};
};

struct Player
{
    int score{};
    int hit{};
    int shot{};
    int defense{};
    int teamSpirit{};
    int probalityDirtyGame{};
    const int PROCENT_DIRTY_GAME{ 30 };
    std::string name{};
};


void startMenu();
void hints();
void author();
void gameRulesRecord();
void gameRules();
void situationOne(int& teamSpirit);
void situationTwo(int& teamSpirit);
void situationThree(int& teamSpitit);
void choiceDefense(int& defense);
void jumpBall(int& jump);
void probabilityHitPlayer(int& hit, int teamSpirit);
void probabilityHitOpponent(int& hit);
void attackShot(int& shot, int teamSpirit);
bool playerAttack(Player& player, Opponent& opponent);
bool opponentAttack(Player& player, Opponent& opponent);
bool rebound();
void game(int jump, Player& player, Opponent& opponent);
void score(int scorePlayer, int scoreOpponent);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));


    Opponent opponent{};
    Player player{};

    std::cout << "Выберите варинат запуска игры:\n1.Тестовый режим.\n2.Режим пользователя.\n";
    std::cout << "Ваш выбор: ";
    std::cin >> engine::testingChoice;
    switch (engine::testingChoice)
    {
    case TEST:
        testingEnabled = true;
        break;
    case UNTEST:
        testingEnabled = false;
        break;
    }
    system("cls");

    if (testingEnabled)
    {
        std::cout << "РЕЖИМ ТЕСТИРОВЩИКА ВКЛЮЧЕН!\n";
        Sleep(1500);
        system("cls");
    }

    gameRulesRecord();
    startMenu();
    if (menu::startGame == menu::EXIT_GAME)
    {
        return 0;
    }

    hints();

    std::cout << "Нажмите клавишу Enter, для стандартного названия противника или\nВведите название команды противника: ";
    std::cin.ignore();
    std::getline(std::cin, opponent.name);
    if (opponent.name == "")
    {
        opponent.name = "Колледж Оклахомы";
    }

    if (testingEnabled)
    {
        std::cout << "\nТЕСТОВОЕ МЕНЮ:\nВыберите уровень командного духа от -20 до 20: ";
        std::cin >> player.teamSpirit;
        system("cls");
        std::cout << "Выебирте одну одну кат сцену цифрами от 1 до 3.\n";
        std::cout << "Кат сцена номер: ";
        int show;
        std::cin >> show;
        switch (show)
        {
        case FIRST_STORY:
            situationOne(player.teamSpirit);
            break;
        case SECOND_STORY:
            situationTwo(player.teamSpirit);
            break;
        case THIRD_STORY:
            situationThree(player.teamSpirit);
            break;
        default:
            std::cout << "Переход к игре без кат сцен!\n";
            system("cls");
            break;
        }

    }
    
    std::cout << "Вашей стартовой защитой будет...";
    choiceDefense(player.defense);
    player.name = "Дартмутский колледж";
    std::cout << "\n";

    system("cls");

    jumpBall(menu::jump);
    if (menu::jump == PLAYER_BALL)
    {
        std::cout << "Судья подкидывает мяч вверх в центральном круге и...\n";
        std::cout << "Вбрасывание выигрывает команда: " << player.name << ".\n\n";
    }
    else
    {
        std::cout << "Судья подкидывает мяч вверх в центральном круге и...\n";
        std::cout << "Вбрасывание выигрывает команда: " << opponent.name << ".\n\n";
    }

    game(menu::jump, player, opponent);
    std::cout << "\nЗвучит свисток, сейчас команды уйдут на перерыв!\nУслышимся после небольшой паузы!\n\n";
    system("pause");
    system("cls");
    std::cout << "Начинается второй тайм! ПОЕХАЛИ!!!\n\n";
    if (menu::jump == PLAYER_BALL)
    {
        menu::jump = OPPONENT_BALL;
    }
    else
    {
        menu::jump = PLAYER_BALL;
    }
    engine::period = engine::PERIOD_START;
    game(menu::jump, player, opponent);
    std::cout << "Последние секунды матча истекли! Судья дает свисток!\nФинальный счет на табло:\n" << player.name << ' ' << player.score << ' ' << opponent.name << ": " << opponent.score << ".\n";
    if (player.score > opponent.score)
    {
        std::cout << "Поздравляем команду " << player.name << " с победой!";
    }
    else if (player.score < opponent.score)
    {
        std::cout << "Поздравляем команду " << opponent.name << " с победой!";
    }
    else
    {
        std::cout << "Сегодня победитель не выявлен, но в следующий раз победит сильнейший!\n\n";
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}

void startMenu()
{
    std::cout << "Добро пожаловать в игру \"Баскетбол\"\n";
    std::cout << "1. Правила игры.\n";
    std::cout << "2. Начать игру.\n";
    std::cout << "3. Об авторе.\n";
    std::cout << "4. Выйти из игры.\n\n";
    std::cout << "Для продолжения выберете действие: ";
    std::cin >> menu::startGame;
    std::cout << "\n";
    if (menu::startGame == menu::RULES_GAME || menu::startGame == menu::AUTHOR_GAME)

    {
        while (menu::startGame == menu::RULES_GAME || menu::startGame == menu::AUTHOR_GAME)
        {
            if (menu::startGame == menu::RULES_GAME)
            {
                system("cls");
                gameRules();
                std::cout << "1. Правила игры.\n";
                std::cout << "2. Начать игру.\n";
                std::cout << "3. Об авторе.\n";
                std::cout << "4. Выйти из игры.\n\n";
                std::cout << "Для продолжения выберете действие: ";
                std::cin >> menu::startGame;
                std::cout << "\n";
            }
            else if (menu::startGame == menu::AUTHOR_GAME)
            {
                system("cls");
                author();
                std::cout << "1. Правила игры.\n";
                std::cout << "2. Начать игру.\n";
                std::cout << "3. Об авторе.\n";
                std::cout << "4. Выйти из игры.\n\n";
                std::cout << "Для продолжения выберете действие: ";
                std::cin >> menu::startGame;
                std::cout << "\n";
            }
        }
    }
}

void hints()
{
    std::cout << "Выберите режим подсказок:\n1.Опытный(без подсказок).\n2.Любитель(подсказки появляются по нажатию клавиши)\n3.Новичок(подсказки выводятся всегда)\n\n";
    std::cout << "Ваш выбор: ";
    std::cin >> menu::hint;
    while (menu::hint > NOOB || menu::hint < EXPERT)
    {
        std::cout << "Не понимаю тебя!\nВыберите режим подсказок: ";
        std::cin >> menu::hint;
    }
}

void author()
{
    std::cout << "Студия разработки игр Dialas представляет.\nАвтор: Медведенко Егор(ник: mee1b).\nВерсия: 1.0.3.\n\n";
    system("pause");
    system("cls");
}

void gameRulesRecord()
{
    // Объясняет ввод с клавиатуры
    menu::rules =
        "Это баскетбольный клуб Дартмутского колледжа. "
        "Ты будешь капитаном и плеймейкером нашей команды.\n"
        "Игра длится 2 тайма по 4 минуты. Одна атака длится 24 секунды.\n\n";
    menu::rulesShot =
        "Делайте броски следующим образом:\n"
        "1. Дальний (трехочковый) бросок в прыжке;\n2. Средний (двухочковый) бросок в прыжке;\n3. Лэй - апп (два очка);\n4. Комбинация и бросок (два очка);\n\n"
        "На попадание влияет:\n1. Базовый процент попадания.\n2. Защита.\n3. Командный дух.\n\n"
        "Командный дух можно, как поднять(отличной игрой и успешным решением жизненных вопросов команды).\nТак и потерять(плохой игрой или неудачними решениями).\n\n";
    menu::rulesDefense =
        "Обе команды будут использовать одну и ту же защиту.\nВыберите схему следующим образом:\n"
        "1. Прессинг - эффективная защита (шанс всех бросков снижен на 10%);\n"
        "2. Личная опека - отличная защита от средних и ближних бросков (шанс удачного среднего броска и лэй - аппа -10%),\n"
        "но открывается огромный простор для дальних бросков и комбинаций (шанс удачного дальнего броска и комбинаций + 15 %);\n"
        "3. Зонная защита - отличная защита от дальних бросков и комбинаций (шанс удачного дальнего броска и комбинации -10%),\n"
        "но открывается огромный простор для лэй - аппов и средних бросков (шанс удачного лэй - аппа и средних бросков + 15%);\n"
        "4. Нет защиты - команда отдыхает в защите (повышается шанс удачной реализации всех бросков +20%);\n"
        "Чтобы изменить защиту, просто введите 0 в качестве следующего броска.\n\n";
}

void gameRules()
{
    // Объясняет ввод с клавиатуры
    menu::rules =
        "Это баскетбольный клуб Дартмутского колледжа. "
        "Ты будешь капитаном и плеймейкером нашей команды.\n"
        "Игра длится 2 тайма по 4 минуты. Одна атака длится 24 секунды.\n\n";
    std::cout << menu::rules;
    menu::rulesShot =
        "Делайте броски следующим образом:\n"
        "1. Дальний (трехочковый) бросок в прыжке;\n2. Средний (двухочковый) бросок в прыжке;\n3. Лэй - апп (два очка);\n4. Комбинация и бросок (два очка);\n\n"
        "На попадание влияет:\n1. Базовый процент попадания.\n2. Защита.\n3. Командный дух.\n\n"
        "Командный дух можно, как поднять(отличной игрой(когда у тебя больше очков, чем у соперника) и успешным решением жизненных вопросов команды).\n"
        "Так и потерять(плохой игрой(когда у тебя меньше очков, чем у соперника или неудачними решениями).\n\n";
    std::cout << menu::rulesShot;
    menu::rulesDefense =
        "Обе команды будут использовать одну и ту же защиту.\nВыберите схему следующим образом:\n"
        "1. Прессинг - эффективная защита (шанс всех бросков снижен на 10%);\n"
        "2. Личная опека - отличная защита от средних и ближних бросков (шанс удачного среднего броска и лэй - аппа -10%),\n"
        "но открывается огромный простор для дальних бросков и комбинаций (шанс удачного дальнего броска и комбинаций + 15 %);\n"
        "3. Зонная защита - отличная защита от дальних бросков и комбинаций (шанс удачного дальнего броска и комбинации -10%),\n"
        "но открывается огромный простор для лэй - аппов и средних бросков (шанс удачного лэй - аппа и средних бросков + 15%);\n"
        "4. Нет защиты - команда отдыхает в защите (повышается шанс удачной реализации всех бросков +20%);\n"
        "Чтобы изменить защиту, просто введите 0 в качестве следующего броска.\n\n";
    std::cout << menu::rulesDefense;
    system("pause");
    system("cls");
}

void situationOne(int& teamSpirit)
{
    Situation situation{};

    situation.scene =
        "Ты и твой товарищ по команде и закадычный приятель Билли Уортингтон направлялись к автобусной остановке,\n"
        "горячо обсуждая предстоящую завтра игру.\n"
        "Вдруг сздади раздался оклик, вы обернулись и увидели Кэти Гринхаус.\n"
        "При виде девушки Билли разулыбался, он давно мечтал за ней приударить, но всё не мог найти повода подойти,\n"
        "так как при всей своей внешней напористости был довольно застенчивым парнем.\n"
        "— Послушай,— обратилась к тебе Кэти, одарив, впрочем, Билли лёгкой ответной улыбкой,\n"
        "— У вас же завтра игра, верно? — Да,— отозвался ты. — Отлично!,— обрадовалась девушка.\n"
        "— Вы ведь будете не против, если мы вас поддержим?\n"
        "— Поддержка — это здорово! Но кто это мы?\n"
        "— Как это— кто!— Кэти взметнула брови. — Я и моя новая команда. Ну так что, ты согласен?\n"
        "Тут тебе всё стало ясно.\n"
        "Кэти страстно увлекалась черлидингом и мечтала когда - нибудь выиграть чемпионат мира по этому виду спорта,\n"
        "так что не упускала возможности попрактиковаться в выступлениях, и, надо сказать, показывала неплохие результаты.\n"
        "Проблема была только в одном, феноменальной нестабильности их представлений.\n"
        "У Кэти и её девочек получались либо совершенно феерические шоу, заряжающие всех вокруг бешеной энергией и позитивом,\n"
        "либо оглушительные провалы, в результате которых частенько калечились не только сами спортсменки,\n"
        "но и обычные зрители, а пару раз доставалось даже игрокам.\n"
        "После недавнего, не очень удачного,  выступления команда Кэти разбежалась, и ей пришлось собирать новый состав,\n"
        "так что, если ты согласишься, это будет их первым выступлением.\n"
        "Билли незаметно, как ему кажется, толкает тебя локтем, призывая согласиться, но решать тебе.\n\n";
    std::cout << situation.scene;
    system("pause");
    system("cls");

    std::cout << "Как же мне поступить?\n1. Принять предложение Кэти.\n2. Отказаться от предложения Кэти.\n";

    std::cout << "Решай: ";
    std::cin >> situation.playerChoice;
    while (situation.playerChoice > situation.UNACTION || situation.playerChoice < situation.ACTION)
    {
        std::cout << "Не поимаю тебя!\nРешай: ";
        std::cin >> situation.playerChoice;
    }
    
    situation.probalityVictory = rand() % 100 + 1;

    if (situation.playerChoice == situation.ACTION && situation.probalityVictory >= history::PROBALITY_WIN)
    {
        situation.riscVictory =
            "\nУСПЕХ!\n\n"
            "Кэти и её команда начали работать незадолго до начала матча, и судя по этим первым минутам,\n"
            "дальше будет только круче.\n"
            "Девушки показали чудеса грации и слаженности, не забывая при этом не только подбадривать,\n"
            "но и подначивать ребят.\n"
            "Теперь вы просто не имеете права облажаться.\n\n";
        std::cout << situation.riscVictory;
        teamSpirit += history::ADD_SPIRIT_VICTORY;
        if (testingEnabled && teamSpirit > MAX_SPIRIT)
        {
            teamSpirit = MAX_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }
    else if (situation.playerChoice == situation.ACTION && situation.probalityVictory < history::PROBALITY_WIN)
    {
        situation.riscFail =
            "\nНЕУДАЧА!\n\n"
            "Кэти и её команда приступили к работе незадолго до начала матча,\n"
            "и с первых минут всё пошло наперекосяк.\n"
            "Одна из девушек подвернула ногу, и пирамида из спортсменок рассыпалась,\n"
            "к счастью, обошлось без серьёзных травм,\n"
            "но  продолжать выступление подругам запретили.\n"
            "Оставшись без поддержки, члены вашей команды, особенно Уортингтон, повесили носы,\n"
            "так что тебе придётся постараться, чтобы расшевелить их.\n\n";
        std::cout << situation.riscFail;
        teamSpirit += history::REM_SPIRIT_FAIL;
        if (testingEnabled && teamSpirit < MIN_SPIRIT)
        {
            teamSpirit = MIN_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }
    else
    {
        situation.riscNone =
            "Услышав отказ, Кэти холодно попрощалась, пожелала удачи в завтрашней игре и быстрым шагом двинулась прочь.\n"
            "Билли окликнул её, но девушка не оглянулась.\n"
            "Едва она скрылась из виду, Уортингтон набросился на тебя с упрёками.\n"
            "— Ты должен был дать ей шанс!, видишь ведь, для неё это важно?!\n"
            "— Ей или тебе? — ты не смог удержаться от улыбки.\n"
            "— Ей!— взвился парень. — Ну и мне, конечно, тоже, — смущённо закончил он, понимая всю очевидность ситуации.\n"
            "— Я бы рад!, но ты же знаешь везучесть Кэти, а если они не справятся, в проигрыше будут все,\n"
            "— попытался ты обьяснить свою позицию.\n"
            "Хотя, по правде сказать, тебя здорово мучила совесть. \n"
            "Кэти ведь искренне хотела помочь, да и ребятам без поддержки будет несладко,\n"
            "особенно если у противника недостатка в мотивации не будет.\n"
            "— Да всё я понимаю, — хмуро пробормотал Билли. Дальше вы шли молча.\n\n";
        std::cout << situation.riscNone;
        teamSpirit += history::NONE_RISC_SPIRIT;
        if (testingEnabled && teamSpirit < MIN_SPIRIT)
        {
            teamSpirit = MIN_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }

}

void situationTwo(int& teamSpirit)
{
    Situation situation;

    situation.scene = 
        "С уроками на сегодня покончено. ты закрыл крышку ноутбука и откинулся на спинку кресла,\n"
        "надо придумать, чем занять вечер.\n"
        "В кармане завибрировал смарттфон, снова спам, на этот рраз от сервиса знакомств.\n"
        "Ты задумчиво крутил телефон в руке, реклама направила твои мысли на путь, которого ты избегал вот уже три месяца.\n"
        "Алисон, светловолосая смешливая девчонка, частенько присутствовала на выступлениях вашей команды, однако, \n"
        "ваше общение не выходило за рамки дружеского, иногда с намёком на лёгкий флирт,\n"
        "так что девушка вряд-ли догадывалась, что ты пламенно в неё влюблён.\n"
        "Быть может, эта сообщение — знак свыше, и стоит пригласить, наконец, Алисон на свидание?\n"
        "Ты нашёл в контактах  номер, и задумался: а вдруг она откажет, или согласится, а потом что то пойдёт не так?\n";
    std::cout << situation.scene;
    system("pause");
    system("cls");

    std::cout << "Как же мне поступить?\n1. Позвонить Алисон.\n2. Не звонить, вдруг ничего не получится.\n";

    std::cout << "Решай: ";
    std::cin >> situation.playerChoice;
    while (situation.playerChoice > situation.UNACTION || situation.playerChoice < situation.ACTION)
    {
        std::cout << "Не поимаю тебя!\nРешай: ";
        std::cin >> situation.playerChoice;
    }

    situation.probalityVictory = rand() % 100 + 1;

    if (situation.playerChoice == situation.ACTION && situation.probalityVictory >= history::PROBALITY_WIN)
    {
        situation.riscVictory =
            "\nУСПЕХ!\n\n"
            "Bногда стоит доверять знакам!\n"
            "Пиццерия, в которую ты пригласил девушку, конечно, не ресторан,\n"
            "но Алисон выглядела вполне довольной, да и с букетом ты угадал.\n"
            "У вас оказалос сотня общих тем для разговора, ты пригласил её на завтрашнюю игру, она обещала прийти,\n"
            "а когда вы прощались, даже разрешила себя поцеловать.\n"
            "Так что домой ты летел, как на крыльях, думая, что завтра вы должны оставить от соперников только мокрое место!\n";
        std::cout << situation.riscVictory;
        teamSpirit += history::ADD_SPIRIT_VICTORY;
        if (testingEnabled && teamSpirit > MAX_SPIRIT)
        {
            teamSpirit = MAX_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }
    else if (situation.playerChoice == situation.ACTION && situation.probalityVictory < history::PROBALITY_WIN)
    {
        situation.riscFail =
            "\nНЕУДАЧА!\n\n"
            "Вот и верь знакам после такого!\n"
            "Ты с досады швырнул телефон на кровать.\n"
            "Алисон согласилась прогуляться, но ты сразу заметил, что с ней что-то-не так.\n"
            "Обычно живая и весёлая, сегодня она была молчалива.\n"
            "Когда же тебе удалось разговорить девушку, выяснилось, что её отец вынужден был сменить работу,\n"
            "из-за чего им придётся переехать куда-то в Африку, где беда не то, что с интернетом,\n"
            "Алисон сказала,что, возможно, ей удастся приехать на будущий год, но тебе показалось,\n"
            "что она и сама не слишком верит в это.\n"
            "Быть может, тебе стоило признаться в своих чувствах раньше, хотя, что бы это изменило?\n"
            "Ты пригласил девушку на завтрашний матч, но она ответила, что у неё много дел из-за переезда.\n"
            "Нужно было подготовиться, продумать тактику игры, но настроения не было, так что ты решил лечь спать.\n";
        std::cout << situation.riscFail;
        teamSpirit += history::REM_SPIRIT_FAIL;
        if (testingEnabled && teamSpirit < MIN_SPIRIT)
        {
            teamSpirit = MIN_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }
    else
    {
        situation.riscNone =
            "Мысленно обозвав себя трусом, ты  всё же отложил телефон.\n"
            "Ты попытался переключиться на предстоящую завтра игру,\n"
            "но мысли снова и снова возвращались к Алисон.\n"
            "Ты проснулся с головной болью, так как заснуть удалось лишь под утро.\n";
        std::cout << situation.riscNone;
        teamSpirit += history::NONE_RISC_SPIRIT;
        if (testingEnabled && teamSpirit < MIN_SPIRIT)
        {
            teamSpirit = MIN_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }

}

void situationThree(int& teamSpirit)
{
    Situation situation;

    situation.scene =
        "Лежащий на столе смартфон издал короткую трель.\n"
        "Ты решил воспользоваться поводом сделать перерыв и, отложив учебник, взглянул на экран.\n"
        "— Кэп, ты где? Все уже собрались, — гласило сообщение.\n"
        "Ты хлопнул себя по лбу.\n"
        "Договорились ведь, что тренировка сегодня пройдёт на два часа раньше, так как в зале,\n"
        "где вы с командой тренируетесь, должны были проводить какое-то мероприятие.\n"
        "Зал принадлежал отцу одного из ребят, так что платить за аренду было не нужно,\n"
        "что всех чрезвычайно радовало, но сегодня это превратилось в проблему, по крайней мере, для тебя.\n"
        "Дело  в том, что ты самым дурацким образом не успел выполнить задание, которое сдать нужно, вот сюрприз, уже завтра.\n"
        "Теперь тебе придётся выбирать, пойти на тренировку, а потом надеяться,\n"
        "что кто-нибудь из ребят даст списать, либо же остаться дома и основательно подготовиться.\n"
        "Но в этом случае ребята обоснованно обидятся, что повлияет на климат в команде.\n";
    std::cout << situation.scene;
    system("pause");
    system("cls");

    std::cout << "Как же мне поступить?\n1. Поехать на тренировку.\n2. Остаться дома и подготовится.\n";

    std::cout << "Решай: ";
    std::cin >> situation.playerChoice;
    while (situation.playerChoice > situation.UNACTION || situation.playerChoice < situation.ACTION)
    {
        std::cout << "Не поимаю тебя!\nРешай: ";
        std::cin >> situation.playerChoice;
    }

    situation.probalityVictory = rand() % 100 + 1;

    if (situation.playerChoice == situation.ACTION && situation.probalityVictory >= history::PROBALITY_WIN)
    {
        situation.riscVictory =
            "\nУСПЕХ!\n\n"
            "Всё-таки ты везучий!\n"
            "Ребята хоть и прикалывались над твоей забывчивостью, но тренировка прошла на ура,\n"
            "так что команда сыграет слаженно, как машина, даже если парней разбудить посреди ночи.\n"
            "С учёбой тоже всё разрешилось наилучшим образом.\n"
            "Твой приятель Джейкоб не только поделился материалом,\n"
            "но и растолковал парочку непонятных моментов, так что проблем быть не должно.\n";
        std::cout << situation.riscVictory;
        teamSpirit += history::ADD_SPIRIT_VICTORY;
        if (testingEnabled && teamSpirit > MAX_SPIRIT)
        {
            teamSpirit = MAX_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }
    else if (situation.playerChoice == situation.ACTION && situation.probalityVictory < history::PROBALITY_WIN)
    {
        situation.riscFail =
            "\nНЕУДАЧА!\n\n"
            "Не везёт так не везёт!\n"
            "Решив всё же отправиться на тренировку, ты попал в пробку.\n"
            "Время занятий пришлось сократить, и к моменту,\n"
            "когда нужно было освобождать зал, вы не проработали и половины запланированного.\n"
            "Кроме того, ты повздорил с Джейкобом, парнем, который мог бы помочь тебе с уроками,\n"
            "так что теперь придётся выкручиваться самому.\n";
        std::cout << situation.riscFail;
        teamSpirit += history::REM_SPIRIT_FAIL;
        if (testingEnabled && teamSpirit < MIN_SPIRIT)
        {
            teamSpirit = MIN_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }
    else
    {
        situation.riscNone =
            "Ты всё же решил остаться дома и как следует  подготовиться.\n"
            "Ребята повозмущались немного в общем чате, но в целом отнеслись к ситуации  с пониманием.\n"
            "Ты накидал текстом, что именно им нужно отработать к следующей игре,\n"
            "конечно, вживую было бы лучше, ну да ничего, должны справиться.\n";
        std::cout << situation.riscNone;
        teamSpirit += history::NONE_RISC_SPIRIT;
        if (testingEnabled && teamSpirit < MIN_SPIRIT)
        {
            teamSpirit = MIN_SPIRIT;
        }
        std::cout << "\nВаш командный дух равен " << teamSpirit << std::endl;
        system("pause");
        system("cls");
    }

}

void choiceDefense(int& defense)
{
    if (menu::hint == EXPERT)
    {
        std::cin >> defense;
    }
    else if (menu::hint == AMATEUR)
    {
        std::cout << "(Чтобы посмотреть схемы защиты нажмите 5.)";
        std::cin >> defense;
        while (defense == RULES_DEFENSE)
        {
            std::cout << menu::rulesDefense;
            std::cout << "Какой будет наша защита? ";
            std::cin >> defense;
        }
    }
    else if (menu::hint == NOOB)
    {
        std::cout << "\n" << menu::rulesDefense;
        std::cin >> defense;
    }
    while (defense < PRESSING || defense > NONE_DEFENSE)
    {
        std::cout << "На тренировках мы не разбирали эти схемы, капитан!\nДавай сыграем то, что мы уже знаем!\n";
        std::cout << "Какой будет наша защита? ";
        std::cin >> defense;
    }
}

void jumpBall(int& jump)
{
    engine::probalityJump = rand() % 100 + 1;
    if (engine::probalityJump > PROCENT_BALL_PLAYER)
    {
        jump = PLAYER_BALL;
    }
    else
    {
        jump = OPPONENT_BALL;
    }
}

void probabilityHitPlayer(int& hit, int teamSpirit)
{
    hit = (rand() % 100 + 1) + teamSpirit;
}

void probabilityHitOpponent(int& hit)
{
    hit = (rand() % 100) + 1;
}

void attackShot(int& shot, int teamSpirit)
{
    if (menu::hint == EXPERT)
    {
        std::cout << "Капитан! Какой бросок делаем в этой атаке? ";
    }
    else if (menu::hint == AMATEUR)
    {
        std::cout << "Капитан! Какой бросок делаем в этой атаке?(чтобы посмотреть виды бросков нажмите 5): ";
        std::cin >> shot;
        while (shot == RULES_SHOT)
        {
            std::cout << menu::rulesShot;
            std::cout << "Если командных дух равен -10 или меньше:\n6.Грязная игра(три очка, плюс 10 к командному духу).\nЕсли командный дух равен 10 или больше:\n7.Рука бога(три очка, плюс 10 к командному духу).\n\n";
            std::cout << "Капитан! Какой бросок делаем в этой атаке? ";
            std::cin >> shot;
        }
        return;
    }
    else if (menu::hint == NOOB)
    {
        std::cout << menu::rulesShot;
        std::cout << "Капитан! Какой бросок делаем в этой атаке? ";
    }
    std::cin >> shot;
    
    if (shot == DIRTY_SHOT && teamSpirit <= DIRTY_SPIRIT)
    {
        return;
    }
    else if (shot == HAND_GOD_SHOT && teamSpirit >= GOD_SPIRIT)
    {
        return;
    }
    while (shot < THREE_POINT_SHOT || shot > COMBINATIONT_SHOT)
    {
        std::cout << "На тренировках мы не разбирали такие броски, капитан!\nДавай сыграем то, что мы уже знаем!\n";
        std::cout << "Какой бросок делаем в этой атаке? ";
        std::cin >> shot;
    }
}

bool playerAttack(Player& player, Opponent& opponent)
{
    if (player.score - opponent.score >= MORE_PLAYER)
    {
        player.teamSpirit += MORE_POINT;
    }
    else if (player.score - opponent.score <= MORE_OPPONENT)
    {
        player.teamSpirit -= MORE_POINT;
    }

    if (player.teamSpirit >= MAX_SPIRIT)
    {
        player.teamSpirit = MAX_SPIRIT;
    }
    else if (player.teamSpirit <= MIN_SPIRIT)
    {
        player.teamSpirit = MIN_SPIRIT;
    }

    std::cout << "Наш командный дух равен " << player.teamSpirit << std::endl;
    if (player.teamSpirit <= DIRTY_SPIRIT && (menu::hint == AMATEUR || menu::hint == NOOB))
    {
        std::cout << "6. Ваш командный дух падает, открыт прием \"Грязная игра\".\n";
    }
    else if (player.teamSpirit >= GOD_SPIRIT && (menu::hint == AMATEUR || menu::hint == NOOB))
    {
        std::cout << "7. Ваш командный дух на подъёме, открыт прием \"Рука бога\".\n";
    }
    attackShot(player.shot, player.teamSpirit);
    std::cout << "\n";
    while (player.shot == CHOICE_DEFENSE)
    {
        if (player.shot == CHOICE_DEFENSE)
        {
            std::cout << "\nКапитан, какую схему защиты играем? ";
            choiceDefense(player.defense);
            attackShot(player.shot, player.teamSpirit);
        }
    }
    if (player.shot == THREE_POINT_SHOT)
    {
        //Шанс трехочкового 40% - базовый
        std::cout << "Трехочковый бросок!!!\n";
        probabilityHitPlayer(player.hit, player.teamSpirit);
        switch (player.defense)
        {
        case PRESSING:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::THREE_POINT_AND_PRESSING)
            {
                std::cout << "Три очка в корзине!!!\n";
                player.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Личная опека\" - (+15%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::THREE_POINT_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Три очка в корзине!!!\n";
                player.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Зонная защита\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::THREE_POINT_AND_ZONE_DEFENSE)
            {
                std::cout << "Три очка в корзине!!!\n";
                player.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Нет защиты\" - (+20%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::THREE_POINT_AND_NONE_DEFENSE)
            {
                std::cout << "Три очка в корзине!!!\n";
                player.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }

    }
    if (player.shot == MEDIUM_SHOT)
    {
        //Шанс двухочкового 50% - базовый
        std::cout << "Средний бросок!!!\n";
        probabilityHitPlayer(player.hit, player.teamSpirit);
        switch (player.defense)
        {
        case PRESSING:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::MEDIUM_SHOT_AND_PRESSING)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Личная опека\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::MEDIUM_SHOT_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Зонная защита\" - (+15%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::MEDIUM_SHOT_AND_ZONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Нет защиты\" - (+20%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::MEDIUM_SHOT_AND_NONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (player.shot == LAY_UP_SHOT)
    {
        //Шанс лэй - аппа 60% - базовый
        std::cout << "Это же лэй - апп!!!\n";
        probabilityHitPlayer(player.hit, player.teamSpirit);
        switch (player.defense)
        {
        case PRESSING:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::LAY_UP_AND_PRESSING)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Личная опека\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::LAY_UP_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Зонная защита\" - (+15%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::LAY_UP_AND_ZONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Нет защиты\" - (+20%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::LAY_UP_AND_NONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (player.shot == COMBINATIONT_SHOT)
    {
        //Шанс комбинации 55% - базовый
        std::cout << "Смотрите, игроки разыгрывают комбинацию!!!\n";
        probabilityHitPlayer(player.hit, player.teamSpirit);
        switch (player.defense)
        {
        case PRESSING:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::COMBINATION_AND_PRESSING)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"Личная опека\" - (+15%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::COMBINATION_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"Зонная защита\" - (-10%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::COMBINATION_AND_ZONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (testingEnabled)
            {
                std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"ЛНет защиты\" - (+20%)\n3.Командный дух " << player.teamSpirit << "%\n";
            }
            if (player.hit > engine::COMBINATION_AND_NONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                player.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (player.shot == DIRTY_SHOT && player.teamSpirit <= DIRTY_SPIRIT)
    {
        if (testingEnabled)
        {
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\nВероятность попадания 70%\n";
        }
        player.probalityDirtyGame = rand() % 100 + 1;
        if (player.probalityDirtyGame >= player.PROCENT_DIRTY_GAME)
        {
            std::cout << "ЭТО ЖЕ ФОЛ!!!\nНо судья ничего не видит.\nТри очка в корзине!\n\n";
            player.score += engine::THREE_POINT;
            score(player.score, opponent.score);
            player.teamSpirit += history::ADD_SPIRIT_VICTORY;
        }
        else
        {
            std::cout << "ЭТО ЖЕ ФОЛ!!!\nСудья назначает штрафной бросок в кольцо команды " << player.name << '\n';
            std::cout << "Команда " << opponent.name << " реализует штрафной бросок!\n\n";
            opponent.score += engine::FREE_THROW_POINT;
            score(player.score, opponent.score); 
        }
        return true;
    }
    if (player.shot == HAND_GOD_SHOT && player.teamSpirit >= GOD_SPIRIT)
    {
        if (testingEnabled)
        {
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\nВероятность попадания 100%\n";
        }
        std::cout << "КАКАЯ ТРАЕКТОРИЯ ПОЛЕТА!!!\nНе бросок, а заглядение.\nТри очка в корзине!\n\n";
        player.score += engine::THREE_POINT;
        std::cout << "Это был великолепный бросок!\nНо видимо он отнял много сил у игроков, перед следующим броском команде нужно собраться!\n\n";
        score(player.score, opponent.score);
        player.teamSpirit += history::REM_SPIRIT_FAIL;
        return true;
    }
    std::cout << "\n\n";
    return false;
}

bool opponentAttack(Player& player, Opponent& opponent)
{
    opponent.shot = (rand() % 4) + 1;
    std::cout << opponent.name << " в атаке:\n";
    if (opponent.shot == THREE_POINT_SHOT)
    {
        //Шанс трехочкового 40% - базовый
        std::cout << "Трехочковый бросок!!!\n";
        probabilityHitOpponent(opponent.hit);
        switch (player.defense)
        {
        case PRESSING:
            if (opponent.hit > engine::THREE_POINT_AND_PRESSING)
            {
                std::cout << "Три очка в корзине!!!\n";
                opponent.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (opponent.hit > engine::LAY_UP_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Три очка в корзине!!!\n";
                opponent.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (opponent.hit > engine::THREE_POINT_AND_ZONE_DEFENSE)
            {
                std::cout << "Три очка в корзине!!!\n";
                opponent.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (opponent.hit > engine::THREE_POINT_AND_NONE_DEFENSE)
            {
                std::cout << "Три очка в корзине!!!\n";
                opponent.score += engine::THREE_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }

    }
    if (opponent.shot == MEDIUM_SHOT)
    {
        //Шанс двухочкового 50% - базовый
        std::cout << "Средний бросок!!!\n";
        probabilityHitOpponent(opponent.hit);
        switch (player.defense)
        {
        case PRESSING:
            if (opponent.hit > engine::MEDIUM_SHOT_AND_PRESSING)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (opponent.hit > engine::MEDIUM_SHOT_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (opponent.hit > engine::MEDIUM_SHOT_AND_ZONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (opponent.hit > engine::MEDIUM_SHOT_AND_NONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (opponent.shot == LAY_UP_SHOT)
    {
        //Шанс лэй - аппа 60% - базовый
        std::cout << "Это же лэй - апп!!!\n";
        probabilityHitOpponent(opponent.hit);
        switch (player.defense)
        {
        case PRESSING:
            if (opponent.hit > engine::LAY_UP_AND_PRESSING)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (opponent.hit > engine::LAY_UP_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (opponent.hit > engine::LAY_UP_AND_ZONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (opponent.hit > engine::LAY_UP_AND_NONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        }
    }
    if (opponent.shot == COMBINATIONT_SHOT)
    {
        //Шанс комбинации 55% - базовый
        std::cout << "Смотрите, игроки разыгрывают комбинацию!!!\n";
        probabilityHitOpponent(opponent.hit);
        switch (player.defense)
        {
        case PRESSING:
            if (opponent.hit > engine::COMBINATION_AND_PRESSING)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case PERSONAL_DEFENSE:
            if (opponent.hit > engine::COMBINATION_AND_PERSONAL_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case ZONE_DEFENSE:
            if (opponent.hit > engine::COMBINATION_AND_ZONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
                return true;
            }
            else
            {
                std::cout << "Промах! Мяч в воздухе, кто же им завладеет?\n";
                return false;
            }
        case NONE_DEFENSE:
            if (opponent.hit > engine::COMBINATION_AND_NONE_DEFENSE)
            {
                std::cout << "Два очка в корзине!!!\n";
                opponent.score += engine::TWO_POINT;
                score(player.score, opponent.score);
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
    engine::probalityRebound = rand() % 100 + 1;
    if (engine::probalityRebound > engine::PROCENT_REBOUND)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void game(int jump, Player& player, Opponent& opponent)
{
    while (engine::period < engine::PERIOD_FINISH)
    {
        if (jump == PLAYER_BALL)
        {
            if (!playerAttack(player, opponent))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в атаке за командой: " << player.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << opponent.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                }
            }
            else
            {
                engine::period += engine::ATTACK_TIME;
            }
            if (!opponentAttack(player, opponent))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в атаке за командой: " << opponent.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                    opponentAttack(player, opponent);
                    engine::period += engine::ATTACK_TIME;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << player.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                }
            }
            else
            {
                engine::period += engine::ATTACK_TIME;
            }
        }
        else if (jump == OPPONENT_BALL)
        {
            if (!opponentAttack(player, opponent))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в защите за командой: " << opponent.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << player.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                }
            }
            else
            {
                engine::period += engine::ATTACK_TIME;
            }
            if (!playerAttack(player, opponent))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в защите за командой: " << player.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                    playerAttack(player, opponent);
                    engine::period += engine::ATTACK_TIME;
                }
                else
                {
                    std::cout << "\nПодбор в защите за командой: " << opponent.name << "\n\n";
                    engine::period += engine::ATTACK_TIME;
                }
            }
            else
            {
                engine::period += engine::ATTACK_TIME;
            }
        }
    }
}

void score(int scorePlayer, int scoreOpponent)
{
    std::cout << "Счет: " << scorePlayer << ' ' << scoreOpponent << "\n\n";
}