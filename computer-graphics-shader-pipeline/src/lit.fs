// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  float theta = -mod(animation_seconds, 4.0) * 2 * M_PI / 4.0;

  mat4 light_transform = mat4(
  cos(theta), 0, -sin(theta), 0,
           0, 1,           0, 0,
  sin(theta), 0,  cos(theta), 0,
           0, 0,           0, 1);

  vec4 light_position = vec4(5.0, 5.0, 5.0, 1.0);
  vec4 light = view * light_transform * light_position;

  vec3 n, v, l;
  n = normalize(normal_fs_in);
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

  

  color = base * blinn_phong(ka, kd, ks, p, n, v, l);
  /////////////////////////////////////////////////////////////////////////////
}
