/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:31:24 by zqadiri           #+#    #+#             */
/*   Updated: 2022/04/18 00:16:12 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "../includes/webserv.hpp"
#include "./serverConfig.hpp"

#define BUFFER_SIZE	2048

class Config
{
	private:
		std::vector<serverConfig*>	servers;
	public:
		Config();
		~Config();
		Config(const Config&);
		Config	&operator=(const Config&);

		//* Parsing funtioncs
		void		parseFile(const char *fileName);
		configFile	readFile(const char *fileName);
		configFile	slitTokens(configFile, std::string);
		size_t		parseServer(configFile , unsigned int&);
		std::string	removeSpace(std::string);
		configFile::iterator	curlLevel(configFile);
		
		//* Accessors
		std::vector<serverConfig*>	getServers(void);
		std::vector<t_listen>		getAllListenDir(void);

		
		class	FileCorrupted : public std::exception{
			public:
				virtual const char* what() const throw();
		};
		class	FileNotWellFormated : public std::exception{
			public:
				virtual const char* what() const throw();
		};

		//* print function
		void	print();
};

#endif