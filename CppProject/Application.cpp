// ReSharper disable CppZeroConstantCanBeReplacedWithNullptr
#include "Graphic.h"
#include "Shader.h"

#include "Blending.h"
// #include "Camera.h"
#include "ApplicationListenerSetter.h"
#include "Camera.h"
#include "Core.h"
#include "Texture2D.h"

#include "Renderer.h"
#include "Draw.h"
#include "File.h"
#include "GraphicUtil.h"
#include "MultiSampleFrameBuffer.h"

using namespace Graphic;

int main(){
    // glfw: initialize and configure
    // ------------------------------
    initGLFW();

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw windowMain creation
    // --------------------
    enableMSAA(16);
    GLFWwindow* window = initWindow("GL Test");

    Core::initCore(window);
    Graphic::loadInbuiltAsserts();
    loadListeners(window);

    glEnable(GL_MULTISAMPLE);

    const Texture2D texture{ "yyz.png" };
    texture.bind();
    texture.setScale(GL_LINEAR, GL_LINEAR);

	Texture2D whiteTex{ "white" };
    const TextureRegion white{ &whiteTex };

    Draw::defTexture(white);
    Draw::texture();

    // uncomment this call to post in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f
    };

    // AttributeLayout layout;
    // layout.addFloat(2);
    // layout.addFloat(2);

    // render loop
    // -----------

    // FrameBuffer frameBuffer{ getRenderer().width, getRenderer().height };

    // getRenderer().registerSizeSyncFrames(frameBuffer);

    Events::generalUpdateEvents.on<Events::Draw>([&](const Events::Draw& d) {
        // getRenderer().frameBegin(frameBuffer);

        float offset = 200.0f;

        for (int il = -8; il <= 8; ++il) {
            const auto i = abs(static_cast<float>(il));

            Color c1{ Mathf::absin(i * OS::globalTime * 1.5f, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 1.5f + 0.33f * 2, 16 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 1.5f + 0.66f * 1, 24 / i,0.6f) + 0.45f , 0.3f + Mathf::absin(OS::globalTime * i * 1.0f, 5, 0.7f) };
            Color c2{ Mathf::absin(i * OS::globalTime * 2.5f, 32 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.5f + 0.33f * 3, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.5f + 0.66f * 2, 16 / i,0.6f) + 0.45f , 0.3f + Mathf::absin(OS::globalTime * i * 2.0f, 5, 0.7f) };
            Color c3{ Mathf::absin(i * OS::globalTime * 3.0f, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 3.0f + 0.33f * 0, 32 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 3.0f + 0.66f * 3, 24 / i,0.6f) + 0.45f , 0.3f + Mathf::absin(OS::globalTime * i * 3.0f, 5, 0.7f) };
            Color c4{ Mathf::absin(i * OS::globalTime * 2.0f, 16 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.0f + 0.33f * 1, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.0f + 0.66f * 0, 32 / i,0.6f) + 0.45f , 0.3f + Mathf::absin(OS::globalTime * i * 4.0f, 5, 0.7f) };

            Draw::vert(texture,
                (i - 0.5f) * offset, (i - 0.5f) * offset, c1, Colors::CLEAR,
                (i - 0.5f) * offset, (i + 0.5f) * offset, c2, Colors::CLEAR,
                (i + 0.5f) * offset, (i + 0.5f) * offset, c3, Colors::CLEAR,
                (i + 0.5f) * offset, (i - 0.5f) * offset, c4, Colors::CLEAR
            );
        }

        Draw::blend(Blendings::ADDICTIVE);

        offset += 12;

        for (int il = -8; il <= 8; ++il) {
            const auto i = abs(static_cast<float>(il));

            Color c4{ Mathf::absin(i * OS::globalTime * 1.5f, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 1.5f + 0.33f * 2, 16 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 1.5f + 0.66f * 1, 24 / i,0.6f) + 0.45f , 0.1f + Mathf::absin(OS::globalTime * i * 1.0f, 5, 0.3f) };
            Color c3{ Mathf::absin(i * OS::globalTime * 2.5f, 32 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.5f + 0.33f * 3, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.5f + 0.66f * 2, 16 / i,0.6f) + 0.45f , 0.1f + Mathf::absin(OS::globalTime * i * 2.0f, 5, 0.3f) };
            Color c2{ Mathf::absin(i * OS::globalTime * 3.0f, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 3.0f + 0.33f * 0, 32 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 3.0f + 0.66f * 3, 24 / i,0.6f) + 0.45f , 0.1f + Mathf::absin(OS::globalTime * i * 3.0f, 5, 0.3f) };
            Color c1{ Mathf::absin(i * OS::globalTime * 2.0f, 16 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.0f + 0.33f * 1, 24 / i,0.6f) + 0.45f, Mathf::absin(i * OS::globalTime * 2.0f + 0.66f * 0, 32 / i,0.6f) + 0.45f , 0.1f + Mathf::absin(OS::globalTime * i * 4.0f, 5, 0.3f) };

            Draw::vert(texture,
                (i - 0.5f) * offset, (i - 0.5f) * offset, c1, Colors::CLEAR,
                (i - 0.5f) * offset, (i + 0.5f) * offset, c2, Colors::CLEAR,
                (i + 0.5f) * offset, (i + 0.5f) * offset, c3, Colors::CLEAR,
                (i + 0.5f) * offset, (i - 0.5f) * offset, c4, Colors::CLEAR
            );
        }

        Vector2D&& c = Core::camera->screenCenter();
        Draw::stroke(5);
        Draw::poly(c.getX(), c.getY(), 64, 160, 0, Mathf::clamp(fmod(OS::globalTime / 5.0f, 1.051f)),
            { Colors::SKY, Colors::ROYAL, Colors::SKY, Colors::WHITE, Colors::ROYAL, Colors::SKY }
        );

        Draw::blend();

        Draw::lineAngleCenter(c.getX(), c.getY(), 45, 50);
        Draw::lineAngleCenter(c.getX(), c.getY(), -45, 50);

        Draw::flush();

        // getRenderer().frameEnd();
    });

    while (!glfwWindowShouldClose(window))
    {
        OS::update();

        Core::camera->setOrtho(static_cast<float>(getRenderer().width), static_cast<float>(getRenderer().height));

        OS::deltaTime = static_cast<float>(glfwGetTime() - OS::globalTime);

        OS::globalTime = static_cast<float>(glfwGetTime());
        OS::globalTick = static_cast<float>(glfwGetTime() * 60.0);

        getRenderer().draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // // glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    disposeInbuiltAsserts();
    Core::dispose();
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------