
// testDlg.h : header file
//
#include "retrieveframeprocessed.h"
#include "ColorStatic.h"
#include "picturectrl.h"
#pragma once

// CtestDlg dialog
class CtestDlg : public CDialogEx
{
// Construction
public:
	CtestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
	

public:

	UINT m_nTimerID;
	void Init();
	trackingobjects::RetrieveFrameProcessed test;
	cv::Size m_sizeInputShow;
	cv::Size m_sizeViolationShow;
	cv::Size m_sizePlateNumberShow;

	CImage *m_pImg;
	CStatic m_staticImage;
	CStatic m_staticViolationImage;
	CStatic m_staticPlateNumberImage;

	BITMAPINFO m_bitInfo;
	CWinThread* thread;
	bool started;
	afx_msg void ThreadProcess();
	static DWORD Thread(LPVOID *x);
	afx_msg void StopThread();
	afx_msg bool ipDraw(HDC hdc, IplImage* img, int xoffset = 0, int yoffset = 0);
	int CtestDlg::Mat2CImage(cv::Mat mat, CImage &img, cv::Size size, BOOL &bFirstCreated);
	void Decorate();
private:
	CColorStatic m_stAppname;
	CColorStatic m_stVersionname;
	CColorStatic m_stTitle;

	CColorStatic m_stCameraIP;
	CColorStatic m_stCameraResolution;
	CColorStatic m_stCameraCode;
	CColorStatic m_stCameraFrameRate;

	CColorStatic m_stErrorType;
	CColorStatic m_stTime;
	CColorStatic m_stAddress;
	CColorStatic m_stPlateNumber;
	CColorStatic m_stViolationImage;


	CPictureCtrl m_IconAppPicture;
};
