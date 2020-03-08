#include <gl/glut.h>
#include "tgaload.h"
#include <cmath>


//"EMPTY YOUR MIND, BE FORMLESS. SHAPELESS, LIKE WATER.
//IF YOU PUT WATER INTO A CUP, IT BECOMES THE CUP, PUT WATER INTO A BOTTLE AND IT BECOMES THE BOTTLE.
//YOU PUT WATER INTO A TEAPOT, IT BECOMES THE TEAPOT. WATER CAN FLOW OR WATER CAN CRASH
//BE WATER MY FRIEND"

//GLfloat angle, fAspect;
GLfloat ASPECTO, ANGULO;
int x_ini, y_ini, bot;
GLfloat obsX, obsY, obsZ, rotX, rotY;
GLfloat obsX_ini, obsY_ini, obsZ_ini, rotX_ini, rotY_ini;
GLfloat escalaX, escalaY, escalaZ;
#define SENS_ROT 10.0
#define SENS_OBS 10.0
#define SENS_TRANS 10.0

//TESE
#define SOLID_CLOSED_CYLINDER(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS) \
gluCylinder(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS); \
glRotatef(180, 1,0,0); \
gluDisk(QUAD, 0.0f, BASE, SLICES, 1); \
glRotatef(180, 1,0,0); \
glTranslatef(0.0f, 0.0f, HEIGHT); \
gluDisk(QUAD, 0.0f, TOP, SLICES, 1); \
glTranslatef(0.0f, 0.0f, -HEIGHT);

GLuint texture_id[8]; //vetor de ID de texturas n�o pode sair daqui, nem mudar de lugar

float xrot;
float yrot;
float zrot;
float ratio;

static GLUquadricObj* quadratic = 0;

void initTexture(void) {
	// Habilita o uso de textura
	glEnable(GL_TEXTURE_2D);

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Define quantas texturas ser�o usadas no programa
	glGenTextures(8, texture_id);  // 1 = uma textura;
	// texture_id = ve tor que guardas os n�meros das texturas
	image_t temp_image0;
	texture_id[0] = 1000;
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	tgaLoad((char *)"texturas/campo.tga", &temp_image0, TGA_FREE | TGA_LOW_QUALITY);
	texture_id[1] = 1001;
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);
	tgaLoad((char*) "texturas/pilastra.tga", &temp_image0, TGA_FREE);
	texture_id[2] = 1002;
	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	tgaLoad((char*) "texturas/teto.tga", &temp_image0, TGA_FREE);
	texture_id[3] = 1003;
	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	tgaLoad((char*) "texturas/chao.tga", &temp_image0, TGA_FREE);
	texture_id[4] = 1004;
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	tgaLoad((char*) "texturas/sky.tga", &temp_image0, TGA_FREE);
	texture_id[5] = 1005;
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	tgaLoad((char*) "texturas/contencao.tga", &temp_image0, TGA_FREE);
	texture_id[6] = 1006;
	glBindTexture(GL_TEXTURE_2D, texture_id[6]);
	tgaLoad((char*) "texturas/telao.tga", &temp_image0, TGA_FREE);
	texture_id[7] = 1007;
	glBindTexture(GL_TEXTURE_2D, texture_id[7]);
	tgaLoad((char*) "texturas/faixav.tga", &temp_image0, TGA_FREE);
}


void eixos(void) {
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 300.0);
	glEnd();
	glPopMatrix();

}

void gerarPaineis(void) {

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();//contencao 1
	glColor3f(2.55f, 2.55f, 2.55f);
	glTranslated(-27, 0, -50);
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);  //DESENHAR O PONTO D
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 3, 0);  // DESENHAR O B
	glTexCoord2f(1.0f, 1.0f); glVertex3f(54, 3, 0); // DESENHAR O PONTO C
	glTexCoord2f(1.0f, 0.0f); glVertex3f(54, 0, 0);  // DESENHAR O PONTO A
	glEnd();
	glPopMatrix();

	glPushMatrix();//contencao 2
	glColor3f(2.55f, 2.55f, 2.55f);
	glTranslated(-30, 0, 47);
	glRotated(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);  //DESENHAR O PONTO D
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 3, 0);  // DESENHAR O B
	glTexCoord2f(1.0f, 1.0f); glVertex3f(94, 3, 0); // DESENHAR O PONTO C
	glTexCoord2f(1.0f, 0.0f); glVertex3f(94, 0, 0);  // DESENHAR O PONTO A
	glEnd();
	glPopMatrix();

	glPushMatrix();//contencao 3
	glColor3f(2.55f, 2.55f, 2.55f);
	glTranslated(30, 0, 47);
	glRotated(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);  //DESENHAR O PONTO D
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 3, 0);  // DESENHAR O B
	glTexCoord2f(0.0f, 1.0f); glVertex3f(94, 3, 0); // DESENHAR O PONTO C
	glTexCoord2f(0.0f, 0.0f); glVertex3f(94, 0, 0);  // DESENHAR O PONTO A
	glEnd();
	glPopMatrix();

	glPushMatrix();//contencao 4
	glColor3f(2.55f, 2.55f, 2.55f);
	glTranslated(-27, 0, 50);
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);  //DESENHAR O PONTO D
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 3, 0);  // DESENHAR O B
	glTexCoord2f(0.0f, 1.0f); glVertex3f(54, 3, 0); // DESENHAR O PONTO C
	glTexCoord2f(0.0f, 0.0f); glVertex3f(54, 0, 0);  // DESENHAR O PONTO A
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void gerarCampo(void) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	glPushMatrix(); //campo
	glBegin(GL_QUADS);
	glColor3f(2.55f, 2.55f, 2.55f);
	glMatrixMode(GL_MODELVIEW);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-30.0, 0, -50.0); //a
	glTexCoord2f(1.0f, 0.0f); glVertex3f(30.0, 0, -50.0); //b
	glTexCoord2f(0.0f, 0.0f); glVertex3f(30.0, 0, 50.0); //c
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-30.0, 0, 50.0); //d
	glEnd();
	glPopMatrix();



	//gol 1 ////////////////////////////////////////////////

	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	glPushMatrix(); // trave esquerda
	glTranslatef(-9.35, 0, -44.6);
	glColor3f(1, 1, 1);
	glRotatef(-90.0f, 8.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);
	gluCylinder(quadratic, 0.1f, 0.1f, 7, 100, 100);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	glPushMatrix(); // trave direita
	glTranslatef(9.35, 0, -44.6);
	glColor3f(1, 1, 1);
	glRotatef(-90.0f, 8.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);
	gluCylinder(quadratic, 0.1f, 0.1f, 7, 100, 100);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	glPushMatrix(); // travess�o
	glTranslatef(9.35, 6.9, -44.6);
	glColor3f(1, 1, 1);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);
	gluCylinder(quadratic, 0.1f, 0.1f, 18.7, 100, 100);
	glPopMatrix();


	//gol 2 //////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(0, 0, 89.2);
	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	glPushMatrix(); // trave esquerda
	glTranslatef(-9.35, 0, -44.6);
	glColor3f(1, 1, 1);
	glRotatef(-90.0f, 8.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);
	gluCylinder(quadratic, 0.1f, 0.1f, 7, 100, 100);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	glPushMatrix(); // trave direita
	glTranslatef(9.35, 0, -44.6);
	glColor3f(1, 1, 1);
	glRotatef(-90.0f, 8.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);
	gluCylinder(quadratic, 0.1f, 0.1f, 7, 100, 100);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	glPushMatrix(); // travess�o
	glTranslatef(9.35, 6.9, -44.6);
	glColor3f(1, 1, 1);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);
	gluCylinder(quadratic, 0.1f, 0.1f, 18.7, 100, 100);
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void desenhaChao(void) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-300.0, -0.01, -300.0);
	glTexCoord2f(0, 20.0); glVertex3f(-300.0, -0.01, 300.0);
	glTexCoord2f(20.0, 20.0); glVertex3f(300.0, -0.01, 300.0);
	glTexCoord2f(20.0, 0); glVertex3f(300.0, -0.01, -300.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void desenhaEsfera(void) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glColor3f(1, 1, 1);
	glutSolidTeapot(300);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void sustentaTelao(float raioDaEstrutura) {
	glPushMatrix(); //SUS TELAO 1
	for (float i = 0; i <= 360; i = i++)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.1 * sin(i), 0.1 * cos(i), 0);
		glBegin(GL_POLYGON);
		glVertex3f(-3.9, 28, raioDaEstrutura - 10);
		glVertex3f(-3.9, 30, raioDaEstrutura);
		glVertex3f(-4.1, 30, raioDaEstrutura);
		glVertex3f(-4.1, 28, raioDaEstrutura - 10);
		glEnd();
		glPopMatrix();
	}

	for (float i = 0; i <= 360; i = i++)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.1 * sin(i), 0.1 * cos(i), 0);
		glBegin(GL_POLYGON);
		glVertex3f(-3.9, 28 - 8, raioDaEstrutura - 10);
		glVertex3f(-3.9, 30, raioDaEstrutura);
		glVertex3f(-4.1, 30, raioDaEstrutura);
		glVertex3f(-4.1, 28 - 8, raioDaEstrutura - 10);
		glEnd();
		glPopMatrix();
	}

	for (float i = 0; i <= 360; i = i++)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.1 * sin(i), 0.1 * cos(i), 0);
		glBegin(GL_POLYGON);
		glVertex3f(-3.9 + 8, 28, raioDaEstrutura - 10);
		glVertex3f(-3.9 + 8, 30, raioDaEstrutura);
		glVertex3f(-4.1 + 8, 30, raioDaEstrutura);
		glVertex3f(-4.1 + 8, 28, raioDaEstrutura - 10);
		glEnd();
		glPopMatrix();
	}

	for (float i = 0; i <= 360; i = i++)
	{
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.1 * sin(i), 0.1 * cos(i), 0);
		glBegin(GL_POLYGON);
		glVertex3f(-3.9 + 8, 28 - 8, raioDaEstrutura - 10);
		glVertex3f(-3.9 + 8, 30, raioDaEstrutura);
		glVertex3f(-4.1 + 8, 30, raioDaEstrutura);
		glVertex3f(-4.1 + 8, 28 - 8, raioDaEstrutura - 10);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}

void gerarTelao(float raioDaEstrutura) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();//TELAO 1 
	glColor3f(2.55f, 2.55f, 2.55f);
	glTranslated(-4, 20, -(raioDaEstrutura - 10));
	glBindTexture(GL_TEXTURE_2D, texture_id[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);  //DESENHAR O PONTO D
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 8, 0);  // DESENHAR O B
	glTexCoord2f(1.0f, 1.0f); glVertex3f(8, 8, 0); // DESENHAR O PONTO C
	glTexCoord2f(1.0f, 0.0f); glVertex3f(8, 0, 0);  // DESENHAR O PONTO A
	glEnd();
	glPopMatrix();


	glPushMatrix();//TELAO 2 
	glColor3f(2.55f, 2.55f, 2.55f);
	glTranslated(-4, 20, raioDaEstrutura - 10);
	glBindTexture(GL_TEXTURE_2D, texture_id[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);  //DESENHAR O PONTO D
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 8, 0);  // DESENHAR O B
	glTexCoord2f(0.0f, 1.0f); glVertex3f(8, 8, 0); // DESENHAR O PONTO C
	glTexCoord2f(0.0f, 0.0f); glVertex3f(8, 0, 0);  // DESENHAR O PONTO A
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	sustentaTelao(raioDaEstrutura);

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 0, 0);
	sustentaTelao(raioDaEstrutura);
	glPopMatrix();

}

class arquibancada {
private:

	static void baseArqui(float c1, float c2, float c3) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(26, 0, -43);
		for (float i = 125; i <= 160; i = i + 0.3) //semi-c�rculo
		{
			glBindTexture(GL_TEXTURE_2D, texture_id[2]);
			glPushMatrix();
			glRotatef(i, 0, 1, 0);
			glColor3f(c1, c2, c3);
			glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex3f(0, 0, 8);
			glTexCoord2f(0, 0.1); glVertex3f(0, 3, 8);
			glTexCoord2f(0.1, 0.1); glVertex3f(3, 3, 8);
			glTexCoord2f(0.1, 0); glVertex3f(3, 0, 8);
			glEnd();
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//contencao de cima
		glBindTexture(GL_TEXTURE_2D, texture_id[7]);
		glColor3f(c1, c2, c3);
		glTranslated(-26.9, 0, -51.5);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
		glTexCoord2f(0, 20.0); glVertex3f(0, 3, 0);
		glTexCoord2f(20.0, 20.0); glVertex3f(27, 3, 0);
		glTexCoord2f(20.0, 0); glVertex3f(27, 0, 0);
		//	glTexCoord2f(20.0,20.0);glVertex3f(54, 3, 0); 
		//	glTexCoord2f(20.0,0);glVertex3f(54, 0, 0);  
		glEnd();
		glPopMatrix();

		glPushMatrix();//contencao esquerda
		glBindTexture(GL_TEXTURE_2D, texture_id[7]);
		glColor3f(c1, c2, c3);
		glTranslated(32.5, 0, 46.4 + 1.4);
		glRotated(90, 0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
		glTexCoord2f(0, 20.0); glVertex3f(0, 3, 0);
		//	glTexCoord2f(20.0,20.0);glVertex3f(95.8, 3, 0); 
		//	glTexCoord2f(20.0,0);glVertex3f(95.8, 0, 0);  
		glTexCoord2f(20.0, 20.0); glVertex3f(47.9, 3, 0);
		glTexCoord2f(20.0, 0); glVertex3f(47.9, 0, 0);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	static void gerarPartedeCima(float c1, float c2, float c3) {
		glPushMatrix();
		baseArqui(c1, c2, c3);
		glRotatef(-180, 0, 0, 1);
		glTranslatef(0, -3, 0);
		baseArqui(c1, c2, c3);
		glPopMatrix();
	}

	static void gerarparteDeBaixo(float c1, float c2, float c3) {
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		glTranslatef(0, -3, 0);
		gerarPartedeCima(c1, c2, c3);
		glPopMatrix();
	}
public:

	static void gerarNivel(void) {
		glPushMatrix();
		float x = 1;
		float y = 1;
		float z = 1;
		for (int i = 1; i <= 13; i++)
		{
			glPushMatrix();
			glScalef(x, y, z);
			//glScalef(x,1,z); //versao sem paredao
			//glTranslatef(0,y*2.5,0); //versao sem paredao
			gerarPartedeCima(1, 1, 1);
			gerarparteDeBaixo(1, 1, 1);
			glPopMatrix();
			x += 0.05; y += 0.4; z += 0.025;
		}
		glPopMatrix();


	}

};

class EstruturaExterna {

private:

	static void gerarAnel(int id_textura, float altura, float raioDaEstrutura) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture_id[id_textura]);
		glPushMatrix(); // Anel chao
		glTranslatef(0, altura, 0);
		glColor3f(1, 1, 1);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glMatrixMode(GL_MODELVIEW);
		quadratic = gluNewQuadric();
		gluQuadricTexture(quadratic, true);
		gluCylinder(quadratic, raioDaEstrutura + 10, raioDaEstrutura, 0.1f, 100, 100);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	static void gerarPilastras(float raioDaEstrutura) {
		glEnable(GL_TEXTURE_2D);
		for (int i = 0; i <= 360; i = i + 5) //desenha pilastras
		{
			glPushMatrix();
			glRotatef(i, 0.0f, 1, 0.0f);
			for (int j = 1; j <= 3; j = j++)
			{
				glBindTexture(GL_TEXTURE_2D, texture_id[1]);
				glPushMatrix(); // FAZER CILINDRO
				glTranslatef(0, 0, raioDaEstrutura + j * 2.5);
				glColor3f(1, 1, 1);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quadratic, .5f, .5f, 30, 50, 50);
				glPopMatrix();
			}
			glPopMatrix();
		}
		glDisable(GL_TEXTURE_2D);
	}

	static void gerarFerragens(float raioDaEstrutura) {
		for (int i = 0; i <= 360; i = i + 10) // desenha ferragens do teto
		{
			glPushMatrix();
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_LINES);
			glVertex3f(raioDaEstrutura / 4, 29.5, 0.0);
			glVertex3f(raioDaEstrutura / 2, 28.0, 0.0);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glRotatef(i, 0.0f, 1, 0.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_LINES);
			glVertex3f(raioDaEstrutura / 2, 28, 0.0);
			glVertex3f(raioDaEstrutura, 30, 0.0);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glRotatef(i, 0.0f, 1, 0.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_LINES);
			glVertex3f(raioDaEstrutura / 2, 28.2, 0.0);
			glVertex3f(raioDaEstrutura, 30.1, 0.0);
			glEnd();
			glPopMatrix();
		}
	}

	static void gerarCobertura(float raioDaEstrutura) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture_id[2]);
		glTranslatef(0, 30.1f, 0);
		glRotated(180, 1, 0, 0);
		glColor4f(80, 80, 80, .98);
		glMatrixMode(GL_MODELVIEW);
		glRotatef(-90.0f, 8.0f, 0.0f, 0.0f);
		quadratic = gluNewQuadric();
		gluQuadricTexture(quadratic, true);
		gluCylinder(quadratic, raioDaEstrutura, raioDaEstrutura / 2, 2, 100, 100);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(0, 28.1f, 0);
		glColor4f(0.7f, 0.7f, 0.7f, 0.7f);
		glRotatef(-90.0f, 8.0f, 0.0f, 0.0f);
		glMatrixMode(GL_MODELVIEW);
		gluCylinder(gluNewQuadric(), raioDaEstrutura / 2, raioDaEstrutura / 4, 1.5, 100, 100);
		glDisable(GL_BLEND);
		glPopMatrix();
	}

public:
	//
	static void gerarExtrutura(float raioDaEstrutura) {
		gerarAnel(1, 4.0, raioDaEstrutura);
		gerarAnel(1, 30.1, raioDaEstrutura);
		gerarCobertura(raioDaEstrutura);
		gerarPilastras(raioDaEstrutura);
		gerarFerragens(raioDaEstrutura);
		gerarTelao(raioDaEstrutura);

	}

};

void Desenha(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	eixos();

	//AMBIENTE
	desenhaChao();
	desenhaEsfera();

	EstruturaExterna::gerarExtrutura(83.5);
	arquibancada::gerarNivel();
	gerarCampo();
	gerarPaineis();


	glPushMatrix();
	glTranslatef(30, 0, 0);
	glColor3f(0.5, 0, 0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(22, 0.2, 65);
	glVertex3f(22, 0.2, -65.0);
	glVertex3f(0, 0.2, -65.0);
	glVertex3f(0, 0.2, 65.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glTranslatef(30, -0.4, 0);
	glColor3f(0.5, 0, 0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(22, 0.2, 65);
	glVertex3f(22, 0.2, -65.0);
	glVertex3f(0, 0.2, -65.0);
	glVertex3f(0, 0.2, 65.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 0.1, -67);
	glColor3f(0.5, 0, 0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(90, 0.2, 16.8);
	glVertex3f(90, 0.2, 0.0);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0.2, 16.8);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(-40, -0.3, -67);
	glColor3f(0.5, 0, 0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(90, 0.2, 16.8);
	glVertex3f(90, 0.2, 0.0);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0.2, 16.8);
	glEnd();
	glPopMatrix();


	glutSwapBuffers();
}

void Inicializa(void)
{
	GLfloat luzAmbiente[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat luzDifusa[4] = { 0.7, 0.7, 0.7, 1.0 };		 // "cor"
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 }; // "brilho"
	GLfloat posicaoLuz[4] = { 0.0, 640.0, -70.0, 10.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLint especMaterial = 10;

	// Especifica que a cor de fundo da janela ser� preta
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	//angle=45;
	ANGULO = 45;
	rotX = rotY = 0;
	obsX = 0;
	obsY = 3;
	obsZ = 10;
	escalaX = escalaY = escalaZ = 1;
}

void EspecificaParametrosVisualizacao(void) //equivalente ao posiciona observador
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	//gluPerspective(angle,fAspect,0.4,500);
	gluPerspective(ANGULO, ASPECTO, 0.4, 800);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
	//gluLookAt(0,80,200, 0,0,0, 0,1,0);
	//gluLookAt(obsX, obsY, obsZ, 0,0,0, 0,1,0);
	glTranslatef(-obsX, -obsY, -obsZ);/*Translata a câmera para essas variáveis*/
	glRotatef(rotX, 1, 0, 0); /*Rotacionar a câmera para essas coordenadas*/
	glRotatef(rotY, 0, 1, 0);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	//fAspect = (GLfloat)w/(GLfloat)h;
	ASPECTO = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void GerenciaMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void motion(int x, int y)
{
	if (bot == GLUT_LEFT_BUTTON) //Rotação
	{
		int deltaX = x_ini - x;
		int deltaY = y_ini - y;
		rotX = rotX_ini - deltaY / SENS_ROT;
		rotY = rotY_ini - deltaX / SENS_ROT;
	}
	else if (bot == GLUT_RIGHT_BUTTON) //Zoom
	{
		int deltaZ = y_ini - y;
		obsZ = obsZ_ini + deltaZ / SENS_OBS;
	}
	else if (bot == GLUT_MIDDLE_BUTTON) //Correr
	{
		int deltaX = x_ini - x;
		int deltaY = y_ini - y;
		obsX = obsX_ini + deltaX / SENS_TRANS;
		obsY = obsY_ini + deltaY / SENS_TRANS;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Programa Principal
int main(int argcp, char **argv)
{
	glutInit(&argcp, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Stadium");
	initTexture();
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(motion);
	Inicializa();
	glutMainLoop();
}