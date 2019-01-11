//
//  TraceARay01.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#include "main.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "trimesh.hpp"
#include "materials.hpp"
#include "hitable.hpp"
#include "hitablearray.hpp"

// global var to enable console debug
const bool g_debugConsole = false;
const int g_maxDepth = 20;
const float g_epsHit = 1e-5;

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
	
	Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 0));
	Vec3 attenuation(0, 0, 0);
	if (world && world->Hit(r, g_epsHit, MAXFLOAT, rec))
	{
		if (depth < g_maxDepth && rec.mat && rec.mat->Scatter(r, rec, attenuation, scattered))
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

Vec3 ColorMaterialsScene(const Ray& r, Scene* world, int depth)
{
	HitRecord rec;
	
	Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 0));
	Vec3 attenuation(0, 0, 0);
	if (world && world->Hit(r, g_epsHit, MAXFLOAT, rec))
	{
		if (depth < g_maxDepth && rec.mat && rec.mat->Scatter(r, rec, attenuation, scattered))
		{
			Vec3 res = attenuation * ColorMaterialsScene(scattered, world, depth + 1);
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
	// init the scene
	Scene* scene = new Scene();
	// allocate a glass material
	Dielectric* glass = new Dielectric(1.33);
	// allocate a sphere primitive
	Sphere* bigSphere = new Sphere(Vec3(0, 0, -1), 0.5, glass);
	// add the sphere to the scene - disposing the scene also dispose the sphere and the material
	scene->AddItem(bigSphere);
	// the air bubble
	scene->AddItem(new Sphere(Vec3(0.25, -0.2, -0.8), -0.05, new Dielectric(1.2)));
	// the small green sphere on the back
	scene->AddItem(new Sphere(Vec3(-0.35, -0.4, -1), 0.1, new LambertianReflector(Vec3(0.0,0.9,0))));
	// the small red sphere on the back
	scene->AddItem(new Sphere(Vec3(0.35, -0.4, -1), 0.1, new LambertianReflector(Vec3(0.9,0.0,0))));
	// the green triangle on the floor
	scene->AddItem(new Triangle(Vec3(-2, -0.5, -2), Vec3(2, -0.5, 5), Vec3(2, -0.5, -2), new LambertianReflector(Vec3(0, .9, 0))));
	// the blue triangle on the floor
	scene->AddItem(new Triangle(Vec3(2, -0.5, 5), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, 5), new LambertianReflector(Vec3(0, 0, .9))));
	// the purple triangle on the left
	scene->AddItem(new Triangle(Vec3(-0.5, 0.5, -0.5), Vec3(-0.5, -0.5, -1.5), Vec3(-0.5, 0.5, -1.5), new MetalReflector(Vec3(.9,.2,.9))));
	// the cyan triangle on the back
	scene->AddItem(new Triangle(Vec3(-0.5, 0.5, -1.5), Vec3(0.5, -0.5, -1.5), Vec3(0.5, 0.5, -1.5), new MetalReflector(Vec3(.2,.9,.9))));
	// the yellow triangle on the right
	scene->AddItem(new Triangle(Vec3(0.5, 0.5, -0.5), Vec3(0.5, 0.5, -1.5), Vec3(0.5, -0.5, -0.5), new MetalReflector(Vec3(.9,.9,.2))));
	
	// the red cube on the top
	const int trisCnt = 8;
	const int pointsCnt = 8;
	Vec3* points = new Vec3[pointsCnt];
	int* indexes = new int[3 * trisCnt];
	if (points && indexes)
	{
		points[0] = Vec3(-0.5, 0.7, -1.5);
		points[1] = Vec3(0.5, 0.7, -1.5);
		points[2] = Vec3(0.5, 0.7, -0.5);
		points[3] = Vec3(-0.5, 0.7, -0.5);
		points[4] = Vec3(-0.5, 1.7, -1.5);
		points[5] = Vec3(0.5, 1.7, -1.5);
		points[6] = Vec3(0.5, 1.7, -0.5);
		points[7] = Vec3(-0.5, 1.7, -0.5);
		
		// bottom quad
		indexes[0] = 0;
		indexes[1] = 1;
		indexes[2] = 2;
		indexes[3] = 0;
		indexes[4] = 2;
		indexes[5] = 3;
		// top quad
		indexes[6] = 4;
		indexes[7] = 6;
		indexes[8] = 5;
		indexes[9] = 4;
		indexes[10] = 7;
		indexes[11] = 6;
		// right quad
		indexes[12] = 1;
		indexes[13] = 5;
		indexes[14] = 6;
		indexes[15] = 1;
		indexes[16] = 6;
		indexes[17] = 2;
		// left quad
		indexes[18] = 0;
		indexes[19] = 3;
		indexes[20] = 7;
		indexes[21] = 0;
		indexes[22] = 7;
		indexes[23] = 4;
//		// front quad
//		indexes[24] = 2;
//		indexes[25] = 6;
//		indexes[26] = 7;
//		indexes[27] = 2;
//		indexes[28] = 7;
//		indexes[29] = 3;
//		// back quad
//		indexes[30] = 0;
//		indexes[31] = 4;
//		indexes[32] = 5;
//		indexes[33] = 0;
//		indexes[34] = 5;
//		indexes[35] = 1;
		
		TriMesh* mesh = new TriMesh(trisCnt, new MetalReflector(Vec3(.9,.2,.2)));
		if (mesh)
		{
			mesh->SetVertexes(points, pointsCnt);
			mesh->SetTriIndexes(indexes);
			if (mesh->Init())
			{
				scene->AddItem(mesh);
				// dispose the memory used to create the mesh
				delete[] points; points = nullptr;
				delete[] indexes; indexes = nullptr;
			}
		}
	}
	// the rainbow spheres
	scene->AddItem(new Sphere(Vec3(0, -0.4, 4), 0.1, new LambertianReflector(Vec3(.9,0,0))));
	scene->AddItem(new Sphere(Vec3(0, -0.4, 3.5), 0.1, new LambertianReflector(Vec3(.9,.45,0))));
	scene->AddItem(new Sphere(Vec3(0, -0.4, 3), 0.1, new LambertianReflector(Vec3(.9,0,0))));
	scene->AddItem(new Sphere(Vec3(0, -0.4, 2.5), 0.1, new LambertianReflector(Vec3(.9,.9,0))));
	scene->AddItem(new Sphere(Vec3(0, -0.4, 2), 0.1, new LambertianReflector(Vec3(0,0.9,0))));
	scene->AddItem(new Sphere(Vec3(0, -0.4, 1.5), 0.1, new LambertianReflector(Vec3(0,0,0.9))));
	scene->AddItem(new Sphere(Vec3(0, -0.4, 1), 0.1, new LambertianReflector(Vec3(.29,0,0.51))));
	scene->AddItem(new Sphere(Vec3(0, -0.4, 0.5), 0.1, new LambertianReflector(Vec3(.58,0,0.82))));
	
	std::cout << "Scene items[" << scene->GetItemsCount() << "]\n";
	
	const Vec3 from (-3, 3, 5);
	const Vec3 to (0, 0.5, -0.5);
	const Vec3 up (0,1,0);
	const float fov = 30;
	const float aperture = 0;
	const float focusDistance = 5; //(from - to).Length();
	const int xRes = 200, yRes = 200;
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, xRes, yRes));
	
	// set image resolution
	const int nx = scene->GetCamera()->GetXRes();
	const int ny = scene->GetCamera()->GetYRes();
	const int nSamples = 1;
	
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
				// create the starting ray from  the camera
				r = scene->GetCamera()->CreateRay(u, v);
				
				// add the values returned by the ray recursively exploring the scene by hitting its items
				col += ColorMaterialsScene(r, scene, 0);
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
	
	if (scene)
	{
		delete(scene);
		scene = nullptr;
	}
	
	image.close();
}
