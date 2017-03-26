#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "graphics/mesh.h"

namespace Utils
{

QString loadShader(const QString &);
float toRadians(float);
void loadMesh(const QString &, Mesh &);

}

#endif // UTILS_H
