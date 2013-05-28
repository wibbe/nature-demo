// Inputs
attribute vec2 a_position;
attribute vec2 a_texCoord0;
attribute vec3 a_texCoord1;

// Uniforms
uniform sampler2D heights;
//uniform mat4 worldViewProjectionMatrix;
uniform mat4 worldViewMatrix;
uniform mat4 projectionMatrix;
uniform float scale;

// Outputs
varying vec3 v_barycentric;
varying vec2 v_texCoord;
varying vec4 v_viewPosition;

void main()
{
  float height = texture2D(heights, a_texCoord0).y;

  vec4 viewPosition = worldViewMatrix * vec4(a_position.x * scale, height * scale * 0.5, a_position.y * scale, 1.0);

  gl_Position = projectionMatrix * viewPosition;
  v_viewPosition = viewPosition;
  v_texCoord = a_texCoord0;
}