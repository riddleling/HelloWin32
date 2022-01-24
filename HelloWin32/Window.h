#pragma once

class Window final
{
public:
	Window(HINSTANCE hInstance, LPCWSTR lpszClassName, LPCWSTR lpWindowName);

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM);

	HWND hWnd_;
	HWND hLabel_;
	HWND hButton_;

	void SetWindowSize();
	void SetLabelPos();
	void SetButtonPos();
	void SayHello();
};