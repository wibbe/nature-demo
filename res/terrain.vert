// Inputs
attribute vec2 a_position;
attribute vec2 a_texCoord0;
attribute vec3 a_texCoord1;

// Uniforms
uniform mat4 u_worldViewProjectionMatrix;
uniform float u_scale;

// Outputs
varying vec3 v_barycentric;

void main()
{
  // Transform position to clip space.
  gl_Position = u_worldViewProjectionMatrix * vec4(a_position.x * u_scale, 0.0, a_position.y * u_scale, 1.0);
  v_barycentric = a_texCoord1;
}