// This file must include the only time in project. It contains specification
// for filter using in this project.

//Defines filter name. It is shown in list of filters in GraphEdit util.
static const WCHAR g_wszName[] = FILTER_WCHAR_NAME;

//Pin's type specification.
const AMOVIESETUP_MEDIATYPE pinSubtypes = 
{ 
    &MEDIATYPE_Video, 
    &MEDIASUBTYPE_NULL 
};

//Describes pins using in the filter
const AMOVIESETUP_PIN AMSPins[]=
{
	{L"Input",             // Pin string name
    FALSE,                 // Is it rendered
    FALSE,                  // Is it an output
    FALSE,                 // Can we have none
    FALSE,                 // Can we have many
    &CLSID_NULL,           // Connects to filter
    NULL,                  // Connects to pin
    1,                     // Number of types
    &pinSubtypes      // Pin Media types
	},
	{L"Output",             // Pin string name
    FALSE,                 // Is it rendered
    TRUE,                  // Is it an output
    FALSE,                 // Can we have none
    FALSE,                 // Can we have many
    &CLSID_NULL,           // Connects to filter
    NULL,                  // Connects to pin
    1,                     // Number of types
    &pinSubtypes      // Pin Media types
	}
};

//Describes filter parameters.
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

//Set list of filters using in the dll
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);
