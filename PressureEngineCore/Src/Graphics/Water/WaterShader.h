#pragma once
#include "../Shaders/Shader.h"
#include "../Entities/Camera.h"
#include "../Entities/Light.h"

namespace Pressure{

	class WaterShader : public Shader {

	public:
		WaterShader();

	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

	public:
		void loadTransformationMatrix(Matrix4f& matrix);
		void loadProjectionMatrix(Matrix4f& matrix);
		void loadViewMatrix(Camera& camera);
		void loadWaveModifier(float angle);
		void loadLights(std::vector<Light>& lights);
		void connectTextureUnits();

	private:
		int location_transformationMatrix;
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_waveModifier;
		int location_reflectionTexture;
		int location_refractionTexture;
		int location_depthMap;

		int location_lightPosition[4];
		int location_lightColor[4];
		int location_attenuation[4];
	};

}