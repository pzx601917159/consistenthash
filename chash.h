/*********************************************************************
	> File Name: chash.h
	> Author: 彭治湘
	> Mail: xxx 
	> Created Time: 2017年01月06日 星期五 17时25分10秒
 ********************************************************************/

#ifndef _CHASH_H
#define _CHASH_H

#include <string>
#include <map>
#include <inttypes.h>

//代表服务器
class Server
{
    public:
    Server(std::string serverName);
    std::string m_serverName;
};

class CHash
{
    public:
    //添加服务器
    void addServer(Server* server);
    //查找服务器
    Server* findServer(std::string key);
    //删除服务器
    void deleteServer(Server* server);
    private:
    std::map<uint32_t,Server*> m_serverMap;
};

#endif //_CHASH_H
