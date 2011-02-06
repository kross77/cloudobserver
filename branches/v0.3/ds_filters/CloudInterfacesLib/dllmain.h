// dllmain.h : Declaration of module class.

class CCloudInterfacesLibModule : public CAtlDllModuleT< CCloudInterfacesLibModule >
{
public :
	DECLARE_LIBID(LIBID_CloudInterfacesLibLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CLOUDINTERFACESLIB, "{334D86CE-7102-47E4-BDAC-345EF328F54F}")
};

extern class CCloudInterfacesLibModule _AtlModule;
