const char* SHADER_TEXTURE_FRAG = STRINGIFY(

\n#ifdef GL_ES\n
precision mediump float;
\n#else\n
\n#endif\n

// uv
varying vec2 uvVarying;
// 贴图
uniform sampler2D texture;
// 透明度
uniform float alpha;

void main() {
    vec4 color   = texture2D(texture, uvVarying);
    color *= alpha;
    gl_FragColor = color;
}

);