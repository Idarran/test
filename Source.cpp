#include <windows.h>

//przyciski
HWND g_przycisk;

//pola
HWND g_text;

//funkcja obs³ugi komunikatów okna
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_COMMAND:
		if ((HWND)lp == g_przycisk) 
		{
			SetWindowText(g_text, "BOOM!");
			MessageBox(hwnd, "You've just annihilated planet Earth!", "Congratulations!", MB_OK | MB_ICONWARNING);
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wp, lp);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//rejestracja klasy okienkowej
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = wnd_proc;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "NAZWA_KLASY";
	RegisterClassEx(&wc);

	//tworzenie okna...
	HWND window = CreateWindowEx(0, "NAZWA_KLASY", "Through the window!",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	if (NULL == window) return -1; //sprawdzenie, czy siê uda³o

								   //tworzenie przycisku
	g_przycisk = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "BigRedBttn",
		WS_CHILD | WS_VISIBLE,
		370, 300, 200, 30, window, NULL, hInstance, NULL);

	//tworzenie pola tekstowego
	g_text = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		370, 250, 200, 30, window, NULL, hInstance, NULL);


	//pêtla obs³ugi komunikatów
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}
