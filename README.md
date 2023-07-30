## timer
> 利用构造和析构，统计对象存活时间，用于推测某函数的运行耗时，使计时代码更简短。
## File_Loader
> std::vector<T>的子类，但支持自动读写文件。只要T支持T(const std::string&) 和 operator<<(std::ostream&)
## adjacency_matrix
> 邻接矩阵相关算法实现, 包含 dijkstra 和 floyd
> 暂时只是整合旧代码 以后会补充更多算法 以及邻接表相关算法
## tcp_once
> 向指定地址发送消息，并获取消息回执，支持linux和windows
