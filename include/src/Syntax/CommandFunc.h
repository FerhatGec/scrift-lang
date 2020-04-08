/* GPLv3 License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the GPLv3 License.
#
# */

#ifndef COMMAND_FUNC_H
#define COMMAND_FUNC_H

#include "../Settings/DefaultSettings.h"            
#include "../main.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stddef.h>
#include <cstdlib>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>





#define MAIN_ALL 6


class FCommand {
public:
    FCommand();
    ~FCommand();
    void echo_str(char *str_echo)
    {
        printf(str_echo);
    }
    void get_username(char *_your_username)
    {
      #ifdef __linux__
       uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    if (pw)
    {
      printf(pw->pw_name);
      _your_username = pw->pw_name;
     }
      printf("\n", _your_username, "\n");
      #else 
      printf("\nFegeya Fusion Username:", "user", "or ",  _n_supported_()); // ; deleted
      #endif
    }
    void _os_kernel_name(char *_your_os_kernel)
    {
    #ifdef _WIN32
    _your_os_kernel = "Windows NT 32-bit\n";
    #elif _WIN64
    _your_os_kernel "Windows NT 64-bit \n";
    #elif __APPLE__ || __MACH__
    _your_os_kernel  = "Darwin \n";
    #elif __linux__
    _your_os_kernel = "Linux <3 \n";
    #elif __FreeBSD__
    _your_os_kernel = "BSD \n";
    #elif __unix || __unix__
    _your_os_kernel = "Unix \n";
    #else
    _your_os_kernel = "Fegeya Fusion or not supported operating system :) \n";
    #endif
    printf(_your_os_kernel);
    }
   void _set_locale()
{
        printf("Set up -> Your system language");// setlocale(LC_CTYPE, NULL);
        setlocale(LC_CTYPE, NULL); // FOR UNIX AND FUSION
        printf(" \n"); 
}
    void list_dir(const char *path) 
    {
        struct dirent *entry; // #i.. <dirent.h>
        DIR *dir = opendir(path); // open path dir
   
        if (dir == NULL) 
        {
            return;
        }
        while ((entry = readdir(dir)) != NULL) 
        {
            std::cout << entry->d_name << "  ";
        }
        closedir(dir);
    }
    void plus_num(uint64_t first_num, uint64_t sec_num)
    {
        printf("First number: ");
        std::cin >> first_num;
        printf("Second number ");
        std::cin >> sec_num;
        uint64_t fs_num = sec_num + first_num;
        std::cout << fs_num << "\n";
    }
    void fetcheya(int ram_size, char *cpu_type)
    {
       // fsync__->CPU(cpu_type);
    }
    void _generated_hash_string(int size)
    {
    
    std::cout << "Enter size : ";
    std::cin >> size;
    std::string str;
    for (int i = 0; i < size; i++)
    {
        auto d = rand() % 26 + 'a';
        str.push_back(d);
    }
    for (int i = 0; i < size; i++)
    {
        std::cout << str[i];
    }
    printf("\n");
    }
    
    void _your_ip()
    {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } 
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return;
    }   
    void error_undfnd(char *undefined_str)
    {
        undefined_str = "This is Undefined \n";
        printf(undefined_str);
    }
    void _file_path(char *list_path_def_name)
    {
         list_dir("/home/"); 
    }
    void _term_(char *file_str)
    {
        file_str = "$|";
        printf(file_str);
    }
    void help()
    {
      //  std::cin >> _cin;
   
     printf(_help_str);
        
    }

    void cd_func(char *new_path)
    {
        
    }
    void hello()
    {
      //  *_h_str = *_hello_str; -> This code calling Segmentation Fault error. 
        printf(_help_str);
    }
    void printerror(char *err_str, int8_t err_number)
    {
        printf(err_str, err_number);
    }
    void _n_supported_(char *file = "Your os not supported!", char *_err_code = "1_n_support \n")
    {
        printf(file, " ", _err_code);
    }
    void error_syntax(char *err_str, int8_t err_number)
    {   
      
        printerror(err_str, err_number);
    }
private:
    char *_hello_str = "help arguments:\n"
    "echo <arg>\n"
    "intnumber plus intnumber\n"
    "./<file>\n"
    "brk || cls -> Close Scrift Shell \n"
    "cd <folder> \n"
    "ls -> List\n"
    "-f || fetcheya -> System info ";
    char *_help_str = "Welcome ScriftLang Terminal\n"
    "ScriftLang licensed with GPLv3'\n"
    "Copyright (c) 2020 Ferhat Gecdogan\n";
};


#endif // COMMAND_FUNC_H
