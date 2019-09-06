
// EscapeRoomView.cpp : implementation of the CEscapeRoomView class
//

#include "pch.h"
#include "framework.h"
#include <math.h>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EscapeRoom.h"
#endif

#include "EscapeRoomDoc.h"
#include "EscapeRoomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEscapeRoomView

IMPLEMENT_DYNCREATE(CEscapeRoomView, CView)

BEGIN_MESSAGE_MAP(CEscapeRoomView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CEscapeRoomView construction/destruction

CEscapeRoomView::CEscapeRoomView() noexcept
{
	ormanOtvoren = false;
	vrataOtvorena = false;
	kljucPronadjen = false;
	prvaOtvorena = false;
	drugaOtvorena = false;
	drugiKljucPronadjen = false;
	treciKljucPronadjen = false;

}

CEscapeRoomView::~CEscapeRoomView()
{
}

BOOL CEscapeRoomView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEscapeRoomView drawing

void CEscapeRoomView::OnDraw(CDC* /*pDC*/)
{
	CEscapeRoomDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
	if (!pDoc)
		return;

	crtajZidove(pDC); //iscrta se cela pocetna slika

	if (ormanOtvoren) {//ako je kliknuto na orman
		CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
		CPen* oldPen = pDC->SelectObject(&pen);
		CBrush br(RGB(0, 0, 0));
		CBrush* oldBrush = pDC->SelectObject(&br);

		CRect tmp = CRect(57 * scalX, 167 * scalY, 106 * scalX, 560 * scalY);
		pDC->Rectangle(tmp);
		CBrush braon(RGB(114, 71, 29));
		pDC->SelectObject(braon);

		POINT pts[4];
		pts[0].x = levo.left * scalX; pts[0].y = levo.top * scalY;
		pts[1].x = (levo.left - 30) * scalX; pts[1].y = (levo.top - 20) * scalY;
		pts[2].x = (levo.left - 30) * scalX; pts[2].y = (levo.bottom + 20) * scalY;
		pts[3].x = levo.left * scalX; pts[3].y = levo.bottom * scalY;

		pDC->Polygon(pts, 4);
		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
		braon.DeleteObject();
		br.DeleteObject();
		pen.DeleteObject();

		if (!kljucPronadjen) {
			CRect rct((levo.left + 8) * scalX, (levo.bottom - 50) * scalY,
				(levo.left + 48) * scalX, (levo.bottom - 10) * scalY);

			/////iscrtavanje kljuca nakon otvorenog ormana
			CString m_name = CString("Key.emf"); //naziv datoteke
			HENHMETAFILE MF; //handle metafajla
			MF = GetEnhMetaFile(m_name); //ucitava se metafajl.emf
			PlayEnhMetaFile(pDC->m_hDC, MF, rct);
			//DeleteEnhMetaFile(MF); //ne brise se metafajl jer ce da se prebaci u inventar samo
		}
	}

	if (prvaOtvorena && !drugaOtvorena) {
		otvoriFioku(pDC, 57, 575, 155, 650); //prva fioka

		if (!drugiKljucPronadjen) {
			CRect r(65 * scalX, 580 * scalY, 105 * scalX, 615 * scalY);
			CString m_name = CString("Key.emf"); //naziv datoteke
			HENHMETAFILE MF; //handle metafajla
			MF = GetEnhMetaFile(m_name); //ucitava se metafajl.emf
			PlayEnhMetaFile(pDC->m_hDC, MF, r);
			DeleteEnhMetaFile(MF);
		}
	}

	if (drugaOtvorena) {
		otvoriFioku(pDC, 57, 660, 155, 740);//druga fioka
		if (!treciKljucPronadjen) {
			CRect r(65 * scalX, 665 * scalY, 105 * scalX, 705 * scalY);
			CString m_name = CString("Key.emf"); //naziv datoteke
			HENHMETAFILE MF; //handle metafajla
			MF = GetEnhMetaFile(m_name); //ucitava se metafajl.emf
			PlayEnhMetaFile(pDC->m_hDC, MF, r);
			DeleteEnhMetaFile(MF);
		}
	}

	if (kljucPronadjen) {

		CRect r(15 * scalX, 25 * scalY, 55 * scalX, 70 * scalY);
		CString m_name = CString("Key.emf"); //naziv datoteke
		HENHMETAFILE MF; //handle metafajla
		MF = GetEnhMetaFile(m_name); //ucitava se metafajl.emf
		PlayEnhMetaFile(pDC->m_hDC, MF, r);
		DeleteEnhMetaFile(MF);
	}// prva = (57, 575), (155, 650); druga = (57, 665), (155, 740)

	if (drugiKljucPronadjen) {
		CRect r(75 * scalX, 25 * scalY, 115 * scalX, 70 * scalY);
		CString m_name = CString("Key.emf"); //naziv datoteke
		HENHMETAFILE MF; //handle metafajla
		MF = GetEnhMetaFile(m_name); //ucitava se metafajl.emf
		PlayEnhMetaFile(pDC->m_hDC, MF, r);
		DeleteEnhMetaFile(MF);
	}

	if (treciKljucPronadjen) {
		CRect r(135 * scalX, 25 * scalY, 175 * scalX, 70 * scalY);
		CString m_name = CString("Key.emf"); //naziv datoteke
		HENHMETAFILE MF; //handle metafajla
		MF = GetEnhMetaFile(m_name); //ucitava se metafajl.emf
		PlayEnhMetaFile(pDC->m_hDC, MF, r);
		DeleteEnhMetaFile(MF);
	}

	if (vrataOtvorena) {//ako je kliknuto na vrata
		CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
		CPen* oldPen = pDC->SelectObject(&pen);
		CBrush br(RGB(0, 0, 0));
		CBrush* oldBrush = pDC->SelectObject(&br);


		POINT vrata[4];
		vrata[0].x = 730 * scalX; vrata[0].y = 730 * scalY;
		vrata[1].x = 730 * scalX; vrata[1].y = 145 * scalY;
		vrata[2].x = 790 * scalX; vrata[2].y = 130 * scalY;
		vrata[3].x = 790 * scalX; vrata[3].y = 790 * scalY;
		pDC->Polygon(vrata, 4);
		CBrush braon(RGB(114, 71, 29));
		pDC->SelectObject(braon);

		POINT novaVrata[4];
		novaVrata[0].x = 730 * scalX; novaVrata[0].y = 730 * scalY;
		novaVrata[1].x = 730 * scalX; novaVrata[1].y = 145 * scalY;
		novaVrata[2].x = 620 * scalX; novaVrata[2].y = 145 * scalY;
		novaVrata[3].x = 620 * scalX; novaVrata[3].y = 730 * scalY;
		pDC->Polygon(novaVrata, 4);


		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
		braon.DeleteObject();
		br.DeleteObject();
		pen.DeleteObject();
	}

}

void CEscapeRoomView::crtajZidove(CDC* pDc) {

	pDc = GetDC();
	CRect rect;
	GetClientRect(&rect);
	scalX = (float)rect.Width() / (float)800;
	scalY = (float)rect.Height() / (float)800;

	CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
	CPen* oldPen = pDc->SelectObject(&pen);
	CBrush brush(RGB(255, 192, 128));
	CBrush* br = pDc->SelectObject(&brush);

	pDc->SetMapMode(MM_ANISOTROPIC);
	pDc->SetWindowExt(800, 800);
	pDc->SetViewportExt(rect.right, rect.bottom);

	CRect rect1(80, 80, 720, 720); //zadnji zid

	pDc->Rectangle(rect1);
	pDc->SelectObject(oldPen);
	pDc->SelectObject(br);


	brush.DeleteObject();
	pen.DeleteObject();

	LeviDesniZidovi_POD(pDc, rect1);

	crtajVrata(pDc, rect1);
	crtajProzor(pDc, rect1);
	crtajOrman(pDc, rect1);
	crtajInventar(pDc);
	crtajSat(pDc, rect1);
}

void CEscapeRoomView::LeviDesniZidovi_POD(CDC* pDC, CRect tmp) {

	CRect rect;
	GetClientRect(&rect);

	CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(198, 140, 83));
	CBrush* br = pDC->SelectObject(&brush); //ista boja za levi i desni zid

	POINT levi[4];
	levi[0].x = rect.left; levi[0].y = rect.top;
	levi[1].x = rect.left; levi[1].y = 800;
	levi[2].x = tmp.left; levi[2].y = tmp.bottom;
	levi[3].x = tmp.left; levi[3].y = tmp.top;

	POINT desni[4];
	desni[0].x = tmp.right; desni[0].y = tmp.top;
	desni[1].x = 800; desni[1].y = rect.top;
	desni[2].x = 800; desni[2].y = 800;
	desni[3].x = tmp.right; desni[3].y = tmp.bottom;

	pDC->Polygon(desni, 4);
	pDC->Polygon(levi, 4);

	CBrush brush1(RGB(183, 210, 227));
	pDC->SelectObject(&brush1);

	POINT pod[4];
	pod[0].x = tmp.left; pod[0].y = tmp.bottom;
	pod[1].x = tmp.right; pod[1].y = tmp.bottom;
	pod[2].x = 800; pod[2].y = 800;
	pod[3].x = rect.left; pod[3].y = 800;

	pDC->Polygon(pod, 4);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(br); //mora br, jer br sadrzi default vrednost cetke, a ne oldbr

	pen.DeleteObject();
	brush1.DeleteObject();
	brush.DeleteObject();
}

void CEscapeRoomView::crtajVrata(CDC* pDC, CRect tmp) {

	CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);//u oldPen upisuje zadnju koriscenu olovku
	CBrush brush(RGB(101, 67, 33));
	CBrush* oldBrush = pDC->SelectObject(&brush); //u oldBrush upisuje zadnju koriscenu cetku


	POINT vrata[4];
	vrata[0].x = tmp.right + 10; vrata[0].y = tmp.bottom + 10;
	vrata[1].x = tmp.right + 10; vrata[1].y = tmp.top + 65;
	vrata[2].x = 800 - 10; vrata[2].y = tmp.top + 50;
	vrata[3].x = 800 - 10; vrata[3].y = 800 - 10;

	COLORREF oldColor = pDC->SetBkColor(RGB(0, 0, 0));

	pDC->Polygon(vrata, 4);
	pDC->SetBkColor(oldColor);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();

	////////KVAKA
	CBrush brushNew(RGB(218, 152, 0));
	CBrush* oldB = pDC->SelectObject(&brushNew);
	pDC->Ellipse(775, 485, 785, 500);
	pDC->Ellipse(767, 480, 782, 505); //25
	pDC->SelectObject(oldB);
	brushNew.DeleteObject();

	/////////KLJUCAONICA
	CBrush brushNew1(RGB(102, 3, 0));
	CBrush* oldB1 = pDC->SelectObject(&brushNew1);
	pDC->Ellipse(775, 510, 785, 527);
	pDC->SelectObject(oldB1);
	brushNew1.DeleteObject();
	CBrush brushNew2(RGB(0, 0, 0));
	CBrush* oldB2 = pDC->SelectObject(&brushNew2);
	pDC->Ellipse(778, 511, 782, 525);
	pDC->SelectObject(oldB2);
	brushNew2.DeleteObject();
}

void CEscapeRoomView::crtajProzor(CDC* pDC, CRect tmp) {


	CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(114, 71, 29));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//veliki prozor
	CRect prozor(tmp.left + 220, tmp.top + 70, tmp.right - 190, tmp.bottom - 200);
	pDC->Rectangle(prozor);

	////unutrasnji prozori, tj. stakla
	CBrush plava(RGB(85, 165, 210));
	pDC->SelectObject(&plava);
	int sredina = ((prozor.left + prozor.right) / 2) - 4;
	CRect levi(prozor.left + 8, prozor.top + 15, sredina, prozor.bottom - 15);
	CRect desni(sredina + 8, prozor.top + 15, prozor.right - 8, prozor.bottom - 15);
	pDC->Rectangle(levi);
	pDC->Rectangle(desni);

	/////GARNISNA
	pDC->SelectObject(&brush); //ista boja za garnislu treba
	pDC->RoundRect(tmp.left + 205, tmp.top + 30, tmp.right - 175, tmp.top + 65, 30, 30);

	//////ZAVESA
	CBrush zavesa(RGB(255, 255, 153));
	pDC->SelectObject(&zavesa);

	POINT tacke[3];
	tacke[0].x = tmp.right - 240; tacke[0].y = tmp.bottom - 200;
	tacke[1].x = tmp.left + 250; tacke[1].y = tmp.bottom - 300;
	tacke[2].x = tmp.left + 215; tacke[2].y = tmp.bottom - 250;

	pDC->BeginPath();
	pDC->MoveTo(tmp.left + 215, tmp.top + 65);
	pDC->LineTo(tmp.right - 185, tmp.top + 65);
	pDC->LineTo(tmp.right - 185, tmp.bottom - 250);
	pDC->PolyBezierTo(tacke, 3);
	pDC->LineTo(tmp.left + 215, tmp.top + 65);
	pDC->EndPath();
	pDC->StrokeAndFillPath();


	pDC->SelectObject(oldBrush); //vracanje na staru cetku
	pDC->SelectObject(oldPen); //vracanje na staru olovku
	brush.DeleteObject();
	plava.DeleteObject();
	zavesa.DeleteObject();
}

void CEscapeRoomView::crtajOrman(CDC* pDC, CRect tmp) {

	CPen pen(BS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(114, 71, 29));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	CRect prednji(tmp.left - 28, tmp.top + 80, tmp.left + 80, tmp.bottom + 30);

	POINT pts[4];
	pts[0].x = prednji.right; pts[0].y = prednji.top;
	pts[1].x = prednji.right + 60; pts[1].y = prednji.top + 15;
	pts[2].x = prednji.right + 60; pts[2].y = prednji.bottom - 30;
	pts[3].x = prednji.right; pts[3].y = prednji.bottom;

	pDC->Rectangle(prednji);
	pDC->Polygon(pts, 4);

	//levo i desno krilo
	int sredina = (prednji.left + prednji.right) / 2;
	levo = new CRect(prednji.left + 5, prednji.top + 7, sredina, prednji.top + 400);
	CRect desno(sredina, prednji.top + 7, prednji.right - 5, prednji.top + 400);
	pDC->Rectangle(levo);
	pDC->Rectangle(desno);

	///fioke, // (57, 665) (155, 740)
	CRect fioka1(levo.left, levo.bottom + 15, desno.right, desno.bottom + 90);
	pDC->Rectangle(fioka1);
	CRect fioka2(fioka1.left, fioka1.bottom + 15, fioka1.right, fioka1.bottom + 90);
	pDC->Rectangle(fioka2);

	////rucice
	CBrush rucice(RGB(218, 152, 0));
	pDC->SelectObject(rucice);
	int mid = (levo.top + levo.bottom) / 2;
	pDC->Ellipse(sredina - 12, mid, sredina - 5, mid + 15);
	pDC->Ellipse(sredina + 12, mid, sredina + 5, mid + 15);
	pDC->Ellipse(sredina - 4, levo.bottom + 45, sredina + 4, levo.bottom + 60);
	pDC->Ellipse(sredina - 4, prednji.bottom - 55, sredina + 4, prednji.bottom - 40);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	rucice.DeleteObject();
	pen.DeleteObject();
}

void CEscapeRoomView::crtajInventar(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(204, 204, 255));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	//prviKljuc
	pDC->RoundRect(rect.left + 10, rect.top + 10, rect.left + 60,
		rect.top + 90, 10, 10);

	//drugiKljuc
	pDC->RoundRect(rect.left + 70, rect.top + 10, rect.left + 120,
		rect.top + 90, 10, 10);

	//treciKljuc
	pDC->RoundRect(rect.left + 130, rect.top + 10, rect.left + 180,
		rect.top + 90, 10, 10);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CEscapeRoomView::crtajSat(CDC* pDC, CRect tmp) {

	CPen blackPen(BS_SOLID, 3, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&blackPen);
	CBrush brownBrush(RGB(101, 67, 33));
	CBrush* oldBrush = pDC->SelectObject(&brownBrush);

	CPoint kr;
	kr.x = 35; kr.y = 35;

	CRect vecaKutija(tmp.right - 127, tmp.top + 130, tmp.right - 53, tmp.top + 405);
	pDC->RoundRect(vecaKutija, kr);

	CBrush blackBrush(RGB(0, 0, 0));
	pDC->SelectObject(&blackBrush);
	CRect kutija(tmp.right - 120, tmp.top + 140, tmp.right - 61, tmp.top + 397);
	pDC->RoundRect(kutija, kr);

	pDC->SelectObject(&brownBrush);
	//560, 110, 700, 250 //veliki krug
	pDC->Ellipse(tmp.right - 160, tmp.top + 30, tmp.right - 20, tmp.top + 170);

	CBrush yellowBrush(RGB(255, 204, 0));
	pDC->SelectObject(&yellowBrush);
	//565, 115, 695, 245 //srednji 
	pDC->Ellipse(tmp.right - 155, tmp.top + 35, tmp.right - 25, tmp.top + 165);

	//590, 140, 670, 220 // manji
	pDC->SelectObject(oldBrush);
	pDC->Ellipse(tmp.right - 130, tmp.top + 60, tmp.right - 50, tmp.top + 140);




	//////////PODEOCI//////////
	CPen penTanjiPodeok(BS_SOLID, 0, RGB(0, 0, 0));
	pDC->SelectObject(penTanjiPodeok);
	CPen penDebljiPodeok(BS_SOLID, 2, RGB(0, 0, 0));

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM xFormOld; //default forma koja ce se setovati PO ZAVRSETKU SVAKOG POZIVA f-je primeniTransformaciju
	 //-40 da bi sredina duzi bila tacno 
	//u pocetak kruga u kom se crtaju podeoci;
	double ugao = 0;
	for (int i = 0; i < 30; i++) {
		if (i % 5 == 0) {
			pDC->SelectObject(penDebljiPodeok);
		}
		else {
			pDC->SelectObject(penTanjiPodeok);
		}
		primeniTransformaciju(pDC, 630, 180, 0, -40, ugao, &xFormOld);
		pDC->MoveTo(0, 0);
		pDC->LineTo(0, 80);
		SetWorldTransform(pDC->m_hDC, &xFormOld);
		ugao += PI / 30;
	}//590, 140, 670, 220 //najmanji krug
	pDC->SelectObject(penTanjiPodeok);
	pDC->Ellipse(tmp.right - 123, tmp.top + 67, tmp.right - 57, tmp.top + 133);
	//////////////////////////


	////////////BROJEVI
	CString broj;
	float alfa = 0;
	////XII
	primeniTransformaciju(pDC, 600, 140, 0, -40, alfa, &xFormOld);
	broj = "XII";
	pisiBroj(pDC, broj, 20, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	//////////////////
	//// I
	alfa += PI / 6;
	primeniTransformaciju(pDC, 625, 130, 0, -40, alfa, &xFormOld);
	broj = "I";
	pisiBroj(pDC, broj, 26, 18);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	//////////
	/// II
	alfa += PI / 6;
	primeniTransformaciju(pDC, 650, 135, 0, -40, alfa, &xFormOld);
	broj = "II";
	pisiBroj(pDC, broj, 22, 18);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	////
	///III
	alfa += PI / 6;
	primeniTransformaciju(pDC, 670, 150, 0, -40, alfa, &xFormOld);
	broj = "III";
	pisiBroj(pDC, broj, 22, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	///
	///IV
	alfa += PI / 6;
	primeniTransformaciju(pDC, 678, 175, 0, -40, alfa, &xFormOld);
	broj = "IV";
	pisiBroj(pDC, broj, 22, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	///
	/////V
	alfa += PI / 6;
	primeniTransformaciju(pDC, 672, 200, 0, -40, alfa, &xFormOld);
	broj = "V";
	pisiBroj(pDC, broj, 22, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	///
	///VI
	alfa += PI / 6;
	primeniTransformaciju(pDC, 660, 218, 0, -40, alfa, &xFormOld);
	broj = "VI";
	pisiBroj(pDC, broj, 22, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	///VII
	alfa += PI / 6;
	primeniTransformaciju(pDC, 640, 230, 0, -40, alfa, &xFormOld);
	broj = "VII";
	pisiBroj(pDC, broj, 20, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	//////////
		///VIII
	alfa += PI / 6;
	primeniTransformaciju(pDC, 615, 230, 0, -40, alfa, &xFormOld);
	broj = "VIII";
	pisiBroj(pDC, broj, 18, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	//////////
	///////IX
	alfa += PI / 6;
	primeniTransformaciju(pDC, 590, 210, 0, -40, alfa, &xFormOld);
	broj = "IX";
	pisiBroj(pDC, broj, 20, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	//////
	////X
	alfa += PI / 6;
	primeniTransformaciju(pDC, 582, 182, 0, -40, alfa, &xFormOld);
	broj = "X";
	pisiBroj(pDC, broj, 22, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	/////
	////XI
	alfa += PI / 6;
	primeniTransformaciju(pDC, 585, 157, 0, -40, alfa, &xFormOld);
	broj = "XI";
	pisiBroj(pDC, broj, 20, 20);
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	//////


	primeniTransformaciju(pDC, 630, 180, 0, -40, ugaoManja, &xFormOld);
	CRect mala(-10, 0, 10, 60);
	CString m_name = CString("MalaKazaljka.emf"); //naziv datoteke
	HENHMETAFILE MF; //handle metafajla
	MF = GetEnhMetaFile(m_name); //ucitava se metafajl.emf
	PlayEnhMetaFile(pDC->m_hDC, MF, mala);
	DeleteEnhMetaFile(MF);
	SetWorldTransform(pDC->m_hDC, &xFormOld);

	primeniTransformaciju(pDC, 630, 180, 0, -45, ugaoVeca, &xFormOld);
	CRect velika(-5, 0, 5, 60);
	CString m_name1 = CString("VelikaKazaljka.emf"); //naziv datoteke
	HENHMETAFILE MF1; //handle metafajla
	MF1 = GetEnhMetaFile(m_name1); //ucitava se metafajl.emf
	PlayEnhMetaFile(pDC->m_hDC, MF1, velika);
	DeleteEnhMetaFile(MF1);
	SetWorldTransform(pDC->m_hDC, &xFormOld);

	//6.1959188

	if (brojac == 0)
		ugaoKlatno = 0;
	else if (brojac == 1)
		ugaoKlatno = 6.1959188;
	else if (brojac == 2)
		ugaoKlatno = 0;
	else if (brojac == 3)
		ugaoKlatno = 0.08975970;

	primeniTransformaciju(pDC, 628, 250, 0, 0, ugaoKlatno, &xFormOld);
	pDC->SelectObject(yellowBrush);
	pDC->RoundRect(-1, 0, 4, 170, 2, 2);
	pDC->Ellipse(-11, 170, 14, 210);

	SetWorldTransform(pDC->m_hDC, &xFormOld);
	SetGraphicsMode(pDC->m_hDC, prevMode);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	blackBrush.DeleteObject();
	blackPen.DeleteObject();
	brownBrush.DeleteObject();

}

void CEscapeRoomView::pisiBroj(CDC* pDC, CString broj, int x, int y) {

	CFont font;
	CString stil("Arial");
	font.CreateFont(15, 7, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, stil);
	CFont* oldFont = pDC->SelectObject(&font);
	CBrush lightYellowBrush(RGB(255, 230, 133));
	CBrush* oldBrush = pDC->SelectObject(&lightYellowBrush);

	pDC->BeginPath();
	pDC->Ellipse(18, 18, 40, 37);
	pDC->EndPath();
	pDC->FillPath();
	pDC->SetTextAlign(TA_LEFT);
	int oldtxt = pDC->SetTextColor(RGB(0, 0, 0));
	int prevBkMode = pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(x, y, broj);

	//vracanje na default
	pDC->SetBkMode(prevBkMode);
	pDC->SelectObject(&oldBrush);
	pDC->SetTextColor(oldtxt);
	pDC->SelectObject(&oldFont);
	font.DeleteObject();
	lightYellowBrush.DeleteObject();
}

void CEscapeRoomView::otvoriFioku(CDC* pDC, int left, int top, int right, int bottom) {

	CPen pen(BS_SOLID, 2, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush br(RGB(0, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&br);

	pDC->Rectangle(left * scalX, top * scalY, right * scalX, bottom * scalY); //zacrni trenutnu fioku
	CBrush braon(RGB(114, 71, 29));
	pDC->SelectObject(braon);

	POINT pomL[4];
	pomL[0].x = left * scalX; pomL[0].y = top * scalY;
	pomL[1].x = (left - 30) * scalX; pomL[1].y = (top + 40) * scalY;
	pomL[2].x = (left - 30) * scalX; pomL[2].y = (top + 120) * scalY;
	pomL[3].x = left * scalX; pomL[3].y = bottom * scalY;
	pDC->Polygon(pomL, 4);

	POINT pomR[4];
	pomR[0].x = right * scalX; pomR[0].y = top * scalY;
	pomR[1].x = (right - 30) * scalX; pomR[1].y = (top + 40) * scalY;
	pomR[2].x = (right - 30) * scalX; pomR[2].y = (top + 120) * scalY;
	pomR[3].x = right * scalX; pomR[3].y = bottom * scalY;
	pDC->Polygon(pomR, 4);

	// 57, 575, 155, 650 prva  // 57, 660, 155, 740 druga
	pDC->Rectangle((left - 30) * scalX, (top + 40) * scalY,
		(right - 30) * scalX, (top + 120) * scalY);

	CBrush rucice(RGB(218, 152, 0));
	pDC->SelectObject(rucice);
	int sredinaX = (((left - 30) * scalX) + ((right - 30) * scalX)) / 2;
	int midY = (((top + 40) * scalY) + ((top + 120) * scalY)) / 2;
	pDC->Ellipse(sredinaX - 7, midY - 7, sredinaX + 7, midY + 7);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	br.DeleteObject();
	braon.DeleteObject();
	rucice.DeleteObject();
}

void CEscapeRoomView::primeniTransformaciju(CDC* pDC, float cx, float cy, float rx, float ry, float alfa, XFORM* oldForm) {

	XFORM xForm;
	GetWorldTransform(pDC->m_hDC, oldForm);

	xForm.eM11 = 1.0;
	xForm.eM12 = 0.0;
	xForm.eM21 = 0.0;
	xForm.eM22 = 1.0;
	xForm.eDx = rx;
	xForm.eDy = ry;

	SetWorldTransform(pDC->m_hDC, &xForm); //prvo translacija za rx i ry

	xForm.eM11 = cos(alfa);
	xForm.eM12 = sin(alfa);
	xForm.eM21 = -sin(alfa);
	xForm.eM22 = cos(alfa);
	xForm.eDx = cx;
	xForm.eDy = cy;

	ModifyWorldTransform(pDC->m_hDC, &xForm, MWT_RIGHTMULTIPLY); //onda rotacija i translacija, moze u dve a moze i u jednu
}


// CEscapeRoomView printing

BOOL CEscapeRoomView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEscapeRoomView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEscapeRoomView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEscapeRoomView diagnostics

#ifdef _DEBUG
void CEscapeRoomView::AssertValid() const
{
	CView::AssertValid();
}

void CEscapeRoomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEscapeRoomDoc* CEscapeRoomView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEscapeRoomDoc)));
	return (CEscapeRoomDoc*)m_pDocument;
}
#endif //_DEBUG


// CEscapeRoomView message handlers

void CEscapeRoomView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	++brojac;
	if (nChar == 'M') {
		ugaoManja += PI / 6;
		brojac = brojac % 4; //zbog klatna, ima 4 stanja, sredina, desno, sredina, levo;
		Invalidate();
	}
	if (nChar == 'V') {
		ugaoVeca += PI / 30;
		brojac = brojac % 4;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CEscapeRoomView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//////////ORMAN
	CRgn otvoriOrman;
	otvoriOrman.CreateRectRgn(levo.left * scalX, levo.top * scalY,
		levo.right * scalX, levo.bottom * scalY); //cela leva vrata

	//otvoriOrman.CreateEllipticRgn(94*scalX, 101*scalY, 101*scalX, 388*scalY);//samo rucica
	if (otvoriOrman.PtInRegion(point)) {
		ormanOtvoren = true;
		Invalidate();
	}
	CRgn zatvoriOrman;
	POINT pts[4];
	pts[0].x = levo.left * scalX; pts[0].y = levo.top * scalY;
	pts[1].x = (levo.left - 30) * scalX; pts[1].y = (levo.top - 20) * scalY;
	pts[2].x = (levo.left - 30) * scalX; pts[2].y = (levo.bottom + 20) * scalY;
	pts[3].x = levo.left * scalX; pts[3].y = levo.bottom * scalY;
	zatvoriOrman.CreatePolygonRgn(pts, 4, ALTERNATE);
	if (zatvoriOrman.PtInRegion(point)) {
		ormanOtvoren = false;
		Invalidate();
	}
	CRgn kljuc;
	kljuc.CreateRectRgn((levo.left + 8) * scalX, (levo.bottom - 50) * scalY,
		(levo.left + 48) * scalX, (levo.bottom - 10) * scalY);
	if (kljuc.PtInRegion(point) && ormanOtvoren) {
		kljucPronadjen = true;
		Invalidate();
	}
	////////////////

	/////////////////PRVA FIOKA
	CRgn prvaFioka;
	prvaFioka.CreateEllipticRgn(102 * scalX, 605 * scalY, 110 * scalX, 625 * scalY);
	if (prvaFioka.PtInRegion(point) && kljucPronadjen) {
		prvaOtvorena = true;
		Invalidate();
	}
	CRgn drugiKljuc;	//+8, +5, -50, - 35
	drugiKljuc.CreateEllipticRgn(65 * scalX, 580 * scalY, 105 * scalX, 615 * scalY);
	if (drugiKljuc.PtInRegion(point) && prvaOtvorena) {
		drugiKljucPronadjen = true;
		Invalidate();
	}
	CRgn zatvoriPrvuFioku;
	zatvoriPrvuFioku.CreateRectRgn(27 * scalX, 615 * scalY, 125 * scalX, 690 * scalY);
	if (zatvoriPrvuFioku.PtInRegion(point)) {
		prvaOtvorena = false;
		Invalidate();
	}
	//////////////////////

	//////////////////DRUGA FIOKA
	CRgn drugaFioka;//+8, +5, -50, - 35
	drugaFioka.CreateEllipticRgn(102 * scalX, 695 * scalY, 110 * scalX, 710 * scalY);
	if (drugaFioka.PtInRegion(point) && drugiKljucPronadjen) {
		drugaOtvorena = true;
		prvaOtvorena = false;
		Invalidate();
	}

	CRgn treciKljuc;
	treciKljuc.CreateEllipticRgn(65 * scalX, 665 * scalY, 105 * scalX, 705 * scalY);
	if (treciKljuc.PtInRegion(point) && drugaOtvorena) {
		treciKljucPronadjen = true;
		Invalidate();
	}

	CRgn zatvoriTrecuFioku;
	zatvoriTrecuFioku.CreateRectRgn(27 * scalX, 740 * scalY, 125 * scalX, 780 * scalY);
	if (zatvoriTrecuFioku.PtInRegion(point)) {
		drugaOtvorena = false;
		Invalidate();
	}
	////////////////////

	//////////VRATA
	CRgn rgnVrata;
	rgnVrata.CreateEllipticRgn(767 * scalX, 480 * scalY, 782 * scalX, 505 * scalY);
	if (rgnVrata.PtInRegion(point) && treciKljucPronadjen) {
		vrataOtvorena = true;
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}
