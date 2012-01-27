#include "image_renderer_service.h"

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<base_service> > &factories(types.get());
	factories["image_renderer_service"].set<image_renderer_service>();
}