#ifndef HTTP_SERVICE_HPP
#define HTTP_SERVICE_HPP

#include <string>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

// Cloud Forever
#include <http.h>
#include <pointer_utils.h>
#include <base_service.hpp>

class http_service : public base_service
{
public:

	virtual std::string service_check(boost::shared_ptr<http_request>, boost::shared_ptr<shared>) = 0;

	virtual void service_call(boost::shared_ptr<boost::asio::ip::tcp::socket>, boost::shared_ptr<http_request>, boost::shared_ptr<shared>) = 0;

	virtual void serialize(boost::shared_ptr<boost::asio::ip::tcp::socket>, boost::shared_ptr<http_request> old_http_request, boost::shared_ptr<shared>, boost::shared_ptr<http_request> new_http_request){};

	virtual service_check_output make_service_check( service_check_input serialized_data)
	{
		boost::shared_ptr<shared> shared_data (new shared(), boost::bind(&pointer_utils::delete_ptr<shared>, _1));
		shared_data->deserialize(serialized_data.shared_data);

		boost::shared_ptr<http_request> request (new http_request(),  boost::bind(&pointer_utils::delete_ptr<http_request>, _1));
		request->deserialize_base(shared_data->get("http_request"));

		boost::shared_ptr<std::string> check_result(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
		try
		{
			*check_result = service_check(request, shared_data);
		}
		catch(std::exception &e)
		{
			boost::shared_ptr<std::string> err(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
			*err = std::string( e.what());
			service_check_output out;
			out.error_data = err;
			return out;
		}
		service_check_output out;
		out.call_me_as = check_result;
		out.shared_data = shared_data->serialize();
		return out;
	}

	virtual service_call_output make_service_call( service_call_input serialized_data)
	{
		
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket = serialized_data.socket;

		boost::shared_ptr<shared> shared_data (new shared(), boost::bind(&pointer_utils::delete_ptr<shared>, _1));
		shared_data->deserialize(serialized_data.shared_data);

		boost::shared_ptr<http_request> request (new http_request(),  boost::bind(&pointer_utils::delete_ptr<http_request>, _1));
		request->deserialize_base(shared_data->get("http_request"));

		try
		{
			service_call(socket, request, shared_data);
		}
		catch(std::exception &e)
		{
			boost::shared_ptr<std::string> err(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
			*err = std::string( e.what());
			service_call_output out;
			out.error_data = err;
			return out;
		}
		service_call_output out;
		shared_data->update("http_request", request->serialize_base());
		out.shared_data = shared_data->serialize();
		return out;
	}

	virtual service_call_input do_serialize( service_call_input serialized_data) {

		boost::shared_ptr<boost::asio::ip::tcp::socket> socket = serialized_data.socket;

		boost::shared_ptr<shared> shared_data (new shared(), boost::bind(&pointer_utils::delete_ptr<shared>, _1));
		shared_data->deserialize(serialized_data.shared_data);

		boost::shared_ptr<http_request> request (new http_request(),  boost::bind(&pointer_utils::delete_ptr<http_request>, _1));
		
		std::string http_request_str = shared_data->get("http_request");

		if(!http_request_str.empty())
			request->deserialize_base(shared_data->get("http_request"));
		else
			shared_data->post("http_request", request->serialize_base(), true);

		boost::shared_ptr<http_request> new_request (new http_request(),  boost::bind(&pointer_utils::delete_ptr<http_request>, _1));
		
		std::string new_http_request_str = shared_data->get("new_http_request");

		if(!new_http_request_str.empty())
			new_request->deserialize_base(new_http_request_str);
		else
			shared_data->post("new_http_request", new_request->serialize_base(), true);

		try
		{
			serialize(socket, request, shared_data, new_request);
		}
		catch(std::exception &e)
		{
			boost::shared_ptr<std::string> err(new std::string(""), boost::bind(&pointer_utils::delete_ptr<std::string>, _1));
			*err = std::string( e.what());
			service_call_input out;
			out.error_data = err;
			return out;
		}
		service_call_input out;
		shared_data->update("http_request", request->serialize_base());
		shared_data->update("new_http_request", new_request->serialize_base());
		out.shared_data = shared_data->serialize();
		return out;
	}

	void set_network(boost::shared_ptr<network_interface> network){	this->network = network; }
	void network_serialise( boost::shared_ptr<boost::asio::ip::tcp::socket> socket,  boost::shared_ptr<shared> shared_data)
	{
		 boost::shared_ptr<std::string> shared_data_str(new std::string(""), boost::bind(&base_service_utils::delete_ptr<std::string>, _1));
		 shared_data_str = shared_data->serialize();
		 boost::shared_ptr<std::string> shared_data_result_str(new std::string(""), boost::bind(&base_service_utils::delete_ptr<std::string>, _1));
		 shared_data_result_str = network->serialise(socket, shared_data_str);
		 shared_data->deserialize(shared_data_result_str);
	}

	private:
	boost::shared_ptr<network_interface> network;
};
#endif // HTTP_SERVICE_HPP