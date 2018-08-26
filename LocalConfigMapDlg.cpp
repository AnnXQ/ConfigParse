
// ConfigParseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LocalConfigMap.h"
#include "LocalConfigMapDlg.h"
#include "afxdialogex.h"
#include "ConfigDetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConfigParseDlg 对话框



CLocalConfigMapDlg::CLocalConfigMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOCALCONFIGMAP_DIALOG, pParent)
    , m_Row(-1)
    , m_Col(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CLocalConfigMapDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CLocalConfigMapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CLocalConfigMapDlg::OnNMDblclkList)
    ON_COMMAND(ID_MENUITEM_IMPORT, &CLocalConfigMapDlg::OnMenuitemImport)
    ON_COMMAND(ID_MENUITEM_EXIT, &CLocalConfigMapDlg::OnMenuitemExit)
    ON_COMMAND(ID_MENUITEM_CLOASEALL, &CLocalConfigMapDlg::OnMenuitemCloaseall)
    ON_COMMAND(ID_MENUITEM_OPENALL, &CLocalConfigMapDlg::OnMenuitemOpenall)
    ON_COMMAND(ID_MENUITEM_HELP, &CLocalConfigMapDlg::OnMenuitemHelp)
    ON_COMMAND(ID_MENUITEM_CONTACT, &CLocalConfigMapDlg::OnMenuitemContact)
    ON_NOTIFY(NM_CLICK, IDC_LIST, &CLocalConfigMapDlg::OnNMClickList)
    ON_COMMAND(ID_GETFILEDETAIL, &CLocalConfigMapDlg::OnGetfiledetail)
END_MESSAGE_MAP()


// CConfigParseDlg 消息处理程序

BOOL CLocalConfigMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


    // 添加菜单
    m_Menu.LoadMenuW(IDR_MENU1);
    SetMenu(&m_Menu);

    //初始化表格头
    //不可缩放版本
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_OWNERDRAWFIXED | LVS_EX_SUBITEMIMAGES);
    m_ListCtrl.InsertColumn(0, _T("开关"), LVCFMT_LEFT, 40);
    m_ListCtrl.InsertColumn(1, _T(CFGITEM_CONFIG_CFGITEM_ATTR_NAME), LVCFMT_LEFT, 150);
    m_ListCtrl.InsertColumn(2, _T(CFGITEM_CONFIG_CFGITEM_DOWN_ATTR_PATH), LVCFMT_LEFT, 300);

    //读取开关图片
    VERIFY(m_checkImgList.Create(IDB_BITMAP_SWITCH, 31, 2, RGB(255, 0, 255)));
    m_ListCtrl.SetImageList(&m_checkImgList, LVSIL_SMALL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLocalConfigMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLocalConfigMapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLocalConfigMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLocalConfigMapDlg::OnMenuitemImport()
{
    _Clear();

    if (!GetXmlFilePath())
        return;

    if (!m_CfgItemConfig.Load())
    {
        MessageBox(_T("读取文件失败"));
        return;
    }

    std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();
    m_ConfigSyncReg.InitVecSwitchState(veccfgtemp);

    for (UINT nRow = 0; nRow < veccfgtemp.size(); nRow++)
    {
        LV_ITEM lvitem;
        memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
        lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
        lvitem.iItem = nRow;
        lvitem.iSubItem = 0;
        lvitem.stateMask = 0;
        lvitem.iImage = veccfgtemp[nRow].SwitchState;
        m_ListCtrl.InsertItem(&lvitem);
        m_ListCtrl.SetItemText(nRow, 1, veccfgtemp[nRow].name);
        m_ListCtrl.SetItemText(nRow, 2, veccfgtemp[nRow].Download.path);
    }
}


void CLocalConfigMapDlg::OnMenuitemExit()
{
    CDialog::OnOK();
}


void CLocalConfigMapDlg::OnMenuitemCloaseall()
{
    UINT itemcount = m_ListCtrl.GetItemCount();
    if (itemcount <= 0)
    {
        MessageBox(_T("请先点击打开导入xml文件"));
        return;
    }

    std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();

    for (UINT nRow = 0; nRow < itemcount; nRow++)
    {
        if (veccfgtemp[nRow].SwitchState)
        {
            if (m_ConfigSyncReg.SetSwitchState(veccfgtemp[nRow], 0, TRUE))
            {
                LV_ITEM lvitem;
                memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
                lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
                lvitem.iItem = nRow;
                lvitem.iSubItem = 0;
                lvitem.stateMask = 0;
                m_ListCtrl.GetItem(&lvitem);
                lvitem.iImage = 0;
                m_ListCtrl.SetItem(&lvitem);
            }
        }
    }
}


void CLocalConfigMapDlg::OnMenuitemOpenall()
{
    UINT itemcount = m_ListCtrl.GetItemCount();
    if (itemcount <= 0)
    {
        MessageBox(_T("请先点击打开导入xml文件"));
        return;
    }

    std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();

    for (UINT nRow = 0; nRow < itemcount; nRow++)
    {
        if (!(veccfgtemp[nRow].SwitchState))
        {
            if (m_ConfigSyncReg.SetSwitchState(veccfgtemp[nRow], 1, TRUE))
            {
                LV_ITEM lvitem;
                memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
                lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
                lvitem.iItem = nRow;
                lvitem.iSubItem = 0;
                lvitem.stateMask = 0;
                m_ListCtrl.GetItem(&lvitem);
                lvitem.iImage = 1;
                m_ListCtrl.SetItem(&lvitem);
            }
        }
    }
}


void CLocalConfigMapDlg::OnMenuitemHelp()
{
    system("start explorer https://3127414196.github.io/ReadMe.html");
}


void CLocalConfigMapDlg::OnMenuitemContact()
{
    MessageBox(_T("请联系annxiong@tencent.com 谢谢"));
}

void CLocalConfigMapDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    
    DWORD dwPos = GetMessagePos();
    CPoint pt(dwPos);
    m_ListCtrl.ScreenToClient(&pt);

    do
    {
        UINT nFlag;
        int nItem = m_ListCtrl.HitTest(pt, &nFlag);
        
        if (nFlag == LVHT_ONITEMICON)
        {
            std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();
            BOOL nowState = (veccfgtemp[nItem].SwitchState == 0) ? FALSE : TRUE;
            m_ConfigSyncReg.SetSwitchState(veccfgtemp[nItem], !nowState, TRUE);
            //改变图标
            LV_ITEM lvitem;
            memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
            lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
            lvitem.iItem = nItem;
            lvitem.iSubItem = 0;
            lvitem.stateMask = 0;
            m_ListCtrl.GetItem(&lvitem);
            lvitem.iImage = !nowState;
            m_ListCtrl.SetItem(&lvitem);
        }
    } while (FALSE);

    *pResult = 0;
}

void CLocalConfigMapDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
    m_Row = pNMListView->iItem;
    m_Col = pNMListView->iSubItem;

    do
    {
        if (m_Row < 0 || m_Col <= 0)  //选中的是空白处，或者是对checkbox进行点击
            break;

        std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();
        CConfigDetailDlg configdetail(veccfgtemp[m_Row]);
        
        configdetail.DoModal();

    } while (FALSE);

    *pResult = 0;
}

void CLocalConfigMapDlg::_Clear()
{
    UINT RowCount = m_ListCtrl.GetItemCount();
    if (RowCount == 0)
        return;
    
    for (UINT nRow = 0; nRow < RowCount; nRow++)
    {
        if (!m_ListCtrl.DeleteItem(0))
            MessageBox(_T("清空表格失败"));
    }

    m_CfgItemConfig._Clear();
}

BOOL CLocalConfigMapDlg::GetXmlFilePath()
{
    BOOL bRet = FALSE;
    do
    {
        CFileDialog dlg(TRUE, _T("xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("LocalConfig(*.xml)|*.xml||"));
        INT_PTR nResponse = dlg.DoModal();
        if (nResponse == IDOK)
        {
            m_CfgItemConfig.m_strFilePath = dlg.GetPathName();
            bRet = TRUE;
        }
    } while (FALSE);

    return bRet;
}


void CLocalConfigMapDlg::OnGetfiledetail()
{
    if (m_ListCtrl.GetItemCount() <= 0)
    {
        MessageBox(_T("请先导入xml文件"));
        return;
    }

    ATL::CAtlString str;
    str.Format(_T("版本号：%d\r\n配置总数：%d"), m_CfgItemConfig.GetVersion(), m_ListCtrl.GetItemCount());
    MessageBox(str);
}
