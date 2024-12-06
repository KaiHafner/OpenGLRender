#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;

//Setting vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
    -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

GLfloat lightVertices[] =
{ //COORDINATES
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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
    GLFWwindow* window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL(); //Loads GLAD so its configured to OpenGL
    glViewport(0, 0, width, height); //Specifies viewport of OpenGL in the window



    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("Resource/Shader/default.vert", "Resource/Shader/default.frag");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices)); // Generates Vertex Buffer Object and links it to vertices
    EBO EBO1(indices, sizeof(indices)); // Generates Element Buffer Object and links it to indices

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    // Shader for light cube
    Shader lightShader("Resource/Shader/light.vert", "Resource/Shader/light.frag");
    VAO lightVAO;    // Generates Vertex Array Object and binds it
    lightVAO.Bind();
    VBO lightVBO(lightVertices, sizeof(lightVertices)); // Generates Vertex Buffer Object and links it to vertices
    EBO lightEBO(lightIndices, sizeof(lightIndices)); // Generates Element Buffer Object and links it to indices
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); // Links VBO attributes such as coordinates and colours to VAO
    // Unbind all to prevent accidentally modifying them
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);


    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    //Textures
    Texture planksTex("Resource/Textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    planksTex.texUnit(shaderProgram, "tex0", 0);
    Texture planksSpec("Resource/Textures/planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    planksSpec.texUnit(shaderProgram, "tex1", 1);

    Texture dirtTex("Resource/Textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    dirtTex.texUnit(shaderProgram, "tex2", 0);

    Texture brickTex("Resource/Textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    brickTex.texUnit(shaderProgram, "tex3", 0);

    //Enables depth buffer
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window)) //Loops until window closed
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the colour of the background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffer and depth buffer
  
        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        shaderProgram.Activate(); // Tell OpenGL which Shader Program we want to use
        // Exports the camera Position to the Fragment Shader for specular lighting
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

        camera.Matrix(shaderProgram, "camMatrix");

        planksTex.Bind(); //binds texture
        planksSpec.Bind();

        VAO1.Bind(); // Bind the VAO so OpenGL knows to use it
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); // Draw primitives, number of indices, datatype of indices, index of indices


        
        lightShader.Activate();// Tells OpenGL which Shader Program we want to use
        camera.Matrix(lightShader, "camMatrix");// Export the camMatrix to the Vertex Shader of the light cube
        lightVAO.Bind();// Bind the VAO so OpenGL knows to use it

        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);// Swap the back buffer with the front buffer
        glfwPollEvents();// Take care of all GLFW events
    }

   //Deletes all objects created
   // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    planksTex.Delete();
    planksSpec.Delete();
    shaderProgram.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightShader.Delete();

    //Deletes window before ending the program
    glfwDestroyWindow(window);

    //Deleted GLFW before ending program
    glfwTerminate();
    return 0;
}