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
	m_DirLightLocation.Color				= GetUniformLocation("gDirectionalLight.Color");
	m_DirLightLocation.AmbientIntensity		= GetUniformLocation("gDirectionalLight.AmbientIntensity");
	m_DirLightLocation.Direction			= GetUniformLocation("gDirectionalLight.Direction");
	m_DirLightLocation.DiffuseIntensity		= GetUniformLocation("gDirectionalLight.DiffuseIntensity");
	
	m_eyeWorldPosLocation					= GetUniformLocation("gEyeWorldPos");
	m_matSpecularIntensityLocation			= GetUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation				= GetUniformLocation("gSpecularPower");

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

