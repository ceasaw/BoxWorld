#include "CMyWnd\CMyWnd.h"

//CMyApp app;

BOOL CMyApp::InitInstance() {
	CMyWnd *pf = new CMyWnd;
	pf->ShowWindow(m_nCmdShow);
	pf->UpdateWindow();
	this->m_pMainWnd = pf;
	return TRUE;
}
