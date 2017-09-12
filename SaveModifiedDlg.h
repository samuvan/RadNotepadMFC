#pragma once
#include "afxwin.h"


// CSaveModifiedDlg dialog

class CSaveModifiedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveModifiedDlg)

public:
	CSaveModifiedDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveModifiedDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVE_MODIFIED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
    virtual void OnOK() override;

	DECLARE_MESSAGE_MAP()
    CListCtrl m_List;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedNo();
};
