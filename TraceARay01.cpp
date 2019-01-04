//
//  TraceARay01.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#include "TraceARay01.hpp"

// global var to enable console debug
bool g_debugConsole = false;

// Linear interpolation template function
template <class T>
T Lerp(T start, T end, float blend)
{
	return start * (1.0 - blend) + end * blend;
}

float hit_sphere(const Vec3& center, float radius, const Ray& r)
{
	const Vec3 oc = r.GetOrigin() - center;
	const float a = Dot(r.GetDirection(), r.GetDirection());
	const float b = 2.0 * Dot(oc, r.GetDirection());
	const float c = Dot(oc, oc) - radius*radius;
	const float discriminant = b*b - 4*a*c;
	if (discriminant > 0)
		return (-b - sqrt(discriminant)) / (2.0 * a);
	else
		return -1.0;
}

float hit_triangle(const Vec3& ptA, const Vec3& ptB, const Vec3& ptC, const Ray& r)
{
	// compute the segments given the three vertexes
	const Vec3 vecAB = ptA - ptB;
	const Vec3 vecBC = ptB - ptC;
	const Vec3 vecCA = ptC - ptA;
	
	// compute the normal
	const Vec3 nrmABC = Normalize(Cross(vecAB, vecCA));
	
	// compute the Dot product (cosine of the angle) between the normal and the ray direction
	const float dotDirNrm = Dot(Normalize(r.GetDirection()), nrmABC);
	
	// check triangle not being perpendicular to ray
	if (dotDirNrm != 0)
	{
		const float k = Dot(ptA - r.GetOrigin(), nrmABC) / dotDirNrm;
		
		// evalute the intersection point
		const Vec3 ptP = r.GetOrigin() + Normalize(r.GetDirection()) * k;
		
		// vectors to intersection points
		const Vec3 vecAP = ptA - ptP;
		const Vec3 vecBP = ptB - ptP;
		const Vec3 vecCP = ptC - ptP;
		
		// normals between triangle edges and vectors to int. points
		const Vec3 crsAB_AP = Cross(vecAB, vecAP);
		const Vec3 crsBC_BP = Cross(vecBC, vecBP);
		const Vec3 crsCA_CP = Cross(vecCA, vecCP);
		
		// Dot products for checking intersection point position
		const float dot1 = Dot(crsAB_AP, crsBC_BP);
		const float dot2 = Dot(crsBC_BP, crsCA_CP);
		const float dot3 = Dot(crsCA_CP, crsAB_AP);

		if (dot1 >= 0 && dot2 >= 0 && dot3 >= 0)
			return k;
	}
	return -1.0;
}

Vec3 color_const(const Ray& r)
{
	// compute the color intersecting a sphere
	const Vec3 sphereCen(0,0,-1);
	const float sphereRad = 0.5;
	if (hit_sphere(sphereCen, sphereRad, r) > 0)
		return Vec3(1,0,0);
	
	// compute the color intersecting a triangle
	const Vec3 triA = Vec3(-0.5,0.5,-1);
	const Vec3 triB = Vec3(0.5,0.5,-1);
	const Vec3 triC = Vec3(0.5,-0.5,-1);
	if (hit_triangle(triA, triB, triC, r) > 0)
		return Vec3(0,1,0);
	
	// compute the background color
	const Vec3 ray_direction = Normalize(r.GetDirection());
	const float blend = 0.5 * (ray_direction.y() + 1.0);
	return Lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), blend);
}

Vec3 color_normals(const Ray& r)
{
	float t;
	
	if (true)
	// hit a sphere
	{
		const Vec3 sphereCen(0,0,-1);
		const float sphereRad = 0.5;
		t = hit_sphere(sphereCen, sphereRad, r);
		if (t > 0.0)
		{
			// normalize the vector representing the normal at hit point
			const Vec3 normalAtHitPoint = Normalize(r.PointAtParameter(t) - sphereCen);
			// convert the normal component [-1,1] to color component [0,1]
			const Vec3 colorFromNormal = Vec3(
																				normalAtHitPoint.x()+1,
																				normalAtHitPoint.y()+1,
																				normalAtHitPoint.z() + 1) * 0.5;
			return colorFromNormal;
		}
	}
	
	if (true)
	{
		// hit a triangle
		const Vec3 triA = Vec3(-0.5,0.5,-1);
		const Vec3 triB = Vec3(0.5,0.5,-1);
		const Vec3 triC = Vec3(0.5,-0.5,-1);
		t = hit_triangle(triA, triB, triC, r);
		if (t > 0.0)
		{
			// normalize the vector representing the normal at hit point
			const Vec3 normalAtHitPoint = Normalize(Cross(triA - triB, triC - triA));
			// convert the normal component [-1,1] to color component [0,1]
			const Vec3 colorFromNormal = Vec3(
																				normalAtHitPoint.x()+1,
																				normalAtHitPoint.y()+1,
																				normalAtHitPoint.z() + 1) * 0.5;
			return colorFromNormal;
		}
	}
	
	// compute the background color
	const Vec3 ray_direction = Normalize(r.GetDirection());
	const float blend = 0.5 * (ray_direction.y() + 1.0);
	return Lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), blend);
}

int main()
{
	// set the film size
	const Vec3 filmSize (4.0, 4.0, 0.0);
	const Vec3 lowerLeftCorner( -filmSize.x() / 2, -filmSize.y() / 2, -1.0);
	const Vec3 horizontal (filmSize.x(), 0.0, 0.0);
	const Vec3 vertical (0.0, filmSize.y(), 0.0);
	// set the film ratio
	const float ratio = float(filmSize.x())/float(filmSize.y());
	
	// set the eye position
	const Vec3 eyePos (0.0, 0.0, 0.0);
	
	// set image resolution
	const int nx = 200;
	const int ny = int(nx / ratio);
	
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
			// evalute u/v params and create the eye direction
			const float u = float (i) / float (nx);
			const float v = float (j) / float (ny);
			//std::cout << "u: " << u << " / v: " << v << " - ";
			const Vec3 eyeDir (lowerLeftCorner + horizontal * u + vertical * v);
			
			// allocate a ray given a certain origin and direction
			Ray r(eyePos, eyeDir);
			
			// evaluate the color given a certain ray
			const Vec3 col = color_normals(r);
			
			// map the value returned by the ray to a meaningful color
			const int ir = int(255.99 * col.r());
			const int ig = int(255.99 * col.g());
			const int ib = int(255.99 * col.b());
			
			if (g_debugConsole)
			{
				std::cout << "uv [" << u << ", " << v << "] / dir [" << eyeDir.x() << ", " << eyeDir.y() << ", " << eyeDir.z() << "] / col ["<< ir <<", " << ", "<< ig << ", " << ib << "]\n";
			}
			
			// spool the color information to file
			image << ir << " " << ig << " " << ib << "\n";
		}
	}
	image.close();
}
