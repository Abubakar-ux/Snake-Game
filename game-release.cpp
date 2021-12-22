#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>
#include<unistd.h>
#include<sstream>
#include<cmath>   
#include<ctime>
#include<cstdlib>
#include<string>
#include<sstream>

#define ROWS 65
#define COLS 65
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2 
using namespace std;

int sx[50] = {32,32,32}, sy[50] = {32,31,30};
int snake_length = 3;
int _score = 0;
int fx , fy;
int line_x = 8 , line_y = 64;
int score_x = 50, score_y = 63;
int condition = 1;
short dir = RIGHT;



void unit(int x , int y) {
	
	if(x == 2 || y == 2 || x==ROWS-4 || y == COLS-4) {
		glLineWidth(3.0);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
		glVertex2f(x+1,y);
		glVertex2f(x+1,y+1);
		glVertex2f(x,y+1);
		glEnd();
	} 
	
 }

void Grid() {
	for(int i = 0; i<ROWS; i++) {
		for (int j = 0; j<COLS; j++) {
			unit(i,j);
		}

	}
 }

void Food() {
	
	if(condition == 1) {
	srand(time(NULL));
	fx = 7 + rand() % (ROWS - 4 - 7);
	fy = 7 + rand() % (COLS - 4 - 7);
	}
	condition = 0;
	DrawCircle(fx,fy,1,colors[ORANGE]);
	
 }


void Snake() {

	int i = snake_length-1;
	while(i>0) {
		sx[i] = sx[i-1];
		sy[i] = sy[i-1];
		i--;
	}
	if(dir == LEFT) {
		sx[0]--;
	}
	if(dir == RIGHT) {
		sx[0]++;
	}
	if(dir == UP) {
		sy[0]++;
	}
	if(dir == DOWN) {
		sy[0]--;
	}
	
	for(int i = 0; i<snake_length; i++) {
		
			DrawSquare( sx[i] , sy[i] , 0.7 , colors[WHITE]);	
		
		
	}
	
	
	
	if(sx[0] == 2 || sy[0] == 2 || sx[0] == ROWS-4 || sy[0] == COLS-4) {
		exit(1);
	}
	
	if((sx[0] == fx && sy[0] == fy) || (sx[0] == fx+1 && sy[0] == fy+1) || (sx[0] == fx-1 && sy[0] == fy-1)) {
		snake_length++;
		condition = 1;
		_score += 5;
		line_x++;
		
	}
	
 }

void status() {
	
	DrawString( 1, 63 , "Snake", colors[MISTY_ROSE]); 
	DrawLine( 8 , 64 ,  45 , 64 , 5 , colors[MISTY_ROSE] );
	DrawLine( 8 ,line_y, line_x ,line_y, 5, colors[ORANGE]);
	
 }

void score() {
	
	ostringstream str1;
	str1 << _score;
	string str = str1.str();
	DrawString( 50, 63, "Score = ", colors[MISTY_ROSE]); 
	DrawString( 58, 63, str , colors[MISTY_ROSE]);

}



void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ROWS, 0, COLS, -1, 1); 
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}



void Display(){
    // set the background color using function glClearColotgr.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
	
    Grid();
    Snake();
    
    Food();
	
    score();
 

   
    
    
    
     // This will draw a circle at x=200,y=200 of radius 50
    																		
																		//                    v1( x,y )   v2( x,y )  , v3( x,y ) 
    //DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
    
    
    
    status();
	
     
   glutSwapBuffers(); // do not modify this line..
}



void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)   {
      
	if(dir != RIGHT) {
		dir = LEFT;
	}
    } 
    
    else if (key == GLUT_KEY_RIGHT) {
	
	if(dir != LEFT) {
		dir = RIGHT;
	}
    } 
    
    else if (key == GLUT_KEY_UP) {
        
	if(dir != DOWN) {
		dir = UP;
	}
    }
    
    else if (key == GLUT_KEY_DOWN)   {
	
	if(dir != UP) {
		dir = DOWN;
	}
		
    }
    

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {


	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
  
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("Abubakar's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

    glutDisplayFunc(Display);
    glutSpecialFunc(NonPrintableKeys); 
    glutTimerFunc(0,Timer,0);
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

