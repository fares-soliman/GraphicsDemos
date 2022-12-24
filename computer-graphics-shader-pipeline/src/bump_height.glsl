// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  
   vec3 is_moon_mult;
  if (is_moon)
    is_moon_mult = vec3(-11, 9.2, 8.2);  
  else
    is_moon_mult = vec3(-1.2, 1.5, 0.7);
  float height = improved_perlin_noise(vec3(improved_perlin_noise(is_moon_mult * s)));

  float is_moon_height_mult;
  if (is_moon)
    is_moon_height_mult = 0.7;
  else
    is_moon_height_mult = 0.2;
  return is_moon_height_mult * smooth_heaviside(height, length(s));
  /////////////////////////////////////////////////////////////////////////////
}
