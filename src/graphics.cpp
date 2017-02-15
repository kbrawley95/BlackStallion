#include "../include/graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

void Graphics::initOpenGL()
{
    //Smooth shading
    glShadeModel(GL_SMOOTH);

    //Clear the background to black
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    
    //Clear the depth buffer to 1.0
    glClearDepth(1.0f);

    //Enable depth testing
    glEnable(GL_DEPTH_TEST);

    //Specify the depth test to use
    glDepthFunc(GL_LEQUAL);

    //Turn on best persepctive correction
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLenum err=glewInit();
    if(GLEW_OK!=err)
    {
        /*Problem: glewInit failed, something is seriously wrong*/
        std::cout<<"Error: "<<glewGetErrorString(err)<<std::endl;
    }
}

void Graphics::setViewport(int width, int height)
{
    //screen ratio
    GLfloat ratio;

    //Make sure height is always above 1
    if(height==0){
        height=1;
    }

    //Calculate screen ratio
    ratio=(GLfloat)width/(GLfloat)height;

    //Setup viewport
    glViewport(0,0,(GLsizei)width, (GLsizei)height);

    //Change to projection matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    //Change perspective matrix, using glu library functions
    gluPerspective(45.0f,ratio, 0.1f, 100.0f);

    //Switch to ModelView
    glMatrixMode(GL_MODELVIEW);

    //Reset using the Indentity glMatrixMode
    glLoadIdentity();
}