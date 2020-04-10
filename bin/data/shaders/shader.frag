#version 450
#define PI 3.1415926

out vec4 fragColor;
in vec2 v_texcoord; //Between 0 and 1

uniform float bass;
uniform float mids;
uniform float high;
uniform float u_time;
uniform vec2 u_resolution;

float random (in vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

// Get fractal brownian motion for position st
#define OCTAVES 6
float fbm (in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * noise(st);
        st *= 2.;
        amplitude *= .5;
    }
    return value;
}

// For spinning the cloud
mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

void main(){
    // Cloud color depends on mid range of frequencies
	vec3 colorA = vec3(1.0, 0.2, 0.4);
	vec3 colorB = vec3(0.3, 0.3, 0.8);
	vec3 baseColor = mix(colorA, colorB, mids);

    // makes cloud color depend on bass frequencies and distance from center
	vec2 coord = v_texcoord;
	coord.x = coord.x * 2.0 - 1.0;
	coord.x = exp(abs(coord.x)) * sign(coord.x);
	float r = abs(coord.x) * bass;
	r -= abs(sin(PI * coord.y));

	vec2 noisecoord = v_texcoord - vec2(0.5, 0.5);
	mat2 noiseRotation = rotate2d(u_time * 0.1);
	noisecoord *= noiseRotation;
	noisecoord += vec2(0.5, 0.5);
	r -= fbm(3.0 * noisecoord + vec2(1.0,1.0));
	
	vec3 extraColor = vec3(r, r, r);

	fragColor = vec4(baseColor - extraColor, 1.0);
}

