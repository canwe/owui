#include <owui/tpl/parametrParser.hh>
#include <owui/tpl/opParametrs.hh>

int main()
{
  Owui::Tpl::ParametrParser parser;
  parser.exec("light${color}__${size}");

  return 0;
}
