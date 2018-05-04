/*!
 * @file path_tracer.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/23
 * @details 
 */
#include "path_tracer.h"
#include "../core/bounds2f.h"
#include "../core/ray.h"
#include "../math/point3f.h"
#include "../math/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
PathTracer::PathTracer (const RenderSettings& settings) :
  settings_ (settings),
  pool_     (std::thread::hardware_concurrency ())
{}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Render (const Bounds2f& tile) const -> void
{
  const Point2f min = tile.Min ();
  const Point2f max = tile.Max ();

  const unsigned int resolution_width
    = settings_.GetItem (RenderSettings::Item::kWidth);
  const unsigned int resolution_height
    = settings_.GetItem (RenderSettings::Item::kHeight);
  const unsigned int num_sample
    = settings_.GetItem (RenderSettings::Item::kNumSamples);

  Ray cam(Point3f(50,52,295.6), Vector3f(0,-0.042612,-1).Normalize ());
  Vector3f cx = Vector3f (resolution_width*.5135/resolution_height);
  Vector3f cy = Cross (cx, cam.Direction ()).Normalize () * 0.5135;

  for (unsigned int y = min.Y (); y <= max.Y (); ++y)
  {
    // TODO: Delete
    // Magic numbers for random numbers.
    unsigned short Xi[3] = {0, 0, static_cast<unsigned short> (y * y * y)};
    for (unsigned int x = min.X (); x <= max.X (); ++x)
    {
      const unsigned int idx = y * resolution_width + x;
      for (unsigned sy = 0; sy < 2; ++sy)
      {
        // i=(h-y-1)*w+x
        for (unsigned int sx = 0; sx < 2; ++sx)
        {
          Vector3f r;
          for (unsigned int s = 0; s < 4; ++s)
          {
            const Float r1 = 2 * erand48(Xi);
            const Float r2 = 2 * erand48(Xi);
            const Float dx = r1 < 1 ? std::sqrt (r1) - 1 : 1 - std::sqrt (2 - r1);
            const Float dy = r2 < 1 ? std::sqrt (r2) - 1 : 1 - std::sqrt (2 - r2);
            const Vector3f d = cx * (((sx+.5 + dx) / 2 + x) / resolution_width  - 0.5)
                             + cy * (((sy+.5 + dy) / 2 + y) / resolution_height - 0.5)
                             + cam.Direction ();
            const Ray ray (cam.Origin () + d * 140,
                           d.Normalized ());
            r = r + radiance(ray,0,Xi)*(1./num_sample);
          }
          image_[idx] = r;
        }
      }
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Contribution (const Ray& ray) -> Vector3f
{
  
  double t;                               // distance to intersection
  int id=0;                               // id of intersected object
  if (!intersect(r, t, id)) return Vec(); // if miss, return black
  const Sphere &obj = spheres[id];        // the hit object
  Vec x=r.o+r.d*t, n=(x-obj.p).norm(), nl=n.dot(r.d)<0?n:n*-1, f=obj.c;
  double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl
  if (++depth>5) if (erand48(Xi)<p) f=f*(1/p); else return obj.e; //R.R.
  if (obj.refl == DIFF){                  // Ideal DIFFUSE reflection
    double r1=2*M_PI*erand48(Xi), r2=erand48(Xi), r2s=sqrt(r2);
    Vec w=nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
    Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
    return obj.e + f.mult(radiance(Ray(x,d),depth,Xi));
  } else if (obj.refl == SPEC)            // Ideal SPECULAR reflection
    return obj.e + f.mult(radiance(Ray(x,r.d-n*2*n.dot(r.d)),depth,Xi));
  Ray reflRay(x, r.d-n*2*n.dot(r.d));     // Ideal dielectric REFRACTION
  bool into = n.dot(nl)>0;                // Ray from outside going in?
  double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;
  if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection
    return obj.e + f.mult(radiance(reflRay,depth,Xi));
  Vec tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
  double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
  double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
  return obj.e + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette
    radiance(reflRay,depth,Xi)*RP:radiance(Ray(x,tdir),depth,Xi)*TP) :
    radiance(reflRay,depth,Xi)*Re+radiance(Ray(x,tdir),depth,Xi)*Tr);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
