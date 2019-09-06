
// EscapeRoomView.h : interface of the CEscapeRoomView class
//

#pragma once


class CEscapeRoomView : public CView
{
protected: // create from serialization only
	CEscapeRoomView() noexcept;
	DECLARE_DYNCREATE(CEscapeRoomView)

// Attributes
public:
	CEscapeRoomDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void crtajZidove(CDC* pDC);
	void LeviDesniZidovi_POD(CDC* pDC, CRect rect);
	void crtajVrata(CDC* pDC, CRect tmp);
	void crtajProzor(CDC* pDC, CRect tmp);
	void crtajOrman(CDC* pDC, CRect tmp);
	void crtajInventar(CDC* pDC);
	void crtajSat(CDC* pDC, CRect tmp);
	void pisiBroj(CDC* pDC, CString broj, int x, int y);
	void primeniTransformaciju(CDC* pDC, float cx, float cy, float rx, float ry, float alfa, XFORM* oldForm);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	void otvoriFioku(CDC* pDC, int levo, int gore, int desno, int dole);
	CRect levo;
	bool kljucPronadjen;
	bool ormanOtvoren;
	bool vrataOtvorena;
	bool prvaOtvorena;
	bool drugaOtvorena;
	bool drugiKljucPronadjen;
	bool treciKljucPronadjen;
	double scalX = 0;
	double scalY = 0;
	double PI = 3.141592653589;
	double ugaoManja = 0;
	double ugaoVeca = 0;
	double ugaoKlatno = 0;
	int brojac = 0;





// Implementation
public:
	virtual ~CEscapeRoomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in EscapeRoomView.cpp
inline CEscapeRoomDoc* CEscapeRoomView::GetDocument() const
   { return reinterpret_cast<CEscapeRoomDoc*>(m_pDocument); }
#endif

