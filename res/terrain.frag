// Uniforms
//uniform sampler2D u_heights;
uniform sampler2D normals;

uniform sampler2D texDirtDiffuse;
uniform sampler2D texDirtNormal;

uniform sampler2D texGrassDiffuse;
uniform sampler2D texGrassNormal;

uniform vec4 diffuseColor;
uniform vec3 lightDirection;
uniform float textureRepeat;

// Inputs
varying vec3 v_barycentric;
varying vec2 v_texCoord;

void main()
{
  //vec4 heightColor = texture2D(u_heights, v_texCoord);
  //color *= vec4(vec3(length(heightColor.xyz)), 1.0);

  vec3 normal = normalize(texture2D(normals, v_texCoord).xyz);
  vec3 tangent = cross(normal, vec3(1.0, 0.0, 0.0));
  vec3 binormal = cross(tangent, normal);
  mat3 tangentSpace = mat3(tangent, normal, binormal);


  vec4 dirtDiffuse = texture2D(texDirtDiffuse, v_texCoord * textureRepeat);
  vec3 dirtNormal = tangentSpace * normalize(texture2D(texDirtNormal, v_texCoord * textureRepeat).xyz);

  vec4 grassDiffuse = texture2D(texGrassDiffuse, v_texCoord * textureRepeat);
  vec3 grassNormal = tangentSpace * normalize(texture2D(texGrassNormal, v_texCoord * textureRepeat).xyz);

  //float blend = dot(normal, vec3(0.0, 1.0, 0.0)) > 0.9 ? 0.0 : 1.0;
  float blend = 0.0;

  vec3 finalColor = mix(dirtDiffuse, grassDiffuse, blend);
  vec3 finalNormal = mix(dirtNormal, grassDiffuse, blend);

  //float NdotL = dot(normal, normalize(lightDirection)) * 0.5 + 0.5;
  float NdotL = max(dot(finalNormal, normalize(lightDirection)), 0.0);



  vec3 color = vec3(NdotL) * finalColor.rgb * diffuseColor.rgb;

#ifdef WIREFRAME
  if (!all(greaterThan(v_barycentric, vec3(0.02))))
    color = vec3(0.0, 0.0, 1.0);
#endif

  gl_FragColor = vec4(color, 1.0);
}