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

	void resize_coefs(const int original_w, const int original_h, int & new_w, int & new_h)
	{
		int num, den;
		if (new_w * original_h < new_h * original_w) {
			num = new_w;
			den = original_w;
		} else {
			num = new_h;
			den = original_h;
		}
		new_w = original_w * num / den;
		new_h = original_h * num / den;
	}
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

	std::string border_to_wkt(std::vector<cv::Point> & border)
	{
		std::stringstream wkt;
		int vobs = border.size();
		int vobs_less_one = vobs - 1;
		wkt << "(";
		for(int i = 0; i < vobs; ++i)
		{
			wkt <<  border[i].x << " " << border[i].y << ", ";
			//if(i != vobs_less_one)
			//      wkt  << ", ";
			if(i == vobs_less_one)
				wkt  <<         border[0].x << " " << border[0].y;

		}
		wkt << ")";
		return wkt.str();
	}

	std::string vector_object_to_WKT(vector_object &vo)
	{
		std::stringstream wkt;
		std::string result;
		wkt << "POLYGON (";
		wkt << border_to_wkt(vo.border);

		int vohs = vo.holes.size();

		if(vohs != 0)
			wkt  << ", ";
		else
		{
			wkt  << ")";
			return wkt.str();
		}

		int vohs_less_one = vohs - 1;
		for(int j = 0; j < vohs; ++j)
		{
			wkt << border_to_wkt(vo.holes[j]);
			if(j != vohs_less_one)
				wkt << ", ";
		}

		wkt  << ")";
		return  wkt.str();
	}

	void store_vector_hole(std::vector< std::vector<cv::Point> > &holes, std::vector< std::vector<cv::Point> > & contours, std::vector<cv::Vec4i> & hierarchy, const int & cid, std::vector<vector_object> & container );
	void store_vectror_countors(std::vector< std::vector<cv::Point> > & contours, std::vector<cv::Vec4i> & hierarchy, const int & cid , std::vector<vector_object> & container);

	void store_vector_hole(std::vector< std::vector<cv::Point> > &holes, std::vector< std::vector<cv::Point> > & contours, std::vector<cv::Vec4i> & hierarchy, const int & cid, std::vector<vector_object> & container )
	{
		holes.push_back(contours[cid]);
		if (hierarchy[cid][2] >= 0) // holes in holes == real poligons
		{
			store_vectror_countors( contours, hierarchy, hierarchy[cid][2], container);
		}
		if (hierarchy[cid][0] >= 0) // holes on same level of depth == another holes of this poligon
		{
			store_vector_hole(holes, contours, hierarchy, hierarchy[cid][0], container);
		}
		return;

	}

	void store_vectror_countors(std::vector< std::vector<cv::Point> > & contours, std::vector<cv::Vec4i> & hierarchy, const int & cid , std::vector<vector_object> & container)
	{
		if (hierarchy[cid][0]>= 0)
			store_vectror_countors(contours, hierarchy, hierarchy[cid][0], container);

		vector_object current;
		current.border = contours[cid];

		if ((hierarchy[cid][0]<= 0) && (hierarchy[cid][2] <= 0))
		{
			container.push_back(current);
			return;
		}

		if(hierarchy[cid][2] >= 0) // h
		{
			store_vector_hole(current.holes, contours, hierarchy, hierarchy[cid][2], container);
		}

		container.push_back(current);
		return;

	}

#ifndef FILL_UTILS_H
#define FILL_UTILS_H

	class fill_utils
	{
	public:
		fill_utils()
		{
			//rng.seed(static_cast<unsigned int>(std::time(0)));
			adder_ = static_cast<unsigned int>(std::time(0));
			hue_r = boost::shared_ptr<boost::random::uniform_real_distribution<float> >(new boost::random::uniform_real_distribution<float>(-3.1f,3.1f));
			sat_r = boost::shared_ptr<boost::random::uniform_real_distribution<float> >(new boost::random::uniform_real_distribution<float>(0.5f,1.0f/sqrt(2.0f)));
			lum_r = boost::shared_ptr<boost::random::uniform_real_distribution<float> >(new boost::random::uniform_real_distribution<float>(0.5f,0.7f));
		}

		cv::Scalar random_RGB_color( const int & class_name)
		{
			int red, green, blue;
			set_RGB(red, green, blue, class_name);
			cv::Scalar color( blue , green, red  );
			return color;
		}

		void set_RGB(int & red, int & green, int & blue, const int & class_name )
		{
			boost::mutex::scoped_lock lock(mut_);
			unsigned int class_name_ = class_name + adder_;
			rng.seed(class_name_);
			float hue = (*hue_r)(rng);// hue is an angle in radians (-Pi...Pi)
			float saturation =  (*sat_r)(rng);// for saturation the range 0...1/sqrt(2) equals 0% ... 100%
			float luminance =  (*lum_r)(rng);// luminance is in the range 0...1

			float u = cos( hue ) * saturation;
			float v = sin( hue ) * saturation;
			float r =  (luminance  + 1.139837398373983740  * v) * 255;
			float g = (luminance  - 0.3946517043589703515  * u - 0.5805986066674976801 * v) * 125;
			float b = (luminance + 2.03211091743119266 * u) * 255;

			red = r;
			green =g;
			blue = b;
		}
		std::string fill_rule(  const int & class_name )
		{ 

			int red, green, blue;
			set_RGB(red, green, blue, class_name);
			std::ostringstream rule;
			rule << "fill-rule:nonzero;fill-opacity:0.5;fill:rgb("
				<< red  << ","  << green << "," << blue
				<< ");stroke:rgb("
				<< (red - 5) << "," << (green - 5) << "," << (blue -5) 
				<<  ");stroke-width:2";
			return rule.str();
		}

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

		std::vector< filter_utils::opencv_vector_object > find_countors(std::vector<cv::Mat> & clustres)
		{
			std::vector< filter_utils::opencv_vector_object > result;

			BOOST_FOREACH(cv::Mat & filled, clustres )
			{
				if(cv::sum(filled).val[0] > 0.0)
				{
					filter_utils::opencv_vector_object o;
					findContours(filled, o.contours, o.hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_TC89_KCOS);
					result.push_back(o);
				}
				else
				{
					std::cout << "It's a black image, so I'm not going to do anything..." << std::endl;
				}
			}
			return result;

		}

		std::vector< std::vector<filter_utils::vector_object> > find_objects(std::vector< filter_utils::opencv_vector_object > & clustres)
		{
			std::vector< std::vector<filter_utils::vector_object> >  result;
			BOOST_FOREACH(filter_utils::opencv_vector_object & cluster, clustres)
			{
				std::vector<filter_utils::vector_object> o;
				filter_utils::store_vectror_countors(cluster.contours, cluster.hierarchy, 0, o);
				result.push_back(o);
			}
			return result;
		}

		std::string render_svg( std::vector< std::vector<filter_utils::vector_object> > & clusters, const int & w, const int & h)
		{
			std::ostringstream svg;

			{
				boost::geometry::svg_mapper<boost::geometry::model::d2::point_xy<double> > mapper(svg, w, h);

				std::vector < boost::geometry::model::multi_polygon< boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > > >  image;

				for (int j=0; j < clusters.size(); ++j)
				{

					boost::geometry::model::multi_polygon< boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > > class_pols;


					for (int i = 0; i < clusters[j].size(); ++i)
					{
						boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;
						std::string wkt = filter_utils::vector_object_to_WKT( clusters[j][i]);
						//std::cout << wkt << std::endl;
						boost::geometry::read_wkt(
							wkt, polygon);
						boost::geometry::correct(polygon);
						boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon2;
						boost::geometry::simplify(polygon, polygon2, 0.5);
						class_pols.push_back(polygon2);
						//class_pols.push_back(polygon);

					}
					image.push_back(class_pols);

				}

				for (int i = 0; i< image.size(); ++i)
				{
					mapper.add(image[i]);
				}

				for (int i = 0; i< image.size(); ++i)
				{
					mapper.map(image[i], fill_util->fill_rule(i) );
				}
			}

			return svg.str();
		}

		std::string render_opencv(const std::string & extension, std::vector< filter_utils::opencv_vector_object > & clusters,  const int & w, const  int  & h)
		{
			cv::Mat dst = cv::Mat::ones(  h, w, CV_8UC3);
			dst =   cv::Scalar(255, 255, 255);
			int iter_int=0;
			BOOST_FOREACH(filter_utils::opencv_vector_object & o, clusters)
			{
				cv::Scalar color= fill_util->random_RGB_color(iter_int);
				int idx = 0;
				for( ; idx >= 0; idx = o.hierarchy[idx][0] )
				{
					//std::cout << idx << " " <<  o.hierarchy[idx][0]  << " "  << o.hierarchy[idx][1] << " " <<  o.hierarchy[idx][2]  << std::endl;
					cv::drawContours( dst, o.contours, idx, color , CV_FILLED, 8, o.hierarchy );
				}
				++iter_int;
			}

			//cv::namedWindow( "Components", CV_WINDOW_AUTOSIZE );
			//cv::imshow( "Components", dst );
			// 
			std::vector<uchar> buff;

			if(extension == ".jpg")
			{
				std::vector<int> p;
				p.push_back(CV_IMWRITE_JPEG_QUALITY);
				p.push_back(90);
				cv::imencode(extension, dst, buff, p);
			}
			else
			{
				cv::imencode(extension, dst, buff);
			}
			std::ostringstream  file;
			util::send_data(file, buff);
			return file.str();
		}
		mask_utils( boost::shared_ptr<filter_utils::fill_utils> your_fill_utils)
		{
			fill_util = your_fill_utils;
		}
	private:
		boost::shared_ptr<filter_utils::fill_utils>  fill_util;
	};
#endif //MASK_UTILS_H
}





class image_renderer_service: public service
{ 
public:
	image_renderer_service()
	{
		fill_util = boost::shared_ptr<filter_utils::fill_utils>(new filter_utils::fill_utils());

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
				// api image_renderer.service?action=resize&from_format=jpg&from_url=absolut_url&to_format=png&w=200&h=200
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
						cv::Mat original;
						cv::Mat result;
						int sx, sy;
						int desired_w = boost::lexical_cast<int>(to_w->second);
						int desired_h = boost::lexical_cast<int>(to_h->second);
						std::string desired_ext = to_format->second;
						if (from_format->second == "mask")
						{
							std::stringstream in;

							in << external_server_response.body;
							filter_utils::mask_utils mask_util(fill_util);
							std::vector<cv::Mat> image;
							image = mask_util.load_source(in, desired_w, desired_h, 1, 2, 3);
							std::vector< filter_utils::opencv_vector_object > opencv_countors  = mask_util.find_countors(image);


							std::string encoded;
							if ((desired_ext == "svg")||(desired_ext == "SVG"))
							{
								std::vector< std::vector<filter_utils::vector_object> > boost_ready_countors = mask_util.find_objects(opencv_countors);
								encoded = mask_util.render_svg(boost_ready_countors, desired_w, desired_h);
							}
							else
								encoded = mask_util.render_opencv(std::string("."+ desired_ext), opencv_countors, desired_w, desired_h);

							http_utils::send(encoded, socket, response, request);

						}
						else
						{
							try
							{
								if (external_server_response.body == "")
								{
									throw std::runtime_error("bad or no such file!");
								}

								std::vector<char> data(external_server_response.body.begin(), external_server_response.body.end());
								original = cv::imdecode(data, 1);
								sy = original.rows;
								sx = original.cols;
								util::resize_coefs(sx, sy,desired_w, desired_h);
								result.create(cv::Size(desired_w, desired_h), original.type());
								cv::resize(original, result, result.size()  , 0,0 , CV_INTER_CUBIC );



							}
							catch(...)
							{
								http_utils::send_error( 500, "unable to read the external server file.", socket, response);
								return;
							}
						}

						std::vector<uchar> buff;
						if ((desired_ext == "jpg")||(desired_ext == "JPG")||(desired_ext == "JPEG")||(desired_ext == "jpeg"))
						{
							std::vector<int> p;
							p.push_back(CV_IMWRITE_JPEG_QUALITY);
							p.push_back(90);
							cv::imencode(".jpg", result, buff, p);
						}
						else
							cv::imencode(std::string("."+ desired_ext), result, buff);

						std::stringstream b2;
						util::send_data(b2, buff);
						http_utils::set_file_content_type(std::string("FILE." + desired_ext), response);
						http_utils::send(b2.str(), socket, response, request);
						return;
					}
					catch(...)
					{
						http_utils::send_error( 500, "unable to contact the external server.", socket, response);
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
	boost::shared_ptr<filter_utils::fill_utils>  fill_util;
	CLOUD_SERVICE_AUXILIARIES;


};

#endif // IMAGE_RENDERER_SERVICE
