#include"contact.h"
 
//初始化
void InitContact(contact* pc)
{
	assert(pc);
	memset(pc->data, 0, sizeof(pc->data));
	pc->sz = 0;
}
 
//暂停
void Pause(){
	printf("\n请输入任意键以回到主菜单...\n");
	// 清理掉上面输入留下的所有回车和垃圾
    while (getchar() != '\n'); 
    getchar(); // 吃掉用户按下的那个回车
}
 
 
//增加信息
void AddContact(contact* pc)
{
	if (pc->sz == DATA_MAX)
	{
		printf("啊偶，好友列表似乎满了，无法继续添加。\n");
		return;
	}
	assert(pc);
	printf("请输入好友的名字->");
	scanf(" %s", pc->data[pc->sz].name);
	printf("请输入好友的年龄->");
	scanf(" %d", &(pc->data[pc->sz].age));
	printf("请输入好友的性别->");
	scanf(" %s", pc->data[pc->sz].sex);
	printf("请输入好友的电话->");
	scanf(" %s", pc->data[pc->sz].tele);
	printf("请输入好友的地址->");
	scanf(" %s", pc->data[pc->sz].address);
	pc->sz++;
	printf("添加成功，祝你们相处愉快！\n恭喜你目前拥有 %d 位好友啦~",pc->sz);
	Pause();
}
 
 
 
//打印通讯录
void PrintContact(contact* pc)
{
	assert(pc);
	int i = 0;
	printf("%-5s %-10s %-5s %-6s %-12s %-15s\n", "序号" , "姓名", "年龄", "性别", "电话", "地址");
	for (i = 0; i < pc->sz; i++)
	{
		printf("%-5d %-10s %-5d %-6s %-12s %-15s\n", i+1, pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].address);
	}
	printf("\n");
	Pause();
	}
	
//判断名字是否一致
int Find_Name(contact* pc, char* name)
{
	assert(pc&&name);
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (0 == strcmp(pc->data[i].name, name))
		{
			return i;
		}
	}
	return -1;
}
 
//删除联系人
void DelContact(contact* pc)
{
	assert(pc);
	char key[NAME_MAX];
	if (pc->sz == 0)
	{
		printf("好友列表空空如也...快去添加些好友吧~\n");
		return;
	}
	printf("输入需要删除的好友的姓名(支持模糊查找)\n");
	scanf(" %s", key);
	int found_count = 0; 
    int match_indexes[100]; 
    for (int i = 0; i < pc->sz; i++)
    {
        if (strstr(pc->data[i].name, key) != NULL)
        {
            match_indexes[found_count] = i; // 把下标存进数组
            found_count++;
        }
    }
	int pos = 0;
    if (found_count == 0)
    {
        printf("没有找到要查找的好友哦，快看看是不是打错字了。\n");
    }
    else if (found_count == 1)
    {
        int pos = match_indexes[0];
        printf("找到一个含有关键词的联系人！\n");
        printf("%-10s %-5s %-6s %-12s %-15s\n", "姓名", "年龄", "性别", "电话", "地址");
        printf("%-10s %-5d %-6s %-12s %-15s\n", 
            pc->data[pos].name, pc->data[pos].age, pc->data[pos].sex, pc->data[pos].tele, pc->data[pos].address);
    }
    else
    {
        printf("找到 %d 个包含 [%s] 的联系人：\n", found_count, key);
        for (int i = 0; i < found_count; i++)
        {
            int pos = match_indexes[i];
            printf("%d. %s (%d岁)\n", i + 1, pc->data[pos].name, pc->data[pos].age);
        }
        int choice = 0;
        printf("\n请输入序号查看详情 (输入 0 取消) -> ");
        scanf(" %d", &choice);

        if (choice < 1 || choice > found_count)
        {
            printf("已取消删除。\n");
            Pause();
            return;
        }
	}
	//二次确认
	printf("确定要删除 [%s] 吗？(按 1 确认，其他任意键取消) -> ", pc->data[pos].name);
    int confirm = 0;
    scanf(" %d", &confirm);
    if (confirm != 1)
    {
        printf("已取消删除。\n");
        Pause();
        return;
    }

	for (int j = pos; j < pc->sz - 1; j++)
    {
        pc->data[j] = pc->data[j + 1];
    }
    pc->sz--;
    printf("成功删除！\n");
	PrintContact(pc);
    Pause();
}
 
 
//查找联系人(支持模糊查找)
void SearchContact(contact* pc)
{
	assert(pc);
	char key[NAME_MAX];
	if (pc->sz == 0)
	{
		printf("好友列表空空如也...快去添加些好友吧~\n");
		Pause();
		return;
	}
	printf("输入要查找的好友的姓名(支持模糊查找)\n");
	scanf(" %s",key);

	int found_count = 0;
	int match_indexes[100];

	for(int i=0;i < pc->sz;i++){
		if(strstr(pc->data[i].name,key) != NULL){
			match_indexes[found_count] = i;
			found_count++;
		}
	}
	if (found_count==0)
	{
		printf("没有找到要查找的好友哦，快看看是不是打错字了。\n");
	}
	else if(found_count==1)
	{
		int pos = match_indexes[0];
		printf("已为你找到该好友，Ta的信息如下：\n");
		printf("%-10s %-5s %-6s %-12s %-15s\n", "姓名", "年龄", "性别", "电话", "地址");
		printf("%-10s %-5d %-6s %-12s %-15s\n", pc->data[pos].name, pc->data[pos].age, pc->data[pos].sex,
			pc->data[pos].tele, pc->data[pos].address);
	}
	else{
		printf("找到了 %d 个包含 [%s] 的好友：\n",found_count,key);
		for (int i = 0; i < found_count; i++)
        {
            int pos = match_indexes[i];
            printf("%d. %s (%d岁)\n", i + 1, pc->data[pos].name, pc->data[pos].age);
        }

		int choice = 0;
        printf("\n请输入序号查看详情 (输入 0 取消) -> ");
        scanf(" %d", &choice);
        if (choice > 0 && choice <= found_count)
        {
            int pos = match_indexes[choice - 1];
            printf("\n--- 详细信息 ---\n");
            printf("姓名: %s\n", pc->data[pos].name);
            printf("年龄: %d\n", pc->data[pos].age);
            printf("性别: %s\n", pc->data[pos].sex);
            printf("电话: %s\n", pc->data[pos].tele);
            printf("地址: %s\n", pc->data[pos].address);
        }
        else
        {
            printf("已取消查看。\n");
        }
    }
	Pause();
}
 
 
//修改联系人
void ModContact(contact* pc)
{
	assert(pc);
	char name[NAME_MAX];
	if (pc->sz == 0)
	{
		printf("通讯录没有联系人\n");
		return;
	}
	printf("输入需要修改联系人的姓名->");
	scanf(" %s", name);
	int pos = Find_Name(pc, name);
	if (pos == -1)
	{
		printf("没有找到要修改的好友哦，快看看是不是打错名字了。\n");
	}
	else
	{
		printf("输入新的姓名->");
		scanf(" %s", pc->data[pos].name);
		printf("输入新的年龄->");
		scanf(" %d", &(pc->data[pos].age));
		printf("输入新的性别->");
		scanf(" %s", pc->data[pos].sex);
		printf("输入新的电话->");
		scanf(" %s", pc->data[pos].tele);
		printf("输入新的地址->");
		scanf(" %s", pc->data[pos].address);
		printf("修改成功！\n这就是你全新的好友列表了:\n");
		PrintContact(pc);
	}
	Pause();
}
 
 
//清空联系人
void EmptyContact(contact* pc)
{
	assert(pc);
	char q =0;
	printf("你确定要重置列表（清空所有好友）吗\n要考虑清楚哦...(Y/N)\n");
	getchar();
	scanf(" %c", &q);
	if (q=='Y' || q=='y')
	{
		int i = 0;
		for (i = pc->sz - 1; i > 0; i--)
		{
			pc->data[i - 1] = pc->data[i];
			pc->sz--;
		}
		if (pc->sz == 1)
		{
			pc->sz--;
		}
		//打印
		printf("列表已重置\n");
		PrintContact(pc);
	}
	else
	{
		printf("已取消重置，一定要考虑清楚哦~\n");
		return;
	}
	Pause();
	
}
 
//qsort排序
int con_name(const void* e1, const void* e2)
{
	return (strcmp(((contact*)e1)->data->name , ((contact*)e2)->data->name));
}
 
//联系人排序
void SortContact(contact* pc)
{
	assert(pc);
	qsort(pc->data, pc->sz, sizeof(pc->data[0]), con_name);
	//打印
	printf("排序完成!\n这就是你全新的好友列表了:\n");
	PrintContact(pc);
	Pause();
 
}
 
 