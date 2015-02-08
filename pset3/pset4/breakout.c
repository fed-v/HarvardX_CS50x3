//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);   // DONE!
GOval initBall(GWindow window);     // DONE!
GRect initPaddle(GWindow window);   // DONE!
GLabel initScoreboard(GWindow window);  // DONE!
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // SET RANDOM INITIAL SPEED
    double xSpeed = 2 + drand48();
    double ySpeed = 2 + drand48();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if(event != NULL)
        {
            if(getEventType(event)== MOUSE_MOVED)
            {
                // SAVE X POSITION OF MOUSE DURING EVENT
                int x = getX(event);
                
                // MAKE SURE PADDLE DOESN'T GO OFFSCREEN
                if(x < getWidth(window)-getWidth(paddle))
                {
                    setLocation(paddle, x, 500);
                }
            }

        }
        
        
        // BALL MOVEMENT!
        
        move(ball, xSpeed, ySpeed);
        
        if(getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0)
        {
            xSpeed = -xSpeed;
        }else if(getY(ball) <= 0)
        {
            ySpeed = -ySpeed;
        }else if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives --;
            setLocation(ball, (getWidth(window)-20)/2, (getHeight(window)-20)/2);
            setLocation(paddle, (getWidth(window)-100)/2, 500);
            
            // RESET RANDOM SPEED!
            xSpeed = 2 + drand48();
            ySpeed = 2 + drand48();
            
            waitForClick();
              
        }
        
        pause(10);
        
        
        // CHECK TO SEE IF I HIT SOMETHING
        GObject objectDetected = detectCollision(window, ball);
        
        if(objectDetected != NULL && strcmp(getType(objectDetected), "GLabel") != 0)
        {
            if(objectDetected == paddle)
            {
                ySpeed = -ySpeed;
            }else if(strcmp(getType(objectDetected), "GRect") == 0)
            {
                removeGWindow(window, objectDetected);
                ySpeed = -ySpeed;
                bricks --;
                points = points + 20;
                
                updateScoreboard(window, label, points);
                
            }
        }
        
        
    }
    
    if(bricks == 0 && points == 1000)
    {
        removeGWindow(window, label);
        GLabel highScore = newGLabel("You Won! Final score is: 1000");
        setFont(highScore, "DejaVuSansMono-20");
        setLocation(highScore, (getWidth(window) - getWidth(highScore)) / 2, (getHeight(window) - getHeight(highScore)) / 2);
        setColor(highScore, "GRAY");
        add(window, highScore);
    }else{
        removeGWindow(window, label);
        removeGWindow(window, ball);
        GLabel highScore = newGLabel("You Lose! C'mon man!");
        setFont(highScore, "DejaVuSansMono-20");
        setLocation(highScore, (getWidth(window) - getWidth(highScore)) / 2, (getHeight(window) - getHeight(highScore)) / 2);
        setColor(highScore, "GRAY");
        add(window, highScore);
    }
    // wait for click before exiting
    
    waitForClick();
     

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    
    int y = 40;
    char* colors[] = {"RED", "ORANGE", "YELLOW", "BLUE", "GREEN"};

    for(int i=0; i<5; i++)
    {
        
        int x = 6;
       
    
        for(int j=0; j<10; j++)
        {
           //CREATE RECTANGLE
           GRect brick = newGRect(x, y, 34, 10);
           setColor(brick, colors[i]);
           setFilled(brick, true);
           add(window, brick);
           
           x = x + 39;
        }
        
        y = y + 15;
    }
}


/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval((getWidth(window)-20)/2, (getHeight(window)-20)/2, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((getWidth(window)-100)/2, 500, 80, 10);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel("SCORE: 0");
    setFont(score, "DejaVuSansMono-20");
    setLocation(score, (getWidth(window) - getWidth(score)) / 2, (getHeight(window) - getHeight(score)) / 2);
    setColor(score, "GRAY");
    add(window, score);
    
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "SCORE: %i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
