// Inputs
attribute vec2 a_position;
attribute vec2 a_texCoord0;
attribute vec3 a_texCoord1;

// Uniforms
uniform sampler2D heights;
uniform mat4 worldViewProjectionMatrix;
uniform float scale;

// Outputs
varying vec3 v_barycentric;
varying vec2 v_texCoord;

void main()
{
  float height = texture2D(heights, a_texCoord0).y;

  gl_Position = worldViewProjectionMatrix * vec4(a_position.x * scale, height * scale * 0.5, a_position.y * scale, 1.0);
  v_barycentric = a_texCoord1;
  v_texCoord = a_texCoord0;
}