#include<iostream>
#include<windows.h>
#include<conio.h>
#include <unistd.h>
using namespace std;

class snakeGame{
    const int width = 30; // Game width
    const int height = 30; // Game height
    int snakeDirX, snakeDirY, fruitX, fruitY, score;
    int tailX[100], tailY[100];
    int nTail=0;
    enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
    eDirection direction;
public: 
    bool gameOver;

    // Initial Game Values
    void Setup();

    // Printing Game 
    void Draw();

    // Taking input from user
    void Input();

    // Logic behind game run
    void Logic();
    };

void snakeGame :: Setup()
{
    gameOver = false;
    direction = STOP;
    snakeDirX = width/2;
    snakeDirY = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void snakeGame :: Draw()
{
    system("cls");
    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            if(j==0 || j==height-1 || i==0 || i==width-1) // printing boundaries
                cout<<"#";
            else if(i==snakeDirY && j==snakeDirX) // printing head
                cout<<"O";
            else if(i==fruitX && j==fruitY) // printing fruit
                cout<<"F";
            else
            {
                // printing tail
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout<<endl;
    }
    cout<<"Score: "<<score<<endl; 
}

void snakeGame :: Input()
{
    if(_kbhit()) // it return true if we press any key otherwise it return false
    {
        int key = _getch(); // Get the actual key code
        switch (key)
        {
            case 72: // Up arrow
                direction = UP;
                break;
            case 80: // Down arrow
                direction = DOWN;
                break;
            case 75: // Left arrow
                direction = LEFT;
                break;
            case 77: // Right arrow
                direction = RIGHT;
                break;
        }
    }
}

void snakeGame :: Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeDirX;
    tailY[0] = snakeDirY;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (direction)
    {
        case LEFT:
            snakeDirX--;
            break;
            
        case RIGHT:
            snakeDirX++;
            break;
            
        case UP:
            snakeDirY--;
            break;
            
        case DOWN:
            snakeDirY++;
            break;
    }
    
    //Game over on touching boundaries
    // if(snakeDirX<=0 || snakeDirX>=width-1 || snakeDirY<=0 || snakeDirY>=height-1)
    //     gameOver = true;
    
    //Snake comes from opposite wall on crossing
    if(snakeDirX<=0) snakeDirX = width-2;
    if(snakeDirX>=width-1) snakeDirX = 0;
    if(snakeDirY<=0) snakeDirY = height-2;
    if(snakeDirY>=height-1) snakeDirY = 0;
    
    if(snakeDirX==fruitY && snakeDirY==fruitX)
    {
        score+=1;
        fruitX = rand() % (width-2)+1;
        fruitY = rand() % (height-1)+1;
        nTail++;
    }
}
    
int main(){
    snakeGame s1;
    s1.Setup();
    while(!s1.gameOver)
    {
        s1.Draw();
        s1.Input();
        s1.Logic();
        sleep(1);
    }
    return 0;
}