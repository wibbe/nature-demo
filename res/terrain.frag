#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform vec4 u_diffuseColor;                  // Diffuse color

// Inputs
varying vec3 v_barycentric;

void main()
{
  if (all(greaterThan(v_barycentric, vec3(0.02))))
    gl_FragColor = vec4(u_diffuseColor.xyz, 1.0);
  else
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}