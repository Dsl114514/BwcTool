#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WIRES 6
#define MAX_COLOR_LENGTH 10
#define MAX_INPUT_LENGTH 256

int determineWireToCut(char wires[][MAX_COLOR_LENGTH], int wireCount, int lastDigitOdd);
int cutThreeWires(char wires[][MAX_COLOR_LENGTH]);
int cutFourWires(char wires[][MAX_COLOR_LENGTH], int lastDigitOdd);
int cutFiveWires(char wires[][MAX_COLOR_LENGTH], int lastDigitOdd);
int cutSixWires(char wires[][MAX_COLOR_LENGTH], int lastDigitOdd);
int hasWireColor(char wires[][MAX_COLOR_LENGTH], int wireCount, const char *color);
int countWireColor(char wires[][MAX_COLOR_LENGTH], int wireCount, const char *color);
int findLastWireColor(char wires[][MAX_COLOR_LENGTH], int wireCount, const char *color);

int main()
{
    char input[MAX_INPUT_LENGTH];
    char serialNumber[MAX_INPUT_LENGTH];
    char wires[MAX_WIRES][MAX_COLOR_LENGTH];
    int wireCount;
    int lastDigitOdd;
    int wireToCutIndex;

    while (1)
    {
        printf("炸弹拆除助手\n");
        printf("请输入电线颜色序列（用空格分隔，例如：红 蓝 白）：");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("输入错误！\n");
            return 1;
        }

        // 移除换行符
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }

        if (strlen(input) == 0)
        {
            printf("输入不能为空！\n");
            continue;
        }

        // 分割输入字符串
        char *token = strtok(input, " ");
        wireCount = 0;
        while (token != NULL && wireCount < MAX_WIRES)
        {
            strcpy(wires[wireCount], token);
            wireCount++;
            token = strtok(NULL, " ");
        }

        if (wireCount < 3 || wireCount > 6)
        {
            printf("无效的电线数量！支持3-6根电线。\n");
            continue;
        }

        printf("请输入序列号（最后一位用于判断）：");
        if (fgets(serialNumber, sizeof(serialNumber), stdin) == NULL)
        {
            printf("序列号读取失败！\n");
            return 1;
        }

        len = strlen(serialNumber);
        if (len > 0 && serialNumber[len - 1] == '\n')
        {
            serialNumber[len - 1] = '\0';
        }

        if (strlen(serialNumber) == 0)
        {
            printf("序列号不能为空！\n");
            continue;
        }

        // 检查序列号最后一位是否为数字
        char lastChar = serialNumber[strlen(serialNumber) - 1];
        if (!isdigit(lastChar))
        {
            printf("序列号最后一位必须是数字！\n");
            continue;
        }

        lastDigitOdd = (lastChar - '0') % 2 == 1;

        wireToCutIndex = determineWireToCut(wires, wireCount, lastDigitOdd);

        if (wireToCutIndex == -1)
        {
            printf("无效的电线数量！支持3-6根电线。\n");
        }
        else
        {
            printf("剪断第%d根电线 (%s)\n", wireToCutIndex + 1, wires[wireToCutIndex]);
            printf("炸弹已成功拆除！\n");
        }
    }

    return 0;
}

int determineWireToCut(char wires[][MAX_COLOR_LENGTH], int wireCount, int lastDigitOdd)
{
    switch (wireCount)
    {
    case 3:
        return cutThreeWires(wires);
    case 4:
        return cutFourWires(wires, lastDigitOdd);
    case 5:
        return cutFiveWires(wires, lastDigitOdd);
    case 6:
        return cutSixWires(wires, lastDigitOdd);
    default:
        return -1;
    }
}

int cutThreeWires(char wires[][MAX_COLOR_LENGTH])
{
    if (!hasWireColor(wires, 3, "红"))
        return 1;
    if (strcmp(wires[2], "白") == 0)
        return 2;
    if (countWireColor(wires, 3, "蓝") > 1)
        return findLastWireColor(wires, 3, "蓝");
    return 2;
}

int cutFourWires(char wires[][MAX_COLOR_LENGTH], int lastDigitOdd)
{
    int redCount = countWireColor(wires, 4, "红");
    if (redCount > 1 && lastDigitOdd)
        return findLastWireColor(wires, 4, "红");
    if (redCount == 0 && strcmp(wires[3], "黄") == 0)
        return 0;
    if (countWireColor(wires, 4, "蓝") == 1)
        return 0;
    if (countWireColor(wires, 4, "黄") > 1)
        return 3;
    return 1;
}

int cutFiveWires(char wires[][MAX_COLOR_LENGTH], int lastDigitOdd)
{
    if (strcmp(wires[4], "黑") == 0 && lastDigitOdd)
        return 3;
    int redCount = countWireColor(wires, 5, "红");
    int yellowCount = countWireColor(wires, 5, "黄");
    if (redCount == 1 && yellowCount > 1)
        return 0;
    if (!hasWireColor(wires, 5, "黑"))
        return 1;
    return 0;
}

int cutSixWires(char wires[][MAX_COLOR_LENGTH], int lastDigitOdd)
{
    int yellowCount = countWireColor(wires, 6, "黄");
    int whiteCount = countWireColor(wires, 6, "白");
    if (yellowCount == 0 && lastDigitOdd)
        return 2;
    if (yellowCount == 1 && whiteCount > 1)
        return 3;
    if (!hasWireColor(wires, 6, "红"))
        return 5;
    return 3;
}

int hasWireColor(char wires[][MAX_COLOR_LENGTH], int wireCount, const char *color)
{
    for (int i = 0; i < wireCount; i++)
    {
        if (strcmp(wires[i], color) == 0)
            return 1;
    }
    return 0;
}

int countWireColor(char wires[][MAX_COLOR_LENGTH], int wireCount, const char *color)
{
    int count = 0;
    for (int i = 0; i < wireCount; i++)
    {
        if (strcmp(wires[i], color) == 0)
            count++;
    }
    return count;
}

int findLastWireColor(char wires[][MAX_COLOR_LENGTH], int wireCount, const char *color)
{
    for (int i = wireCount - 1; i >= 0; i--)
    {
        if (strcmp(wires[i], color) == 0)
            return i;
    }
    return -1;
}
