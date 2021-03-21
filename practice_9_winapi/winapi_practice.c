#include <Windows.h>
#include <assert.h>

static HDC hmc;

BOOL pressedLMouse = FALSE;

BOOL thickness = FALSE;

int rCircle = 1;

COLORREF color = RGB(0, 0, 0);

HMENU menuColor;

HMENU menuThickness;

enum MENU
{
	CLEAR = 100,
	EXPORT,
	EXPORTAS,
	BEGINC = 200,
	BLACK,
	RED,
	GREEN,
	BLUE,
	WHITE,
	AQUA,
	FUCHSIA,
	GRAY,
	LIME,
	MAROON,
	NAVY,
	OLIVE,
	PURPLE,
	SILVER,
	TEAL,
	YELLOW,
	ENDC,
	BEGINT = 300,
	VERYSMALL,
	SMALL,
	NORMAL,
	LARGE,
	VERYLARGE,
	ENDT,
};


//Для смены галочек в меню
void checkedChange(HMENU menu,int changedItem,int begin,int end)
{
	for (int i = begin+1; i < end; ++i)
	{
		if(i==changedItem)
			CheckMenuItem(menu, i, MF_CHECKED);
		else
			CheckMenuItem(menu, i, MF_UNCHECKED);
	}
}


PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// Retrieve the bitmap color format, width, and height.  
	assert(GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp));

	// Convert the color format to a count of bits.  
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// Allocate memory for the BITMAPINFO structure. (This structure  
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
	// data structures.)  

	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));

	// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure.  

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag.  
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color  
	// indices and store the result in biSizeImage.  
	// The width must be DWORD aligned unless the bitmap is RLE 
	// compressed. 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the  
	// device colors are important.  
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void CreateBMPFile(LPTSTR pszFile, HBITMAP hBMP)
{
	HANDLE hf;                 // file handle  
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // memory pointer  
	DWORD dwTotal;              // total count of bytes  
	DWORD cb;                   // incremental count of bytes  
	BYTE *hp;                   // byte pointer  
	DWORD dwTmp;
	PBITMAPINFO pbi;
	HDC hDC;

	hDC = CreateCompatibleDC(GetWindowDC(GetDesktopWindow()));
	SelectObject(hDC, hBMP);

	pbi = CreateBitmapInfoStruct(hBMP);

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	assert(lpBits);

	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	assert(GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS));

	// Create the .BMP file.  
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	assert(hf != INVALID_HANDLE_VALUE);

	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	// Compute the size of the entire file.  
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	assert(WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL));

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	assert(WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)));

	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	assert(WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL));

	// Close the .BMP file.  
	assert(CloseHandle(hf));

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}

BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName)
{
	HDC hDC;
	int iBits;
	WORD wBitCount;
	DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	BITMAP Bitmap0;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh, hDib, hPal, hOldPal2 = NULL;
	hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;
	GetObject(hBitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap0.bmWidth;
	bi.biHeight = -Bitmap0.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 256;
	dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8
		* Bitmap0.bmHeight;
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}


	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

	if (hOldPal2)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	fh = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}


// найденная на просторах интернета функция, частично изменена
void SaveBMP(HWND hWnd, HDC hdc,int check)
{
	//BITMAPFILEHEADER bfh; //структура с заголовком файла
	//BITMAPINFOHEADER bih;   //структура с описанием формата картинки
	//BITMAPINFO bi;  //описание формата для функции GetDIBits ()
	//void *pdwBits = NULL; //указатель на буфер с будущим рисунком
	//DWORD dwWB = 0; //переменная для хранения записанных байт в файл
	//HANDLE hFile = NULL; //хэндл открытого файла

	////HBITMAP bmpMem = CreateCompatibleBitmap(hdc, 800, 600);

	////Создаем пустой буфер, в который потом скопируется картинка
	//pdwBits = (void *)GlobalAlloc(GMEM_FIXED, 800 * 600 * 4);

	////Обнуляем структуры
	//memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
	//memset(&bih, 0, sizeof(BITMAPINFOHEADER));
	//memset(&bi, 0, sizeof(BITMAPINFO));

	////Заполняем заголовочную структуру
	//bfh.bfType = 0x4D42;                           // Обозначим, что это bmp 'BM'
	//bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
	//bfh.bfSize = bfh.bfOffBits + 800 * 600 * 4;   // Посчитаем размер конечного файла

	//											  //Заполняем описание картинки
	//bih.biSize = sizeof(bih);                      // Так положено
	//bih.biBitCount = 16;                           // 16 бит на пиксель
	//bih.biCompression = BI_RGB;                    // Без сжатия
	//bih.biHeight = 600;
	//bih.biWidth = 800;
	//bih.biPlanes = 1;

	///*RGBQUAD rgbquad;

	//rgbquad.rgbBlue = 255;
	//rgbquad.rgbGreen = 255;
	//rgbquad.rgbRed = 255;
	//rgbquad.rgbReserved = 0;*/

	//bi.bmiHeader = bih;
	////bi.bmiColors[0] = rgbquad;

	////Копируем в структуру BITMAPINFO
	////CopyMemory(&bi, &bih, sizeof(BITMAPINFOHEADER));

	////Получаем с помощью функции саму картинку из контекста в памяти
	//CreateDIBitmap(hdc, &bih, 0, pdwBits, &bi, DIB_RGB_COLORS);
	////GetDIBits(hdc, bmpMem, 0, 600, pdwBits, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	//Создаем файл для записи

	//if(!check)
	//	hFile = CreateFileW(L"D:\\output.bmp",
	//		GENERIC_WRITE,
	//		0,
	//		NULL,
	//		CREATE_ALWAYS,
	//		FILE_ATTRIBUTE_NORMAL,
	//		(HANDLE)NULL);
	//else
	//{
	//	OPENFILENAME ofn = { 0 };
	//	TCHAR pathBuffer[1024] = { 0 };
	//	ofn.lStructSize = sizeof(OPENFILENAME);
	//	ofn.hwndOwner = hWnd;
	//	ofn.nMaxFile = sizeof(pathBuffer)/sizeof(*pathBuffer);
	//	ofn.lpstrFile = pathBuffer;
	//	GetSaveFileNameW(&ofn);

	//	pathBuffer;

	//	hFile = CreateFileW(pathBuffer,
	//		GENERIC_WRITE,
	//		0,
	//		NULL,
	//		CREATE_ALWAYS,
	//		FILE_ATTRIBUTE_NORMAL,
	//		(HANDLE)NULL);
	//}
	//if (hFile == INVALID_HANDLE_VALUE) {
	//	if (pdwBits) GlobalFree(pdwBits);
	//	return;
	//}

	////Записываем структуру с заголовком файла
	//if (!WriteFile(hFile, (void *)&bfh, sizeof(BITMAPFILEHEADER), &dwWB, NULL)) {
	//	if (pdwBits) GlobalFree(pdwBits);
	//	return;
	//}

	////Записываем структуру с описанием формата картинки
	//if (!WriteFile(hFile, (void *)&bih, sizeof(BITMAPINFOHEADER), &dwWB, NULL)) {
	//	if (pdwBits) GlobalFree(pdwBits);
	//	return;
	//}

	//if (!WriteFile(hFile, (void *)pdwBits, 800 * 600 * 4, &dwWB, NULL)) {
	//	if (pdwBits) GlobalFree(pdwBits);
	//	return;
	//}

	////Закрываем хэндл файла и очищаем буфер
	//CloseHandle(hFile);
	//if (pdwBits) GlobalFree(pdwBits);
}

LRESULT CALLBACK PaintProc(_In_ HWND hwindow, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;


	case WM_LBUTTONDOWN:
	{
		pressedLMouse = TRUE;
		return 0;
	}
	case WM_LBUTTONUP:
	{
		pressedLMouse = FALSE;
		return 0;
	}
	case WM_MOUSEMOVE: {
		if (pressedLMouse)
		{
			RECT r = { 0 };
			//для точки
			if (!thickness)
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				SetPixel(hmc, x, y, color);
				r.left = x;
				r.top = y;
				r.right = x + 1;
				r.bottom = y + 1;
			}
			//для круга
			else
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				HBRUSH hBrush = CreateSolidBrush(color);
				HPEN hPen = CreatePen(PS_SOLID,0,color);
				HBRUSH hprevBrush = SelectObject(hmc, hBrush);
				HPEN hprevPen = SelectObject(hmc, hPen);
				Ellipse(hmc, x - rCircle, y - rCircle, x + rCircle, y + rCircle);
				r.left = x - rCircle;
				r.top = y - rCircle;
				r.right = x + rCircle;
				r.bottom = y + rCircle;
				SelectObject(hmc, hprevBrush);
				SelectObject(hmc, hprevPen);
				DeleteObject(hBrush);
				DeleteObject(hPen);
				DeleteObject(hprevBrush);
				DeleteObject(hprevPen);
			}
			InvalidateRect(hwindow, &r, FALSE);
			UpdateWindow(hwindow);
		}
		return 0;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps = { 0 };
		HDC hdc = BeginPaint(hwindow, &ps);
		if (hdc != NULL) {
			const int x = ps.rcPaint.left;
			const int y = ps.rcPaint.top;
			const int w = ps.rcPaint.right - x + 1;
			const int h = ps.rcPaint.bottom - y + 1;
			BitBlt(hdc, x, y, w, h, hmc, x, y, SRCCOPY);
			EndPaint(hwindow, &ps);
		}
		return 0;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case CLEAR:
		{
			RECT rect = { 0,0,800,600 };
			//GetWindowRect(hwindow, &rect);         не работает
			FillRect(hmc, &rect, RGB(255, 255, 255));
			InvalidateRect(hwindow, &rect, FALSE);
			UpdateWindow(hwindow);
			break;
		}
		case EXPORT:
		{
			RECT rec;
			GetClientRect(hwindow, &rec);
			//HDC hdc1 = GetWindowDC(hwindow);
			HBITMAP bmp = CreateCompatibleBitmap(hmc, rec.right-rec.left, rec.bottom-rec.top);
			//HDC hdc2 = CreateCompatibleDC(hmc);
			SelectObject(hmc, bmp);
			BitBlt(hmc, 0, 0, rec.right, rec.bottom, hmc, 0, 0, SRCCOPY);
			//CreateBMPFile(L"D:\\output.bmp",bmp);
			SaveHBITMAPToFile(bmp, L"D:\\output.bmp");
			break;
		}
		case EXPORTAS:
		{
			
			break;
		}
		case BLACK:
		{
			color = RGB(0, 0, 0);
			checkedChange(menuColor,BLACK,BEGINC,ENDC);
			break;
		}
		case RED:
		{
			color = RGB(255, 0, 0); 
			checkedChange(menuColor,RED,BEGINC,ENDC);
			break;
		}
		case GREEN:
		{
			color = RGB(0, 128, 0);
			checkedChange(menuColor,GREEN,BEGINC,ENDC);
			break;
		}
		case BLUE:
		{
			color = RGB(0, 0, 255);
			checkedChange(menuColor,BLUE,BEGINC,ENDC);
			break;
		}
		case WHITE:
		{
			color = RGB(255, 255, 255);
			checkedChange(menuColor,WHITE,BEGINC,ENDC);
			break;
		}
		case AQUA:
		{
			color = RGB(0, 255, 255);
			checkedChange(menuColor, AQUA, BEGINC, ENDC);
			break;
		}
		case FUCHSIA:
		{
			color = RGB(255, 0, 255);
			checkedChange(menuColor, FUCHSIA, BEGINC, ENDC);
			break;
		}
		case GRAY:
		{
			color = RGB(128, 128, 128);
			checkedChange(menuColor, GRAY, BEGINC, ENDC);
			break;
		}
		case LIME:
		{
			color = RGB(0, 255, 0);
			checkedChange(menuColor, LIME, BEGINC, ENDC);
			break;
		}
		case MAROON:
		{
			color = RGB(128, 0, 0);
			checkedChange(menuColor, MAROON, BEGINC, ENDC);
			break;
		}
		case NAVY:
		{
			color = RGB(0, 0, 128);
			checkedChange(menuColor, NAVY, BEGINC, ENDC);
			break;
		}
		case OLIVE:
		{
			color = RGB(128, 128, 0);
			checkedChange(menuColor, OLIVE, BEGINC, ENDC);
			break;
		}
		case PURPLE:
		{
			color = RGB(128, 0, 128);
			checkedChange(menuColor, PURPLE, BEGINC, ENDC);
			break;
		}
		case SILVER:
		{
			color = RGB(192, 192, 192);
			checkedChange(menuColor, SILVER, BEGINC, ENDC);
			break;
		}
		case TEAL:
		{
			color = RGB(0, 128, 128);
			checkedChange(menuColor, TEAL, BEGINC, ENDC);
			break;
		}
		case YELLOW:
		{
			color = RGB(255, 255, 128);
			checkedChange(menuColor, YELLOW, BEGINC, ENDC);
			break;
		}
		case VERYSMALL:
		{
			thickness = FALSE;
			checkedChange(menuThickness, VERYSMALL, BEGINT, ENDT);
			break;
		}
		case SMALL:
		{
			thickness = TRUE;
			rCircle = 5;
			checkedChange(menuThickness,SMALL,BEGINT,ENDT);
			break;
		}
		case NORMAL:
		{
			thickness = TRUE;
			rCircle = 10;
			checkedChange(menuThickness, NORMAL, BEGINT, ENDT);
			break;
		}
		case LARGE:
		{
			thickness = TRUE;
			rCircle = 25;
			checkedChange(menuThickness, LARGE, BEGINT, ENDT);
			break;
		}
		case VERYLARGE:
		{
			thickness = TRUE;
			rCircle = 100;
			checkedChange(menuThickness, VERYLARGE, BEGINT, ENDT);
			break;
		}
		}
		return 0;
	}

	default:
		return DefWindowProcW(hwindow, message, wParam, lParam);
	}
}

int WINAPI wWinMain(_In_ HINSTANCE module, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {
	const int width = 800;
	const int height = 600;
	const wchar_t paintClassName[] = L"Paint Window";

	WNDCLASSEXW paintClass = { 0 };
	paintClass.cbSize = sizeof(WNDCLASSEXW);
	paintClass.lpfnWndProc = PaintProc;
	paintClass.hInstance = module;
	paintClass.lpszClassName = paintClassName;

	if (!RegisterClassExW(&paintClass)) {
		MessageBoxW(NULL, L"Failed to register window class", L"Error", MB_ICONERROR);
		return EXIT_FAILURE;
	}

	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;
	RECT screenSize = { 0 };
	if (SystemParametersInfoW(SPI_GETWORKAREA, 0, &screenSize, 0)) {
		x = (screenSize.left + screenSize.right) / 2 - width / 2;
		y = (screenSize.top + screenSize.bottom) / 2 - height / 2;
	}

	HWND hwindow = CreateWindowExW(0, paintClassName, L"Рисовалка", WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, x, y, width, height, NULL, NULL, module, NULL);
	if (hwindow == NULL) {
		UnregisterClassW(paintClassName, module);
		MessageBoxW(NULL, L"Failed to create window", L"Error", MB_ICONERROR);
		return EXIT_FAILURE;
	}

	HDC hdc = GetDC(hwindow);
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, width, height);

	hmc = CreateCompatibleDC(hdc);
	HGDIOBJ hprevbitmap = SelectObject(hmc, hbitmap);

	RECT r = { 0, 0, width, height };
	FillRect(hmc, &r, GetSysColorBrush(COLOR_WINDOW));

	ShowWindow(hwindow, nCmdShow);

	HMENU menu = CreateMenu();
	HMENU menuFile = CreatePopupMenu();
	HMENU menuEdit = CreatePopupMenu();
	menuColor = CreatePopupMenu();
	menuThickness = CreatePopupMenu();
	HMENU menuExport = CreatePopupMenu();
	AppendMenuW(menu, MF_STRING | MF_POPUP, (UINT)menuFile, L"File");
	AppendMenuW(menu, MF_STRING | MF_POPUP, (UINT)menuEdit, L"Edit");

		//Меню файл
		AppendMenuW(menuFile, MF_STRING, CLEAR, L"Clear");
		AppendMenuW(menuFile, MF_SEPARATOR, 0, NULL);
		AppendMenuW(menuFile, MF_STRING | MF_POPUP, (UINT)menuExport, L"Export");
			AppendMenuW(menuExport, MF_STRING, EXPORT, L"Export");
			AppendMenuW(menuExport, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuExport, MF_STRING, EXPORTAS, L"Export as");

		//Меню редактирования
		AppendMenuW(menuEdit, MF_STRING | MF_POPUP, (UINT)menuColor, L"Color");
			AppendMenuW(menuColor, MF_STRING|MF_CHECKED, BLACK, L"Black");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, RED, L"Red");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, GREEN, L"Green");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, BLUE, L"Blue");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, WHITE, L"White");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, AQUA, L"Aqua");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, FUCHSIA, L"Fuchsia");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, GRAY, L"Gray");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, LIME, L"Lime");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, MAROON, L"Maroon");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, NAVY, L"Navy");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, OLIVE, L"Olive");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, PURPLE, L"Purple");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, SILVER, L"Silver");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, TEAL, L"Teal");
			AppendMenuW(menuColor, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuColor, MF_STRING, YELLOW, L"Yellow");
		AppendMenuW(menuEdit, MF_SEPARATOR, 0, NULL);
		AppendMenuW(menuEdit, MF_STRING | MF_POPUP, (UINT)menuThickness, L"Thickness");
			AppendMenuW(menuThickness, MF_STRING | MF_CHECKED, VERYSMALL, L"Very small");
			AppendMenuW(menuThickness, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuThickness, MF_STRING, SMALL, L"Small");
			AppendMenuW(menuThickness, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuThickness, MF_STRING , NORMAL, L"Normal");
			AppendMenuW(menuThickness, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuThickness, MF_STRING , LARGE, L"Large");
			AppendMenuW(menuThickness, MF_SEPARATOR, 0, NULL);
			AppendMenuW(menuThickness, MF_STRING, VERYLARGE, L"Very large");

	SetMenu(hwindow, menu);

	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	SelectObject(hprevbitmap, hprevbitmap);
	DeleteObject(hbitmap);
	DeleteObject(hmc);
	DeleteObject(hdc);
	DeleteObject(menu);
	DeleteObject(menuFile);
	DeleteObject(menuEdit);
	DeleteObject(menuColor);
	DeleteObject(menuThickness);
	DeleteObject(menuExport);

	return EXIT_SUCCESS;
}