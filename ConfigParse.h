#pragma once

#include "ConfigStruct.h"
#include <vector>
#include <map>


class CConfigParse
{
#define CFGITEM_CONFIG_FILE_PATH_NAME           _T("LocalConfigMap.xml")

public:
    CConfigParse();
    ~CConfigParse();

    BOOL Load();
    void UnLoad();
    void _Clear();
    BOOL CreatPolicyIDMap();

    //获取配置版本信息
    int GetVersion();
    //获取整个m_vecCfgItem
    std::vector<CFGITEM>& GetVecCfgItem();
    //获取policy_id对应的id
    BOOL GetIDGroup(UINT uIndex, std::vector<UINT>& idGroup);

    ATL::CAtlString m_strFilePath;
protected:
    DWORD m_dwVersion;
    std::vector<CFGITEM> m_vecCfgItem;
    std::map<UINT, std::vector<UINT>> m_mapPolicyID;
    ATL::CComAutoCriticalSection m_csForCfgItemCfg;
};

