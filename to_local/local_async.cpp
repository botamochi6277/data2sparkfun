// http request for local phant server
// references
// http://nekko1119.hatenablog.com/entry/2013/10/02/145532
// https://learn.sparkfun.com/tutorials/pushing-data-to-datasparkfuncom/arduino--ethernet-shield
// http://amedama1x1.hatenablog.com/entry/2014/08/23/203057
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <string>

#define _USE_MATH_DEFINES // for pi
#include <cmath>	//for math func (cos,sin,tan)
#include <chrono>	//for wait
#include <thread>	//for wait

namespace asio = boost::asio;
namespace ip = asio::ip;

// local
std::string const HOST = "192.168.1.15"; // [your PC's IP address]
std::string const PUBLIC_KEY = "BQJZ3L4WggSMgp49jjMgfEpXMbEL";
std::string const PRIVATE_KEY = "bZAP8nBr22s8ajd6AA8ahAgQ93A2";




bool wait( const std::string& typ , const std::chrono::system_clock::time_point& strt , const unsigned int& t ){
  if( typ == "nano" ) std::this_thread::sleep_until( strt + std::chrono::nanoseconds( t ) );
  else if( typ == "micro" ) std::this_thread::sleep_until( strt + std::chrono::microseconds( t ) );
  else if( typ == "milli" ) std::this_thread::sleep_until( strt + std::chrono::milliseconds( t ) );
  else if( typ == "sec" ) std::this_thread::sleep_until( strt + std::chrono::seconds( t ) );
  else if( typ == "min" ) std::this_thread::sleep_until( strt + std::chrono::minutes( t ) );
  else if( typ == "hour" ) std::this_thread::sleep_until( strt + std::chrono::hours( t ) );
  else return false;

  return true;
}

int main()
{
  std::cout << "Hello, I am " << __FILE__ << std::endl;
  std::cout << "My birthday is " << __DATE__ << ", " << __TIME__ <<std::endl;
  std::cout << "Send data to " << HOST << "/input/" << PUBLIC_KEY << std::endl;

  try{
    auto start = std::chrono::system_clock::now();

    for(;;){
      auto t_now = std::chrono::system_clock::now();
      unsigned long tMilli = std::chrono::duration_cast<std::chrono::milliseconds>(t_now - start).count();
      if (tMilli > 10.0e3) {
        std::cout << "Finish at " << tMilli << " ms"<<  std::endl;
        break;
      }

      asio::io_service io_service;
      ip::tcp::socket sock(io_service);

      ip::tcp::resolver resolver(io_service);
      ip::tcp::resolver::query query(HOST, "http");

      // ip::tcp::endpoint endpoint(*resolver.resolve(query),8080);
      boost::asio::ip::tcp::endpoint endpoint(
          boost::asio::ip::address::from_string(HOST), 8080);
      sock.connect(endpoint);
      asio::streambuf request;
      std::ostream request_ostream(&request);
      // http://data.sparkfun.com/input/[publicKey]?private_key=[privateKey]&time=[value]&val1=[value]&val2=[value]
      request_ostream << "GET " << "/input/" << PUBLIC_KEY << "?private_key=" << PRIVATE_KEY
                      << "&time=" << tMilli
                      << "&val1=" << sin(2*M_PI*(double)tMilli/1000.0)
                      << "&val2=" << cos(2*M_PI*(double)tMilli/1000.0)
                      << " HTTP/1.1\r\n";
      request_ostream << "HOST: " << HOST << "\r\n";
      request_ostream << "Connection: close\r\n\r\n";

      auto counter = 0;
      asio::async_write(sock, request,[&](boost::system::error_code, std::size_t) {
        if (++counter == 2) sock.close();
    });
      wait("milli", t_now, 50.0);
    }

  }
  catch(std::exception& e){
    std::cout << "Error!" << std::endl;
    std::cout << e.what() << std::endl;
  }
}
