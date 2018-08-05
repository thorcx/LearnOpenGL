#include <glad/glad.h>
#include "LightingTechnique.h"


FLightingTechnique::FLightingTechnique()
{

}

bool FLightingTechnique::Init()
{
	if (!Technique::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "Source/Shaders/LightingVS.glsl")) {
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "Source/Shaders/LightingFS.glsl")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WVPLocation							= GetUniformLocation("gWVP");
	m_WorldMatrixLocation					= GetUniformLocation("gWorld");
	m_SamplerLocation						= GetUniformLocation("gSampler");
	m_DirLightLocation.Color				= GetUniformLocation("gDirectionalLight.Base.Color");
	m_DirLightLocation.AmbientIntensity		= GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	m_DirLightLocation.Direction			= GetUniformLocation("gDirectionalLight.Direction");
	m_DirLightLocation.DiffuseIntensity		= GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
	
	m_eyeWorldPosLocation					= GetUniformLocation("gEyeWorldPos");
	m_matSpecularIntensityLocation			= GetUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation				= GetUniformLocation("gSpecularPower");

	m_numPointLightsLocation				= GetUniformLocation("gNumPointLights");

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLightsLocation); i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
		m_pointLightsLocation[i].Color = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
		m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
		m_pointLightsLocation[i].Position = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
		m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
		m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
		m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
		m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

		if (m_pointLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
			return false;
		}
	}

	if (m_DirLightLocation.AmbientIntensity == 0xFFFFFFFF ||
		m_WVPLocation == 0xFFFFFFFF ||
		m_WorldMatrixLocation == 0xFFFFFFFF ||
		m_SamplerLocation == 0xFFFFFFFF ||
		m_DirLightLocation.Color == 0xFFFFFFFF ||
		m_DirLightLocation.DiffuseIntensity == 0xFFFFFFFF ||
		m_DirLightLocation.Direction == 0xFFFFFFFF ||
		m_eyeWorldPosLocation == 0xFFFFFFFF || 
		m_matSpecularIntensityLocation == 0xFFFFFFFF ||
		m_matSpecularPowerLocation == 0xFFFFFFFF) {
		return false;
	}


	return true;
}

void FLightingTechnique::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void FLightingTechnique::SetWorldMatrix(const Matrix4f& World)
{
	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)World.m);
}

void FLightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_SamplerLocation, TextureUnit);
}

void FLightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
	glUniform3f(m_DirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
	glUniform1f(m_DirLightLocation.AmbientIntensity, Light.AmbientIntensity);
	Vector3f Direction = Light.Direction;
	Direction.Normalize();
	glUniform3f(m_DirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
	glUniform1f(m_DirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}

void FLightingTechnique::SetEyeWorldPos(const Vector3f& EyeWorldPos)
{
	glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
}

void FLightingTechnique::SetMatSpecularIntensity(float Intensity)
{
	glUniform1f(m_matSpecularIntensityLocation, Intensity);
}

void FLightingTechnique::SetMatSpecularPower(float Power)
{
	glUniform1f(m_matSpecularPowerLocation, Power);
}

void FLightingTechnique::SetPointLights(unsigned int NumLights, const PointLight* pLights)
{
	glUniform1i(m_numPointLightsLocation, NumLights);

	for (unsigned int i = 0; i < NumLights; i++) {
		glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
		glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
		glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
		glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
		glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}
}

