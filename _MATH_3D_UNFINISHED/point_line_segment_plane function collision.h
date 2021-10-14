#include <iostream>
#include <cmath>

struct Vec3
{
  float x;
  float y;
  float z;
  static inline Vec3 sub(const Vec3& v1,const Vec3& v2) { return {v1.x - v2.x,v1.y - v2.y,v1.z - v2.z}; }
  static inline Vec3 add(const Vec3& v1,const Vec3& v2) { return {v1.x + v2.x,v1.y + v2.y,v1.z + v2.z}; }
  static inline float dot(const Vec3& v1,const Vec3& v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }
  static inline Vec3 cross(const Vec3& v1,const Vec3& v2) { return {v1.y*v2.z - v1.z*v2.y,v1.z*v2.x - v1.x*v2.z,v1.x*v2.y - v1.y*v2.x}; }
};

inline bool check_if_same_size(const Vec3& p1,const Vec3& p2,const Vec3& a,const Vec3& b)
{
	return Vec3::dot(Vec3::cross(Vec3::sub(b,a),Vec3::sub(p1,a)),Vec3::cross(Vec3::sub(b,a),Vec3::sub(p2,a))) >= 0;
}

inline bool check_if_point_in_triangle(const Vec3& p,const Vec3& a,const Vec3& b,const Vec3& c)
{
	return check_if_same_size(p,a,b,c) && check_if_same_size(p,b,a,c) && check_if_same_size(p,c,a,b);
}

inline float get_distance_between_points(Vec3 p1,Vec3 p2)
{
  return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
}

Vec3 get_closest_point_to_point_to_3d_line(const Vec3& p1,const Vec3& p2,const Vec3& p)
{
  Vec3 dl = {p2.x-p1.x,p2.y-p1.y,p2.z-p1.z};
  float t = (dl.x*(p.x - p1.x) + dl.y*(p.y - p1.y) + dl.z*(p.z - p1.z))/(dl.x*dl.x + dl.y*dl.y + dl.z*dl.z);
  return {p1.x + t*dl.x,p1.y + t*dl.y,p1.z + t*dl.z};
}

inline float get_closest_distance_to_point_to_3d_line(const Vec3& p1,const Vec3& p2,const Vec3& p)
{
  Vec3 c_point = get_closest_point_to_point_to_3d_line(p1,p2,p);
  return get_distance_between_points(p, c_point);
}

Vec3 get_closest_point_to_point_to_3d_segment(const Vec3& p1,const Vec3& p2,const Vec3& p)
{
  Vec3 dl = {p2.x-p1.x,p2.y-p1.y,p2.z-p1.z};
  float t = (dl.x*(p.x - p1.x) + dl.y*(p.y - p1.y) + dl.z*(p.z - p1.z))/(dl.x*dl.x + dl.y*dl.y + dl.z*dl.z);
  if(t > 0 && t < (p2.x - p1.x)/dl.x) return {p1.x + t*dl.x,p1.y + t*dl.y,p1.z + t*dl.z};
  else if(t < 0) return p1;
  else return p2;
}

float get_closest_distance_to_point_to_3d_segment(const Vec3& p1,const Vec3& p2,const Vec3& p)
{
  Vec3 c_point = get_closest_point_to_point_to_3d_segment(p1,p2,p);
  return get_distance_between_points(p, c_point);
}

Vec3 get_closest_point_to_point_to_plane(Vec3 p1,Vec3 p2,Vec3 p3,Vec3 p)
{
	
}

int main()
{
  float pld = get_closest_distance_to_point_to_3d_line({2,3,5}, {1,2,3}, {8,2,10});
  std::cout << pld << std::endl;
}