#version 450

uniform mat4 modelViewProjectionMatrix;
in vec4 a_position;
out vec2 v_texcoord;

void main() {
    // Make a canvas covering the whole screen
    switch (gl_VertexID) {
        case 0: v_texcoord = vec2(0.0, 1.0);
                break;
        case 1: v_texcoord = vec2(1.0, 1.0);
                break;
        case 2: v_texcoord = vec2(1.0, 0.0);
                break;
        case 3: v_texcoord = vec2(0.0, 0.0);
                break;
    }

    gl_Position = modelViewProjectionMatrix * a_position;
}

