/*
Module : ScintillaDocView.h
Purpose: Defines the interface for MFC CView and CDocument derived wrapper classes for the Scintilla 
         edit control (www.scintilla.org)
Created: PJN / 19-03-2004

Copyright (c) 2004 - 2021 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


//////////////////// Macros / Defines /////////////////////////////////////////

#pragma once

#ifndef __SCINTILLADOCVIEW_H__
#define __SCINTILLADOCVIEW_H__


#include "ScintillaCtrl.h"

#ifndef _VECTOR_
#pragma message("To avoid this message please put vector into your pre compiled header (normally stdafx.h)")
#include <vector>
#endif //#ifndef _VECTOR_

#ifndef _MEMORY_
#pragma message("To avoid this message please put memory into your pre compiled header (normally stdafx.h)")
#include <memory>
#endif //#ifndef _MEMORY_


#ifndef SCINTILLADOCVIEW_EXT_CLASS
#define SCINTILLADOCVIEW_EXT_CLASS
#endif //#ifndef SCINTILLADOCVIEW_EXT_CLASS


//////////////////// Classes //////////////////////////////////////////////////

class SCINTILLADOCVIEW_EXT_CLASS CScintillaFindReplaceDlg : public CFindReplaceDialog
{
public:
//Constructors / Destructors
  CScintillaFindReplaceDlg() noexcept;

//Methods
  BOOL Create(BOOL bFindDialogOnly, LPCTSTR lpszFindWhat, LPCTSTR lpszReplaceWith = nullptr, DWORD dwFlags = FR_DOWN, CWnd* pParentWnd = nullptr) override;
  [[nodiscard]] BOOL GetRegularExpression() const noexcept { return m_bRegularExpression; };
  void SetRegularExpression(_In_ BOOL bRegularExpression) noexcept { m_bRegularExpression = bRegularExpression; };

protected:
//Member variables
  BOOL m_bRegularExpression;

//Methods
  BOOL OnInitDialog() override;

//Message handlers
  afx_msg void OnRegularExpression();
  afx_msg void OnNcDestroy();

  DECLARE_MESSAGE_MAP()
};

class SCINTILLADOCVIEW_EXT_CLASS CScintillaEditState
{
public:
    //Constructors / Destructors
    CScintillaEditState() noexcept;

    //Member variables
    CScintillaFindReplaceDlg* pFindReplaceDlg;    //find or replace dialog
    BOOL                      bFindOnly;          //Is pFindReplace the find or replace?
    CString                   strFind;            //last find string
    CString                   strReplace;         //last replace string
    BOOL                      bCase;              //TRUE==case sensitive, FALSE==not
    int                       bNext;              //TRUE==search down, FALSE== search up
    BOOL                      bWord;              //TRUE==match whole word, FALSE==not
    BOOL                      bRegularExpression; //TRUE==regular expression search, FALSE==not
};

class SCINTILLADOCVIEW_EXT_CLASS CScintillaView : public CView
{
public:
//Constructors / Destructors
  CScintillaView();

//Methods
  CScintillaCtrl& GetCtrl();
  void SetMargins(_In_ const CRect& rMargin) noexcept { m_rMargin = rMargin; };
  [[nodiscard]] CRect GetMargins() const noexcept { return m_rMargin; };
  [[nodiscard]] BOOL GetUseROFileAttributeDuringLoading() const noexcept { return m_bUseROFileAttributeDuringLoading; };
  void SetUseROFileAttributeDuringLoading(_In_ BOOL bUseROFileAttributeDuringLoading) noexcept { m_bUseROFileAttributeDuringLoading = bUseROFileAttributeDuringLoading; };

#ifdef _DEBUG
  void Dump(CDumpContext& dc) const override;
#endif //#ifdef _DEBUG

protected:
//Printing support
  void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) override;
  BOOL OnPreparePrinting(CPrintInfo* pInfo) override;
  void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) override;
  void OnPrint(CDC* pDC, CPrintInfo* pInfo) override;
  void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo = nullptr) override;
  virtual BOOL PaginateTo(CDC* pDC, CPrintInfo* pInfo);
  virtual Sci_Position PrintPage(CDC* pDC, CPrintInfo* pInfo, Sci_Position nIndexStart, Sci_Position nIndexStop);
  virtual void PrintHeader(CDC* pDC, CPrintInfo* pInfo, Sci_RangeToFormat& frPrint);
  virtual void PrintFooter(CDC* pDC, CPrintInfo* pInfo, Sci_RangeToFormat& frPrint);

//Search and Replace support
  virtual void OnFindNext(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);
  virtual void TextNotFound(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression, _In_ BOOL bReplaced);
  virtual BOOL FindText(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);
  virtual void OnEditFindReplace(_In_ BOOL bFindOnly);
  virtual BOOL FindTextSimple(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);
  virtual void OnReplaceSel(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression, _In_z_ LPCTSTR lpszReplace);
  virtual void OnReplaceAll(_In_z_ LPCTSTR lpszFind, _In_z_ LPCTSTR lpszReplace, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);
  virtual BOOL SameAsSelected(_In_z_ LPCTSTR lpszCompare, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);
  virtual Sci_Position FindAndSelect(_In_ DWORD dwFlags, _Inout_ Sci_TextToFind& ft);
  virtual void AdjustFindDialogPosition();
  virtual CScintillaFindReplaceDlg* CreateFindReplaceDialog();

//Misc methods
  void OnDraw(CDC* pDC) override;
  BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
  virtual void DeleteContents();
  void Serialize(CArchive& ar) override;
  BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
  void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) override;
  BOOL UserWantsMetric();
  virtual void LoadMarginSettings(const CString& sSection = _T("PageSetup"));
  virtual void SaveMarginSettings(const CString& sSection = _T("PageSetup"));
  virtual std::unique_ptr<CScintillaCtrl> CreateScintillaControl();
  virtual BOOL ShouldDestroyFindReplaceDialog();

//Notifications
  virtual void OnStyleNeeded(_Inout_ SCNotification* pSCNotification);
  virtual void OnCharAdded(_Inout_ SCNotification* pSCNotification);
  virtual void OnSavePointReached(_Inout_ SCNotification* pSCNotification);
  virtual void OnSavePointLeft(_Inout_ SCNotification* pSCNotification);
  virtual void OnModifyAttemptRO(_Inout_ SCNotification* pSCNotification);
  virtual void OnDoubleClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnUpdateUI(_Inout_ SCNotification* pSCNotification);
  virtual void OnModified(_Inout_ SCNotification* pSCNotification);
  virtual void OnMacroRecord(_Inout_ SCNotification* pSCNotification);
  virtual void OnMarginClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnMarginRightClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnNeedShown(_Inout_ SCNotification* pSCNotification);
  virtual void OnPainted(_Inout_ SCNotification* pSCNotification);
  virtual void OnUserListSelection(_Inout_ SCNotification* pSCNotification);
  virtual void OnDwellStart(_Inout_ SCNotification* pSCNotification);
  virtual void OnDwellEnd(_Inout_ SCNotification* pSCNotification);
  virtual void OnZoom(_Inout_ SCNotification* pSCNotification);
  virtual void OnHotSpotClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnHotSpotDoubleClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnCallTipClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnAutoCSelection(_Inout_ SCNotification* pSCNotification);
  virtual void OnIndicatorClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnIndicatorRelease(_Inout_ SCNotification* pSCNotification);
  virtual void OnAutoCCharDeleted(_Inout_ SCNotification* pSCNotification);
  virtual void OnAutoCCancelled(_Inout_ SCNotification* pSCNotification);
  virtual void OnHotspotReleaseClick(_Inout_ SCNotification* pSCNotification);
  virtual void OnFocusIn(_Inout_ SCNotification* pSCNotification);
  virtual void OnFocusOut(_Inout_ SCNotification* pSCNotification);
  virtual void OnAutoCCompleted(_Inout_ SCNotification* pSCNotification);
  virtual void OnAutoCSelectionChange(_Inout_ SCNotification* pSCNotification);
  virtual void OnChange();
  virtual void OnScintillaSetFocus();
  virtual void OnScintillaKillFocus();

//Member variables
  std::unique_ptr<CScintillaCtrl>    m_pEdit;                            //The scintilla control
  std::vector<Sci_Position>          m_PageStart;                       //array of starting pages
  CRect                              m_rMargin;                          //Margin for printing
  BOOL                               m_bFirstSearch;                     //Is this the first search
  BOOL                               m_bChangeFindRange;                 //Should search start again from beginning
  Sci_Position                       m_lInitialSearchPos;                //Initial search position
  BOOL                               m_bUseROFileAttributeDuringLoading; //Should we check the RO file attribute to see if the file should be opened in read only mode by scintilla
  BOOL                               m_bPrintHeader;                     //Should Headers be printed?
  BOOL                               m_bPrintFooter;                     //Should Footers be printed?
  BOOL                               m_bUsingMetric;                     //TRUE if the margin is specified in Metric units, else FALSE implies imperial
  BOOL                               m_bPersistMarginSettings;           //Should we persist the margin settings for the Page Setup dialog
  BOOL                               m_bCPP11Regex;                      //Should the C++11 regex functionality in Scintilla be used

  afx_msg void OnPaint();
  afx_msg void OnUpdateNeedSel(CCmdUI* pCmdUI);
  afx_msg void OnUpdateNeedPaste(CCmdUI* pCmdUI);
  afx_msg void OnUpdateNeedText(CCmdUI* pCmdUI);
  afx_msg void OnUpdateNeedFind(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
  afx_msg void OnUpdateNeedTextAndFollowingText(CCmdUI* pCmdUI);
  afx_msg void OnEditCut();
  afx_msg void OnEditCopy();
  afx_msg void OnEditPaste();
  afx_msg void OnEditClear();
  afx_msg void OnEditUndo();
  afx_msg void OnEditRedo();
  afx_msg void OnEditSelectAll();
  afx_msg void OnEditFind();
  afx_msg void OnEditReplace();
  afx_msg void OnEditRepeat();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnFilePageSetup();
  afx_msg void OnDestroy();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg LRESULT OnFindReplaceCmd(WPARAM, LPARAM lParam);

  DECLARE_MESSAGE_MAP()

  DECLARE_DYNCREATE(CScintillaView)

  friend class CScintillaDoc;
};

class SCINTILLADOCVIEW_EXT_CLASS CScintillaDoc : public CDocument
{
protected: //create from serialization only
  CScintillaDoc();
  DECLARE_DYNAMIC(CScintillaDoc)

//Attributes
public:
  [[nodiscard]] virtual CScintillaView* GetView() const;

//Implementation
public:
  void DeleteContents() override;
  BOOL IsModified() override;
  void SetModifiedFlag(BOOL bModified = TRUE) override;
  void Serialize(CArchive& ar) override;
  BOOL OnSaveDocument(LPCTSTR lpszPathName) override;
};


#endif //#ifndef __SCINTILLADOCVIEW_H__
