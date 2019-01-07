//
//  TraceARay01.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#include "TraceARay01.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "materials.hpp"
#include "hitable.hpp"
#include "hitablearray.hpp"

// global var to enable console debug
bool g_debugConsole = false;

Vec3 ColorNormalsHitables(const Ray& r, HitableArray* world)
{
	HitRecord rec;
	if (world && world->Hit(r, 0.0, MAXFLOAT, rec))
	{
		const Vec3 colorFromNormal = Vec3(
																			rec.n.x() + 1,
																			rec.n.y() + 1,
																			rec.n.z() + 1) * 0.5;
		return colorFromNormal;
	}
	
	// compute the background color
	const Vec3 ray_direction = r.GetDirection();
	const float blend = 0.5 * (ray_direction.y() + 1.0);
	return Lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), blend);
}

Vec3 ColorDiffuseHitables(const Ray& r, HitableArray* world)
{
	HitRecord rec;
	const float epsHit = 1e-5;
	if (world && world->Hit(r, epsHit, MAXFLOAT, rec))
	{
		const Vec3 target = rec.p + rec.n + RandomPointOnSphere();
		// recursively compute the color
		const Vec3 color = ColorDiffuseHitables( Ray( rec.p, target - rec.p), world) * 0.5;
		return color;
	}
	
	// compute the background color
	const float blend = 0.5 * (r.GetDirection().y() + 1.0);
	return Lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), blend);
}

Vec3 ColorMaterialsHitables(const Ray& r, HitableArray* world, int depth)
{
	HitRecord rec;
	const float epsHit = 1e-2;
	const int maxDepth = 10;
	Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 0));
	Vec3 attenuation(0, 0, 0);
	if (world && world->Hit(r, epsHit, MAXFLOAT, rec))
	{
		if (depth < maxDepth && rec.mat && rec.mat->Scatter(r, rec, attenuation, scattered))
		{
			Vec3 res = attenuation * ColorMaterialsHitables(scattered, world, depth + 1);
			return res;
		}
		
		return Vec3(0, 0, 0);
	}
	
	// compute the background color
	const float blend = 0.5 * (r.GetDirection().y() + 1.0);
	return Lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), blend);
}

int main()
{
	// define the world (by specifying the hitable elements)
	const int objsCnt = 6;
	Hitable *objects[objsCnt];
	objects[0] = new Sphere(Vec3(0, 0, -1), 0.5, new MetalReflector(Vec3(.9,.9,.9)));
	objects[1] = new Triangle(Vec3(-2, -0.5, -2), Vec3(2, -0.5, -0), Vec3(2, -0.5, -2), new MetalReflector(Vec3(.2,.9,.2)));
	objects[2] = new Triangle(Vec3(2, -0.5, -0), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, -0), new MetalReflector(Vec3(.2,.2,.9)));
	objects[3] = new Triangle(Vec3(-0.5, 0.5, -0.5), Vec3(-0.5, -0.5, -1), Vec3(-0.5, 0.5, -1), new MetalReflector(Vec3(.9,.2,.9)));
	objects[4] = new Triangle(Vec3(-0.5, 0.5, -1), Vec3(0.5, -0.5, -1), Vec3(0.5, 0.5, -1), new MetalReflector(Vec3(.2,.9,.9)));
	objects[5] = new Triangle(Vec3(0.5, 0.5, -0.5), Vec3(0.5, 0.5, -1), Vec3(0.5, -0.5, -0.5), new MetalReflector(Vec3(.9,.9,.2)));
	HitableArray *world = new HitableArray(objects, objsCnt);
	
	Camera cam (Vec3 (0.0, 0.0, 0.0), 4.0, 200, 200);
	// set image resolution
	const int nx = cam.GetXRes();
	const int ny = cam.GetYRes();
	const int nSamples = 32;
	
	// allocate the final image
	std::ofstream image;
	image.open("/Users/riccardogigante/Desktop/test.ppm", std::ofstream::out);
	// write the image header
	image << "P3\n" << nx << " " << ny << "\n255\n";
	
	// loop over the pixel to compute their colors
	for (int j = ny - 1; j>= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			float u = 0, v = 0;
			
			Vec3 col(0,0,0);
			Ray r(Vec3 (0,0,0), Vec3(0,0,0));
			for (int s = 0; s < nSamples; ++s)
			{
				u = float(i + drand48()) / float(nx);
				v = float(j + drand48()) / float(ny);
				r = cam.CreateRay(u, v);
				
				col += ColorMaterialsHitables(r, world, 0);
			}
			
			// divide the final value by the number of samples (get the average value)
			col = col / float(nSamples);
			
			// apply some "minimal" gamma correction (gamma 2 -> x^1/2)
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			
			// map the value returned by the ray to a meaningful color
			const int ir = int(255.99 * col.r());
			const int ig = int(255.99 * col.g());
			const int ib = int(255.99 * col.b());

 			// spool the color information to file
			image << ir << " " << ig << " " << ib << "\n";
			
			if (g_debugConsole)
			{
				std::cout << "uv [" << u << ", " << v << "] / dir [" << r.GetDirection().x() << ", " << r.GetDirection().y() << ", " << r.GetDirection().z() << "] / col ["<< ir <<", " << ", "<< ig << ", " << ib << "]\n";
			}

		}
	}
	
	if (world)
	{
		delete(world);
		world = nullptr;
	}
	image.close();
}
