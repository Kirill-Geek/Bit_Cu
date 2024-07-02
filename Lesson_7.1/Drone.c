#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#define MAX_X 15
#define MAX_Y 15

#define MAX_SNAKE_LENGTH 15

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DOWN_2
} Direction;

typedef struct tail_t
{
    int x;
    int y;
} tail_t;

typedef struct snake_t
{
    int x;
    int y;
    struct tail_t *tail;
    size_t tsize;
    Direction direction;
} snake_t;

typedef struct food_t
{
    int x;
    int y;
    int isEaten;
} food_t;

food_t initFood()
{
    food_t food;
    food.x = rand() % MAX_X;
    food.y = rand() % MAX_Y;
    food.isEaten = 0;
    return food;
}

struct snake_t initSnake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * MAX_SNAKE_LENGTH);
    for (int i = 0; i < tsize; ++i)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    snake.direction = LEFT;
    return snake;
}

void printSnake(struct snake_t snake, food_t food)
{
    char matrix[MAX_X + 5][MAX_Y];
    for (int i = 0; i < MAX_X + 5; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            if (i == 15 && j == 0)
            {
                for (j = 0; j < 15; ++j)
                {
                    matrix[i][j] = '-';
                }
                i = 16;
                j = 0;
            }
            matrix[i][j] = ' ';
        }
    }

    matrix[food.x][food.y] = '$';

    matrix[snake.x][snake.y] = '@';
    for (int i = 0; i < snake.tsize; ++i)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
    }
    for (int i = 0; i < MAX_X + 5; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}
snake_t emptiness(snake_t *snake)
{
    if (snake->direction == LEFT || snake->direction == RIGHT)
    {
        snake->direction = DOWN_2;
        return *snake;
    }
    if (snake->direction == UP || snake->direction == DOWN)
    {
        snake->direction = DOWN_2;
        return *snake;
    }
};
snake_t move_2(snake_t snake)
{
    if (snake.x > MAX_X)
    {
        snake.tsize--;
    }
};

snake_t move(snake_t snake, food_t *food)
{
    for (int i = snake.tsize; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    switch (snake.direction)
    {
    case UP:
    {
        snake.x = snake.x - 1;
        if (snake.x < 0)
        {
            snake.x = MAX_X - 1;
        }
        break;
    }
    case DOWN:
    {
        snake.x = snake.x + 1;
        if (snake.x == MAX_X)
        {
            snake.x = 0;
        }
        break;
    }
    case LEFT:
    {
        snake.y = snake.y - 1;
        if (snake.y < 0)
        {
            snake.y = MAX_Y - 1;
        }
        break;
    }
    case RIGHT:
    {
        snake.y = snake.y + 1;
        if (snake.y == MAX_Y)
        {
            snake.y = 0;
        }
        break;
    }
    case DOWN_2:
    {
        snake.x = snake.x + 1;
        if (snake.x == MAX_X + 5)
        {
            snake.x = 0;
        }
        break;
    }
    }
    if (snake.x == food->x && snake.y == food->y)
    {
        food->isEaten = 1;
        snake.tsize++;
    }

    if (snake.tsize != 0)
    {
        emptiness(&snake);
    }
    return snake;
}

void input(snake_t *snake) // добавлено ручное управление
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            snake->direction = UP;
            break;
        case 's':
            snake->direction = DOWN;
            break;
        case 'a':
            snake->direction = LEFT;
            break;
        case 'd':
            snake->direction = RIGHT;
            break;
        }
    }
}

void generateSnakeDirection(snake_t *snake, food_t food)
{
    if ((snake->direction == LEFT || snake->direction == RIGHT) && snake->x == food.x)
    {
        return;
    }
    if ((snake->direction == LEFT || snake->direction == RIGHT) && snake->x != food.x)
    {
        if (snake->y == food.y)
        {
            snake->direction = UP;
        }
        return;
    }
    if ((snake->direction == UP || snake->direction == DOWN) && snake->y == food.y)
    {
        return;
    }
    if ((snake->direction == UP || snake->direction == DOWN) && snake->y != food.y)
    {
        if (food.x == snake->x)
        {
            snake->direction = LEFT;
        }
        return;
    }
}

int main()
{
    struct snake_t snake = initSnake(10, 5, 0);

    food_t food = initFood();
    printSnake(snake, food);
    while (1)
    {
        input(&snake);

        generateSnakeDirection(&snake, food);
        snake = move(snake, &food);

        if (food.isEaten)
        {
            food = initFood();
        }
        sleep(1);
        system("cls");
        printSnake(snake, food);
        if (snake.tsize > 0)
        {
            if (snake.x > MAX_X)
            {
                snake.tsize = 0;
            }
        }
    }
    return 0;
}