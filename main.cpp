//
//  main.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#include "main.hpp"
#include "camera.hpp"
#include "framebuffer.hpp"
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
const int g_samples = 16;
const int g_xRes = 400;
const int g_yRes = 800;

void Color(Vec3& col, Vec3& nrm, const Ray& r, Scene* world, int depth = 0)
{
	HitRecord rec;
	if (world && world->Hit(r, g_epsHit, MAXFLOAT, rec))
	{
		Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 0));
		Vec3 attenuation(0, 0, 0);
		if (depth < g_maxDepth && rec.mat && rec.mat->Scatter(r, rec, attenuation, scattered))
		{
			Color(col, nrm, scattered, world, depth + 1);
			nrm = Vec3(rec.n.x() + 1, rec.n.y() + 1, rec.n.z() + 1) * 0.5;
			col *= attenuation;
			return;
		}

		col = Vec3(1, 0, 0);
		return;
	}
	
	// compute the background color
	const float blend = 0.5 * (r.GetDirection().y() + 1.0);
	col = Lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), blend);
	nrm = Vec3(0,0,0);
	return;
}

int main()
{
	// init the scene
	Scene* scene = new Scene();
	// allocate a glass material
	Dielectric* glass = new Dielectric(1.33);
	// allocate a sphere primitive
	Sphere* bigSphere = new Sphere("bigSphere", Vec3(0, 0, -1), 0.5, glass);
	// add the sphere to the scene - disposing the scene also dispose the sphere and the material
	scene->AddItem(bigSphere);
	// the air bubble
	scene->AddItem(new Sphere("airSphere", Vec3(0.25, -0.2, -0.8), -0.05, new Dielectric(1.2)));
	// the small green sphere on the back
	scene->AddItem(new Sphere("greenSphere", Vec3(-0.35, -0.4, -1), 0.1, new LambertianReflector(Vec3(0.0,0.9,0))));
	// the small red sphere on the back
	scene->AddItem(new Sphere("redSphere", Vec3(0.35, -0.4, -1), 0.1, new LambertianReflector(Vec3(0.9,0.0,0))));
	// the green triangle on the floor
	scene->AddItem(new Triangle("greenTri", Vec3(-2, -0.5, -2), Vec3(2, -0.5, 5), Vec3(2, -0.5, -2), new LambertianReflector(Vec3(0, .9, 0))));
	// the blue triangle on the floor
	scene->AddItem(new Triangle("blueTri", Vec3(2, -0.5, 5), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, 5), new LambertianReflector(Vec3(0, 0, .9))));
	// the purple triangle on the left
	scene->AddItem(new Triangle("purpleTri", Vec3(-0.5, 0.5, -0.5), Vec3(-0.5, -0.5, -1.5), Vec3(-0.5, 0.5, -1.5), new MetalReflector(Vec3(.9,.2,.9))));
	// the cyan triangle on the back
	scene->AddItem(new Triangle("cyanTri", Vec3(-0.5, 0.5, -1.5), Vec3(0.5, -0.5, -1.5), Vec3(0.5, 0.5, -1.5), new MetalReflector(Vec3(.2,.9,.9))));
	// the yellow triangle on the right
	scene->AddItem(new Triangle("yellowTri", Vec3(0.5, 0.5, -0.5), Vec3(0.5, 0.5, -1.5), Vec3(0.5, -0.5, -0.5), new MetalReflector(Vec3(.9,.9,.2))));
	
	// the red cube on the top
	const int trisCnt = 12;
	const int pointsCnt = 8;
	Vec3* points = new Vec3[pointsCnt];
	int* indexes = new int[3 * trisCnt];
	if (points && indexes)
	{
		points[0] = Vec3(-0.5, 0.7, 0);
		points[1] = Vec3(0.5, 0.7, 0);
		points[2] = Vec3(0.5, 0.7, 1);
		points[3] = Vec3(-0.5, 0.7, 1);
		points[4] = Vec3(-0.5, 1.7, 0);
		points[5] = Vec3(0.5, 1.7, 0);
		points[6] = Vec3(0.5, 1.7, 1);
		points[7] = Vec3(-0.5, 1.7, 1);
		
		// bottom quad 0
		indexes[0] = 0;
		indexes[1] = 1;
		indexes[2] = 2;
		indexes[3] = 0;
		indexes[4] = 2;
		indexes[5] = 3;
		// right quad 2
		indexes[6] = 1;
		indexes[7] = 5;
		indexes[8] = 6;
		indexes[9] = 1;
		indexes[10] = 6;
		indexes[11] = 2;
		// top quad 4
		indexes[12] = 4;
		indexes[13] = 6;
		indexes[14] = 5;
		indexes[15] = 4;
		indexes[16] = 7;
		indexes[17] = 6;
		// left quad 6
		indexes[18] = 0;
		indexes[19] = 3;
		indexes[20] = 7;
		indexes[21] = 0;
		indexes[22] = 7;
		indexes[23] = 4;
		// front quad
		indexes[24] = 2;
		indexes[25] = 6;
		indexes[26] = 7;
		indexes[27] = 2;
		indexes[28] = 7;
		indexes[29] = 3;
		// back quad
		indexes[30] = 0;
		indexes[31] = 4;
		indexes[32] = 5;
		indexes[33] = 0;
		indexes[34] = 5;
		indexes[35] = 1;
		
		TriMesh* mesh = new TriMesh("cubeMesh", trisCnt, new MetalReflector(Vec3(.05,.1,.07), .05));
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
	scene->AddItem(new Sphere("redSphere", Vec3(0, -0.45, 4), 0.05, new LambertianReflector(Vec3(.9,0,0))));
	scene->AddItem(new Sphere("orangeSphere", Vec3(0, -0.45, 3.33), 0.05, new LambertianReflector(Vec3(.9,.45,0))));
	scene->AddItem(new Sphere("yellowSphere", Vec3(0, -0.45, 2.66), 0.05, new LambertianReflector(Vec3(.9,.9,0))));
	scene->AddItem(new Sphere("greenSphere", Vec3(0, -0.45, 2), 0.05, new LambertianReflector(Vec3(0,0.9,0))));
	scene->AddItem(new Sphere("blueSphere", Vec3(0, -0.45, 1.33), 0.05, new LambertianReflector(Vec3(0,0,0.9))));
	scene->AddItem(new Sphere("indigoSphere", Vec3(0, -0.45, 0.66), 0.05, new LambertianReflector(Vec3(.29,0,0.51))));
	scene->AddItem(new Sphere("purpleSphere", Vec3(0, -0.45, 0), 0.05, new LambertianReflector(Vec3(.58,0,0.82))));
	
	const Vec3 from (0, -0.3, 5);
	const Vec3 to (0, 0.5, -0.5);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0.05;
	const float focusDistance = 6; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	// set image resolution
	const int nx = scene->GetCamera()->GetXRes();
	const int ny = scene->GetCamera()->GetYRes();
	
	std::ofstream rgbImage, nrmImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal.ppm", std::ofstream::out);

	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;

	// allocate temporary data
	int lrs = 0; //  last refreshed sample
	float u = 0, v = 0; //
	Vec3 rgb(0,0,0);
	Vec3 nrm(0,0,0);
	Ray r(Vec3 (0,0,0), Vec3(0,0,0));
	
	// loop over samples
	for (int s = 1; s < g_samples + 1; ++s)
	{
		std::cout << "Rendering [" << s << "/" << g_samples << "]\n";
		float inv_s = 1.0 / float(s);
		
		// loop over the pixels to compute their colors
		for (int j = ny - 1; j>= 0; --j)
		{
			const float inv_ny = 1.0 / float(ny);
			for (int i = 0; i < nx; ++i)
			{
				const float inv_nx = 1.0 / float(nx);
				
				u = float(i + drand48()) * inv_nx;
				v = float(j + drand48()) * inv_ny;
				
				// create the starting ray from  the camera
				r = scene->GetCamera()->CreateRay(u, v);

				// add the values returned by the ray recursively exploring the scene by hitting its items
				Color(rgb, nrm, r, scene);

				// update with color
				fb->GetColor()[j][3 * i + 0] = (fb->GetColor()[j][3 * i + 0] * ( s - 1 ) + rgb[0]) * inv_s;
				fb->GetColor()[j][3 * i + 1] = (fb->GetColor()[j][3 * i + 1] * ( s - 1 ) + rgb[1]) * inv_s;
				fb->GetColor()[j][3 * i + 2] = (fb->GetColor()[j][3 * i + 2] * ( s - 1 ) + rgb[2]) * inv_s;
				
				// update with normal
				fb->GetNormal()[j][3 * i + 0] = (fb->GetNormal()[j][3 * i + 0] * ( s - 1 ) + nrm[0]) * inv_s;
				fb->GetNormal()[j][3 * i + 1] = (fb->GetNormal()[j][3 * i + 1] * ( s - 1 ) + nrm[1]) * inv_s;
				fb->GetNormal()[j][3 * i + 2] = (fb->GetNormal()[j][3 * i + 2] * ( s - 1 ) + nrm[2]) * inv_s;

				if (g_debugConsole)
				{
					std::cout << "uv [" << u << ", " << v << "] / dir [" << r.GetDirection().x() << ", " << r.GetDirection().y() << ", " << r.GetDirection().z() << "] / col ["<< rgb[0] <<", " << ", "<< rgb[1] << ", " << rgb[2] << "]\n";
				}
			}
		}
		
		// update the framebuffer with an incremental sample count
		if (s >= lrs * 2)
		{
			std::cout << "Spooling [" << s << "]\n";
			fb->SpoolToPPM(rgbImage, "color");
			fb->SpoolToPPM(nrmImage, "normal");
			lrs = s;
		}
	}
	rgbImage.close();
	nrmImage.close();

	// dispose the framebuffer
	if (fb)
	{
		delete fb;
		fb = nullptr;
	}
	
	// dispose the scene
	if (scene)
	{
		delete(scene);
		scene = nullptr;
	}
}
