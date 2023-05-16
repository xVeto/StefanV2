#include <bits/stdc++.h>
using namespace std;

int numAddingMoves=50;
char c;

class Snake 
{ 
    public:
        vector <pair <int,int>> body;
        pair <int,int> headPos = body[body.size()-1];
        int size=0;
        int movesLeft=50;

        void move(int x, int y)
        {
            body.push_back({x,y});
            headPos = body[body.size()-1];
            movesLeft--;
        }

        pair <int,int> getHeadPos()
        {
            return headPos;
        }

        vector <pair <int,int>> getBody()
        {
            return body;
        }
};

class Food
{ 
    public:
        int x;
        int y;

        int getX() 
        {
            return x;
        }

        int getY() 
        {
            return y;
        }
};

class Board
{ 
    private:
        class Food food;
        class Snake snake;

        void genFood()
        {
            int x = rand() % width;
            int y = rand() % height;
            if (board[x][y] == 0)
            {
                food.x = x;
                food.y = y;
                board[x][y]=1;
            }
            else
            {
                while (board[x][y] != 0)
                {
                    x = rand() % width;
                    y = rand() % height;
                }
                food.x = x;
                food.y = y;
                board[x][y]=1;
            }
        }

    public:
        int width;
        int height;
        int board[101][101];
        // 0-puste; 1-jedzenie; 2-ogon snake'a;

        void stopGame()
        {
            cout << snake.size-1 << " " << snake.body.size();
            exit(0);
        }

        void prepare()
        {
            cin >> width;
            cin >> height;
            int x = rand() % width;
            int y = rand() % height;
            snake.headPos = {x,y};
            board[x][y]=2;
            genFood();
        }

        void move(int x, int y)
        {
            if (x >= width || x < 0 || y >= height || y < 0) 
            {
                stopGame();
                return;
            }
            else if (snake.movesLeft <= 0) 
            {
                stopGame();
                return;
            }
            else if (board[x][y] == 2)
            {
                stopGame();
                return;
            }
            else if (board[x][y] == 1)
            {
                snake.size++;
                snake.movesLeft += numAddingMoves;
            }
            board[x][y]=2;
            snake.move(x,y);
            if (snake.body.size() > 1) board[snake.body[snake.size-2].first][snake.body[snake.size-2].second] = 0;
            genFood();
        }

        pair <int,int> getHeadPos()
        {
            return snake.headPos;
        }

        void display()
        {
            for (int i=0;i<height;i++)
            {
                for (int j=0;j<width;j++)
                {
                    cout << board[i][j];
                }
                cout << endl;
            }
        }

        void output()
        {
            // do dokończenia (wypisać odpowednie wejście dla sieci neuronowej - reycasty);
        }
};

int main()
{
    srand(time(NULL));

    class Board board;
    board.prepare();
    
    while (true)
    {
        board.display();
        cin >> c;
        pair <int,int> headP = board.getHeadPos();
        if (c == 'w')
        {
            board.move(headP.first, headP.second+1);
        }
        else if (c == 's')
        {
            board.move(headP.first, headP.second-1);
        }
        else if (c == 'a')
        {
            board.move(headP.first-1, headP.second);
        }
        else if (c == 'd')
        {
            board.move(headP.first+1, headP.second);
        }
    }

    return 0;
}