#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../includes/webserv.hpp"
#include "../src/Request/request.hpp"
#include "../src/CGI/CGI.hpp"
#include "dirent.h"

class request;

class Response
{
    public:
        Response();
        Response(int);
        Response(const Response &);
        Response & operator=(const Response &);
        ~Response();

        //Response start
        std::string                 Request_statuscode_checked(request &request, serverConfig*);
        void                        Methods_exec(request &request, int fd, serverConfig *);
        void                        Return_string(request &request, serverConfig*, int fd);
        std::string                 ConvertHtml(std::string path);
        std::string                 Content_type();
        int                         File_length(std::string);
        void                        File_type(request &req);
        void                        File_type(std::string);
        bool                        isCGI(request &req, serverConfig *servconf);
        void                        GET(int fd, request &req, serverConfig*);
        std::string                 getfileChange();
        std::string                 CompletePath(request &req, serverConfig*);
        std::vector<std::string>    getFilesInDirectory(std::string);
        void                        AutoIndexExec(std::string);
        std::string                 new_header_str(request &req, serverConfig *servconf);
        void                        File_exec(std::string *str_ret, std::string str_req_uri, std::string my_root_find);
        void                        Errors_write(int, std::string *);
        bool                        Allow_Methods(request &req, serverConfig*, std::string);

        //!---------------- DELETE Functions --------------------------
        void						getStatusString();
        int                         IsFile(const std::string& path);
        int				            removeDir(std::string);
        void                        writeResponse();
        void                        DELETE(request &req, serverConfig*);

        //!---------------- POST Functions --------------------------
        bool		                supportUpload(request &req,  serverConfig *servconf);
        bool                        supportCGI(request &req, serverConfig *servconf);
        int			                parseLine(std::string line);
        void                        POST(int, request &req, serverConfig*);

    public: //!!!!! private
        std::string             _response_string;
        int                     _status_code;
        std::string             _pages_to_string;
        std::string             _file_change_get;
        std::string             _file_change_delete;
        std::string             _file_extension;
        std::string             _check_extension_mine;
        bool                    _get_file_success_open;
        bool                    _my_auto_index;
        bool                    _check_auto_index;

        std::string             _contentDisposition;
        std::string             _contentType;
        std::string             header;
        std::string		        str_uri;
        int                     body_length;
        std::ifstream           _res;
        bool                    _handled;
	    static std::string		my_root;
        std::string             my_index;
        std::string             _uploadFileName;
};

#endif