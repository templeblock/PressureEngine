#version 400
//#line 1 "WaterFragmentShader.glsl"

in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in vec4 clipSpace;

out vec4 out_Color;

uniform vec3 lightColor[4];
uniform vec3 attenuation[4];

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D depthMap;

const float shineDamper = 10;
const float reflectivity = 0.8;

const vec4 waterColor = vec4(0.0, 0.6, 1.0, 1.0);
const float near = 0.1;
const float far = 1000.0;

void main(void) {

	vec2 ndc = (clipSpace.xy/clipSpace.w) / 2.0 + 0.5;
	float depth = texture(depthMap, ndc).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	float waterDepth = floorDistance - waterDistance;

	vec2 distortion = ndc - vec2(surfaceNormal.x / 8.0, surfaceNormal.z / 8.0) * clamp(waterDepth / 20.0, 0.0, 1.0);
	distortion = clamp(distortion, 0.001, 0.999);

	vec4 reflectColor = texture(reflectionTexture, vec2(distortion.x, -distortion.y));
	vec4 refractColor = texture(refractionTexture, distortion);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for (int i = 0; i < 4; i++) {
		float distance = length(toLightVector[i]);
		float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);		
		float nDot1 = dot(surfaceNormal, toLightVector[i]);
		float brightness = max(nDot1, 0.0);
		vec3 lightDirection = -toLightVector[i];
		vec3 reflectedLightDirection = reflect(lightDirection, surfaceNormal);
		float specularFactor = dot(reflectedLightDirection, toCameraVector);
		specularFactor = max(specularFactor, 0.0);
		float dampedFactor = pow(specularFactor, shineDamper);
		totalDiffuse += (brightness * lightColor[i]) / attFactor;
		totalSpecular += (dampedFactor * reflectivity * lightColor[i]) / attFactor;
	}
	totalDiffuse = max(totalDiffuse, 0.1);
	float refractiveFactor = dot(toCameraVector, surfaceNormal);
	totalSpecular *= clamp(waterDepth / 10.0, 0.0, 1.0);

	out_Color = vec4(totalDiffuse, 1.0) * mix(reflectColor, refractColor, refractiveFactor) + vec4(totalSpecular, 1.0);
	out_Color = mix(out_Color, waterColor, 0.2);
	out_Color.a = clamp(waterDepth / 5.0, 0.0, 1.0);

}