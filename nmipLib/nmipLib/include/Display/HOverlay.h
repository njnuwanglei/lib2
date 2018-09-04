#pragma once
#include "..\nmipExport.h"

#include <vector>
using namespace std;
struct HDisplayObject_T
{
	HRegion reg;
	HXLD xld;
	COLORREF clr;
	int mode;
};
class NMIP_DLL_API CHOverlay
{
public:
	CHOverlay(void);
	~CHOverlay(void);

	void DrawRegion(HRegion hReg, COLORREF clr);
	void ClearOverlay();
	HDisplayObject_T* GetDisplayObject (int i);
	int GetDisplayObjectCount ();
private:
	vector<HDisplayObject_T> m_vecDispObj;
};

