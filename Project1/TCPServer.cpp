#include <boost/asio.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <thread>

#if _WIN32_WINNT <= 0x0502
#define BOOST_ASIO_DISABLE_IOCP
#define BOOST_ASIO_ENABLE_CANCELIO
#endif

using namespace boost;

namespace my {

	//template<class T, class Allocator = std::allocator<T>>
	template<class T>
	class Result {
	public:
		//explicit Result(T t) : t(t) {}
		Result(T t, system::system_error& ec = system::system_error(system::error_code())) : data(t), ec(ec) {}

		Result(const Result& src) : data(src.data), ec(src.ec) {}
		const Result& operator=(const Result& src) {
			data = src.data;
			ec = src.ec;
		}

		Result(Result&& rhs) {
			data = std::move(rhs.data);
			ec = std::move(rhs.ec);
		}

		Result&& operator=(Result&& rhs) {
			data = std::move(rhs.data);
			ec = std::move(rhs.ec);
		}

		T getData() {
			return data;
		}

		void setData(T t) {
			data = t;
		}

		system::system_error getErrorCode() {
			return ec;
		}

		void setErrorCode(system::system_error& _ec) {
			ec = _ec;
		}

	private:
		T data;
		system::system_error ec;
	};

}

namespace mmy {
	int a;
	int b;
}

namespace my {
	//template<T>
	class StringResult : my::Result<std::string> {
	public:
		//explicit StringResult(const std::string& msg) : Result::Result(msg) {}
		//explicit StringResult(const char* msg) : Result::Result(msg) {}
		explicit StringResult(const std::string& msg, system::system_error& ec = system::system_error(system::error_code())) : Result::Result(msg, ec) {}
	};
}


using namespace my;

int startTcpService(unsigned short port_num = 3333) {

	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);

	asio::io_service ios;

	asio::ip::tcp::acceptor acceptor(ios, ep.protocol());

	boost::system::error_code ec;

	acceptor.bind(ep, ec);

	if (ec.value() != 0) {
		std::cout << "Failed to bind the acceptor socket!" << "Error Code = "
			<< ec.value() << ", Message = " << ec.message() << ", Port = " << port_num;
		return ec.value();
	}

	return EXIT_SUCCESS;
}

int connectTcp(const char* hostName = "127.0.0.1", const unsigned short portNo = 3333) {
	
	try {

	asio::ip::tcp::endpoint ep(asio::ip::address::from_string(hostName), portNo);

	asio::io_service ios;

	asio::ip::tcp::socket sock(ios, ep.protocol());

	sock.connect(ep);

	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code() << ", Message = " << e.what();
		return e.code().value();
	}

	return EXIT_SUCCESS;
	
}

int connectTcps(const std::string& hostName = "127.0.0.1", const std::string& portNo = "3333") {

	asio::io_service ios;

	asio::ip::tcp::resolver::query resolver_query(hostName, 
		portNo, 
		asio::ip::tcp::resolver::query::numeric_service);

	asio::ip::tcp::resolver resolver(ios);

	try {

		asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query);

		asio::ip::tcp::socket sock(ios);

		asio::connect(sock, it);

	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error Code = " << e.code() << ", Message = " << e.what();
		return e.code().value();
	}
	return EXIT_SUCCESS;
}

int startTcpServices(const unsigned short portNo = 3333, const int backLogSize = 30) {
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), portNo);

	asio::io_service ios;

	try {
		asio::ip::tcp::acceptor acceptor(ios, ep.protocol());

		acceptor.bind(ep);

		acceptor.listen(backLogSize);

		asio::ip::tcp::socket sock(ios);

		acceptor.accept(sock);

	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error Code = " << e.code() << ", Message = " << e.what();
		return e.code().value();
	}
	return EXIT_SUCCESS;
}

int send(const char* msg = "Hello", void* s = nullptr) {

	std::string buf;

	buf = msg;

	asio::const_buffers_1 output_buf = asio::buffer(msg, strlen(msg));

	return EXIT_SUCCESS;
}

int receive(std::string& str, void* s) {

	const size_t BUF_SIZE_BYTES = 20;

	std::unique_ptr<char[]> buf(new char[BUF_SIZE_BYTES]);

	asio::mutable_buffers_1 input_buf = asio::buffer(static_cast<void*>(buf.get()), BUF_SIZE_BYTES);

	return EXIT_SUCCESS;
}


int startUdpService(unsigned short portNo) {
	asio::ip::udp::endpoint ep(asio::ip::address_v4::any(), portNo);

	asio::io_service ios;

	asio::ip::udp::socket sock(ios, ep.protocol());

	boost::system::error_code ec;

	sock.bind(ep, ec);

	if (ec.value() != 0) {
		std::cout << "Failed to bind the socket." << "Error code = " << ec.value() << ", Message = " << ec.message();

		return ec.value();
	}

	return EXIT_SUCCESS;
}

int a2i(const char* s) {
	int sign;
	int sum;

	sign = ('-' == *s) ? -1 : 1;
	sum = 0;
	while (s) {
		sum = sum*10 + (*s - '0');
		s++;
	}
	return sum;
}

void writeToSocket(asio::ip::tcp::socket& sock) {
	std::string buf = "hello";

	std::size_t total_bytes_written = 0;

	while (total_bytes_written != buf.length()) {
		total_bytes_written += sock.write_some(asio::buffer(buf.c_str() + total_bytes_written,
			buf.length() - total_bytes_written));
	}
}

void writeToScketEnhanced(asio::ip::tcp::socket& sock) {
	std::string buf = "Hello";

	asio::write(sock, asio::buffer(buf));
}

std::string readFromSocket(asio::ip::tcp::socket& sock) {
	const unsigned char MESSAGE_SIZE = 7;
	char buf[MESSAGE_SIZE];
	std::size_t total_bytes_read = 0;

	while (total_bytes_read != MESSAGE_SIZE) {
		total_bytes_read += sock.read_some(asio::buffer(buf + total_bytes_read, 
			MESSAGE_SIZE - total_bytes_read));
	}
	return std::string(buf);
}

int createTcpSocket(const std::string& host = "127.0.0.1", const unsigned short portNo = 3333) {
	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(host), portNo);

		asio::io_service ios;

		asio::ip::tcp::socket sock(ios, ep.protocol());

		sock.connect(ep);

		writeToSocket(sock);
	}
	catch (system::system_error& e) {
		std::cout << "Error occured!. Error Code = " << e.code() << ", Message = " << e.what();
		return e.code().value();
	}
	return EXIT_SUCCESS;
}

//template<T>
Result<std::string> createSockNRead(const std::string host = "127.0.0.1", const unsigned short portNo = 3333) {
	std::string rcvStr;
	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(host), portNo);

		asio::io_service ios;

		asio::ip::tcp::socket sock(ios, ep.protocol());

		sock.connect(ep);

		rcvStr = readFromSocket(sock);
		
		return Result<std::string>(rcvStr, system::system_error(system::error_code()));
	}
	catch (system::system_error& e) {
		std::cout << "Error occured!, Error Code = " << e.code() << ", Message = " << e.what();
		return Result<std::string>(std::string(""), e);
	}
}

// Async Tcp Write
struct Session {
	std::shared_ptr<asio::ip::tcp::socket> sock;
	std::string buf;
	std::size_t total_bytes_written;

	std::unique_ptr<char[]> readBuf;
	std::size_t total_bytes_read;
	unsigned int readBufSize;
};

void cbWriteTcpAsync(const boost::system::error_code& ec,
	std::size_t bytes_transferred,
	std::shared_ptr<Session> s) {
	if (ec.value() != 0) {
		std::cout << "Enter occured!. Error Code = " << ec.value()
			<< ", Message = " << ec.message();
		return;
	}

	s->total_bytes_written += bytes_transferred;

	if (s->total_bytes_written == s->buf.length()) {
		return;
	}
	s->sock->async_write_some(asio::buffer(s->buf.c_str() + s->total_bytes_written,
		s->buf.length() - s->total_bytes_written),
		std::bind(cbWriteTcpAsync, std::placeholders::_1, std::placeholders::_2, 
			s));
}

void writeToSocketAsync(std::shared_ptr<asio::ip::tcp::socket> sock) {
	std::shared_ptr<Session> s(new Session);

	s->buf = std::string("Hello");
	s->total_bytes_written = 0;
	s->sock = sock;

	s->sock->async_write_some(
		asio::buffer(s->buf),
		std::bind(cbWriteTcpAsync,
			std::placeholders::_1,
			std::placeholders::_2,
			s));
}

int writeAsyncTcp(const std::string& host, const unsigned short& portNo = 3333, const std::string& msg = "Hello") {

	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(host), 
						portNo);

		asio::io_service ios;

		std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(ios, ep.protocol()));

		sock->connect(ep);

		writeToSocketAsync(sock);

		ios.run();
	}
	catch (system::system_error& e) {
		std::cout << "Error occured!. Error Code=" << e.code() << ", Message = " << e.what();
		return e.code().value();
	}

	return EXIT_SUCCESS;
}

void cbReadTcpAsync(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s) {
	if (ec.value() != 0) {
		std::cout << "Error occured!, Error Code = " << ec.value() << ", Message = " << ec.message();
		return;
	}

	s->total_bytes_read += bytes_transferred;

	if (s->total_bytes_read >= s->readBufSize) return;

	s->sock->async_read_some(
		asio::buffer(s->readBuf.get() + s->total_bytes_read,
			s->readBufSize - s->total_bytes_read),
		std::bind(cbReadTcpAsync, std::placeholders::_1, std::placeholders::_2, s));
}

void readFromTcpSocketAsync(std::shared_ptr<asio::ip::tcp::socket> sock) {
	const unsigned int MESSAGE_SIZE = 7;

	std::shared_ptr<Session> s(new Session());

	s->readBuf.reset(new char[MESSAGE_SIZE]);

	s->total_bytes_read = 0;
	s->sock = sock;
	s->readBufSize = MESSAGE_SIZE;

	s->sock->async_read_some(asio::buffer(s->readBuf.get(), s->readBufSize),
		std::bind(cbReadTcpAsync, 
			std::placeholders::_1, 
			std::placeholders::_2, 
			s));
}

StringResult connectAndReadTcpAsync(const std::string& host = "127.0.0.1", const unsigned short portNo = 3333) {
	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(host), portNo);

		asio::io_service ios;

		std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(ios, ep.protocol()));

		sock->connect(ep);

		readFromTcpSocketAsync(sock);
	}
	catch (boost::system::system_error& e) {
		std::cout << "Error occured!. Error Code = " << e.code() << ", Message=" << e.what();
		return StringResult(e.what(), e);
	}
	return StringResult("OK");
}

int connectTcp(const std::string& host = "127.0.0.1", const unsigned short& portNo = 3333) {
	try {
		asio::ip::tcp::endpoint  ep(asio::ip::address::from_string(host), portNo);

		asio::io_service ios;

		std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(ios, ep.protocol()));

		sock->async_connect(ep, [&sock](const boost::system::error_code& ec) {
			if (ec.value() != 0) {
				if (ec == asio::error::operation_aborted) {
					std::cout << "Operation canceled";
				}
				else {
					std::cout << "Error occured!, Error Code = " << ec.value() << ", Message=" << ec.message();
				}
			}
			else {
				// TODO : connect hear..



			}
		});

		std::thread worker_thread([&ios]() {
			try {
				ios.run();
			}
			catch (boost::system::system_error& e) {
				std::cout << "Error occured!, Error Code = " << e.code() << ", Message = " << e.what();
			}
		});

		std::this_thread::sleep_for(std::chrono::seconds(2));

		sock->cancel();

		worker_thread.join();
	}
	catch (boost::system::system_error& e) {
		std::cout << "Error occured!, Error Code=" << e.code() << ", Message=" << e.code();
		return e.code().value();
	}
	return EXIT_SUCCESS;
}



int main(int argc, char* argv[]) {

	int portNo;
	char* hostName;

	portNo = 3333;

	for (int i = 0; i < argc; i++)
	{
		if ("-p" == argv[i] && argc > i+1) {
			portNo = a2i(argv[i + 1]);
		}
		if ("-h" == argv[i] && argc > i + 1) {
			hostName = argv[i + 1];
		}
	}

	portNo = portNo < 1 ? 3333 : portNo;

	startTcpService(portNo);

}