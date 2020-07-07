#include <cstdio>
#include<GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include<math.h>
#include<iostream>
using namespace std;
GLuint textureID[6];
GLuint bit=54;

// Data read from the header of the BMP file
unsigned char header[54]; // Each BMP file begins by a -bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
// Actual RGB data
unsigned char * data;

//BOOL PlaySound(LPCTSTR pszSound,   HMODULE hmod,   DWORD   fdwSound);~PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
//PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
///

//  angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera’s direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;


GLfloat position = -10.0f;
GLfloat position1 = -10.0f;
GLfloat position2 = -10.0f;
GLfloat speed = 0.1f;
GLfloat speed1 = 0.1f;
GLfloat speed2 = 0.1f;

GLfloat day=1.0f;
GLfloat daycloud=0.0f;
GLfloat dayspeed=0.01f;
GLfloat dayspeed2=0.5f;

GLfloat binaru=0;
GLfloat positionxcloud = -30.0f;
///

GLuint loadBMP_custom(const char * imagepath)
{
// Open the file

FILE * file = fopen(imagepath,"rb");
if (!file){printf("Image could not be opened\n"); return 0;}
if ( fread(header, 1, bit, file)!=bit ){ // If not  bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
}
if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
}
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);

// Some BMP files are misformatted, guess missing information
if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
if (dataPos==0)      dataPos=bit; // The BMP header is done that way

// Create a buffer
data = new unsigned char [imageSize];

// Read the actual data from the file into the buffer
fread(data,1,imageSize,file);

//Everything is in memory now, the file can be closed
fclose(file);
   ///glGenTextures(1, &texName);
   glGenTextures(1, &textureID[0]);
   ///glBindTexture(GL_TEXTURE_2D, texName);
   // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID[0]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
//glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP,GL_TRUE);
// Generate mipmaps, by the way.
//glGenerateMipmap(GL_TEXTURE_2D);
//    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
}

GLuint init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

    ///makeCheckImage();
    char maps[][20] = {"grass.bmp","21FEB.bmp"};
  // GLuint Texture //= loadBMP_custom(maps[0]);
   ///glPixelStorei(GL_UNPACK_ALIGNMENT, 1);



   /// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
///    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   }



///
void update(int value) {

    if(position > 50.0)
        position = -50.0f;

    position += speed;

    if(position1 > 50.0)
        position1 = -50.0f;

    position1 += speed1;

    if(positionxcloud > 60.0)
        positionxcloud = -50.0f;

    positionxcloud += speed2;



    //if(positio=)
    if(day>1)
    {day=0.8;
    glutPostRedisplay();
     day=0.6;
         glutPostRedisplay();
     day=0.4;
         glutPostRedisplay();
     day=0.2;
         glutPostRedisplay();
     day=0.0;
    }

    day+=dayspeed;





glutPostRedisplay();


if(daycloud<=1)
    {daycloud+=dayspeed2;
    glutPostRedisplay();

   }
   else
daycloud=0;
glutPostRedisplay();



glutTimerFunc(100, update, 0);
}




/////////////////////////////////sun//////////////////////////////////////////
void cloud()
{
      glColor4f(1, 1, 1,day) ;


     //glEnable ( GL_LIGHTING ) ;

   glPushMatrix();
        glTranslated(4+positionxcloud,70,23.5);
       glutSolidSphere(3,30,30);
   glPopMatrix();

    glPopMatrix();
        glPushMatrix();
        glTranslated(4+positionxcloud,70,25);
       glutSolidSphere(2,30,34);
    glPopMatrix();

     glPopMatrix();
        glPushMatrix();
        glTranslated(1+positionxcloud,70,24);
       glutSolidSphere(2,30,34);
    glPopMatrix();
  glPushMatrix();
        glTranslated(7+positionxcloud,72,25);
       glutSolidSphere(2.5,30,30);
   glPopMatrix();


//glutWireSphere(3,30,16);
//glutSolidSphere(2,30,30);


}


void drawSun()
{
     //glEnable ( GL_LIGHTING )

       glPushMatrix();
      glColor3f ( .97f, 0.84f, 0.109f ) ;
      glTranslatef(0,50,20);

      glutSolidSphere(1,20,20);

glPopMatrix();

}

////////////////////////////////////////thr conr sky.////////////////////////////////////////

void drawSky()
{
    glColor4f(0,0,0,day);
    glTranslatef(0,1,-100);
    glRotated(90,-1,0,0);
    glutSolidSphere(90,50,50);

}

/////////////////////////////////////A CAR//////////////////////////////////////////

void  drawCarBody()
{
    //GLboolean false;

            glColor3f(1,0,0);
            glTranslatef(-.2,-0.02,0);

            for(int j=0;j<16;j++)
            {
                 for(int i=0;i<8;i++)
            {

            glTranslated(0,0,0.1);
            glutSolidCube(.1);
            }
            glTranslatef(0.1,0,-0.8);


            }
            glTranslatef(-1.6,0.1,0);

              glColor3f(.1,1,1);
            for(int j=0;j<16;j++)
            {
                 for(int i=0;i<8;i++)
            {

            if(j==0&&i==1||j==0&&i==6)
                glColor4f(1,1,1,daycloud);
            else
                glColor3f(1,0,0);



            glTranslated(0,0,0.1);
            glutSolidCube(.1);

            }
            glTranslatef(0.1,0,-0.8);


            }
            glTranslatef(-1.6,0.1,0);

             glColor3f(1,0,0);


            for(int j=0;j<16;j++)
            {
                 for(int i=0;i<8;i++)
            {

            glTranslated(0,0,0.1);
            glutSolidCube(.1);
            }
            glTranslatef(0.1,0,-0.8);


            }
            glTranslatef(-1.4,0.1,0);
            glColor3f(.6,0,0);
             for(int j=0;j<13;j++)
            {
                 for(int i=0;i<8;i++)
            {

            glTranslated(0,0,0.1);
            glutSolidCube(.1);
            }
            glTranslatef(0.1,0,-0.8);


            }
            glTranslatef(-1.3,0.1,0);

            for(int j=0;j<13;j++)
            {
                 for(int i=0;i<8;i++)
            {

            glTranslated(0,0,0.1);
            glutSolidCube(.1);
            }
            glTranslatef(0.1,0,-0.8);


            }

             glTranslatef(-1.3,0.1,0);

             for(int j=0;j<13;j++)
            {
                 for(int i=0;i<8;i++)
            {

            glTranslated(0,0,0.1);
            glutSolidCube(.1);
            }
            glTranslatef(0.1,0,-0.8);


            }

            glTranslatef(-1.3,0.1,0);

             for(int j=0;j<13;j++)
            {
                 for(int i=0;i<8;i++)
            {

            glTranslated(0,0,0.1);
            glutSolidCube(.1);
            }
            glTranslatef(0.1,0,-0.8);


            }


}

void drawTire()
{
    glColor3f(.1,.1,.1);
    //glRotated(90,0,1,0);
    glutSolidCone(.2,.9,15,15);
    glColor3f(1,1,1);
    glutSolidCone(.18,.9,15,15);

    glTranslatef(0,0,.9);
    glColor3f(.1,.1,.1);
        glRotated(180,0,1,0);
    glutSolidCone(.2,.9,15,15);
    glColor3f(1,1,1);
    glutSolidCone(.18,.9,15,15);
}

void drawCar()
{

    glTranslatef(0,-0.7,-0.01);

    drawTire();
    glTranslatef(1,0,0);
    drawTire();
    glTranslatef(0,0.2,0);
    drawCarBody();
}



/********************************************************************************************/
void drawCylinder(GLfloat radius,GLfloat height,GLboolean halfCylinder)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angleStep = .1;
    int halfPiemultiplier=0;
    if(halfCylinder)
    {
    halfPiemultiplier=1;
    }
    else
    {
    halfPiemultiplier=2;
    }

    glBegin(GL_QUAD_STRIP);

        while( angle < halfPiemultiplier*3.1415 ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angleStep;

        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();


    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < halfPiemultiplier*3.1415 ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angleStep;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}



void drawBoat()
{
glRotated(180,1,0,0);

glColor3ub(148,114,64);
drawCylinder(.5,3,true);


glRotated(180,0,1,0);
glutSolidCone(.5,1,14,14);
glTranslated(0,0,-3);
glRotated(180,0,1,0);
glutSolidCone(.5,1,14,14);
glTranslated(0,0,-1.3);
glRotated(180,1,0,0);
glColor3ub(193,154,107);
drawCylinder(.5,1,true);

}



void drawplane()
{
glColor3ub(61,80,94);

glTranslatef(0,-3,0 );
//glTranslatef(.1f,0.0f, position-8);
glRotated(90,1,0,0);
drawCylinder(.1,1.2,false);
glTranslatef(0,3,0 );

glTranslatef(0,-3,.5 );
glColor3ub(61,80,94);
glRotated(70,0,1,0);
glutSolidCone(.07,.9,15,15);
//glTranslatef(0,3,-.5 );


glTranslatef(-.05,0,-.1);
glRotated(250,0,1,0);
glutSolidCone(.08,.9,15,15);

}


////////////////////////////////////////////////////////////////////////////////////////
void drawBuilding()
{
    //vertical 1
    glColor3ub(0, 0, 0);
    glTranslatef(0 ,.75, 0);
 //   glutSolidCube(.10f);
      for(int j=0;j<2;j++)
            {
                 for(int i=0;i<13;i++)
            {

                glColor3f(0,0,0);



           glTranslatef(0 ,.1,0);
            glutWireCube(1.5);
            }

           // glTranslatef(0.0,0,0.0);
            }


glColor3ub( 255, 255, 255);
 glTranslatef(.9 ,.7, -.8);
      for(int j=0;j<1;j++)
            {
                 for(int i=0;i<18;i++)
            {



           glTranslatef(-.1 ,0, 0);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

// glTranslatef(-.7 ,0, -.6);

      for(int j=0;j<1;j++)
            {
                 for(int i=0;i<17;i++) //down height
            {



           glTranslatef(0 ,0, .1);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }


            //new
               for(int j=0;j<1;j++)
            {
                 for(int i=0;i<18;i++) //down height
            {
           glTranslatef(.1 ,0, 0);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }



            //new
               for(int j=0;j<1;j++)
            {
                 for(int i=0;i<17;i++) //down height
            {



           glTranslatef(0 ,0, -.1);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }



            // Building

  glTranslatef(-.9 ,-3.3, .8);
 //   glutSolidCube(.10f);
      for(int j=0;j<2;j++)
            {
                 for(int i=0;i<13;i++)
            {

              glColor3ub(203, 65, 84);



           glTranslatef(0 ,.1,0);
            glutSolidCube(1.5);
            }

           // glTranslatef(0.0,0,0.0);
            }

  glTranslatef(.701 ,.4, 1);
 glColor3ub(255, 255, 255);

     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

              glTranslatef(0 ,-.4, 1.57);
 glColor3ub(255, 255, 255);

     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

            ///
              glTranslatef(0 ,-.4, 1.59);
 glColor3ub(255, 255, 255);

     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

///
              glTranslatef(0 ,-.4, 1.6);
 glColor3ub(255, 255, 255);

     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }
///
              glTranslatef(0 ,-.4, 1.62);
 glColor3ub(255, 255, 255);

     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }
///
              glTranslatef(0 ,-.4, 1.63);
 glColor3ub(255, 255, 255);

     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }
            ////
              glTranslatef(0 ,-.4, 1.62);
 glColor3ub(255, 255, 255);

     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }
            ////
              glTranslatef(0 ,-.4, 1.61);


     for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }
            ////
 glTranslatef(0 ,-.4, 1.61);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1) //down height
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

            //left Door ***************************
 glTranslatef(-.15 ,-.26, 0.6);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<1;i+=1)
            {



           glTranslatef(0 ,0, -.1);
            glutSolidCube(.4);
            }
            glTranslatef(0.0,0,0.0);
            }


//Right Door
 glTranslatef(-1.102 ,0.01, 0.2);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<1;i+=1) //down height
            {



           glTranslatef(0 ,0, -.1);
            glutSolidCube(.4);
            }
            glTranslatef(0.0,0,0.0);
            }


////RIght window

 glTranslatef(-.15 ,.5, .95);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1)
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }


 glTranslatef(0 ,.5, 1.57);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1)
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

 glTranslatef(0 ,.5, 1.6);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1)
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }


 glTranslatef(0 ,.5, 1.65);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1)
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }
 glTranslatef(0 ,.5, 1.6);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1)
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }


 glTranslatef(0 ,.5, 1.6);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1)
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

 glTranslatef(0 ,.5, 1.6);
 for(int j=0;j<1;j++)
            {
                 for(int i=0;i<4;i+=1)
            {



           glTranslatef(0 ,0, -.4);
            glutSolidCube(.1);
            }
            glTranslatef(0.0,0,0.0);
            }

}


void branch(){
    glRotatef(-90, 1, 0, 0);
     glTranslatef(0,0,-.3);
    ///////
      glColor3ub(103, 55, 40);
  //  glRotatef(-90, 1, 0, 0);
    glutSolidCone(.1,4,15,15);
}

void tree()
{

glRotatef(-90, 1, 0, 0);
     glColor3ub(41, 147, 39);
   // glRotatef(-90, 1, 0, 0);
    glutSolidCone(.5,1,15,15);
    glColor3ub(103, 55, 40);
    glutSolidCone(.18,1,15,15);

    glTranslatef(0,0,.5);
    glColor3f(.1,.1,.1);

     glColor3ub(41, 147, 39);
  //  glRotatef(-90, 1, 0, 0);
    glutSolidCone(.5,.5,15,15);
    glColor3f(1,1,1);
    glutSolidCone(.18,.5,15,15);

   // glTranslatef(0,1,0);
    glColor3f(.1,.1,.1);

    glTranslatef(0,0,.3);
    ///////
      glColor3ub(41, 147, 39);
  //  glRotatef(-90, 1, 0, 0);
    glutSolidCone(.5,.5,15,15);
//glRotatef(90, 1, 0, 0);
 //glutSolidTorus (.1,1,12,3);

glRotatef(-90, 1, 0, 0);
branch();


}


void tree1()
{

 glTranslatef(0,.1,0);
     glColor3ub(41, 147, 39);
   // glRotatef(-90, 1, 0, 0);
    glutSolidSphere(.5,7,15);
    glColor3ub(103, 55, 40);

    glColor3ub(41, 147, 39);
   // glRotatef(-90, 1, 0, 0);
    glutSolidSphere(.6,8,15);
    glColor3ub(103, 55, 40);

glRotatef(-90, 1, 0, 0);

glRotatef(-90, 1, 0, 0);
branch();


}

void drawroadlightleft(){

glColor3ub(255,255,255);
glTranslated(.5,-.5,1); //x,z,y
glRotated(90,1,0,0);
drawCylinder(.01,.50,false);

glTranslated(0,0,0.02); // x ,z,y
glRotated(90,0,1,0);
drawCylinder(.01,.20,false);

glRotated(90,0,1,0);
glTranslated(-.15,-.038,-.09); //x,z,y
glutSolidCone(.03,.1,14,12);

//light ray
glColor4f(1,1,0,.2);
glTranslated(0,0,-.4);
glutSolidCone(.09,.5,14,12);

}

void drawroadlightright(){

glColor3ub(255,255,255);
glTranslated(.5,-.5,1); //x,z,y
glRotated(90,1,0,0);
drawCylinder(.01,.50,false);
//ver
glTranslated(-.2,0,0.02); // x ,z,y
glRotated(90,0,1,0);
drawCylinder(.01,.20,false);
//light
glRotated(90,0,1,0);
glTranslated(-.05,-.038,-.09); //x,z,y
glutSolidCone(.03,.1,14,12);

//light ray
glColor4f(1,1,0,.2);
glTranslated(0,0,-.4);
glutSolidCone(.09,.5,14,12);

}

void drawCustomBox(float x,float y,float z,bool activateFront,bool activateBack,bool activateBottom,bool activateTop,bool activateRight,bool activateLeft)
{
////Comment out the colours
glColor3f(.698,0,0);
glBegin(GL_QUADS);
if(activateBottom)
{
//bottom
glVertex3f(-x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,y*.5,-z*.5);
glVertex3f( x*.5,y*.5,-z*.5);
glVertex3f( x*.5,-y*.5,-z*.5);

}

if(activateFront)
{
glColor3f(0,.698,0);

//////Front
glVertex3f( x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,-y*.5,z*.5);
glVertex3f(x*.5,-y*.5,z*.5);


}

if(activateRight)
{
glColor3f(0,0,.698);
//////Right
glVertex3f(x*.5,-y*.5,-z*.5);
glVertex3f(x*.5,-y*.5,z*.5);
glVertex3f(x*.5,y*.5,z*.5);
glVertex3f(x*.5,y*.5,-z*.5);

}

if(activateBack)
{
glColor3f(.5,.5,.5);
//Back
glVertex3f(x*.5,y*.5,z*.5);
glVertex3f(-x*.5,y*.5,z*.5);
glVertex3f(-x*.5,y*.5,-z*.5);
glVertex3f(x*.5,y*.5,-z*.5);

}
if(activateTop)
{
//////Top
glColor3f(0,0.698,.698);
glVertex3f(-x*.5,-y*.5,z*.5);
glVertex3f(-x*.5,y*.5,z*.5);
glVertex3f( x*.5,y*.5,z*.5);
glVertex3f( x*.5,-y*.5,z*.5);

}
if(activateLeft)
{
glColor3f(0.698,.698,0);
////////left
glVertex3f(-x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,-y*.5,z*.5);
glVertex3f(-x*.5,y*.5,z*.5);
glVertex3f(-x*.5,y*.5,-z*.5);

}

glEnd();

}

void drawBox(float x,float y,float z,bool activateFront,bool activateBack,bool activateBottom,bool activateTop,bool activateRight,bool activateLeft)
{
////Comment out the colours
//glColor3f(.698,0,0);
glBegin(GL_QUADS);
if(activateBottom)
{
//bottom
glVertex3f(-x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,y*.5,-z*.5);
glVertex3f( x*.5,y*.5,-z*.5);
glVertex3f( x*.5,-y*.5,-z*.5);

}

if(activateFront)
{
//glColor3f(0,.698,0);

//////Front
glVertex3f( x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,-y*.5,z*.5);
glVertex3f(x*.5,-y*.5,z*.5);


}

if(activateRight)
{
//glColor3f(0,0,.698);
//////Right
glVertex3f(x*.5,-y*.5,-z*.5);
glVertex3f(x*.5,-y*.5,z*.5);
glVertex3f(x*.5,y*.5,z*.5);
glVertex3f(x*.5,y*.5,-z*.5);

}

if(activateBack)
{
//glColor3f(.5,.5,.5);
//Back
glVertex3f(x*.5,y*.5,z*.5);
glVertex3f(-x*.5,y*.5,z*.5);
glVertex3f(-x*.5,y*.5,-z*.5);
glVertex3f(x*.5,y*.5,-z*.5);

}
if(activateTop)
{
//////Top
//glColor3f(0,0.698,.698);
glVertex3f(-x*.5,-y*.5,z*.5);
glVertex3f(-x*.5,y*.5,z*.5);
glVertex3f( x*.5,y*.5,z*.5);
glVertex3f( x*.5,-y*.5,z*.5);

}
if(activateLeft)
{
//glColor3f(0.698,.698,0);
////////left
glVertex3f(-x*.5,-y*.5,-z*.5);
glVertex3f(-x*.5,-y*.5,z*.5);
glVertex3f(-x*.5,y*.5,z*.5);
glVertex3f(-x*.5,y*.5,-z*.5);

}

glEnd();

}

void drawTriangle3d(GLfloat lengthX,GLfloat lengthY,GLfloat baseshiftX,GLfloat baseshiftY,GLfloat lengthThick,GLfloat thickShift0,GLfloat thickShiftX,GLfloat thickShiftY,GLboolean triangle1Remove,GLboolean triangle2Remove,GLboolean sideX_Remove,GLboolean sideY_Remove,GLboolean sideHYP_Remove)
{
float length,width,thickness;

glBegin(GL_TRIANGLES);
if(triangle1Remove)
{}
else
{
glColor3f(.5,0,0);
glVertex3f(0+baseshiftX,0+baseshiftY,-lengthThick+(thickShift0*.1));
glVertex3f(lengthX,0,-lengthThick+(thickShiftX*0.1));
glVertex3f(0,lengthY,-lengthThick+(thickShiftY*0.1));

}

if(triangle2Remove)
{}
else
{
glColor3f(0,.6,.5);
glVertex3f(0+baseshiftX,0+baseshiftY,lengthThick-(thickShift0*.1));
glVertex3f(lengthX,0,lengthThick-(thickShiftX*0.1));
glVertex3f(0,lengthY,lengthThick-(thickShiftY*0.1));

}


glEnd();
glBegin(GL_QUADS);

if(sideX_Remove)
{}
else
{
glColor3f(.5,.9,.5);
glVertex3f(0+baseshiftX,0+baseshiftY,-lengthThick+(thickShift0*.1));
glVertex3f(0+baseshiftX,0+baseshiftY,lengthThick-(thickShift0*.1));
glVertex3f(lengthX,0,lengthThick-(thickShiftX*0.1));
glVertex3f(lengthX,0,-lengthThick+(thickShiftX*0.1));

}
if(sideHYP_Remove)
{}
else
{
glColor3f(.5,.3,.5);
glVertex3f(lengthX,0,-lengthThick+(thickShiftX*0.1));
glVertex3f(lengthX,0,lengthThick-(thickShiftX*0.1));
glVertex3f(0,lengthY,lengthThick-(thickShiftY*0.1));
glVertex3f(0,lengthY,-lengthThick+(thickShiftY*0.1));
}
if(sideY_Remove)
{}
else
{
glColor3f(0,0,.5);
glVertex3f(0,lengthY,-lengthThick+(thickShiftY*0.1));
glVertex3f(0,lengthY,lengthThick-(thickShiftY*0.1));
glVertex3f(0+baseshiftX,0+baseshiftY,lengthThick-(thickShift0*.1));
glVertex3f(0+baseshiftX,0+baseshiftY,-lengthThick+(thickShift0*.1));

}
glEnd();



}
//car **************************************************
void carframe(){
    glRotated(90,0,1,0);

    glTranslated(-.5,.2,.06);
    drawCustomBox(.5,.2,.44,true,true,true,true,true,true);  //z , y, x
    glRotated(90,0,0,1);
    glTranslated(-.13,.25,0);
    drawTriangle3d(.23,0,0,.1,.212,0,0,0,false,false,false,false,false);  //z
//glRotated(90,0,0,1);
   // glTranslated(-.6,-.2,0);  // , y , z
    //drawTriangle3d(.2,1,.3,0,.2,0,0,0,false,false,false,false,false);  //z ,
}
void cartorus(){
    glColor3ub(128,128,128);
    glRotated(90,0,1,0);
    glTranslated(0,-.8,0); //z,y,x
    glutSolidTorus(.04,.09,40,150);

    glTranslated(1.5,0,0);  //z
    glutSolidTorus(.04,.09,40,150);

    glTranslated(0,0,.5);  //z,y,x
    glutSolidTorus(.04,.09,40,150);

    glTranslated(-1.5,0,0);  //z,y,x
    glutSolidTorus(.04,.09,40,150);

    glTranslated(.9,.1,-.25);
    drawCustomBox(2,.1,.42,true,true,true,true,true,true);

    glRotated(270.2,0,1,0);
    glTranslated(-.08,0,.1); // x , y , z
    carframe();

}

void hill()
{
    glColor3ub(15,114,22);
    glRotated(240,1,1,1);
    glutSolidCone(1,1.6,14,15);
    glColor3ub(71,182,37);
    glTranslated(0,0.7,0);
    glutSolidCone(1,1,14,15);
    glColor3ub(208,176,45);
    glTranslated(0,0.5,0);
    glutSolidCone(.8,0.5,14,15);

}

void railine(){
    glColor3ub(118,126,132);

    glTranslated(0,-.97,-5);
    drawCylinder(.009,8,false);

    glTranslated(.5,0,0);
    drawCylinder(.009,8,false);

//ver
    glColor3ub(150,120,83);
    glRotated(280,0,1,0);
    glTranslated(.18,-.02,0);
    drawCylinder(.03,.6,false);

    glTranslated(1.2,0,.18);
    drawCylinder(.03,.6,false);

    glTranslated(1.2,0,.21);
    drawCylinder(.03,.6,false);

    glTranslated(1.2,0,.23);
    drawCylinder(.03,.6,false);

    glTranslated(1.2,0,.22);
    drawCylinder(.03,.6,false);

    glTranslated(1.2,0,.22);
    drawCylinder(.03,.6,false);

    glTranslated(1.2,0,.22);
    drawCylinder(.03,.6,false);
}
void rail(){
    //wheel
    glColor3ub(150,120,83);
    glTranslated(0,-.91,1);
    glRotated(120,1,1,1);

    glutSolidTorus(.011,.04,17,20);
    glTranslated(0,-1.2,0);
    glutSolidTorus(.011,.04,17,20);

    glTranslated(0,0,.5);
    glutSolidTorus(.011,.04,17,20);

    glTranslated(0,1.2,0);
    glutSolidTorus(.011,.04,17,20);

    glTranslated(.5,-.7,-.25);  //  y ,z,x
    drawCustomBox(.9,1.5,.6,true,true,true,true,true,true);  //y z x

    //white strip  rgb(84,59,50)
     glColor3ub(84,59,50);
    glTranslated(-.33,.77,-.299);  // y z x
    drawCylinder(.015,.6,false);
    glTranslated(.1,0,0);
    drawCylinder(.015,.6,false);
    glTranslated(.7,0,.03);
    drawCylinder(.02,.55,false);

    glRotated(280,1,0,0);
    glTranslated(-.04,0,0);
    drawCylinder(.02,.1,false);
glRotated(0,0,0,0);
    glTranslated(0,-.23,.1);
    drawCylinder(.02,.1,false);


    glTranslated(0,-0.3,0);
    drawCylinder(.02,.1,false);
    //light
glColor3ub(255,255,255);
    glRotated(180,1,0,0);
    glTranslated(-.3,-.25,0);
    glutSolidCone(.04,.1,18,13);

    glColor4f(1,1,0,.4);
    glRotated(0,0,0,0);
    glTranslated(0,0,-.9);
    glutSolidCone(.2,1,18,13);

    glColor3ub(255,255,255);
    glRotated(90,0,1,0);
    glTranslated(-1.4,.1,.1);
    drawCylinder(.08,.4,false);

    glRotated(0,0,0,0);
    glTranslated(-.4,0,.02);
    drawCylinder(.08,.4,false);
glColor3ub(84,59,50);
    glRotated(180,1,1,0);
    glTranslated(0,0,-.4);
    glutSolidTorus(.02,.11,17,20);
//wheel
    glColor3ub(150,120,83);
    glRotated(90,0,1,0);
    glTranslated(-1.15,-1.3,.55);  //y,z  x
    glutSolidTorus(.011,.04,17,20);

    glRotated(0,0,0,0);
    glTranslated(0,-.9,.14);  //y,z  x
    glutSolidTorus(.011,.04,17,20);

    glTranslated(0,-1,.19);  //y,z  x
    glutSolidTorus(.011,.04,17,20);

    glTranslated(0,-1.3,.23);  //y,z  x
    glutSolidTorus(.011,.04,17,20);


    glTranslated(0,-1,.23);  //y,z  x
    glutSolidTorus(.011,.04,17,20);


    glTranslated(0,-1,.238);  //y,z  x
    glutSolidTorus(.011,.04,17,20);


    glRotated(80,1,0,0);
    glTranslated(.39,-.36,-5);  //y x z
    drawCustomBox(.7,.5,1.9,true,true,true,true,true,true);

    glColor3ub(181,161,63);
    glTranslated(0,0,1.3);
    drawCylinder(.45,2.5,false);

    glTranslated(.11,.2,3.2);
    drawCustomBox(.87,.5,1.3,true,true,true,true,true,true);


}


GLdouble a,b,c;

void NewBoat()
{
    /////////////base
   glBegin(GL_POLYGON);//base back
  glColor3f(1, 0, 0);
  glVertex3f(-0.7, 0.3,0.0);
     glVertex3f(-0.5, 0, 0.0);
     glVertex3f(0.5, 0.0, .0);
     glVertex3f(0.7, 0.3, .0);
  glEnd();

glColor3f(1,0, 0);//base up
glBegin(GL_POLYGON);
glVertex3f(-0.7, 0.3,0.0);
glVertex3f(-0.7,0.3,1);
glVertex3f(0.7,0.3,1);
glVertex3f(0.7, 0.3,0.0);
glEnd();


 glColor3f(1,0, 0);//base front
glBegin(GL_QUADS);
glVertex3f(-0.7,0.3,1);
glVertex3f(-0.5, 0,0);
glVertex3f(0.5, 0.0,0);
glVertex3f(0.7, 0.3,1);
glEnd();

 glColor3f(1,0, 0);//base left
glBegin(GL_POLYGON);
glVertex3f(-0.7, 0.3,0.0);
glVertex3f(-0.7,0.3,1);
glVertex3f(-0.5, 0, 0.0);

glEnd();

glColor3f(1,0, 0);//base right
glBegin(GL_POLYGON);
glVertex3f(0.7, 0.3,0.0);
glVertex3f(0.7,0.3,1);
glVertex3f(0.5, 0, 0.0);

glEnd();



///////////////////////////////////base1



  glBegin(GL_QUADS);//base1 back
  glColor3f(0,1, 0);
  glVertex3f(-0.5, 0.5,0);
     glVertex3f(-0.5, 0.3, 0);
     glVertex3f(0.5, 0.3, 0);
     glVertex3f(0.5, 0.5, .0);
  glEnd();

 glColor3f(0, 1,0);//base1 front
glBegin(GL_QUADS);
glVertex3f(-0.5, 0.5,1);
glVertex3f(-0.5, 0.3,1);
glVertex3f(0.5, 0.3, 1);
glVertex3f(0.5, 0.5, 1.0);
glEnd();



glColor3f(0,1, 0);//base1 left x negtive
glBegin(GL_QUADS);
glVertex3f(-0.5, 0.5,0);
glVertex3f(-0.5, 0.3, 0);
glVertex3f(-0.5, 0.3, 1);
glVertex3f(-0.5, 0.5, 1.0);
glEnd();

glColor3f(0, 1,0);//base1 right xall positive
glBegin(GL_QUADS);
glVertex3f(0.5, 0.5, .0);
glVertex3f(0.5, 0.3, 0);
glVertex3f(0.5, 0.3, 1);
glVertex3f(0.5, 0.5, 1);
glEnd();

glColor3f(0,1, 0);//base1 top
glBegin(GL_QUADS);
glVertex3f(-0.5, 0.5,0);///back1
glVertex3f(-0.5, 0.5,1);///front1
glVertex3f(0.5, 0.5,1);///front4
     glVertex3f(0.5, 0.5, .0);///back4
glEnd();



/////////////////////////base2
 glBegin(GL_QUADS);//base2 back
  glColor3f(0, 0, 1);
   glVertex3f(-0.3, 0.6,0);
     glVertex3f(-0.3, 0.5, 0);
     glVertex3f(0.3, 0.5, 0);
     glVertex3f(0.3, 0.6, 0);

  glEnd();



   glBegin(GL_QUADS);//base2 front
  glColor3f(0, 0, 1);
   glVertex3f(-0.3, 0.6,1);
     glVertex3f(-0.3, 0.5, 1);
     glVertex3f(0.3, 0.5, 1);
     glVertex3f(0.3, 0.6, 1);

  glEnd();

  glBegin(GL_POLYGON);//base2 back
  glColor3f(0, 0, 1);
   glVertex3f(-0.3, 0.6,0);
     glVertex3f(-0.3, 0.5, 0);
      glVertex3f(0.3, 0.5, 0);
     glVertex3f(0.3, 0.6, 0);

  glEnd();

  glBegin(GL_POLYGON);//base2 front
  glColor3f(0, 0, 1);
   glVertex3f(-0.3, 0.6,1);
     glVertex3f(-0.3, 0.5, 1);
      glVertex3f(0.3, 0.5, 1);
     glVertex3f(0.3, 0.6, 1);
  glEnd();

glColor3f(0, 0,1);//base2 top
glBegin(GL_QUADS);
glVertex3f(-0.3, 0.6,0);///back1
glVertex3f(-0.3, 0.6,1);///front1
glVertex3f(0.3, 0.6, 1);///front4
     glVertex3f(0.3, 0.6, 0);///back4
glEnd();

  glColor3f(0, 0, 1);//base2 left x negative
glBegin(GL_QUADS);
glVertex3f(-0.3, 0.6,0);
glVertex3f(-0.3, 0.5, 0);
glVertex3f(-0.3, 0.5, 1);
glVertex3f(-0.3, 0.6, 1.0);
glEnd();

glColor3f(0, 0, 1);//base2 right xall positive
glBegin(GL_QUADS);
glVertex3f(0.3, 0.6, .0);
glVertex3f(0.3, 0.5, 0);
glVertex3f(0.3, 0.5, 1);
glVertex3f(0.3, 0.6, 1);
glEnd();


////////////////////////////////////////////////chminy1
   glBegin(GL_QUADS);//chminy1 back
  glColor3f(1, 0, 0);
  glVertex3f(0.05, 0.85,0);
     glVertex3f(0.05, 0.6, 0);
     glVertex3f(0.15, 0.6, 0);
    glVertex3f(0.15, 0.8, 0);

  glEnd();

   glBegin(GL_QUADS);//chminy1 front
  glColor3f(1, 0, 0);
  glVertex3f(0.05, 0.85,1);
     glVertex3f(0.05, 0.6, 1);
     glVertex3f(0.15, 0.6, 1);
    glVertex3f(0.15, 0.8, 1);

  glEnd();


  glColor3f(1, 0, 0);//chminy1 top
glBegin(GL_QUADS);
glVertex3f(0.05, 0.85,0);///back1
glVertex3f(0.05, 0.85,1);///front1
glVertex3f(0.15, 0.8, 1);///front4
    glVertex3f(0.15, 0.8, 0);///back4
glEnd();

   glColor3f(1, 0, 0);//chminy1 left x negtive
glBegin(GL_QUADS);
glVertex3f(0.05, 0.85,0);
     glVertex3f(0.05, 0.6, 0);
     glVertex3f(0.05, 0.6, 1);
glVertex3f(0.05, 0.85,1);
glEnd();

glColor3f(1, 0, 0);//chminy1 right xall positive
glBegin(GL_QUADS);
glVertex3f(0.15, 0.8, 0);
glVertex3f(0.15, 0.6, 0);
glVertex3f(0.15, 0.6, 1);
glVertex3f(0.15, 0.8, 1);
glEnd();

////////////////////////////////////chminy2

glBegin(GL_QUADS);//chminy2 back
  glColor3f(1, 0, 0);
   glVertex3f(-0.15, 0.85,0);
      glVertex3f(-0.15, 0.6, 0);
     glVertex3f(-0.05, 0.6, 0);
    glVertex3f(-0.05, 0.8,0);

  glEnd();

 glBegin(GL_QUADS);//chminy2 front
  glColor3f(1, 0, 0);
   glVertex3f(-0.15, 0.85,1);
      glVertex3f(-0.15, 0.6, 1);
     glVertex3f(-0.05, 0.6, 1);
    glVertex3f(-0.05, 0.8,1);

  glEnd();

  glColor3f(1, 0, 0);//chminy2 top
glBegin(GL_QUADS);
 glVertex3f(-0.15, 0.85,0);///back1
glVertex3f(-0.15, 0.85,1);///front1
glVertex3f(-0.05, 0.8,1);///front4
glVertex3f(-0.05, 0.8,0);///back4
glEnd();

  glColor3f(1, 0, 0);//chminy2 left x negtive back1,2 front2,1
glBegin(GL_QUADS);
glVertex3f(-0.15, 0.85,0);
      glVertex3f(-0.15, 0.6, 0);
     glVertex3f(-0.15, 0.6, 1);
 glVertex3f(-0.15, 0.85,1);
glEnd();

glColor3f(1, 0, 0);//chminy2 right xall positive
glBegin(GL_QUADS);
 glVertex3f(-0.05, 0.8,0);
glVertex3f(-0.05, 0.6, 0);
 glVertex3f(-0.05, 0.6, 1);
    glVertex3f(-0.05, 0.8,1);
glEnd();



}
void drawIceCreamCart()
{
glTranslatef(0,1,0);

glColor3f(.9,.9,.9);
drawBox(3,2,2,false,true,true,true,true,true);
glTranslatef(2,-.3,0);
glColor3b(25,35,29);
drawBox(1,1.5,2,false,true,true,true,true,true);
///2 dite hobe
glTranslatef(-2,2,0);
glRotated(90,1,0,0);
glColor3f(.71,.4,.11);
glutSolidCone(1.4,2,16,16);
glColor3f(.8,.49,.2);
glutWireCone(1.4,2,16,16);
glColor3f(1,1,1);
glTranslatef(.5,0,0);
glutSolidSphere(.7,16,16);
glTranslatef(-1,0,0);
glutSolidSphere(.7,16,16);
glTranslatef(0.5,0.5,0);
glutSolidSphere(.7,16,16);
glTranslatef(0,0,-.5);
glutSolidSphere(.7,16,16);
glTranslatef(0,2,2.3);
glTranslatef(0,-2.469,0);
glColor3f(0,0,0);
glPushMatrix();
glTranslatef(0,-0.50,0);
drawBox(2,2.99,1,false,true,false,false,false,false);
glPopMatrix();
glColor3f(0.1,0.1,0.1);
glRotatef(90,1,0,0);
glTranslatef(-0.5,0,0);
glTranslatef(0,.9,-.9);
glutSolidTorus(.1,.3,16,16);
glTranslatef(1.5,0,0);
glutSolidTorus(.1,.3,16,16);
glTranslatef(0,0,1.9);
glutSolidTorus(.1,.3,16,16);
glTranslatef(-1.5,0,0);
glutSolidTorus(0.1,0.3,16,16);

}


void car3(){
    glColor3ub(125, 120, 117);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(0,0,-.05);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(1.2,0,0);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(0,0,.05);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(0,0,.3);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(0,0,0.05);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(-1.2,0,0);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(0,0,0.-.055);
    glutSolidTorus(.023,.08,20,20);

    glTranslated(.8,.08,-.14); // z y x
    drawCustomBox(1.9,.05,.44,true,true,true,true,true,true);  // z y x

    glTranslated(-.6,.17,0); // z y x
    drawCustomBox(.5,.3,.44,true,true,true,true,true,true);  // z y x



    glColor3ub(255,255,255);
    glTranslated(-.44,-.155,-.17);
    glRotated(95,0,1,0);
    glutSolidCone(.02,.08,22,22);

    glTranslated(-.33,0,-.01);
    glRotated(0,0,0,0);
    glutSolidCone(.02,.08,22,22);

    glColor3ub( 235, 184, 45);
    glTranslated(.07,.2,.7);  //x y z
    drawCylinder(.2,1.2,false);



}

void drawUturn()
{
float choto=0.1;
glTranslatef(0,2,-15);
glPushMatrix();
glRotatef(90,-1,0,0);

glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, textureID[0]);
glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -1.0+choto, -0.5+choto);
   glTexCoord2f(0.0, 1.0); glVertex3f(0.0, -1.0+choto, 0.5-choto);
   glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 0.0-choto, 0.5-choto);
   glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0-choto, -0.5+choto);
   glEnd();
    glTranslatef(0.1,-0.5,-1);
    glColor3f(1,1,0);
   glBegin(GL_QUADS);

   glVertex3f(0,-.1,-.1);
   glVertex3f(0,-.1,01.1);
   glVertex3f(0,0.1,01.1);
   glVertex3f(0,0.1,-01.1);
glEnd();
glDisable(GL_TEXTURE_2D);

}
void drawGround()
{
glColor3f(0.f, 0.9f, 0.f);
glEnable(GL_TEXTURE_2D);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, textureID[0]);
glBegin(GL_QUADS);
glTexCoord2f(0.0, 0.0); glVertex3f(-100.0f, 0.0f, -100.0f);
glTexCoord2f(0.0, 1.0); glVertex3f(-100.0f, 0.0f, 100.0f);
glTexCoord2f(1.0, 1.0); glVertex3f( 100.0f, 0.0f, 100.0f);
glTexCoord2f(1.0, 0.0); glVertex3f( 100.0f, 0.0f, -100.0f);
glEnd();
glDisable(GL_TEXTURE_2D);


}

void DrawPOBoX(GLfloat constant)
{
    glRotatef(90,0,1,0);
    //constant=1;
    glColor3f(0.7,0,0);
    drawCylinder(.5*constant,1*constant,true);
    //glColor3f(0,1,1);
    glTranslated(0,-0.1,0.2);
    drawBox(1*constant,0.5*constant,1*constant,false,false,true,true,true,true);
    glRotatef(90,1,0,0);
    glTranslatef(0,0,0);
    glColor3f(139/255,69/255,19/255);
    glutSolidCone(0.1*constant,4*constant,3.5,4);

}
#include <math.h>
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glLineWidth(5);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
    glPopMatrix();
}

void DrawCirclePattern(float cx, float cy, float r, int num_segments)
{
    glPushMatrix();
    glPointSize(5);
    glBegin(GL_POINTS);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glColor3b(100,100,100);
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
        glPopMatrix();
    }
void DrawTrashCan()
{
    glRotatef(-90,1,0,0);
    glPushMatrix();
    for(int i=0;i<70;i++)
    {
    DrawCirclePattern(1,1,0.5,10);
    glTranslatef(0,0,0.01);
    }
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glTranslatef(1,1,-0.04);
   drawCylinder(0.5,1,false);
    glPopMatrix();
   glColor3b(100,100,100);
   glPushMatrix();
   glTranslatef(0,0,0.87);
   DrawCircle(1,1,0.54,10);
    glPopMatrix();

    //DrawCircle(1,1,0.5,10);
 //drawCylinder(0.4,1,false);
}
void renderScene(void) {

// Clear Color and Depth Buffers

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //gradient color sky
//.52+a,.8+b,.92+c,
glClearColor(a,b,c,.5);
// Reset transformations
glLoadIdentity();
// Set the camera
gluLookAt( x, 1.0f, z,
x+lx, 1.0f, z+lz,
0.0f, 1.0f, 0.0f);  //eyex eyesy iz  centerx center y center z
//up x upy upx vector

drawGround();
/*
// Draw ground
glColor3f(0.f, 0.9f, 0.f);
glBegin(GL_QUADS);
glVertex3f(-100.0f, 0.0f, -100.0f);
glVertex3f(-100.0f, 0.0f, 100.0f);
glVertex3f( 100.0f, 0.0f, 100.0f);
glVertex3f( 100.0f, 0.0f, -100.0f);
glEnd();
*/

glColor3ub(175, 143, 87);
glBegin(GL_QUADS);
glVertex3f(-5.0f, 0.1f, -100.0f);
glVertex3f(-5.0f, 0.1f, 100.0f);
glVertex3f( 5.0f, 0.1f, 100.0f);
glVertex3f( 5.0f, 0.1f, -100.0f);
glEnd();



glColor3f(0.f, 0.f, 0.f);
glBegin(GL_QUADS);
glVertex3f(-3.0f, 0.11f, -100.0f);
glVertex3f(-3.0f, 0.11f, 100.0f);
glVertex3f( 3.0f, 0.11f, 100.0f);
glVertex3f( 3.0f, 0.11f, -100.0f);
glEnd();

for(int i=-100;i<101;i+=20)
{
    for(int j=-6;j<10;j+=13)  //road left right
    {
    glPushMatrix();
    glTranslatef(j,0,i);
    drawBuilding();
    glPopMatrix();
    }
}

//tree**********************************************
for(int i=-100;i<101;i+=7)
{
    for(int j=-4;j<12;j+=8)  //road left right
    {
    glPushMatrix();
    glTranslatef(j,1,i);
    //glRotated()
    tree();

    glPopMatrix();
    }
}

for(int i=-100;i<101;i+=8)
{
    for(int j=-6;j<20;j+=13)  //road left right
    {
    glPushMatrix();
    glTranslatef(j,1,i);
    tree1();
    glPopMatrix();
    }
}

for(int i=-100;i<101;i+=9)
{
    for(int j=-7;j<15;j+=17)  //road left right
    {
    glPushMatrix();
    glTranslatef(j,1,i);
    tree();
    glPopMatrix();
    }
}

glTranslatef(0,0,-100); //center

for(int i=-100;i<100;i+=5)
{
glColor3f(1.f, 1.f, 1.f);
glTranslatef(0,0,5);
glBegin(GL_QUADS);
glVertex3f(-.50f, 0.12f, -1.0f);
glVertex3f(-.50f, 0.12f, 1.0f);
glVertex3f( .50f, 0.12f, 1.0f);
glVertex3f( .50f, 0.12f, -1.0f);
glEnd();
}

glPushMatrix();
glTranslatef(.5,1,-100); //onk same
glTranslatef(.1f,0.0f, position); //onk same move
glRotated(90,0,1,0); //road j dik oi dik
drawCar();
glPopMatrix();

//2nd car
glPushMatrix();
glTranslatef(-.9,1,-100); //onk same
glTranslatef(.1f,0.0f, position-7); //onk same move
glRotated(90,0,1,0); //road j dik oi dik
glPopMatrix();


drawSky();
glPushMatrix();
cloud();
drawSun();
glPopMatrix();
drawSun();

//plane************************************************************************************
glPushMatrix();
glColor3b(255,0,0);
glTranslated(1,position1+15,3.5);  //(x,z,y)
drawplane();
glPopMatrix();


//BOAT************************************************************************************
glTranslated(20,0,-.9);
glColor3ub(200, 244, 250);
glRotated(90,1,0,0);

glBegin(GL_QUADS);
glVertex3f(-4.0f, 0.1f, -100.0f);
glVertex3f(-4.0f, 0.1f, 100.0f);
glVertex3f( 4.0f, 0.1f, 100.0f);
glVertex3f( 4.0f, 0.1f, -100.0f);

glEnd();

glTranslated(-20,0,.9);
glTranslated(0,1,0);

glPushMatrix();
glTranslated(20,-.7,0);
glTranslatef(.1f,0.0f, position-20);
//glTranslatef(.1f,0.0f, .0f);
drawBoat();
glPopMatrix();

glTranslated(0,0,0);

//Road side Light************************************************************************************


for(int i=-100;i<101;i+=7)
{
    glPushMatrix();
    glTranslatef(-3,.3,i);
    drawroadlightleft();
    glPopMatrix();
}

glTranslated(0,0,0);
//glTranslated(1,.6,-1);
for(int i=-100;i<101;i+=7)
{
    glPushMatrix();
    glTranslatef(2,.3,i);
    //glRotated()
    drawroadlightright();
    glPopMatrix();
}
glTranslated(0,0,0);


glPushMatrix();
glTranslatef(-2.0f,0.0f, position-20);
cartorus();
glPopMatrix();
glTranslated(0,0,0);


glTranslated(-30,-.6,0);

for(int i=-100;i<101;i+=2)
{
    glPushMatrix();
    glTranslatef(2,-.1,i);
    hill();
    glPopMatrix();
}
glTranslated(30,.6,0);
glTranslated(0,0,0);


glTranslated(-13,-1.1,0);
for(int i=-100;i<101;i+=8)
{
    glPushMatrix();
    glTranslatef(0,1,i);
    railine();
    glPopMatrix();
}
glTranslated(13,1.1,0);

glTranslated(0,0,0);

glPushMatrix();
glTranslated(-13,-.12, position-21);
rail();
glPopMatrix();
glRotatef(90,0,1,0);
glTranslated(10,-1,17);
glTranslated(0,0,0);
glPushMatrix();
glTranslated(position,0, 0);
NewBoat();
glPopMatrix();

glPushMatrix();
glTranslated(position,0, 0);
glTranslated(-10,.3,-35);
drawIceCreamCart();
glPopMatrix();



glPushMatrix();
glTranslated(-position+20,.5,-16); // z y x
car3();
glPopMatrix();
glTranslatef(-1,-1,1);
drawUturn();
glPopMatrix();

glTranslatef(-1,0,-2);
glRotatef(90,0,1,0);

glTranslatef(-3.5,-0.2,-86);
for(int j=0;j<2;j++)
{glPushMatrix();
for(int i=0;i<9;i++)
{
glPushMatrix();
DrawPOBoX(0.4);

glPopMatrix();
glTranslatef(0,0,20);
}
glPopMatrix();
glTranslatef(9,0,0);
}
glColor3f(0.3,0.3,0.3);
glTranslatef(-14,+0.2,+86);
glTranslatef(-1,-1,0);

glPushMatrix();
glTranslatef(-3.5,-0.2,-86);
glTranslatef(0,0,-4);
for(int j=0;j<2;j++)
{glPushMatrix();
for(int i=0;i<9;i++)
{
glPushMatrix();
DrawTrashCan();

glPopMatrix();
glTranslatef(0,0,20);
}
glPopMatrix();
glTranslatef(9,0,0);
}
glPopMatrix();
glutSwapBuffers();
}

void changeSize(int w, int h) {
if (h == 0)
h = 1;
float ratio = w * 1.0 / h;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(45.0f, ratio, 0.1f, 100.0f);
glMatrixMode(GL_MODELVIEW);


}


void processNormalKeys(unsigned char key, int x, int y) {
switch (key) {

case 'a':
    speed = 0.0f;
    break;
case 'w':
    speed += 0.1f;
    break;
//plane
case 'p':
    speed1 += 0.1f;
    break;
case 'l':
    if(speed1>0.3)
    speed1 = 0.1f;
    break;

case 'd':
    dayspeed+=0.01f;
    break;

case 'D':
    dayspeed=0.0f;
    break;
glutPostRedisplay();
    if (key == 27)
exit(0);

}




}

void processSpecialKeys(int key, int xx, int yy) {

float fraction = 0.1f;

switch (key) {
case GLUT_KEY_LEFT :
angle -= 0.01f;
lx = sin(angle);
lz = -cos(angle);
break;
case GLUT_KEY_RIGHT :
angle += 0.01f;
lx = sin(angle);
lz = -cos(angle);
break;
case GLUT_KEY_UP :
x += lx * fraction;
z += lz * fraction;
break;
case GLUT_KEY_DOWN :
x -= lx * fraction;
z -= lz * fraction;
break;
}
}



int main(int argc, char **argv) {
cout<<"---------Controller---------"<<endl;
cout<<"Press w for speed up the car, boat and train."<<endl;
cout<<"Press a for stop car, boat and train."<<endl;
cout<<"Press p for speed up Plane."<<endl;
cout<<"Press l for reducing the speed of the plane."<<endl;
cout<<"Press d for speed up the day speed"<<endl;
cout<<"Press D for speed None for day"<<endl;
cout<<"Thanks."<<endl;

   a=.52;
   b=.8;
   c=.92;
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(320,320);
glutCreateWindow(" GLUT");
// register callbacks
///init();
glEnable(GL_BLEND);
glutDisplayFunc(renderScene);
glutReshapeFunc(changeSize);
glutIdleFunc(renderScene);
glutKeyboardFunc(processNormalKeys);
glutSpecialFunc(processSpecialKeys);
// OpenGL init
glutTimerFunc(1000, update, 0);

glEnable(GL_DEPTH_TEST);


// enter GLUT event processing cycle
glutMainLoop();
return 0;
}



