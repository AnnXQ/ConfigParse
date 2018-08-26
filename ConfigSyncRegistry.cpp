#include "stdafx.h"
#include "ConfigSyncRegistry.h"
#include "AutoCriticalSection.h"
#include "RegistryHandler.h"

CConfigSyncRegistry::CConfigSyncRegistry()
{
}


CConfigSyncRegistry::~CConfigSyncRegistry()
{
}

void CConfigSyncRegistry::InitVecSwitchState(std::vector<CFGITEM>& vecCfgItem)
{
    for (UINT i = 0; i < vecCfgItem.size(); i++)
    {
        DWORD dwInitState = 1;
        BOOL isGet = FetchStateFromReg(vecCfgItem[i], &dwInitState);
        SetSwitchState(vecCfgItem[i], dwInitState, !isGet);
    }
}

BOOL CConfigSyncRegistry::FetchStateFromReg(CFGITEM& cfgitem, DWORD * pdwstate)
{
    BOOL bRet = FALSE;

    do
    {
        DWORD State;
        CRegistryHandler m_RegistryHandler(CONFIGSYNC_KEY, CONFIGSYNC_LPSUBKEY);
        
        if (m_RegistryHandler.QueryValue<DWORD>(cfgitem.guid, CONFIGSYNC_TYPE, &State, CONFIGSYNC_TYPE_SIZE))
        {
            bRet = TRUE;
            if (pdwstate)
                *pdwstate = State;
        }
    } while (FALSE);

    return bRet;
}

BOOL CConfigSyncRegistry::SetSwitchState(CFGITEM& cfgitem, DWORD pdwstate, BOOL bwritethrough)
{
    BOOL bRet = FALSE;

    do
    {
        if (!bwritethrough)
        {
            cfgitem.SwitchState = pdwstate;
            bRet = TRUE;
            break;
        }

        CRegistryHandler m_RegistryHandler(CONFIGSYNC_KEY, CONFIGSYNC_LPSUBKEY);
        
        bRet = m_RegistryHandler.Motify<DWORD>(cfgitem.guid, CONFIGSYNC_TYPE, pdwstate, CONFIGSYNC_TYPE_SIZE);
        
        if (bRet)
            cfgitem.SwitchState = pdwstate;

    } while (FALSE);

    return bRet;
}
