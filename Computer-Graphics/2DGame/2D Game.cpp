#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const int screenWidth = 900;
const int screenHeight = 700;
const int planeWidth = 80;
const int planeHeight = 80;
const float planeSpeed = 5.0f;
const float bulletSpeed = 8.0f;
const int enemyWidth = 40;
const int enemyHeight = 40;
bool gameOver = false;

struct Bullet
{
    float x, y;
    bool isActive;
};

struct Enemy
{
    float x, y;
    bool isActive;
};

std::vector<Bullet> bullets;
std::vector<Enemy> enemies;

float planeX = (screenWidth - planeWidth) / 2.0f;
float planeY = 50.0f;
bool isMovingLeft = false;
bool isMovingRight = false;
int score = 0;

GLuint planeTexture;
GLuint enemyTexture;
GLuint backgroundTexture; // Added for the background

void drawBullet(float x, float y, float width, float height)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Set bullet color to white
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y + height / 2.0f);
    glVertex2f(x - width / 2.0f, y + height / 2.0f);
    glEnd();
}

void loadTextures()
{
    planeTexture = SOIL_load_OGL_texture("spaceship.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (planeTexture == 0)
    {
        std::cerr << "Error loading plane texture: " << SOIL_last_result() << std::endl;
        exit(1);
    }

    enemyTexture = SOIL_load_OGL_texture("enemy_spaceship.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (enemyTexture == 0)
    {
        std::cerr << "Error loading enemy spaceship texture: " << SOIL_last_result() << std::endl;
        exit(1);
    }

    // Load the background texture
    backgroundTexture = SOIL_load_OGL_texture("spacebackground.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (backgroundTexture == 0)
    {
        std::cerr << "Error loading background texture: " << SOIL_last_result() << std::endl;
        exit(1);
    }
}

void drawBackground()
{
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(screenWidth, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(screenWidth, screenHeight);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0, screenHeight);
    glEnd();
    glDisable(GL_BLEND);
}

void drawEnemy(float x, float y)
{
    glBindTexture(GL_TEXTURE_2D, enemyTexture); // Load the enemy spaceship texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x - enemyWidth / 2.0f, y - enemyHeight / 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + enemyWidth / 2.0f, y - enemyHeight / 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + enemyWidth / 2.0f, y + enemyHeight / 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x - enemyWidth / 2.0f, y + enemyHeight / 2.0f);
    glEnd();
}

void drawCharacter()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw the background first
    drawBackground();
    glPushMatrix();
    glTranslatef(planeX, planeY, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, planeTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-planeWidth / 2.0f, -planeHeight / 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(planeWidth / 2.0f, -planeHeight / 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(planeWidth / 2.0f, planeHeight / 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-planeWidth / 2.0f, planeHeight / 2.0f);
    glEnd();
    glPopMatrix();

    for (const auto &bullet : bullets)
    {
        if (bullet.isActive)
        {
            drawBullet(bullet.x, bullet.y, 5.0f, 10.0f); // Bullet size: 5x10
        }
    }

    for (const auto &enemy : enemies)
    {
        if (enemy.isActive)
        {
            drawEnemy(enemy.x, enemy.y);
        }
    }
}

void drawScore()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, screenHeight - 30);
    std::string scoreStr = "Score: " + std::to_string(score);
    
    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    for (char c : scoreStr)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);
    
}

void drawGameOverScreen() {
    glColor3f(1.0, 1.0, 1.0); // White color for text
    glRasterPos2f(screenWidth / 2 - 60, screenHeight / 2);
    std::string gameOverText = "Game Over!";
    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    for (char c : gameOverText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(screenWidth / 2 - 70, screenHeight / 2 - 20);
    std::string scoreText = "Final Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(screenWidth / 2 - 90, screenHeight / 2 - 40);
    std::string restartText = "Press 'R' to restart.";
    for (char c : restartText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);
}

void update(int value)
{
    if (!gameOver)
    {
        if (isMovingLeft)
        {
            planeX -= planeSpeed;
            if (planeX < planeWidth / 2)
            {
                planeX = planeWidth / 2;
            }
        }
        if (isMovingRight)
        {
            planeX += planeSpeed;
            if (planeX > screenWidth - planeWidth / 2)
            {
                planeX = screenWidth - planeWidth / 2;
            }
        }

        // Update bullet positions
        for (auto &bullet : bullets)
        {
            if (bullet.isActive)
            {
                bullet.y += bulletSpeed;
            }
        }

        // Update enemy spaceship positions and check for collisions
        for (auto &enemy : enemies)
        {
            if (enemy.isActive)
            {
                enemy.y -= 2.0f; // Fall down with a speed of 2.0f

                // Check for collision with bullets
                for (auto &bullet : bullets)
                {
                    if (bullet.isActive &&
                        bullet.x >= enemy.x - enemyWidth / 2 &&
                        bullet.x <= enemy.x + enemyWidth / 2 &&
                        bullet.y >= enemy.y - enemyHeight / 2 &&
                        bullet.y <= enemy.y + enemyHeight / 2)
                    {
                        bullet.isActive = false;
                        enemy.isActive = false;
                        score++;
                    }
                }

                // Check if the enemy spaceship hits the ground or the player's spaceship
                if (enemy.y < -enemyHeight / 2 || (enemy.y - enemyHeight / 2 <= planeY + planeHeight / 2 &&
                                                   enemy.x >= planeX - planeWidth / 2 && enemy.x <= planeX + planeWidth / 2))
                {
                    gameOver = true;
                }
            }
        }

        // Spawn a new enemy spaceship randomly
        if (rand() % 100 < 2)
        {
            Enemy enemy;
            enemy.isActive = true;
            enemy.x = rand() % (screenWidth - enemyWidth) + enemyWidth / 2;
            enemy.y = screenHeight + enemyHeight / 2;
            enemies.push_back(enemy);
        }

        glutPostRedisplay();
        glutTimerFunc(16, update, 0); // 60 FPS]
        drawScore();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (gameOver)
    {   
        drawGameOverScreen();
    }
    else
    {
        // Draw the game when not over
        drawCharacter();
    }

    drawScore(); // Draw the score on the screen

    glutSwapBuffers();
}


void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        isMovingLeft = true;
        break;
    case GLUT_KEY_RIGHT:
        isMovingRight = true;
        break;
    }
}

void specialKeysUp(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        isMovingLeft = false;
        break;
    case GLUT_KEY_RIGHT:
        isMovingRight = false;
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC key
        exit(0);
        break;
    case 32: // Space bar
    {
        Bullet bullet;
        bullet.isActive = true;
        bullet.x = planeX;
        bullet.y = planeY + planeHeight / 2.0f;
        bullets.push_back(bullet);
    }
    break;
    case 'r':
    case 'R':
        if (gameOver)
        {
            // Restart the game
            gameOver = false;
            bullets.clear();
            enemies.clear();
            planeX = (screenWidth - planeWidth) / 2.0f;
            planeY = 50.0f;
            score = 0;

            display();
            glutTimerFunc(0, update, 0);
        }
        break;
    }
}

void init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    loadTextures();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("2D GAME : SPACE WARS");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutKeyboardFunc(keyboard);
    init();
    glutTimerFunc(0, update, 0);
    
    
        sf::Music backgroundMusic;
        if (!backgroundMusic.openFromFile("background_music.wav")) {
            return -1;
        }

        backgroundMusic.setLoop(true); // Make the music loop
        backgroundMusic.play(); // Start playing the music
    

    glutMainLoop();

    return 0;
}
