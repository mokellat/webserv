/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:36:44 by zqadiri           #+#    #+#             */
/*   Updated: 2022/05/13 15:20:36 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONFIG_HPP_
#define SERVERCONFIG_HPP_

#include "../includes/webserv.hpp"

struct _location
{
	std::string				_path;
	std::list<std::string>	_allow_methods;
	std::string				_root;
	std::string				_index;
	int						_limitBodySize;
	bool					_alias;
	std::string				_pathCGI;
	std::vector<_location>	_nestedLocations;
};

class serverConfig
{
	private:
		std::list<std::string>		_server_name;
		std::string					_root;
		std::string					_index;
		t_listen					_hostPort;
		bool						_autoindex;
		std::list<std::string>		_error_pages;
		std::list<std::string>		_allow_methods;
		std::vector<_location>		_locations;
		 
	public:
		serverConfig();
		serverConfig(std::string _root, std::string _index, std::string _host);
		~serverConfig();
		serverConfig(const serverConfig &obj);
		serverConfig	&operator=(const serverConfig&);

		const t_listen				 	&gethostPort(void) const;
		const std::list<std::string>	&getServerName(void) const;
		const std::vector<_location>	&getLocations(void) const;
		const std::list<std::string> 	&getErrorsPages(void) const;
		bool							getAutoIndex(void) const;
		const std::list<std::string> 	&getAllowMethods(void) const;
		unsigned int 	serverName(serverConfig&, configFile, unsigned int&);
		unsigned int	parseLocation(serverConfig&, configFile, unsigned int&);
		unsigned int	listen(serverConfig &, configFile, unsigned int&);
		unsigned int	root(serverConfig &, configFile, unsigned int&);
		unsigned int	index(serverConfig &, configFile, unsigned int&);
		unsigned int	errorPages(serverConfig &, configFile, unsigned int&);
		unsigned int	autoIndex(serverConfig &, configFile, unsigned int&);

		unsigned int	allowMethods(serverConfig &, configFile, unsigned int&);
		unsigned int	location(_location &, configFile, unsigned int &);
};

#endif
