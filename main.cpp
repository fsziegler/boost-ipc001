#include <iostream>
#include <boost/program_options.hpp>
#include "ZiegVersion.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    try {
       po::options_description basic_opts("Generic options");
       basic_opts.add_options()
          ("version,v", "print version string")
          ("help,h","produce help message")
          ("client,c","run in client mode")
          ("server,s","run in server mode")
       ;

       po::options_description cmdline_options;
       cmdline_options.add(basic_opts);
       po::variables_map vm;
       po::store(po::parse_command_line(argc, argv, cmdline_options), vm);
       po::notify(vm);

       if (vm.count("help")) {
          cout << cmdline_options << endl;
          return 0;
       }
       if (vm.count("version")) {
          cout << "   Version: ";
          cout << ZiegVersion::GetFullVersionString() << endl;
          cout << "Build Date: ";
          cout << ZiegVersion::BuildDate << endl;
          cout << "Build Time: ";
          cout << ZiegVersion::BuildTime << endl;
          cout << "      UUID: ";
          cout << ZiegVersion::UUID << endl;
       }
    }
    catch(...)
    {

    }



    cout << "Hello World!" << endl;
    return 0;
}
