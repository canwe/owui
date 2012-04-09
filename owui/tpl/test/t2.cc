#include <owui/tpl/parametrParser.hh>


int main (int argc, char** argv)
{
  Owui::Tpl::ParametrParser parser;
  parser.exec("light${color}__${size}");
}
