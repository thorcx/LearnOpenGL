#pragma once


class ICallbacks
{
public:
	virtual void KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags) {};

	virtual void MouseCB(struct GLFWwindow *window, double x, double y) {};

	virtual void FrameBufferSizeCB(struct GLFWwindow *window, int width, int height) {};
};