// Inputs
attribute vec2 a_position;
attribute vec2 a_texCoord0;
attribute vec3 a_texCoord1;

// Uniforms
uniform sampler2D u_heights;
uniform mat4 u_worldViewProjectionMatrix;
uniform float u_scale;

// Outputs
varying vec3 v_barycentric;

void main()
{
  float height = texture2D(u_heights, a_texCoord0).y;

  gl_Position = u_worldViewProjectionMatrix * vec4(a_position.x * u_scale, clamp(height, 0.0, 5.0), a_position.y * u_scale, 1.0);
  v_barycentric = a_texCoord1;
}