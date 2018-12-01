#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "png_texture.h"

//#define PI 3.1415
const float PI = 3.14;
const float DEG2RAD = 3.14159/180;

#define COORD_TEXTURA_PLANO 1.0
#define COORD_TEXTURA_AVIAO 1.0
#define COR_DO_PLANO 0.52,0.52,0.78,1.0
#define COR_DO_AVIAO 0.3,0.52,0.18,1.0
#define TEXTURA_DO_PLANO "montanhas.png"
#define TEXTURA_DO_AVIAO "ladybug.png"


GLint WIDTH =1000;
GLint HEIGHT=700;

GLfloat obs[3]={0.0,7.0,0.0};
GLfloat look[3]={0.0,3.0,0.0};
GLuint  textura_plano;
GLuint  textura_aviao;

GLshort texturas=1;
GLfloat tetaxz=0;
GLfloat raioxz=10;
GLuint  jato;
GLuint theTorus;


GLfloat ctp[4][2]={
  {-COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO},
  {-COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO}
};

GLfloat cta[4][2]={
  {-COORD_TEXTURA_AVIAO,-COORD_TEXTURA_AVIAO},
  {+COORD_TEXTURA_AVIAO,-COORD_TEXTURA_AVIAO},
  {+COORD_TEXTURA_AVIAO,+COORD_TEXTURA_AVIAO},
  {-COORD_TEXTURA_AVIAO,+COORD_TEXTURA_AVIAO}
};


void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,30.0);
  glMatrixMode(GL_MODELVIEW);
}


static void torus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}

void compoe_jato(void){
  GLUquadricObj *quadric;

  GLfloat asa[][3]={
    {-4.0,0.0,0.0},
    {+4.0,0.0,0.0},
    {0.0,0.0,3.0}
  };

  GLfloat cauda[][3]={
    {0.0,0.0,0.0},
    {0.0,2.0,-1.0},
    {0.0,2.0,0.0},
    {0.0,0.0,2.0}
  };
  /* inicia a composicao do jato */
  jato = glGenLists(1);
  glNewList(jato, GL_COMPILE);
  /* asas */
//  glBegin(GL_TRIANGLES);
//  glTexCoord2fv(cta[0]); glVertex3fv(asa[0]);
//  glTexCoord2fv(cta[1]); glVertex3fv(asa[1]);
//  glTexCoord2fv(cta[3]); glVertex3fv(asa[2]);
//  glEnd();

  /* corpo */
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  //gluCylinder(quadric, 1, 1, 4, 12, 3);

  /* nariz */
  quadric = gluNewQuadric();
  //gluQuadricTexture(quadric, GL_TRUE);
  //glBindTexture(GL_TEXTURE_2D, GL_TRUE);
  glBindTexture(GL_TEXTURE_2D,textura_aviao);
  glPushMatrix();
  glTranslatef(0,0,4);
  //gluCylinder(quadric, 1, 1.5, 1.5, 12, 3);
  glBegin(GL_QUADS); //PARTE DA FRENTE DO PARACHOQUE
    glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 0.1f, 2.0f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 0.1f, 2.0f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f,-1.0f, 2.0f);
    glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-1.0f, 2.0f);
    glEnd();
  glPopMatrix();

  glPushMatrix(); //PARTE DE CIMA DO PARACHOQUE
  glTranslatef(0,-0.9,3.75);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f, -0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 1.0f, -0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f, 1.0f,  2.25f);
    glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f, 1.0f,  2.25f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//ESQUERDA DO PARACHOQUE
  glTranslatef(0,-0.9,5.25);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-2.0f, 1.0f, 0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 1.0f,-0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f,-0.1f,-0.75f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-2.0f,-0.1f, 0.75f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//DIREITA DO PARACHOQUE
  glTranslatef(0,-0.9,5.25);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f,-0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f( 1.0f, 1.0f, 0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f( 1.0f,-0.1f, 0.75f);
    glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-0.1f,-0.75f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//DIREITA DA LATERAL
  glTranslatef(2,-0.4,3.75);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.75f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.75f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//ESQUEDA DA LATERAL
  glTranslatef(-1,-0.4,3.75);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.75f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.75f);
  glEnd();
  glPopMatrix();

  // -------------------------------------------
  // VIDROS

  glPushMatrix(); // Lateral dos vidro direita
    glTranslatef(0.9,2.4,2.3);
    glRotatef(68,1,0,0);
    quadric = gluNewQuadric();

    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix(); // Lateral dos vidro ESQUERDA
    glTranslatef(-1.9,2.4,2.3);
    glRotatef(68,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  glPushMatrix(); // PARTE DE CIMA DO VIDRO FRENTE
    glTranslatef(-1.9,2.4,2.3);
    glRotatef(90,0,1,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.8, 12, 3);
  glPopMatrix();

  glPushMatrix(); // CIMA DO VIDRO ESQUERDA
    glTranslatef(-1.9,2.4,-0.1);
    glRotatef(0,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  glPushMatrix(); // CIMA DO VIDRO DIREITA
    glTranslatef(0.9,2.4,-0.1);
    glRotatef(0,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  glPushMatrix(); // PARTE DE CIMA DO VIDRO TRAZEIRA
    glTranslatef(-1.9,2.4,0);
    glRotatef(90,0,1,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.8, 12, 3);
  glPopMatrix();

  glPushMatrix(); // Lateral dos vidro direita
    glTranslatef(0.9,0.1,-1);
    glRotatef(-68,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  glPushMatrix(); // Lateral dos vidro ESQUERDA
    glTranslatef(-1.9,0.1,-1);
    glRotatef(-68,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    //gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  // ---------------------------------------
  // PARTE TRASEIRA DO CARRO

  glPushMatrix(); //PARTE DE CIMA DO PARACHOQUE
  glTranslatef(0,-0.9,-3.1);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f, -0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 1.0f, -0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f, 1.0f,  2.25f);
    glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f, 1.0f,  2.25f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//DIREITA DA LATERAL
  glTranslatef(2,-0.4,-1.55);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.7f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.7f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.7f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.7f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//ESQUEDA DA LATERAL
  glTranslatef(-1,-0.4,-1.55);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.7f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.7f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.7f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.7f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//ESQUERDA DA LATERAL TRASEIRA
  glTranslatef(0,-0.9,-3.05);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-2.0f, 1.0f, 0.8f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 1.0f,-0.8f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f,-0.1f,-0.8f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-2.0f,-0.1f, 0.8f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//DIREITA DA LATERAL TRASEIRA
  glTranslatef(0,-0.9,-3.05);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f,-0.8f);
    glTexCoord2fv(ctp[1]);  glVertex3f( 1.0f, 1.0f, 0.8f);
    glTexCoord2fv(ctp[2]);  glVertex3f( 1.0f,-0.1f, 0.8f);
    glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-0.1f,-0.8f);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,0,-5.85);
  glBegin(GL_QUADS); //PARTE DA FRENTE DO PARACHOQUE
    glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 0.1f, 2.0f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 0.1f, 2.0f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f,-1.0f, 2.0f);
    glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-1.0f, 2.0f);
    glEnd();
  glPopMatrix();
  /* cauda */
    /*glBegin(GL_POLYGON);
  glTexCoord2fv(cta[0]); glVertex3fv(cauda[0]);
  glTexCoord2fv(cta[1]); glVertex3fv(cauda[1]);
  glTexCoord2fv(cta[2]); glVertex3fv(cauda[2]);
  glTexCoord2fv(cta[3]); glVertex3fv(cauda[3]);
  glEnd();*/

// ---------------------------------
//rodas
  // Volante
  glTranslatef(0,0,2.8);
  theTorus = glGenLists (2);
  glNewList(theTorus, GL_COMPILE);
  torus(4, 25);
  glTranslatef(1,-1,0);
  glRotatef(90,0,1,0);
  torus(9500, 25);
  glEndList();

  quadric = gluNewQuadric();
  gluQuadricTexture(quadric,GL_TRUE);
  glPushMatrix();
  glTranslatef(2,0,4);
  glPopMatrix();

  /* cabine do piloto */
//  glTranslatef(0,1,3.5);
//  glPushMatrix();
//  glScalef(0.7,0.7,2.0);
//  quadric=gluNewQuadric();
//  glColor4f(0.3,0.5,1,0.5);
//  glDisable(GL_TEXTURE_2D);
//  gluSphere(quadric,0.5,12,12);
//  glPopMatrix();

  /* termina a composicao do jato*/
  glEndList();
}

void display(void){
  glEnable(GL_DEPTH_TEST);

  //glDepthMask(GL_TRUE);
  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  /* calcula a posicao do observador */
  obs[0]=raioxz*cos(2*PI*tetaxz/360);
  obs[2]=raioxz*sin(2*PI*tetaxz/360);
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);

  /* habilita/desabilita usoglPushMatrix();//DIREITA DA LATERAL
  glTranslatef(2,-0.4,3.75);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.75f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.75f);
  glEnd();
  glPopMatrix();

  glPushMatrix();//ESQUEDA DA LATERAL
  glTranslatef(-1,-0.4,3.75);
  glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.75f);
    glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.75f);
    glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.75f);
    glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.75f);
  glEnd();
  glPopMatrix(); de texturas*/
  if(texturas){
    glEnable(GL_TEXTURE_2D);
  }
  else{
    glDisable(GL_TEXTURE_2D);
  }
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  // grava a transformacao atual
  glPushMatrix();
  glColor4f(COR_DO_PLANO);
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glBindTexture(GL_TEXTURE_2D,textura_plano);
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(-10,0,10);
  glTexCoord2fv(ctp[1]);  glVertex3f(10,0,10);
  glTexCoord2fv(ctp[2]);  glVertex3f(10,0,-10);
  glTexCoord2fv(ctp[3]);  glVertex3f(-10,0,-10);
  glEnd();
  glTranslatef(0.0,2.0,-3.0);
  glColor4f(COR_DO_AVIAO);
  glBindTexture(GL_TEXTURE_2D,textura_aviao);
  glCallList(jato);
  glPopMatrix();
  // volta para a ultima transformacao

  // grava a transformacao atual
  glPushMatrix();
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glColor4f(COR_DO_PLANO);
  glBindTexture(GL_TEXTURE_2D,textura_plano);

  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(-10,0,10);
  glTexCoord2fv(ctp[1]);  glVertex3f(10,0,10);
  glTexCoord2fv(ctp[2]);  glVertex3f(10,0,-10);
  glTexCoord2fv(ctp[3]);  glVertex3f(-10,0,-10);
  glEnd();
  glTranslatef(0.0,2.0,-3.0);
  glColor4f(COR_DO_AVIAO);
  glBindTexture(GL_TEXTURE_2D,textura_aviao);
  glCallList(jato);
  glPopMatrix();
  // volta para a ultima transformacao

  glPopMatrix();
  glutSwapBuffers();
}


void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
    obs[1]=obs[1]+1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] =obs[1]-1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 't':
    texturas = !texturas;
    glutPostRedisplay();
    break;
  case 'r':
    raioxz=raioxz+1;
    glutPostRedisplay();
    break;
  case 'R':
    raioxz=raioxz-1;
    if(raioxz==0){
      raioxz=1;
    }
    glutPostRedisplay();
    break;
  }
}

void carregar_texturas(void){
  textura_plano = png_texture_load(TEXTURA_DO_PLANO, NULL, NULL);
  textura_aviao = png_texture_load(TEXTURA_DO_AVIAO, NULL, NULL);
}

void init(){
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  carregar_texturas();
  compoe_jato();

  //  glShadeModel(GL_FLAT);
  glEnable(GL_TEXTURE_2D);
}

int main(int argc,char **argv){
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_ALPHA);

  if(!glutCreateWindow("Carro Conceito")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return(0);
}
