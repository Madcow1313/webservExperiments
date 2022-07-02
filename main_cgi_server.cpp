#include "header.hpp"
using namespace std;
int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>CGI Envrionment Variables</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";

    while (*envp)
        cout << *envp++ << "<br/>";

    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}