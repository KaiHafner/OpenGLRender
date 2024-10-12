#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

//Setting vertices coordinates
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower left c
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower right c
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //upper right c

    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //Inner down
};
GLuint indices[] =
{
    0, 3, 5,//lower left tri
    3, 2, 4, //lower right tri
    5, 4, 1 //top tri
};

int main(void)
{
    glfwInit(); //Initialises GLFW

    //Tell GLFW what version of OpenGL we are using (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Tell GLFW we are using the CORE profile (only modern functions)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creates a GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(800, 800, "Renderer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL(); //Loads GLAD so its configured to OpenGL
    glViewport(0, 0, 800, 800); //Specifies viewport of OpenGL in the window

    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkVBO(VBO1, 0);
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    while (!glfwWindowShouldClose(window)) //Loops until window closed
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the color of the background
        glClear(GL_COLOR_BUFFER_BIT); // Clean the back buffer and assign the new color to it
        shaderProgram.Activate(); // Tell OpenGL which Shader Program we want to use
        VAO1.Bind(); // Bind the VAO so OpenGL knows to use it
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Draw primitives, number of indices, datatype of indices, index of indices
        glfwSwapBuffers(window); // Swap the back buffer with the front buffer
        glfwPollEvents(); // Take care of all GLFW events
    }

    //Deletes all objects created
   // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    //Deletes window before ending the program
    glfwDestroyWindow(window);

    //Deleted GLFW before ending program
    glfwTerminate();
    return 0;
}