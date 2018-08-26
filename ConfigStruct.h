#pragma once

#define CFGITEM_CONFIG_ROOT                     "Config"
#define CFGITEM_CONFIG_VER                      "version"

#define CFGITEM_CONFIG_CFGITEM                  "CfgItem"
#define CFGITEM_CONFIG_CFGITEM_ATTR_ID          "id"
#define CFGITEM_CONFIG_CFGITEM_ATTR_NAME        "name"
#define CFGITEM_CONFIG_CFGITEM_ATTR_GUID        "guid"

#define CFGITEM_CONFIG_CFGITEM_QQPC             "QQPCMgrSupport"
#define CFGITEM_CONFIG_CFGITEM_QQPC_ATTR_MIN    "build_min"
#define CFGITEM_CONFIG_CFGITEM_QQPC_ATTR_MAX    "build_max"

#define CFGITEM_CONFIG_CFGITEM_DOWN             "Download"
#define CFGITEM_CONFIG_CFGITEM_DOWN_ATTR_APPID  "appid"
#define CFGITEM_CONFIG_CFGITEM_DOWN_ATTR_PATH   "path"

#define CFGITEM_CONFIG_CFGITEM_CLOUD            "Cloud"
#define CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_TYPE  "policy_type"
#define CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_PID   "policy_id"
#define CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_SID   "switch_id"
#define CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_UID   "url_id"
#define CFGITEM_CONFIG_CFGITEM_CLOUD_ATTR_MID   "md5_id"

#define CFGITEM_CONFIG_CFGITEM_IPC              "Ipc"
#define CFGITEM_CONFIG_CFGITEM_IPC_ATTR_NODE    "node"
#define CFGITEM_CONFIG_CFGITEM_IPC_ATTR_MSGID   "msgid"
#define CFGITEM_CONFIG_CFGITEM_IPC_ATTR_NOTIFY  "notifywhensuc"
#define CFGITEM_CONFIG_CFGITEM_IPC_ATTR_CONTEXT "context"

typedef struct _QQPCMGRSUPPORT
{
    UINT build_min;
    UINT build_max;
}QQPCMGRSUPPORT, *PQQPCMGRSUPPORT;

typedef struct _DOWNLOAD
{
    UINT appid;
    ATL::CAtlString path;
}DOWNLOAD, *PDOWNLOAD;

typedef struct _CLOUD
{
    ATL::CAtlString policy_type;
    UINT policy_id;
    UINT switch_id;
    UINT url_id;
    UINT md5_id;
}CLOUD, *PCLOUD;

typedef struct _IPC
{
    ATL::CAtlString node;
    ATL::CAtlString msgid;
    UINT notifywhensuc;
    ATL::CAtlString context;
}IPC, *PIPC;

class CFGITEM
{
public:
    CFGITEM()
        : SwitchState(1)
    {
    }

    ~CFGITEM()
    {
    }

    UINT id;
    ATL::CAtlString name;
    ATL::CAtlString guid;
    //用于保存guid对应的状态
    DWORD SwitchState;
    QQPCMGRSUPPORT QQPcMgrSupport;
    DOWNLOAD Download;
    CLOUD Cloud;
    IPC Ipc;
};