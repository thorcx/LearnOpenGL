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

	m_WVPLocation			= GetUniformLocation("gWVP");
	m_SamplerLocation		= GetUniformLocation("gSampler");
	m_DirLightColorLocation = GetUniformLocation("gDirectionalLight.Color");
	m_DirLightAmbientIntensityLocation = GetUniformLocation("gDirectionalLight.AmbientIntensity");

	if (m_DirLightAmbientIntensityLocation == -1 || m_DirLightColorLocation == -1 ||
		m_WVPLocation == -1 || m_SamplerLocation == -1)
	{
		return false;
	}

	return true;
}

void FLightingTechnique::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void FLightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_SamplerLocation, TextureUnit);
}

void FLightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
	glUniform3f(m_DirLightColorLocation, Light.Color.x, Light.Color.y, Light.Color.z);
	glUniform1f(m_DirLightAmbientIntensityLocation, Light.AmbientIntensity);
}

