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
#include "box.hpp"
#include "trimesh.hpp"
#include "rectangle.hpp"
#include "materials.hpp"
#include "hitable.hpp"
#include "hitableinstance.hpp"

// global var to enable console debug
const int g_xRes = 512;
const int g_yRes = 512;

//#define MATRIX_TESTS
//#define NEW_HITABLE_TEST
//#define SPHERE_TEST
//#define BOX_TEST
//#define TRI_TEST
//#define ALL_TEST
//#define RECTANGLE_TEST
//#define EMISSION_TEST
#define CORNELL_BOX
//#define STANDARD_RUN
#define EXECUTE_RENDER

int NewHitableTest()
{
	// init the scene
	Scene* scene = new Scene();
	
	// set the environment
	Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
	scene->AddEnvironment(env);
	
	// allocate metals
	MetalReflector*  red = new MetalReflector("red", Vec3(0.9, 0, 0));
	MetalReflector*  green = new MetalReflector("green", Vec3(0, 0.9, 0));
	MetalReflector*  cyan = new MetalReflector("cyan", Vec3(0.9, 0.9, 0.9));
	scene->AddMaterial(red);
	scene->AddMaterial(green);
	scene->AddMaterial(cyan);
	
	// allocate transformation
	Matrix trf;
	
	Triangle* triRed = new Triangle("triRed", Vec3(-0.5, 0.5, 0.7), Vec3(0.5, -0.5, 0.7), Vec3(0.5, 0.5, 0.7), red);
	trf.AddOffset(.1, .1, 0);
	triRed->AddMatrix(trf);
	triRed->InitTransformation();
	scene->AddItem(triRed);
	
	Triangle* triGreen = new Triangle("triGreen", Vec3(-0.5, 0.5, 0), Vec3(0.5, -0.5, 0), Vec3(0.5, 0.5, 0), green);
	scene->AddItem(triGreen);
	
	HitableInstance* instanceTriRed = new HitableInstance(triRed);
	trf.Reset();
	trf.AddOffset(0,0,-.25);
	trf.AddUniformScale(.5); //.79 / .8 / .81
	instanceTriRed->AddMatrix(trf);
	instanceTriRed->InitTransformation();
	instanceTriRed->SetName("instanceCyan");
	instanceTriRed->SetMaterial(cyan);
	scene->AddItem(instanceTriRed);
	
	const Vec3 from (0,0,2);
	const Vec3 to (0,0,0);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0; //0.05;
	const float focusDistance = 5; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	scene->RenderPixel(40 * g_xRes/64.0, 27 * g_yRes/64.0, 0, true); //hit top-right
	scene->RenderPixel(50 * g_xRes/64.0, 27 * g_yRes/64.0, 0, true); //hit top-right
	scene->RenderPixel(60 * g_xRes/64.0, 27 * g_yRes/64.0, 0, true); //hit top-right
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_NEW_HITABLE_TEST.ppm", std::ofstream::out);
	
	std::ofstream nrmImage;
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_NEW_HITABLE_TEST.ppm", std::ofstream::out);
	
	std::ofstream objIDImage;
	objIDImage.open("/Users/riccardogigante/Desktop/test_objID_NEW_HITABLE_TEST.ppm", std::ofstream::out);
	
	scene->Render(1, 0, fb, &rgbImage, &nrmImage, &objIDImage);
	
	rgbImage.close();
	nrmImage.close();
	objIDImage.close();
	
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

int TriTest()
{
	// init the scene
	Scene* scene = new Scene();
	
	// set the environment
	Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
	scene->AddEnvironment(env);
	
	// allocate metals
	MetalReflector*  red = new MetalReflector("red", Vec3(0.9, 0, 0));
	MetalReflector*  green = new MetalReflector("green", Vec3(0, 0.9, 0));
	scene->AddMaterial(red);
	scene->AddMaterial(green);
	
	Triangle* tri = new Triangle("triRed", Vec3(-0.5, 0.5, 0.5), Vec3(0.5, -0.5, 0.5), Vec3(0.5, 0.5, 0.5), red);
	//		scene->AddItem(tri);
	Triangle* tri2 = new Triangle("triGreen", Vec3(-0.5, 0.5, 0), Vec3(0.5, -0.5, 0), Vec3(0.5, 0.5, 0), green);
	scene->AddItem(tri2);
	
	HitableInstance* instance2 = new HitableInstance(tri);
	Matrix trf;
	trf.Reset();
	trf.AddOffset(0,0,.5);
	trf.AddUniformScale(.5); //.79 / .8 / .81
	instance2->AddMatrix(trf);
	instance2->InitTransformation();
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
	
	scene->RenderPixel(52 * g_xRes/64.0, 52 * g_yRes/64.0, 0, true);
	scene->RenderPixel(46 * g_xRes/64.0, 46 * g_yRes/64.0, 0, true);
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage, nrmImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_TRI_TEST.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_TRI_TEST.ppm", std::ofstream::out);
	
	scene->Render(16, 0, fb, &rgbImage, &nrmImage);
	
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

int BoxTest()
{
	// init the scene
	Scene* scene = new Scene();
	
	// set the environment
	Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
	scene->AddEnvironment(env);
	
	// allocate lambertians
	LambertianReflector*  whiteDiffuse = new LambertianReflector("white diffuse", Vec3(0.9, 0.9, 0.9));
	scene->AddMaterial(whiteDiffuse);
	LambertianReflector*  redDiffuse = new LambertianReflector("red diffuse", Vec3(0.9, 0.1, 0.1));
	scene->AddMaterial(redDiffuse);
	LambertianReflector*  greenDiffuse = new LambertianReflector("green diffuse", Vec3(0.1, 0.9, 0.1));
	scene->AddMaterial(greenDiffuse);
	LambertianReflector*  blueDiffuse = new LambertianReflector("blue diffuse", Vec3(0.1, 0.1, 0.9));
	scene->AddMaterial(blueDiffuse);
	
	// allocate metals
	MetalReflector*  redMetal = new MetalReflector("red metal", Vec3(0.9, 0.1, 0.1));
	MetalReflector*  greenMetal = new MetalReflector("green metal", Vec3(0.1, 0.9, 0.1));
	MetalReflector*  blueMetal = new MetalReflector("blue metal", Vec3(0.1, 0.1, 0.9));
	scene->AddMaterial(redMetal);
	scene->AddMaterial(greenMetal);
	scene->AddMaterial(blueMetal);
	
	Triangle* trifloor1 = new Triangle("triFloor1", Vec3(-20, 0, -20), Vec3(20, 0, 50), Vec3(20, 0, -20), whiteDiffuse);
	scene->AddItem(trifloor1);
	Triangle* trifloor2 = new Triangle("triFloor2", Vec3(20, 0, 50), Vec3(-20, 0, -20), Vec3(-20, 0, 50), whiteDiffuse);
	scene->AddItem(trifloor2);
	
	Matrix trf;
	
//	Box* boxRed = new Box("box Red", Vec3(0.2, 1, .5), Vec3(1.2,3,0), redDiffuse);
//	scene->AddItem(boxRed);
//	trf.AddRotationY(-45);
//	trf.AddOffset(0.5, 0, -0.5);
//	boxRed->AddMatrix(trf);
//	trf.Reset();
//	boxRed->InitTransformation();
	
	Box * boxGreenBig = new Box("box Red", Vec3(0.0, 0.1, 0.0), Vec3(10.0), redDiffuse);
	scene->AddItem(boxGreenBig);
	
	Box * boxGreenSmall = new Box("box Green", Vec3(0.0, 0.1, 0.0), Vec3(-2.0,2.0,2.0), greenDiffuse);
	scene->AddItem(boxGreenSmall);
	
	Rectangle * rectangleBlue = new Rectangle("Blue Rectangle", Vec3(-2.0,0.1,0.0), Vec3(0.0,5.0,0.0), Vec3(-5.0,0.0,0.0), blueDiffuse);
	scene->AddItem(rectangleBlue);
	

#if 0
	HitableInstance* instanceGreenBox = new HitableInstance(boxGreen);
	trf.AddRotationY(30);
	trf.AddOffset(0, 1, 0);
	instanceGreenBox->AddMatrix(trf);
	trf.Reset();
	instanceGreenBox->InitTransformation();
	instanceGreenBox->SetName("instanceGreen");
	scene->AddItem(instanceGreenBox);
	
	HitableInstance* instanceGreenBoxBeingBlue = new HitableInstance(boxGreen);
	trf.AddRotationY(-30);
	trf.AddOffset(0, 2, 0);
	instanceGreenBoxBeingBlue->SetMaterial(blueDiffuse);
	instanceGreenBoxBeingBlue->AddMatrix(trf);
	trf.Reset();
	instanceGreenBoxBeingBlue->InitTransformation();
	instanceGreenBoxBeingBlue->SetName("instanceBlue");
	scene->AddItem(instanceGreenBoxBeingBlue);
#endif
	
	const Vec3 from (0,20,-10000);
	const Vec3 to (0,0,0);
	const Vec3 up (0,1,0);
	const float fov = .1;
	const float aperture = 0; //0.05;
	const float focusDistance = 5; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	scene->RenderPixel(31 * g_xRes/64.0, 31 * g_yRes/64.0, 0, true);
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage, nrmImage, objIDImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_BOX_TEST.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_BOX_TEST.ppm", std::ofstream::out);
	objIDImage.open("/Users/riccardogigante/Desktop/test_objID_BOX_TEST.ppm", std::ofstream::out);
	
	scene->Render(16, 0, fb, &rgbImage, &nrmImage, &objIDImage);
	
	rgbImage.close();
	nrmImage.close();
	objIDImage.close();
	
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

int EmissionTest()
{
	// init the scene
	Scene* scene = new Scene();
	
	// allocate lambertians
	LambertianReflector*  white = new LambertianReflector("white", Vec3(0.9, 0.9, 0.9));
	scene->AddMaterial(white);
	
	// allocate metals
	MetalReflector*  red = new MetalReflector("red", Vec3(0.9, 0, 0));
	scene->AddMaterial(red);
	
	// allocate emitter
	DiffuseEmitter*  light = new DiffuseEmitter("light", Vec3(.3, .4, 1));
	scene->AddMaterial(light);
	
	
	// allocate emitter
	DiffuseEmitter*  light2 = new DiffuseEmitter("light", Vec3(2));
	scene->AddMaterial(light2);
	
	Triangle* trifloor1 = new Triangle("triFloor1", Vec3(-2, 0, -2), Vec3(2, 0, 5), Vec3(2, 0, -2), white);
	scene->AddItem(trifloor1);
	Triangle* trifloor2 = new Triangle("triFloor2", Vec3(2, 0, 5), Vec3(-2, 0, -2), Vec3(-2, 0, 5), white);
	scene->AddItem(trifloor2);
	
	Sphere* redSphere = new Sphere("Red Sphere", Vec3(-1, .5, 0), 0.5, red);
		scene->AddItem(redSphere);
	
	Sphere* emittingSphere = new Sphere("Emitting Sphere", Vec3(1, .5, 0), 0.5, light);
	scene->AddItem(emittingSphere);
	
	Rectangle* emittingRectangle = new Rectangle("Emitting rectangle", Vec3(-1,2,-1), Vec3(2,0,0), Vec3(0,0,2), light2);
	scene->AddItem(emittingRectangle);

	
	const Vec3 from (0,1,5);
	const Vec3 to (0,1,0);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0; //0.05;
	const float focusDistance = 5; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	scene->RenderPixel(32/64.0 * g_xRes, (64-32+8)/64.0 * g_yRes, 0, true); // inside emitter
	scene->RenderPixel(32/64.0 * g_xRes, (64-32-8)/64.0 * g_yRes, 0, true); // outside emitter
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage, nrmImage, objIDImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_EMISSION_TEST.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_EMISSION_TEST.ppm", std::ofstream::out);
	objIDImage.open("/Users/riccardogigante/Desktop/test_objID_EMISSION_TEST.ppm", std::ofstream::out);
	
	
	scene->Render(32, 0, fb, &rgbImage, &nrmImage, &objIDImage);
	
	rgbImage.close();
	nrmImage.close();
	objIDImage.close();
	
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

int CornellBox()
{
	// init the scene
	Scene* scene = new Scene();
	
	// set the environment
//	Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
//	scene->AddEnvironment(env);
	
	// allocate lambertians
	LambertianReflector*  whiteDiffuse = new LambertianReflector("White Diffuse", Vec3(0.9, 0.9, 0.9));
	scene->AddMaterial(whiteDiffuse);
	LambertianReflector*  redDiffuse = new LambertianReflector("Red Diffuse", Vec3(0.9, 0.1, 0.1));
	scene->AddMaterial(redDiffuse);
	LambertianReflector*  greenDiffuse = new LambertianReflector("Green Diffuse", Vec3(0.1, 0.9, 0.1));
	scene->AddMaterial(greenDiffuse);
	
	// allocate metals
	MetalReflector*  metal = new MetalReflector("Metal", Vec3(0.9, 0.0, 0.9));
	scene->AddMaterial(metal);
	
	// allocate emitter
	DiffuseEmitter*  emitter = new DiffuseEmitter("light", Vec3(10));
	scene->AddMaterial(emitter);
	
	// define scene
	Rectangle * light = new Rectangle("light", Vec3(213,548,227), Vec3(130,0,0), Vec3(0,0,105), emitter);
	scene->AddItem(light);
	Rectangle * floor = new Rectangle("floor", Vec3(0,0,0), Vec3(0,0,560), Vec3(550,0,0),  whiteDiffuse);
	scene->AddItem(floor);
	Rectangle * ceiling = new Rectangle("ceiling", Vec3(0,549,0), Vec3(550,0,0), Vec3(0,0,560), whiteDiffuse);
	scene->AddItem(ceiling);
	Rectangle * backWall = new Rectangle("back", Vec3(0,0,560), Vec3(0,550,0), Vec3(550,0,0), whiteDiffuse);
	scene->AddItem(backWall);
	Rectangle * rightWall = new Rectangle("right", Vec3(0,0,0), Vec3(0,550,0), Vec3(0,0,560), greenDiffuse);
	scene->AddItem(rightWall);
	Rectangle * leftWall = new Rectangle("left", Vec3(550,0,0), Vec3(0,0,560), Vec3(0,550,0), redDiffuse);
	scene->AddItem(leftWall);
	
	Box * shortBox = new Box ("short", Vec3(0.0), Vec3(165), whiteDiffuse);
	Matrix trf;
	trf.AddRotationY(-17);
	trf.AddOffset(130, 0, 65);
	shortBox->AddMatrix(trf);
	trf.Reset();
	shortBox->InitTransformation();
	scene->AddItem(shortBox);
	
	Box * tallBox = new Box ("tall", Vec3(0), Vec3(165,330,165), whiteDiffuse);
	trf.AddRotationY(17);
	trf.AddOffset(265, 0, 296);
	tallBox->AddMatrix(trf);
	trf.Reset();
	tallBox->InitTransformation();
	scene->AddItem(tallBox);
	
	const Vec3 from (278, 273, -800);
	const Vec3 to (278, 273, 0);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0; //0.05;
	const float focusDistance = 800; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	scene->RenderPixel(114, (g_yRes-110), 0, true); 
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage, nrmImage, objIDImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_CORNELL_BOX.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_CORNELL_BOX.ppm", std::ofstream::out);
	objIDImage.open("/Users/riccardogigante/Desktop/test_objID_CORNELL_BOX.ppm", std::ofstream::out);
	
	
	scene->Render(512, 0, fb, &rgbImage, &nrmImage, &objIDImage);
	
	rgbImage.close();
	nrmImage.close();
	objIDImage.close();
	
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

int RectangleTest()
{
	// init the scene
	Scene* scene = new Scene();
	
	// set the environment
	Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
	scene->AddEnvironment(env);
	
	// allocate lambertians
	LambertianReflector*  white = new LambertianReflector("white", Vec3(0.9, 0.9, 0.9));
	scene->AddMaterial(white);
	
	// allocate emitter
	DiffuseEmitter*  light = new DiffuseEmitter("light", Vec3(.5, .5, .5));
	scene->AddMaterial(light);
//
//	Triangle* trifloor1 = new Triangle("triFloor1", Vec3(-2, 0, -2), Vec3(2, 0, 5), Vec3(2, 0, -2), white);
//	scene->AddItem(trifloor1);
//	Triangle* trifloor2 = new Triangle("triFloor2", Vec3(2, 0, 5), Vec3(-2, 0, -2), Vec3(-2, 0, 5), white);
//	scene->AddItem(trifloor2);
	
	// allocate metals
	MetalReflector*  metal = new MetalReflector("Metal", Vec3(0.9, 0.0, 0.9));
	scene->AddMaterial(metal);
	
	Rectangle* redRect1 = new Rectangle("Front Rectangle", Vec3(-1,-1.5,0), Vec3(2,0,0), Vec3(0,1,0) , light);
		scene->AddItem(redRect1);
	
	Rectangle* redRect2 = new Rectangle("Back Rectangle", Vec3(-1,1.5,0), Vec3(2,0,0), Vec3(0,-1,0) , light);
	scene->AddItem(redRect2);
	
	const Vec3 from (0,0,10);
	const Vec3 to (0,0,0);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0; //0.05;
	const float focusDistance = 5; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	scene->RenderPixel(32/64.0 * g_xRes, (24)/64.0 * g_yRes, 0, true); // front rectangle
	scene->RenderPixel(32/64.0 * g_xRes, (40)/64.0 * g_yRes, 0, true); // back rectangle
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage, nrmImage, objIDImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_RECTANGLE_TEST.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_RECTANGLE_TEST.ppm", std::ofstream::out);
	objIDImage.open("/Users/riccardogigante/Desktop/test_objID_RECTANGLE_TEST.ppm", std::ofstream::out);
	
	
	scene->Render(8, 0, fb, &rgbImage, &nrmImage, &objIDImage);
	
	rgbImage.close();
	nrmImage.close();
	objIDImage.close();
	
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

int SphereTest()
{
	// init the scene
	Scene* scene = new Scene();
	
	// set the environment
	Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
	scene->AddEnvironment(env);
	
	// allocate metals
	MetalReflector*  red = new MetalReflector("red", Vec3(0.9, 0, 0));
	MetalReflector*  green = new MetalReflector("green", Vec3(0, 0.9, 0));
	scene->AddMaterial(red);
	scene->AddMaterial(green);
	
	Sphere* sphereRed = new Sphere("sphere Red", Vec3(-0.5, 0, 0), 0.4, red);
	scene->AddItem(sphereRed);
	
	HitableInstance* instance2 = new HitableInstance(sphereRed);
	Matrix trf;
	trf.Reset();
	trf.AddOffset(1,0,0);
	trf.AddNonUniformScale(1,2,1);
	instance2->AddMatrix(trf);
	instance2->InitTransformation();
	instance2->SetName("instanceRed");
	scene->AddItem(instance2);
	
	const Vec3 from (0,0,4);
	const Vec3 to (0,0,0);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0; //0.05;
	const float focusDistance = 5; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	scene->RenderPixel(46/64.0 * g_xRes, (64 - 46)/64.0 * g_yRes, 0, true);
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage, nrmImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_SPHERE_TEST.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_SPHERE_TEST.ppm", std::ofstream::out);
	
	scene->Render(1, 0, fb, &rgbImage, &nrmImage);
	
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

int AllTest()
{
	// init the scene
	Scene* scene = new Scene();
	
	// set the environment
	Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
	scene->AddEnvironment(env);
	
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
	
	Triangle* trifloor1 = new Triangle("triFloor1", Vec3(-2, -0.5, -2), Vec3(2, -0.5, 5), Vec3(2, -0.5, -2), white);
	scene->AddItem(trifloor1);
	Triangle* trifloor2 = new Triangle("triFloor2", Vec3(2, -0.5, 5), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, 5), white);
	scene->AddItem(trifloor2);
	
	Triangle* tri = new Triangle("triRed", Vec3(-0.5, 0.5, -0.5), Vec3(0.5, -0.5, -0.5), Vec3(0.5, 0.5, -0.5), red);
	//		scene->AddItem(tri);
	Triangle* tri2 = new Triangle("triGreen", Vec3(-0.5, 0.5, 0), Vec3(0.5, -0.5, 0), Vec3(0.5, 0.5, 0), green);
	scene->AddItem(tri2);
	
	HitableInstance* instance1 = new HitableInstance(tri);
	Matrix trf;
	trf.AddOffset(0.5, 0, -1);
	instance1->AddMatrix(trf);
	instance1->InitTransformation();
	instance1->SetName("instanceRed");
	scene->AddItem(instance1);
	
	Sphere* sphere = new Sphere("Sphere", Vec3(-1,0,0), 0.5, blue);
	scene->AddItem(sphere);
	
	HitableInstance* instance2 = new HitableInstance(sphere);
	trf.Reset();
	trf.AddOffset(1.5, -0.25, 1);
	instance2->AddMatrix(trf);
	trf.Reset();
	trf.AddUniformScale(0.5);
	instance2->AddMatrix(trf);
	trf.Reset();
	trf.AddNonUniformScale(1,1,2);
	instance2->AddMatrix(trf);
	instance2->InitTransformation();
	instance2->SetName("instanceBlu");
	scene->AddItem(instance2);
	
	const Vec3 from (5,5,5);
	const Vec3 to (0,0,0);
	const Vec3 up (0,1,0);
	const float fov = 40;
	const float aperture = 0; //0.05;
	const float focusDistance = 5; //(from - to).Length();
	
	// add camera to the scene
	scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
	
	scene->RenderPixel(21 * g_xRes/64, (64-32) * g_yRes/64, 0, true);
	
#ifdef EXECUTE_RENDER
	Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
	if (!fb)
		return -1;
	
	std::ofstream rgbImage, nrmImage, objIDImage;
	rgbImage.open("/Users/riccardogigante/Desktop/test_color_ALL_TEST.ppm", std::ofstream::out);
	nrmImage.open("/Users/riccardogigante/Desktop/test_normal_ALL_TEST.ppm", std::ofstream::out);
	objIDImage.open("/Users/riccardogigante/Desktop/test_objID_ALL_TEST.ppm", std::ofstream::out);
	
	scene->Render(1, 0, fb, &rgbImage, &nrmImage, &objIDImage);
	
	rgbImage.close();
	nrmImage.close();
	objIDImage.close();
	
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

int main()
{
#ifdef MATRIX_TESTS
	MatrixTests();
#endif
	
#ifdef NEW_HITABLE_TEST
	NewHitableTest();
#endif
	
#ifdef SPHERE_TEST
	SphereTest();
#endif
	
#ifdef BOX_TEST
	BoxTest();
#endif
	
#ifdef TRI_TEST
	TriTest();
#endif
	
#ifdef EMISSION_TEST
	EmissionTest();
#endif
	
#ifdef RECTANGLE_TEST
	RectangleTest();
#endif
	
#ifdef ALL_TEST
	AllTest();
#endif
		
#ifdef CORNELL_BOX
	CornellBox();
#endif
	
#ifdef STANDARD_RUN
	{
		// init the scene
		Scene* scene = new Scene();
//
//		// set the environment
//		Gradient* env = new Gradient("standard gradient", Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0));
//		scene->AddEnvironment(env);
		
		//allocate a glass
		Dielectric* glass = new Dielectric("glass", 1.33);
		scene->AddMaterial(glass);
		//allocate a red glass
		Dielectric* redGlass = new Dielectric("red glass", 1.33, Vec3(.9, .2, .2));
		scene->AddMaterial(redGlass);
		//allocate a yellow glass
		Dielectric* yellowGlass = new Dielectric("yellow glass", 1.33, Vec3(.9, .9, .2));
		scene->AddMaterial(yellowGlass);

		// allocate lambertians
		LambertianReflector*  white = new LambertianReflector("white", Vec3(0.95, 0.95, 0.95));
		scene->AddMaterial(white);
//		LambertianReflector*  whiteEmitter = new LambertianReflector("white lambertian emitter", Vec3(0,0,0), Vec3(1,1,1));
		DiffuseEmitter*  whiteEmitter = new DiffuseEmitter("white diffuse emitter", Vec3(6,6,6));
		scene->AddMaterial(whiteEmitter);
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
		
		// the light bubble
		scene->AddItem(new Rectangle("lightRect", Vec3(-.5, 2, -.5), Vec3(1,0,0), Vec3(0,0,1), whiteEmitter));
		
		// the small green sphere on the back
		scene->AddItem(new Sphere("greenSphere", Vec3(-0.35, -0.4, -1), 0.1, green));
		// the small red sphere on the back
		scene->AddItem(new Sphere("redSphere", Vec3(0.35, -0.4, -1), 0.1, red));
		// the green triangle on the floor
		scene->AddItem(new Triangle("greenTriangle", Vec3(-2, -0.5, -2), Vec3(2, -0.5, 5), Vec3(2, -0.5, -2), green));
		// the blue triangle on the floor
		scene->AddItem(new Triangle("blueTriangle", Vec3(2, -0.5, 5), Vec3(-2, -0.5, -2), Vec3(-2, -0.5, 5), blue));
		// the purple triangle on the left
		scene->AddItem(new Triangle("purpleMTriangle", Vec3(-0.5, 0.5, -0.5), Vec3(-0.5, -0.5, -1.5), Vec3(-0.5, 0.5, -1.5), purpleM));
		// the cyan triangle on the back
		scene->AddItem(new Triangle("cyanMTriangle", Vec3(-0.5, 0.5, -1.5), Vec3(0.5, -0.5, -1.5), Vec3(0.5, 0.5, -1.5), cyanM));
		// the yellow triangle on the right
		scene->AddItem(new Triangle("yellowMTriangle", Vec3(0.5, 0.5, -0.5), Vec3(0.5, 0.5, -1.5), Vec3(0.5, -0.5, -0.5), yellowM));


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
				
				if (mesh->InitTris() && mesh->InitTransformation())
				{
					scene->AddItem(mesh);
					// dispose the memory used to create the mesh
					delete[] points; points = nullptr;
					delete[] indexes; indexes = nullptr;
				}
			}
		}
		
		HitableInstance* inst = new HitableInstance(mesh);
		Matrix trf;
		trf.AddOffset(1.05,0,0);
		trf.AddNonUniformScale(1, .5, 1);
		inst->AddMatrix(trf);
		trf.Reset();
		inst->InitTransformation();
		scene->AddItem(inst);
		
		Triangle* instanceTri = new Triangle("cyanMTriangle", Vec3(-0.5, 0.5, -1.5), Vec3(0.5, -0.5, -1.5), Vec3(0.5, 0.5, -1.5), white);
		scene->AddItem(instanceTri);
		instanceTri->SetVisible(false);
		
		HitableInstance* inst2 = new HitableInstance(instanceTri);
		inst2->SetMaterial(cyanM);
		trf.AddOffset(-1,1,0);
		inst2->AddMatrix(trf);
		trf.Reset();
		inst2->InitTransformation();
		scene->AddItem(inst2);
		
		Sphere* instanceSphere = new Sphere("instanced sphere", Vec3(0, 0, 0), 0.2, white);
		instanceSphere->SetVisible(false);
		
		HitableInstance* inst3 = new HitableInstance(instanceSphere);
		inst3->SetMaterial(redGlass);
		scene->AddItem(inst3);
		trf.AddOffset(-.5, .5, 0);
		trf.AddNonUniformScale(1, 1, .33);
		inst3->AddMatrix(trf);
		trf.Reset();
		inst3->InitTransformation();
		
		HitableInstance* inst4 = new HitableInstance(instanceSphere);
		inst4->SetMaterial(yellowGlass);
		scene->AddItem(inst4);
		trf.AddOffset(.5, .5, 0);
		trf.AddNonUniformScale(1, 1, 2);
		inst4->AddMatrix(trf);
		trf.Reset();
		inst4->InitTransformation();

		// the rainbow spheres
		scene->AddItem(new Sphere("redSphere", Vec3(-0.3, -0.45, 4), 0.05, red));
		scene->AddItem(new Sphere("orangeSphere", Vec3(-0.3, -0.45, 3.33), 0.05, orange));
		scene->AddItem(new Sphere("yellowSphere", Vec3(-0.3, -0.45, 2.66), 0.05, yellow));
		scene->AddItem(new Sphere("greenSphere", Vec3(-0.3, -0.45, 2), 0.05, green));
		scene->AddItem(new Sphere("blueSphere", Vec3(-0.3, -0.45, 1.33), 0.05, blue));
		scene->AddItem(new Sphere("indigoSphere", Vec3(-0.3, -0.45, 0.66), 0.05, indigo));
		scene->AddItem(new Sphere("purpleSphere", Vec3(-0.3, -0.45, 0), 0.05, purple));
		
		Box* box = new Box("box", Vec3(-.05,-0.5,-.05), Vec3(.05,-0.4,.05), red);
		trf.AddOffset(0.3, 0, 0);
		box->AddMatrix(trf);
		trf.Reset();
		box->InitTransformation();
		scene->AddItem(box);
		HitableInstance* boxInst1 = new HitableInstance(box);
		boxInst1->SetMaterial(orange);
		trf.AddOffset(0.3, 0, 0.66);
		boxInst1->AddMatrix(trf);
		trf.Reset();
		boxInst1->InitTransformation();
		scene->AddItem(boxInst1);
		HitableInstance* boxInst2 = new HitableInstance(box);
		boxInst2->SetMaterial(orange);
		trf.AddOffset(0.3, 0, 0.66);
		boxInst2->AddMatrix(trf);
		trf.Reset();
		boxInst2->InitTransformation();
		scene->AddItem(boxInst2);
		HitableInstance* boxInst3 = new HitableInstance(box);
		boxInst3->SetMaterial(yellow);
		trf.AddOffset(0.3, 0, 1.33);
		boxInst3->AddMatrix(trf);
		trf.Reset();
		boxInst3->InitTransformation();
		scene->AddItem(boxInst3);
		HitableInstance* boxInst4 = new HitableInstance(box);
		boxInst4->SetMaterial(green);
		trf.AddOffset(0.3, 0, 2);
		boxInst4->AddMatrix(trf);
		trf.Reset();
		boxInst4->InitTransformation();
		scene->AddItem(boxInst4);
		HitableInstance* boxInst5 = new HitableInstance(box);
		boxInst5->SetMaterial(blue);
		trf.AddOffset(0.3, 0, 2.66);
		boxInst5->AddMatrix(trf);
		trf.Reset();
		boxInst5->InitTransformation();
		scene->AddItem(boxInst5);
		HitableInstance* boxInst6 = new HitableInstance(box);
		boxInst6->SetMaterial(indigo);
		trf.AddOffset(0.3, 0, 3.33);
		boxInst6->AddMatrix(trf);
		trf.Reset();
		boxInst6->InitTransformation();
		scene->AddItem(boxInst6);
		HitableInstance* boxInst7 = new HitableInstance(box);
		boxInst7->SetMaterial(indigo);
		trf.AddOffset(0.3, 0, 4);
		boxInst7->AddMatrix(trf);
		trf.Reset();
		boxInst7->InitTransformation();
		scene->AddItem(boxInst7);
		
		
		const Vec3 from (0,0,5);
		const Vec3 to (0,0.5,0);
		const Vec3 up (0,1,0);
		const float fov = 40;
		const float aperture = 0; //0.05;
		const float focusDistance = 5; //(from - to).Length();
		
		// add camera to the scene
		scene->AddCamera(new Camera(from, to, up, fov, aperture, focusDistance, g_xRes, g_yRes));
		
		std::ofstream rgbImage, nrmImage, objIDImage;
		rgbImage.open("/Users/riccardogigante/Desktop/test_color.ppm", std::ofstream::out);
		nrmImage.open("/Users/riccardogigante/Desktop/test_normal.ppm", std::ofstream::out);
		objIDImage.open("/Users/riccardogigante/Desktop/test_objID.ppm", std::ofstream::out);

		Framebuffer* fb = new Framebuffer(g_xRes, g_yRes, 3);
		if (!fb)
			return -1;
		
		scene->Render(1024, 0, fb, &rgbImage, &nrmImage, &objIDImage);
		
		rgbImage.close();
		nrmImage.close();
		objIDImage.close();

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
#endif
	return 0;
}
