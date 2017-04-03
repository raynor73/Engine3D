#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "qopenglfunctions_selector.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"

namespace Utils
{

QString loadShader(const QString &);
float toRadians(float);
void loadMesh(const QString &, Mesh &, bool);
Texture *newTexture(QOPENGLFUNCTIONS_CLASSNAME &f, const QString &);

}

#endif // UTILS_H
