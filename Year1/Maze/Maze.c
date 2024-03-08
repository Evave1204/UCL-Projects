#include "graphics.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int waitTime = 150;
int maze[100][100] = {};
int visit[100][100];
int x = 0;
int y = 1;
int size = 27;
int size2 = 100;
int square_size = 10;
int direction_x[4] = {1, 0, -1, 0};
int direction_y[4] = {0, -1, 0, 1};
bool t = true;



void Initialise(int size1)
{
    int x_index;
    int y_index;
    int i, j;
    x_index = x;
    y_index = y;
    for (int y = 0; y < size; y ++)
    {
        for (int x = 0; x < size; x ++)
        {
            if (x != 0 && y != 0 && x != size - 1 && y != size - 1)
            {
                if (x % 2 == 1 && y % 2 == 1)
                {   
                maze[y][x] = 1;
                }
            }
        
        
        }
    }
    for (i = 0; i < size2; i ++)
    {
        for (j = 0; j < size2; j ++)
        {
            if (i >= size || j >= size)
            {
                maze[i][j] = -1;
            }
        }
    }
}


int check_neighbour(int x, int y)
{
    if ((y >= 3 && maze[y - 2][x] == 1) || ((y < size - 3) && maze[y + 2][x] == 1) || (x >= 3 && maze[y][x - 2] == 1) || ((x < size -3) && maze[y][x + 2] == 1))
    {
        return 1;
    }
    return 0;
}


void create_maze(int x_index, int y_index) //create a maze randomly
{
    int k, x1, y1, flag = 0;
    x1 = x_index;
    y1 = y_index;
    while (1)
    {
        flag = 0;
        flag = check_neighbour(x_index, y_index);
        if (flag == 0)
        {
            return;
        }
        else
        {
            maze[y_index][x_index] = 5;
            x1 = x_index;
            y1 = y_index;
            while(1) // randomly select a wall in the neighbour and break it
            {
                k = rand() % 4;
                if (k == 0 && y_index >= 3 && maze[y_index - 2][x_index] == 1) // up
                {
                    y_index -= 2;
                }
                else if (k == 1 && y_index < size - 3 && maze[y_index + 2][x_index] == 1) // down
                {
                    y_index += 2;
                }
                else if (k == 2 && x_index >= 3 && maze[y_index][x_index - 2] == 1) // left
                {
                    x_index -= 2;
                }
                else if (k == 3 && x_index < size - 3 && maze[y_index][x_index + 2] == 1) // right
                {
                    x_index += 2;
                }
                else
                {
                    continue;
                }
                maze[(y1 + y_index) / 2][(x1 + x_index) / 2] = 5;
                maze[y_index][x_index] = 5;
                create_maze(x_index, y_index);
                break;
            }

        }
    }
}



void change_maze() // let 5 becomes 1
{
    int i, j;
    for (i = 0; i < size ; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (maze[i][j] == 5)
            {
                maze[i][j] = 1;
            }
        }
    }
}



// Set the background contents, which is then always displayed and
// not modified.
void drawBackground()
{
    int row = 0;
    int column = 0;
    int i, j;
    
    background(); //Must  draw on the background layer.

    for (row = 0; row < size; row++)
    {
        for (column = 0; column < size; column++)
        {
            setColour(black);
            drawRect(square_size * column, square_size * row, square_size, square_size);
            if (maze[row][column] == 0)
            {
                fillRect(square_size * column, square_size * row, square_size, square_size);
            }
            if (row == size - 2 && column == size - 1)
            {
                maze[row][column] = 1;
                setColour(gray);
                fillRect(square_size * column, square_size * row, square_size, square_size);   
            }            
        }
    }
    maze[1][0] = 1;

}


void update(int tx, int ty, int k)
{
    int x1[3] = {};
    int y1[3] = {};
    clear();
    if (k == 0) // go right
    {
        x1[0] = (square_size * tx); 
        x1[1] = (square_size * tx);
        x1[2] = (square_size * (tx + 1));
        y1[0] = (square_size * ty);
        y1[1] = (square_size * (ty + 1));
        y1[2] = (square_size * ty) + (square_size / 2);
    }
    else if (k == 1) // go down
    {
        x1[0] = (square_size * tx);
        x1[1] = (square_size * (tx + 1));
        x1[2] = (square_size * tx) + (square_size / 2);
        y1[0] = (square_size * (ty + 1));
        y1[1] = (square_size * (ty + 1));
        y1[2] = (square_size * ty);
        
    }
    else if (k == 2) // go left
    {
        x1[0] = (square_size * (tx + 1));
        x1[1] = (square_size * tx);
        x1[2] = (square_size * (tx + 1));
        y1[0] = (square_size * ty);
        y1[1] = (square_size * ty) + (square_size / 2);
        y1[2] = (square_size * (ty + 1));
    }
    else // k = 3, go up
    {
        x1[0] = (square_size * tx);
        x1[1] = (square_size * (tx + 1));
        x1[2] = (square_size * tx) + (square_size / 2);
        y1[0] = (square_size * ty);
        y1[1] = (square_size * ty);
        y1[2] = (square_size * (ty + 1));
    }
    fillPolygon(3, x1, y1);
}



void move(int tx, int ty, int k)
{
    foreground();
    setColour(green);
    update(tx, ty, k);
    sleep(waitTime);

}




void dfs(int x, int y)
{
    int aim_x = size - 1;
    int aim_y = size - 2;
    if (x == aim_x && y == aim_y)
    {
        t = false;
        return;
    }
    else
    {
        for (int k = 0; k <= 3 && t; k++)
        {
            int tx, ty, tx1, ty1;
            tx = x + direction_x[k];
            ty = y + direction_y[k];
            if (maze[ty][tx] == 1 && visit[ty][tx] == 0)
            {
                move(tx,ty,k);
                visit[ty][tx] = 1;
                dfs(tx, ty);
                visit[ty][tx] = 2;
                if (t == false)
                {
                    break;
                }
                move(tx, ty, (k + 2) % 4); // when come back, go in the inverse direction
            }
        }
        return;
    }

        
}



int main(void)
{
    srand((unsigned)time(NULL));
    setWindowSize(1000, 1000);
    Initialise(size);
    create_maze(1,1);
    change_maze();
    drawBackground();
    //visit[y][x] = 1;
    dfs(y,x);
    return 0;
}