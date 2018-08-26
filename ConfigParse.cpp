#include "stdafx.h"
#include "ConfigParse.h"
#include "XmlParser.h"
#include "AutoCriticalSection.h"
#include <atlpath.h>


CConfigParse::CConfigParse()
    :m_dwVersion(0)
{
}


CConfigParse::~CConfigParse()
{
}

BOOL CConfigParse::Load()
{
//#define CFGITEM_CONFIG_FILE_PATH_NAME           _T("LocalConfigMap.xml")
    
    BOOL bRet = FALSE;

    do
    {
        ATL::CAtlString strFilePath = m_strFilePath;
        if (!ATLPath::FileExists(strFilePath))
        {
            CAtlString strCfgDir;
            GetModuleFileName(NULL, strCfgDir.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
            strCfgDir.ReleaseBuffer();
            PathRemoveFileSpec(strCfgDir.GetBuffer());
            strCfgDir.ReleaseBuffer();
            if (!strCfgDir.IsEmpty() && (strCfgDir.Right(1) != L'\\' || strCfgDir.Right(1) != L'/'))
            {
                strCfgDir += L"\\";
            }

            strFilePath = strCfgDir + m_strFilePath;
            if (!ATLPath::FileExists(strFilePath))
            {
                break;
            }
        }

        CXmlParser<> xmlParse;
        if (!xmlParse.Load(strFilePath))
            break;

        if (!xmlParse.FindElem(CFGITEM_CONFIG_ROOT))
        {
            break;
        }

        m_dwVersion = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_VER);

        CAutoCriticalSection lock(m_csForCfgItemCfg);
        xmlParse.IntoElem();

        while (xmlParse.FindElem(CFGITEM_CONFIG_CFGITEM))
        {
            CFGITEM CfgItem;
            CfgItem.id = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_ATTR_ID);
            CfgItem.name = xmlParse.GetAttrib<ATL::CAtlString>(CFGITEM_CONFIG_CFGITEM_ATTR_NAME);
            CfgItem.guid = xmlParse.GetAttrib<ATL::CAtlString>(CFGITEM_CONFIG_CFGITEM_ATTR_GUID);

            xmlParse.IntoElem();

            if (xmlParse.FindElem(CFGITEM_CONFIG_CFGITEM_QQPC))
            {
                CfgItem.QQPcMgrSupport.build_min = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_QQPC_ATTR_MIN);
                CfgItem.QQPcMgrSupport.build_max = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_QQPC_ATTR_MAX);
            }
            
            if (xmlParse.FindElem(CFGITEM_CONFIG_CFGITEM_DOWN))
            {
                CfgItem.Download.appid = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_DOWN_ATTR_APPID);
                CfgItem.Download.path = xmlParse.GetAttrib<ATL::CAtlString>(CFGITEM_CONFIG_CFGITEM_DOWN_ATTR_PATH);
            }

            
            if (xmlParse.FindElem(CFGITEM_CONFIG_CFGITEM_CLOUD))
            {
                CfgItem.Cloud.policy_type = xmlParse.GetAttrib<ATL::CAtlString>(CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_TYPE);
                CfgItem.Cloud.policy_id = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_PID);
                CfgItem.Cloud.switch_id = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_SID);
                CfgItem.Cloud.url_id = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_UID);
                CfgItem.Cloud.md5_id = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_MID);
            }

            if (xmlParse.FindElem(CFGITEM_CONFIG_CFGITEM_IPC))
            {
                CfgItem.Ipc.node = xmlParse.GetAttrib<ATL::CAtlString>(CFGITEM_CONFIG_CFGITEM_IPC_ATTR_NODE);
                CfgItem.Ipc.msgid = xmlParse.GetAttrib<ATL::CAtlString>(CFGITEM_CONFIG_CFGITEM_IPC_ATTR_MSGID);
                CfgItem.Ipc.notifywhensuc = xmlParse.GetAttrib<UINT>(CFGITEM_CONFIG_CFGITEM_IPC_ATTR_NOTIFY);
                CfgItem.Ipc.context = xmlParse.GetAttrib<ATL::CAtlString>(CFGITEM_CONFIG_CFGITEM_IPC_ATTR_CONTEXT);
            }

            xmlParse.OutOfElem();
            m_vecCfgItem.push_back(CfgItem);
        }

        bRet = CreatPolicyIDMap();

        if (!bRet)
        {
            UnLoad();
        }

    } while (FALSE);

    return bRet;
}

void CConfigParse::UnLoad()
{
    CAutoCriticalSection lock(m_csForCfgItemCfg);
    m_vecCfgItem.clear();
}

void CConfigParse::_Clear()
{
    m_vecCfgItem.clear();
    m_mapPolicyID.clear();
}

BOOL CConfigParse::CreatPolicyIDMap()
{
    BOOL bRet = FALSE;

    do
    {
        std::map<UINT, std::vector<UINT>>::iterator Mapiter;

        UINT policy_id = 0;
        UINT id = 0;
        int vecSize = m_vecCfgItem.size();
        if (vecSize <= 0)
            break;

        for (int i = 0; i < vecSize; i++)
        {
            id = m_vecCfgItem[i].id;
            policy_id = m_vecCfgItem[i].Cloud.policy_id;

            Mapiter = m_mapPolicyID.find(policy_id);
            if (Mapiter != m_mapPolicyID.end())
            {
                Mapiter->second.push_back(id);
            }
            else
            {
                std::vector<UINT> temp;
                temp.push_back(id);
                m_mapPolicyID.insert(std::map<UINT, std::vector<UINT>>::value_type(policy_id, temp));
            }
        }

        bRet = TRUE;

    } while (FALSE);

    return bRet;
}

int CConfigParse::GetVersion()
{
    return m_dwVersion;
}

std::vector<CFGITEM>& CConfigParse::GetVecCfgItem()
{
    return m_vecCfgItem;
}

BOOL CConfigParse::GetIDGroup(UINT uIndex, std::vector<UINT>& idGroup)
{
    std::map<UINT, std::vector<UINT>>::iterator iter = m_mapPolicyID.find(uIndex);

    if (iter != m_mapPolicyID.end())
    {
        int size = iter->second.size();

        for (int i = 0; i < size; i++)
            idGroup.push_back((iter->second)[i]);
        return TRUE;
    }

    return FALSE;
}
