#include "users_files_service.h"

BOOST_EXTENSION_TYPE_MAP_FUNCTION
{
	std::map<std::string, boost::extensions::factory<service> > &factories(types.get());
	factories["users_files_service"].set<users_files_service>();
}