#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <vector>
#include <boost/program_options.hpp>
#include "ZiegVersion.h"

using namespace std;
using namespace boost::interprocess;
namespace po = boost::program_options;

void clientRun()
{
    try{
       //Erase previous message queue
       //message_queue::remove("message_queue");

       //Create a message_queue.
       message_queue mq
          (open_or_create               //only create
          ,"message_queue"           //name
          ,100                       //max message number
          ,sizeof(int)               //max message size
          );

       //Send 100 numbers
       for(int i = 0; i < 100; ++i){
          mq.send(&i, sizeof(i), 0);
       }
    }
    catch(interprocess_exception &ex){
       std::cout << ex.what() << std::endl;
    }
}

void serverRun()
{
    try{
       //Open a message queue.
       message_queue mq
          (open_or_create        //only create
          ,"message_queue"  //name
           ,100                       //max message number
           ,sizeof(int)               //max message size
           );

       unsigned int priority;
       message_queue::size_type recvd_size;

       //Receive 100 numbers
       for(int i = 0; i < 100; ++i){
          int number;
          mq.receive(&number, sizeof(number), recvd_size, priority);
          if(number != i || recvd_size != sizeof(number))
             return;
          cout << "Number received: " << number << endl;
       }
    }
    catch(interprocess_exception &ex){
       message_queue::remove("message_queue");
       std::cout << ex.what() << std::endl;
       return;
    }
    message_queue::remove("message_queue");
}

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
       if (vm.count("client")) {
           cout << "Running in client mode ..." << endl;
           clientRun();
       }
       else if (vm.count("server")) {
           cout << "Running in server mode ..." << endl;
           serverRun();
       }

    }
    catch(exception& ex)
    {
       cout << "Exception " << ex.what() << " thrown." << endl;
    }
    catch(...)
    {
       cout << "Unknown exception thrown." << endl;
    }

    cout << "Bye!" << endl;
    return 0;
}
