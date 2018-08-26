
// ConfigParseDlg.h : 头文件
//

#pragma once
#include "ConfigParse.h"
#include "ConfigSyncRegistry.h"
#include "afxcmn.h"

// CConfigParseDlg 对话框
class CLocalConfigMapDlg : public CDialogEx
{
// 构造
public:
    CLocalConfigMapDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOCALCONFIGMAP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_ListCtrl;
    CImageList m_checkImgList;
    CMenu m_Menu;
    afx_msg void OnMenuitemImport();
    afx_msg void OnMenuitemExit();
    afx_msg void OnMenuitemCloaseall();
    afx_msg void OnMenuitemOpenall();
    afx_msg void OnMenuitemHelp();
    afx_msg void OnMenuitemContact();
    afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

    //清空表格
    void _Clear();
    //打开文件资源管理器，并设置文件路径
    BOOL GetXmlFilePath();

private:
    int m_Row;
    int m_Col;
    CConfigSyncRegistry m_ConfigSyncReg;
    CConfigParse m_CfgItemConfig;
public:
    afx_msg void OnGetfiledetail();
};
