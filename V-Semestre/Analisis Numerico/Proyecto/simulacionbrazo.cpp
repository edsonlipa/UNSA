#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;

#define A /2 (A>>1)
#define NUM 200

float matrix[NUM][NUM]={0};//no
float r=0,thetaDeg=0,theta=0,horizontal=NUM*3.75;
float maximum;
bool paused=false;

float posx1=200;//100
float posy1=0;//100
float angleA=0;//90

float temp=0;
int window_w,window_h;

int mode=0;	//0:points,1:lines

const float gradient[3][3]={{0,0.05,0.1},{0,0.5,1},{0.675,0.925,1}};

float point(float n){
	return (int(n)-(NUM/2))<<2;
}

void update1(float nAn){
	float temp1,temp2;
	temp1= ((posx1-(100))*cos(nAn))-(posy1*sin(nAn));
	temp2= ((posx1-(100))*sin(nAn))+(posy1*cos(nAn));
	posx1=temp1+(100);
	posy1=temp2;
	std::cout << " x: "<<posx1<<", y: "<<posy1 <<" angulo: "<<angleA<< '\n';
	angleA+=nAn;
}
//Get color from gradient

inline void color(float p){
	static int i;
	static float col[3];

	if(p<=0.5){
		p*=2;
		for(i=0;i<3;++i)
			col[i]=p*gradient[1][i]+(1-p)*gradient[0][i];
	}
	else{
		p=(p-0.5)*2;
		for(i=0;i<3;++i)
			col[i]=p*gradient[2][i]+(1-p)*gradient[1][i];
	}

	glColor3fv(col);
}

inline void drawPoints(){
	static int i,j;

    glBegin(GL_POINTS);
	for(i=0;i<NUM;++i){
        for(j=0;j<NUM;++j){
            color(matrix[i][j]/maximum);
            glVertex3f((j-(NUM/2))<<2,matrix[i][j]*(NUM>>4),(i-(NUM/2))<<2);
        }
	}
    glEnd();
}

inline void drawlines(){
	static int i,j;
	for(i=0;i<NUM;++i){
		glBegin(GL_LINE_STRIP);
			for(j=0;j<NUM;++j){
				color(matrix[i][j]/maximum);
				glVertex3f((j-(NUM/2))<<2,matrix[i][j]*(NUM>>4),(i-(NUM/2))<<2);
			}
		glEnd();
	}

	for(j=0;j<NUM;++j){
		glBegin(GL_LINE_STRIP);
			for(i=0;i<NUM;++i){
				color(matrix[i][j]/maximum);
				glVertex3f((j-(NUM/2))<<2,matrix[i][j]*(NUM>>4),(i-(NUM/2))<<2);
			}
		glEnd();
	}
}

float p;
string s2="Adithya Ramesh\n1PE13CS007\n\nAjay Singh\n1PE13CS013";
long long int count=0;

static void display(){
if(!paused){
		static int i,j;
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);///LIMPIA PUNTOS REALIZADOS
		glClearColor(1,1,1,1);

		if(count++<=600){
			glPushMatrix();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0,window_w,0,window_h,0,2);
			glMatrixMode(GL_MODELVIEW);
			if(count<=180)	p=count/180.0f;
			else	p=1-max((count-480)/120.0f,0.0f);
			color(p);

// /*____LETRAS*/
			glLoadIdentity();
			glLineWidth(1.5);
			glTranslatef(0,glutStrokeHeight(GLUT_STROKE_ROMAN)*0.75,0);
			glTranslatef(20,0,0);
			glScalef(0.15,0.15,1);
			glutStrokeString(GLUT_STROKE_ROMAN,(const unsigned char*)s2.c_str());
	/*""^^^LETRAS*/

			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
		// if(mode==0)
		// 	drawPoints();
		// else
		// 	drawlines();
/*PARA ABAJO PLANOS CARTECIANOS*/

		glBegin(GL_LINE_STRIP);
		  color(0.0625);
		// glColor3i(1,1,1);
			glVertex3f(NUM*2,0,-NUM*2);
			glVertex3f(NUM*2,0,NUM*2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		// glColor3i(1,1,1);
		  color(0.0625);
			glVertex3f(NUM*2,0,NUM*2);
			glVertex3f(-NUM*2,0,NUM*2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		// glColor3i(1,1,1);
			color(0.0625);
			glVertex3f(NUM*2,0,-NUM*2);
			glVertex3f(-NUM*2,0,-NUM*2);
		glEnd();

		glBegin(GL_LINE_STRIP); //origen
			//color(0.0625);
			color(0.111);
			glVertex3f((0-(NUM/2))<<2,0,(0-(NUM/2))<<2);
			glVertex3f((0-(NUM/2))<<2,(200-(NUM/2))<<2,(0-(NUM/2))<<2);
		glEnd();

		glBegin(GL_LINE_STRIP);//	brazo
			color(0.0625);
			glVertex3f(point(0)  ,0      ,point(100));
			glVertex3f(point(0)  ,2*NUM  ,point(100));
			glVertex3f(point(posy1)  ,2*NUM  ,point(posx1)); //y z x
			// glVertex3f(point(50)  ,3	*NUM/2    ,point(100)); //y z x
		glEnd();

		glBegin(GL_LINE_STRIP);
			color(0.0625);
			glVertex3f(-NUM*2,0,-NUM*2);
			glVertex3f(-NUM*2,0,NUM*2);
		glEnd();
		/*PARA ARRIBA  PLANOS CARTECIANOS*/

		// theta+=M_PI_2/1440;

		glLoadIdentity();
		gluLookAt(	r*cos(theta),horizontal,r*sin(theta),	//camera position
								0,0,0,								//center is at (0,0,0)
								0,1,0	);							//up is in positive Y direction
		// temp+=0.01;
		glutSwapBuffers();
	}
}

static void idle(){
	glutPostRedisplay();
}

static void reshape(int w,int h){
	window_w=w;
	window_h=h;
	glViewport(0,0,w,h);

	//Setup the view
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,(GLdouble)w/h,0.01,6400);
	glMatrixMode(GL_MODELVIEW);
}

#define ZOOMSTEP NUM>>4
static void keys(GLubyte key,int x,int y){
	switch(key){
		case 'o': {
							// angleA=20;
							update1(10);
							break;}
		case 'p':
							update1(-0.1);
							break;
		case 'a': theta+=M_PI_2/144;
						break;

		case 'd': theta-=M_PI_2/144;
						break;
		case 'w': horizontal+=M_PI*3;
						break;
		case 's': horizontal-=M_PI*3;
						break;
		case '+':		r-=ZOOMSTEP;
						break;
		case '-':		r+=ZOOMSTEP;
						break;
		case '\033':	exit(0);	//Esc to quit
						break;
		case ' ':		paused=!paused;
						break;

	}

	glutPostRedisplay();
}

inline void init(){
	//Initialize window
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE|GLUT_MULTISAMPLE);	//RGB+3D+Animated+Antialiased
	glutInitWindowSize(640,480);
	glutCreateWindow("Graph");
	glutFullScreen();

	//Assign callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutIdleFunc(idle);

	//Use depth buffering for hidden surface elimination.
	glEnable(GL_DEPTH_TEST);

	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	r=7.071068*NUM;									//5 root 2
	thetaDeg=45;
	theta=thetaDeg*M_PI/180;
	// y1=50;
	glLoadIdentity();
	gluLookAt(	r*cos(theta),NUM*3.75,r*sin(theta),	//camera position
				0,0,0,								//center is at (0,0,0)
				0,1,0	);							//up is in positive Y direction

	glLineWidth(0.75);
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	init();
	glutMainLoop();
	return 0;
}
