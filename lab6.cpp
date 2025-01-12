#pragma once

class CMiniDrawView : public CView
{
protected: 
    CMiniDrawView() noexcept; 
    DECLARE_DYNCREATE(CMiniDrawView)

protected:
    CString m_ClassName;
    int m_Dragging;
    HCURSOR m_HCross;
    CPoint m_PointOld;
    CPoint m_PointOrigin;

public:
    CMiniDrawDoc* GetDocument() const;

public:
    virtual void OnDraw(CDC* pDC);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
    virtual ~CMiniDrawView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  
inline CMiniDrawDoc* CMiniDrawView::GetDocument() const
{
    return reinterpret_cast<CMiniDrawDoc*>(m_pDocument);
}
#endif
