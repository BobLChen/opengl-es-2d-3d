const char* SHADER_COLOR_VERT = STRINGIFY(

\n#ifdef GL_ES\n
precision mediump float;
\n#else\n
\n#endif\n

attribute vec3 posVa;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(posVa, 1);
}

);
