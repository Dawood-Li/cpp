// sudo apt-get install libmysqlcppconn-dev
// sudo apt install -y mysql-server mysql-client libmysqlclient-dev
#include <mysql_driver.h>  
#include <mysql_connection.h>  
  
#include <cppconn/driver.h>  
#include <cppconn/exception.h>  
#include <cppconn/resultset.h>  
#include <cppconn/statement.h>  
  
using namespace std;  
  
int main(void)  
{  
    auto* driver = sql::mysql::get_mysql_driver_instance();
    auto* con = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
    auto* stmt = con->createStatement();
    auto* res = stmt->executeQuery("SELECT * from test");
    while (res->next()) {  
        // cout << res->getInt("id") << endl;  
        // cout << res->getInt(1) << endl;  

        // cout << res->getString("name") << endl;  
        // cout << res->getString(2) << endl;  
    }  
  
    delete res;  
    delete stmt;  
    delete con;  
    return 0;  
}
