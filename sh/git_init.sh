#!/usr/bin/bash
# 新建git目录并关联

. run.sh

project=$1

# 远程创建目录
ssh -P $port -i  ~/.ssh/id_rsa.$username@$hostname git@$hostname "rm -rf $project"
ssh -P $port -i  ~/.ssh/id_rsa.$username@$hostname git@$hostname "rm -rf $project.git"
ssh -P $port -i  ~/.ssh/id_rsa.$username@$hostname git@$hostname "git init --bare $project.git"

# 部署钩子
post_receive=$(cat ../sh/post-receive)
post_receive=$(eval "echo \"$post_receive\"")
ssh -P $port -i  ~/.ssh/id_rsa.$username@$hostname git@$hostname "echo \"$post_receive\" > ~/$project.git/hooks/post-receive"
ssh -P $port -i  ~/.ssh/id_rsa.$username@$hostname git@$hostname "chmod +x ~/$project.git/hooks/post-receive"

# git蛋疼的无法指定ssh密钥 只能手动复制密钥
cp ~/.ssh/id_rsa.$username@$hostname ~/.ssh/id_rsa

# 若本地目录不存在 则创建目录
if [ ! -d ../$project ]; then
    mkdir ../$project
fi

# 若未进行git初始化 则初始化git
if [ ! -d "../$project.git" ]; then
    git ../$project init
fi

# 若没有初始化脚本 则给他一个默认的初始化脚本
if [ ! -d "../init.sh" ]; then
    git ../$project init
    cp init.sh ../$project
fi

# 关联远程仓库
git -C ../$project remote remove $host
git -C ../$project remote add $host git@$hostname:$project.git 

# 进行第一次提交
echo "1st commit"
git -C ../$project add *
git -C ../$project commit -m "1st commit"
git -C ../$project push -f $host master
echo "1st commit done"
