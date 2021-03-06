#pragma once
#include "../Shaders/Shader.h"
#include "../Entities/Camera.h"
#include "../Entities/Light.h"

namespace Pressure {

	class EntityShader : public Shader {

	public:
		EntityShader();

	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

	public:
		//load uniforms.
		void loadTransformationMatrix(Matrix4f& matrix);
		void loadProjectionmatrix(Matrix4f& matrix);
		void loadViewMatrix(Matrix4f& matrix);
		void loadLights(std::vector<Light>& lights);
		void loadShineVariables(float damper, float reflectivity);
		void loadFakeLighting(bool useFakeLighting);
		void loadClipPlane(const Vector4f& plane);
		void loadToShadowMapSpace(Matrix4f& matrix);
		void connectTextureUnits();
		void loadWindModifier(const float windModifier);
		void loadShadowDistance(float shadowDistance);

	private:
		//uniform locations.
		int location_transformationMatrix;
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_lightPosition[4];
		int location_lightColor[4];
		int location_attenuation[4];
		int location_shineDamper;
		int location_reflectivity;
		int location_fakeLighting;
		int location_plane;
		int location_toShadowMapSpace;
		int location_shadowMap;
		int location_textureSampler;
		int location_windModifier;
		int location_shadowDistance;

	};

}
