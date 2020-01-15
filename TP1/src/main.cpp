#include <iostream>
#include <shader.hpp> // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h> // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp> // OpenGL Mathematics : www.http://glm.g-truc.net/0.9.5/index.html

using namespace glm;
using namespace std;

int main() {
  cout << "Debut du programme..." << endl;

  // Initialisation de GLFW
  if(!glfwInit()) {
    cout << "Echec de l'initialisation de GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // Anti Aliasing
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2); // OpenGL 2.1
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

  // Ouverture d'une fenêtre en 1024x768
  // et creation d'un contexte OpenGL
  if(!glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW)) {
    cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Definition du titre de la fenêtre
  glfwSetWindowTitle( "Polytech RICM 4 - TP1" );

  // Autorise GLFW a recevoir les appuis de touche
  glfwEnable(GLFW_STICKY_KEYS);

  // Initialisation de  GLEW
  if(glewInit() != GLEW_OK) {
    cout << "Echec de l'initialisation de GLEW" << endl;
    exit(EXIT_FAILURE);
  }

  // Verification des donnees du contexte OpenGL
  const GLubyte* renderer = glGetString (GL_RENDERER);
  cout << "Carte Graphique : " << renderer << endl;

  const GLubyte* version = glGetString (GL_VERSION);
  cout << "Driver OpenGL : " << version << endl;



  //==================================================
  // ToDo : Initialiser
  //==================================================

  cout << "Initialisations..." << endl;
  // Initialisation Shader

  GLuint programID = LoadShaders("../shader/vertex1.glsl","../shader/fragment.glsl");
  vec3 v(-1.0f, -1.0f, 0.0f);
  vec3 vertex[3];
  vertex[0]= vec3(-0.5f,-0.5f,0.0f);
  vertex[1]= vec3(0.5f,-0.5f,0.0f);
  vertex[2]= vec3(-0.5f,0.5f,0.0f);
  GLuint vertexPositionID = glGetAttribLocation(programID, "vertex_position");

  GLuint vaoID;
  glGenVertexArrays(1,&vaoID);
  glBindVertexArray(vaoID);
  GLuint vboID;
  glGenBuffers(1,&vboID);

  glBindBuffer(GL_ARRAY_BUFFER,vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertexPositionID);
  glVertexAttribPointer;
  glVertexAttribPointer(
    vertexPositionID,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*) 0
  );

  glBindVertexArray(0);
  // Definition de la couleur du fond
  glClearColor(0.4f,0.2f,0.7f,0.0f);
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);



  cout << "Debut de la boucle principale..." << endl;
  unsigned int i = 0;
  
  // Boucle de dessin
  do {
   
    // Nettoyage de la zone de dessin
    glClear( GL_COLOR_BUFFER_BIT );
    glUseProgram(programID);
	  //----------------------------------------Zone dessin-----------------------------//
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES, 0,3);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    glBegin (GL_TRIANGLE_FAN) ;
    glColor3f(0.2,0.3,0.4);
    glVertex3f (-0.5f,0.5f,0.0f) ;
    glColor3f(0.2,0.3,0.4);
    glVertex3f (0.5f,-0.5f,0.0f) ;
    glColor3f(0.2,0.3,0.4);
    glVertex3f (0.5f,0.5f,0.0f) ;
    
    glEnd() ;
    //--------------------------------------Fin Zone Dessin----------------------------//

    // Echange des zones de dessin buffers
    glfwSwapBuffers();
	  
    cout << "Compteur : " << i++ << "\r";
    cout.flush();

  } // Execution de la boucle...
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
	 glfwGetWindowParam( GLFW_OPENED )        );  // ... ou fermeture de la fenetre

  cout << endl;

  // Ferme GLFW et OpenGL
  glfwTerminate();



  //==================================================
  // ToDo : Nettoyer la memoire
  //==================================================

  glDeleteBuffers(1,&vboID);
  glDeleteBuffers(1,&vaoID);

  cout << "Fin du programme..." << endl;

  return EXIT_SUCCESS;
}

