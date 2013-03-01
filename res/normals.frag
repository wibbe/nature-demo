
uniform sampler2D heights;
uniform float pixelScale;

varying vec2 v_pos;

vec3 getPosition(float x, float y)
{
  vec2 uv = v_pos + vec2(x, y) * pixelScale;
  float height = texture2D(heights, uv).y;
  return vec3(uv.x, height * 2.0, uv.y);
}

vec3 getNormal(vec3 pos, float x, float y)
{
  vec3 tangent = normalize(getPosition(x, y) - pos);
  vec3 binormal = cross(vec3(0.0, 1.0, 0.0), tangent);
  return normalize(cross(tangent, binormal));
}

void main()
{
  vec3 center = getPosition(0.0, 0.0);
  vec3 sum = getNormal(center, 1.0, 0.0) +
             getNormal(center, 1.0, -1.0) +
             getNormal(center, 0.0, -1.0) +
             getNormal(center, -1.0, -1.0) +
             getNormal(center, -1.0, 0.0) +
             getNormal(center, -1.0, 1.0) +
             getNormal(center, 0.0, 1.0) +
             getNormal(center, 1.0, 1.0);

  vec3 normal = normalize(sum / 8.0);
  gl_FragColor = vec4(normal, 1.0);
}