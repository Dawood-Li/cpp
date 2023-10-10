#!/usr/bin/bash
# 安装环境

# 使用 dnf 包管理
if command -v dnf &> /dev/null; then  
    sudo dnf update -y
    sudo dnf install git-all docker docker-compose mailx sendmail -y

# 使用 apt 包管理
elif command -v apt &> /dev/null; then  
    sudo apt update -y
    sudo apt upgrade -y
    sudo apt install git-all docker docker-compose -y
else
    echo "[ ERROR ] unsupport your package manager"
    exit 1  
fi

# 启动docker 拉取镜像
sudo systemctl enable docker
sudo systemctl start docker
sudo docker pull fedora
sudo docker pull nginx
sudo docker pull mariadb
sudo docker pull redis

# 设置邮件发送向公网而非本地
sudo sed -i 's/Addr=127.0.0.1/Addr=0.0.0.0/g' /etc/mail/sendmail.mc
sudo systemctl restart sendmail

mail -s "testtest" dawood_li@outlook.com
