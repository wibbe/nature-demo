// Uniforms
uniform sampler2D normals;

uniform sampler2D texDirtDiffuse;
uniform sampler2D texDirtNormal;

uniform sampler2D texGrassDiffuse;
uniform sampler2D texGrassNormal;

uniform float textureRepeat;

// Inputs
varying vec2 v_texCoord;

void main()
{
  vec3 normal = normalize(texture2D(normals, v_texCoord).xyz);
  vec3 tangent = cross(normal, vec3(1.0, 0.0, 0.0));
  vec3 binormal = cross(tangent, normal);
  mat3 tangentSpace = mat3(tangent, normal, binormal);

  vec4 dirtDiffuse = texture2D(texDirtDiffuse, v_texCoord * textureRepeat);
  vec3 dirtNormal = tangentSpace * normalize(texture2D(texDirtNormal, v_texCoord * textureRepeat).xyz);

  vec4 grassDiffuse = texture2D(texGrassDiffuse, v_texCoord * textureRepeat);
  vec3 grassNormal = tangentSpace * normalize(texture2D(texGrassNormal, v_texCoord * textureRepeat).xyz);

  float blend = dot(normal, vec3(0.0, 1.0, 0.0)) > 0.8 ? 1.0 : 0.0;

  vec3 finalColor = mix(dirtDiffuse, grassDiffuse, blend);
  vec3 finalNormal = mix(dirtNormal, grassNormal, blend);

  gl_FragData[0] = vec4(finalColor, 1.0);
  gl_FragData[1] = vec4(finalNormal, 1.0);
}