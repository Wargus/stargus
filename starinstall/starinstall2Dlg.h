// starinstall2Dlg.h : header file
//

#if !defined(AFX_STARINSTALL2DLG_H__024ACF32_BBA3_4D6B_893B_5E1FE765A20A__INCLUDED_)
#define AFX_STARINSTALL2DLG_H__024ACF32_BBA3_4D6B_893B_5E1FE765A20A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStarinstall2Dlg dialog

class CStarinstall2Dlg : public CDialog
{
// Construction
public:
	CStarinstall2Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStarinstall2Dlg)
	enum { IDD = IDD_STARINSTALL_DIALOG2 };
	CButton	m_button;
	CEdit	m_progressctl;
	CString	m_progress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarinstall2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void AddProgress(LPTSTR msg);
	CString	m_folder;

// Implementation
protected:
	HICON m_hIcon;
	int m_lines;
	int m_done;

	// Generated message map functions
	//{{AFX_MSG(CStarinstall2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnAddProgress(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARINSTALL2DLG_H__024ACF32_BBA3_4D6B_893B_5E1FE765A20A__INCLUDED_)
