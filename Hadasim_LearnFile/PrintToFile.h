#ifndef __PRINT_TO_H__
#define __PRINT_TO_H__
#include <string>
#include <list>
#include <iostream>
#include <fstream> 


class PrintToFile
{
public:
	PrintToFile(){}
	PrintToFile(std::string m_name_file);
	void AddRequest(std::string m_request);
	void MakeRequestsFile();
	void CloseTheFile();
private:
	std::string m_name_file;
	std::string m_current_request;
	std::list<std::string> m_requested_list;
	std::ofstream m_outfile;
};
#endif //__PRINT_TO_H__


