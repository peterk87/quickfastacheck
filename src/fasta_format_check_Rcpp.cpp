#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
List is_valid_nt_fasta_format(CharacterVector file_lines)
{
	long header_count = 0;
	long line_count = 0;
	for(CharacterVector::iterator it = file_lines.begin(); it != file_lines.end(); ++it)
	{	
		line_count++;
		long count = 0;
		for (int i = 0; i < (*it).size(); ++i)
		{
			char x = (*it)[i];
		// }
		// for(auto &x : *it)
		// {

      if(header_count == 0 && x != '>')
      {
        return List::create(_["isFasta"] = false, _["failMsg"] = "First non-blank line was not FASTA header line beginning with '>' on line ");// + static_cast<std::ostringstream*>( &(std::ostringstream() << line_count)->str() ));
      }
			if(count == 0 && x == '>')
			{
				header_count++;
				break;
			}
			count++;
			switch (x)
			{
				case 'A':case 'a':
				case 'C':case 'c':
				case 'G':case 'g':
				case 'T':case 't':
				case 'R':case 'r':
				case 'Y':case 'y':
				case 'S':case 's':
				case 'W':case 'w':
				case 'K':case 'k':
				case 'M':case 'm':
				case 'B':case 'b':
				case 'D':case 'd':
				case 'H':case 'h':
				case 'V':case 'v':
				case 'N':case 'n':
					continue;
				default:
					std::string tmp;
					std::stringstream ss;
					ss << x;
					ss >> tmp;
					return List::create(_["isFasta"] = false, _["failMsg"] = "Unexpected character '" + tmp + "' on line ");// + static_cast<std::ostringstream*>( &(std::ostringstream() << line_count) )-str() + " column " + static_cast<std::ostringstream*>( &(std::ostringstream() << count)->str() ));
			}
		}
	}
	if (header_count > 0)
	{
		return List::create(_["isFasta"] = true, _["failMsg"] = "");
	}
	else
	{
		return List::create(_["isFasta"] = false, _["failMsg"] = "No headers (i.e. lines starting with '>') in file");
	}
}