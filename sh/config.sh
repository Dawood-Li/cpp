#!/usr/bin/bash
# 参数 远端地址 管理员账号密码
host="test01"           # server简称
hostname="192.168.1.13" # server地址
port="22"               # ssh端口
username="dawood"       # 用户名
password="1234"         # 密码

# 只输出一次
if [[ -z "${INITIALIZED}" ]]; then  
    INITIALIZED="true"  
    echo "use these arguments includes from config.sh: "
    echo "host     : $host"
    echo "hostname : $hostname"
    echo "port     : $port"
    echo "username : $username"
    echo "password : $password"
fi
