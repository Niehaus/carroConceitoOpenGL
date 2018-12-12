#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "png_texture.h"

const float PI = 3.14;
const float DEG2RAD = 3.14159/180;

#define COORD_TEXTURA_PLANO 1.0
#define COORD_TEXTURA_CARRO 1.0
#define COR_DO_PLANO 0.52,0.52,0.78,1.0
#define COR_DO_CARRO 0.3,0.52,0.18,1.0
#define TEXTURA_DO_PLANO "montanhas.png"
#define TEXTURA_DO_CARRO "ladybug.png"


GLint WIDTH =1000;
GLint HEIGHT=700;

GLfloat obs[3]={0.0,7.0,0.0};
GLfloat look[3]={0.0,3.0,0.0};
GLfloat rodas[1000];
GLfloat rodas2[1000];
GLuint  textura_plano;
GLuint  textura_carro;

GLshort texturas=1;
GLfloat tetaxz=0;
GLfloat raioxz=10;
GLuint  carro;
GLuint theTorus;
GLfloat rotacao_porta_direita1 = -0.0f, rotacao_porta_direita2 = 0.0f,rotacao_cotovelo = 0.0f, rotacao_roda = 90.0f, base = 0.0f;

GLfloat ctp[4][2]={
  {-COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO},
  {-COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO}
};

GLfloat cta[4][2]={
  {-COORD_TEXTURA_CARRO,-COORD_TEXTURA_CARRO},
  {+COORD_TEXTURA_CARRO,-COORD_TEXTURA_CARRO},
  {+COORD_TEXTURA_CARRO,+COORD_TEXTURA_CARRO},
  {-COORD_TEXTURA_CARRO,+COORD_TEXTURA_CARRO}
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

   twopi = 2* PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x/2, y/2, z/2);
         }
      }
      glEnd();
   }
}

void drawCircle(float radius)
{
   glBegin(GL_POLYGON);

   for (int i=0; i < 1000; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
      rodas[i] = cos(degInRad)*radius;
      rodas2[i] = sin(degInRad)*radius;
   }

   glEnd();
}

void compoe_carro(void){
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
  /* inicia a composicao do carro */
  carro = glGenLists(1);
  glNewList(carro, GL_COMPILE);
  /* corpo */
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);

  quadric = gluNewQuadric();

  glBindTexture(GL_TEXTURE_2D,textura_carro);
  glPushMatrix();
  glTranslatef(0,0,4);

  // PARACHOQUE
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
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  glPushMatrix(); // CIMA DO VIDRO DIREITA
    glTranslatef(0.9,2.4,-0.1);
    glRotatef(0,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  glPushMatrix(); // PARTE DE CIMA DO VIDRO TRAZEIRA
    glTranslatef(-1.9,2.4,0);
    glRotatef(90,0,1,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    gluCylinder(quadric, 0.1, 0.1, 2.8, 12, 3);
  glPopMatrix();

  glPushMatrix(); // Lateral dos vidro direita
    glTranslatef(0.9,0.1,-1);
    glRotatef(-68,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  glPushMatrix(); // Lateral dos vidro ESQUERDA
    glTranslatef(-1.9,0.1,-1);
    glRotatef(-68,1,0,0);
    quadric = gluNewQuadric();
    glColor3f(0,0,0);
    gluCylinder(quadric, 0.1, 0.1, 2.5, 12, 3);
  glPopMatrix();

  // ---------------------------------------
  // PORTA

  glPushMatrix(); // LATERAL DIREITA DA PORTA
    glTranslatef(1.0, 0.1, 2.95);
    glRotatef(90,1,0,0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 1.2, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix(); // PARTE DEBAIXO DA PORTA
    glTranslatef(1.0, -1.06, -0.7);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 3.6, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix(); // LATERAL DIREITA DA PORTA
    glTranslatef(1.0, 0.1, -0.7);
    glRotatef(90,1,0,0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 1.2, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix(); // SEPARAÇÂO DAS PORTAS LADO DIREITO
    glTranslatef(1.0, 0.1, 1.15);
    glRotatef(90,1,0,0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 1.2, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix();//PORTA DIREITA FRENTE 1
    glTranslatef(0, -0.9, 2);
    glRotatef(rotacao_porta_direita1,0.0f,1.0f,0.0f);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f,-0.9f);
      glTexCoord2fv(ctp[1]);  glVertex3f( 1.0f, 1.0f, 0.9f);
      glTexCoord2fv(ctp[2]);  glVertex3f( 1.0f,-0.1f, 0.9f);
      glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-0.1f,-0.9f);
    glEnd();
  glPopMatrix();

  glPushMatrix();//PORTA DIREITA FRENTE 2
    glTranslatef(0, -0.9, 0.16);
    glRotatef(rotacao_porta_direita2,0.0f,1.0f,0.0f);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f,-0.9f);
      glTexCoord2fv(ctp[1]);  glVertex3f( 1.0f, 1.0f, 0.9f);
      glTexCoord2fv(ctp[2]);  glVertex3f( 1.0f,-0.1f, 0.9f);
      glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-0.1f,-0.9f);
    glEnd();
  glPopMatrix();

  //OUTRO LADO DA PORTA - ESQUERDA------------------------------
  // ------------------------------
  glPushMatrix(); // LATERAL DIREITA DA PORTA
    glTranslatef(-2.0, 0.1, 2.95);
    glRotatef(90,1,0,0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 1.2, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix(); // PARTE DEBAIXO DA PORTA ESQUERDA
    glTranslatef(-2.0, -1.06, -0.7);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 3.6, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix(); // LATERAL DIREITA DA PORTA ESQUERDA
    glTranslatef(-2.0, 0.1, -0.7);
    glRotatef(90,1,0,0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 1.2, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix(); // SEPARAÇÂO DAS PORTAS LADO ESQUERDO
    glTranslatef(-2.0, 0.1, 1.15);
    glRotatef(90,1,0,0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.05, 0.05, 1.2, 12, 3);
    glColor3f(0,0,0);
  glPopMatrix();

  glPushMatrix();//PORTA ESQUERDA FRENTE 1
    glTranslatef(-3.0, -0.9, 2);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f,-0.9f);
      glTexCoord2fv(ctp[1]);  glVertex3f( 1.0f, 1.0f, 0.9f);
      glTexCoord2fv(ctp[2]);  glVertex3f( 1.0f,-0.1f, 0.9f);
      glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-0.1f,-0.9f);
    glEnd();
  glPopMatrix();

  glPushMatrix();//PORTA ESQUERDA FRENTE 2
    glTranslatef(-3.0, -0.9, 0.16);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f,-0.9f);
      glTexCoord2fv(ctp[1]);  glVertex3f( 1.0f, 1.0f, 0.9f);
      glTexCoord2fv(ctp[2]);  glVertex3f( 1.0f,-0.1f, 0.9f);
      glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-0.1f,-0.9f);
    glEnd();
  glPopMatrix();

  // ---------------------------------------
  // PARTE DE BAIXO DO CARRO
  glPushMatrix(); //PARTE DE BAIXO DO PARACHOQUE
    glTranslatef(0,-2,3.75);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f, -0.75f);
      glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 1.0f, -0.75f);
      glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f, 1.0f,  2.25f);
      glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f, 1.0f,  2.25f);
    glEnd();
  glPopMatrix();

  glPushMatrix(); //PARTE DE BAIXO DO PARACHOQUE
    glTranslatef(0,-2,-3.1);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f, -0.75f);
      glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 1.0f, -0.75f);
      glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f, 1.0f,  2.25f);
      glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f, 1.0f,  2.25f);
    glEnd();
  glPopMatrix();

  glPushMatrix(); //PARTE DE BAIXO DOS BANCOS
    glTranslatef(0,-2,0);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 1.0f, -0.75f);
      glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 1.0f, -0.75f);
      glTexCoord2fv(ctp[0]);  glVertex3f(-2.0f, 1.0f,  3.0f);
      glTexCoord2fv(ctp[1]);  glVertex3f( 1.0f, 1.0f,  3.0f);
    glEnd();
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
      glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.9f);
      glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.9f);
      glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.9f);
      glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.9f);
    glEnd();
  glPopMatrix();

  glPushMatrix();//ESQUEDA DA LATERAL
    glTranslatef(-1,-0.4,-1.55);
    glBegin(GL_QUADS);
      glTexCoord2fv(ctp[0]);  glVertex3f(-1.0f, 0.5f, 0.9f);
      glTexCoord2fv(ctp[1]);  glVertex3f(-1.0f, 0.5f,-0.9f);
      glTexCoord2fv(ctp[2]);  glVertex3f(-1.0f,-0.1f,-0.9f);
      glTexCoord2fv(ctp[3]);  glVertex3f(-1.0f,-0.1f, 0.9f);
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

  // ----------------------------------------------------
  // RODAS DIANTEIRA DIREITA
  glPushMatrix();
    glTranslatef(1.3, -1.0, 3.8);
    glRotatef(rotacao_roda, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.1, -1.0, 3.8);
    glRotatef(rotacao_roda, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3, -1.0, 3.8);
    glRotatef(-90,0,1,0);
    glRotatef(rotacao_roda, 0, 1, 0);
    glScalef(0.5f,1,1);
    glBegin(GL_QUAD_STRIP);
     for (int i = 0; i < 1000; i++) {
       glVertex3f(0.5f,rodas2[i],rodas[i]);
       glVertex3f(-0.5f,rodas2[i],rodas[i]);
     }
     glEnd();
  glPopMatrix();

  // ----------------------------------------------------
  // RODAS DIANTEIRA ESQUERDA
  glPushMatrix();
    glTranslatef(-2.3, -1.0, 3.8);
    glRotatef(rotacao_roda, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2.1, -1.0, 3.8);
    glRotatef(rotacao_roda, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2.3, -1.0, 3.8);
    glRotatef(-90,0,1,0);
    glRotatef(rotacao_roda, 0, 1, 0);
    glScalef(0.5f,1,1);
    glBegin(GL_QUAD_STRIP);
     for (int i = 0; i < 1000; i++) {
       glVertex3f(0.5f,rodas2[i],rodas[i]);
       glVertex3f(-0.5f,rodas2[i],rodas[i]);
     }
     glEnd();
  glPopMatrix();
  // ----------------------------------------------------
  // RODAS TRASEIRA ESQUERDA
  glPushMatrix();
    glTranslatef(-2.3, -1.0, -1.5);
    glRotatef(90, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2.1, -1.0, -1.5);
    glRotatef(90, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();

  glPushMatrix();
     glTranslatef(-2.3, -1.0, -1.5);
     glScalef(0.5f,1,1);
     glBegin(GL_QUAD_STRIP);
     for (int i = 0; i < 1000; i++) {
       glVertex3f(0.5f,rodas2[i],rodas[i]);
       glVertex3f(-0.5f,rodas2[i],rodas[i]);
     }
     glEnd();
  glPopMatrix();

  // ----------------------------------------------------
  // RODAS TRASEIRA DIREITA
  glPushMatrix();
    glTranslatef(1.3, -1.0, -1.5);
    glRotatef(90, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();


  glPushMatrix();
    glTranslatef(1.1, -1.0, -1.5);
    glRotatef(90, 0, 1, 0);
    drawCircle(0.5f);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3, -1.0, -1.5);
    glScalef(0.5f,1,1);
    glBegin(GL_QUAD_STRIP);
     for (int i = 0; i < 1000; i++) {
       glVertex3f(0.5f,rodas2[i],rodas[i]);
       glVertex3f(-0.5f,rodas2[i],rodas[i]);
     }
     glEnd();
  glPopMatrix();

  // ---------------------------------
  /* cabine do piloto */
//  glTranslatef(0,1,3.5);
//  glPushMatrix();
//  glScalef(0.7,0.7,2.0);
//  quadric=gluNewQuadric();
//  glColor4f(0.3,0.5,1,0.5);
//  glDisable(GL_TEXTURE_2D);
//  gluSphere(quadric,0.5,12,12);
//  glPopMatrix();

// Volante
glPushMatrix();
glTranslatef(0,0,2.8f);
theTorus = glGenLists (2);
glNewList(theTorus, GL_COMPILE);
torus(4, 25);
glPopMatrix();

glPushMatrix(); // haste do Volante
  glTranslatef(0,0.5f,2.8f);
  glRotatef(68,1,0,0);
  quadric = gluNewQuadric();
  gluCylinder(quadric, 0.05, 0.05, 0.5, 12, 1);
  glColor3f(0,0,0);
glPopMatrix();

glPushMatrix(); // haste 2 do Volante
  glTranslatef(0,-0.5f,2.8f);
  glRotatef(-68,1,0,0);
  quadric = gluNewQuadric();
  gluCylinder(quadric, 0.05, 0.05, 0.6, 12, 1);
  glColor3f(0,0,0);
glPopMatrix();

glPushMatrix(); // haste 3 do Volante
  glTranslatef(0.5f,0,2.8f);
  glRotatef(-68,0,1,0);
  quadric = gluNewQuadric();
  gluCylinder(quadric, 0.05, 0.05, 0.5, 12, 1);
  glColor3f(0,0,0);
glPopMatrix();

glPushMatrix(); // haste 4 do Volante
  glTranslatef(-0.5f,0,2.8f);
  glRotatef(68,0,1,0);
  quadric = gluNewQuadric();
  gluCylinder(quadric, 0.05, 0.05, 0.5, 12, 1);
  glColor3f(0,0,0);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0,1);

// FECHA PAINEL
glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 0.1f, 2.0f);
  glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 0.1f, 2.0f);
  glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f,-1.0f, 2.0f);
  glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-1.0f, 2.0f);
  glEnd();
glPopMatrix();


// FECHA PAINEL TRADEIRO
glPushMatrix();
glTranslatef(0,0,-2.8f);
glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f( 1.0f, 0.1f, 2.0f);
  glTexCoord2fv(ctp[1]);  glVertex3f(-2.0f, 0.1f, 2.0f);
  glTexCoord2fv(ctp[2]);  glVertex3f(-2.0f,-1.0f, 2.0f);
  glTexCoord2fv(ctp[3]);  glVertex3f( 1.0f,-1.0f, 2.0f);
  glEnd();
glPopMatrix();
  /* termina a composicao do carro*/
  glEndList();
}

void display(void){
  glEnable(GL_DEPTH_TEST);
  compoe_carro(); //redesenha
  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  /* calcula a posicao do observador */
  obs[0]=raioxz*cos(2*PI*tetaxz/360);
  obs[2]=raioxz*sin(2*PI*tetaxz/360);
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);

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
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
  glBindTexture(GL_TEXTURE_2D,textura_plano);
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(-10,0,10);
  glTexCoord2fv(ctp[1]);  glVertex3f(10,0,10);
  glTexCoord2fv(ctp[2]);  glVertex3f(10,0,-10);
  glTexCoord2fv(ctp[3]);  glVertex3f(-10,0,-10);
  glEnd();
  glTranslatef(0.0,2.0,-3.0);
  glColor4f(COR_DO_CARRO);
  glBindTexture(GL_TEXTURE_2D,textura_carro);
  glCallList(carro);
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
  glColor4f(COR_DO_CARRO);
  glBindTexture(GL_TEXTURE_2D,textura_carro);
  glCallList(carro);
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
    printf("dando zoom %f\n",raioxz );
      glutPostRedisplay();
      break;
  case 'a':
    rotacao_porta_direita1-=2.1;  if(rotacao_porta_direita1 < -90) rotacao_porta_direita1 = -90;
    rotacao_porta_direita2+=2.1;  if(rotacao_porta_direita2 > 90) rotacao_porta_direita2 = 90;
    glutPostRedisplay();
      break;
  case 's':
    rotacao_porta_direita1+=2.1;  if(rotacao_porta_direita1 > 0.2) rotacao_porta_direita1 = 0.2;
    rotacao_porta_direita2+=-2.1; if(rotacao_porta_direita2 < -0.2) rotacao_porta_direita2 = -0.2;
    glutPostRedisplay();
      break;
  case 'w':
    rotacao_roda+=1.0; if(rotacao_roda > 110) rotacao_roda = 110;
    glutPostRedisplay();
    break;
  case 'd':
    rotacao_roda-=1.0; if(rotacao_roda < 70) rotacao_roda = 70;
    glutPostRedisplay();
    break;
  }
  glutPostRedisplay();
}

void carregar_texturas(void){
  textura_plano = png_texture_load(TEXTURA_DO_PLANO, NULL, NULL);
  textura_carro = png_texture_load(TEXTURA_DO_CARRO, NULL, NULL);
}

void init(){
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  carregar_texturas();
  compoe_carro();

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
