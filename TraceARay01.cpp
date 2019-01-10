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
#include "trimesh.hpp"
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
	const float epsHit = 1e-3;
	const int maxDepth = 20;
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
	const int objsCnt = 10;
	Hitable *objects[objsCnt];
	// the glass sphere
	objects[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Dielectric(1.2));
	// the air bubble
	objects[1] = new Sphere(Vec3(0.25, -0.2, -0.8), -0.05, new Dielectric(1.2));
	// the small green sphere on the back
	objects[2] = new Sphere(Vec3(-0.35, -0.4, -1), 0.1, new LambertianReflector(Vec3(0.0,0.9,0)));
	// the small red sphere on the back
	objects[3] = new Sphere(Vec3(0.35, -0.4, -1), 0.1, new LambertianReflector(Vec3(0.9,0.0,0)));
	// the green triangle on the floor
	objects[4] = new Triangle(Vec3(-2, -0.5, -2), Vec3(2, -0.5, -0), Vec3(2, -0.5, -2), new LambertianReflector(Vec3(0, .9, 0)));
	// the blue triangle on the floor
	objects[5] = new Triangle(Vec3(2, -0.5, -0), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, -0), new LambertianReflector(Vec3(0, 0, .9)));
	// the purple triangle on the left
	objects[6] = new Triangle(Vec3(-0.5, 0.5, -0.5), Vec3(-0.5, -0.5, -1.5), Vec3(-0.5, 0.5, -1.5), new MetalReflector(Vec3(.9,.2,.9)));
	// the cyan triangle on the back
	objects[7] = new Triangle(Vec3(-0.5, 0.5, -1.5), Vec3(0.5, -0.5, -1.5), Vec3(0.5, 0.5, -1.5), new MetalReflector(Vec3(.2,.9,.9)));
	// the yellow triangle on the right
	objects[8] = new Triangle(Vec3(0.5, 0.5, -0.5), Vec3(0.5, 0.5, -1.5), Vec3(0.5, -0.5, -0.5), new MetalReflector(Vec3(.9,.9,.2)));
//	 the red quadrangle on the front
	const int trisCnt = 2;
	const int pointsCnt = 4;
	Vec3* points = new Vec3[pointsCnt];
	int* indexes = new int[3 * trisCnt];
	if (points && indexes)
	{
		points[0] = Vec3(-0.5, 0.7, -1.5);
		points[1] = Vec3(0.5, 0.7, -0.5);
		points[2] = Vec3(-0.5, 0.7, -0.5);
		points[3] = Vec3(0.5, 0.7, -1.5);
		
		
		indexes[0] = 0;
		indexes[1] = 1;
		indexes[2] = 2;
		indexes[3] = 0;
		indexes[4] = 3;
		indexes[5] = 1;
		
		TriMesh* mesh = new TriMesh(trisCnt, new MetalReflector(Vec3(.9,.2,.2)));
		if (mesh)
		{
			mesh->SetVertexes(points, pointsCnt);
			mesh->SetTriIndexes(indexes);
			if (mesh->Init())
			{
				objects[9] = mesh;
				// dispose the memory used to create the mesh
				delete[] points; points = nullptr;
				delete[] indexes; indexes = nullptr;
			}
		}
	}
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
