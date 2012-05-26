#ifndef NETWORK_INTERFACE_HPP
#define NETWORK_INTERFACE_HPP
// Boost
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

// Cloud Forever Service Interface
#include <shared_data.hpp>

class network_interface
{
public:
		virtual boost::shared_ptr<std::string> serialise( boost::shared_ptr<boost::asio::ip::tcp::socket> socket,  boost::shared_ptr<std::string> shared_data_str){ return boost::shared_ptr<std::string>();}
};

#endif // NETWORK_INTERFACE_HPP

