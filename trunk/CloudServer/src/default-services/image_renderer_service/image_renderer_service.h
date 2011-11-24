#ifndef IMAGE_RENDERER_SERVICE_H
#define IMAGE_RENDERER_SERVICE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <iterator>
#include <math.h>

//Boost
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/progress.hpp>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/multi/geometries/multi_polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/stream.hpp>

// Boost Extension
#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

//This file is stored in 3rdparty folder, it differs from original Boost.Trunk
#include <boost/geometry/extensions/io/svg/svg_mapper.hpp>

//OpenCV
#include <opencv2/opencv.hpp>

//CF-UTIL
#include <general_utils.h>

//SERVICE INTERFACE
#include <service.hpp>


class image_renderer_service: public service
{ 
public:
	image_renderer_service(){}

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
	{
		response->body = "hello image renderer service";
		response->headers.insert(std::pair<std::string, std::string>("Content-Length", boost::lexical_cast<std::string>(response->body.length())));
		response->send(*socket);
	}

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config){}

	virtual void start(){}
	virtual void stop(){}

private:


	CLOUD_SERVICE_AUXILIARIES;


};

#endif // IMAGE_RENDERER_SERVICE
