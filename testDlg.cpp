
// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

// convert
CImage imgInputVideo;
CImage imgViolationFrame;
CImage imgPlateNumberFrame;


BOOL bInputCreated = FALSE;
BOOL bViolationCreated = FALSE;
BOOL bPlateNumberCreated = FALSE;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestDlg dialog



CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_MY_FRAME, m_staticImage);
	DDX_Control(pDX, IDC_VIOLATION_FRAME, m_staticViolationImage);
	DDX_Control(pDX, IDC_PLATE_NUMBER_FRAME, m_staticPlateNumberImage);

	DDX_Control(pDX, IDC_VIETTEL_APP_NAME_STATIC, m_stAppname);
	DDX_Control(pDX, IDC_VIETTEL_VERSION_STATIC, m_stVersionname);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_VIETTEL_TITLE_STATIC, m_stTitle);
	DDX_Control(pDX, IDC_TIME_STATIC, m_stTime);
	DDX_Control(pDX, IDC_ADDRESS_STATIC, m_stAddress);
	DDX_Control(pDX, IDC_PLATE_NUMBER_STATIC, m_stPlateNumber);
	DDX_Control(pDX, IDC_VILOATION_IMAGE_STATIC, m_stViolationImage);
	DDX_Control(pDX, IDC_ERROR_TYPE_STATIC, m_stErrorType);
	DDX_Control(pDX, IDC_LOGO_STATIC, m_IconAppPicture);
	
	DDX_Control(pDX, IDC_CAMERA_IP_STATIC, m_stCameraIP);
	DDX_Control(pDX, IDC_CAMERA_RESOLUTION_STATIC, m_stCameraResolution);
	DDX_Control(pDX, IDC_CAMERA_CODE_STATIC, m_stCameraCode);
	DDX_Control(pDX, IDC_CAMERA_FRAME_RATE_STATIC, m_stCameraFrameRate);

	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CtestDlg message handlers

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	Init();
	Decorate();

	test.startRetrieveFrame();
	//m_nTimerID = SetTimer(2348, 10, 0);
	thread = AfxBeginThread((AFX_THREADPROC)CtestDlg::Thread, (LPVOID) this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

cv::Mat inputFrame;
cv::Mat plateNumberFrame;
cv::Mat violationFrame;
cv::Mat matImgTmp;
cv::Mat plateNumber;
cv::Mat violationImage;

void CtestDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
}

void CtestDlg::Init()
{
	RECT r;
	m_staticImage.GetClientRect(&r);
	m_sizeInputShow = cv::Size(r.right, r.bottom);

	m_staticViolationImage.GetClientRect(&r);
	m_sizeViolationShow = cv::Size(r.right, r.bottom);

	m_staticPlateNumberImage.GetClientRect(&r);
	m_sizePlateNumberShow = cv::Size(r.right, r.bottom);
}

void CtestDlg::OnDestroy()
{
}

DWORD CtestDlg::Thread(LPVOID *lpvParam)
{
	CtestDlg *thr = (CtestDlg*)lpvParam;
	thr->ThreadProcess();
	return NULL;
}


void CtestDlg::ThreadProcess()
{
	do{
		// show on input frame 
		inputFrame = test.getFrameProcessed();
		Mat2CImage(inputFrame, imgInputVideo, m_sizeInputShow, bInputCreated);
		imgInputVideo.BitBlt(::GetDC(m_staticImage.m_hWnd), 0, 0);
		
		double val = (double)rand() / RAND_MAX;
		int random;

		// show on plate number
		plateNumberFrame = test.getPlateNumber();

		if (val < 0.05)  //  5% + 20%
		{	
			// fake data
			plateNumberFrame = inputFrame;
		}

		if (0 == Mat2CImage(plateNumberFrame, imgPlateNumberFrame, m_sizePlateNumberShow, bPlateNumberCreated))
		{
			imgPlateNumberFrame.BitBlt(::GetDC(m_staticPlateNumberImage.m_hWnd), 0, 0);
		}

		// show on violation 
		violationFrame = test.getViolationImage();
		if (val < 0.05)  //  5% + 20%
		{
			// fake data
			violationFrame = inputFrame;
		}
		
		if (0 == Mat2CImage(violationFrame, imgViolationFrame, m_sizeViolationShow, bViolationCreated))
		{
			imgViolationFrame.BitBlt(::GetDC(m_staticViolationImage.m_hWnd), 0, 0);
			// Show violation error

			GetDlgItem(IDC_ERROR_TYPE_VALUE_STATIC)->SetWindowTextW(_T("Nguoc Chieu"));
		}


	} while (2);
}


int CtestDlg::Mat2CImage(cv::Mat frame, CImage &img, cv::Size size, BOOL &bCreated)
{
	if (frame.empty())
		return -1;

	//if (frame.size() != size)
	{
		matImgTmp = cv::Mat(size, CV_8UC3);
		cv::resize(frame, matImgTmp, size, 0, 0, cv::INTER_AREA);
	}
	//else {
	//	matImgTmp = frame.clone();
	//}

	int nBPP = matImgTmp.channels() * 8;
	if (bCreated == FALSE)
	{
		img.Create(matImgTmp.cols, matImgTmp.rows, nBPP);
		bCreated = TRUE;
	}

	if (nBPP == 8)
	{
		static RGBQUAD pRGB[256];
		for (int i = 0; i < 256; i++)
			pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed = i;
		img.SetColorTable(0, 256, pRGB);
	}
	uchar* psrc = matImgTmp.data;
	uchar* pdst = (uchar*)img.GetBits();
	int imgPitch = img.GetPitch();
	for (int y = 0; y < matImgTmp.rows; y++)
	{
		memcpy(pdst, psrc, matImgTmp.cols*matImgTmp.channels());
		psrc += matImgTmp.step;
		pdst += imgPitch;
	}

	return 0;
}

void CtestDlg::Decorate()
{
	// title, version 
	m_stAppname.SetTextColor(RED);

	m_stTime.SetTextColor(RED);
	//m_stDate.SetTextColor(RED);
	m_stPlateNumber.SetTextColor(RED);
	m_stViolationImage.SetTextColor(RED);
	m_stErrorType.SetTextColor(RED);

	m_stVersionname.SetTextColor(RED);
	m_stTitle.SetTextColor(RED);


	m_stCameraIP.SetTextColor(RED);
	m_stCameraResolution.SetTextColor(RED);
	m_stCameraCode.SetTextColor(RED);
	m_stCameraFrameRate.SetTextColor(RED);
	m_stAddress.SetTextColor(RED);


	CFont font;
	font.CreateFontW(
		25,					 // nHeight
		10,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));                 // lpszFacename

	m_stTitle.SetFont(&font, TRUE);
	// Set logo 
	m_IconAppPicture.Load(CString(_T("ViettelLogo.jpg")));
	
	// Set camera info 
	GetDlgItem(IDC_EDIT_CAMERA_IP)->SetWindowTextW(_T("10.1.1.1"));
	GetDlgItem(IDC_EDIT_CAMERA_IP)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_CAMERA_CODE)->SetWindowTextW(_T("CAM_1"));
	GetDlgItem(IDC_EDIT_CAMERA_CODE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_FRAME_RATE)->SetWindowTextW(_T("25ps"));
	GetDlgItem(IDC_EDIT_FRAME_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_RESOLUTION)->SetWindowTextW(_T("FULLHD"));
	GetDlgItem(IDC_EDIT_RESOLUTION)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_CAMERA_ADDRESS)->SetWindowTextW(_T("NUT GIAO THONG 136 PHAM HUNG"));
	GetDlgItem(IDC_EDIT_CAMERA_ADDRESS)->EnableWindow(FALSE);

}