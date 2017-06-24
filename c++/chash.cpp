/*********************************************************************
	> File Name: chash.cpp
	> Author: 彭治湘
	> Mail: xxx 
	> Created Time: 2017年01月06日 星期五 17时25分10秒
 ********************************************************************/
#include "chash.h"
#include <inttypes.h>
#include "crc32.h"
#include <string.h>
#include <stdio.h>

//字符串转换为整数
uint32_t strToInt(const std::string& str)
{
    return Crc32_Compute(str.c_str());
}

Server::Server(std::string serverName)
{
    m_serverName = serverName;
}

//添加服务器
void CHash::addServer(Server* server)
{
    if(server == NULL)
        return;
    int add_num = 0;
    //生成虚拟节点
    //虚拟节点的个数为32，可以随意设置
    for(int i=0;i<32;i++)
    {
        char buff[1024];
        memset(buff,0,sizeof(buff));
        snprintf(buff,sizeof(buff)/sizeof(char),"%u%u%u%u%u%s",i,i,i,i,i,server->m_serverName.c_str());
        std::string serverkey = buff;
        //插入
        uint32_t key = strToInt(serverkey);
        if(m_serverMap.find(key) == m_serverMap.end())
            //插入 
            m_serverMap[key] = server;
        else
            ++add_num;
            
    }
    if(add_num > 0)
    {
        for(int i=0; i<32 && add_num>0; i++)
        {
            char buff[1024];
            memset(buff,0,sizeof(buff));
            snprintf(buff,sizeof(buff)/sizeof(char),"%u%u%u%u%u%u%u%u%u%u%s",i,i,i,i,i,i,i,i,i,i,server->m_serverName.c_str());
            std::string serverkey = buff;
            //插入
            uint32_t key = strToInt(serverkey);
            if(m_serverMap.find(key) == m_serverMap.end())
            {
                //插入 
                m_serverMap[key] = server;
                --add_num;
            }
        }
    }
}

//查找服务器
Server* CHash::findServer(std::string keystr)
{
    if(m_serverMap.size() == 0)
        return NULL;
    if(m_serverMap.size() == 1)
        return m_serverMap.begin()->second;
    uint32_t key = strToInt(keystr);
    std::map<uint32_t,Server*>::iterator it = m_serverMap.begin();
    while(it != m_serverMap.end())
    {
        if(key < it->first)
            return it->second;
        it++;
    }
    return m_serverMap.begin()->second;
}

//删除服务器
void CHash::deleteServer(Server* server)
{
    if(server == NULL)
        return;
    std::map<uint32_t,Server*>::iterator it = m_serverMap.begin();
    while(it != m_serverMap.end())
    {
        if(it->second == server)
            m_serverMap.erase(it++);
    }
}

