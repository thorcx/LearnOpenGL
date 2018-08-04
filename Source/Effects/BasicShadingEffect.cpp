#include <glad/glad.h>

#include "BasicShadingEffect.h"

FBasicShadingEffect::FBasicShadingEffect()
{

}

bool FBasicShadingEffect::Init()
{
	if (!Technique::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "Source/Shaders/DebugBaseVS.glsl")) {
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "Source/Shaders/DebugBaseFS.glsl")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}
	return true;
}

