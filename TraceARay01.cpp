//
//  TraceARay01.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#include "TraceARay01.hpp"
#include "vec3.hpp"
#include "ray.hpp"

bool hit_sphere_old(const vec3& center, float radius, const ray& r)
{
	const vec3 oc = r.origin() - center;
	const float a = dot(r.direction(), r.direction());
	const float b = 2.0 * dot(oc, r.direction());
	const float c = dot(oc, oc) - radius*radius;
	const float discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}

float hit_sphere(const vec3& center, float radius, const ray& r)
{
	const vec3 oc = r.origin() - center;
	const float a = dot(r.direction(), r.direction());
	const float b = 2.0 * dot(oc, r.direction());
	const float c = dot(oc, oc) - radius*radius;
	const float discriminant = b*b - 4*a*c;
	if (discriminant > 0)
		return (-b - sqrt(discriminant)) / (2.0 * a);
	else
		return -1.0;
}

bool hit_triangle_old(const vec3& ptA, const vec3& ptB, const vec3& ptC, const ray& r)
{
	const vec3 vecAB = ptA - ptB;
	const vec3 vecBC = ptB - ptC;
	const vec3 vecCA = ptC - ptA;
	
	const vec3 nrmABC = unit_vector(cross(vecAB, vecBC));
	const float dotDirNrm = dot(unit_vector(r.direction()), nrmABC);
	if (dotDirNrm != 0)
	{
		const float k = dot(ptA - r.origin(),nrmABC)/dotDirNrm;
		
		//intersection point
		const vec3 ptP = r.origin() + unit_vector(r.direction()) * k;

		// vectors to intersection points
		const vec3 vecAP = ptA - ptP;
		const vec3 vecBP = ptB - ptP;
		const vec3 vecCP = ptC - ptP;
		
		// normals between triangle edges and vectors to int. points
		const vec3 crsAB_AP = cross(vecAB, vecAP);
		const vec3 crsBC_BP = cross(vecBC, vecBP);
		const vec3 crsCA_CP = cross(vecCA, vecCP);
		
		// dot products for checking intersection point position
		const float dot1 = dot(crsAB_AP, crsBC_BP);
		const float dot2 = dot(crsBC_BP, crsCA_CP);
		const float dot3 = dot(crsCA_CP, crsAB_AP);
		
		if (dot1 >= 0 && dot2 >= 0 && dot3 >= 0)
			return true;
	}
	return false;
}

float hit_triangle(const vec3& ptA, const vec3& ptB, const vec3& ptC, const ray& r)
{
	const vec3 vecAB = ptA - ptB;
	const vec3 vecBC = ptB - ptC;
	const vec3 vecCA = ptC - ptA;
	
	const vec3 nrmABC = unit_vector(cross(vecAB, vecCA));
	const float dotDirNrm = dot(unit_vector(r.direction()), nrmABC);
	if (dotDirNrm != 0)
	{
		const float k = dot(ptA - r.origin(),nrmABC) / dotDirNrm;
		
		//intersection point
		const vec3 ptP = r.origin() + unit_vector(r.direction()) * k;
		
		// vectors to intersection points
		const vec3 vecAP = ptA - ptP;
		const vec3 vecBP = ptB - ptP;
		const vec3 vecCP = ptC - ptP;
		
		// normals between triangle edges and vectors to int. points
		const vec3 crsAB_AP = cross(vecAB, vecAP);
		const vec3 crsBC_BP = cross(vecBC, vecBP);
		const vec3 crsCA_CP = cross(vecCA, vecCP);
		
		// dot products for checking intersection point position
		const float dot1 = dot(crsAB_AP, crsBC_BP);
		const float dot2 = dot(crsBC_BP, crsCA_CP);
		const float dot3 = dot(crsCA_CP, crsAB_AP);
		
		if (dot1 >= 0 && dot2 >= 0 && dot3 >= 0)
			return k;
	}
	return -1.0;
}

vec3 color_old(const ray& r)
{
//	if (hit_sphere_old(vec3(0,0,-1), 0.5, r))
//		return vec3(1,0,0);
	
//	if (hit_triangle_old(vec3(-1.5,0.5,-1), vec3(-0.5,0.5,-1), vec3(-0.5,-0.5,-1), r))
//		return vec3(0,1,0);
	
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return vec3(1.0, 1.0, 1.0) * (1.0 -t ) + vec3(0.5, 0.7, 1.0) * t;
}

vec3 color(const ray& r)
{
	float t;
	const vec3 sphereCen(0,0,-1);
	const float sphereRad = 0.5;
	t = hit_sphere(sphereCen, sphereRad, r);
	if (t > 0.0)
	{
		const vec3 norm = unit_vector(r.point_at_parameter(t) - sphereCen);
		return vec3(norm.x()+1, norm.y()+1, norm.z()+1)*0.5;
	}
	
//	const vec3 triA = vec3(-0.5,0.5,-1);
//	const vec3 triB = vec3(0.5,0.5,-1);
//	const vec3 triC = vec3(0.5,-0.5,-1);
//	t = hit_triangle(triA, triB, triC, r);
//	if (t > 0.0)
//	{
//		const vec3 norm = cross(triA - triB, triC - triA);
//		return vec3(norm.x()+1, norm.y()+1, norm.z()+1)*0.5;
//	}
	
	//	if (hit_triangle(, vec3(-0.5,0.5,-1), , r))
	//		return vec3(0,1,0);
	
	const vec3 ray_direction = unit_vector(r.direction());
	const float blend = 0.5 * (ray_direction.y() + 1.0);
	return vec3(1.0, 1.0, 1.0) * (1.0 - blend) + vec3(0.5, 0.7, 1.0) * blend;
}

int main()
{
	const int nx = 200;
	const int ny = 100;
	std::ofstream image;
	image.open("/Users/riccardogigante/Desktop/test.ppm", std::ofstream::out);
	image << "P3\n" << nx << " " << ny << "\n255\n";
	
	const vec3 lower_left_corner(-2.0, -1.0, -1.0);
	const vec3 horizontal (4.0, 0.0, 0.0);
	const vec3 vertical (0.0, 2.0, 0.0);
	const vec3 origin (0.0, 0.0, 0.0);
	for (int j = ny - 1; j>= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			float u = float (i) / float (nx);
			float v = float (j) / float (ny);
			//std::cout << "u: " << u << " / v: " << v << " - ";
			ray r(origin, lower_left_corner + horizontal*u + vertical*v);
			
			vec3 col = color(r);
			const int ir = int(255.99 * col.r());
			const int ig = int(255.99 * col.g());
			const int ib = int(255.99 * col.b());
			image << ir << " " << ig << " " << ib << "\n";
		}
	}
	image.close();
}
