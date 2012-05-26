#include <network_interface.hpp>
#include <boost/shared_ptr.hpp>
#include "server_utils.h"

class server_network : public network_interface
{
public:
	server_network(boost::shared_ptr<server_utils::server_description> host_description)
	{
		this->host_description = host_description;
	}

	virtual boost::shared_ptr<std::string> serialise( boost::shared_ptr<boost::asio::ip::tcp::socket> socket,  boost::shared_ptr<std::string> shared_data_str) 
	{
		boost::shared_ptr<std::string> heap_shared_data_str(new std::string(""), boost::bind(&base_service_utils::delete_ptr<std::string>, _1));
		heap_shared_data_str = shared_data_str;
		boost::shared_ptr<shared> shared_data(new shared());
		shared_data->deserialize(heap_shared_data_str);
		// todo:serialize direction up down from(int i)
		std::list<int>::iterator order_it;
		boost::shared_ptr<server_utils::service_container> service_cont;

		for (order_it= host_description->services_ids.begin(); order_it!= host_description->services_ids.end(); ++order_it)
		{
			service_cont =  host_description->service_map[*order_it];
			boost::shared_ptr<base_service> requested_service = service_cont->service_ptr;
				try
				{
					service_call_input data;
					data.socket = socket;			
					data.shared_data = shared_data->serialize();

					service_call_input service_output;

					service_output.shared_data = data.shared_data;

					service_output = requested_service->do_serialize(data);

					if ((*(service_output.error_data)) != "")
					{
						return heap_shared_data_str;
					}
					shared_data->deserialize(service_output.shared_data);
				}
				catch(...)
				{}


			}
		boost::shared_ptr<std::string> heap_shared_data_str_result(new std::string(""), boost::bind(&base_service_utils::delete_ptr<std::string>, _1));
		heap_shared_data_str_result  = shared_data->serialize();
		return heap_shared_data_str_result;
		
	}

private:
	boost::shared_ptr<server_utils::server_description> host_description;
};