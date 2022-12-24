// Compute Blinn-Phong Shading given a material specification, a point on a
// surface and a light direction. Assume the light is white and has a low
// ambient intensity.
//
// Inputs:
//   ka  rgb ambient color
//   kd  rgb diffuse color
//   ks  rgb specular color
//   p  specular exponent (shininess)
//   n  unit surface normal direction
//   v  unit direction from point on object to eye
//   l  unit light direction
// Returns rgb color
vec3 blinn_phong(
  vec3 ka,
  vec3 kd,
  vec3 ks,
  float p,
  vec3 n,
  vec3 v,
  vec3 l)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  vec3 ambient = vec3(ka.x * 0.5, ka.y * 0.5, ka.z * 0.5);

  vec3 lambertian = vec3(kd.x * 0.8 * (max(0.0, dot(n, l))), kd.y * 0.8 * (max(0.0, dot(n, l))), kd.z * 0.8 * (max(0.0, dot(n, l))));

  vec3 h = (v + l) / length(v + l);

  vec3 reflection = vec3((ks.x * 0.8 * pow((max(0.0, dot(n, h))), p)), (ks.y * 0.8 * pow((max(0.0, dot(n, h))), p)), (ks.z * 0.8 * pow((max(0.0, dot(n, h))), p)));

  return ambient + lambertian + reflection;

  /////////////////////////////////////////////////////////////////////////////
}


