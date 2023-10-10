#pragma once

#include <functional>
#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>
#include <exception>

// 菜单抽象
// 动态绑定
// 全局单例

/*
    Usage:

# in file chat.hpp
#pragma once

#include "headers.hpp"

inline void qq_init() {
	Menu::get_instance().add_option("1", "腾讯QQ", [&]() {
		QQ qq;
		Menu menu_qq("qq");
		menu_qq.add_option("1", "注册", [&]() { qq.regist(); });
		menu_qq.add_option("2", "登录", [&]() {
			auto user = qq.login();
			if (qq.is_login(user) == false) { return; }
			Menu menu1("个人主页");
			menu1.add_option("1", "查询个人信息", [&]() { qq.my_info(user); });
			menu1.add_option("2", "修改个人信息", [&]() { qq.change_my_info(user); });
			menu1.add_option("3", "修改密码", [&]() { qq.change_my_password(user); });
			menu1.add_option("4", "我的群聊", [&]() {
				auto menu_qq_4 = Menu("我的群聊");
				menu_qq_4.add_option("1", "查看我的群聊", [&]() { qq.my_groupes(user); });
				menu_qq_4.add_option("2", "查看群聊成员", [&]() { qq.group_info(user); });
				menu_qq_4.add_option("3", "创建群聊", [&]() { qq.create_group(user); });
				menu_qq_4.add_option("4", "加入群聊", [&]() { qq.join_group(user); });
				menu_qq_4.add_option("5", "邀请进群", [&]() { qq.invite_group(user); });
				menu_qq_4.add_option("6", "退出群聊", [&]() { qq.quit_group(user); });
				menu_qq_4.run();
			});
			menu1.add_option("5", "我的好友", [&]() {
				auto menu_qq_5 = Menu("我的好友");
				menu_qq_5.add_option("1", "查看好友", [&]() { qq.my_friends(user); });
				menu_qq_5.add_option("2", "添加好友", [&]() { qq.add_friend(user); });
				menu_qq_5.add_option("3", "删除好友", [&]() { qq.del_friend(user); });
				menu_qq_5.add_option("4", "查看共同好友", [&]() { qq.find_common_friends(user); });
				menu_qq_5.run();
			});
			menu1.add_option("6", "注销账号", [&]() { qq.deactivate(user); });
			menu1.run();
		});
		menu_qq.run();
	});
}


# in file main.cpp
#include "chat.hpp"

int main() {
	try {
		qq_init();
		auto menu = Menu::get_instance();
		menu.set_title("主菜单");
		menu.run();
	}
	catch (const std::string& err) {
		std::cout << err << std::endl;
	}
}

*/

class Menu {

private:
    
    std::string title;
    std::unordered_map<std::string, std::string> describes;
    std::unordered_map<std::string, std::function<void()>> functions;
    std::unordered_map<std::string, Menu> sub_menus;
    bool _quit = false;

public:

    static Menu& get_instance() {
        static std::shared_ptr<Menu> instance = std::make_shared<Menu>();
        return *instance;
    }

    Menu() = default;

    Menu(const std::string& title) : title(title) {}

    // 因为不是完全的单例类 所以也需要拷贝构造和移动构造
    Menu(const Menu &) = default;
    Menu(Menu&& menu) noexcept {
        this->title     = std::move(menu.title);
        this->describes = std::move(menu.describes);
        this->functions = std::move(menu.functions);
        this->title     = std::move(menu.title);
    };

    void set_title(const std::string& title) {
        this->title = title;
    }

    void add_option(const std::string& option, const std::string& describe, const std::function<void()>& function) {
        if (option == "q") {
            throw std::string("选项不能为Q：") + "title: " + title;
        }
        if (describes.count(option) || functions.count(option)) {
            throw std::string("选项已存在：") + "title: " + title + " option: " + option;
        }
        describes[option] = describe;
        functions[option] = function;
    }

    void run() {
        std::string line;
        while (! _quit) {

            // 清屏
            clear();

            // 输出标题和菜单选项
            std::cout << "********************************" << std::endl;
            std::cout << "* " << title << std::endl;
            std::cout << "********************************" << std::endl;
            for (auto& [ch, desc] : describes) {
                std::cout << "* " << ch << ": " << desc << std::endl;
            }
            std::cout << "* q: quit" << std::endl;
            std::cout << "********************************" << std::endl;

            // 获取输入
            std::getline(std::cin, line);

            // 清屏
            clear();

            // 退出菜单
            if (line == "q") {
                return;
            }

            // 进入选项
            else if (functions.count(line)) {
                std::cout << "********************************" << std::endl;
                std::cout << "* " << title << ": " << describes[line] << std::endl;
                std::cout << "********************************" << std::endl;
                functions[line]();
            }

            // 选项不存在
            else {
                clear();
                std::cout << "选项不存在" << std::endl;
            }

            // 下一轮操作
            std::cout << std::endl;
            std::cout << "按[Enter]继续" << std::endl;
            std::getline(std::cin, line);
        }
    }

    void quit() {
        _quit = true;
    }

    static void clear() { system("cls"); }

    static std::string input(const std::string& tips) {
        std::string ret;
        std::cout << "请输入 " << tips << ":";
        std::getline(std::cin, ret);
        std::cin.clear();
        return ret;
    }
};
