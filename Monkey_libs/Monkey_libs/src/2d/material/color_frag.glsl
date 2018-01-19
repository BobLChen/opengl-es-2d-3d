const char* SHADER_COLOR_FRAG = STRINGIFY(
\n#ifdef GL_ES\n
precision mediump float;
\n#else\n
\n#endif\n
uniform vec4 colorAlpha;

void main() {
    gl_FragColor = colorAlpha;
}
);