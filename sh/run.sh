#!/usr/bin/bash
# 在远端执行本地脚本

# 使用方法: 
# 执行命令 普通权限 run_command [command]
# 执行命令 管理权限 sudo_run_command [command]
# 执行脚本 普通权限 run_script [script]
# 执行脚本 管理权限 sudo_run_script [script]

source config.sh

# 密钥检查
if [ ! -f ~/.ssh ];then
    mkdir ~/.ssh
    echo "mkdir ~/.ssh"
# else
    # echo "~/.ssh exist"
fi

keyfile=~/.ssh/id_rsa.$username@$hostname
option="-i $keyfile"
if [ ! -f $keyfile ];then
ssh-keygen -t rsa -b 4096 -f $keyfile -P "" -C "$username@$hostname"
# ssh-copy-id -i $keyfile.pub $username@$hostname

echo "ssh copy id selv version"
ssh $username@$hostname "cat $keyfile.pub >> .ssh/authorized_keys"
echo "ssh $username@$hostname \"cat $keyfile.pub >> .ssh/authorized_keys\""
echo "ssh copy id selv version done"

cat >> ~/.ssh/config <<EOF
Host $host
    HostName $hostname
    Port $port
    User $username
    IdentityFile $keyfile
EOF
fi

# 上传文件
function upload_file() {
    local src=$1; local dst=$2
    scp -P $port $option $src $username@$hostname:$dst
}

# 上传文件夹
function upload_floder() {
    local src=$1; local dst=$2
    scp -P $port $option -r $src $username@$hostname:$dst
}

# 执行命令
function run_command() {
    echo "[ RUN ] $*"
    local command="$1"; shift; local args="$*"
    ssh -P $port $option $username@$hostname "$command $args"
}

# 执行命令 sudo
function sudo_run_command() {
    local command="$1"; shift; local args="$*"
    run_command "echo '$password' | sudo -S $command $args"; echo
}

function _run_script() {  
    local command="$1"; shift; local script="$1"; shift; local args="$*"
    echo "command: $command"
    echo "script: $script"
    echo "args: $args"
    upload_file $script "~"
    eval "$command bash $script $args"
    run_command rm "$script"
    echo "[ OK ] $script"
}  

# 执行脚本 
function run_script() {
    local script="$1"; shift; local args="$*"
    _run_script "run_command" "$script" "$args"    
}  
  
# 执行脚本 sudo
function sudo_run_script() {        
    local script="$1"; shift; local args="$*"
    _run_script "sudo_run_command" "$script" "$args"    
}
