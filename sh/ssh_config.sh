#!/usr/bin/bash
# 使用脚本设置sshd选项

file="/etc/ssh/sshd_config"
function set() {  
    local k="$1"
    local v="$2"
    sudo sed -i "s/$k .*/$k $v/" $file
    sudo sed -i "s/#$k .*/$k $v/" $file
}

set "PubkeyAuthentication" "yes"  # 启用公钥认证
set "RSAAuthentication" "yes"     # 启用RSA认证
set "PermitRootLogin" "no"        # 允许root远程登录
set "PasswordAuthentication" "no" # 允许密码登录 no则仅允许密钥登陆
set "Port" "22"                   # 修改默认端口

sudo systemctl restart sshd
