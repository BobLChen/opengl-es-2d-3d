const char* SHADER_TEXTURE_VERT = STRINGIFY(

\n#ifdef GL_ES\n
precision mediump float;
\n#else\n

\n#endif\n

attribute vec3 posVa;
attribute vec2 uvVa;

varying vec2 uvVarying;

uniform mat4 mvp;

void main() {
    uvVarying = uvVa;
    gl_Position = mvp * vec4(posVa, 1);
}

);