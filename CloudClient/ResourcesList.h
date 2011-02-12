#pragma once
#include <string>
#include <vector>

using namespace std;

struct CameraDescription
{
	int idx;
	string description;
	string frendlyName;
};

class ResourcesList
{
private:
	static HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum );
	vector <CameraDescription> cameras;
public:
	//interface
	int EnumerateVideoDevices();
};