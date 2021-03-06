#include "define.h"
#include "components/obj.h"
#include "components/loader.h"
#include "Api/Apipdi.h"
#include "./components/userInterface.h"

// Window current width
unsigned int windowWidth = 800;
// Window current height
unsigned int windowHeight = 600;
// Window title
const char *windowTitle = "PDI API";
// Window pointer
GLFWwindow *window;

CUserInterface *userInterFace;
// Camera object
bool pressLeft = false;
string filter = "normal";
 
// Shader object
Shader *shader;
// Index (GPU) of the texture
unsigned int textureID;
bool textureIDUsing;

unsigned char* textureData;

std::vector<Obj*> objects;

void createTexture(unsigned char*);

int renderType = 0;

int textureWidth, textureHeight, numberOfChannels;

bool GPUActive = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void onMouseButton(GLFWwindow* window, int button, int action, int mods);

/**
 * Handles the window resize
 * @param{GLFWwindow} window pointer
 * @param{int} new width of the window
 * @param{int} new height of the window
 * */

void updateUserInterface()
{
    if(userInterFace->getDeployType() != filter || GPUActive != userInterFace->GPU){

        filter = userInterFace->getDeployType();
        GPUActive = userInterFace->GPU;
        unsigned char* data;

        if (filter == "normal") {

            glDeleteTextures(1, &textureID);
            createTexture(textureData);

        }else if(filter == "blackWhite"){

            glDeleteTextures(1, &textureID);
            data = blackWhiteImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU);
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "negative"){

            glDeleteTextures(1, &textureID);
            data = negativeImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU);
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "grayScale"){

            glDeleteTextures(1, &textureID);
            data = grayScaleImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU);
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "sobel"){

            glDeleteTextures(1, &textureID);
            data = sobelImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "gaus"){

            glDeleteTextures(1, &textureID);
            data = lOfGuusImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "avg"){

            glDeleteTextures(1, &textureID);
            data = avgImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "sobel"){

            glDeleteTextures(1, &textureID);
            data = sobelImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "prewitt"){

            glDeleteTextures(1, &textureID);
            data = prewittImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "roberts"){

            glDeleteTextures(1, &textureID);
            data = robertsImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "toon"){

            glDeleteTextures(1, &textureID);
            data = toonImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }else if(filter == "mediana"){

            glDeleteTextures(1, &textureID);
            data = medianImage(textureWidth, textureHeight, numberOfChannels, textureData, userInterFace->GPU, glm::vec2(userInterFace->kernelX,userInterFace->kernelY));
            createTexture(data);
            stbi_image_free(data);
            getTime();

        }
    }
}


void resize(GLFWwindow *window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    // Sets the OpenGL viewport size and position
    glViewport(0, 0, windowWidth, windowHeight);

    userInterFace->reshape(width, height);
}
/**
 * Initialize the glfw library
 * @returns{bool} true if everything goes ok
 * */
bool initWindow()
{
    // Initialize glfw
    glfwInit();
    // Sets the Opegl context to Opengl 3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates the window
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);

    // The window couldn't be created
    if (!window)
    {
        std::cout << "Failed to create the glfw window" << std::endl;
        glfwTerminate(); // Stops the glfw program
        return false;
    }

    // Creates the glfwContext, this has to be made before calling initGlad()
    glfwMakeContextCurrent(window);

    // Window resize callback
    glfwSetFramebufferSizeCallback(window, resize);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, onMouseButton);

    return true;
}
/**
 * Initialize the glad library
 * @returns{bool} true if everything goes ok
 * */
bool initGlad()
{
    // Initialize glad
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // If something went wrong during the glad initialization
    if (!status)
    {
        std::cout << status << std::endl;
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}
/**
 * Initialize the opengl context
 * */
void initGL()
{
    // Enables the z-buffer test
    glEnable(GL_DEPTH_TEST);
    // Sets the ViewPort
    glViewport(0, 0, windowWidth, windowHeight);
    // Sets the clear color
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}
/**
 * Builds all the geometry buffers and
 * loads them up into the GPU
 * (Builds a simple triangle)
 * */
void buildGeometry()
{
    objects.push_back(objLoader("assets/Objects/plane.obj"));
}
/**
 * Loads a texture into the GPU
 * @param{const char} path of the texture file
 * @returns{unsigned int} GPU texture index
 * */
void loadTexture(const char *path)
{

    glGenTextures(1, &textureID);

    stbi_set_flip_vertically_on_load(true);

    textureData = stbi_load(path, &textureWidth, &textureHeight, &numberOfChannels, 0);

    userInterFace->width = textureWidth;
    userInterFace->height = textureHeight;
    userInterFace->pixels = 8*numberOfChannels;
    userInterFace->uniqueColors = uniqueColors(textureWidth,textureHeight,numberOfChannels,textureData);
    createTexture(textureData);

    // renderHistograma(textureWidth,textureHeight,textureData);
}

/**
 * Initialize everything
 * @returns{bool} true if everything goes ok
 * */
bool init()
{
    // Initialize the window, and the glad components
    if (!initWindow() || !initGlad())
        return false;

    TwInit(TW_OPENGL_CORE, NULL);
    userInterFace = CUserInterface::Instance();
    userInterFace->reshape(windowWidth, windowHeight);
    // Initialize the opengl context
    initApipdi();
    loadTexture("assets/textures/test2.jpg");
    // loadTexture("assets/textures/test1.jpg");
    initGL();
    // Loads the shader
    shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    // Loads all the geometry into the GPU
    buildGeometry();
    // Loads the texture into the GPU

    return true;
}
/**
 * Process the keyboard input
 * There are ways of implementing this function through callbacks provide by
 * the GLFW API, check the GLFW documentation to find more
 * @param{GLFWwindow} window pointer
 * */
void processKeyboardInput(GLFWwindow *window)
{
    // Checks if the escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // Tells glfw to close the window as soon as possible
        glfwSetWindowShouldClose(window, true);
    
    
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        // Reloads the shader
        delete shader;
        shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    }
}
/**
 * Render Function
 * */
void render()
{
    // Clears the color and depth buffers from the frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //glViewport(0, 0, windowWidth, windowHeight);
    /** Draws code goes here **/
    // Use the shader
    shader->use();
    // Binds the vertex array to be 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureID);
    
    for(int i = 0; i < objects.size(); i++){
       objects[i]->Draw();
    }

}
/**
 * App main loop
 * */
void update()
{
    // Loop until something tells the window, that it has to be closed
    while (!glfwWindowShouldClose(window))
    {
        // Checks for keyboard inputs
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        processKeyboardInput(window);
       
        // glViewport(0, 0, 200, 200);
        // drawHistograma(1);
        // Renders everything
        glViewport(0, 0, windowWidth, windowHeight);
        render();

        
        TwDraw();

        updateUserInterface();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}
/**
 * App starting point
 * @param{int} number of arguments
 * @param{char const *[]} running arguments
 * @returns{int} app exit code
 * */
int main(int argc, char const *argv[])
{
    // Initialize all the app components
    if (!init())
    {
        // Something went wrong
        std::cin.ignore();
        return -1;
    }

    std::cout << "=====================================================" << std::endl
              << "        Press Escape to close the program            " << std::endl
              << "=====================================================" << std::endl;

    // Starts the app main loop
    update();

    // Deletes the texture from the gpu
    glDeleteTextures(1, &textureID);
    // Deletes the vertex array from the GPU
    for(int i = 0; i < objects.size(); i++){
        delete objects[i];
    }
    // Destroy the shader
    delete shader;

    // Stops the glfw program
    TwTerminate();

    glfwTerminate();

    return 0;
}

void createTexture(unsigned char* data) {

    //glGenTextures(1, &textureID);

    if (data)
    {
        // Gets the texture channel format
        GLenum format;
        switch (numberOfChannels)
        {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        }

        // Binds the texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        // Creates the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
        // Creates the texture mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set the filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "ERROR:: Unable to load texture " << std::endl;
        glDeleteTextures(1, &textureID);
    }
    // We dont need the data texture anymore because is loaded on the GPU
    //free(data);

}

void beginLoad(string path) {
	string aux = path;
	string extension = aux.erase(0, aux.find(".") + 1);
	//Caso archivo OFF:

    if (extension == "jpg" || extension == "JPG") {

        stbi_image_free(textureData);
        glDeleteTextures(1,&textureID);
        const char* cstr = path.c_str();
        //path.copy(aux2, path.size()+1);
        loadTexture(cstr);
        //delete [] cstr;
    }

}

void beginSave(){

    userInterFace->hide();
    render();
    saveImage("Image.jpg",windowWidth,windowHeight);
    userInterFace->show();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	TwMouseMotion(static_cast<int>(xpos), static_cast<int>(ypos));
}

void onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	auto a = action == GLFW_PRESS ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
	auto b = TW_MOUSE_LEFT;
    
    TwMouseButton(a, b);
}