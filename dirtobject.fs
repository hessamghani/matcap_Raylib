// Fragment shader for raylib
#version 330 core

// Uniforms
uniform sampler2D texture0;

// Varying
in vec3 vNormal;
out vec4 finalColor;

void main(void) {
    // Map normal to texture coordinates (from [-1,1] to [0,1])
    vec2 texCoord = (vNormal.xy + 1.0) / 2.0;
    
    // Sample the texture at the calculated texture coordinates
    vec4 smpColor = texture(texture0, texCoord);
    
    // Output the color
    finalColor = smpColor;
}
