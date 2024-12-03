// Vertex shader for raylib
#version 330 core

// Input attributes
in vec3 vertexPosition;
in vec3 vertexNormal;

// Uniforms
uniform mat4 mvp;         // In raylib, `mvp` is typically used instead of `mvpMatrix`
uniform mat4 normalMatrix; // Pass this from your application

// Varying
out vec3 vNormal;

void main(void) {
    // Normalize the vertexNormal using the normal matrix (inverse transpose of model-view matrix)
    vNormal = normalize((normalMatrix * vec4(vertexNormal, 0.0)).xyz);
    
    // Output the position to the GPU pipeline
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
