#!/usr/bin/bash
# 远程添加用户 并部署密钥 并直接进入ssh连接此用户进行测试

new_user_name=$1
new_user_passwd=$2

. config.sh
. run.sh

# 为新用户生成密钥
ssh-keygen -t rsa -b 4096 -f ~/.ssh/id_rsa.$new_user_name@$hostname -P "" -C "$new_user_name@$hostname"

# 创建用户
sudo_run_command adduser $new_user_name

# 设置密码
run_command "echo $'$password\n$new_user_passwd\n$new_user_passwd' | sudo -S passwd $new_user_name"

# 给root权限
sudo_run_command usermod -a -G wheel $new_user_name

# 上传密钥
bash pubkey_upload.sh git git

# 验证是否成功
ssh -i ~/.ssh/id_rsa.$new_user_name@$hostname $new_user_name@$hostname "echo \"adduser success\""
