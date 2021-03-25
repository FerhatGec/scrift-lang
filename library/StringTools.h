/*# MIT License
# Forked from https://github.com/ferhatgec/stringtools
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#*/

#ifndef STRING_TOOLS_HPP
#define STRING_TOOLS_HPP

#include <iostream>
#include <cstring>

namespace stringtools {
	static std::string EraseAllSubString(std::string & mainString, const std::string & erase) {
    		size_t pos = std::string::npos;
   		while((pos = mainString.find(erase)) != std::string::npos) {
        		mainString.erase(pos, erase.length());
  		}
  		return mainString;
  	}
  	
    static void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;

        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
        	start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    	}
	}

    static bool replace(std::string& str, const std::string& from, const std::string& to) {
    	size_t start_pos = str.find(from);

    	if(start_pos == std::string::npos)
       		return false;

    	str.replace(start_pos, from.length(), to);
    	return true;
	}

    static int IntConverter(const char *s) {
  		int sum = 0;
  		char ch;
  		char sign = *s;
 		if (*s == '-' || *s == '+') s++;
  		while ((ch = *s++) >= '0' && ch <= '9') {
    			sum = sum * 10 - (ch - '0');
  		}
  		if (sign != '-') {
    			sum = -sum;
  		}
  		return sum;
	}
	
	static int IntConverterWithWhitespace(char* s) {
		int sum = 0;
  		char ch;
  		std::string conv(s); 
  		s = const_cast<char*>(EraseAllSubString(conv, " ").c_str());
 		char sign = *s;
 		if (*s == '-' || *s == '+') s++;
  		while ((ch = *s++) >= '0' && ch <= '9') {
    			sum = sum * 10 - (ch - '0');
  		}
  		if (sign != '-') {
    			sum = -sum;
  		}
  		return sum;
	}
	
	static int Count(std::string s, char ch) {
  		int count = 0;
		int size = s.size();
	 	for (int i = 0; i < size; i++)
    			if (s[i] == ch) count++;

  		return count;
	}
	
	static std::string GetBetweenString(std::string oStr, std::string sStr1, std::string sStr2) {  
    		int start = oStr.find(sStr1);   
    		if (start >= 0) {       
     			std::string tstr = oStr.substr(start + sStr1.length());        
      			int stop = tstr.find(sStr2);      
      			if (stop >1)          
        			return oStr.substr(start + sStr1.length(), stop);
      			else
        			return "error";  
    		}
    		else
       		return "error"; 
	}	
	
	static void GetBtwString(std::string oStr, std::string sStr1, std::string sStr2, std::string &rStr) {  
    		int start = oStr.find(sStr1);   
    		if (start >= 0) {       
      		std::string tstr = oStr.substr(start + sStr1.length());        
      		int stop = tstr.find(sStr2);      
      		if (stop >1)          
        		rStr = oStr.substr(start + sStr1.length(), stop);
      		else
        		rStr ="error";  
    		}
    		else
       		rStr = "error"; 
	}
	
	static inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
    	s.erase(0, s.find_first_not_of(t));
    	return s;
	}

    /* From FlaScript's StringTools replacement */
    static std::string EraseSub(std::string & mainString, const std::string & erase) {
		size_t pos = std::string::npos;

   		if((pos = mainString.find(erase)) != std::string::npos)
        		mainString.erase(pos, erase.length());

  		return mainString;
  	}

	static std::string getFirstCommand(std::string str) {
    	std::string word = "";
    	if(!strstr(str.c_str(), " ")) return str;
    	
    	for(auto x : str) {
        	if (x == ' ') {
            	break;
        	} else {
            	word = word + x;
        	}
    	}
    	
    	return word;
	}

  static bool Find(std::string &data, std::string substring) {
  		size_t check = data.find(substring);

		if (check != std::string::npos) return true; /* Found */
		else
			return false; /* Not found */

		return false;
	}
}

#endif // STRING_TOOLS_HPP