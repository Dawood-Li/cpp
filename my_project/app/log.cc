#include <iostream>  
#include <fstream>  

int main() {

    std::ofstream logfile("logfile.log", std::ios_base::app);
    std::clog.rdbuf(logfile.rdbuf());
    std::clog << "log test" << std::endl;
}
