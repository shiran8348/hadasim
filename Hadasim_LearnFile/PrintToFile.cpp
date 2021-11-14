#include "PrintToFile.h"

PrintToFile::PrintToFile(std::string a_name_file):
m_current_request(""),
m_requested_list({}),
m_name_file(a_name_file),
m_outfile(m_name_file) {
	m_outfile << "Ditails for: " + m_name_file +" file:\n\n";
}
void PrintToFile::AddRequest(std::string m_request) {
	try {
		m_current_request = m_request;
		
		m_requested_list.push_back (m_request);
	}
	catch (std::exception ) {

	}
}
void PrintToFile::MakeRequestsFile() {
	
	for (auto const& line : m_requested_list) {
		m_outfile << line << std::endl;
//		std::cout << std::endl << line; //console
	}
}
void PrintToFile::CloseTheFile() {
	m_outfile.close();
}