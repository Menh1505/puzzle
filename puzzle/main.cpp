#include <iostream>
#include <windows.h>
#include <time.h>
#include <queue>

using namespace std;

void clearScreen()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x - 1,y - 1 };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

char map[3][3];
int posX, posY;

void playerEnter(char map[3][3], int& posX, int& posY)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> map[i][j];
            if (map[i][j] == '0')
            {
                map[i][j] = ' ';
                posX = j;
                posY = i;
            }
        }
    }
}

void autoEnter(char map[3][3], int& posX, int& posY) 
{
    srand(time(0));
    vector<int> check;

    check.push_back(1 + rand() % 9);
    while (check.size() < 9)
    {
        bool push = 1;
        int tmp = 1 + rand() % 9;
        for (int i = 0; i < check.size(); ++i)
        {
            if (check[i] == tmp)
            {
                push = 0;
                break;
            }
        }
        if (push) check.push_back(tmp);
    }
    for (int i = 0; i < check.size(); ++i)
    {
        cout << check[i] << " ";
    }
    for (int i = 0; i < check.size(); ++i)
    {
        if (check[i] == 9)
        {
            map[i % 3][i / 3] = ' ';
            posY = i % 3;
            posX = i / 3;
        }
        else map[i % 3][i / 3] = (char)(check[i] + '0');
    }
}

void autoRun(int& posX, int& posY)
{
    
}

void launch() //start
{
    SetConsoleOutputCP(65001);
nhap:
    system("cls");
    cout << "Choose how to Enter map" << endl;
    cout << "1. Player Enter" << endl;
    cout << "2. Auto Enter" << endl;
    short n;
    cin >> n;

    switch (n)
    {
    case 1:
        playerEnter(map, posX, posY);
        break;
    case 2:
        autoEnter(map, posX, posY);
        break;
    default:
        cout << "Choose 1 or 2 please";
        goto nhap;
        break;
    }

}

void run()
{
    system("cls");
    while (true)
    {
        clearScreen();
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                cout << map[i][j] << "  ";
            }
            cout << "\n\n";
        }
        cout << "\n\nPress Enter to auto solve";
        if (GetAsyncKeyState(VK_UP))
        {
            if (posY < 2)
            {
                map[posY][posX] = map[posY + 1][posX];
                map[posY + 1][posX] = ' ';
                posY++;
            }
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            if (posY > 0)
            {
                map[posY][posX] = map[posY - 1][posX];
                map[posY - 1][posX] = ' ';
                posY--;
            }
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (posX < 2)
            {
                map[posY][posX] = map[posY][posX + 1];
                map[posY][posX + 1] = ' ';
                posX++;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (posX > 0)
            {
                map[posY][posX] = map[posY][posX - 1];
                map[posY][posX - 1] = ' ';
                posX--;
            }
        }
        Sleep(200);
    }
}

int main()
{
    SetConsoleOutputCP(65001);

    launch();
    run();
    
    return 0;
}