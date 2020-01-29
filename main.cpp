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
#include "matrix.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "trimesh.hpp"
#include "materials.hpp"
#include "hitable.hpp"
#include "hitableinstance.hpp"

// global var to enable console debug
const int g_xRes = 64;
const int g_yRes = 64;

int main()
{
//	MatrixTests();
//	return 0;
	
	{
		// init the scene
		Scene* scene = new Scene();
		
		// allocate lambertians
		LambertianReflector*  white = new LambertianReflector("white", Vec3(0.9, 0.9, 0.9));
		scene->AddMaterial(white);
		
		// allocate metals
		MetalReflector*  red = new MetalReflector("red", Vec3(0.9, 0, 0));
		MetalReflector*  green = new MetalReflector("green", Vec3(0, 0.9, 0));
		MetalReflector*  blue = new MetalReflector("blue", Vec3(0, 0, 0.9));
		scene->AddMaterial(red);
		scene->AddMaterial(green);
		scene->AddMaterial(blue);
		
//		scene->AddItem(new Triangle("tr1", Vec3(-2, -0.5, -2), Vec3(2, -0.5, 5), Vec3(2, -0.5, -2), white));
//		scene->AddItem(new Triangle("tri2", Vec3(2, -0.5, 5), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, 5), white));
		
		Triangle2* tri = new Triangle2(Vec3(-0.5, 0.5, -0.5), Vec3(0.5, -0.5, -0.5), Vec3(0.5, 0.5, -0.5), red);
//		scene->AddItem(tri);
		tri->SetName("triRed");
		Triangle2* tri2 = new Triangle2(Vec3(-0.5, 0.5, 0), Vec3(0.5, -0.5, 0), Vec3(0.5, 0.5, 0), green);
		tri2->SetName("triGreen");
		scene->AddItem(tri2);
		
		HitableInstance* instance2 = new HitableInstance(tri);
		Matrix trf;
		trf.Reset();
		trf.AddOffset(0, 0, 1);
		instance2->AddMatrix(trf);
		instance2->Init();
		instance2->SetName("instanceRed");
		scene->AddItem(instance2);
		
		const Vec3 from (0,0,2);
		const Vec3 to (0,0,0);
		const Vec3 up (0,1,0);
		const float fov = 40;
		const float aperture = 0; //0.05;
		const float focusDistance = 5; //(from - to).Length();
		
		// add camera to the scene
		scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
		
		Vec3 pixelCol;
//		scene->ColorPixel(0, 0); // bottom-left
//		scene->ColorPixel(63, 0); // bottom-right
//		scene->ColorPixel(63, 63); // top-right
//		scene->ColorPixel(0, 63); //top-left
		
		scene->ColorPixel(60, 60, 0, true); //hit top-right
		scene->ColorPixel(53, 53, 0, true); //hit top-right
		scene->ColorPixel(10, 10, 0, true); //no hit bottom-left
#if 1
		Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
		if (!fb)
			return -1;
		
		std::ofstream rgbImage, nrmImage;
		rgbImage.open("/Users/riccardogigante/Desktop/test_color.ppm", std::ofstream::out);
		nrmImage.open("/Users/riccardogigante/Desktop/test_normal.ppm", std::ofstream::out);
		
		scene->Render(1, 0, fb, rgbImage, nrmImage);
		
		rgbImage.close();
		nrmImage.close();
		
		// dispose the framebuffer
		if (fb)
		{
			delete fb;
			fb = nullptr;
		}
#endif
		
		// dispose the scene (camera, items and materials)
		if (scene)
		{
			delete(scene);
			scene = nullptr;
		}
		
		return 0;
	}
	
	// init the scene
	Scene* scene = new Scene();
	
  	//allocate a glass
	Dielectric* glass = new Dielectric("glass", 1.33);
	scene->AddMaterial(glass);
	// allocate lambertians
	LambertianReflector*  green = new LambertianReflector("green", Vec3(0.0, 0.9, 0.0));
	scene->AddMaterial(green);
	LambertianReflector*  red   = new LambertianReflector("red", Vec3(0.9, 0.0, 0.0));
	scene->AddMaterial(red);
	LambertianReflector*  blue  = new LambertianReflector("blue", Vec3(0.0, 0.0, 0.9));
	scene->AddMaterial(blue);
	LambertianReflector* orange = new LambertianReflector("orange", Vec3(.9,.45,0));
	scene->AddMaterial(orange);
	LambertianReflector* yellow = new LambertianReflector("yellow", Vec3(.9,.9,0));
	scene->AddMaterial(yellow);
	LambertianReflector* indigo = new LambertianReflector("indigo", Vec3(.29,0,0.51));
	scene->AddMaterial(indigo);
	LambertianReflector* purple = new LambertianReflector("purple", Vec3(.58,0,0.82));
	scene->AddMaterial(purple);
	// allocate metals
	MetalReflector* purpleM = new MetalReflector("purpleM", Vec3(.9,.2,.9));
	scene->AddMaterial(purpleM);
	MetalReflector* cyanM   = new MetalReflector("cyanM", Vec3(.2,.9,.9));
	scene->AddMaterial(cyanM);
	MetalReflector* yellowM = new MetalReflector("yellowM", Vec3(.9,.9,.2));
	scene->AddMaterial(yellowM);
	MetalReflector* greyM = new MetalReflector("greyM", Vec3(.5,.5,.5));
	scene->AddMaterial(greyM);
	
	
	// allocate a sphere primitive
	Sphere* bigSphere = new Sphere("bigSphere", Vec3(0, 0, -1), 0.5, glass);
	// add the sphere to the scene - disposing the scene also dispose the sphere and the material
	scene->AddItem(bigSphere);
	// the air bubble
	scene->AddItem(new Sphere("airSphere", Vec3(0.25, -0.2, -0.8), -0.05, glass));
	// the small green sphere on the back
	scene->AddItem(new Sphere("greenSphere", Vec3(-0.35, -0.4, -1), 0.1, green));
	// the small red sphere on the back
	scene->AddItem(new Sphere("redSphere", Vec3(0.35, -0.4, -1), 0.1, red));
	// the green triangle on the floor
	scene->AddItem(new Triangle("greenTri", Vec3(-2, -0.5, -2), Vec3(2, -0.5, 5), Vec3(2, -0.5, -2), green));
	// the blue triangle on the floor
	scene->AddItem(new Triangle("blueTri", Vec3(2, -0.5, 5), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, 5), blue));
	// the purple triangle on the left
	scene->AddItem(new Triangle("purpleTri", Vec3(-0.5, 0.5, -0.5), Vec3(-0.5, -0.5, -1.5), Vec3(-0.5, 0.5, -1.5), purpleM));
	// the cyan triangle on the back
	scene->AddItem(new Triangle("cyanTri", Vec3(-0.5, 0.5, -1.5), Vec3(0.5, -0.5, -1.5), Vec3(0.5, 0.5, -1.5), cyanM));
	// the yellow triangle on the right
	scene->AddItem(new Triangle("yellowTri", Vec3(0.5, 0.5, -0.5), Vec3(0.5, 0.5, -1.5), Vec3(0.5, -0.5, -0.5), yellowM));


	// the red cube on the top
	const int trisCnt = 12;//12;
	const int pointsCnt = 8;
	Vec3* points = new Vec3[pointsCnt];
	int* indexes = new int[3 * trisCnt];
	TriMesh* mesh = nullptr;
	if (points && indexes)
	{
		points[0] = Vec3(-0.5, -0.5, -0.5);
		points[1] = Vec3(0.5, -0.5, -0.5);
		points[2] = Vec3(0.5, -0.5, 0.5);
		points[3] = Vec3(-0.5, -0.5, 0.05);
		points[4] = Vec3(-0.5, 0.5, -0.5);
		points[5] = Vec3(0.5, 0.5, -0.5);
		points[6] = Vec3(0.5, 0.5, 0.05);
		points[7] = Vec3(-0.5, 0.5, 0.5);

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

		mesh = new TriMesh("cubeMesh", trisCnt, greyM);
		if (mesh)
		{
			// test the transformation stack
			// allocate a transformation and define it
			Matrix mtx;

			// define first transformation
			mtx.AddUniformScale(.5);
			mtx.AddRotationY(90);
			mtx.AddRotationX(15);
			mtx.AddOffset(0,1,2);
			// add the first transformation to the stack
			mtx.AddNonUniformScale(3, 2, 1);
			mesh->AddMatrix(mtx);

			// define second transformation
			// reset the transformation for a new one
			mtx.Reset();
			mtx.AddRotationZ(33);
			// add the second transformation to the stack
			mesh->AddMatrix(mtx);

			// define third transformation
			// reset the transformation for a new one
			mtx.Reset();
			mtx.AddRotationZ(-5);
			// add the second transformation to the stack
			mesh->AddMatrix(mtx);

			// define forth transformation
			// reset the transformation for a new one
			mtx.Reset();
			mtx.AddOffset(0,-0.5,0);
			mtx.AddRotationY(-5);
			// add the first transformation to the stack
			mesh->AddMatrix(mtx);

			// define fifth transformation
			// reset the transformation for a new one
			mtx.Reset();
			mtx.AddUniformScale(.3);
			// add the first transformation to the stack
			mesh->AddMatrix(mtx);

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
	
	HitableInstance* inst = new HitableInstance(mesh);
	Matrix trf2;
	trf2.AddOffset(1.05,0,0);
	trf2.AddNonUniformScale(1, .5, 1);
	inst->AddMatrix(trf2);
	inst->Init();
	scene->AddItem(inst);
	
	HitableInstance* inst2 = new HitableInstance(new Triangle("cyanTri", Vec3(-0.5, 0.5, -1.5), Vec3(0.5, -0.5, -1.5), Vec3(0.5, 0.5, -1.5), cyanM));
	trf2.Reset();
	trf2.AddOffset(-1,1,0);
//		trf2.AddNonUniformScale(.5, 1, 1);
	inst2->AddMatrix(trf2);
	inst2->Init();
	scene->AddItem(inst2);
	
	HitableInstance* inst3 = new HitableInstance(new Sphere("bigSphere", Vec3(0, 0, 0), 0.2, glass));
	trf2.Reset();
	trf2.AddOffset(-.5, .5, 0);
	trf2.AddNonUniformScale(1, 1, .33);
	inst3->AddMatrix(trf2);
	inst3->Init();
	scene->AddItem(inst3);

	// the rainbow spheres
	scene->AddItem(new Sphere("redSphere", Vec3(0, -0.45, 4), 0.05, red));
	scene->AddItem(new Sphere("orangeSphere", Vec3(0, -0.45, 3.33), 0.05, orange));
	scene->AddItem(new Sphere("yellowSphere", Vec3(0, -0.45, 2.66), 0.05, yellow));
	scene->AddItem(new Sphere("greenSphere", Vec3(0, -0.45, 2), 0.05, green));
	scene->AddItem(new Sphere("blueSphere", Vec3(0, -0.45, 1.33), 0.05, blue));
	scene->AddItem(new Sphere("indigoSphere", Vec3(0, -0.45, 0.66), 0.05, indigo));
	scene->AddItem(new Sphere("purpleSphere", Vec3(0, -0.45, 0), 0.05, purple));
	
	const Vec3 from (0,0,5);
	const Vec3 to (0,0.5,0);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0; //0.05;
	const float focusDistance = 5; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	std::ofstream rgbImage, nrmImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal.ppm", std::ofstream::out);

	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	scene->Render(1, 0, fb, rgbImage, nrmImage);
	
	rgbImage.close();
	nrmImage.close();

	// dispose the framebuffer
	if (fb)
	{
		delete fb;
		fb = nullptr;
	}
	
	// dispose the scene (camera, items and materials)
	if (scene)
	{
		delete(scene);
		scene = nullptr;
	}
}
