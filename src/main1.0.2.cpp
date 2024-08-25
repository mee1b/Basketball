#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <windows.h>

/*  The basketball class - ��� ������������ ����, � ������� �� ���������� �
    ���� �������� � ����������� ������� ������������ ��������
    � ���� ������������ �������� ����������� ��� ������������� ������� ������ ����.
    �� ������ �������� ���� �������, � ����� �������������� ����� */

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

    std::cout << "��� ����� ���� ������������ ��������� � ���� ������������(9).\n������� ������ ���� ����� ��� ���. ����!\n\n";

    int scorePlayer{ 0 }, scoreOpponent{ 0 }, shot, teamSpirit{ 0 };
    int startGame = startMenu();
    if (startGame == 4)
    {
        return 0;
    }
    else if (startGame == 9)
    {
        std::cout << "�������� ����:\n�������� ������� ���������� ���� �� -100 �� 100: ";
        std::cin >> teamSpirit;
        system("cls");
        std::cout << "�������� ���� ���� ��� ����� ������� �� 1 �� 3.\n";
        std::cout << "��� ����� �����: ";
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
            std::cout << "������� � ���� ��� ��� ����!\n";
            system("cls");
            break;
        }

    }
    

    std::cout << "����� ��������� ������� �����...";
    int defense = choiceDefense();
    std::string opponentName, myTeam{ "����������� �������" };
    std::cout << "������� �������� ������� ����������: ";
    std::cin.ignore();
    std::getline(std::cin, opponentName);
    std::cout << "\n";

    system("cls");

    int jump = jumpBall();
    if (jump == 0)
    {
        std::cout << "����� ����������� ��� ����� � ����������� ����� �...\n";
        std::cout << "����������� ���������� �������: " << myTeam << ".\n\n";
    }
    else
    {
        std::cout << "����� ����������� ��� ����� � ����������� ����� �...\n";
        std::cout << "����������� ���������� �������: " << opponentName << ".\n\n";
    }

    game(jump, scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName, myTeam);
    std::cout << "\n������ �������, ������ ������� ����� �� �������!\n��������� ����� ��������� �����!\n\n";
    system("pause");
    system("cls");
    std::cout << "���������� ������ ����! �������!!!\n\n";
    if (jump == 0)
    {
        jump = 1;
    }
    else
    {
        jump = 0;
    }
    game(jump, scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName, myTeam);
    std::cout << "��������� ������� ����� �������! ����� ���� �������!\n��������� ���� �� �����:\n" << myTeam << ' ' << scorePlayer << ' ' << opponentName << ": " << scoreOpponent << ".\n";
    if (scorePlayer > scoreOpponent)
    {
        std::cout << "����������� ������� " << myTeam << " � �������!";
    }
    else if (scorePlayer < scoreOpponent)
    {
        std::cout << "����������� ������� " << opponentName << " � �������!";
    }
    else
    {
        std::cout << "������� ���������� �� �������, �� � ��������� ��� ������� ����������!\n\n";
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}

int startMenu()
{
    int startGame{};
    std::cout << "����� ���������� � ���� \"���������\"\n";
    std::cout << "1. ������� ����.\n";
    std::cout << "2. ������ ����.\n";
    std::cout << "3. �� ������.\n";
    std::cout << "4. ����� �� ����.\n";
    std::cout << "9. ���� ������������.\n\n";
    std::cout << "��� ����������� �������� ��������: ";
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
                std::cout << "1. ������� ����.\n";
                std::cout << "2. ������ ����.\n";
                std::cout << "3. �� ������.\n";
                std::cout << "4. ����� �� ����.\n\n";
                std::cout << "��� ����������� �������� ��������: ";
                std::cin >> startGame;
                std::cout << "\n";
            }
            else if (startGame == 3)
            {
                system("cls");
                author();
                std::cout << "1. ������� ����.\n";
                std::cout << "2. ������ ����.\n";
                std::cout << "3. �� ������.\n";
                std::cout << "4. ����� �� ����.\n\n";
                std::cout << "��� ����������� �������� ��������: ";
                std::cin >> startGame;
                std::cout << "\n";
            }
        }
    }

    return startGame;
}

void author()
{
    std::cout << "������ ���������� ��� Dialas ������������.\n�����: ���������� ����(���: mee1b).\n������: 1.0.2.\n\n";
}

void gameRules()
{
    // ��������� ���� � ����������
    std::cout << "��� ������������� ���� ������������ ��������. ";
    std::cout << "�� ������ ��������� � ������������ ����� �������.\n";
    std::cout << "���� ������ 2 ����� �� 4 ������. ���� ����� ������ 24 �������.\n\n";
    std::cout << "������� ������ ��������� �������:\n";
    std::cout << "1. ������� (�����������) ������ � ������;\n2. ������� (�����������) ������ � ������;\n3. ��� - ��� (��� ����);\n4. ���������� � ������ (��� ����);\n";//����, ��������, ����� ������������
    std::cout << "�� �������� ������:\n1. ������� ������� ��������.\n2. ������.\n3. ��������� ���.\n";
    std::cout << "��������� ��� �����, ��� �������(�������� ����� � �������� �������� ��������� �������� �������).\n��� � ��������(������ ����� ��� ���������� ���������)\n";
    std::cout << "��� ������� ����� ������������ ���� � �� �� ������.\n�������� ����� ��������� �������:\n";
    std::cout << "6. �������� - ����������� ������ (���� ���� ������� ������ �� 10%);\n";
    std::cout << "7. ������ ����� - �������� ������ �� ������� � ������� ������� (���� �������� �������� ������ � ��� - ���� -10%),\n";
    std::cout << "�� ����������� �������� ������� ��� ������� ������� � ���������� (���� �������� �������� ������ � ���������� + 15 %);\n";
    std::cout << "8. ������ ������ - �������� ������ �� ������� ������� � ���������� (���� �������� �������� ������ � ���������� -10%),\n";
    std::cout << "�� ����������� �������� ������� ��� ��� - ����� � ������� ������� (���� �������� ��� - ���� � ������� ������� + 15%);\n";
    std::cout << "9. ��� ������ - ������� �������� � ������ (���������� ���� ������� ���������� ���� ������� +20%);\n";
    std::cout << "����� �������� ������, ������ ������� 0 � �������� ���������� ������.\n\n";
    system("pause");
    system("cls");
}

void situationOne(int& teamSpirit)
{
    std::cout << "�� � ���� ������� �� ������� � ���������� �������� ����� ���������� ������������ � ���������� ���������,\n";
    std::cout << "������ �������� ����������� ������ ����.\n";
    std::cout << "����� ������ �������� �����, �� ���������� � ������� ���� ��������.\n";
    std::cout << "��� ���� ������� ����� �����������, �� ����� ������ �� ��� ����������, �� �� �� ��� ����� ������ �������,\n";
    std::cout << "��� ��� ��� ���� ����� ������� ������������ ��� �������� ����������� ������.\n";
    std::cout << "� ��������,� ���������� � ���� ����, ������, �������, ����� ����� �������� �������,\n";
    std::cout << "� � ��� �� ������ ����, �����? � ��,� ��������� ��. � �������!,� ������������ �������.\n";
    std::cout << "� �� ���� ������ �� ������, ���� �� ��� ���������?\n";
    std::cout << "� ��������� � ��� �������! �� ��� ��� ��?\n";
    std::cout << "� ��� ��� ���!� ���� ��������� �����. � � � ��� ����� �������. �� ��� ���, �� ��������?\n";
    std::cout << "��� ���� �� ����� ����.\n";
    std::cout << "���� �������� ���������� ����������� � ������� ����� - ������ �������� ��������� ���� �� ����� ���� ������,\n";
    std::cout << "��� ��� �� �������� ����������� ���������������� � ������������, �, ���� �������, ���������� �������� ����������.\n";
    std::cout << "�������� ���� ������ � �����, ������������� �������������� �� �������������.\n";
    std::cout << "� ���� � � ������� ���������� ���� ���������� ����������� ���, ���������� ���� ������ ������� �������� � ���������,\n";
    std::cout << "���� ������������� �������, � ���������� ������� ��������� ���������� �� ������ ���� �����������,\n";
    std::cout << "�� � ������� �������, � ���� ��� ����������� ���� �������.\n";
    std::cout << "����� ���������, �� ����� ��������,  ����������� ������� ���� �����������, � �� �������� �������� ����� ������,\n";
    std::cout << "��� ���, ���� �� �����������, ��� ����� �� ������ ������������.\n";
    std::cout << "����� ���������, ��� ��� �������, ������� ���� ������, �������� �����������, �� ������ ����.\n\n";
    system("pause");
    system("cls");

    std::cout << "��� �� ��� ���������?\n1. ������� ����������� ����.\n2. ���������� �� ����������� ����.\n";

    std::cout << "�����: ";
    int choiceSituation;
    std::cin >> choiceSituation;
    while (choiceSituation > 2 || choiceSituation < 1)
    {
        std::cout << "�� ������ ����!\n�����: ";
        std::cin >> choiceSituation;
    }
    
    srand(static_cast<unsigned int>(time(0)));
    int randSituation = rand() % 100 + 1;

    if (choiceSituation == 1 && randSituation >= 50)
    {
        std::cout << "\n�����!\n\n";
        std::cout << "���� � � ������� ������ �������� ��������� �� ������ �����, � ���� �� ���� ������ �������,\n";
        std::cout << "������ ����� ������ �����.\n";
        std::cout << "������� �������� ������ ������ � �����������, �� ������� ��� ���� �� ������ ������������,\n";
        std::cout << "�� � ����������� �����.\n";
        std::cout << "������ �� ������ �� ������ ����� ����������.\n\n";
        teamSpirit += 10;
        system("pause");
        system("cls");
    }
    else if (choiceSituation == 1 && randSituation < 50)
    {
        std::cout << "\n�������!\n\n";
        std::cout << "���� � � ������� ���������� � ������ ��������� �� ������ �����,\n";
        std::cout << "� � ������ ����� �� ����� �����������.\n";
        std::cout << "���� �� ������� ���������� ����, � �������� �� ����������� �����������,\n";
        std::cout << "� �������, �������� ��� ��������� �����,\n";
        std::cout << "��  ���������� ����������� �������� ���������.\n";
        std::cout << "��������� ��� ���������, ����� ����� �������, �������� ����������, �������� ����,\n";
        std::cout << "��� ��� ���� ������� �����������, ����� ����������� ��.\n\n";
        teamSpirit -= 10;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "������� �����, ���� ������� �����������, �������� ����� � ���������� ���� � ������� ����� ��������� �����.\n";
        std::cout << "����� �������� �, �� ������� �� ����������.\n";
        std::cout << "���� ��� �������� �� ����, ���������� ���������� �� ���� � �������.\n";
        std::cout << "� �� ������ ��� ���� �� ����!, ������ ����, ��� �� ��� �����?!\n";
        std::cout << "� �� ��� ����? � �� �� ���� ���������� �� ������.\n";
        std::cout << "� ��!� ������� ������. � �� � ���, �������, ����, � �������� �������� ��, ������� ��� ����������� ��������.\n";
        std::cout << "� � �� ���!, �� �� �� ������ ��������� ����, � ���� ��� �� ���������, � ��������� ����� ���,\n";
        std::cout << "� ��������� �� ��������� ���� �������.\n";
        std::cout << "����, �� ������ �������, ���� ������� ������ �������. \n";
        std::cout << "���� ���� �������� ������ ������, �� � ������� ��� ��������� ����� ��������,\n";
        std::cout << "�������� ���� � ���������� ���������� � ��������� �� �����.\n";
        std::cout << "� �� �� � �������, � ����� ����������� �����. ������ �� ��� �����.\n\n";
        teamSpirit -= 5;
        system("pause");
        system("cls");
    }

}

void situationTwo(int& teamSpirit)
{
    std::cout << "� ������� �� ������� ���������. �� ������ ������ �������� � ��������� �� ������ ������,\n";
    std::cout << "���� ���������, ��� ������ �����.\n";
    std::cout << "� ������� ������������ ���������, ����� ����, �� ���� ���� �� ������� ���������.\n";
    std::cout << "�� ��������� ������ ������� � ����, ������� ��������� ���� ����� �� ����, �������� �� ������� ��� ��� ��� ������.\n";
    std::cout << "������, ������������� ��������� ��������, ��������� �������������� �� ������������ ����� �������, ������, \n";
    std::cout << "���� ������� �� �������� �� ����� ����������, ������ � ������ �� ����� �����,\n";
    std::cout << "��� ��� ������� ����-�� ������������, ��� �� �������� � �� ������.\n";
    std::cout << "���� �����, ��� ��������� � ���� �����, � ����� ����������, �������, ������ �� ��������?\n";
    std::cout << "�� ����� � ���������  �����, � ���������: � ����� ��� �������, ��� ����������, � ����� ��� �� ����� �� ���?\n";
    system("pause");
    system("cls");

    std::cout << "��� �� ��� ���������?\n1. ��������� ������.\n2. �� �������, ����� ������ �� ���������.\n";

    std::cout << "�����: ";
    int choiceSituation;
    std::cin >> choiceSituation;
    while (choiceSituation > 2 || choiceSituation < 1)
    {
        std::cout << "�� ������ ����!\n�����: ";
        std::cin >> choiceSituation;
    }

    srand(static_cast<unsigned int>(time(0)));
    int randSituation = rand() % 100 + 1;

    if (choiceSituation == 1 && randSituation >= 50)
    {
        std::cout << "\n�����!\n\n";
        std::cout << "B����� ����� �������� ������!\n";
        std::cout << "��������, � ������� �� ��������� �������, �������, �� ��������,\n";
        std::cout << "�� ������ ��������� ������ ���������, �� � � ������� �� ������.\n";
        std::cout << "� ��� �������� ����� ����� ��� ��� ���������, �� ��������� � �� ���������� ����, ��� ������� ������,\n";
        std::cout << "� ����� �� ���������, ���� ��������� ���� ����������.\n";
        std::cout << "��� ��� ����� �� �����, ��� �� �������, �����, ��� ������ �� ������ �������� �� ���������� ������ ������ �����!\n";
        teamSpirit += 10;
        system("pause");
        system("cls");
    }
    else if (choiceSituation == 1 && randSituation < 50)
    {
        std::cout << "\n�������!\n\n";
        std::cout << "��� � ���� ������ ����� ������!\n";
        std::cout << "�� � ������ ������� ������� �� �������.\n";
        std::cout << "������ ����������� �����������, �� �� ����� �������, ��� � ��� ���-��-�� ���.\n";
        std::cout << "������ ����� � ������, ������� ��� ���� ���������.\n";
        std::cout << "����� �� ���� ������� ����������� �������, ����������, ��� � ���� �������� ��� ������� ������,\n";
        std::cout << "��-�� ���� �� ������� ��������� ����-�� � ������, ��� ���� �� ��, ��� � ����������,\n";
        std::cout << "������ �������,���, ��������, �� ������� �������� �� ������� ���, �� ���� ����������,\n";
        std::cout << "��� ��� � ���� �� ������� ����� � ���.\n";
        std::cout << "���� �����, ���� ������ ���������� � ����� �������� ������, ����, ��� �� ��� ��������?\n";
        std::cout << "�� ��������� ������� �� ���������� ����, �� ��� ��������, ��� � �� ����� ��� ��-�� ��������.\n";
        std::cout << "����� ���� �������������, ��������� ������� ����, �� ���������� �� ����, ��� ��� �� ����� ���� �����.\n";
        teamSpirit -= 10;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "�������� ������� ���� ������, ��  �� �� ������� �������.\n";
        std::cout << "�� ��������� ������������� �� ����������� ������ ����,\n";
        std::cout << "�� ����� ����� � ����� ������������ � ������.\n";
        std::cout << "�� ��������� � �������� �����, ��� ��� ������� ������� ���� ��� ����.\n";
        teamSpirit -= 5;
        system("pause");
        system("cls");
    }

}

void situationThree(int& teamSpirit)
{
    std::cout << "������� �� ����� �������� ����� �������� �����.\n";
    std::cout << "�� ����� ��������������� ������� ������� ������� �, ������� �������, �������� �� �����.\n";
    std::cout << "� ���, �� ���? ��� ��� ���������, � ������� ���������.\n";
    std::cout << "�� ������� ���� �� ���.\n";
    std::cout << "������������ ����, ��� ���������� ������� ������ �� ��� ���� ������, ��� ��� � ����,\n";
    std::cout << "��� �� � �������� ������������, ������ ���� ��������� �����-�� �����������.\n";
    std::cout << "��� ����������� ���� ������ �� �����, ��� ��� ������� �� ������ ���� �� �����,\n";
    std::cout << "��� ���� ����������� ��������, �� ������� ��� ������������ � ��������, �� ������� ����, ��� ����.\n";
    std::cout << "����  � ���, ��� �� ����� �������� ������� �� ����� ��������� �������, ������� ����� �����, ��� �������, ��� ������.\n";
    std::cout << "������ ���� ������� ��������, ����� �� ����������, � ����� ���������,\n";
    std::cout << "��� ���-������ �� ����� ���� �������, ���� �� �������� ���� � ������������ �������������.\n";
    std::cout << "�� � ���� ������ ������ ����������� ��������, ��� �������� �� ������ � �������.\n";
    system("pause");
    system("cls");

    std::cout << "��� �� ��� ���������?\n1. ������� �� ����������.\n2. �������� ���� � ������������.\n";

    std::cout << "�����: ";
    int choiceSituation;
    std::cin >> choiceSituation;
    while (choiceSituation > 2 || choiceSituation < 1)
    {
        std::cout << "�� ������ ����!\n�����: ";
        std::cin >> choiceSituation;
    }

    srand(static_cast<unsigned int>(time(0)));
    int randSituation = rand() % 100 + 1;

    if (choiceSituation == 1 && randSituation >= 50)
    {
        std::cout << "\n�����!\n\n";
        std::cout << "��-���� �� �������!\n";
        std::cout << "������ ���� � ������������� ��� ����� �������������, �� ���������� ������ �� ���,\n";
        std::cout << "��� ��� ������� ������� ��������, ��� ������, ���� ���� ������ ��������� ������� ����.\n";
        std::cout << "� ������ ���� �� ����������� ��������� �������.\n";
        std::cout << "���� �������� ������� �� ������ ��������� ����������,\n";
        std::cout << "�� � ����������� ������� ���������� ��������, ��� ��� ������� ���� �� ������.\n";
        teamSpirit += 10;
        system("pause");
        system("cls");
    }
    else if (choiceSituation == 1 && randSituation < 50)
    {
        std::cout << "\n�������!\n\n";
        std::cout << "�� ���� ��� �� ����!\n";
        std::cout << "����� �� �� ����������� �� ����������, �� ����� � ������.\n";
        std::cout << "����� ������� �������� ���������, � � �������,\n";
        std::cout << "����� ����� ���� ����������� ���, �� �� ����������� � �������� ����������������.\n";
        std::cout << "����� ����, �� ��������� � ���������, ������, ������� ��� �� ������ ���� � �������,\n";
        std::cout << "��� ��� ������ ������� ������������� ������.\n";
        teamSpirit -= 10;
        system("pause");
        system("cls");
    }
    else
    {
        std::cout << "�� �� �� ����� �������� ���� � ��� �������  �������������.\n";
        std::cout << "������ ������������� ������� � ����� ����, �� � ����� ��������� � ��������  � ����������.\n";
        std::cout << "�� ������� �������, ��� ������ �� ����� ���������� � ��������� ����,\n";
        std::cout << "�������, ������ ���� �� �����, �� �� ������, ������ ����������.\n";
        teamSpirit -= 5;
        system("pause");
        system("cls");
    }

}

int choiceDefense()
{
    int defense{};
    std::cout << "(����� ���������� ����� ������ ������� 1.)";
    std::cin >> defense;
    while (defense == 1)
    {
        std::cout << "6. �������� - ����������� ������ (���� ���� ������� ������ �� 10%);\n";
        std::cout << "7. ������ ����� - �������� ������ �� ������� � ������� ������� (���� �������� �������� ������ � ��� - ���� -10%),\n";
        std::cout << "�� ����������� �������� ������� ��� ������� ������� � ���������� (���� �������� �������� ������ � ���������� + 15 %);\n";
        std::cout << "8. ������ ������ - �������� ������ �� ������� ������� � ���������� (���� �������� �������� ������ � ���������� -10%),\n";
        std::cout << "�� ����������� �������� ������� ��� ��� - ����� � ������� ������� (���� �������� ��� - ���� � ������� ������� + 15%);\n";
        std::cout << "9. ��� ������ - ������� �������� � ������ (���������� ���� ������� ���������� ���� ������� +20%);\n";
        std::cout << "����� ����� ���� ������? ";
        std::cin >> defense;
    }
    while (defense < 6 || defense > 9)
    {
        std::cout << "�� ����������� �� �� ��������� ��� �����, �������!\n����� ������� ��, ��� �� ��� �����!\n";
        std::cout << "����� ����� ���� ������? ";
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
    std::cout << "�������! ����� ������ ������ � ���� �����?(����� ���������� ���� ������� ������� 5): ";
    std::cin >> shot;
    while (shot == 5)
    {
        std::cout << "1. ������� (�����������) ������ � ������;\n2. ������� (�����������) ������ � ������;\n3. ��� - ��� (��� ����);\n4. ���������� � ������ (��� ����)\n";
        std::cout << "���� ��������� ��� ����� -10 ��� ������:\n11.������� ����(��� ����, ���� 10 � ���������� ����).\n���� ��������� ��� ����� 10 ��� ������:\n11.���� ����(��� ����, ���� 10 � ���������� ����).\n\n";
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
        std::cout << "�� ����������� �� �� ��������� ����� ������, �������!\n����� ������� ��, ��� �� ��� �����!\n";
        std::cout << "����� ������ ������ � ���� �����? ";
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

    std::cout << "��� ��������� ��� ����� " << teamSpirit << std::endl;
    if (teamSpirit <= -10)
    {
        std::cout << "11. ��� ��������� ��� ������, ������ ����� \"������� ����\".\n";
    }
    else if (teamSpirit >= 10)
    {
        std::cout << "11. ��� ��������� ��� �� �������, ������ ����� \"���� ����\".\n";
    }
    int hit{ 0 };
    attackShot(shot, teamSpirit);
    std::cout << "\n";
    while (shot == 0)
    {
        if (shot == 0)
        {
            std::cout << "\n�������, ����� ����� ������ ������? ";
            defense = choiceDefense();
            attackShot(shot,teamSpirit);
        }
    }
    if (shot == 1)
    {
        //���� ������������ 40% - �������
        std::cout << "����������� ������!!!\n";
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "�������� ���������:\n1.������� ���� - 40%.\n2.������ \"��������\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            std::cout << "�������� ���������:\n1.������� ���� - 40%.\n2.������ \"������ �����\" - (+15%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 45)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            std::cout << "�������� ���������:\n1.������� ���� - 40%.\n2.������ \"������ ������\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            std::cout << "�������� ���������:\n1.������� ���� - 40%.\n2.������ \"��� ������\" - (+20%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        }

    }
    if (shot == 2)
    {
        //���� ������������ 50% - �������
        std::cout << "������� ������!!!\n";
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "�������� ���������:\n1.������� ���� - 50%.\n2.������ \"��������\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            std::cout << "�������� ���������:\n1.������� ���� - 50%.\n2.������ \"������ �����\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            std::cout << "�������� ���������:\n1.������� ���� - 50%.\n2.������ \"������ ������\" - (+15%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            std::cout << "�������� ���������:\n1.������� ���� - 50%.\n2.������ \"��� ������\" - (+20%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 30)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        }
    }
    if (shot == 3)
    {
        //���� ��� - ���� 60% - �������
        std::cout << "��� �� ��� - ���!!!\n";
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "�������� ���������:\n1.������� ���� - 60%.\n2.������ \"��������\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            std::cout << "�������� ���������:\n1.������� ���� - 60%.\n2.������ \"������ �����\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            std::cout << "�������� ���������:\n1.������� ���� - 60%.\n2.������ \"������ ������\" - (+15%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 25)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            std::cout << "�������� ���������:\n1.������� ���� - 60%.\n2.������ \"��� ������\" - (+20%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 20)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        }
    }
    if (shot == 4)
    {
        //���� ���������� 55% - �������
        std::cout << "��������, ������ ����������� ����������!!!\n";
        hit = probabilityHitPlayer(teamSpirit);
        switch (defense)
        {
        case 6:
            std::cout << "�������� ���������:\n1.������� ���� - 55%.\n2.������ \"��������\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            std::cout << "�������� ���������:\n1.������� ���� - 55%.\n2.������ \"������ �����\" - (+15%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            std::cout << "�������� ���������:\n1.������� ���� - 55%.\n2.������ \"������ ������\" - (-10%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            std::cout << "�������� ���������:\n1.������� ���� - 55%.\n2.������ \"���� ������\" - (+20%)\n3.��������� ��� " << teamSpirit << "%\n";
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        }
    }
    if (shot == 11 && teamSpirit <= -10)
    {
        std::cout << "�������� ���������:\n����������� ��������� 100%\n";
        std::cout << "��� �� ���!!!\n�� ����� ������ �� �����.\n��� ���� � �������!\n\n";
        scorePlayer += 3;
        score(scorePlayer, scoreOpponent);
        teamSpirit += 10;
        return true;
    }
    if (shot == 11 && teamSpirit >= 10)
    {
        std::cout << "�������� ���������:\n����������� ��������� 100%\n";
        std::cout << "����� ���������� ������!!!\n�� ������, � ����������.\n��� ���� � �������!\n\n";
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
    std::cout << opponentName << " � �����:\n";
    if (shot == 1)
    {
        //���� ������������ 40% - �������
        std::cout << "����������� ������!!!\n";
        hit = probabilityHitOpponent();
        switch (defense)
        {
        case 6:
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            if (hit > 45)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        }

    }
    if (shot == 2)
    {
        //���� ������������ 50% - �������
        std::cout << "������� ������!!!\n";
        hit = probabilityHitOpponent();
        switch (defense)
        {
        case 6:
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            if (hit > 30)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        }
    }
    if (shot == 3)
    {
        //���� ��� - ���� 60% - �������
        std::cout << "��� �� ��� - ���!!!\n";
        hit = probabilityHitOpponent();
        switch (defense)
        {
        case 6:
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            if (hit > 25)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            if (hit > 20)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        }
    }
    if (shot == 4)
    {
        //���� ���������� 55% - �������
        std::cout << "��������, ������ ����������� ����������!!!\n";
        hit = probabilityHitOpponent();
        switch (defense)
        {
        case 6:
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 7:
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 8:
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
                return false;
            }
        case 9:
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n";
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
                    std::cout << "\n������ � ����� �� ��������: " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "\n������ � ������ �� ��������: " << opponentName << "\n\n";
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
                    std::cout << "\n������ � ����� �� ��������: " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                    opponentAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit, opponentName);
                    period += ATTACK_TIME;
                }
                else
                {
                    std::cout << "\n������ � ������ �� ��������: " << myTeam << "\n\n";
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
                    std::cout << "\n������ � ������ �� ��������: " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "\n������ � ������ �� ��������: " << myTeam << "\n\n";
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
                    std::cout << "\n������ � ������ �� ��������: " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                    playerAttack(scorePlayer, scoreOpponent, shot, defense, teamSpirit);
                    period += ATTACK_TIME;
                }
                else
                {
                    std::cout << "\n������ � ������ �� ��������: " << opponentName << "\n\n";
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
    std::cout << "����: " << scorePlayer << ' ' << scoreOpponent << "\n\n";
}