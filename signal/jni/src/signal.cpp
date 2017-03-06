#include<stdio.h>
#include<signal.h>
#include<time.h>

time_t sLast = 0;
static int count = 0;
static struct sigaction sOldAct;

void handler(int signal)
{
	time_t tNow = time(NULL);
	if (tNow > 2 + sLast)
	{
		printf("signal : %d\n", signal);
		sLast = tNow;
		++count;
		if (count > 2)
		{
			printf("return to sys signal : %d\n", signal);
			sOldAct.sa_handler(signal);
		}
	}
}

void use_signal()
{
	signal(SIGSEGV, handler);
}

//注册信号处理句柄
void use_sigaction()
{
	struct sigaction act;
	act.sa_handler = handler;
	//act.sa_flags = SA_RESETHAND | SA_NODEFER;
	sigaction(SIGSEGV, &act, &sOldAct);
}

//空指针异常测试
void test_null_pointer()
{
	int* p = NULL;
	*p = 0;
}

//越界测试
void test_array_beyond()
{
	char buf[5] = {0};
	char buf1[5] = {0};
	buf[6] = 0;
}

int main(void)
{
	//use_signal();
	use_sigaction();
	//test_array_beyond();
	test_null_pointer();
	printf("over\n");
	return 0;
}

