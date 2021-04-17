uniform sampler2D texture;
uniform float renderCount;

void main() {
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    pixel.x = (sin(renderCount)/2.0 + 0.5) * pixel.x;
    gl_FragColor = gl_Color * pixel;
}
