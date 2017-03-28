#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "graphics/mesh.h"
#include "graphics/texture.h"

namespace Utils
{

QString loadShader(const QString &);
float toRadians(float);
void loadMesh(const QString &, Mesh &);
Texture loadTexture(const QString &);

}

#endif // UTILS_H
