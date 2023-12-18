
// imageProc_20190848Doc.cpp: CimageProc20190848Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imageProc_20190848.h"
#endif

#include "imageProc_20190848Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <algorithm>
#include "CAngleInputDialog.h"
#define PI 3.14159
#define NUM_FRAMES 10

// CimageProc20190848Doc

IMPLEMENT_DYNCREATE(CimageProc20190848Doc, CDocument)

BEGIN_MESSAGE_MAP(CimageProc20190848Doc, CDocument)
END_MESSAGE_MAP()


// CimageProc20190848Doc 생성/소멸

CimageProc20190848Doc::CimageProc20190848Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	inputImage = NULL;
	inputImage2 = NULL;
	resultImage = NULL;
	gResultImg = NULL;
	for (int i = 0; i < NUM_FRAMES; i++) morphedImg[i] = NULL;
}

CimageProc20190848Doc::~CimageProc20190848Doc()
{
	int i;
	if (inputImage != NULL) {
		for (i = 0; i < imageHeight; i++) 
			free(inputImage[i]);
		free(inputImage);
	}
	if (inputImage2 != NULL) {
		for (i = 0; i < imageHeight; i++) 
			free(inputImage2[i]);
		free(inputImage2);
	}
	if (resultImage != NULL) {
		for (i = 0; i < imageHeight; i++) 
			free(resultImage[i]);
		free(resultImage);
	}
	if (gResultImg != NULL) {
		for (i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}

	for (i = 0; i < NUM_FRAMES; i++) {
		if (morphedImg[i] != NULL) {
			int  j;
		    	for (j = 0; j < imageHeight; j++)
					free(morphedImg[i][j]);
				free(morphedImg[i]);
			
		}
	}
}

BOOL CimageProc20190848Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CimageProc20190848Doc serialization

void CimageProc20190848Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CimageProc20190848Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CimageProc20190848Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CimageProc20190848Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CimageProc20190848Doc 진단

#ifdef _DEBUG
void CimageProc20190848Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CimageProc20190848Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CimageProc20190848Doc 명령


void CimageProc20190848Doc::pixelAdd()
{  
	int value = 0;
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth*depth; x++) {
			 
				value = inputImage[y][x] + 100;
				if (value > 255) resultImage[y][x] = 255;
				else resultImage[y][x] = value;
			
			
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CimageProc20190848Doc::pixelSub()
{
	// TODO: 여기에 구현 코드 추가.
	int value = 0;
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth*depth; x++) {
			value = inputImage[y][x] - 100;
			if (value > 255) resultImage[y][x] = 255;
			else if (value < 0)resultImage[y][x] = 0;
			else resultImage[y][x] = value;
		}
	}
}


void CimageProc20190848Doc::pixelMul()
{
	// TODO: 여기에 구현 코드 추가.
	int value = 0;
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth*depth; x++) {
			value = inputImage[y][x] * 2;
			if (value > 255) resultImage[y][x] = 255;
			else resultImage[y][x] = value;
		}
	}
}


void CimageProc20190848Doc::pixelDiv()
{
	// TODO: 여기에 구현 코드 추가.
	int value = 0;
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth*depth; x++) {
			value = inputImage[y][x] / 2;
			if (value > 255) resultImage[y][x] = 255;
			else resultImage[y][x] = value;
		}
	}

	 

}

//히스토그램 평활화 코드
void CimageProc20190848Doc::pixelHistoEq()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, i, k;
	int acc_hist = 0;
	float N = (float)(imageHeight * imageWidth * depth);
	int hist[256], sum[256];

	for (k = 0; k < 256; k++)hist[k] = 0;
    //명암값의 빈도수 조사
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth * depth; x++) {
			k = inputImage[y][x];
			hist[k]++;
		}
	}
	//누적분포
	hist[k] = 0;
	for (i = 0; i < 256; i++) {
		acc_hist +=  hist[i];
		sum[i] = acc_hist;
	}
	//픽셀 밝기변환
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth * depth; x++) {
			k = inputImage[y][x];
			resultImage[y][x] = (unsigned char)(sum[k] / N * 255);
		}
	}
}


//명암대비 스트레칭 코드
void CimageProc20190848Doc::pixelStretch()
{
	int max,min;
	int x, y;
	min = inputImage[0][0];
	max = inputImage[0][0];
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth * depth; x++) {
				if (max < inputImage[y][x])max = inputImage[y][x];
				if (min > inputImage[y][x])min = inputImage[y][x];
		}
	}
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth*depth; x++) {
			resultImage[y][x] = (unsigned char)(inputImage[y][x] - min)*255 / (max - min);
		}
	}


	
}

//이진법 코드
void CimageProc20190848Doc::pixelBinaryzation()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	int threshold = 120;
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth*depth; x++) {
			if (inputImage[y][x] > threshold) {
				resultImage[y][x] = 255;
			}
			else {
				resultImage[y][x] = 0;
			}


		}
	}
}

void CimageProc20190848Doc::pixelTwoImageAdd()
{
	// TODO: 여기에 구현 코드 추가.
	int value;
	LoadTwoImages();
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth*depth; x++) {
			value = 0.7*inputImage[y][x] + 0.3*inputImage2[y][x];
			if (value > 255) resultImage[y][x] = 255;
			else resultImage[y][x] = value;
		}
	}
}


void CimageProc20190848Doc::LoadTwoImages()
{
	// TODO: 여기에 구현 코드 추가.
	CFile file;
	CFileDialog dlg(TRUE);

	AfxMessageBox("Select the First Image");

	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadImageFile(ar);
		file.Close();
	}
	AfxMessageBox("Select the Second Image");
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadSecondImageFile(ar);
		file.Close();
	}

}


void CimageProc20190848Doc::pixelTwoImageSub()
{
	// TODO: 여기에 구현 코드 추가.
	int value;
	LoadTwoImages();
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth*depth; x++) {
			value = abs(inputImage[y][x] - inputImage2[y][x]);
			if (value > 64) value = 255;
			else if(value<64) value = 0;

			resultImage[y][x] = value;
		}
	}
}


void CimageProc20190848Doc::LoadImageFile(CArchive& ar)
{
	// TODO: 여기에 구현 코드 추가.
	int i, maxValue;
	char type[16], buf[256];
	bool isbmp= false;
	CFile * fp = ar.GetFile();
	CString fname = fp -> GetFilePath();
	if (strcmp(strchr(fname, '.'), ".ppm") == 0 ||
		strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 ||
		strcmp(strchr(fname, '.'), ".PGM") == 0) {
		
		ar.ReadString(type, 15); //P5
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);

		do { ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)depth = 1;
		else depth=3;

	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh,sizeof(bmfh));

		//BMP화일임을 나타내는 "BM"마커가 있는지 확인한다
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))return;
		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		imageWidth = bih.biWidth;
		imageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		if (depth == 1) {
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;

	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 ||
		       strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256*256 크기의 파일만 가능합니다");
			return;
		}

		imageHeight = 256;
		imageWidth = 256;
		depth = 1;
	}
	
	inputImage = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImage = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));

	for (i = 0; i < imageHeight; i++) {
		inputImage[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImage[i] = (unsigned char*)malloc(imageWidth * depth);
		
	}
	//inputImage[y][x]처럼 사용됨

	//파일 읽어서 저장
	if (!isbmp) {
		for (i = 0; i < imageHeight; i++) ar.Read(inputImage[i], imageWidth * depth);
	}
	else {
		BYTE nu[4];
		int widthfile;
		widthfile = (imageWidth * 8 + 31) / 32 * 4;
		for (i = 0; i < imageHeight; i++) {
			if (depth == 1)  ar.Read(inputImage[imageHeight - 1 - i], imageWidth * depth);
			else {
				for (int j = 0; j < imageWidth; j++) {
					BYTE r, g, b;
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);

					inputImage[imageHeight - 1 - i][3 * j + 0] = r;
					inputImage[imageHeight - 1 - i][3 * j + 1] = g;
					inputImage[imageHeight - 1 - i][3 * j + 2] = b;
				}
			}
			if ((widthfile - imageWidth) != 0)ar.Read(nu, (widthfile - imageWidth) * depth);
		}
	}
}


void CimageProc20190848Doc::LoadSecondImageFile(CArchive& ar)
{
	// TODO: 여기에 구현 코드 추가.
	int i, maxValue;
	int temp_w, temp_h, temp_depth;
	int w, h, d;
	bool isbmp = false;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	if (strcmp(strchr(fname, '.'), ".ppm") == 0 ||
		strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 ||
		strcmp(strchr(fname, '.'), ".PGM") == 0) {

		ar.ReadString(type, 15); //P5
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &temp_w, &temp_h);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)temp_depth = 1;
		else temp_depth = 3;

	}

	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//BMP화일임을 나타내는 "BM"마커가 있는지 확인한다
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))return;
		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		temp_w = bih.biWidth;
		temp_h = bih.biHeight;
		temp_depth = bih.biBitCount / 8;

		if (depth == 1) {
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;

	}

	else if (strcmp(strchr(fname, '.'), ".raw") == 0 ||
		strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256*256 크기의 파일만 가능합니다");
			return;
		}

		temp_w = 256;
		temp_h = 256;
		temp_depth = 1;
	}

	if (imageHeight != temp_h || imageWidth != temp_w || depth != temp_depth) {
		AfxMessageBox("두번째이미지크기 오류");
		return;

	}
	
	inputImage2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));

	for (i = 0; i < imageHeight; i++) {
		inputImage2[i] = (unsigned char*)malloc(imageWidth * depth);

	}
	//inputImage[y][x]처럼 사용됨

	//영상데이터읽기

	if (!isbmp) {
		for (i = 0; i < imageHeight; i++) ar.Read(inputImage2[i], imageWidth * depth);
	}
	else {
		BYTE nu[4];
		int widthfile;
		widthfile = (imageWidth * 8 + 31) / 32 * 4;
		for (i = 0; i < imageHeight; i++) {
			if (depth == 1)  ar.Read(inputImage2[imageHeight - 1 - i], imageWidth * depth);
			else {
				for (int j = 0; j < imageWidth; j++) {
					BYTE r, g, b;
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);

					inputImage2[imageHeight - 1 - i][3 * j + 0] = r;
					inputImage2[imageHeight - 1 - i][3 * j + 1] = g;
					inputImage2[imageHeight - 1 - i][3 * j + 2] = b;
				}
			}
			if ((widthfile - imageWidth) != 0)ar.Read(nu, (widthfile - imageWidth) * depth);
		}
	}
}


void CimageProc20190848Doc::Convolve(unsigned char** inImage, unsigned char** outImage, int cols, int rows,float mask[][3],int bias,int depth)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, x, y;//i,j는 마스크 위치
	int redSum, greenSum, blueSum;
	int sum;

	for (int y = 1; y < rows-1; y++) 
		for (int x = 1; x < cols - 1; x++) {
			if (depth == 1) {
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++) {
						sum += (inImage[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				outImage[y][x] = sum;
			}
			else {
				redSum = 0;
				greenSum = 0;
				blueSum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++) {
						redSum += (inImage[y + j - 1][3*(x + i )+0] * mask[j][i]);
						greenSum += (inImage[y + j - 1][3 * (x + i ) + 1] * mask[j][i]);
						blueSum += (inImage[y + j - 1][3 * (x + i ) + 2] * mask[j][i]);
					}
				redSum += bias;
				greenSum += bias;
				blueSum += bias;

				if (redSum > 255) redSum = 255;
				else if (redSum < 0) redSum = 0;
				if (greenSum > 255) greenSum = 255;
				else if (greenSum < 0) greenSum = 0;
				if (blueSum > 255) blueSum = 255;
				else if (blueSum < 0) blueSum = 0;

				outImage[y][3 * x + 0] = redSum;
				outImage[y][3 * x + 1] = greenSum;
				outImage[y][3 * x + 2] = blueSum;
			}
		}
}

void CimageProc20190848Doc::RegionSharpening(void)
{
	// TODO: 여기에 구현 코드 추가.
	float kernel[3][3] = { {0,-1,0},{-1,5,-1},{0,-1,0} };
	
	Convolve(inputImage, resultImage, imageWidth, imageHeight, kernel, 0, depth);

}

void CimageProc20190848Doc::RegionSmoothing()
{
	// TODO: 여기에 구현 코드 추가.

	float kernel[3][3] = { {1 / 9.0f,1 / 9.0f,1 / 9.0f},{1 / 9.0f,1 / 9.0f,1 / 9.0f},{1 / 9.0f,1 / 9.0f,1 / 9.0f} };

	Convolve(inputImage, resultImage, imageWidth, imageHeight, kernel, 0, depth);
}


void CimageProc20190848Doc::RegionEmbossing()
{
	// TODO: 여기에 구현 코드 추가.
	float kernel[3][3] = { {-1,0,0},{0,0,0},{0,0,1} };

	Convolve(inputImage, resultImage, imageWidth, imageHeight, kernel, 0, depth);
}


void CimageProc20190848Doc::RegionSobel()
{
	// TODO: 여기에 구현 코드 추가.
	int i, x, y, sum;
	float mask2[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	float mask1[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	int rsum, gsum, bsum;

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));

	for (i = 0; i < imageHeight; i++) {
		Er[i] = (unsigned char*)malloc(imageWidth * depth);
		Ec[i] = (unsigned char*)malloc(imageWidth * depth);
	}
	Convolve(inputImage, Er, imageWidth, imageHeight, mask1, 128, depth);
	Convolve(inputImage, Ec, imageWidth, imageHeight, mask2, 128, depth);
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				sum = sqrt(pow(Er[y][x] - 128, 2) + pow(Ec[y][x] - 128, 2));
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				resultImage[y][x] = sum;
			}
			else {
				rsum = sqrt(pow(Er[y][x * 3 + 0] - 128, 2) + pow(Ec[y][x * 3 + 0] - 128, 2));
				gsum = sqrt(pow(Er[y][x * 3 + 1] - 128, 2) + pow(Ec[y][x * 3 + 1] - 128, 2));
				bsum = sqrt(pow(Er[y][x * 3 + 2] - 128, 2) + pow(Ec[y][x * 3 + 2] - 128, 2));
				sum = sqrt(rsum * rsum + gsum * gsum + bsum + bsum);
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				resultImage[y][3 * x + 0] = sum;
				resultImage[y][3 * x + 1] = sum;
				resultImage[y][3 * x + 2] = sum;
			}
		}

	}
	for (i = 0; i < imageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);
}


void CimageProc20190848Doc::RegionPrewitt()
{
	// TODO: 여기에 구현 코드 추가.
	int i, x, y, sum;
	float mask1[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1} };
	float mask2[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1} };
	int rsum, gsum, bsum;

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));

	for (i = 0; i < imageHeight; i++) {
		Er[i] = (unsigned char*)malloc(imageWidth * depth);
		Ec[i] = (unsigned char*)malloc(imageWidth * depth);
	}
	Convolve(inputImage, Er, imageWidth, imageHeight, mask1, 128, depth);
	Convolve(inputImage, Ec, imageWidth, imageHeight, mask2, 128, depth);
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				sum = sqrt(pow(Er[y][x]-128, 2) + pow(Ec[y][x]-128, 2));
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				resultImage[y][x] = sum;
			}
			else {
				rsum = sqrt(pow(Er[y][x * 3 + 0]-128, 2) + pow(Ec[y][x * 3 + 0]-128, 2));
				gsum = sqrt(pow(Er[y][x * 3 + 1]-128, 2) + pow(Ec[y][x * 3 + 1]-128, 2));
				bsum = sqrt(pow(Er[y][x * 3 + 2]-128, 2) + pow(Ec[y][x * 3 + 2]-128, 2));
				sum = sqrt(rsum * rsum + gsum * gsum + bsum + bsum);
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				resultImage[y][3 * x + 0] = sum;
				resultImage[y][3 * x + 1] = sum;
				resultImage[y][3 * x + 2] = sum;
			}
		}

	}
	for (i = 0; i < imageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);
}


void CimageProc20190848Doc::RegionRoberts()
{
	// TODO: 여기에 구현 코드 추가.
	int i, x, y, sum;
	float mask1[3][3] = { {-1,0,0},{0,1,0},{0,0,0} };
	float mask2[3][3] = { {0,0,-1},{0,1,0},{0,0,0} };
	int rsum, gsum, bsum;

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc((imageHeight) * sizeof(unsigned char*));

	for (i = 0; i < imageHeight; i++) {
		Er[i] = (unsigned char*)malloc(imageWidth * depth);
		Ec[i] = (unsigned char*)malloc(imageWidth * depth);
	}
	Convolve(inputImage, Er, imageWidth, imageHeight, mask1, 128, depth);
	Convolve(inputImage, Ec, imageWidth, imageHeight, mask2, 128, depth);
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				sum = sqrt(pow(Er[y][x] - 128, 2) + pow(Ec[y][x] - 128, 2));
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				resultImage[y][x] = sum;
			}
			else {
				rsum = sqrt(pow(Er[y][x * 3 + 0] - 128, 2) + pow(Ec[y][x * 3 + 0] - 128, 2));
				gsum = sqrt(pow(Er[y][x * 3 + 1] - 128, 2) + pow(Ec[y][x * 3 + 1] - 128, 2));
				bsum = sqrt(pow(Er[y][x * 3 + 2] - 128, 2) + pow(Ec[y][x * 3 + 2] - 128, 2));
				sum = sqrt(rsum * rsum + gsum * gsum + bsum + bsum);
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				resultImage[y][3 * x + 0] = sum;
				resultImage[y][3 * x + 1] = sum;
				resultImage[y][3 * x + 2] = sum;
			}
		}

	}
	for (i = 0; i < imageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);
}


void CimageProc20190848Doc::RegionAverageFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	int sum,r,g,b;
	int pixel;
	for (y = 0; y < imageHeight; y++) {
		for (x = 0;x<imageWidth;x++){
			sum = 0;
			pixel = 0;
			r = 0, g = 0, b = 0;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (x + j >= 0 && x + j <= imageWidth - 1 && y + i >= 0 && y + i <= imageHeight - 1) {
						if (depth == 1)  sum += inputImage[y + i][x + j];

						else {
							r += inputImage[y + i][3 * (x + j) + 0];
							g += inputImage[y + i][3 * (x + j) + 1];
							b += inputImage[y + i][3 * (x + j) + 2];
						}
							pixel++;
						
					}
				}
			}
			if(depth==1) resultImage[y][x] = sum / pixel;
			else {
				resultImage[y][3*x+0] = r / pixel;
				resultImage[y][3*x+1] = g / pixel;
				resultImage[y][3*x+2] = b / pixel;
			}
		}
	}
}


void CimageProc20190848Doc::RegionMedian()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	int n[9];
	for (y = 1; y < imageHeight-1; y++){
		for (x = 1; x < imageWidth-1; x++) {
			if (depth == 1) {
				n[0] = inputImage[y - 1][x - 1];
				n[1] = inputImage[y - 1][x];
				n[2] = inputImage[y - 1][x + 1];
				n[3] = inputImage[y][x - 1];
				n[4] = inputImage[y][x];
				n[5] = inputImage[y][x + 1];
				n[6] = inputImage[y + 1][x - 1];
				n[7] = inputImage[y + 1][x];
				n[8] = inputImage[y + 1][x + 1];

				std::sort(n, n + 9);
				resultImage[y][x] = n[4];
				
			}
			else {
				n[0] = inputImage[y - 1][3*(x - 1)+0];
				n[1] = inputImage[y - 1][3 * x  + 0];
				n[2] = inputImage[y - 1][3 * (x + 1) + 0];
				n[3] = inputImage[y][3 * (x - 1) + 0];
				n[4] = inputImage[y][3 * x + 0];
				n[5] = inputImage[y][3 * (x + 1) + 0];
				n[6] = inputImage[y + 1][3 * (x - 1) + 0];
				n[7] = inputImage[y + 1][3 * x + 0];
				n[8] = inputImage[y + 1][3 * (x + 1) + 0];

				std::sort(n, n + 9);
				resultImage[y][3*x+0] = n[4];

				n[0] = inputImage[y - 1][3 * (x - 1) + 1];
				n[1] = inputImage[y - 1][3 * x + 1];
				n[2] = inputImage[y - 1][3 * (x + 1) + 1];
				n[3] = inputImage[y][3 * (x - 1) + 1];
				n[4] = inputImage[y][3 * x + 1];
				n[5] = inputImage[y][3 * (x + 1) + 1];
				n[6] = inputImage[y + 1][3 * (x - 1) + 1];
				n[7] = inputImage[y + 1][3 * x + 1];
				n[8] = inputImage[y + 1][3 * (x + 1) + 1];

				std::sort(n, n + 9);
				resultImage[y][3 * x + 1] = n[4];

				n[0] = inputImage[y - 1][3 * (x - 1) + 2];
				n[1] = inputImage[y - 1][3 * x + 2];
				n[2] = inputImage[y - 1][3 * (x + 1) + 2];
				n[3] = inputImage[y][3 * (x - 1) + 2];
				n[4] = inputImage[y][3 * x + 2];
				n[5] = inputImage[y][3 * (x + 1) + 2];
				n[6] = inputImage[y + 1][3 * (x - 1) + 2];
				n[7] = inputImage[y + 1][3 * x + 2];
				n[8] = inputImage[y + 1][3 * (x + 1) + 2];

				std::sort(n, n + 9);
				resultImage[y][3 * x + 2] = n[4];
			}
		}

	}
	
}


void CimageProc20190848Doc::MopologyColorGray()
{
	// TODO: 여기에 구현 코드 추가.
	if (depth == 1)return;
	int x, y,gray;
	for (y = 0; y < imageHeight; y++) {
	    for(x=0;x<imageWidth;x++){
			gray = (inputImage[y][3 * x + 0] + inputImage[y][3 * x + 1] + inputImage[y][3 * x + 2]) / 3;
			inputImage[y][3 * x + 0] = gray;
			inputImage[y][3 * x + 1] = gray;
			inputImage[y][3 * x + 2] = gray;
		}
	}

}


void CimageProc20190848Doc::MopologyBinary()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	int th = 100;
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				if (inputImage[y][x] > th)inputImage[y][x] = 255;
				else inputImage[y][x] = 0;
			}
			else {
				if ((inputImage[y][3 * x + 0] + inputImage[y][3 * x + 1] + inputImage[y][3 * x + 2]) / 3 > th)
				{
					inputImage[y][3 * x + 0] = 255;
					inputImage[y][3 * x + 1] = 255;
					inputImage[y][3 * x + 2] = 255;
				}
				else {
					inputImage[y][3 * x + 0] = 0;
					inputImage[y][3 * x + 1] = 0;
					inputImage[y][3 * x + 2] = 0;
				}
			}
		}
	}
}




void CimageProc20190848Doc::Erosion()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y,min;
	int rmin, gmin, bmin;
	for (y = 1; y < imageHeight-1; y++) {
		for (x = 1; x < imageWidth-1; x++) {
			min = 255; rmin = 255; gmin = 255; bmin = 255;
			for (int j = y-1; j <= y+1; j++) {
				for (int i = x-1; i <= x+1; i++) {
					if (depth == 1) {
						if (inputImage[j][i] < min) min = inputImage[j][i];
					}
					else {
						if (inputImage[j][3 * i + 0] < rmin) rmin = inputImage[j][3 * i + 0];
						if (inputImage[j][3 * i + 1] < gmin) gmin = inputImage[j][3 * i + 1];
						if (inputImage[j][3 * i + 2] < bmin) bmin = inputImage[j][3 * i + 2];
					}
				}
			}
			if(depth==1) resultImage[y][x] = min;
			else {
				resultImage[y][3 * x + 0] = rmin;
				resultImage[y][3 * x + 1] = gmin;
				resultImage[y][3 * x + 2] = bmin;
			}
		}
	}
}


void CimageProc20190848Doc::Dilation()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, max;
	int rmax, gmax, bmax;
	for (y = 1; y < imageHeight - 1; y++) {
		for (x = 1; x < imageWidth - 1; x++) {
			max = 0; rmax = 0; gmax = 0; bmax = 0;
			for (int j = y - 1; j <= y + 1; j++) {
				for (int i = x - 1; i <= x + 1; i++) {
					if (depth == 1) {
						if (inputImage[j][i] > max) max = inputImage[j][i];
					}
					else {
						if (inputImage[j][3 * i + 0] > rmax) rmax = inputImage[j][3 * i + 0];
						if (inputImage[j][3 * i + 1] > gmax) gmax = inputImage[j][3 * i + 1];
						if (inputImage[j][3 * i + 2] > bmax) bmax = inputImage[j][3 * i + 2];
					}
				}
			}
			if (depth == 1) resultImage[y][x] = max;
			else {
				resultImage[y][3 * x + 0] = rmax;
				resultImage[y][3 * x + 1] = gmax;
				resultImage[y][3 * x + 2] = bmax;
			}
		}
	}
}


void CimageProc20190848Doc::Opening()
{
	// TODO: 여기에 구현 코드 추가.
	Erosion();

	CopyResultToInput();
	Erosion();

	CopyResultToInput();
	Erosion();

	CopyResultToInput();
	Dilation();

	CopyResultToInput();
	Dilation();

	CopyResultToInput();
	Dilation();


}


void CimageProc20190848Doc::CopyResultToInput()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	for (y = 0; y < imageHeight; y++) {
		for (x = 0; x < imageWidth*depth; x++) {
			inputImage[y][x] = resultImage[y][x];
		}
	}
}


void CimageProc20190848Doc::Closing()
{
	// TODO: 여기에 구현 코드 추가.
	Dilation();

	CopyResultToInput();
	Dilation();

	CopyResultToInput();
	Dilation();

	CopyResultToInput();
	Erosion();

	CopyResultToInput();
	Erosion();

	CopyResultToInput();
	Erosion();

}


void CimageProc20190848Doc::GeometryZoominPixelCopy()
{
	// TODO: 여기에 구현 코드 추가.
	int xscale = 3;
	int yscale = 3;
	int i;

	if (gResultImg != NULL) {
		for (i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}

	gImageWidth = imageWidth * xscale;
	gImageHeight = imageHeight * yscale;
	
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}
	//전방향사상
	/* 
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			for (int j = 0; j < yscale; j++) {
				for (i = 0; i < xscale; i++) {
					if (depth == 1) {
						gResultImg[yscale * y + j][xscale * x + i] = inputImage[y][x];
					}
					else {
						gResultImg[yscale * y + j][(xscale * x + i) * 3 + 0] = inputImage[y][x * 3 + 0];
						gResultImg[yscale * y + j][(xscale * x + i) * 3 + 1] = inputImage[y][x * 3 + 1];
						gResultImg[yscale * y + j][(xscale * x + i) * 3 + 2] = inputImage[y][x * 3 + 2];
					}
				}
			}
		}
	}
	*/
	//역방향 사사상
	for (int y = 0; y < gImageHeight; y++)
		for (int x = 0; x < gImageWidth; x++) {
			if (depth == 1) {
				gResultImg[y][x] = inputImage[y / yscale][x / xscale];
			}
			else 
			{
				gResultImg[y][3 * x + 0] = inputImage[y / yscale][3 * (x / xscale) + 0];
				gResultImg[y][3 * x + 1] = inputImage[y / yscale][3*(x / xscale)+1];
				gResultImg[y][3 * x + 2] = inputImage[y / yscale][3*(x / xscale)+2];
			}
		}

}


void CimageProc20190848Doc::GeometryZoominInterpolation()
{
	// TODO: 여기에 구현 코드 추가.
	int i;

	float xscale =2.1;
	float yscale =1.5;
	float src_x,src_y ;
	float alpha,beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (gResultImg != NULL) {
		for (i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}

	gImageWidth = imageWidth * xscale;
	gImageHeight = imageHeight * yscale;

	//메모리할당
	
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}

	for (int y = 0; y < gImageHeight; y++)
		for (int x = 0; x < gImageWidth; x++) {
			src_x = x / xscale;
			src_y = y / yscale;

			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay+1;
			Dx = Ax+1;
			Dy = Ay+1;

			if (Bx > imageWidth - 1) Bx = imageWidth - 1;
			if (Dx > imageWidth - 1) Dx = imageWidth - 1;
			if (Cy > imageHeight - 1) Cy = imageHeight - 1;
			if (Dy > imageHeight - 1) Dy = imageHeight - 1;

			if (depth == 1) {
				E = (1 - alpha) * inputImage[Ay][Ax] + alpha * inputImage[By][Bx];
				F = (1 - alpha) * inputImage[Cy][Cx] + alpha * inputImage[Dy][Dx];

				gResultImg[y][x] = (unsigned char)(E * (1 - beta) + F * beta);
			}
			else {
				E = (1 - alpha) * inputImage[Ay][3*Ax+0] + alpha * inputImage[By][3*Bx+0];
				F = (1 - alpha) * inputImage[Cy][3*Cx+0] + alpha * inputImage[Dy][3*Dx+0];
				gResultImg[y][3*x+0] = (unsigned char)(E * (1 - beta) + F * beta);

				E = (1 - alpha) * inputImage[Ay][3 * Ax + 1] + alpha * inputImage[By][3 * Bx + 1];
				F = (1 - alpha) * inputImage[Cy][3 * Cx + 1] + alpha * inputImage[Dy][3 * Dx + 1];
				gResultImg[y][3 * x + 1] = (unsigned char)(E * (1 - beta) + F * beta);

				E = (1 - alpha) * inputImage[Ay][3 * Ax + 2] + alpha * inputImage[By][3 * Bx + 2];
				F = (1 - alpha) * inputImage[Cy][3 * Cx + 2] + alpha * inputImage[Dy][3 * Dx + 2];
				gResultImg[y][3 * x + 2] = (unsigned char)(E * (1 - beta) + F * beta);
			}
		}

}


void CimageProc20190848Doc::GeometryZoomoutSubsampling()
{
	// TODO: 여기에 구현 코드 추가.

	int xscale = 3;
	int yscale = 2;
	int src_x, src_y;

	int i,y,x;

	//메모리 초기화
	if (gResultImg != NULL) {
		for (i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}

	gImageWidth = imageWidth / xscale;
	gImageHeight = imageHeight / yscale;

	//메모리할당
	
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}

	for (y = 0; y < gImageHeight; y++) {
		for (x = 0; x < gImageWidth; x++) {
			if (depth == 1)
				gResultImg[y][x] = inputImage[y * yscale][x * xscale];
			else {
				gResultImg[y][3 * x + 0] = inputImage[y * yscale][3 * (x * xscale) + 0];
				gResultImg[y][3 * x + 1] = inputImage[y * yscale][3 * (x * xscale) + 1];
				gResultImg[y][3 * x + 2] = inputImage[y * yscale][3 * (x * xscale) + 2];
			}
		}
	}

}


void CimageProc20190848Doc::GeometryZoomoutAvg()
{
	// TODO: 여기에 구현 코드 추가.
	int xscale = 3;
	int yscale = 2;
	int sum,rsum,gsum,bsum;
	int src_x, src_y;
	int  i,j;

	//메모리 초기화
	if (gResultImg != NULL) {
		for (i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}

	gImageWidth = imageWidth / xscale + 1;
	gImageHeight = imageHeight / yscale + 1;


	//메모리할당
	
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}

	for (int y = 0; y < imageHeight; y+=yscale) {
		for (int x = 0; x < imageWidth; x+=xscale) {
			sum = 0;
			rsum = 0;
			gsum = 0;
			bsum = 0;
			for (j = 0; j < yscale; j++) 
				for (i = 0; i < xscale; i++) {
					src_x = x + i;
					src_y = y + j;
					if (src_x > imageWidth - 1) src_x = imageWidth - 1;
					if (src_y > imageHeight - 1) src_y = imageHeight - 1;
					if (depth == 1) 
					    sum += inputImage[src_y][src_x];
					else {
						rsum += inputImage[src_y][3 * src_x + 0];
						gsum += inputImage[src_y][3 * src_x + 1];
						bsum += inputImage[src_y][3 * src_x + 2];
					}
				}
			if (depth == 1)
				gResultImg[y / yscale][x / xscale] = sum / (xscale * yscale);
			else {
				gResultImg[y / yscale][3 * (x / xscale) + 0] = rsum / (xscale * yscale);
				gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (xscale * yscale);
				gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (xscale * yscale);
			}
		}
	}
	

}


void CimageProc20190848Doc::GeometryRotate()
{

	CAngleInputDialog dig;
	// TODO: 여기에 구현 코드 추가.
	int x, y, i, j, xdiff, ydiff;
	int angle = 120; //degree
	float radian;
	int Cx, Cy, Oy;
	int x_source, y_source;

	dig.m_iAngle = angle;
	if (dig.DoModal() == IDCANCEL) return;
	angle = dig.m_iAngle;

	if (gResultImg != NULL) {
		for (i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}
	
	radian = 2 * PI / 360 * angle;
	gImageWidth = (imageHeight * fabs(cos(PI / 2 - radian)) + imageWidth * fabs(cos(radian)));
	gImageHeight = (imageHeight * fabs(cos(radian)) + imageWidth * fabs(cos(PI / 2 - radian)));

	
	gResultImg = (unsigned char**)malloc(gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < gImageHeight; i++) {
		gResultImg[i] = (unsigned char*)malloc(gImageWidth * depth);
	}

	// 중심점
	Cx = imageWidth / 2;
	Cy = imageHeight / 2;

	//y의 마지막 좌표값
	Oy = imageHeight - 1;
	xdiff = (gImageWidth - imageWidth) / 2;
	ydiff = (gImageHeight - imageHeight) / 2;

	for (y = -ydiff; y < gImageHeight - ydiff; y++)
		for (x = -xdiff; x < gImageWidth - xdiff; x++) {
			x_source = (Oy - y - Cy) * sin(radian) +( x - Cx) * cos(radian) + Cx;
			y_source = (Oy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy;

			y_source = Oy - y_source;
			if (depth == 1) {
				if (x_source<0 || x_source>imageWidth - 1 || y_source<0 || y_source>imageHeight - 1) gResultImg[y + ydiff][x + xdiff] = 255;
				else gResultImg[y + ydiff][x + xdiff] = inputImage[y_source][x_source];
			}
			else {
				if (x_source<0 || x_source>imageWidth - 1 || y_source<0 || y_source>imageHeight - 1) { 
					gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else {
					gResultImg[y + ydiff][3 * (x + xdiff) + 0] = inputImage[y_source][3 * x_source + 0];
					gResultImg[y + ydiff][3 * (x + xdiff) + 1] = inputImage[y_source][3 * x_source + 1];
					gResultImg[y + ydiff][3 * (x + xdiff) + 2] = inputImage[y_source][3 * x_source + 2];
				}
			}
		}
	

}


void CimageProc20190848Doc::GeometryMirror()
{
	// TODO: 여기에 구현 코드 추가.
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				resultImage[y][x] = inputImage[y][imageWidth - 1 - x];
			}
			else {
				resultImage[y][3*x+0] = inputImage[y][3*(imageWidth - 1 - x)+0];
				resultImage[y][3*x+1] = inputImage[y][3 * (imageWidth - 1 - x) + 1];
				resultImage[y][3*x+2] = inputImage[y][3 * (imageWidth - 1 - x) + 2];
			}
		}
	}
}


void CimageProc20190848Doc::GeometryFlip()
{
	// TODO: 여기에 구현 코드 추가.
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			if (depth == 1) {
				resultImage[imageHeight -1 -y][x] = inputImage[y][x];
			}
			else {
				resultImage[imageHeight - 1 - y][3 * x + 0] = inputImage[y][3 * x + 0];
				resultImage[imageHeight - 1 - y][3 * x + 1] = inputImage[y][3 * x + 1];
				resultImage[imageHeight - 1 - y][3 * x + 2] = inputImage[y][3 * x + 2];
			}
		}
	}
}

typedef struct 
{
	int Px;
	int Py;
	int Qx;
	int Qy;

}control_line;

control_line mctrl_source = { 100,100,150,150 };
control_line mctrl_dest = { 100,100,200,200 };


void CimageProc20190848Doc::GeometryWarping()
{
	// TODO: 여기에 구현 코드 추가.

	mctrl_source.Px = clickStartPx;
	mctrl_source.Py = clickStartPy;
	mctrl_source.Qx = clickStartQx;
	mctrl_source.Qy = clickStartQy;

	mctrl_dest.Px = clickEndPx;
	mctrl_dest.Py = clickEndPy;
	mctrl_dest.Qx = clickEndQx; 
	mctrl_dest.Qy = clickEndQy;

	control_line source_line[5] = {{100,100,150,150}, {0,0,imageWidth-1,0}, {imageWidth-1,0,imageWidth-1,imageHeight-1}, 
		{imageWidth - 1,imageHeight - 1,0 , imageHeight - 1}, {0 , imageHeight - 1,0,0} };
	control_line dest_line[5] = { {100,100,200,200}, {0,0,imageWidth - 1,0}, {imageWidth - 1,0,imageWidth - 1,imageHeight - 1},
		{imageWidth - 1,imageHeight - 1,0 , imageHeight - 1}, {0 , imageHeight - 1,0,0} };

	source_line[0] = mctrl_source;
	dest_line[0] = mctrl_dest;

	int x, y;
	double u;
	double h;
	double d;
	double tx, ty;
	double xp, yp;
	double weight;
	double totalWeight;
	double a =0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, x2, y1, y2;
	int src_x1, src_x2, src_y1, src_y2;

	double src_line_length, dest_line_length;

	int num_lines = 5;
	int line;
	int source_x, source_y;
	int last_row, last_col;
	last_row = imageHeight - 1;
	last_col = imageWidth - 1;

	for (y = 0; y < imageHeight; y++) 
		for (x = 0; x < imageWidth; x++) {
			tx = 0.0;
			ty = 0.0;
			totalWeight = 0.0;
			//각 제어선 벼로 영향을 계산
			for (line = 0; line < num_lines; line++) {
				x1 = dest_line[line].Px;
				y1 = dest_line[line].Py;
				x2 = dest_line[line].Qx;
				y2 = dest_line[line].Qy;

				dest_line_length = sqrt((double)(x2 - x1)* (x2 - x1) + (y2 - y1)* (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / (double)((x2 - x1)* (x2 - x1) + (y2 - y1)* (y2 - y1));
				h = (double)((y - y1)*(x2 - x1) - (x - x1)*(y2 - y1)) / dest_line_length;

				if (u < 0) d = sqrt((double)(x - x1)* (x - x1) + (y - y1)* (y - y1));
				else if (u > 1) d = sqrt((double)(x - x2)* (x - x2) + (y - y2)* (y - y2));
				else d = fabs(h);

				src_x1 = source_line[line].Px;
				src_x2 = source_line[line].Qx;
				src_y1 = source_line[line].Py;
				src_y2 = source_line[line].Qy;

				src_line_length = sqrt((double)(src_x2 - src_x1)* (src_x2 - src_x1) + (src_y2 - src_y1)* (src_y2 - src_y1));

				//입력영상에서의 대응 픽셀 위치 계산
				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				//제어선에 대한 가중치 계산
				weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalWeight += weight;

			}
			source_x = x + (int)(tx / totalWeight + 0.5);
			source_y = y + (int)(ty / totalWeight + 0.5);

			if (source_x < 0)source_x = 0;
			if (source_x > last_col)source_x = last_col;
			if (source_y < 0)source_y = 0;
			if (source_y>last_row)source_y = last_row;

			if (depth == 1)  resultImage[y][x] = inputImage[source_y][source_x]; 
			else {
				resultImage[y][3 * x + 0] = inputImage[source_y][3 * source_x + 0];
				resultImage[y][3 * x + 1] = inputImage[source_y][3 * source_x + 1];
				resultImage[y][3 * x + 2] = inputImage[source_y][3 * source_x + 2];
			}
			
		
		}

       
}


void CimageProc20190848Doc::GeometryMorphing()
{
	// TODO: 여기에 구현 코드 추가.
	control_line source_line[23] =
	{ {116,7,207,5},{34,109,90,21},{55,249,30,128},{118,320,65,261},
	 {123,321,171,321},{179,319,240,264},{247,251,282,135},{281,114,228,8},
	 {78,106,123,109},{187,115,235,114},{72,142,99,128},{74,150,122,154},
	 {108,127,123,146},{182,152,213,132},{183,159,229,157},{219,131,240,154},
	 {80,246,117,212},{127,222,146,223},{154,227,174,221},{228,252,183,213},
	 {114,255,186,257},{109,258,143,277},{152,278,190,262} };
	control_line dest_line[23] =
	{ {120,8,200,6},{12,93,96,16},{74,271,16,110},{126,336,96,290},
	 {142,337,181,335},{192,335,232,280},{244,259,288,108},{285,92,212,13},
	 {96,135,136,118},{194,119,223,125},{105,145,124,134},{110,146,138,151},
	 {131,133,139,146},{188,146,198,134},{189,153,218,146},{204,133,221,140},
	 {91,268,122,202},{149,206,159,209},{170,209,181,204},{235,265,208,199},
	 {121,280,205,284},{112,286,160,301},{166,301,214,287} };

	double u;
	double h;
	double d;
	double tx, ty;
	double xp, yp;
	double weight;
	double totalWeight;
	double a = 0.001, b = 2.0, p = 0.75;
	unsigned char** warpedImg =NULL;
	unsigned char** warpedImg2=NULL;
	int frame;
	double fweight;
	control_line warp_lines[23];
	double tx2, ty2, xp2, yp2;
	int dest_x1, dest_y1, dest_x2, dest_y2, source_x2, source_y2;
	int x1, y1, x2, y2, src_x1, src_x2, src_y1, src_y2;
	double src_line_length, dest_line_length;
	int i, j;
	int num_lines = 23;
	int line, x, y, source_x, source_y, last_row, last_col;

	//두 입력 영상을 읽어 들임
	LoadTwoImages();


	// 중간 프레임의 위핑 결과를 저장

	if (warpedImg != NULL) {
		for (i = 0; i < imageHeight; i++)
			free(warpedImg[i]);
		free(warpedImg);
	}
	warpedImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) warpedImg[i] = (unsigned char*)malloc(imageWidth * depth);

	if (warpedImg2 != NULL) {
		for (i = 0; i < imageHeight; i++)
			free(warpedImg2[i]);
		free(warpedImg2);
	}
	warpedImg2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) warpedImg2[i] = (unsigned char*)malloc(imageWidth * depth);

	for (i = 0; i < NUM_FRAMES; i++) {
		if (morphedImg[i] != NULL) {
			int  j;
			for (j = 0; j < imageHeight; j++)
				free(morphedImg[i][j]);
			free(morphedImg[i]);

		}
	}
	for (i = 0; i < NUM_FRAMES; i++) {
		morphedImg[i] = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
		for (j = 0; j < imageHeight; j++) morphedImg[i][j] = (unsigned char*)malloc(imageWidth * depth);
	}

	
	last_col = imageWidth - 1;
	last_row = imageHeight - 1;

	for (frame = 1; frame <= NUM_FRAMES; frame++) {
		fweight = (double)(frame) / NUM_FRAMES;

		for (line = 0; line < num_lines; line++) {
			warp_lines[line].Px = (int)(source_line[line].Px + (dest_line[line].Px - source_line[line].Px) * fweight);
			warp_lines[line].Py = (int)(source_line[line].Py + (dest_line[line].Py - source_line[line].Py) * fweight);
			warp_lines[line].Qx = (int)(source_line[line].Qx + (dest_line[line].Qx - source_line[line].Qx) * fweight);
			warp_lines[line].Qy = (int)(source_line[line].Qy + (dest_line[line].Qy - source_line[line].Qy) * fweight);
		}
		for (y = 0; y < imageHeight; y++) {
			for (x = 0; x < imageHeight; x++) {
				totalWeight = 0.0;
				tx = 0.0;
				ty = 0.0;
				tx2 = 0.0;
				ty2 = 0.0;
				for (line = 0; line < num_lines; line++)
				{
					x1 = warp_lines[line].Px;
					y1 = warp_lines[line].Py;
					x2 = warp_lines[line].Qx;
					y2 = warp_lines[line].Qy;
					dest_line_length = sqrt((double)(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
					u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
						(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
					h = (double)((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

					if (u < 0) d = sqrt((double)(x - x1) * (x - x1) + (y - y1) * (y - y1));
					else if (u > 1) d = sqrt((double)(x - x2) * (x - x2) + (y - y2) * (y - y2));
					else d = fabs(h);

					src_x1 = source_line[line].Px;
					src_y1 = source_line[line].Py;
					src_x2 = source_line[line].Qx;
					src_y2 = source_line[line].Qy;
					src_line_length = sqrt((double)(src_x2 - src_x1) * (src_x2 - src_x1) +
						(src_y2 - src_y1) * (src_y2 - src_y1));
					dest_x1 = dest_line[line].Px;
					dest_y1 = dest_line[line].Py;
					dest_x2 = dest_line[line].Qx;
					dest_y2 = dest_line[line].Qy;
					dest_line_length = sqrt((double)(dest_x2 - dest_x1) * (dest_x2 - dest_x1) +
						(dest_y2 - dest_y1) * (dest_y2 - dest_y1));

					xp = src_x1 + u * (src_x2 - src_x1) -
						h * (src_y2 - src_y1) / src_line_length;
					yp = src_y1 + u * (src_y2 - src_y1) +
						h * (src_x2 - src_x1) / src_line_length;

					xp2 = dest_x1 + u * (dest_x2 - dest_x1) -
						h * (dest_y2 - dest_y1) / dest_line_length;
					yp2 = dest_y1 + u * (dest_y2 - dest_y1) +
						h * (dest_x2 - dest_x1) / dest_line_length;
					weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

					tx += (xp - x) * weight;
					ty += (yp - y) * weight;

					tx2 += (xp2 - x) * weight;
					ty2 += (yp2 - y) * weight;

					totalWeight += weight;
				}
				source_x = x + (int)(tx / totalWeight + 0.5);
				source_y = y + (int)(ty / totalWeight + 0.5);

				source_x2 = x + (int)(tx2 / totalWeight + 0.5);
				source_y2 = y + (int)(ty2 / totalWeight + 0.5);

				if (source_x < 0) source_x = 0;
				if (source_x > last_col) source_x = last_col;
				if (source_y < 0) source_y = 0;
				if (source_y > last_row) source_y = last_row;

				if (source_x2 < 0) source_x2 = 0;
				if (source_x2 > last_col) source_x2 = last_col;
				if (source_y2 < 0) source_y2 = 0;
				if (source_y2 > last_row) source_y2 = last_row;
				warpedImg[y][x] = inputImage[source_y][source_x];
				warpedImg2[y][x] = inputImage2[source_y2][source_x2];
			}
		}

		for (y = 0; y < imageHeight; y++)
			for (x = 0; x < imageWidth; x++) {
				int val = (int)((1.0 - fweight) * warpedImg[y][x] +
					fweight * warpedImg2[y][x]);
				if (val < 0) val = 0;
				if (val > 255) val = 255;
				morphedImg[frame - 1][y][x] = val;
			}
	}
}

