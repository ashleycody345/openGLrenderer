#include <iostream>
#include <GLFW\glfw3.h>
#include "stb_image.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float &val, float deltaTime, glm::vec3 &cameraPos, glm::vec3 &cameraFront);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
glm::mat4 mylookAt(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 up);


// mouse
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
bool firstMouse = 1;

// camera variables
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int main() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    // initialize window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouseCallback);

    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // initialize shader program here using shader object
    Shader shaderProg("vertexShader.glsl", "fragmentShader.glsl");


    float triangle[] = {
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
                          
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
                          
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
                          
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
                          
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
                          
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f
                          
    // floor              
    //-9.0f, -3.0f, -9.0f,  0.0f, 0.0f, 0.0f,
    //-9.0f, -3.0f, 9.0f,   0.0f, 0.0f, 0.0f,
    //9.0f, -3.0f, 9.0f,    0.0f, 0.0f, 0.0f,
    //9.0f, -3.0f, 9.0f,    0.0f, 0.0f, 0.0f,
    //-9.0f, -3.0f, -9.0f,  0.0f, 0.0f, 0.0f,
    //9.0f, -3.0f, -9.0f,   0.0f, 0.0f, 0.0f
    };

    // seed RNG table
    std::srand(std::time(nullptr));

    // generate random colors, set one side to that color, repeat for 6 sides
    //glm::vec3 rand_vec = glm::vec3(0.0f);
    //for(int i = 0; i < 6; i++){
    //    // random vector, define component-wise
    //    rand_vec.r = float(std::rand() % 255) / 255.0f;
    //    rand_vec.g = float(std::rand() % 255) / 255.0f;
    //    rand_vec.b = float(std::rand() % 255) / 255.0f;

    //    // insert components of vector into a side
    //    for(int j = 0; j < 6; j++){
    //        triangle[3 + 36*i + 6*j] = rand_vec.r;
    //        triangle[4 + 36*i + 6*j] = rand_vec.g;
    //        triangle[5 + 36*i + 6*j] = rand_vec.b;
    //    }
    //}

    // print contents of colors:
    //for(int i = 0; i < 6; i++){
    //    std::cout << "Colors at " << i << ":\n";
    //    for(int j = 0; j < 6; j++){
    //        std::cout << triangle[36*i + 6*j + 3] << ", " << triangle[36 * i + 6 * j + 4] << ", " << triangle[36 * i + 6 * j + 5] << std::endl;
    //    }
    //}

    //unsigned int VBO, VAO;
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // --------------------------------
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    // settings for vertex coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // settings for color
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3*sizeof(float)));
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    


    //// texture generation
    //unsigned int texture[2];
    //glGenTextures(2, texture);

    //glBindTexture(GL_TEXTURE_2D, texture[0]);

    //// remember to set parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //// load image
    //int width, height, nrChannels;
    //unsigned char *data = stbi_load("black.jpg", &width, &height, &nrChannels, 0);

    //if(data){
    //    // if data successfully generated, load texture data
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else{
    //    std::cout << "Failed to load texture data\n";
    //}

    //stbi_image_free(data);


    //// texture 2
    //glBindTexture(GL_TEXTURE_2D, texture[1]);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //data = stbi_load("gabefunny.png", &width, &height, &nrChannels, 0);
    //if(data){
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else{
    //    std::cout << "Failed to load texture data\n";
    //}

    //stbi_image_free(data);

    //// set texture uniforms
    //shaderProg.use();
    //shaderProg.setInt("texture1", 0);
    //shaderProg.setInt("texture2", 1);

    float ratio = 0.0f;

    //
    // model matrix
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate to flatten to the ground, original model still has upright coords


    // projection matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // enable z-buffer
    glEnable(GL_DEPTH_TEST);


    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    

    // capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    float prevTime = glfwGetTime();
    float deltaTime = glfwGetTime() - prevTime;
    
    

    // render loop:
    while (!glfwWindowShouldClose(window))
    {
        deltaTime = glfwGetTime() - prevTime;
        prevTime = glfwGetTime();
        processInput(window, ratio, deltaTime, cameraPos, cameraFront);

        // bound ratio to interval [0, 1]
        //if(ratio < 0.0f) ratio = 0.0f;
        //if(ratio > 1.0f) ratio = 1.0f;

        // rendering instructions...
        shaderProg.use();
        // glUseProgram(shaderProgram);

        // clear z-buffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glUniformMatrix4fv(glGetUniformLocation(shaderProg.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(glGetUniformLocation(shaderProg.ID, "imageRatio"), 1); // texture ratio float

        // update rotation matrix
        //model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        for(int i = 0; i < 10; i++){
            // texture procedure
            //glBindTexture(GL_TEXTURE_2D, texture[0]);
            // 
            // image ratio uniform
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, ((float)glfwGetTime() * glm::radians(50.0f)) * (i % 3 == 0) + glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            glUniformMatrix4fv(glGetUniformLocation(shaderProg.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));



            //glActiveTexture(GL_TEXTURE0);
            //glBindTexture(GL_TEXTURE_2D, texture[0]);
            //glActiveTexture(GL_TEXTURE1);
            //glBindTexture(GL_TEXTURE_2D, texture[1]);

            glBindVertexArray(VAO);

            //glClearColor(0.2f, 0.2f, 0.2f, 1.0f);


            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        // view matrix
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glUniformMatrix4fv(glGetUniformLocation(shaderProg.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texture[0]);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, texture[1]);

        glBindVertexArray(VAO);

        //glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        

        //glDrawArrays(GL_TRIANGLES, 0, 36);

        
        // call events, swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }


    glfwTerminate();


	return 0;
}

// query for key input, process input
// (esc. to exit)
void processInput(GLFWwindow* window, float &val, float deltaTime, glm::vec3 &cameraPos, glm::vec3 &cameraFront)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    float cameraSpeed = 2.5f;
    if (glfwGetKey(window, GLFW_KEY_W)) {
        cameraPos += deltaTime * cameraSpeed * glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z));
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        cameraPos -= deltaTime * cameraSpeed * glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z));
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        cameraPos += deltaTime * cameraSpeed * glm::normalize(glm::cross(glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z)), glm::vec3(0.0f, 1.0f, 0.0f)));
    }
    if (glfwGetKey(window, GLFW_KEY_A)) { 
        cameraPos -= deltaTime * cameraSpeed * glm::normalize(glm::cross(glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z)), glm::vec3(0.0f, 1.0f, 0.0f)));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        cameraPos += glm::vec3(0.0f, -1.0f, 0.0f) * cameraSpeed * deltaTime;
    }
}

// when window changes in size, reset viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// receive mouse input, determine mouse movement
void mouseCallback(GLFWwindow* window, double xpos, double ypos){
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch <= -89.0f) pitch = -89.0f;
    if(pitch >= 89.0f) pitch = 89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

glm::mat4 mylookAt(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 up){
    glm::vec3 cameraDir = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDir));
    glm::vec3 cameraUp = glm::cross(cameraDir, cameraRight);
    glm::mat4 look = glm::mat4(1.0f);
    look[0][0] = cameraRight.x; // First column, first row
    look[1][0] = cameraRight.y;
    look[2][0] = cameraRight.z;
    look[0][1] = cameraUp.x; // First column, second row
    look[1][1] = cameraUp.y;
    look[2][1] = cameraUp.z;
    look[0][2] = cameraDir.x; // First column, third row
    look[1][2] = cameraDir.y;
    look[2][2] = cameraDir.z;
    //look[0] = glm::vec4(cameraRight, 0.0f);
    //look[1] = glm::vec4(cameraUp, 0.0f);
    //look[2] = glm::vec4(cameraDir, 0.0f);
    glm::mat4 pos = glm::mat4(1.0f);
    pos[3][0] = -cameraPos.x; // Fourth column, first row
    pos[3][1] = -cameraPos.y;
    pos[3][2] = -cameraPos.z;
    //pos[3][0] = -cameraPos.x;
    //pos[3][1] = -cameraPos.y;
    //pos[3][2] = -cameraPos.z;
         
    return look * pos;
}