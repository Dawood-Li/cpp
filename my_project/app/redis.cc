// sudo apt-get install libhiredis-dev
#include <hiredis/hiredis.h>  
  
int main() {  
    // 创建Redis连接  
    redisContext* redis = redisConnect("localhost", 6379);  
  
    // 检查连接是否成功  
    if (redis == NULL || redis->err) {  
        if (redis) {  
            printf("Connection error: %s\n", redis->errstr);  
            redisFree(redis);  
        } else {  
            printf("Connection error: can't allocate redis context\n");  
        }  
        return 1;  
    }  
  
    // 执行Redis命令  
    const char* cmd = "SET mykey \"Hello, Redis!\"";  
    if (redisCommand(redis, "%s", cmd) != REDIS_OK) {  
        printf("Redis command error: %s\n", redis->errstr);  
        redisFree(redis);  
        return 1;  
    }  
  
    // 读取响应结果  
    redisReply* reply;  
    reply = redisGetReply(redis, NULL);  
    if (reply == NULL) {  
        printf("Redis command error: %s\n", redis->errstr);  
        redisFree(redis);  
        return 1;  
    }  
  
    printf("SET result: %s\n", reply->str);  
    freeReplyObject(reply);  
  
    // 关闭连接  
    redisFree(redis);  
  
    return 0;  
}