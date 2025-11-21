/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RenderSystemOPENGL.hpp"

namespace RType
{

RenderSystemOPENGL::RenderSystemOPENGL()
    : _isFullScreen(false), _nextSpriteId(1), _nextFontId(1), _nextMusicId(1), _nextSoundId(1)
{
    

    if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW\n");
    _window = glfwCreateWindow(1920, 1080, "RType", NULL, NULL);
    
    if (!_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window\n");
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    throw std::runtime_error("Failed to initialize GLAD\n");
}

}

RenderSystemOPENGL::~RenderSystemOPENGL()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void RenderSystemOPENGL::pollEvents() {}


void RenderSystemOPENGL::clearWindow() { glClear(GL_COLOR_BUFFER_BIT); }

void RenderSystemOPENGL::updateWindow()
{
    glfwSwapBuffers(_window);
    glfwPollEvents();

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}


}  // namespace RType
