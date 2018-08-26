#pragma once
#include "ConfigStruct.h"
#include <vector>

class CConfigSyncRegistry
{
public:
    CConfigSyncRegistry();
    ~CConfigSyncRegistry();

#define CONFIGSYNC_KEY          HKEY_LOCAL_MACHINE
#define CONFIGSYNC_LPSUBKEY     _T("SOFTWARE\\Wow6432Node\\Tencent\\ConfigSync")
#define CONFIGSYNC_TYPE         REG_DWORD
#define CONFIGSYNC_TYPE_SIZE    (sizeof(DWORD))

    void InitVecSwitchState(std::vector<CFGITEM>& vecCfgItem);
    
    //从注册表中取出guid对应的值
    //pdwstate为NULL，只查询注册表中是否有guid的键值，不为NULL，将状态pdwstate返回
    BOOL FetchStateFromReg(CFGITEM& cfgitem, DWORD* pdwstate = 0);

    //bwritethrough为TRUE表示是否要写入注册表
    //bwritethrough为FALSE表示不写入注册表，只写入m_vecswitchstate
    //默认不写回
    BOOL SetSwitchState(CFGITEM& cfgitem, DWORD pdwstate, BOOL bwritethrough = FALSE);
};

