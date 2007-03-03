// starinstallDlg.h : header file
//

#if !defined(AFX_STARINSTALLDLG_H__9F829908_C656_4B56_A615_333857578AB2__INCLUDED_)
#define AFX_STARINSTALLDLG_H__9F829908_C656_4B56_A615_333857578AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStarinstallDlg dialog

class CStarinstallDlg : public CDialog
{
// Construction
public:
	CStarinstallDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStarinstallDlg)
	enum { IDD = IDD_STARINSTALL_DIALOG };
	CString	m_folder;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarinstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStarinstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARINSTALLDLG_H__9F829908_C656_4B56_A615_333857578AB2__INCLUDED_)
