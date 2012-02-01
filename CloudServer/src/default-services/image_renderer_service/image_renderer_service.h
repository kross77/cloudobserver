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
#include <timer.h>

//SERVICE INTERFACE
#include <service.hpp>

namespace util
{
	template < class T>
	void send_data(T & o, const std::vector<uchar> & v)
	{
		std::copy( v.begin(), v.end(), std::ostream_iterator<uchar>(o) );
	}

	void resize_coefs(const int original_w, const int original_h, int & new_w, int & new_h);
}


namespace filter_utils
{
	struct opencv_vector_object
	{
		std::vector< std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
	};

	struct vector_object
	{
		std::vector<cv::Point> border;
		std::vector< std::vector<cv::Point> > holes;
	};

	std::string border_to_wkt(std::vector<cv::Point> & border);

	std::string vector_object_to_WKT(vector_object &vo);

	void store_vector_hole(std::vector< std::vector<cv::Point> > &holes, std::vector< std::vector<cv::Point> > & contours, std::vector<cv::Vec4i> & hierarchy, const int & cid, std::vector<vector_object> & container );
	
	void store_vectror_countors(std::vector< std::vector<cv::Point> > & contours, std::vector<cv::Vec4i> & hierarchy, const int & cid , std::vector<vector_object> & container);

#ifndef FILL_UTILS_H
#define FILL_UTILS_H

	class fill_utils
	{
	public:
		fill_utils();

		cv::Scalar random_RGB_color( const int & class_name);

		void set_RGB(int & red, int & green, int & blue, const int & class_name );
		
		std::string fill_rule(  const int & class_name );

	private:
		int adder_;
		mutable boost::mutex mut_;
		boost::random::mt19937 rng;  
		boost::shared_ptr<boost::random::uniform_real_distribution<float> > hue_r;
		boost::shared_ptr<boost::random::uniform_real_distribution<float> > lum_r;
		boost::shared_ptr<boost::random::uniform_real_distribution<float> > sat_r;

	};

#endif // FILL_UTILS_H
#ifndef MASK_UTILS_H
#define MASK_UTILS_H
	class mask_utils
	{
	public:
		template < class T>
		std::vector<cv::Mat> load_source( T & in, int & w, int & h, const int & X, const int & Y, const int & Z)
		{
			timer local_sub_timer;
			local_sub_timer.restart();
			int sx, sy;

			in.read(reinterpret_cast<char*>(&sy), sizeof(int));
			in.read(reinterpret_cast<char*>(&sx), sizeof(int));

			if ((sy <= 0) || (sx <= 0))
			{
				throw std::runtime_error("bad or no such file!");
			}
			std::vector< std::vector<unsigned char> > image(sy); // to array

			//std::cout << std::endl <<  "reading .mask file" << std::endl;
			//      boost::progress_display show_progress0( sy);
			for(int i =0; i < sy; ++i)
			{
				std::vector<unsigned char> row(sx);
				in.read(reinterpret_cast<char*>(&row[0]), sx);
				image[i] = row; // remove copy paste
			}

			/////////////////////////////
			//std::cout << "read file into vec-vec in: " << local_sub_timer.elapsed() <<  std::endl;

			std::map<unsigned char , cv::Mat* > clusters;
			local_sub_timer.restart();
			for(int i =0; i < sy; ++i)
			{
				for(int j =0; j < sx; ++j)
				{
					unsigned char current_k = image[i][j];
					if (clusters[current_k] == NULL){
						clusters[current_k] = new cv::Mat();
						(*clusters[current_k]) = cv::Mat::zeros(cv::Size(sx, sy), CV_8UC1);
					}
					(*clusters[current_k]).row(i).col(j) = 255;
				}
			}
			//std::cout << "created a mat for each cluster in: " << local_sub_timer.elapsed() <<  std::endl;
			local_sub_timer.restart();
			std::vector<cv::Mat> result;
			std::cout << "\t Desired image" << std::endl << "\t\t width: " << w << std::endl << "\t\t height: " << h << std::endl << std::endl;
			util::resize_coefs(sx, sy, w, h);
			std::cout << "\t Image original" << std::endl << "\t\t width: " << sx << std::endl << "\t\t height: " << sy << std::endl  <<  "\t Image that will be returned:" << std::endl  << "\t\t width: " << w << std::endl << "\t\t height: " << h << std::endl << std::endl;
			for( std::map<unsigned char , cv::Mat*>::iterator it = clusters.begin(); it != clusters.end(); ++it )
			{

				cv::Mat filled(cv::Size(w, h), (*it->second).type());
				cv::resize((*it->second), filled, filled.size()  , 0,0 , CV_INTER_CUBIC );

				cv::threshold( filled, filled, 1, 255, CV_THRESH_BINARY );
				result.push_back(filled);
			}

			return result;
		}

		std::vector< filter_utils::opencv_vector_object > find_countors(std::vector<cv::Mat> & clustres);

		std::vector< std::vector<filter_utils::vector_object> > find_objects(std::vector< filter_utils::opencv_vector_object > & clustres);

		std::string render_svg( std::vector< std::vector<filter_utils::vector_object> > & clusters, const int & w, const int & h);

		std::string render_opencv(const std::string & extension, std::vector< filter_utils::opencv_vector_object > & clusters,  const int & w, const  int  & h);
		
		mask_utils( boost::shared_ptr<filter_utils::fill_utils> your_fill_utils);
	private:
		boost::shared_ptr<filter_utils::fill_utils>  fill_util;
	};
#endif //MASK_UTILS_H
}

class image_renderer_service: public http_service
{ 
public:
	image_renderer_service();

	virtual std::string service_check(boost::shared_ptr<http_request> request, boost::shared_ptr<shared> shared_data);

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, boost::shared_ptr<http_request> request,  boost::shared_ptr<shared> shared_data);

	virtual void apply_config(boost::shared_ptr<boost::property_tree::ptree> config){}

	virtual void start(){}

	virtual void stop(){}

private:
	boost::shared_ptr<filter_utils::fill_utils>  fill_util;
};

#endif // IMAGE_RENDERER_SERVICE
