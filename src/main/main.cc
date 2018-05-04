#include "../core/niepce.h"
#include "../core/thread_pool.h"
#include "../core/assembled_tiles.h"
#include "../math/point3f.h"
#include "../renderer/path_tracer.h"
#include "../shape/sphere.h"
/*
// ---------------------------------------------------------------------------
*/
using namespace niepce;
/*
// ---------------------------------------------------------------------------
*/
Sphere spheres[] = {//Scene: radius, position, emission, color, material
  Sphere(1e5, Point3f( 1e5+1,40.8,81.6), Vector3f(),Vector3f(.75,.25,.25),DIFF),//Left
  Sphere(1e5, Point3f(-1e5+99,40.8,81.6),Vector3f(),Vector3f(.25,.25,.75),DIFF),//Rght
  Sphere(1e5, Point3f(50,40.8, 1e5),     Vector3f(),Vector3f(.75,.75,.75),DIFF),//Back
  Sphere(1e5, Point3f(50,40.8,-1e5+170), Vector3f(),Vector3f(),           DIFF),//Frnt
  Sphere(1e5, Point3f(50, 1e5, 81.6),    Vector3f(),Vector3f(.75,.75,.75),DIFF),//Botm
  Sphere(1e5, Point3f(50,-1e5+81.6,81.6),Vector3f(),Vector3f(.75,.75,.75),DIFF),//Top
  Sphere(16.5,Point3f(27,16.5,47),       Vector3f(),Vector3f(1,1,1)*.999, SPEC),//Mirr
  Sphere(16.5,Point3f(73,16.5,78),       Vector3f(),Vector3f(1,1,1)*.999, REFR),//Glas
  Sphere(600, Point3f(50,681.6-.27,81.6),Vector3f(12,12,12),  Vector3f(), DIFF) //Lite
};
/*
// ---------------------------------------------------------------------------
*/
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }
/*
// ---------------------------------------------------------------------------
*/
inline bool intersect(const Ray &r, double &t, int &id){
  double n=sizeof(spheres)/sizeof(Sphere), d, inf=t=1e20;
  for(int i=int(n);i--;) if((d=spheres[i].intersect(r))&&d<t){t=d;id=i;}
  return t<inf;
}
/*
// ---------------------------------------------------------------------------
*/
Vector3f radiance(const Ray &r, int depth, unsigned short *Xi){
  double t;                               // distance to intersection
  int id=0;                               // id of intersected object
  if (!intersect(r, t, id)) return Vector3f(); // if miss, return black
  const Sphere& obj = spheres[id];        // the hit object
  Vector3f x=r.o+r.d*t, n=(x-obj.p).norm(), nl=n.dot(r.d)<0?n:n*-1, f=obj.c;
  double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl
  if (++depth>5) if (erand48(Xi)<p) f=f*(1/p); else return obj.e; //R.R.
  if (obj.refl == DIFF){                  // Ideal DIFFUSE reflection
    double r1=2*M_PI*erand48(Xi), r2=erand48(Xi), r2s=sqrt(r2);
    Vector3f w=nl, u=((fabs(w.x)>.1?Vector3f(0,1):Vector3f(1))%w).norm(), v=w%u;
    Vector3f d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
    return obj.e + f.mult(radiance(Ray(x,d),depth,Xi));
  } else if (obj.refl == SPEC)            // Ideal SPECULAR reflection
    return obj.e + f.mult(radiance(Ray(x,r.d-n*2*n.dot(r.d)),depth,Xi));
  Ray reflRay(x, r.d-n*2*n.dot(r.d));     // Ideal dielectric REFRACTION
  bool into = n.dot(nl)>0;                // Ray from outside going in?
  double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;
  if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection
    return obj.e + f.mult(radiance(reflRay,depth,Xi));
  Vector3f tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
  double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
  double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
  return obj.e + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette
    radiance(reflRay,depth,Xi)*RP:radiance(Ray(x,tdir),depth,Xi)*TP) :
    radiance(reflRay,depth,Xi)*Re+radiance(Ray(x,tdir),depth,Xi)*Tr);
}
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto RenderScene () -> void
{
  PathTracer pt;
  std::vector <std::future <void>> futures;
  ThreadPool worker (std::thread::hardware_concurrency ());

  for (int y = 0; y < 5; ++y)
  {
    for (int x = 0; x < 5; ++x)
    {
      auto func = std::bind (&PathTracer::Render, pt);
      futures.emplace_back (worker.Enqueue (func));
    }
  }

  for (int i = 0; i < futures.size (); ++i)
  {
    futures[i].wait ();
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
int main (int argc, char* argv[])
{
  niepce::AssembledTiles tiles (std::make_pair (960, 540),
                                std::make_pair ( 32,  18));
  return 0;
}
