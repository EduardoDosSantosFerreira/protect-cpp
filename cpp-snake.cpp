#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 25;

class Snake {
public:
    Snake();
    void move();
    void grow();
    bool collided();
    bool eaten(int foodX, int foodY);
    void setDirection(char dir);
    char getDirection();
    COORD getHeadPosition();
    vector<COORD> getBody();

private:
    COORD head;
    vector<COORD> body;
    char direction;
};

class Food {
public:
    Food();
    void generatePosition();
    COORD getPosition();

private:
    COORD position;
};

Snake::Snake() {
    head = { WIDTH / 2, HEIGHT / 2 };
    body.push_back({ head.X - 1, head.Y });
    body.push_back({ head.X - 2, head.Y });
    direction = 'r';
}

void Snake::move() {
    for (int i = body.size() - 1; i > 0; --i) {
        body[i] = body[i - 1];
    }
    body[0] = head;

    switch (direction) {
    case 'u':
        --head.Y;
        break;
    case 'd':
        ++head.Y;
        break;
    case 'l':
        --head.X;
        break;
    case 'r':
        ++head.X;
        break;
    }
}

void Snake::grow() {
    body.push_back({ -1, -1 });  // Dummy value, actual position will be updated in the next move
}

bool Snake::collided() {
    if (head.X <= 0 || head.X >= WIDTH - 1 || head.Y <= 0 || head.Y >= HEIGHT - 1) {
        return true;
    }

    for (const auto& bodyPart : body) {
        if (head.X == bodyPart.X && head.Y == bodyPart.Y) {
            return true;
        }
    }

    return false;
}

bool Snake::eaten(int foodX, int foodY) {
    return (head.X == foodX && head.Y == foodY);
}

void Snake::setDirection(char dir) {
    switch (dir) {
    case 'u':
        if (direction != 'd') direction = 'u';
        break;
    case 'd':
        if (direction != 'u') direction = 'd';
        break;
    case 'l':
        if (direction != 'r') direction = 'l';
        break;
    case 'r':
        if (direction != 'l') direction = 'r';
        break;
    }
}

char Snake::getDirection() {
    return direction;
}

COORD Snake::getHeadPosition() {
    return head;
}

vector<COORD> Snake::getBody() {
    return body;
}

Food::Food() {
    generatePosition();
}

void Food::generatePosition() {
    position = { rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1 };
}

COORD Food::getPosition() {
    return position;
}

void drawBoard(Snake& snake, Food& food, int score) {
    COORD headPos = snake.getHeadPosition();
    vector<COORD> body = snake.getBody();
    COORD foodPos = food.getPosition();

    system("cls");

    cout << "SCORE: " << score << "\n\n";

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1) {
                cout << '#';
            }
            else if (i == headPos.Y && j == headPos.X) {
                cout << '0';
            }
            else if (i == foodPos.Y && j == foodPos.X) {
                cout << '@';
            }
            else {
                bool isBodyPart = false;
                for (const auto& bodyPart : body) {
                    if (i == bodyPart.Y && j == bodyPart.X) {
                        cout << 'o';
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart) {
                    cout << ' ';
                }
            }
        }
        cout << '\n';
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Snake snake;
    Food food;

    int score = 0;

    char gameOver = false;

    while (!gameOver && !_kbhit()) {
        drawBoard(snake, food, score);

        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                snake.setDirection('u');
                break;
            case 'a':
                snake.setDirection('l');
                break;
            case 's':
                snake.setDirection('d');
                break;
            case 'd':
                snake.setDirection('r');
                break;
            }
        }

        snake.move();

        if (snake.collided()) {
            gameOver = true;
        }

        if (snake.eaten(food.getPosition().X, food.getPosition().Y)) {
            food.generatePosition();
            snake.grow();
            score += 10;
        }

        Sleep(100);  // Adjust this value to control the snake's speed
    }

    return 0;
}
