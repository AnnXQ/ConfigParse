// ConfigDetailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LocalConfigMap.h"
#include "ConfigDetailDlg.h"
#include "afxdialogex.h"


// CConfigDetailDlg 对话框

IMPLEMENT_DYNAMIC(CConfigDetailDlg, CDialogEx)

CConfigDetailDlg::CConfigDetailDlg(CFGITEM& cfgitem, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIGDETAIL_DIALOG, pParent)
    , m_vecCfgItem(cfgitem)
{

}

CConfigDetailDlg::~CConfigDetailDlg()
{
}

void CConfigDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_EDIT_BUILD_MIN, m_editbuild_min);
    DDX_Control(pDX, IDC_EDIT_BUILD_MAX, m_editbuild_max);
    DDX_Control(pDX, IDC_EDIT_APPID, m_editappid);
    DDX_Control(pDX, IDC_EDIT_PATH, m_editpath);
    DDX_Control(pDX, IDC_EDIT_POLICY_TYPE, m_editpolicy_type);
    DDX_Control(pDX, IDC_EDIT_POLICY_ID, m_editpolicy_id);
    DDX_Control(pDX, IDC_EDIT_SWITCH_ID, m_editswitch_id);
    DDX_Control(pDX, IDC_EDIT_URL_ID, m_editurl_id);
    DDX_Control(pDX, IDC_EDIT_MD5_ID, m_editmd5_id);
    DDX_Control(pDX, IDC_EDIT_NODE, m_editnode);
    DDX_Control(pDX, IDC_EDIT_MSGID, m_editmsgid);
    DDX_Control(pDX, IDC_EDIT_NOTIFY, m_editnotifywhensuc);
    DDX_Control(pDX, IDC_EDIT_CONTEXT, m_editcontext);
}


BEGIN_MESSAGE_MAP(CConfigDetailDlg, CDialogEx)
END_MESSAGE_MAP()


// CConfigDetailDlg 消息处理程序
BOOL CConfigDetailDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //显示数据
    CString tempstr;
    tempstr.Format(_T("%d"), m_vecCfgItem.QQPcMgrSupport.build_min);
    m_editbuild_min.SetWindowTextW(tempstr);

    tempstr.Format(_T("%d"), m_vecCfgItem.QQPcMgrSupport.build_max);
    m_editbuild_max.SetWindowTextW(tempstr);

    tempstr.Format(_T("%d"), m_vecCfgItem.Download.appid);
    m_editappid.SetWindowTextW(tempstr);

    m_editpath.SetWindowTextW(m_vecCfgItem.Download.path);

    m_editpolicy_type.SetWindowTextW(m_vecCfgItem.Cloud.policy_type);

    tempstr.Format(_T("%d"), m_vecCfgItem.Cloud.policy_id);
    m_editpolicy_id.SetWindowTextW(tempstr);

    tempstr.Format(_T("%d"), m_vecCfgItem.Cloud.switch_id);
    m_editswitch_id.SetWindowTextW(tempstr);

    tempstr.Format(_T("%d"), m_vecCfgItem.Cloud.url_id);
    m_editurl_id.SetWindowTextW(tempstr);

    tempstr.Format(_T("%d"), m_vecCfgItem.Cloud.md5_id);
    m_editmd5_id.SetWindowTextW(tempstr);

    m_editnode.SetWindowTextW(m_vecCfgItem.Ipc.node);
    m_editmsgid.SetWindowTextW(m_vecCfgItem.Ipc.msgid);

    tempstr.Format(_T("%d"), m_vecCfgItem.Ipc.notifywhensuc);
    m_editnotifywhensuc.SetWindowTextW(tempstr);

    m_editcontext.SetWindowTextW(m_vecCfgItem.Ipc.context);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CConfigDetail 消息处理程序