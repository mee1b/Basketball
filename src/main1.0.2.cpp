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
void situationOne(int& teamSpirit);
void situationTwo(int& teamSpirit);
void situationThree(int& teamSpitit);
int choiceDefense();
int jumpBall();
int probabilityHitPlayer(int teamSpirit);
int probabilityHitOpponent();
void attackShot(int& shot, int teamSpirit);
bool playerAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, int& teamSpirit);
bool opponentAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, int& teamSpirit, std::string opponentName);
bool rebound();
void game(int jump, int& scorePlayer, int& scoreOpponent, int& shot, int& defense, int& teamSpirit, std::string opponentName, std::string myTeam);
void score(int scorePlayer, int scoreOpponent);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "ДЛЯ ТЕСТА ВСЕХ ВОЗМОЖНОСТЕЙ ПЕРЕЙДИТЕ В МЕНЮ ТЕСТИРОВЩИКА(9).\nОБЫЧНОЕ НАЧАЛО ИГРЫ БУДЕТ БЕЗ КАТ. СЦЕН!\n\n";

    int scorePlayer{ 0 }, scoreOpponent{ 0 }, shot, teamSpirit{ 0 };
    int startGame = startMenu();
    if (startGame == 4)
    {
        return 0;
    }
    else if (startGame == 9)
    {
        std::cout << "ТЕСТОВОЕ МЕНЮ:\nВыберите уровень командного духа от -100 до 100: ";
        std::cin >> teamSpirit;
        system("cls");
        std::cout << "Выебирте одну одну кат сцену цифрами от 1 до 3.\n";
        std::cout << "Кат сцена номер: ";
        int show;
        std::cin >> show;
        switch (show)
        {
        case 1:
            situationOne(teamSpirit);
            break;
        case 2:
            situationTwo(teamSpirit);
            break;
        case 3:
            situationThree(teamSpirit);
            break;
        default:
            std::cout << "Переход к игре без кат сцен!\n";
            system("cls");
            break;
        }

    }
    

    std::cout << "Вашей стартовой защитой будет...";
    int defense = choiceDefense();
    std::string opponentName, myTeam{ "Дартмутский колледж" };
    std::cout << "Введите название команды противника: ";
    std::cin.ignore();
    std::getline(std::cin, opponentName);
    std::cout << "\n";

    system("cls");

    int jump = jumpBall();
    if (jump == 0)
    {
        std::cout << "Судья подкидывает мяч вверх в центральном круге и...\n";
        std::cout << "Вбрасывание выигрывает команда: " << myTeam << ".\n\n";
    }
    else
    {
        std::cout << "Судья подкидывает мяч вверх в центральном круге и...\n";
        std::cout << "Вбрасывание выигрывает команда: " << opponentName << ".\n\n";
    }

    game(jump, scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName, myTeam);
    std::cout << "\nЗвучит свисток, сейчас команды уйдут на перерыв!\nУслышимся после небольшой паузы!\n\n";
    system("pause");
    system("cls");
    std::cout << "Начинается второй тайм! ПОЕХАЛИ!!!\n\n";
    if (jump == 0)
    {
        jump = 1;
    }
    else
    {
        jump = 0;
    }
    game(jump, scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName, myTeam);
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
    system("pause");
    return 0;
}

int startMenu()
{
    int startGame{};
    std::cout << "Добро пожаловать в игру \"Баскетбол\"\n";
    std::cout << "1. Правила игры.\n";
    std::cout << "2. Начать игру.\n";
    std::cout << "3. Об авторе.\n";
    std::cout << "4. Выйти из игры.\n";
    std::cout << "9. Меню тестировщика.\n\n";
    std::cout << "Для продолжения выберете действие: ";
    std::cin >> startGame;
    std::cout << "\n";
    if (startGame == 1 || startGame == 3)

    {
        while (startGame == 1 || startGame == 3)
        {
            if (startGame == 1)
            {
                system("cls");
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
                system("cls");
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
    std::cout << "Студия разработки игр Dialas представляет.\nАвтор: Медведенко Егор(ник: mee1b).\nВерсия: 1.0.2.\n\n";
}

void gameRules()
{
    // Объясняет ввод с клавиатуры
    std::cout << "Это баскетбольный клуб Дартмутского колледжа. ";
    std::cout << "Ты будешь капитаном и плеймейкером нашей команды.\n";
    std::cout << "Игра длится 2 тайма по 4 минуты. Одна атака длится 24 секунды.\n\n";
    std::cout << "Делайте броски следующим образом:\n";
    std::cout << "1. Дальний (трехочковый) бросок в прыжке;\n2. Средний (двухочковый) бросок в прыжке;\n3. Лэй - апп (два очка);\n4. Комбинация и бросок (два очка);\n";//очки, возможно, будут переработаны
    std::cout << "На поадание влияет:\n1. Базовый процент попдания.\n2. Защита.\n3. Командный дух.\n";
    std::cout << "Командный дух можно, как поднять(отличной игрой и успешным решением жизненных вопросов команды).\nТак и потерять(плохой игрой или неудачними решениями)\n";
    std::cout << "Обе команды будут использовать одну и ту же защиту.\nВыберите схему следующим образом:\n";
    std::cout << "6. Прессинг - эффективная защита (шанс всех бросков снижен на 10%);\n";
    std::cout << "7. Личная опека - отличная защита от средних и ближних бросков (шанс удачного среднего броска и лэй - аппа -10%),\n";
    std::cout << "но открывается огромный простор для дальних бросков и комбинаций (шанс удачного дальнего броска и комбинаций + 15 %);\n";
    std::cout << "8. Зонная защита - отличная защита от дальних бросков и комбинаций (шанс удачного дальнего броска и комбинации -10%),\n";
    std::cout << "но открывается огромный простор для лэй - аппов и средних бросков (шанс удачного лэй - аппа и средних бросков + 15%);\n";
    std::cout << "9. Нет защиты - команда отдыхает в защите (повышается шанс удачной реализации всех бросков +20%);\n";
    std::cout << "Чтобы изменить защиту, просто введите 0 в качестве следующего броска.\n\n";
    system("pause");
    system("cls");
}

void situationOne(int& teamSpirit)
{
    std::cout << "Ты и твой товарищ по команде и закадычный приятель Билли Уортингтон направлялись к автобусной остановке,\n";
    std::cout << "горячо обсуждая предстоящую завтра игру.\n";
    std::cout << "Вдруг сздади раздался оклик, вы обернулись и увидели Кэти Гринхаус.\n";
    std::cout << "При виде девушки Билли разулыбался, он давно мечтал за ней приударить, но всё не мог найти повода подойти,\n";
    std::cout << "так как при всей своей внешней напористости был довольно застенчивым парнем.\n";
    std::cout << "— Послушай,— обратилась к тебе Кэти, одарив, впрочем, Билли лёгкой ответной улыбкой,\n";
    std::cout << "— У вас же завтра игра, верно? — Да,— отозвался ты. — Отлично!,— обрадовалась девушка.\n";
    std::cout << "— Вы ведь будете не против, если мы вас поддержим?\n";
    std::cout << "— Поддержка — это здорово! Но кто это мы?\n";
    std::cout << "— Как это— кто!— Кэти взметнула брови. — Я и моя новая команда. Ну так что, ты согласен?\n";
    std::cout << "Тут тебе всё стало ясно.\n";
    std::cout << "Кэти страстно увлекалась черлидингом и мечтала когда - нибудь выиграть чемпионат мира по этому виду спорта,\n";
    std::cout << "так что не упускала возможности попрактиковаться в выступлениях, и, надо сказать, показывала неплохие результаты.\n";
    std::cout << "Проблема была только в одном, феноменальной нестабильности их представлений.\n";
    std::cout << "У Кэти и её девочек получались либо совершенно феерические шоу, заряжающие всех вокруг бешеной энергией и позитивом,\n";
    std::cout << "либо оглушительные провалы, в результате которых частенько калечились не только сами спортсменки,\n";
    std::cout << "но и обычные зрители, а пару раз доставалось даже игрокам.\n";
    std::cout << "После недавнего, не очень удачного,  выступления команда Кэти разбежалась, и ей пришлось собирать новый состав,\n";
    std::cout << "так что, если ты согласишься, это будет их первым выступлением.\n";
    std::cout << "Билли незаметно, как ему кажется, толкает тебя локтем, призывая согласиться, но решать тебе.\n\n";
    system("pause");
    system("cls");

    std::cout << "Как же мне поступить?\n1. Принять предложение Кэти.\n2. Отказаться от предложения Кэти.\n";

    std::cout << "Решай: ";
    int choiceSituation;
    std::cin >> choiceSituation;
    while (choiceSituation > 2 || choiceSituation < 1)
    {
        std::cout << "Не поимаю тебя!\nРешай: ";
        std::cin >> choiceSituation;
    }
    
    srand(static_cast<unsigned int>(time(0)));
    int randSituation = rand() % 100 + 1;

    if (choiceSituation == 1 && randSituation >= 50)
    {
        std::cout << "\nУСПЕХ!\n\n";
        std::cout << "Кэти и её команда начали работать незадолго до начала матча, и судя по этим первым минутам,\n";
        std::cout << "дальше будет только круче.\n";
        std::cout << "Девушки показали чудеса грации и слаженности, не забывая при этом не только подбадривать,\n";
        std::cout << "но и подначивать ребят.\n";
        std::cout << "Теперь вы просто не имеете права облажаться.\n\n";
        teamSpirit += 10;
        system("pause");
        system("cls");
    }
    else if (choiceSituation == 1 && randSituation < 50)
    {
        std::cout << "\nНЕУДАЧА!\n\n";
        std::cout << "Кэти и её команда приступили к работе незадолго до начала матча,\n";
        std::cout << "и с первых минут всё пошло наперекосяк.\n";
        std::cout << "Одна из девушек подвернула ногу, и пирамида из спортсменок рассыпалась,\n";
        std::cout << "к счастью, обошлось без серьёзных травм,\n";
        std::cout << "но  продолжать выступление подругам запретили.\n";
        std::cout << "Оставшись без поддержки, члены вашей команды, особенно Уортингтон, повесили носы,\n";
        std::cout << "так что тебе придётся постараться, чтобы расшевелить их.\n\n";
        teamSpirit -= 10;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "Услышав отказ, Кэти холодно попрощалась, пожелала удачи в завтрашней игре и быстрым шагом двинулась прочь.\n";
        std::cout << "Билли окликнул её, но девушка не оглянулась.\n";
        std::cout << "Едва она скрылась из виду, Уортингтон набросился на тебя с упрёками.\n";
        std::cout << "— Ты должен был дать ей шанс!, видишь ведь, для неё это важно?!\n";
        std::cout << "— Ей или тебе? — ты не смог удержаться от улыбки.\n";
        std::cout << "— Ей!— взвился парень. — Ну и мне, конечно, тоже, — смущённо закончил он, понимая всю очевидность ситуации.\n";
        std::cout << "— Я бы рад!, но ты же знаешь везучесть Кэти, а если они не справятся, в проигрыше будут все,\n";
        std::cout << "— попытался ты обьяснить свою позицию.\n";
        std::cout << "Хотя, по правде сказать, тебя здорово мучила совесть. \n";
        std::cout << "Кэти ведь искренне хотела помочь, да и ребятам без поддержки будет несладко,\n";
        std::cout << "особенно если у противника недостатка в мотивации не будет.\n";
        std::cout << "— Да всё я понимаю, — хмуро пробормотал Билли. Дальше вы шли молча.\n\n";
        teamSpirit -= 5;
        system("pause");
        system("cls");
    }

}

void situationTwo(int& teamSpirit)
{
    std::cout << "С уроками на сегодня покончено. ты закрыл крышку ноутбука и откинулся на спинку кресла,\n";
    std::cout << "надо придумать, чем занять вечер.\n";
    std::cout << "В кармане завибрировал смарттфон, снова спам, на этот рраз от сервиса знакомств.\n";
    std::cout << "Ты задумчиво крутил телефон в руке, реклама направила твои мысли на путь, которого ты избегал вот уже три месяца.\n";
    std::cout << "Алисон, светловолосая смешливая девчонка, частенько присутствовала на выступлениях вашей команды, однако, \n";
    std::cout << "ваше общение не выходило за рамки дружеского, иногда с намёком на лёгкий флирт,\n";
    std::cout << "так что девушка вряд-ли догадывалась, что ты пламенно в неё влюблён.\n";
    std::cout << "Быть может, эта сообщение — знак свыше, и стоит пригласить, наконец, Алисон на свидание?\n";
    std::cout << "Ты нашёл в контактах  номер, и задумался: а вдруг она откажет, или согласится, а потом что то пойдёт не так?\n";
    system("pause");
    system("cls");

    std::cout << "Как же мне поступить?\n1. Позвонить Алисон.\n2. Не звонить, вдруг ничего не получится.\n";

    std::cout << "Решай: ";
    int choiceSituation;
    std::cin >> choiceSituation;
    while (choiceSituation > 2 || choiceSituation < 1)
    {
        std::cout << "Не поимаю тебя!\nРешай: ";
        std::cin >> choiceSituation;
    }

    srand(static_cast<unsigned int>(time(0)));
    int randSituation = rand() % 100 + 1;

    if (choiceSituation == 1 && randSituation >= 50)
    {
        std::cout << "\nУСПЕХ!\n\n";
        std::cout << "Bногда стоит доверять знакам!\n";
        std::cout << "Пиццерия, в которую ты пригласил девушку, конечно, не ресторан,\n";
        std::cout << "но Алисон выглядела вполне довольной, да и с букетом ты угадал.\n";
        std::cout << "У вас оказалос сотня общих тем для разговора, ты пригласил её на завтрашнюю игру, она обещала прийти,\n";
        std::cout << "а когда вы прощались, даже разрешила себя поцеловать.\n";
        std::cout << "Так что домой ты летел, как на крыльях, думая, что завтра вы должны оставить от соперников только мокрое место!\n";
        teamSpirit += 10;
        system("pause");
        system("cls");
    }
    else if (choiceSituation == 1 && randSituation < 50)
    {
        std::cout << "\nНЕУДАЧА!\n\n";
        std::cout << "Вот и верь знакам после такого!\n";
        std::cout << "Ты с досады швырнул телефон на кровать.\n";
        std::cout << "Алисон согласилась прогуляться, но ты сразу заметил, что с ней что-то-не так.\n";
        std::cout << "Обычно живая и весёлая, сегодня она была молчалива.\n";
        std::cout << "Когда же тебе удалось разговорить девушку, выяснилось, что её отец вынужден был сменить работу,\n";
        std::cout << "из-за чего им придётся переехать куда-то в Африку, где беда не то, что с интернетом,\n";
        std::cout << "Алисон сказала,что, возможно, ей удастся приехать на будущий год, но тебе показалось,\n";
        std::cout << "что она и сама не слишком верит в это.\n";
        std::cout << "Быть может, тебе стоило признаться в своих чувствах раньше, хотя, что бы это изменило?\n";
        std::cout << "Ты пригласил девушку на завтрашний матч, но она ответила, что у неё много дел из-за переезда.\n";
        std::cout << "Нужно было подготовиться, продумать тактику игры, но настроения не было, так что ты решил лечь спать.\n";
        teamSpirit -= 10;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "Мысленно обозвав себя трусом, ты  всё же отложил телефон.\n";
        std::cout << "Ты попытался переключиться на предстоящую завтра игру,\n";
        std::cout << "но мысли снова и снова возвращались к Алисон.\n";
        std::cout << "Ты проснулся с головной болью, так как заснуть удалось лишь под утро.\n";
        teamSpirit -= 5;
        system("pause");
        system("cls");
    }

}

void situationThree(int& teamSpirit)
{
    std::cout << "Лежащий на столе смартфон издал короткую трель.\n";
    std::cout << "Ты решил воспользоваться поводом сделать перерыв и, отложив учебник, взглянул на экран.\n";
    std::cout << "— Кэп, ты где? Все уже собрались, — гласило сообщение.\n";
    std::cout << "Ты хлопнул себя по лбу.\n";
    std::cout << "Договорились ведь, что тренировка сегодня пройдёт на два часа раньше, так как в зале,\n";
    std::cout << "где вы с командой тренируетесь, должны были проводить какое-то мероприятие.\n";
    std::cout << "Зал принадлежал отцу одного из ребят, так что платить за аренду было не нужно,\n";
    std::cout << "что всех чрезвычайно радовало, но сегодня это превратилось в проблему, по крайней мере, для тебя.\n";
    std::cout << "Дело  в том, что ты самым дурацким образом не успел выполнить задание, которое сдать нужно, вот сюрприз, уже завтра.\n";
    std::cout << "Теперь тебе придётся выбирать, пойти на тренировку, а потом надеяться,\n";
    std::cout << "что кто-нибудь из ребят даст списать, либо же остаться дома и основательно подготовиться.\n";
    std::cout << "Но в этом случае ребята обоснованно обидятся, что повлияет на климат в команде.\n";
    system("pause");
    system("cls");

    std::cout << "Как же мне поступить?\n1. Поехать на тренировку.\n2. Остаться дома и подготовится.\n";

    std::cout << "Решай: ";
    int choiceSituation;
    std::cin >> choiceSituation;
    while (choiceSituation > 2 || choiceSituation < 1)
    {
        std::cout << "Не поимаю тебя!\nРешай: ";
        std::cin >> choiceSituation;
    }

    srand(static_cast<unsigned int>(time(0)));
    int randSituation = rand() % 100 + 1;

    if (choiceSituation == 1 && randSituation >= 50)
    {
        std::cout << "\nУСПЕХ!\n\n";
        std::cout << "Всё-таки ты везучий!\n";
        std::cout << "Ребята хоть и прикалывались над твоей забывчивостью, но тренировка прошла на ура,\n";
        std::cout << "так что команда сыграет слаженно, как машина, даже если парней разбудить посреди ночи.\n";
        std::cout << "С учёбой тоже всё разрешилось наилучшим образом.\n";
        std::cout << "Твой приятель Джейкоб не только поделился материалом,\n";
        std::cout << "но и растолковал парочку непонятных моментов, так что проблем быть не должно.\n";
        teamSpirit += 10;
        system("pause");
        system("cls");
    }
    else if (choiceSituation == 1 && randSituation < 50)
    {
        std::cout << "\nНЕУДАЧА!\n\n";
        std::cout << "Не везёт так не везёт!\n";
        std::cout << "Решив всё же отправиться на тренировку, ты попал в пробку.\n";
        std::cout << "Время занятий пришлось сократить, и к моменту,\n";
        std::cout << "когда нужно было освобождать зал, вы не проработали и половины запланированного.\n";
        std::cout << "Кроме того, ты повздорил с Джейкобом, парнем, который мог бы помочь тебе с уроками,\n";
        std::cout << "так что теперь придётся выкручиваться самому.\n";
        teamSpirit -= 10;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "Ты всё же решил остаться дома и как следует  подготовиться.\n";
        std::cout << "Ребята повозмущались немного в общем чате, но в целом отнеслись к ситуации  с пониманием.\n";
        std::cout << "Ты накидал текстом, что именно им нужно отработать к следующей игре,\n";
        std::cout << "конечно, вживую было бы лучше, ну да ничего, должны справиться.\n";
        teamSpirit -= 5;
        system("pause");
        system("cls");
    }

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

int probabilityHitPlayer(int teamSpirit)
{
    srand(static_cast<unsigned int>(time(0)));
    int hit = (rand() % 100) + 1;
    if (hit + teamSpirit >= 100)
    {
        hit = 100;
    }
    else
    {
        hit += teamSpirit;
    }

    return hit;
}

int probabilityHitOpponent()
{
    int hit = (rand() % 100) + 1;

    return hit;
}

void attackShot(int& shot, int teamSpirit)
{
    std::cout << "Капитан! Какой бросок делаем в этой атаке?(чтобы посмотреть виды бросков нажмите 5): ";
    std::cin >> shot;
    while (shot == 5)
    {
        std::cout << "1. Дальний (трехочковый) бросок в прыжке;\n2. Средний (двухочковый) бросок в прыжке;\n3. Лэй - апп (два очка);\n4. Комбинация и бросок (два очка)\n";
        std::cout << "Если командных дух равен -10 или меньше:\n11.Грязная игра(три очка, плюс 10 к командному духу).\nЕсли командный дух равен 10 или больше:\n11.Рука бога(три очка, плюс 10 к командному духу).\n\n";
        attackShot(shot, teamSpirit);
    }
    if (shot == 11 && teamSpirit <= (-10))
    {
        return;
    }
    else if (shot == 11 && teamSpirit >= 10)
    {
        return;
    }
    while (shot < 0 || shot > 5)
    {
        std::cout << "На тренировках мы не разбирали такие броски, капитан!\nДавай сыграем то, что мы уже знаем!\n";
        std::cout << "Какой бросок делаем в этой атаке? ";
        std::cin >> shot;
    }
}

bool playerAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, int& teamSpirit)
{
    if (scorePlayer - scoreOpponent >= 1)
    {
        teamSpirit += 5;
    }
    else if (scorePlayer - scoreOpponent <= -1)
    {
        teamSpirit -= 5;
    }

    if (teamSpirit >= 100)
    {
        teamSpirit = 100;
    }
    else if (teamSpirit <= -100)
    {
        teamSpirit = -100;
    }

    std::cout << "Наш командный дух равен " << teamSpirit << std::endl;
    if (teamSpirit <= -10)
    {
        std::cout << "11. Ваш командный дух падает, открыт прием \"Грязная игра\".\n";
    }
    else if (teamSpirit >= 10)
    {
        std::cout << "11. Ваш командный дух на подъёме, открыт прием \"Рука бога\".\n";
    }
    int hit{ 0 };
    attackShot(shot, teamSpirit);
    std::cout << "\n";
    while (shot == 0)
    {
        if (shot == 0)
        {
            std::cout << "\nКапитан, какую схему защиты играем? ";
            defense = choiceDefense();
            attackShot(shot,teamSpirit);
        }
    }
    if (shot == 1)
    {
        //Шанс трехочкового 40% - базовый
        std::cout << "Трехочковый бросок!!!\n";
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Личная опека\" - (+15%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Зонная защита\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 40%.\n2.Защита \"Нет защиты\" - (+20%)\n3.Командный дух " << teamSpirit << "%\n";
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
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Личная опека\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Зонная защита\" - (+15%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 50%.\n2.Защита \"Нет защиты\" - (+20%)\n3.Командный дух " << teamSpirit << "%\n";
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
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Личная опека\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Зонная защита\" - (+15%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 60%.\n2.Защита \"Нет защиты\" - (+20%)\n3.Командный дух " << teamSpirit << "%\n";
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
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"Прессинг\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"Личная опека\" - (+15%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"Зонная защита\" - (-10%)\n3.Командный дух " << teamSpirit << "%\n";
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
            std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\n1.Базовый шанс - 55%.\n2.Защита \"ЛНет защиты\" - (+20%)\n3.Командный дух " << teamSpirit << "%\n";
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
    if (shot == 11 && teamSpirit <= -10)
    {
        std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\nВероятность попадания 100%\n";
        std::cout << "ЭТО ЖЕ ФОЛ!!!\nНо судья ничего не видит.\nТри очка в корзине!\n\n";
        scorePlayer += 3;
        score(scorePlayer, scoreOpponent);
        teamSpirit += 10;
        return true;
    }
    if (shot == 11 && teamSpirit >= 10)
    {
        std::cout << "ТЕСТОВОЕ СООБЩЕНИЕ:\nВероятность попадания 100%\n";
        std::cout << "КАКАЯ ТРАЕКТОРИЯ ПОЛЕТА!!!\nНе бросок, а заглядение.\nТри очка в корзине!\n\n";
        scorePlayer += 3;
        score(scorePlayer, scoreOpponent);
        teamSpirit += 10;
        return true;
    }
    std::cout << "\n\n";
    return false;
}

bool opponentAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, int& teamSpirit, std::string opponentName)
{
    int hit{ 0 };
    srand(static_cast<unsigned int>(time(0)));
    shot = (rand() % 4) + 1;
    std::cout << opponentName << " в атаке:\n";
    if (shot == 1)
    {
        //Шанс трехочкового 40% - базовый
        std::cout << "Трехочковый бросок!!!\n";
        hit = probabilityHitOpponent();
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
        hit = probabilityHitOpponent();
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
        hit = probabilityHitOpponent();
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
        hit = probabilityHitOpponent();
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
    if ((rand() % 100 + 1) > 80)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void game(int jump, int& scorePlayer, int& scoreOpponent, int& shot, int& defense, int& teamSpirit, std::string opponentName, std::string myTeam)
{
    int period{ 0 };
    while (period < 120)
    {
        if (jump == 0)
        {
            if (!playerAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit))
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
            if (!opponentAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в атаке за командой: " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                    opponentAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName);
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
            if (!opponentAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName))
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
            if (!playerAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit))
            {
                if (rebound())
                {
                    std::cout << "\nПодбор в защите за командой: " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                    playerAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit);
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