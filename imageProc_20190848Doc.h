
// imageProc_20190848Doc.h: CimageProc20190848Doc 클래스의 인터페이스
//


#pragma once


class CimageProc20190848Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CimageProc20190848Doc() noexcept;
	DECLARE_DYNCREATE(CimageProc20190848Doc)

// 특성입니다. 
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CimageProc20190848Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//입력이미지
	unsigned char** inputImage;
	unsigned char** inputImage2; 
	//출력이미지
	unsigned char**  resultImage;
	
	int imageWidth;
	int imageHeight;
	int depth; // 값 1=흑백, 3= 컬러
	int gImageWidth;
	int gImageHeight;
	unsigned char** gResultImg;
	unsigned char** morphedImg[10];

	int clickStartPx, clickStartPy, clickStartQx, clickStartQy;
	int clickEndPx, clickEndPy, clickEndQx, clickEndQy;

	void pixelAdd();
	void pixelSub();
	void pixelMul();
	void pixelDiv();
	void pixelHistoEq();
	void pixelStretch();
	void pixelBinaryzation();
	void pixelTwoImageAdd();
	void LoadTwoImages();
	void pixelTwoImageSub();
	
	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
	void RegionSharpening();
	void Convolve(unsigned char** inImage, unsigned char** outImage, int cols, int rows, float mask[][3], int bias, int depth);
	void RegionSmoothing();
	void RegionEmbossing();
	void RegionSobel();
	void RegionPrewitt();
	void RegionRoberts();
	void RegionAverageFilter();
	void RegionMedian();
	void MopologyColorGray();
	void MopologyBinary();
	void Erosion();
	void Dilation();
	void Opening();
	void CopyResultToInput();
	void Closing();
	void GeometryZoominPixelCopy();
	void GeometryZoominInterpolation();
	void GeometryZoomoutSubsampling();
	void GeometryZoomoutAvg();
	void GeometryRotate();
	void GeometryMirror();
	void GeometryFlip();
	void GeometryWarping();
	void GeometryMorphing();
};
