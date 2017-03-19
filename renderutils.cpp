#include "renderutils.h"

void RenderUtils::clearScreen(QOpenGLFunctions &f)
{
    // TODO: Stencil buffer
    f.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtils::initGraphics(QOpenGLFunctions &f)
{
    f.glClearColor(0, 0, 0, 0);

    f.glFrontFace(GL_CW);
    f.glCullFace(GL_BACK);
    f.glEnable(GL_CULL_FACE);
    f.glEnable(GL_DEPTH_TEST);

    // TODO: Depth clamp

    f.glEnable(GL_FRAMEBUFFER_SRGB);
}
