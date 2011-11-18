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

//This file is stored in 3rdparty folder, it differs from original Boost.Trunk
#include <boost/geometry/extensions/io/svg/svg_mapper.hpp>

//OpenCV
#include <opencv2/opencv.hpp>

//CF-UTIL
#include <util.h>

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
	class fill_utils
	{
	public:
		fill_utils()
		{
			rng.seed(static_cast<unsigned int>(std::time(0)));
			hue_r = boost::shared_ptr<boost::random::uniform_real_distribution<float> >(new boost::random::uniform_real_distribution<float>(-3.1f,3.1f));
			sat_r = boost::shared_ptr<boost::random::uniform_real_distribution<float> >(new boost::random::uniform_real_distribution<float>(0.5f,1.0f/sqrt(2.0f)));
			lum_r = boost::shared_ptr<boost::random::uniform_real_distribution<float> >(new boost::random::uniform_real_distribution<float>(0.5f,0.7f));
		}

		cv::Scalar random_RGB_color()
		{
			int red, green, blue;
			set_RGB(red, green,blue);
			cv::Scalar color( red, green, blue );
			return color;
		}

		void set_RGB(int & red, int & green, int & blue  )
		{
			float hue = (*hue_r)(rng);// hue is an angle in radians (-Pi...Pi)
			float saturation =  (*sat_r)(rng);// for saturation the range 0...1/sqrt(2) equals 0% ... 100%
			float luminance =  (*lum_r)(rng);// luminance is in the range 0...1

			float u = cos( hue ) * saturation;
			float v = sin( hue ) * saturation;
			float r =  (luminance  + 1.139837398373983740  * v) * 255;
			float g = (luminance  - 0.3946517043589703515  * u - 0.5805986066674976801 * v) * 255;
			float b = (luminance + 2.03211091743119266 * u) * 255;

			red = r;
			green =g;
			blue = b;
		}
		std::string fill_rule()
		{ 
			int red, green, blue;
			set_RGB(red, green,blue);
			std::ostringstream rule;
			rule << "fill-rule:nonzero;fill-opacity:0.5;fill:rgb("
				<< red  << ","  << green << "," << blue
				<< ");stroke:rgb("
				<< (red - 5) << "," << (green - 5) << "," << (blue -5) 
				<<  ");stroke-width:2";
			return rule.str();
		}

	private:
		boost::random::mt19937 rng;  
		boost::shared_ptr<boost::random::uniform_real_distribution<float> > hue_r;
		boost::shared_ptr<boost::random::uniform_real_distribution<float> > lum_r;
		boost::shared_ptr<boost::random::uniform_real_distribution<float> > sat_r;

	};
}

boost::shared_ptr<filter_utils::fill_utils>  fill_util;

std::vector<cv::Mat> load_source( const std::string & file_name, int & w, int & h)
{
	timer local_sub_timer;
	local_sub_timer.restart();
	int sx, sy;


	//read image
	std::ifstream in(file_name.c_str(), std::ios_base::in | std::ios_base::binary);

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

		//cv::Mat filled_t(cv::Size(w, h), black.type());
		//cv::resize(black, filled_t, filled_t.size(), 0,0 , CV_INTER_CUBIC );
		//cv::Mat del(cv::Size(3, 3), CV_8UC1);
		//del.setTo(cv::Scalar(1));
		//cv::dilate(filled_t, filled, del);

		cv::threshold( filled, filled, 1, 255, CV_THRESH_BINARY );
		result.push_back(filled);
	}
	//std::cout << "resized each cluster mat in: " << local_sub_timer.elapsed() <<  std::endl;

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
			mapper.map(image[i], fill_util->fill_rule() );
		}
	}

	return svg.str();
}

std::string render_opencv(const std::string & extension, std::vector< filter_utils::opencv_vector_object > & clusters,  const int & w, const  int  & h)
{
	cv::Mat dst = cv::Mat::ones(  h, w, CV_8UC3);
	dst =   cv::Scalar(255, 255, 255);

	BOOST_FOREACH(filter_utils::opencv_vector_object & o, clusters)
	{
		cv::Scalar color= fill_util->random_RGB_color();
		int idx = 0;
		for( ; idx >= 0; idx = o.hierarchy[idx][0] )
		{
			//std::cout << idx << " " <<  o.hierarchy[idx][0]  << " "  << o.hierarchy[idx][1] << " " <<  o.hierarchy[idx][2]  << std::endl;
			cv::drawContours( dst, o.contours, idx, color , CV_FILLED, 8, o.hierarchy );
		}

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

int main(  )
{

	timer totall_timer;
	totall_timer.restart();
	fill_util = boost::shared_ptr<filter_utils::fill_utils>( new filter_utils::fill_utils());
	int w, h;


	std::cout << "Please input desired result width." << std::endl;
	do
	{
		std::cout << "Your choice: ";
		std::string line;
		std::getline(std::cin, line);
		try
		{
			w = boost::lexical_cast<int>(line);
		}
		catch (boost::bad_lexical_cast&)
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
	} while ((w <= 0) || (w > 20000));

	std::cout << "Please input desired result height." << std::endl;
	do
	{
		std::cout << "Your choice: ";
		std::string line;
		std::getline(std::cin, line);
		try
		{
			h = boost::lexical_cast<int>(line);
		}
		catch (boost::bad_lexical_cast&)
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
	} while ((h <= 0) || (h > 20000));

	timer local_timer;
	std::vector<cv::Mat> image;

	std::string file_name;
	std::cout << "Please input desired file name. \n(for example nimfa.mask)" << std::endl;
	bool selected=false;
	do
	{
		std::cout << "Your choice: ";
		std::string line;
		std::getline(std::cin, line);
		try
		{
			file_name = boost::lexical_cast<std::string>(line);
			local_timer.restart();
			image = load_source(file_name.c_str(), w, h);
			selected = true;
		}
		catch (...)
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
	} while (!selected);

	std::cout << "read image in: " << local_timer.elapsed() << std::endl;


	local_timer.restart();
	std::vector< filter_utils::opencv_vector_object > opencv_countors  = find_countors(image);
	std::cout << "found countours via OpenCV in: " << local_timer.elapsed() << std::endl;

	local_timer.restart();

	if (file_name.length() > 5)
		file_name = file_name.substr(0, file_name.length() - 5);

	general_utils::create_directory("rendered");

	std::string out_file_name = "rendered/" + file_name + ".w-" + boost::lexical_cast<std::string>(w) +".h-" + boost::lexical_cast<std::string>(h);

	std::ofstream jpeg_file( std::string( out_file_name + ".jpg").c_str(),  std::stringstream::binary);
	std::string jpg = render_opencv(".jpg", opencv_countors, w, h);
	jpeg_file << jpg;
	jpeg_file.close();
	std::cout << "rendered out a JPEG image: " << out_file_name <<".jpg in: " << local_timer.elapsed() << std::endl;

	{
		std::ofstream zip_png_file( std::string( out_file_name + ".jpg" + ".gz").c_str(),  std::ofstream::binary);
		boost::iostreams::filtering_streambuf< boost::iostreams::input> in;
		in.push( boost::iostreams::gzip_compressor());
		std::stringstream data;
		data << jpg;
		in.push(data);
		boost::iostreams::copy(in, zip_png_file);
	}

	local_timer.restart();
	std::ofstream png_file( std::string( out_file_name + ".png").c_str(),  std::stringstream::binary);
	std::string png =  render_opencv(".png", opencv_countors, w, h);
	png_file << png;
	png_file.close();
	std::cout << "rendered out a PNG image: " << out_file_name <<".png  in: " << local_timer.elapsed() << std::endl;

	{
		std::ofstream zip_png_file( std::string( out_file_name + ".png" + ".gz").c_str(),  std::ofstream::binary);
		boost::iostreams::filtering_streambuf< boost::iostreams::input> in;
		in.push( boost::iostreams::gzip_compressor());
		std::stringstream data;
		data << png;
		in.push(data);
		boost::iostreams::copy(in, zip_png_file);
	}

	local_timer.restart();
	std::vector< std::vector<filter_utils::vector_object> > boost_ready_countors = find_objects(opencv_countors);
	std::cout << "formated countours for boost::geometry in: " << local_timer.elapsed() << std::endl;

	local_timer.restart();
	std::ofstream svg_file( std::string( out_file_name + ".svg").c_str(),  std::stringstream::binary);
	std::string svg = render_svg(boost_ready_countors, w,h);
	svg_file <<  svg;

	svg_file.close();
	std::cout << "rendered out a SVG image: " << out_file_name <<".svg  in: " << local_timer.elapsed() << std::endl;

	{
		std::ofstream zip_png_file( std::string( out_file_name + ".svg" + ".gz").c_str(),  std::ofstream::binary);
		boost::iostreams::filtering_streambuf< boost::iostreams::input> in;
		in.push( boost::iostreams::gzip_compressor());
		std::stringstream data;
		data << svg;
		in.push(data);
		boost::iostreams::copy(in, zip_png_file);
	}

	std::cout << "All ready in: " << totall_timer.elapsed() << std::endl;


	std::ofstream html_file( "rendered/preview.html");

	if (out_file_name.length() > 9) // "rendered/"
		out_file_name = out_file_name.substr(9, out_file_name.length());


	html_file <<  "<html>\n<head><head><body><h1>JPG - "<< jpg.size() <<"</h1><img src=\"" << out_file_name <<".jpg\"><br/><h1>PNG - "<< png.size() <<"</h1><img src=\"" << out_file_name << ".png\" ><br/><h1>SVG - "<< svg.size() <<"</h1><img src=\"" << out_file_name << ".svg\" ></body></html>" << std::endl;
	html_file.close();
	std::cout << "Created HTML that shows all 3 images: rendered/preview.html" << std::endl;

	std::cin.get();
	return 0;
}
