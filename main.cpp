#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

//Setting vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLuint indices[] =
{
    0, 2, 1, // Upper triangle
    0, 3, 2 // Lower triangle
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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);          // Position
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Color
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture Coordinates

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    Texture dirt("dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    dirt.texUnit(shaderProgram, "tex0", 0);

    while (!glfwWindowShouldClose(window)) //Loops until window closed
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the color of the background
        glClear(GL_COLOR_BUFFER_BIT); // Clean the back buffer and assign the new color to it
        shaderProgram.Activate(); // Tell OpenGL which Shader Program we want to use

        glUniform1f(uniID, 0.5f);
        dirt.Bind();

        VAO1.Bind(); // Bind the VAO so OpenGL knows to use it
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw primitives, number of indices, datatype of indices, index of indices
        glfwSwapBuffers(window); // Swap the back buffer with the front buffer
        glfwPollEvents(); // Take care of all GLFW events
    }

    //Deletes all objects created
   // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    dirt.Delete();
    shaderProgram.Delete();

    //Deletes window before ending the program
    glfwDestroyWindow(window);

    //Deleted GLFW before ending program
    glfwTerminate();
    return 0;
}