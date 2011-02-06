
static const WCHAR g_wszName[] = FILTER_WCHAR_NAME;


const AMOVIESETUP_MEDIATYPE pinSubtypes = 
{ 
    &MEDIATYPE_Video, 
    &MEDIASUBTYPE_NULL 
};

const AMOVIESETUP_PIN AMSPins[]=
{
	{L"Input",             // Pin string name
    FALSE,                 // Is it rendered
    FALSE,                 // Is it an output
    FALSE,                 // Can we have none
    FALSE,                 // Can we have many
    &CLSID_NULL,           // Connects to filter
    L"Output",             // Connects to pin
    1,                     // Number of types
    &pinSubtypes           // Pin Media types
	}
};

const AMOVIESETUP_FILTER AMSFilter =
{
    &CLSID_Filter,  // Filter CLSID
    g_wszName,     // String name
    MERIT_DO_NOT_USE,      // Filter merit
    sizeof(AMSPins)/sizeof(AMSPins[0]),                     // Number pins
    AMSPins             // Pin details
};

// List of class IDs and creator functions for the class factory. This
// provides the link between the OLE entry point in the DLL and an object
// being created. The class factory will call the static CreateInstance
CFactoryTemplate g_Templates[] = 
{
    {
        g_wszName,
        &CLSID_Filter,
        CFilter::CreateInstance,
        NULL,
        &AMSFilter
    },
};

int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);
