# 个人cpp代码暂存库 基于c++17

## 非常感谢能够阅读我的代码，发现并反馈问题。

## NETWORKS 网络库 (得意之作)
| 模块                  | 介绍 |  
| :---:                 | :--- |  
| **sockfd**            | 表示一个socket连接 |  
| **epoll_server**      | 表示一个tcp epoll server |  
| **http_message**      | 表示一个http报文 |
| **http_server**       | http服务接口 |  

## UTILS 工具库 暂存 待整理
| 模块                  | 介绍 |  
| :---:                 | :--- |  
| **menu**              | 值得一看 一个控制台菜单的抽象 |
| **adjacency_matrix**  | 值得一看 邻接矩阵相关算法实现, 包含 dijkstra 和 floyd 暂时只是整合旧代码 以后会补充更多算法 以及邻接表相关算法 |
| **File_Loader**       | std::vector<T>的子类，额外支持了自动读写文件 |
| **tcp_once**          | 向指定地址发送消息，并获取消息回执，支持linux和windows |
| **fileloader**        | c++文件加载器 |  
| **timer**             | 利用构造和析构，统计对象存活时间 |

## 排序算法（得意之作）
* 使用了工厂模式 对主流的排序算法进行了性能测试 最终得出结论：  
1. std::sotr最强
2. 插排其次  
3. 凡人写的快排并不快  
4. 算法复杂度分析确实可以估算性能级别 但实测性能的差距会根据实现细微区别，编译器，CPU架构等，而略有差异。
5. 开O2 开O2 开O2 比优化算法重要的多  
6. 堆排和归并忘写了。。。。

## 数据结构
* avl树 值得一看

## MY_PROJECT
* 基于docker的项目部署方案

## SH
### 一组linux shell脚本 实现了一下功能：
* ssh公钥推送
* 远程命令执行
* 远程脚本执行
* 创建用户
* 远程创建git仓库 在本地同步关联仓库 并启用git钩子 push时自动调用项目部署脚本

## 剩余待补充
## 个人代码暂存库 暂未整理完 不做过多介绍

## 后续工作：
* 加入mysql和redis的接口的c++抽象
* 加入websocket模块
* 加入连接池 和对SSE的支持
* 实现json解析和xml解析
* 实现jwt鉴权

