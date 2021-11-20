// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
float rot2 = 0.0f;
float rot3 = 0.0f;
float rot4 = 0.0f;
float rot5 = 0.0f;
bool activanim;
bool activanim2;
bool activanim3;
bool activanim4;
bool activanim5;


int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica 4", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader lampshader( "Shaders/lamp.vs", "Shaders/lamp.frag" );

    // Load models
    Model Casa((char*)"Models/Casa/Casa.obj");
    Model Porton((char*)"Models/Casa/Porton.obj");
    Model Puerta((char*)"Models/Casa/Puerta.obj");
    Model Burro((char*)"Models/Casa/Burro.obj");
    Model Llave((char*)"Models/Casa/Llave.obj");
    Model Cortina((char*)"Models/Casa/Cortina.obj");

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        //Impresion del porton de la casa.
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(3.0487f, 3.68f, 3.5f));
        model = glm::rotate(model, glm::radians(-rot), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Porton.Draw(shader);
        
        //Impresion de la puerta de la casa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.938f, 1.72f, 4.87f));
        model = glm::rotate(model, glm::radians(-rot2), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta.Draw(shader);

        //Impresion del burro de la cocina
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.426f, 1.45f, -2.3f));
        model = glm::rotate(model, glm::radians(rot3), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Burro.Draw(shader);

        //Impresion de la llave del fregadero de la cocina
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.918f, 1.89f, -4.93f));
        model = glm::rotate(model, glm::radians(rot4), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot5), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Llave.Draw(shader);

        //Impresion de la cortina del fregadero de la cocina
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.7f, 0.799f, -3.57f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cortina.Draw(shader);
        
        //Impresion del resto de la casa
        model = glm:: mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Casa.Draw(shader);
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
    //Animacion del porton
    if (activanim)
    {
        if (rot < 90)
        {
            rot += 0.6f;
        }
    }
    else if (!activanim)
    {
        if (rot > 0)
        {
            rot -= 0.6f;
        }
    }
    //Animacion de la puerta
    if (activanim2)
    {
        if (rot2 < 90)
        {
            rot2 += 0.6f;
        }
    }
    else if (!activanim2)
    {
        if (rot2 > 0)
        {
            rot2 -= 0.6f;
        }
    }
    //Animacion del burro
    if (activanim3)
    {
        if (rot3 < 90)
        {
            rot3 += 0.6f;
        }
    }
    else if (!activanim3)
    {
        if (rot3 > 0)
        {
            rot3 -= 0.6f;
        }
    }
    //Animacion 1 del grifo
    if (activanim4)
    {
        if (rot4 < 90)
        {
            rot4 += 0.6f;
        }
    }
    else if (!activanim4)
    {
        if (rot4 > 0)
        {
            rot4 -= 0.6f;
        }
    }
    //Animacion 2 del grifo
    if (activanim5)
    {
        if (rot5 < 90)
        {
            rot5 += 0.6f;
        }
    }
    else if (!activanim5)
    {
        if (rot5 > 0)
        {
            rot5 -= 0.6f;
        }
    }


}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
    //Animacion del porton
    if (keys[GLFW_KEY_O])
    {
        activanim= !activanim;
    }
    //Animacion de la puerta
    if (keys[GLFW_KEY_I])
    {
        activanim2 = !activanim2;
    }
    //Animacion del burro
    if (keys[GLFW_KEY_P])
    {
        activanim3 = !activanim3;
    }

    //Animación de la llave del fregadero
    if (keys[GLFW_KEY_K])
    {
        activanim4 = !activanim4;
    }
    if (keys[GLFW_KEY_L])
    {
        activanim5 = !activanim5;
    }
    

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

