#include <glad/glad.h>
#include <GLFW/glfw3.h>

int width = 800;
int height = 600;

int main()
{
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(width, height, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    // Load the source of the vertex and fragment shader.
    const char* vertexCode = "#version 150\n"
                     "in vec3 a_vertex;void main(void){gl_Position = vec4(a_vertex, 1.0);}";
    const char* fragmentCode = "#version 150\n"
                     "out vec4 fragColor;void main(void){ fragColor = vec4(1.0, 1.0, 1.0, 0.85);}";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindAttribLocation(shaderProgram, 0, "a_vertex");

    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    float buffer[18] = {
        -0.4, -0.4, 0.1,
         0.6, -0.4, 0.1,
         0.1, 0.85, 0.1,

        -0.5, -0.5, -0.1,
         0.5, -0.5, -0.1,
         0.0, 0.75, -0.1
    };

    GLuint bufferHandle[2];
    glGenBuffers(2, bufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, bufferHandle[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer) / 2, &buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, bufferHandle[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer) / 2, &buffer[9], GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glEnableVertexAttribArray(0);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, width, height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, bufferHandle[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glColorMask(1, 0, 0, 1);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glBindBuffer(GL_ARRAY_BUFFER, bufferHandle[1]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glColorMask(0, 1, 0, 1);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glDisableVertexAttribArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        glfwGetWindowSize(window, &width, &height);
    }

    glfwTerminate();
    return 0;
}
