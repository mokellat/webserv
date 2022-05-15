/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:10:13 by zqadiri           #+#    #+#             */
/*   Updated: 2022/05/15 14:32:51 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "servers.hpp"

/*---- Constructors & Destructor ------*/

Servers::Servers(){
	
}

Servers::~Servers(){
}

Servers::Servers(const Servers &sv){
	*this = sv;
}

/*---- Operators -------*/

Servers	&Servers::operator=(const Servers&obj){
	this->config = obj.config;
	return *this;
}

/*----- Accessors -------*/

std::vector<serverConfig*>	Servers::getServers(void){
	return		config.getServers();
}

/*---- Member Functions ----*/

// void	Servers::testConnection(int sock){
// 	if (sock < 0){
// 		write (2, "Failed To Connect\n", 18);
// 		exit (EXIT_FAILURE);
// 	}
// }

void		Servers::conf(char **argv){
	config.parseFile(argv[1]);
}

void		Servers::setup(void){
	std::vector<t_listen>	listen = config.getAllListenDir();
	_max_fd = 0;
	FD_ZERO(&_fd_set);
	for(std::vector<t_listen>::iterator it = listen.begin(); it != listen.end(); ++it){
		server sev(*it);
		if (sev.setup() != -1)
		{
			int fd = sev.get_fd();
			FD_SET(fd, &_fd_set);
			if (fd > _max_fd)
				_max_fd = fd;
			_servers.push_back(sev);
			std::cout << "Server: "<< fd << " " << it->port << " Setup Done" << std::endl;
		}
		else
			std::cout << "Server: "<< it->port << " Setup Failed" << std::endl;
	}
}

void		Servers::run(void){
	
	std::cout << "run()\n";
	fd_set write_set;
	FD_ZERO(&write_set);
	
	while (1)
	{
		std::cout << "select()\n";
		fd_set fset;
		fd_set wset;
		FD_ZERO(&fset);
		FD_ZERO(&wset);
		FD_COPY(&_fd_set, &fset);
		FD_COPY(&write_set, &wset);
		int selected = select(_max_fd + 1, &fset, &wset, NULL, NULL);
		if (selected == -1)
		{
			std::cout << "select error" << std::endl;
			return ;
		}
		if (selected > 0) 
		{
			for (std::list<server>::iterator serv = _servers.begin(); serv != _servers.end(); ++serv)
			{
				if (!serv->is_sockets_empty())
					serv->handle_sockets(fset, wset, _fd_set, write_set);
				serv->add_socket(fset, _fd_set, _max_fd);
			}
		}
		else
			std::cout << "didnt select" << std::endl;
	}
}