/*
 *
 */

#include <GLUT/glut.h>
#include <stdio.h>

#include "ParticleStructure.h"


particle particles[5];

int particleAmount = sizeof( particles) / sizeof( particles[0] );

//int particleAmount = 100;


#include "object.h"

object objects[1];

int objectAmount = sizeof( objects) / sizeof( objects[0] );

int arg = 1;

float light_pos[] = {100,100,100,1};

float pos[] = {0,1,0};

float camPos[] = {100 , 100 , 0};
float angle = 0.0f;

float gravity = -1;

int maxAge = 100;

bool pause = false;

bool friction = false;

int argMod = 10000;

int frames = 0;

/*were objects are created for scene
 shape: 0 = blank
 1 = cube
 2 = circle
 */



void createObjects(void)
{
    
    objects[0].position[0] = 0;
    objects[0].position[1] = 0;
    objects[0].position[2] = -50;
    objects[0].scale[0] = 100;
    objects[0].scale[1] = 100;
    objects[0].scale[2] = 2;
    objects[0].bounce = 1;
    objects[0].shape = 1;
    objects[0].color[0] = 1;
    objects[0].color[1] = 0;
    objects[0].color[2] = 0;
    
}

void drawMenu(void)
{
    if (pause){
        //menu stuff
    }
}

int checkIfWithin(int particleNumber, int objectNumber)
{
    int i = particleNumber;
    int j = objectNumber;
    if (particles[i].position[0] >= (objects[j].position[0]-objects[j].scale[0]/2) & particles[i].position[0] <= (objects[j].position[0]+objects[j].scale[0])/2)
    {
        if
            (particles[i].position[1] >= (objects[j].position[1]-objects[j].scale[1]/2) & particles[i].position[1] <= (objects[j].position[1]+objects[j].scale[1])/2)
        {
            if(particles[i].position[2] >= (objects[j].position[2]-objects[j].scale[2]/2) & particles[i].position[2] <= (objects[j].position[2]+objects[j].scale[2])/2)
            {
                return true; //it is within
            }
        }
    
    }
    /*
    if (particles[i].position[2]<=objects[j].position[2])
    {
        return true;
    }
     */
    return false;
}

void changeDirection(int particleNumber, int objectNumber)
{
    int i = particleNumber;
    int j = objectNumber;
    
    float bounce = -objects[j].bounce;
    
    //particles[i].direction[0] = particles[i].direction[0]*bounce;
    //particles[i].direction[1] = particles[i].direction[1]*bounce;
    particles[i].direction[2] = particles[i].direction[2]*bounce;
    
}

void updateDirection(int i)
{
   for (int i = 0; i<particleAmount; i++) {
     for (int j = 0; j<objectAmount; j++) {
            
        bool check = checkIfWithin(i,j);
         
         if (check){
             changeDirection(i,j);
         }
         else{
             particles[i].direction[2] = particles[i].direction[2] + gravity; // gravity update
         }
        }
    }
   }

void restartParticle(int i)
{
    
    particles[i].position[0] = 0;
    
    particles[i].position[1] = 0;
    
    particles[i].position[2] = 0;
    
    particles[i].size = 1;
    
    particles[i].color[0] = (float)rand()/((float)RAND_MAX/(1));;
    
    particles[i].color[1] = (float)rand()/((float)RAND_MAX/(1));;
    
    particles[i].color[2] = (float)rand()/((float)RAND_MAX/(1));;
    
    //particles[i].rotation =
    
    particles[i].age = 0;
    
    particles[i].direction[0] = -2 + (float)rand()/((float)RAND_MAX/(2+2));;;
    particles[i].direction[1] = -2 + (float)rand()/((float)RAND_MAX/(2+2));;;
    
    particles[i].direction[2] = 7;

    particles[i].speed = 1;
    
}

void particleInit(void)
{
    for (int i = 0; i < particleAmount; i++) {
        
        restartParticle(i);
        
    }
    
}

void updateParticles(void)
{
    
    for (int i = 0; i < particleAmount; i++) {
        updateDirection(i);
        
        particles[i].position[0] = particles[i].position[0] + particles[i].speed * particles[i].direction[0];
        
        particles[i].position[1] = particles[i].position[1] + particles[i].speed * particles[i].direction[1];
        
        particles[i].position[2] = particles[i].position[2] + particles[i].speed * particles[i].direction[2];
        
        //particles[i].rotation =
        
        particles[i].age++;

        if (particles[i].age>maxAge) {
            restartParticle(i);
        }
    }
}

void loadMenu(void)
{
    if (!pause)
    {
        frames = argMod+1;
        pause = true;
    }
    else
    {
        frames = 0;
        pause = false;
    }
    
    
    
}

void keyboard(unsigned char key, int x, int y)
{
    
	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'q':
		case 27:
			//exit (0);
			break;
            
		case 'r':
        case 'R':
			particleInit();
			break;
            
		case 'f':
        case 'F':
            if (!friction){
            for (int i = 0; i< objectAmount; i++) {
                objects[i].bounce = 0.9;
            }
                friction = true;
            }
            else{
                for (int i = 0; i< objectAmount; i++) {
                    objects[i].bounce = 1;
                }
                friction = false;
            }
            break;

            
        case ' ':
            loadMenu();
            break;

            
            
	}
    
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch(key)
	{
		case GLUT_KEY_LEFT:
			camPos[0]-=0.5;
			break;
            
		case GLUT_KEY_RIGHT:
			camPos[0]+=0.5;
			break;
            
		case GLUT_KEY_UP:
			camPos[2] -= 0.5;
			break;
            
		case GLUT_KEY_DOWN:
			camPos[2] += 0.5;
			break;
            
		case GLUT_KEY_HOME:
			camPos[1] += 0.5;
			break;
            
		case GLUT_KEY_END:
			camPos[1] -= 0.5;
			break;
            
	}
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
	float position[4] = {-1,1,0, 0};
    
	float amb[4] = {1.0, 1, 1, 1};
	float diff[4] = {1,0,0, 1};
	float spec[4] = {0,0,1, 1};
    
    
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    
    
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective(45, 1, 1, 1000);
    
}

void idle(void)
{
    arg++;
    
    if (arg%argMod == frames) {
        updateParticles();
        
        glutPostRedisplay();
        
        arg = 1;
    }
}

void drawObjects(void)
{
   for (int i = 0; i<objectAmount; i++) {
        glPushMatrix();
       
       float m_dif[] = {objects[i].color[0], objects[i].color[1],objects[i].color[2], 1.0};
       glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);

        glTranslated(objects[i].position[0],objects[i].position[2],objects[i].position[1]);
        glScaled(objects[i].scale[0], objects[i].scale[2], objects[i].scale[1]);
        
        if (objects[i].shape == 1){
            glutSolidCube(1);
        }
        if (objects[i].shape == 2){
            glutSolidSphere(1, 10, 10);
        }
        glPopMatrix();
    }
  
}

void drawParticles(void)
{
    for (int i = 0; i < particleAmount; i++) {
        
        glPushMatrix();
        float m_dif[] = {particles[i].color[0], particles[i].color[1],particles[i].color[2], 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
        
        glTranslated(particles[i].position[0], particles[i].position[2], particles[i].position[1]);
        
        
        //glColor3fv(particles[i].color);
        glutSolidSphere(particles[i].size, 10, 10);
       
        
        glPopMatrix();
        
    }
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
    
	//float origin[] = {0,0,0,1};
	float m_amb[] = {0.33, 0.22, 0.03, 1.0};
	float m_dif[] = {1, 0, 0, 1.0};
	float m_spec[] = {0.99, 0.91, 0.81, 1.0};
	float shiny = 60;
    
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    
	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    glColor3f(1,1,1);
    
    
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    
    drawParticles();
    
    drawObjects();
    
    drawMenu();
    

	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
    particleInit();
    createObjects();
    
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
    
	glutCreateWindow("Assignment 2");	//creates the window
    
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
    glutIdleFunc(idle);
    
	glEnable(GL_DEPTH_TEST);
	init();
    
	glutMainLoop();				//starts the event loop
    
	return(0);					//return may not be necessary on all compilers
}