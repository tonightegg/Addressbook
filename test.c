#include"contact.h"
#include <windows.h>
 
void menu()
{
	printf("Communication works \nfor those who work at it\n");
	printf("                               --John Powell\n");
	printf("  ╭─────────────────────────────────╮\n");
    printf("  │        你的专属通讯录 v1.0      │\n");
    printf("  ├─────────────────────────────────┤\n");
    printf("  │   1. 添加好友     2. 删除好友   │\n");
    printf("  │   3. 查找好友     4. 修改资料   │\n");
    printf("  │   5. 好友列表     6. 重新排序   │\n");
    printf("  │   7. 重置列表     0. 暂时离开   │\n");
    printf("  ╰─────────────────────────────────╯\n");
	printf("          输入对应数字以跳转...      \n");
}
 
 
void test()
{
	int input = 0;
	contact con;//contact,论命名习惯 
	InitContact(&con);//局部变量，分配在栈上需要初始化 
	do
	{
		menu();//菜单
		printf("选择功能->");
        // 如果 scanf 没读到 1 个整数，说明输入了字母或乱码
        if (scanf("%d", &input) != 1) 
        {
            printf("输入错误，请输入数字！\n");
            // 清空输入缓冲区里的所有垃圾字符
            while (getchar() != '\n'); 
            continue; // 直接跳过后面的 switch，重新循环
        }
		switch (input)
		{
		case ADD:
			//增加信息
			AddContact(&con);
			break;
		case DEL:
			//删除联系人
			DelContact(&con);
			break;
		case SEARCH:
			//查找联系人
			SearchContact(&con);
			break;
		case MOD:
			//修改联系人
			ModContact(&con);
			break;
		case PRINT:
			//打印通讯录
			PrintContact(&con);
			break;
		case SORT:
			//联系人排序
			SortContact(&con);
			break;
		case EMPTY:
			//清空联系人
			EmptyContact(&con);
			break;
		case EXIT:
			printf("正在退出程序，期待与你的下次见面~\n");
			break;
		case 520:
			printf("感谢喜欢！\n喂，不要瞎摁啊。\n");
		case 233:
			printf("( ゜- ゜)つロ 干杯~\n");
		default:
			printf("跳转失败，请检查是否存在输入错误!\n");
			break;
 
		}
	} while (input);
 
}
 
int main()
{
	SetConsoleOutputCP(65001);
	test();
	return 0;
}