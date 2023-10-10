drop database if exists ChatDB;
create database ChatDB;
use ChatDB;

create table User (
    id int auto_increment primary key,
    role varchar(20) not null default 'user',
    account varchar(255) not null,
    password varchar(255) not null,
    name varchar(255) not null default '无名用户',
    gender varchar(10) not null default '男',
    age int not null default 18,
    email varchar(255)
);

create table Msg (
    id int auto_increment primary key,
    from_id int not null,
    to_id int not null,
    time timestamp default current_timestamp,
    context text,
    foreign key (from_id) references User(id),
    foreign key (to_id) references User(id)
);

insert into User (role, account, password, name, gender, age, email) values
('admin', 'root', '1234', '管理员', '男', 18, 'admin@example.com'),
('user', 'user1', '1234', '张三', '男', 25, 'user1@example.com'),
('user', 'user2', '1234', '李四', '女', 30, 'user2@example.com'),
('user', 'user3', '1234', '王五', '男', 20, 'user3@example.com');


insert into Msg (from_id, to_id, context) values
(2, 3, '你好！今天过得怎么样？'),
(3, 2, '你好！我度过了一个非常愉快的一天。'),
(2, 3, '你最喜欢的电影是什么？'),
(3, 2, '《肖申克的救赎》。我认为这是一部非常经典的电影。'),
(2, 3, '你听说了吗？他们正在开发一种新的智能手机，具有无与伦比的性能。'),
(3, 2, '真的吗？那听起来非常令人兴奋！'),
(2, 3, '你最近读了什么好书吗？'),
(3, 2, '《追风筝的人》。我认为这本书非常引人入胜。'),
(2, 3, '你最喜欢的旅游目的地是哪里？'),
(3, 2, '我喜欢去夏威夷。那里的海滩非常美丽，而且空气很清新。');
