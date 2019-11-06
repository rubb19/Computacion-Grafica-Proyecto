//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

CCamera objCamera; 
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
CTexture text7;	//Casa01
CTexture text8;	//Casa01
CTexture text9;	//Casa01
CTexture text10;	//Casa01
CTexture text11;	//Casa01
CTexture text12;	//Casa01
CTexture text13;	//Casa01
CTexture text14;	//Casa01
CTexture text15;	//Casa01
CTexture text16;	//Casa01
CTexture text17;	//Casa01
CTexture text18;	//Casa01


CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	
CFiguras fig5;	
CFiguras fig6;

CFiguras fig7; 

//Figuras de 3D Studio
CModel kit;
CModel llanta;

//Animación del coche
float movKit = 0.0;
float rotKit = 0.0;
bool g_fanimacion = false;

			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On
    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("tejado.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadBMP("casa.bmp");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadBMP("tejado_contorno.bmp");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadBMP("pared_bart.bmp");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadBMP("piso_bart.bmp");
	text6.BuildGLTexture();
	text6.ReleaseImage();


	text7.LoadBMP("cama_bart.bmp");
	text7.BuildGLTexture();
	text7.ReleaseImage();
	
	text8.LoadBMP("cabecera_bart.bmp");
	text8.BuildGLTexture();
	text8.ReleaseImage();

	text9.LoadBMP("librero_bart.bmp");
	text9.BuildGLTexture();
	text9.ReleaseImage();

	text10.LoadBMP("ventana_bart.bmp");
	text10.BuildGLTexture();
	text10.ReleaseImage();

	text11.LoadBMP("poster_bart.bmp");
	text11.BuildGLTexture();
	text11.ReleaseImage();

	text12.LoadBMP("pizarron_bart.bmp");
	text12.BuildGLTexture();
	text12.ReleaseImage();

	text13.LoadBMP("escritorio_bart.bmp");
	text13.BuildGLTexture();
	text13.ReleaseImage();


	text14.LoadBMP("puerta.bmp");
	text14.BuildGLTexture();
	text14.ReleaseImage();


	text15.LoadBMP("ventana.bmp");
	text15.BuildGLTexture();
	text15.ReleaseImage();

	//text3.LoadTGA("city/arrow.tga");
	//text3.BuildGLTexture();
	//text3.ReleaseImage();

	//text4.LoadTGA("city/pavimento.tga");
	//text4.BuildGLTexture();
	//text4.ReleaseImage();

	text16.LoadBMP("cesped.bmp");
	text16.BuildGLTexture();
	text16.ReleaseImage();

	text17.LoadBMP("ventana_bart.bmp");
	text17.BuildGLTexture();
	text17.ReleaseImage();

	text18.LoadBMP("boliche.bmp");
	text18.BuildGLTexture();
	text18.ReleaseImage();

	//Carga de Figuras
	kit._3dsLoad("kitt.3ds");	
	//kit.VertexNormals();
	
	llanta._3dsLoad("k_rueda.3ds");


	objCamera.Position_Camera(10,2.5f,13, 10,2.5f,10, 0, 1, 0);

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}



void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(900.0, 900.0, 900.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();

		

			//Para que el comando glColor funcione con iluminacion
			glEnable(GL_COLOR_MATERIAL);
			
			//glPushMatrix(); //Flecha
			//	glScalef(7,0.1,7);
			//	glDisable(GL_LIGHTING);
			//	fig3.prisma_anun(text3.GLindex, 0);
			//	glEnable(GL_LIGHTING);
			//glPopMatrix();

			//glPushMatrix(); //Camino1
			//	glTranslatef(23.5,0.0,0.0);
			//	glScalef(40,0.1,7);
			//	glDisable(GL_LIGHTING);
			//	fig3.prisma2(text4.GLindex, 0);
			//	glEnable(GL_LIGHTING);
			//glPopMatrix();

		//	glPushMatrix(); //Cama
		//	glTranslatef(23.5,0.0,10.0);
		//	glScalef(10.0,10.0,10.0);
		//	glDisable(GL_LIGHTING);
		//	fig3.prisma2(text4.GLindex, 0);
		//	glEnable(GL_LIGHTING);
		//glPopMatrix();


			//glPushMatrix(); //Camino2
			//	glTranslatef(-23.5,0.0,0.0);
			//	glScalef(40,0.1,7);
			//	glDisable(GL_LIGHTING);
			//	fig3.prisma2(text4.GLindex, 0);
			//	glEnable(GL_LIGHTING);
			//glPopMatrix();

			//glPushMatrix(); //Pasto
			//	glTranslatef(0.0,0.0,-4.0);
			//	glScalef(87,0.1,1);
			//	glDisable(GL_LIGHTING);
			//	fig4.prisma2(text5.GLindex, 0);
			//	glEnable(GL_LIGHTING);
			//glPopMatrix();

			glPushMatrix(); //Pasto
				glTranslatef(-100.0,-20.0,-80.0);
				glScalef(240,0.1,180);
				glDisable(GL_LIGHTING);
				fig4.prisma2(text16.GLindex, text16.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();





			glPushMatrix(); //Casa01
				glRotatef(90, 1, 0, 0);
				glScalef(10, 10.0, 10.0);
				glDisable(GL_LIGHTING);
				fig5.prisma3(text3.GLindex, text3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix(); //Ventana
			glTranslatef(24.0, -4.0, -10.0); //x,y,z
			glRotatef(90, 1, 0, 0);
			glScalef(3.2, 0.001, 3.2); //(x,z,y)
			glDisable(GL_LIGHTING);
			fig5.prisma2(text15.GLindex, text15.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();
			glPushMatrix(); 
			glTranslatef(30.4, -4.0, -10.0); //x,y,z
			glRotatef(90, 1, 0, 0);
			glScalef(3.2, 0.001, 3.2); //(x,z,y)
			glDisable(GL_LIGHTING);
			fig5.prisma2(text15.GLindex, text15.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix(); //Ventana
			glTranslatef(53.0, -4.0, -10.0); //x,y,z
			glRotatef(90, 1, 0, 0);
			glScalef(3.2, 0.001, 3.2); //(x,z,y)
			glDisable(GL_LIGHTING);
			fig5.prisma2(text15.GLindex, text15.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();
			glPushMatrix(); 
			glTranslatef(59.4, -4.0, -10.0); //x,y,z
			glRotatef(90, 1, 0, 0);
			glScalef(3.2, 0.001, 3.2); //(x,z,y)
			glDisable(GL_LIGHTING);
			fig5.prisma2(text15.GLindex, text15.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix(); //Puerta
			glTranslatef(40.0, -10.0, -9.9); //x,y,z
			glRotatef(90, 1, 0, 0);
			glScalef(5.0, 0.001, 5.0); //(x,z,y)
			glDisable(GL_LIGHTING);
			fig5.prisma2(text14.GLindex, text14.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();



			glPushMatrix(); //Contorno Tejado 1
				glRotatef(90, 1, 0, 0);
				glScalef(10, 10.0, 10.0);
				glDisable(GL_LIGHTING);
				fig5.prisma4(text4.GLindex, text4.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix(); //Tejado 1
				glRotatef(90, 1, 0, 0);
				glScalef(10, 10.0, 10.0);
				glDisable(GL_LIGHTING);
				fig5.prisma5(text2.GLindex, text2.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix(); //Casa02
				glTranslatef(50.1, 0.0, -24.0);
				glRotatef(90, 1, 0, 0);
				glScalef(10, 6.0, 10.0); //x,z,y 50, 28.8, 27.5
				glDisable(GL_LIGHTING);
				fig5.prisma3(text3.GLindex, text3.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();


			glPushMatrix(); //Contorno Tejado 2
			glTranslatef(50.1, 0.0, -24.0);
			glRotatef(90, 1, 0, 0);
			glScalef(10, 6.0, 10.0);
			glDisable(GL_LIGHTING);
			fig5.prisma4(text4.GLindex, text4.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();




			glPushMatrix(); //Tejado
			glTranslatef(50.1, 0.0, -24.0);
			glRotatef(90, 1, 0, 0);
			glScalef(10, 6.0, 10.0);
			glDisable(GL_LIGHTING);
			fig5.prisma5(text2.GLindex, text2.GLindex);
			glEnable(GL_LIGHTING);
			glPopMatrix();

			//glPushMatrix(); //Cochera
			//glTranslatef(130.0, -10.0, 0.0); //x,y,z
			//glRotatef(90, 0, 1, 0);
			//glRotatef(90, 1, 0, 0);
			//glScalef(4.0, 10.0, 5.0);
			//glDisable(GL_LIGHTING);
			//fig5.prisma3(text3.GLindex, text3.GLindex);
			//glEnable(GL_LIGHTING);
			//glPopMatrix();

			//glPushMatrix(); //Contorno Cochera 2
			//glTranslatef(130.0, -10.0, 0.0); //x,y,z
			//glRotatef(90, 0, 1, 0);
			//glRotatef(90, 1, 0, 0);
			//glScalef(4.0, 10.0, 5.0);
			//glDisable(GL_LIGHTING);
			//fig5.prisma4(text4.GLindex, text4.GLindex);
			//glEnable(GL_LIGHTING);
			//glPopMatrix();

			//glPushMatrix(); //Tejado cochera
			//glTranslatef(130.0, -10.0, 0.0); //x,y,z
			//glRotatef(90, 0, 1, 0);
			//glRotatef(90, 1, 0, 0);
			//glScalef(4.0, 10.0, 5.0);
			//glDisable(GL_LIGHTING);
			//fig5.prisma5(text2.GLindex, text2.GLindex);
			//glEnable(GL_LIGHTING);
			//glPopMatrix();
			


			//CUARTO BART
			glScalef(1.5, 1.5, 1.5); //(x,z,y) 19.5,12,9
			glTranslatef(-86.6, -1.8, -38.4); //x,y,z menos para abajo
			glPushMatrix();
				glPushMatrix(); //Cuarto-Bart
				glTranslatef(120.0, 0.0, 0.0);
				glRotatef(90, 1, 0, 0);
				glScalef(6.5, 4, 3); //(x,z,y) 13,8,6
				glDisable(GL_LIGHTING);
				fig5.prisma2(text5.GLindex, text5.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Piso-Bart
				glTranslatef(120.05, -5.82, 0.05); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(6.45, 3.9, 0.05); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text6.GLindex, text6.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Cama-Bart
				glTranslatef(120.4, -4.39, 0.05); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(3.2, 1.6, 0.7); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text7.GLindex, text7.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Cabecera-cama
				glTranslatef(120.17, -2.5, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.15, 1.6, 1.6); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text8.GLindex, text8.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Poste-izq-cama
				glTranslatef(120.17, -1.8, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.15, 0.15, 2.0); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text8.GLindex, text8.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Poste-izq-esfera
				glTranslatef(120.3, -1.65, 0.235); //x,y,z
				glRotatef(90, 1, 0, 0);
				glDisable(GL_LIGHTING);
				fig7.esfera (0.15,20,20,text8.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Poste-der-cama
				glTranslatef(120.17, -1.8, 2.950); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.15, 0.15, 2.0); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text8.GLindex, text8.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Poste-der-esfera
				glTranslatef(120.3, -1.65, 3.110); //x,y,z
				glRotatef(90, 1, 0, 0);
				glDisable(GL_LIGHTING);
				fig1.esfera(0.15, 20, 20,text6.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();


				glPushMatrix(); //Poster
				glTranslatef(121.3, -0.95, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.0, 0.001, 1.2); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text11.GLindex, text11.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();



				glPushMatrix(); //Ventana
				glTranslatef(124.5, -0.95, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.6, 0.001, 1.4); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text17.GLindex, text17.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();



				glTranslatef(-1.5, 0.0, 0.0); //x,y,z
				glPushMatrix(); //LIBRERO
			
				glPushMatrix(); //Librero
				glTranslatef(130.1, -1.05, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.4, 0.1, 2.4); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Librero_izq
				glTranslatef(130.1, -1.05, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.1, 0.4, 2.4); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();


				glPushMatrix(); //Librero_der
				glTranslatef(132.7, -1.05, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.1, 0.4, 2.4); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Librero_top
				glTranslatef(130.1, -1.05, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.4, 0.4, 0.06); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Librero_repisa-1
				glTranslatef(130.305, -2.1, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.2, 0.4, 0.06); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Librero_repisa-2
				glTranslatef(130.305, -3.3, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.2, 0.4, 0.06); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Librero_repisa-2
				glTranslatef(130.305, -4.5, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.2, 0.4, 0.06); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Librero_repisa-3
				glTranslatef(130.305, -5.7, 0.075); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(1.2, 0.4, 0.06); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text9.GLindex, text9.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();
				glPopMatrix(); //TERMINA LIBRERO

				glPushMatrix(); //boliche
				glTranslatef(130.4, -4.5, 1.575); //x,y,z
				glRotatef(90, 1, 0, 0);
				glDisable(GL_LIGHTING);
				fig1.esfera(0.6, 20, 20, text18.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Escritorio back
				glTranslatef(132.8, -4.0, 1.175); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.05, 2.0, 0.9); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text13.GLindex, text13.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Escritorio cajones izq
				glTranslatef(131.5, -4.0, 1.175); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.65, 0.5, 0.9); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text13.GLindex, text13.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Escritorio cajones der
				glTranslatef(131.5, -4.0, 4.175); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.65, 0.5, 0.9); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text13.GLindex, text13.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix(); //Escritorio tapa
				glTranslatef(131.45, -4.0, 1.175); //x,y,z
				glRotatef(90, 1, 0, 0);
				glScalef(0.7, 2.0, 0.05); //(x,z,y)
				glDisable(GL_LIGHTING);
				fig5.prisma2(text13.GLindex, text13.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();
			glPopMatrix();




			

		glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
		glColor3f(1.0,0.0,0.0);
		pintaTexto(-12,12.0,-14.0,(void *)font,"Proyecto Final");
		pintaTexto(-12,10.5,-14,(void *)font,"Modelo 3D Animado");
		glColor3f(1.0,1.0,1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;


	if(g_fanimacion)
	{
		movKit +=1.0;
	}

	if (g_fanimacion)
	{
		rotKit += 1.0;
	}

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 870.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+1.0 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+1.0));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+1.0));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+1.0 );
			break;

		case 't':   //Movimientos de camara
		case 'T':
			objCamera.Move_Camera(CAMERASPEED + 0.2);
			break;

		case 'g':
		case 'G':
			objCamera.Move_Camera(-(CAMERASPEED + 0.2));
			break;

		case 'f':
		case 'F':
			objCamera.Strafe_Camera(-(CAMERASPEED + 0.2));
			break;

		case 'h':
		case 'H':
			objCamera.Strafe_Camera(CAMERASPEED + 0.2);
			break;

		case ' ':		//Poner algo en movimiento
			g_fanimacion^= true; //Activamos/desactivamos la animacíon
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED*.7);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED*.7);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 10"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}
