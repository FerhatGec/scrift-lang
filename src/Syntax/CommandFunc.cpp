/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <Syntax/Language.hpp>
#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>
#include <Syntax/Colors.hpp>
#include <Syntax/GetNameFunction.hpp>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <Scrift.hpp>
#include <Syntax/CommandFunc.h>
#include <pwd.h>
#include <string.h>
#include <synflang.hpp>
#include <experimental/filesystem>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "../../include/Library/Keywords.hpp"

namespace filesys = std::experimental::filesystem;
FKeyword keyword;
static const char *_uname;

FCommand::FCommand()
{
    

}

FCommand::~FCommand()
{
    delete[] _home_dir, _file_path_cd_function, _uname;   
}

void 
FCommand::remove_character(char * _str, char ptr)
{
    if(_str == NULL)
        return;

    char * _pstr = _str;
    while(*_str)
    {
        if(*_str != ptr)
            *_pstr++ = *_str;
    _str++;
    }
    *_pstr = '\0';    
}


std::string
FCommand::FName()
{
	struct utsname buf;

	if(!uname(&buf)) { //Get name and information about current kernel.
		WHITE_COLOR
		//printf("%s\n",buf.sysname);//Display the system name.
		return buf.sysname;
	} else {
		BOLD_RED_COLOR
		perror("uname");
		return "?";
	}
	BLACK_COLOR
}


void
FCommand::echo_printlnf(std::string name) { 
    FLanguage lang;
    if(name != "")
    {
        WHITE_COLOR
        if(name.rfind("#USER") == 0) {        
            keyword.EndWithUser();
        } 
        else if(name.rfind("#PATH") == 0) {
            keyword.EndWithPath();
        } else if(name.rfind("#") == 0) {
        	printlnf(getenv(lang.EraseAllSubString(name, "#").c_str()));
        }
        else {
        printlnf(name.c_str());
        }
        BLACK_COLOR
    }
}

void
FCommand::_set_locale() {
        BOLD_MAGENTA_COLOR
        printlnf("Set up -> Your system language");// setlocale(LC_CTYPE, NULL);
        BLACK_COLOR // reset
        setlocale(LC_CTYPE, NULL); // FOR UNIX AND FUSION
        printlnf(" \n"); 
}


void
FCommand::list_direc(boolean _home) {
        integer files = 0;
        struct stat filestat;
        struct dirent *entry;
        DIR *dir;

        if(_home != false) {dir = opendir((getenv("HOME"), "/", _file_path_cd_function)); /*For Linux and *nix*/
        } else if(_home == false || _home == NULL)
        {
            dir = opendir(getenv("HOME"));
        }
        
        if (dir == NULL) 
        {
            printerror("ERR:DIRECTORY NOT FOUND", 12, "ERR:DIRNFND");
            return;
        }
        while ((entry = readdir(dir))) 
        {
            files++;
            char * _str = entry->d_name;
            remove_character(_str, '.');
            remove_character(_str, '..');
            stat(entry->d_name,&filestat);
            if(entry->d_type == DT_DIR) {
                BOLD_RED_COLOR
                printf("%4s: %s\n","Dir",entry->d_name); 
            }
            BLACK_COLOR
        }
        closedir(dir);
}

void 
FCommand::list_file(boolean _home) {
        integer files = 0;
        struct stat filestat;
        struct dirent *entry;
        DIR *dir;

        if(_home != false) {dir = opendir((getenv("HOME"), "/", _file_path_cd_function)); /*For Linux and *nix*/
        } else if(_home == false || _home == NULL)
        {
            dir = opendir(getenv("HOME"));
        }
        
        if (dir == NULL) 
        {
            RED_COLOR
            printerror("ERR:DIRECTORY NOT FOUND", 12, "ERR:DIRNFND");
            BLACK_COLOR
            return;
        }
        while ((entry = readdir(dir))) 
        {
            files++;
            char * _str = entry->d_name;
            remove_character(_str, '.');
            remove_character(_str, '..');
            //printf("%d", entry->d_type, "\n");
            //printf("%d");
          //  printf("\033[0;34m");
            stat(entry->d_name,&filestat);
            if(entry->d_type == DT_DIR) {
            } else{
                BOLD_YELLOW_COLOR
                printf("%4s: %s\n"," File",entry->d_name);
            } 
            BLACK_COLOR
        }
        closedir(dir);
}


std::string 
FCommand::chartostring(std::string const & s, fchar *a)
{
    return s + a;
}


void
FCommand::plus_num(uinteger64 first_num, uinteger64 sec_num)
{
        printlnf("First number: ");
        std::cin >> first_num;
        printlnf("Second number ");
        std::cin >> sec_num;
        uinteger64 fs_num = sec_num + first_num;
        std::cout << fs_num << "\n";
}


void
FCommand::_generated_hash_string(integer size)
{
    std::string str;
    for (integer i = 0; i < size; i++)
    {
        auto d = rand() % 40 + '0';
        str.push_back(d);
    }
    for (integer i = 0; i < size; i++)
    {
    	BOLD_CYAN_COLOR
        std::cout << str[i];
        BLACK_COLOR
    }
}

void
FCommand::getIPAddress(){
   int sock = socket(PF_INET, SOCK_DGRAM, 0);
    sockaddr_in loopback;

    if (sock == -1) {
        std::cerr << "Could not socket\n";
    }

    std::memset(&loopback, 0, sizeof(loopback));
    loopback.sin_family = AF_INET;
    loopback.sin_addr.s_addr = INADDR_LOOPBACK;   // using loopback ip address
    loopback.sin_port = htons(9);                 // using debug port

    if (connect(sock, reinterpret_cast<sockaddr*>(&loopback), sizeof(loopback)) == -1) {
        close(sock);
        std::cerr << "Could not connect\n";
    }

    socklen_t addrlen = sizeof(loopback);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&loopback), &addrlen) == -1) {
        close(sock);
        std::cerr << "Could not getsockname\n";
    }

    close(sock);

    char buf[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &loopback.sin_addr, buf, INET_ADDRSTRLEN) == 0x0) {
        std::cerr << "Could not inet_ntop\n";
    } else {
        std::cout << WBOLD_GREEN_COLOR <<"Local ip address: ";
        std::cout << WBOLD_YELLOW_COLOR << buf << "\n";
    }
}

void
FCommand::printerror(fchar *err_str, integer8 err_number, fchar * _error_code)
{
        RED_COLOR
        printlnf(err_str);
        slashn 
        std::cout << err_number;
        slashn
        printlnf(_error_code);
        BLACK_COLOR // reset
}

void
FCommand::_n_supported_()
{
    RED_COLOR
    printerror("Your os not supported!", 10, "1_n_support \n");
    BLACK_COLOR // reset
}
