// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step

vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}
vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}
vec3 fade(vec3 t) {return t*t*t*(t*(t*6.0-15.0)+10.0);}

float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  vec3 i = floor(st);
  vec3 frac = fract(st);

  vec3 point_x0y0z0 = i; 
  vec3 point_x1y0z0 = vec3(1 + i.x, i.y, i.z);
  vec3 point_x0y1z0 = vec3(i.x, 1 + i.y, i.z);
  vec3 point_x1y1z0 = vec3(1 + i.x, 1 + i.y, i.z);
  vec3 point_x0y0z1 = vec3(i.x, i.y, 1 + i.z);
  vec3 point_x1y0z1 = vec3(1 + i.x, i.y, 1 + i.z);
  vec3 point_x0y1z1 = vec3(i.x, 1 + i.y, 1 + i.z);
  vec3 point_x1y1z1 = i + vec3(1);

  vec3 gradient_x0y0z0 = random_direction(point_x0y0z0);
  vec3 gradient_x1y0z0 = random_direction(point_x1y0z0);
  vec3 gradient_x0y1z0 = random_direction(point_x0y1z0);
  vec3 gradient_x1y1z0 = random_direction(point_x1y1z0);
  vec3 gradient_x0y0z1 = random_direction(point_x0y0z1);
  vec3 gradient_x1y0z1 = random_direction(point_x1y0z1);
  vec3 gradient_x0y1z1 = random_direction(point_x0y1z1);
  vec3 gradient_x1y1z1 = random_direction(point_x1y1z1);

  vec3 distance_x0y0z0 = normalize(st - point_x0y0z0);
  vec3 distance_x1y0z0 = normalize(st - point_x1y0z0);
  vec3 distance_x0y1z0 = normalize(st - point_x0y1z0);
  vec3 distance_x1y1z0 = normalize(st - point_x1y1z0);
  vec3 distance_x0y0z1 = normalize(st - point_x0y0z1);
  vec3 distance_x1y0z1 = normalize(st - point_x1y0z1);
  vec3 distance_x0y1z1 = normalize(st - point_x0y1z1);
  vec3 distance_x1y1z1 = normalize(st - point_x1y1z1);

  float dots_x0y0z0 = dot(gradient_x0y0z0, distance_x0y0z0);
  float dots_x1y0z0 = dot(gradient_x1y0z0, distance_x1y0z0);
  float dots_x0y1z0 = dot(gradient_x0y1z0, distance_x0y1z0);
  float dots_x1y1z0 = dot(gradient_x1y1z0, distance_x1y1z0);
  float dots_x0y0z1 = dot(gradient_x0y0z1, distance_x0y0z1);
  float dots_x1y0z1 = dot(gradient_x1y0z1, distance_x1y0z1);
  float dots_x0y1z1 = dot(gradient_x0y1z1, distance_x0y1z1);
  float dots_x1y1z1 = dot(gradient_x1y1z1, distance_x1y1z1);

  vec3 smooothed = smooth_step(frac);  

  float lerp_x1, lerp_x2, lerp_y1, lerp_y2;
  lerp_x1 = mix(dots_x0y0z0, dots_x1y0z0, smooothed.x);
  lerp_x2 = mix(dots_x0y1z0, dots_x1y1z0, smooothed.x);
  lerp_y1 = mix(lerp_x1, lerp_x2, smooothed.y);

  lerp_x1 = mix(dots_x0y0z1, dots_x1y0z1, smooothed.x);
  lerp_x2 = mix(dots_x0y1z1, dots_x1y1z1, smooothed.x);
  lerp_y2 = mix(lerp_x1, lerp_x2, smooothed.y);

  float lerp_final = mix(lerp_y1, lerp_y2, smooothed.z);

  return clamp(lerp_final, -1, 1);
  /////////////////////////////////////////////////////////////////////////////
}

