#!/usr/bin/bash
# 上传用户A的公钥到用户B的~/.ssh/Authorized_keys
# 用户A和用户B可以是相同的用户

. run.sh

userA=$1
userB=$2

# 临时提权
sudo_run_command chmod 777 /home/$userB
sudo_run_command mkdir /home/$userB/.ssh
sudo_run_command chmod 777 /home/$userB/.ssh
sudo_run_command touch /home/$userB/.ssh/authorized_keys
sudo_run_command chmod 777 /home/$userB/.ssh/authorized_keys
sudo_run_command chown -R $username:$username /home/$userB

# 拷贝公钥
upload_file ~/.ssh/id_rsa.$userA@$hostname.pub "~"
sudo_run_command "cat ~/id_rsa.$userA@$hostname.pub >> /home/$userB/.ssh/authorized_keys"
sudo_run_command rm "~/id_rsa.$userA@$hostname.pub"

# 恢复权限
sudo_run_command chmod 700 /home/$userB
sudo_run_command chmod 700 /home/$userB/.ssh
sudo_run_command chmod 600 /home/$userB/.ssh/authorized_keys
sudo_run_command chown -R $userB:$userB /home/$userB
