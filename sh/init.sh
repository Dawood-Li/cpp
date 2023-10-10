#!/usr/bin/bash
# 项目自动部署脚本 默认文件

# 测试 拉起一个nginx容器 测试成功
sudo docker run -itd --rm -p 80:80 nginx
echo "the Nginx container runs on port 80"
