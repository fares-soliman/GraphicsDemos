// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
float theta = -mod(animation_seconds, 4.0) * 2 * M_PI / 4.0;

  mat4 light_transform = mat4(
  cos(theta), 0, -sin(theta), 0,
           0, 1,           0, 0,
  sin(theta), 0,  cos(theta), 0,
           0, 0,           0, 1);

  vec4 light_position = vec4(5.0, 5.0, 5.0, 1.0);
  vec4 light = view * light_transform * light_position;

  vec3 n, v, l;
  v = -normalize(view_pos_fs_in.xyz/view_pos_fs_in.w);
  l = normalize((light.xyz/light.w) - (view_pos_fs_in.xyz/view_pos_fs_in.w));

  vec3 ka, ks, kd;
  float p;
  vec3 base;

  if (is_moon) {
    ka = vec3(0.10, 0.2, 0.2);
    ks = vec3(0.8, 0.8, 0.8);
    kd = vec3(0.4, 0.4, 0.4);
    p = 1000;
    base = vec3(0.4);
  } else{
    ka = vec3(0.2, 0.1, 0.2);
    ks = vec3(0.6, 0.6, 0.6);
    kd = vec3(0.4, 0.5, 0.9);
    p = 500;
    base = vec3(0, 0, 1);
  }

  vec3 T, B;
  float e = 0.0001;

  tangent(normalize(sphere_fs_in), T, B);
  vec3 bp = bump_position(is_moon, normalize(sphere_fs_in)); 

  vec3 normal_vec1 = (bump_position(is_moon, normalize(sphere_fs_in + (e * T))) - bp) / e;
  vec3 normal_vec2 = (bump_position(is_moon, normalize(sphere_fs_in + (e * B))) - bp) / e;

  n = normalize(cross(normal_vec1, normal_vec2));


  v = -normalize((view * vec4(bp, 1.0)).xyz);
  l = normalize(light.xyz - (view * vec4(bp, 1.0)).xyz);

  color = base * blinn_phong(ka, kd, ks, p, n, v, l);

}
