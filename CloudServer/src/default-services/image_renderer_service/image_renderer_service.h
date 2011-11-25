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
#include <http_utils.h>

//SERVICE INTERFACE
#include <service.hpp>


class image_renderer_service: public service
{ 
public:
	image_renderer_service()
	{
		http_util = boost::shared_ptr<http_utils>(new http_utils());
	}

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request, boost::shared_ptr<http_response> response)
	{
		typedef std::map<std::string, std::string> map_ss;
		typedef std::pair<std::string, std::string> pair_ss;

		map_ss::iterator it = request->arguments.find("action");

		if (it != request->arguments.end())
		{
			if (it->second == "resize")
			{
				// api image_renderer.service?from_format=jpg&from_url=absolut_url&to_format=png&w=200&h=200
				map_ss::iterator from_format = request->arguments.find("from_format");
				map_ss::iterator from_url = request->arguments.find("from_url");
				map_ss::iterator to_format = request->arguments.find("to_format");
				map_ss::iterator to_w = request->arguments.find("w");
				map_ss::iterator to_h = request->arguments.find("h");
				if((from_format != request->arguments.end())&&(from_url != request->arguments.end())&&(to_format != request->arguments.end())&&(to_w != request->arguments.end())&&(to_h != request->arguments.end()))
				{
						http_request request_to_external_server;
						request_to_external_server.headers.insert(pair_ss("Connection","close"));
						request_to_external_server.method = "GET";

						http_response external_server_response;
						try
						{
							boost::asio::io_service io_service_;
							boost::asio::ip::tcp::socket socket_(io_service_);
							external_server_response.receive(request_to_external_server.send(from_url->second, socket_));
							http_util->send(external_server_response.body, socket, response);
							return;
						}
						catch(...)
						{
							http_util->send_error( 500, "unable to contact the external server.", socket, response);
							return;
						}
				}
			}
		}
		

		response->body = "hello image renderer service";
		response->headers.insert(pair_ss("Content-Length", boost::lexical_cast<std::string>(response->body.length())));
		response->send(*socket);
	}

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config){}

	virtual void start(){}
	virtual void stop(){}

private:
	boost::shared_ptr<http_utils> http_util;

	CLOUD_SERVICE_AUXILIARIES;


};

#endif // IMAGE_RENDERER_SERVICE
