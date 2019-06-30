#include <afxwin.h>

#include"CMapAI/CMapAI.h"
class CMyWnd :public CFrameWnd {

public:
	CMyWnd() {
		Create(NULL, "drawWindow");
		CClientDC dc(this);
		

	}
};

class CMyApp :public CWinApp {
	BOOL InitInstance();

};