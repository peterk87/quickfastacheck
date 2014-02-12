#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
List is_valid_nt_fasta_format(CharacterVector file_lines)
{
	auto header_count = 0;
	auto line_count = 0;
	for(CharacterVector::iterator it = file_lines.begin(); it != file_lines.end(); ++it)
	{	
		line_count++;
		auto count = 0;
		for(auto &x : *it)
		{
      if(header_count == 0 && x != '>')
      {
        return List::create(_["isFasta"] = false, _["failMsg"] = "First non-blank line was not FASTA header line beginning with '>' on line " + std::to_string(line_count));
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
					return List::create(_["isFasta"] = false, _["failMsg"] = "Unexpected character '" + tmp + "' on line " + std::to_string(line_count) + " column " + std::to_string(count));
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