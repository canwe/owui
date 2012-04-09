#include <owui/fcgi/fcgiGateway.hh>
#include <owui/fcgi/lib.hh>
#include <owui/base/servletServer.hh>
#include <owui/base/httpRequest.hh>
#include <owui/base/httpResponse.hh>

#include <fstream>


using namespace Owui;


class MyServlet: public Servlet
{
public:  
  virtual void service(RequestContext& reqCtx);
};

void MyServlet::service(RequestContext& reqCtx)
{
  HttpRequest& request = reqCtx.request();    
  Ostream& os = reqCtx.response().outStream();
  
  os
    << "Content-type: text/html\r\n\r\n"
    << "<p>Test servlet output, uri: " << request.uri() << "</p>\n";
    
  os << "<p>env:<br/>\n";  
  typedef HttpRequest::Env Env;

  for(Env::const_iterator it = request.env().begin(); it != request.env().end(); ++it)
  {
    os << it->first << "=" << it->second << "<br/>\n";  
  }
  
  os << "</p>\n";
   
  cerr << "myservlet\n";
}


void test()
{
  OLIBS_DEBOUT("staring fcgi daemon...\n");

  ServletServer servletServer;
  servletServer.add(new MyServlet);
  
  Fcgi::FcgiGateway gateway(servletServer, ":9000", 100);
  gateway.run();
}


int main ()
{
  try
  {
    LibLoader<Fcgi::Lib> fcgiLib;
    test();
  }
  catch(const std::exception& e)
  {
    cerr << "ex: " << e.what() << std::endl;
  }
  
  return 0;
}

