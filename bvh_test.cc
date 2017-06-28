#include "core/niepce.h"
#include "scene/scene.h"
#include "materials/material.h"
#include "shapes/triangle_mesh.h"
#include "shapes/triangle.h"

using namespace niepce;

int main(int argc, char *argv[])
{
  Scene scene;
  scene.MakeCornellBox();
  return 0;
}
