#ifndef _OWUI_FCGI_SERVLET_TASK_HH_
#define _OWUI_FCGI_SERVLET_TASK_HH_


#include <owui/fcgi/base.hh>
#include <olibs/thr/task.hh>
#include <olibs/base/optr.hh>


class HttpServletTask: public Task 
{
  Optr<HttpRequest>   m_request;
  Optr<HttpResponse>  m_response;

public:
  HttpServletTask(HttpRequest* request, HttpResponse* response);
  
protected:
  virtual void taskFunc();
};



} // namespace Fcgi
} // namespace Owui

#endif // _OWUI_FCGI_SERVLET_TASK_HH_

