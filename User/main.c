#include "stm32f10x.h"                  // Device header
#include "stdlib.h"
#include "string.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "AD.h"

uint32_t i, j, k, m, n, js, max, t, v, step;
uint32_t f1, f2, f3, f4;
uint32_t a[17];
uint32_t b[17];
uint32_t c[17];

int main(void)
{
	Key_Init();
	OLED_Init();
	AD_Init();
	while(1)
	{
		OLED_Clear();
		memset(a, 0, 17 * sizeof(int));//主操作数组
		memset(b, 0, 17 * sizeof(int));//对比数组,比较操作后a数组是否有变动
		memset(c, 0, 17 * sizeof(int));//索引数组
		step = 0;//记步归零
		v = 4;//4*4的2048
		f4 = 1;//初次生成判断
		while (1)
		{
			k = 0;
			f1 = 0;
			f2 = 0;
			f3 = 0;
			memset(c, 0, 17 * sizeof(int));
			for (i = 1; i <= v * v; i++)//判断操作后a数组是否有变动
			{
				if (a[i] != b[i])
				{
					f3 = 1;
					break;
				}
			}
			for (i = 1; i <= v * v; i++)//判断是否还有空位置
			{
				if (a[i] == 0)
				{
					k++;
					c[k] = i;
				}
			}
			if ((k != 0 && f3 == 1) || f4 == 1)//若有变动且有空位则开始随机生成
			{
				srand(AD_GetValue());//使用悬空引脚读取外部模拟电压作随机数种子
				a[c[rand() % k + 1]] = 2;
				step = step + 1;
				f4 = 0;
			}
			else if(k == 0)//否则进入游戏结束判断
			{
				for (i = 1; i <= v; i++)//列移动判断
				{
					for (j = 0; j <= v - 2; j++)
					{
						if (a[j * v + i] == a[(j + 1) * v + i])
						{
							f1 = 1;
							break;
						}
					}
				}
				for (j = 0; j <= v - 1; j++)//行移动判断
				{
					for (i = 1; i <= v - 1; i++)
					{
						if (a[j * v + i] == a[j * v + i + 1])
						{
							f2 = 1;
							break;
						}
					}
				}
				if (f1 == 0 && f2 == 0)//行列均无法移动,游戏结束
				{
					max = 0;
					for (i = 1; i <= v * v; i++)
					{
						if (a[i] > max)
							max = a[i];//更新最大合成数
					}
					OLED_Clear();
					OLED_ShowString(1, 1, "Game Over!");
					OLED_ShowString(2, 1, "MaxNum:");
					OLED_ShowNum(2, 8, max, 3);
					OLED_ShowString(3, 1, "Step:");
					OLED_ShowNum(3, 6, step, 5);
					OLED_ShowString(4, 1, "Click to restart");
					Delay_ms(1000);
					while(Key_GetNum() == 0);
					break;
				}
			}
			for (i = 0; i < 4; i++)//输出主操作数组至OLED屏
			{
				if (a[i * 4 + 1] != 0)
				{
					if (a[i * 4 + 1] < 10)
					{
						OLED_ShowString(i + 1, 1, "   ");
						OLED_ShowNum(i + 1, 4, a[i * 4 + 1], 1);
					}
					else if (a[i * 4 + 1] < 100)
					{
						OLED_ShowString(i + 1, 1, "  ");
						OLED_ShowNum(i + 1, 3, a[i * 4 + 1], 2);
					}
					else if (a[i * 4 + 1] < 1000)
					{
						OLED_ShowString(i + 1, 1, " ");
						OLED_ShowNum(i + 1, 2, a[i * 4 + 1], 3);
					}
					else
					{
						OLED_ShowNum(i + 1, 1, a[i * 4 + 1], 4);
					}	
				}
				else
				{
					OLED_ShowString(i + 1, 1, "    ");
				}
				if (a[i * 4 + 2] != 0)
				{
					if (a[i * 4 + 2] < 10)
					{
						OLED_ShowString(i + 1, 5, "   ");
						OLED_ShowNum(i + 1, 8, a[i * 4 + 2], 1);
					}
					else if (a[i * 4 + 2] < 100)
					{
						OLED_ShowString(i + 1, 5, "  ");
						OLED_ShowNum(i + 1, 7, a[i * 4 + 2], 2);
					}
					else if (a[i * 4 + 2] < 1000)
					{
						OLED_ShowString(i + 1, 5, " ");
						OLED_ShowNum(i + 1, 6, a[i * 4 + 2], 3);
					}
					else
					{
						OLED_ShowNum(i + 1, 5, a[i * 4 + 2], 4);
					}
				}
				else
				{
					OLED_ShowString(i + 1, 5, "    ");
				}
				if (a[i * 4 + 3] != 0)
				{
					if (a[i * 4 + 3] < 10)
					{
						OLED_ShowString(i + 1, 9, "   ");
						OLED_ShowNum(i + 1, 12, a[i * 4 + 3], 1);
					}
					else if (a[i * 4 + 3] < 100)
					{
						OLED_ShowString(i + 1, 9, "  ");
						OLED_ShowNum(i + 1, 11, a[i * 4 + 3], 2);
					}
					else if (a[i * 4 + 3] < 1000)
					{
						OLED_ShowString(i + 1, 9, " ");
						OLED_ShowNum(i + 1, 10, a[i * 4 + 3], 3);
					}
					else
					{
						OLED_ShowNum(i + 1, 9, a[i * 4 + 3], 4);
					}
				}
				else
				{
					OLED_ShowString(i + 1, 9, "    ");
				}
				if (a[i * 4 + 4] != 0)
				{
					if (a[i * 4 + 4] < 10)
					{
						OLED_ShowString(i + 1, 13, "   ");
						OLED_ShowNum(i + 1, 16, a[i * 4 + 4], 1);
					}
					else if (a[i * 4 + 4] < 100)
					{
						OLED_ShowString(i + 1, 13, "  ");
						OLED_ShowNum(i + 1, 15, a[i * 4 + 4], 2);
					}
					else if (a[i * 4 + 4] < 1000)
					{
						OLED_ShowString(i + 1, 13, " ");
						OLED_ShowNum(i + 1, 14, a[i * 4 + 4], 3);
					}
					else
					{
						OLED_ShowNum(i + 1, 13, a[i * 4 + 4], 4);
					}
				}
				else
				{
					OLED_ShowString(i + 1, 13, "    ");
				}
			}
			for (i = 1; i <= v * v; i++)//复制a数组操作前状态
			{
				b[i] = a[i];
			}
			if (Key_GetNum() == 1)//向左落底
			{
				for (j = 1; j <= v; j++)
				{
					k = (j - 1) * v + 1;
					for (i = 1; i <= v; i++)
					{
						m = (j - 1) * v + i;
						if (a[m] != 0)
						{
							if (m % v == 0)
							{
								n = 0;
							}
							else
							{
								for (n = m + 1; n <= j * v; n++)
								{
									if (a[n] != 0 || n % v == 0)
										break;
								}
								i = (n - 1) % v;
							}
							if (a[m] == a[n])
							{
								a[k] = a[m] * 2;
								a[n] = 0;
							}
							else
							{
								a[k] = a[m];
							}
							if (m != k)
								a[m] = 0;
							k = k + 1;
						}
					}
				}
			}
			else if (Key_GetNum() == 2)//向右落底
			{
				for (j = 1; j <= v; j++)
				{
					k = j * v;
					for (i = v; i >= 1; i--)
					{
						m = (j - 1) * v + i;
						if (a[m] != 0)
						{
							if (m % v == 1)
							{
								n = 0;
							}
							else
							{
								for (n = m - 1; n >= (j - 1) * v + 1; n--)
								{
									if (a[n] != 0 || n % v == 1)
										break;
								}
								i = n % v + 1;
							}
							if (a[m] == a[n])
							{
								a[k] = a[m] * 2;
								a[n] = 0;
							}
							else
							{
								a[k] = a[m];
							}
							if (m != k)
								a[m] = 0;
							k = k - 1;
						}
					}
				}
			}
			else if (Key_GetNum() == 3)//向上落底
			{
				for (i = 1; i <= v; i++)
				{
					k = i;
					for (j = 1; j <= v; j++)
					{
						m = (j - 1) * v + i;
						if (a[m] != 0)
						{
							if (m > (v - 1) * v)
							{
								n = 0;
							}
							else
							{
								for (n = m + v; n <= i + (v - 1) * v; n = n + v)
								{
									if (a[n] != 0 || (n - 1) / v + 1 == v)
										break;
								}
								j = (n - 1) / v;
							}
							if (a[m] == a[n])
							{
								a[k] = a[m] * 2;
								a[n] = 0;
							}
							else
							{
								a[k] = a[m];
							}
							if (m != k)
								a[m] = 0;
							k = k + v;
						}
					}
				}
			}
			else if (Key_GetNum() == 4)//向下落底
			{
				for (i = 1; i <= v; i++)
				{
					k = i + (v - 1) * v;
					for (j = v; j >= 1; j--)
					{
						m = (j - 1) * v + i;
						if (a[m] != 0)
						{
							if (m <= v)
							{
								n = 0;
							}
							else
							{
								for (n = m - v; n >= i; n = n - v)
								{
									if (a[n] != 0 || (n - 1) / v == 0)
										break;
								}
								j = (n - 1) / v + 2;
							}
							if (a[m] == a[n])
							{
								a[k] = a[m] * 2;
								a[n] = 0;
							}
							else
							{
								a[k] = a[m];
							}
							if (m != k)
								a[m] = 0;
							k = k - v;
						}
					}
				}
			}
		}
	}
}
