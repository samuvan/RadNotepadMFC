
// RadNotepadView.h : interface of the CRadNotepadView class
//

#pragma once


class CRadNotepadView : public CScintillaView
{
protected: // create from serialization only
	CRadNotepadView();
	DECLARE_DYNCREATE(CRadNotepadView)

// Attributes
public:
	CRadNotepadDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    virtual void OnModified(_Inout_ SCNotification* pSCNotification);
protected:

// Implementation
public:
	virtual ~CRadNotepadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    void DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back);

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
    afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg void OnViewMarker(UINT nId);
    afx_msg void OnUpdateViewMarker(CCmdUI *pCmdUI);
    afx_msg void OnViewWhitespace();
    afx_msg void OnUpdateViewWhitespace(CCmdUI *pCmdUI);
    afx_msg void OnViewEndOfLine();
    afx_msg void OnUpdateViewEndOfLine(CCmdUI *pCmdUI);
    afx_msg void OnViewWordWrap();
    afx_msg void OnUpdateViewWordWrap(CCmdUI *pCmdUI);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in RadNotepadView.cpp
inline CRadNotepadDoc* CRadNotepadView::GetDocument() const
   { return reinterpret_cast<CRadNotepadDoc*>(m_pDocument); }
#endif

