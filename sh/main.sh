#!/usr/bin/bash

# 清理密钥 清理控制台输出
rm ~/.ssh/* -rf

clear

. config.sh
. run.sh

# 安装环境 已执行 在虚拟机快照 为了节约时间
sudo_run_script install.sh

# 添加git用户
echo "[ RUN ] adduser git"
bash adduser.sh git 1234 > /dev/null 2>&1
echo "[ DONE ] adduser git"

# 上传自己的公钥到git目录
echo "[ RUN ] upload dawood's pubkey to git"
bash pubkey_upload.sh $username git > /dev/null 2>&1
echo "[ DONE ] upload dawood's pubkey to git"

# 建仓
echo "[ RUN ] initialize a git repository"
bash git_init.sh testrepo01 > /dev/null 2>&1
echo "[ DONE ] initialize a git repository"

# 关闭selinux并重启 开启selinux导致docker容器无法读写数据卷
# sudo_run_command sed -i \
    # 's/SELINUX=enforcing/SELINUX=disabled/g' \
    # /etc/selinux/config
# sudo_run_command reboot now
# echo "等待服务器重启"
# sleep 30s

echo "[ ALL DONE ]"

# 统计项目行数 + 输出文件描述 300行多点
# find . -type f | xargs -I {} sh -c 'head -n 2 {} | tail -n 1' | paste <(find . -type f | xargs wc -l) - | sort -rn
