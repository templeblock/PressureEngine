#version 400

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in vec4 shadowCoords;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform sampler2D shadowMap;

uniform vec3 lightColor[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;

void main(void) {

	float objectNearestLight = texture(shadowMap, shadowCoords.xy).r;
	float lightFactor = 1.0;
	if (shadowCoords.z > objectNearestLight) {
		lightFactor = 1.0 - (shadowCoords.w * 0.4);
	}

	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitVectorToCamera = normalize(toCameraVector);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for(int i = 0; i < 4; i++) {
		float distance = length(toLightVector[i]);
		float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(toLightVector[i]);
		float nDot1 = dot(unitNormal, unitLightVector);
		float brightness = max(nDot1, 0.0);
		vec3 lightDirection = -unitLightVector;
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
		specularFactor = max(specularFactor, 0.0);
		float dampedFactor = pow(specularFactor, shineDamper);
		totalDiffuse += (brightness * lightColor[i]) / attFactor;
		totalSpecular += (dampedFactor * reflectivity * lightColor[i]) / attFactor;
	}
	totalDiffuse = max(totalDiffuse, 0.1) * lightFactor;

	vec4 textureColor = texture(textureSampler, pass_textureCoords);
	if (textureColor.a < 0.5) {
		discard;
	}

	out_Color = vec4(totalDiffuse, 1.0) * textureColor + vec4(totalSpecular, 1.0);

} 