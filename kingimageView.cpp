// kingimageView.cpp : implementation of the CKingimageView class
//

#include "stdafx.h"
#include "kingimage.h"
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "kingimageDoc.h"
#include "kingimageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKingimageView

IMPLEMENT_DYNCREATE(CKingimageView, CScrollView)

BEGIN_MESSAGE_MAP(CKingimageView, CScrollView)
	//{{AFX_MSG_MAP(CKingimageView)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PROCESS, OnProcess)
	ON_COMMAND(ID_any, Onany)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	/*ON_COMMAND(ID_PROCESS_DILATION, &CKingimageView::OnProcessDilation)
	ON_COMMAND(ID_PROCESS_EROSION, &CKingimageView::OnProcessErosion)
	ON_COMMAND(ID_PROCESS_BINARY, &CKingimageView::OnProcessBinary)
	ON_COMMAND(ID_PROCESS_SEGMENTATION, &CKingimageView::OnProcessSegmentation)*/
	ON_COMMAND(ID_PROCESS_TRAINLABEL32779, &CKingimageView::OnProcessTrainlabel32779)
	ON_COMMAND(ID_PROCESS_NN32780, &CKingimageView::OnProcessNn32780)
	ON_COMMAND(ID_PROCESS_KMEANS, &CKingimageView::OnProcessKmeans)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKingimageView construction/destruction

CKingimageView::CKingimageView()
{
	// TODO: add construction code here

}

CKingimageView::~CKingimageView()
{
}

BOOL CKingimageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView drawing

void CKingimageView::OnDraw(CDC* pDC)
{
	CKingimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	pDC->SetStretchBltMode(COLORONCOLOR);
//	int x,y,bytes;
	if (pDoc->imagetype==PCX)
		(pDoc->_pcx)->draw(pDC);
	if (pDoc->imagetype==BMP)
		(pDoc->_bmp)->draw(pDC);
	if (pDoc->imagetype==GIF)
		(pDoc->_gif)->draw(pDC);
	if (pDoc->imagetype==JPG)
		(pDoc->_jpg)->draw(pDC);
/*	if (pDoc->imagetype==BMP)
	{
	
	x=((KINGBMP*)(pDoc->_ppicture))->bmpinfo.bmiHeader.biWidth;
	y=((KINGBMP*)(pDoc->_ppicture))->bmpinfo.bmiHeader.biHeight;
	bytes=(pDoc->_ppicture)->needbyte;
	int place=0;
	for (int j=0;j<y;j++)
		for (int i=0;i<x;i++){
//			int color= (pDoc->_bmp)->point[place++] ;
			pDC->SetPixel(i,j,RGB( (pDoc->_picture)->pixel[place+2], (pDoc->_picture)->pixel[place+1] ,(pDoc->_picture)->pixel[place]));
			place+=3;
		}

  /*	if ( (pDoc->_bmp)->bitsperpixel!=24 ){
		CPalette *palette=new CPalette();
		LOGPALETTE palet;
		palet.palVersion=0x300;
		palet.palNumEntries=(pDoc->_bmp)->usedcolor;
		for (int i=0;i<palet.palNumEntries;i++){
			palet.palPalEntry[i].peRed=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbRed;
			palet.palPalEntry[i].peBlue=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbBlue;
			palet.palPalEntry[i].peGreen=( (pDoc->_bmp) -> bmpinfo) .bmiColors[i].rgbGreen;
			palet.palPalEntry[i].peFlags=0;//( (pDoc->_bmp) -> bmpinfo) .bmiColors[0].rgbRed;
		}
		BOOL re=palette->CreatePalette(&palet);
		CPalette *pp;
		pp=pDC->SelectPalette(palette,TRUE);
	}
*/
//	::SetDIBitsToDevice(pDC->m_hDC,0,0,x,y,0,0,0,y,(pDoc->_ppicture)->point,&(((KINGBMP*)(pDoc->_ppicture))->bmpinfo),DIB_RGB_COLORS);
	
//	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView printing

BOOL CKingimageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKingimageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKingimageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKingimageView diagnostics

#ifdef _DEBUG
void CKingimageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKingimageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CKingimageDoc* CKingimageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKingimageDoc)));
	return (CKingimageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKingimageView message handlers



void CKingimageView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize totalSize=CSize(::GetSystemMetrics(SM_CXSCREEN),
		                  ::GetSystemMetrics(SM_CYSCREEN));
	CSize pageSize=CSize(totalSize.cx/2,totalSize.cy/2);
	CSize lineSize=CSize(totalSize.cx/10,totalSize.cy/10);

	SetScrollSizes(MM_TEXT,totalSize,pageSize,lineSize);
}

void CKingimageView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CScrollView::OnMouseMove(nFlags, point);
}


//******************************************************
//  Image Processing Sample Program for CS555
//  Image origin: lower-left point
//  Image info:
//		int width;
//		int height;
//		int bitsperpixel;
//		int needbyte;
//		int usedcolor;
//		int usedbyte;
//		BYTE *pixel;	//maybe serval point in one BYTE
//		BYTE *point;
//
//  
//******************************************************
void CKingimageView::OnProcess()
{
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();


	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4-r)%4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3*iWidth) % 4;
		int p = (4-r)%4;
		Wp = 3*iWidth + p;
	}

	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
			pImg[i*Wp+j] = 255;
		}
	}
	else if(iBitPerPixel == 24)  ////True color 24bits image
	{
		for(int i=0; i<iHeight; i++)
		for(int j=0; j<iWidth; j++)
		{
			pImg[i*Wp+j*3]   = 0;      //B
			// pImg[i*Wp+j*3+1] = 0;      //G
			pImg[i*Wp+j*3+2] = 0;      //R 
		}
	}

	////redraw the screen
	OnDraw(GetDC());
}
// The function does basic image thresholding.
float findthres(int densityfreq[], float thrd)
{

	float rightsize = 0;
	float leftsize = 0;
	float leftmean = 0;
	float rightmean = 0;
	float rightsum = 0;
	float leftsum = 0;
	for (int i = 0; i < thrd;i++)
	{
		leftsize = leftsize + densityfreq[i];
	}
	for (int j = int(thrd + 1); j < 256;j++)
	{
		rightsize = rightsize + densityfreq[j];
	}
	for (int m = 0; m < thrd;m++)
	{
		leftsum = leftsum + m*densityfreq[m];
	}
	for (int n = int(thrd + 1); n < 256;n++)
	{
		rightsum = rightsum + n*densityfreq[n];
	}
	leftmean = leftsum / leftsize;
	rightmean = rightsum / rightsize;
	float newthrd = (leftmean + rightmean) / (2.00);
	if (abs(newthrd-thrd) < 1)
	{
		return newthrd;
	}
	else
	{
		return findthres(densityfreq, newthrd);
	}
}
//binary dilation(k must be odd)
void dilation(float *I, int m, int n, int *structure_element, int k)
{
	int dila[76800];
	for (int i = 0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			 dila[i*n + j] = I[i*n + j] ;
		}
	for (int i= 0;i< m;i++)
		for (int j =0;j < n;j++)
		{
			if (I[i*n + j] > 0)
			{
				for (int x=-(k-1)/2;x<=(k-1)/2;x++)
					for (int y = -(k - 1) / 2;y <= (k - 1) / 2;y++)
					{
						//dila[(i + x)*n + j + y] = 255;
						int temp = structure_element[(x + (k - 1) / 2)*k + y + (k - 1) / 2];
						if ( temp > 0)
						{
							if ((i + x) >= 0 && (i + x) < m && (j + y) >= 0 && (j + y) < n)
							{
								dila[(i + x)*n + j + y] = 255;

							}
						}
					}

			}
		}
	for (int i =0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			I[i*n + j] = dila[i*n + j];
		}
}
//binary erosion (k must be odd)
void erosion(float *I, int m, int n, int *structure_element, int k)
{
	int ero[76800];
	for (int i =0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			ero[i*n + j] = 0;
		}
	for (int i = 0;i< m;i++)
		for (int j = 0;j < n;j++)
		{
			int flag = 1;
			for (int x = -(k - 1) / 2;x <= (k - 1) / 2;x++)
				for (int y = -(k - 1) / 2;y <= (k - 1) / 2;y++)
				{
					int temp = structure_element[(x + (k - 1) / 2)*k + y + (k - 1) / 2];
					if (temp > 0)
					{
						if ((i + x) >= 0 && (i + x) < m && (j + y) >= 0 && (j + y) < n)
						{
							if (I[(i + x)*n + j + y] == 0)
								flag = 0;
						}
						else
						{
							flag = 0;
						}
					}
				}
			if (flag == 1)
				ero[i*n+j] = 255;
		}
	for (int i = 0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			I[i*n + j] = ero[i*n + j];
		}
}
//greylevel dilation
void grey_dilation(float *I, int m, int n, int *structure_element, int k)
{
	int dila[76800];
	for (int i = 0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			dila[i*n + j] = I[i*n + j];
		}
	for (int i = 0;i< m;i++)
		for (int j = 0;j < n;j++)
		{
			float max = 0;
			for (int x = -(k - 1) / 2;x <= (k - 1) / 2;x++)
				for (int y = -(k - 1) / 2;y <= (k - 1) / 2;y++)
				{
					if ((i + x) >= 0 && (i + x) < m && (j + y) >= 0 && (j + y) < n)
					{
						int temp = structure_element[(x + (k - 1) / 2)*k + y + (k - 1) / 2] + I[(i + x)*n + j + y];
						max = max > temp? max : temp;
					}
				}
			dila[i*n + j] = max > 256 ? 255 :max;
		}
	for (int i = 0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			I[i*n + j] = dila[i*n + j];
		}
}
//greylevel erosion
void grey_erosion(float *I, int m, int n, int *structure_element, int k)
{
	int ero[76800];
	for (int i = 0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			ero[i*n + j] = I[i*n + j];
		}
	for (int i = 0;i< m;i++)
		for (int j = 0;j < n;j++)
		{
			float min = 256;
			for (int x = -(k - 1) / 2;x <= (k - 1) / 2;x++)
				for (int y = -(k - 1) / 2;y <= (k - 1) / 2;y++)
				{
					if ((i + x) >= 0 && (i + x) < m && (j + y) >= 0 && (j + y) < n)
					{
						int temp = I[(i + x)*n + j + y]-structure_element[(x + (k - 1) / 2)*k + y + (k - 1) / 2] ;
						min = min < temp ? min : temp;
					}
				}
			ero[i*n + j] = min > 0 ? min : 0;
		}
	for (int i = 0;i<m;i++)
		for (int j = 0;j < n;j++)
		{
			I[i*n + j] = ero[i*n + j];
		}
}
void CKingimageView::Onany() 
{
	// TODO: Add your command handler code here
	
}







//void CKingimageView::OnProcessBinary()
//{
//	// TODO: Add your command handler code here
//	CKingimageDoc* pDoc = GetDocument();
//	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
//	int iWidth = pDoc->_bmp->width;
//	int iHeight = pDoc->_bmp->height;
//	BYTE *pImg = pDoc->_bmp->point;
//
//	int Wp = iWidth;
//	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
//	{
//		int r = iWidth % 4;
//		int p = (4 - r) % 4;
//		Wp = iWidth + p;
//	}
//	else if (iBitPerPixel == 24)	// RGB image
//	{
//		int r = (3 * iWidth) % 4;
//		int p = (4 - r) % 4;
//		Wp = 3 * iWidth + p;
//	}
//
//	if (iBitPerPixel == 24)  ////True color 24bits image
//	{
//		float *H = new float[iWidth*iHeight];
//		float *S = new float[iWidth*iHeight];
//		float *I = new float[iWidth*iHeight];
//
//		for (int i = 0; i<iHeight; i++)
//			for (int j = 0; j<iWidth; j++)
//			{
//
//				int b = pImg[i*Wp + j * 3];      //B
//				int g = pImg[i*Wp + j * 3 + 1];      //G
//				int r = pImg[i*Wp + j * 3 + 2];      //R 
//				I[i*iWidth + j] = (b + g + r) / 3;
//				S[i*iWidth + j] = 1 - 3 * min(b, min(g, b)) / (float)(b + g + r);
//				float theta = acos((double)(r - 0.5*g - 0.5*b) / (float)(pow((pow(r - g, 2) + (r - b)*(g - b)), 0.5)));
//				if (b <= g)
//				{
//					if (b != g || g != r)
//						H[i*iWidth + j] = theta;
//					else
//						H[i*iWidth + j] = -1;
//				}
//				else
//					H[i*iWidth + j] = 3.1415926 * 2 - theta;
//			}
//		//blur the image to remove noise
//		float *blur = new float[iWidth*iHeight];
//		//int laplacian[] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
//		int gaussian[] = { 2,4,5,4,2,4,9,12,9,4,5,12,15,12,5,4,9,12,9,4,2,4,5,4,2 };
//
//		for (int i = 2; i < iHeight - 2; i++)
//			for (int j = 2; j < iWidth - 2; j++)
//			{
//				blur[i*iWidth + j] = 0;
//				for (int x = 0;x<5;x++)
//					for (int y = 0;y < 5;y++)
//					{
//						blur[i*iWidth + j] = blur[i*iWidth + j] + float(I[(i + x - 2)*iWidth + (j + y - 2)] * gaussian[x * 5 + y] / 115.00);
//					}
//				blur[i*iWidth + j] = ((blur[i*iWidth + j] > 255) ? 255 : blur[i*iWidth + j]);
//				blur[i*iWidth + j] = ((blur[i*iWidth + j] <0) ? 0 : blur[i*iWidth + j]);
//			}
//		for (int i = 2; i < iHeight - 2; i++)
//			for (int j = 2; j < iWidth - 2; j++)
//			{
//				I[i*iWidth + j] = (int)blur[i*iWidth + j];
//			}
//
//		// Thresholding convert grey scale image to binary
//		// Construct density frequency
//		int intensityfreq[256] = { 0 };
//		for (int i = 0;i<iHeight;i++)
//			for (int j = 0;j < iWidth;j++)
//			{
//				intensityfreq[int(I[i*iWidth + j])] = intensityfreq[int(I[i*iWidth + j])] + 1;
//			}
//		int bn = 0;
//		for (int i = 0; i < 256;i++)
//		{
//			bn = bn + intensityfreq[i];
//		}
//		int thred = 127;
//		float threshold = findthres(intensityfreq, thred);
//
//		// binary picture
//		for (int x = 0; x < iHeight; x++)
//			for (int y = 0; y < iWidth; y++)
//			{
//				I[x*iWidth + y] = I[x*iWidth + y] > threshold ? 255 : 0;
//			}
//		//
//		//test for binary picture
//		for (int x = 0; x < iHeight; x++)
//			for (int y = 0; y < iWidth; y++)
//			{
//				pImg[x*Wp + y * 3] = I[x*iWidth + y];
//				pImg[x*Wp + y * 3 + 1] = I[x*iWidth + y];
//				pImg[x*Wp + y * 3 + 2] = I[x*iWidth + y];
//			}
//	}
//	OnDraw(GetDC());
//
//}


void CKingimageView::OnProcessDilation()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4 - r) % 4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3 * iWidth) % 4;
		int p = (4 - r) % 4;
		Wp = 3 * iWidth + p;
	}
	if (iBitPerPixel == 24)  ////True color 24bits image
	{
		float *H = new float[iWidth*iHeight];
		float *S = new float[iWidth*iHeight];
		float *I = new float[iWidth*iHeight];

		for (int i = 0; i<iHeight; i++)
			for (int j = 0; j<iWidth; j++)
			{

				int b = pImg[i*Wp + j * 3];      //B
				int g = pImg[i*Wp + j * 3 + 1];      //G
				int r = pImg[i*Wp + j * 3 + 2];      //R 
				I[i*iWidth + j] = (b + g + r) / 3;
				S[i*iWidth + j] = 1 - 3 * min(b, min(g, b)) / (float)(b + g + r);
				float theta = acos((double)(r - 0.5*g - 0.5*b) / (float)(pow((pow(r - g, 2) + (r - b)*(g - b)), 0.5)));
				if (b <= g)
				{
					if (b != g || g != r)
						H[i*iWidth + j] = theta;
					else
						H[i*iWidth + j] = -1;
				}
				else
					H[i*iWidth + j] = 3.1415926 * 2 - theta;
			}
		int k = 5;
		int SE[25];
		for (int i = 0;i < 25;i++)
			SE[i] = 25;
		grey_dilation(I, iHeight, iWidth, SE, k);
		for (int x = 0; x < iHeight; x++)
			for (int y = 0; y < iWidth; y++)
			{
				pImg[x*Wp + y * 3] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 1] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 2] = I[x*iWidth + y];
			}
	}
	OnDraw(GetDC());


}
float square(float x)
{
	return x*x;
}
//distance between data point and one cluster
float distance(int row_num, int col_num, float *cluster,float *I, int width)
{
	float distance = 0;
	for (int i=0;i<4;i++)
		for (int j = 0;j < 4;j++)
		{
			distance = distance + square(I[(239 - (row_num * 4 + i))*width + col_num * 4 + j] - cluster[i * 4 + j]);
		}
	return distance;
}



void CKingimageView::OnProcessTrainlabel32779()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	//First, convert RGB to Grey scale
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4 - r) % 4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3 * iWidth) % 4;
		int p = (4 - r) % 4;
		Wp = 3 * iWidth + p;
	}

	if (iBitPerPixel == 24)  ////True color 24bits image
	{
		float *H = new float[iWidth*iHeight];
		float *S = new float[iWidth*iHeight];
		float *I = new float[iWidth*iHeight];

		for (int i = 0; i<iHeight; i++)
			for (int j = 0; j<iWidth; j++)
			{

				int b = pImg[i*Wp + j * 3];      //B
				int g = pImg[i*Wp + j * 3 + 1];      //G
				int r = pImg[i*Wp + j * 3 + 2];      //R 
				I[i*iWidth + j] = (b + g + r) / 3;
				S[i*iWidth + j] = 1 - 3 * min(b, min(g, b)) / (float)(b + g + r);
				float theta = acos((double)(r - 0.5*g - 0.5*b) / (float)(pow((pow(r - g, 2) + (r - b)*(g - b)), 0.5)));
				if (b <= g)
				{
					if (b != g || g != r)
						H[i*iWidth + j] = theta;
					else
						H[i*iWidth + j] = -1;
				}
				else
					H[i*iWidth + j] = 3.1415926 * 2 - theta;
			}
		//initialize label vector
		int train_label[2400];
		for (int s = 0;s < 2400;s++)
		{
			int sum = 0;
			div_t output;
			output = div(s, 80);
			int row_num = output.quot;
			int col_num = output.rem;
			for (int i = 0;i<4;i++)
				for (int j = 0;j < 4;j++)
				{
					sum = sum + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
				}
			int ave = (int)(sum / 16);
			if (ave < 125)
				train_label[s] = 0;
			else
			{
				if (ave < 175)
					train_label[s] = 1;
				else
					train_label[s] = 2;
			}
			for (int i = 0;i<4;i++)
				for (int j = 0;j < 4;j++)
				{
					if (train_label[s] == 0)
						I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 0;
					if (train_label[s] == 1)
						I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 128;
					if (train_label[s] == 2)
						I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 255;
				}
		}
		for (int x = 0; x < iHeight; x++)
			for (int y = 0; y < iWidth; y++)
			{
				pImg[x*Wp + y * 3] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 1] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 2] = I[x*iWidth + y];
			}
	}


	////redraw the screen
	OnDraw(GetDC());
}


void CKingimageView::OnProcessNn32780()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4 - r) % 4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3 * iWidth) % 4;
		int p = (4 - r) % 4;
		Wp = 3 * iWidth + p;
	}
	if (iBitPerPixel == 24)  ////True color 24bits image
	{
		float *H = new float[iWidth*iHeight];
		float *S = new float[iWidth*iHeight];
		float *I = new float[iWidth*iHeight];

		for (int i = 0; i<iHeight; i++)
			for (int j = 0; j<iWidth; j++)
			{

				int b = pImg[i*Wp + j * 3];      //B
				int g = pImg[i*Wp + j * 3 + 1];      //G
				int r = pImg[i*Wp + j * 3 + 2];      //R 
				I[i*iWidth + j] = (b + g + r) / 3;
				S[i*iWidth + j] = 1 - 3 * min(b, min(g, b)) / (float)(b + g + r);
				float theta = acos((double)(r - 0.5*g - 0.5*b) / (float)(pow((pow(r - g, 2) + (r - b)*(g - b)), 0.5)));
				if (b <= g)
				{
					if (b != g || g != r)
						H[i*iWidth + j] = theta;
					else
						H[i*iWidth + j] = -1;
				}
				else
					H[i*iWidth + j] = 3.1415926 * 2 - theta;
			}
		int train_label[2400];
		for (int s = 0;s < 2400;s++)
		{
			int sum = 0;
			div_t output;
			output = div(s, 80);
			int row_num = output.quot;
			int col_num = output.rem;
			for (int i = 0;i<4;i++)
				for (int j = 0;j < 4;j++)
				{
					sum = sum + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
				}
			int ave = (int)(sum / 16);
			if (ave < 125)
				train_label[s] = 0;
			else
			{
				if (ave < 175)
					train_label[s] = 1;
				else
					train_label[s] = 2;
			}
		}
		int test_label[2400];
		int nearest_neighbor[2400];
//perform Nearest neighbor to obtain the labels for test data
		for (int s = 0;s<2400;s++)
		{
			// for sth test point, search through trainning point to look for nearest neighbor
			float min_dist = 100000000;
			div_t output;
			output = div(s + 2400, 80);
			int row_num = output.quot; //row_num for test point
			int col_num = output.rem;  //col_num for test point
			for (int t = 0; t<2400;t++)
			{
				float dist = 0;
				div_t output_train;
				output_train = div(t, 80);
				int row_num_train = output_train.quot;
				int col_num_train = output_train.rem;
				for (int i = 0;i<4;i++)
					for (int j = 0;j<4;j++)
					{
						dist = dist + (I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] - I[(239 - (row_num_train * 4 + i))*iWidth + col_num_train * 4 + j])*(I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] - I[(239 - (row_num_train * 4 + i))*iWidth + col_num_train * 4 + j]);
					}
				if (dist < min_dist)
				{
					min_dist = dist;
					test_label[s] = train_label[t];
					nearest_neighbor[s] = t;
				}
			}
		}
		// image N1 ,i.e. use class label as pixel grey values.
		//for (int s = 0;s < 2400;s++)
		//{
		//	div_t output;
		//	output = div(s + 2400, 80);
		//	int row_num = output.quot; //row_num for test point
		//	int col_num = output.rem;  //col_num for test point
		//	for (int i = 0;i<4;i++)
		//		for (int j = 0;j < 4;j++)
		//		{
		//			if (test_label[s] == 0)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 0;
		//			if (test_label[s] == 1)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 128;
		//			if (test_label[s] == 2)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 255;
		//		}
		//}
		//image N2, i.e. replace testing vector with trainning vector
		//for (int s = 0; s < 2400;s++)
		//{
		//	div_t output;
		//	output = div(s + 2400, 80);
		//	int row_num = output.quot; //row_num for test point
		//	int col_num = output.rem;  //col_num for test point
		//	int train_idx = nearest_neighbor[s];
		//	div_t output_train;
		//	output_train = div(train_idx, 80);
		//	int row_num_train = output_train.quot;
		//	int col_num_train = output_train.rem;
		//	for (int i = 0;i<4;i++)
		//		for (int j = 0;j < 4;j++)
		//		{
		//			I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = I[(239 - (row_num_train * 4 + i))*iWidth + col_num_train * 4 + j];
		//		}
		//	
		//}
		//image N3, i.e. replace testing vector with average of training vector
		//for (int s = 0; s < 2400;s++)
		//{
		//	div_t output;
		//	output = div(s + 2400, 80);
		//	int row_num = output.quot; //row_num for test point
		//	int col_num = output.rem;  //col_num for test point
		//	int train_idx = nearest_neighbor[s];
		//	div_t output_train;
		//	output_train = div(train_idx, 80);
		//	int row_num_train = output_train.quot;
		//	int col_num_train = output_train.rem;
		//	int sum = 0;
		//	for (int i = 0;i<4;i++)
		//		for (int j = 0;j < 4;j++)
		//		{
		//			sum = sum + I[(239 - (row_num_train * 4 + i))*iWidth + col_num_train * 4 + j];
		//		}
		//	for (int i = 0;i<4;i++)
		//		for (int j = 0;j < 4;j++)
		//		{
		//			I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = (int) sum/16.0;
		//		}

		//}
		//caculate average vector for each class using training data
		//int sum1[16];
		//int sum2[16];
		//int sum0[16];
		//int size0 = 0;
		//int size1 = 0;
		//int size2 = 0;
		//for (int i = 0;i<4;i++)
		//	for (int j = 0;j < 4;j++)
		//	{
		//		sum0[i * 4 + j] = 0;
		//		sum1[i * 4 + j] = 0;
		//		sum2[i * 4 + j] = 0;

		//	}
		//for (int s = 0; s < 2400;s++)
		//{
		//	div_t output;
		//	output = div(s, 80);
		//	int row_num = output.quot;
		//	int col_num = output.rem;
		//	if (train_label[s] == 0)
		//	{
		//		size0++;
		//		for (int i = 0;i<4;i++)
		//			for (int j = 0;j < 4;j++)
		//			{
		//				sum0[i * 4 + j] = sum0[4 * i + j] + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
		//			}
		//	}
		//	if (train_label[s] == 1)
		//	{
		//		size1++;
		//		for (int i = 0;i<4;i++)
		//			for (int j = 0;j < 4;j++)
		//			{
		//				sum1[i * 4 + j] = sum1[4 * i + j] + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
		//			}
		//	}
		//	if (train_label[s] == 2)
		//	{
		//		size2++;
		//		for (int i = 0;i<4;i++)
		//			for (int j = 0;j < 4;j++)
		//			{
		//				sum2[i * 4 + j] = sum2[4 * i + j] + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
		//			}
		//	}
		//}
		//for (int i = 0;i<4;i++)
		//	for (int j = 0;j < 4;j++)
		//	{
		//		sum0[i * 4 + j] = (int)sum0[i * 4 + j] / size0;
		//		sum1[i * 4 + j] = (int)sum1[i * 4 + j] / size1;
		//		sum2[i * 4 + j] = (int)sum2[i * 4 + j] / size2;

		//	}
		////image N4, i.e. replace testing vector with the average of the class
		//for (int s = 0;s < 2400;s++)
		//{
		//	div_t output;
		//	output = div(s + 2400, 80);
		//	int row_num = output.quot; //row_num for test point
		//	int col_num = output.rem;  //col_num for test point
		//	for (int i = 0;i<4;i++)
		//		for (int j = 0;j < 4;j++)
		//		{
		//			if (test_label[s] == 0)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = sum0[i * 4 + j];
		//			if (test_label[s] == 1)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = sum1[i * 4 + j];
		//			if (test_label[s] == 2)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = sum2[i * 4 + j];
		//		}
		//}
		//manually cluster testing data
		int test_label_manual[2400];
		for (int s = 0;s < 2400;s++)
		{
			int sum = 0;
			div_t output;
			output = div(s+2400, 80);
			int row_num = output.quot;
			int col_num = output.rem;
			for (int i = 0;i<4;i++)
				for (int j = 0;j < 4;j++)
				{
					sum = sum + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
				}
			int ave = (int)(sum / 16);
			if (ave < 125)
				test_label_manual[s] = 0;
			else
			{
				if (ave < 175)
					test_label_manual[s] = 1;
				else
					test_label_manual[s] = 2;
			}
		}
		//image T1
		//for (int s = 0;s < 2400;s++)
		//{
		//	div_t output;
		//	output = div(s + 2400, 80);
		//	int row_num = output.quot; //row_num for test point
		//	int col_num = output.rem;  //col_num for test point
		//	for (int i = 0;i<4;i++)
		//		for (int j = 0;j < 4;j++)
		//		{
		//			if (test_label_manual[s] == 0)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 0;
		//			if (test_label_manual[s] == 1)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 128;
		//			if (test_label_manual[s] == 2)
		//				I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 255;
		//		}
		//}
		//calculate error rate
		int error = 0;
		for (int s = 0;s < 2400;s++)
		{
			if (test_label[s] != test_label_manual[s])
				error++;
		}
		float error_rate = error / 2400.0;
		//display the image
		for (int x = 0; x < iHeight; x++)
			for (int y = 0; y < iWidth; y++)
			{
				pImg[x*Wp + y * 3] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 1] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 2] = I[x*iWidth + y];
			}
	}
	OnDraw(GetDC());

}


void CKingimageView::OnProcessKmeans()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CKingimageDoc* pDoc = GetDocument();
	int iBitPerPixel = pDoc->_bmp->bitsperpixel;
	int iWidth = pDoc->_bmp->width;
	int iHeight = pDoc->_bmp->height;
	BYTE *pImg = pDoc->_bmp->point;

	int Wp = iWidth;
	if (iBitPerPixel == 8)  ////Grey scale 8 bits image
	{
		int r = iWidth % 4;
		int p = (4 - r) % 4;
		Wp = iWidth + p;
	}
	else if (iBitPerPixel == 24)	// RGB image
	{
		int r = (3 * iWidth) % 4;
		int p = (4 - r) % 4;
		Wp = 3 * iWidth + p;
	}
	if (iBitPerPixel == 24)  ////True color 24bits image
	{
		float *H = new float[iWidth*iHeight];
		float *S = new float[iWidth*iHeight];
		float *I = new float[iWidth*iHeight];

		for (int i = 0; i < iHeight; i++)
			for (int j = 0; j < iWidth; j++)
			{

				int b = pImg[i*Wp + j * 3];      //B
				int g = pImg[i*Wp + j * 3 + 1];      //G
				int r = pImg[i*Wp + j * 3 + 2];      //R 
				I[i*iWidth + j] = (b + g + r) / 3;
				S[i*iWidth + j] = 1 - 3 * min(b, min(g, b)) / (float)(b + g + r);
				float theta = acos((double)(r - 0.5*g - 0.5*b) / (float)(pow((pow(r - g, 2) + (r - b)*(g - b)), 0.5)));
				if (b <= g)
				{
					if (b != g || g != r)
						H[i*iWidth + j] = theta;
					else
						H[i*iWidth + j] = -1;
				}
				else
					H[i*iWidth + j] = 3.1415926 * 2 - theta;
			}
		// perform k-means on training data when k =3
		int train_label[2400];
		float short_distance[2400];
		// first random select 3 pts as clusters
		int c1 = rand() % 2400;
		int c2 = rand() % 2400;
		int c3 = rand() % 2400;
		float cluster1[16];
		float cluster2[16];
		float cluster3[16];
		div_t output1;
		output1 = div(c1, 80);
		int row_num1 = output1.quot;
		int col_num1 = output1.rem;
		div_t output2;
		output2 = div(c2, 80);
		int row_num2 = output2.quot;
		int col_num2 = output2.rem;
		div_t output3;
		output3 = div(c3, 80);
		int row_num3 = output3.quot;
		int col_num3 = output3.rem;
		for (int i = 0;i < 4;i++)
			for (int j = 0;j < 4;j++)
			{
				cluster1[i * 4 + j] = I[(239 - (row_num1 * 4 + i))*iWidth + col_num1 * 4 + j];
				cluster2[i * 4 + j] = I[(239 - (row_num2 * 4 + i))*iWidth + col_num2 * 4 + j];
				cluster3[i * 4 + j] = I[(239 - (row_num3 * 4 + i))*iWidth + col_num3 * 4 + j];
			}
		int max_ite = 5000;
		for (int i = 0;i < max_ite;i++)
		{// step 1: assign class label to training data
			for (int s = 0;s < 2400;s++)
			{
				div_t output;
				output = div(s, 80);
				int row_num = output.quot;
				int col_num = output.rem;
				float d1 = distance(row_num, col_num, cluster1, I, iWidth);
				float d2 = distance(row_num, col_num, cluster2, I, iWidth);
				float d3 = distance(row_num, col_num, cluster3, I, iWidth);
				if (d1 < d2)
				{
					if (d1 < d3)
					{
						train_label[s] = 1;
						short_distance[s] = d1;
					}
					else
					{
						train_label[s] = 3;
						short_distance[s] = d3;
					}
				}
				else
				{
					if (d2 < d3)
					{
						train_label[s] = 2;
						short_distance[s] = d2;
					}
					else
					{
						train_label[s] = 3;
						short_distance[s] = d3;
					}
				}
			}
			//step 2: calculate new cluster.
			int size1 = 0;
			int size2 = 0;
			int size3 = 0;
			int sum1[16];
			int sum2[16];
			int sum3[16];
			for (int i = 0; i < 16; i++)
			{
				sum1[i] = 0;
				sum2[i] = 0;
				sum3[i] = 0;
			}
			for (int s = 0;s < 2400;s++)
			{
				div_t output;
				output = div(s, 80);
				int row_num = output.quot;
				int col_num = output.rem;
				if (train_label[s] == 1)
				{
					size1++;
					for (int i = 0;i < 4;i++)
						for (int j = 0;j < 4;j++)
						{
							sum1[4 * i + j] = sum1[4 * i + j] + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
						}
				}
				if (train_label[s] == 2)
				{
					size2++;
					for (int i = 0;i < 4;i++)
						for (int j = 0;j < 4;j++)
						{
							sum2[4 * i + j] = sum2[4 * i + j] + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
						}
				}
				if (train_label[s] == 3)
				{
					size3++;
					for (int i = 0;i < 4;i++)
						for (int j = 0;j < 4;j++)
						{
							sum3[4 * i + j] = sum3[4 * i + j] + I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j];
						}
				}
			}
			for (int i = 0;i < 16;i++)
			{
				cluster1[i] = sum1[i] / (float)size1;
				cluster2[i] = sum2[i] / (float)size2;
				cluster3[i] = sum3[i] / (float)size3;
			}
		}
		float sum1 = 0;
		float sum2 = 0;
		float sum3 = 0;
		for (int i = 0;i < 16;i++)
		{
			sum1 = cluster1[i] + sum1;
			sum2 = cluster2[i] + sum2;
			sum3 = cluster3[i] + sum3;
		}

		float ave1 = sum1 / 16.0;
		float ave2 = sum2 / 16.0;
		float ave3 = sum3 / 16.0;
		int lab[3];
		if (ave1 <= ave2 && ave2 <= ave3)
		{
			lab[0] = 1;
			lab[1] = 2;
			lab[2] = 3;
		}
		if (ave1 <= ave3 && ave3 <= ave2)
		{
			lab[0] = 1;
			lab[1] = 3;
			lab[2] = 2;
		}
		if (ave2 <= ave1 && ave1 <= ave3)
		{
			lab[0] = 2;
			lab[1] = 1;
			lab[2] = 3;
		}
		if (ave2 <= ave3 && ave3 <= ave1)
		{
			lab[0] = 2;
			lab[1] = 3;
			lab[2] = 1;
		}
		if (ave3 <= ave1 && ave1 <= ave2)
		{
			lab[0] = 3;
			lab[1] = 1;
			lab[2] = 2;
		}
		if (ave3 <= ave2 && ave2 <= ave1)
		{
			lab[0] = 3;
			lab[1] = 2;
			lab[2] = 1;
		}
		for (int s = 0;s < 2400;s++)
		{
			div_t output;
			output = div(s, 80);
			int row_num = output.quot;
			int col_num = output.rem;
			for (int i = 0;i<4;i++)
				for (int j = 0;j < 4;j++)
				{
					if (lab[train_label[s]-1] == 1)
						I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 255;
					if (lab[train_label[s] -1]== 2)
						I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 0;
					if (lab[train_label[s]-1] == 3)
						I[(239 - (row_num * 4 + i))*iWidth + col_num * 4 + j] = 128;
				}
		}
		for (int x = 0; x < iHeight; x++)
			for (int y = 0; y < iWidth; y++)
			{
				pImg[x*Wp + y * 3] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 1] = I[x*iWidth + y];
				pImg[x*Wp + y * 3 + 2] = I[x*iWidth + y];
			}
	}
	
	OnDraw(GetDC());

}
