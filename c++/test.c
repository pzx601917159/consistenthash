/*********************************************************************
	> File Name: test.c
	> Author: 彭治湘
	> Mail: xxx 
	> Created Time: 2017年01月06日 星期五 18时03分29秒
 ********************************************************************/
#include "crc32.h"
#include <stdio.h>
#include "chash.h"
#include <iostream>
int main()
{
    CHash hash;
    Server server1("127.0.0.1:1883");
    Server server2("127.0.0.1:1884");
    Server server3("127.0.0.1:1885");
    Server server4("127.0.0.1:1886");
    Server server5("127.0.0.1:1887");
    Server server6("127.0.0.1:1888");
    Server server7("127.0.0.1:1889");
    hash.addServer(&server1);
    hash.addServer(&server2);
    hash.addServer(&server3);
    hash.addServer(&server4);
    hash.addServer(&server5);
    hash.addServer(&server6);
    hash.addServer(&server7);
    char buf[1024];
    std::map<Server*,int> serverCountMap;
    memset(buf,0,sizeof(buf));
    for(int i=0;i<100000;i++)
    {
        snprintf(buf,1024,"127.0.0.1:%d",i);
        Server* server =  hash.findServer(buf);
        if(serverCountMap.find(server) == serverCountMap.end())
            serverCountMap[server] = 1;
        else
            serverCountMap[server] = serverCountMap[server] + 1;
    }
    std::map<Server*,int>::iterator it = serverCountMap.begin();
    while(it != serverCountMap.end())
    {
        std::cout << it->first->m_serverName << ":" << it->second << std::endl;
        it++;
    }
    return 0;
}
