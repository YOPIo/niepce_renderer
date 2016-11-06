#include "./core/render_manager.h"

auto main(int argc, char *argv[]) -> int
{
  niepce::RenderManager manager;
  niepce::Size size(640, 480);
  manager.RenderCornellBox("cornell_box.hdr", size, 2, 2);
  return 0;
}
