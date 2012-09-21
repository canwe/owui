/*
#include <owui/tpl/parser.hh>
#include <owui/tpl/lib.hh>
#include <owui/tpl/parser.hh>
#include <owui/tpl/code.hh>
#include <owui/tpl/executor.hh>
#include <olibs/txt/text.hh>


#include <fstream>


using namespace Owui;


void test(const String& fname)
{
  Txt::Text text(fname.c_str());
 
  Tpl::CodeCtx codeCtx(*((const Tpl::TagCatalog*)0), (Tpl::TagAllocator*)0);
  Tpl::Code code;
  Tpl::Parser parser(text, code, codeCtx);
  parser.parse();
  
//  cout << "prg print:\n";
//  code.print(cout);
//  cout << "\n";
  
//  cout << "exec...\n";
//  Tpl::Executor executor;
//  executor.exec(code, cout);
//  cout << "\nDone.\n";
}


int main (int argc, char** argv)
{
  try
  {
    LibLoader<Tpl::Lib> tplLib;
    
    if(argc != 2)
    {
      cerr << "usage t1 wutFname\n";
      return 1;
    }

    test(argv[1]);
  }
  catch(const std::exception& e)
  {
    cerr << "ex: " << e.what() << std::endl;
  }
  
  return 0;
}
*/
