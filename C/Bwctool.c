using System;

class Program
{
    static void Main()
    {
        while (true)
        {
            Console.WriteLine("炸弹拆除助手");
            Console.WriteLine("请输入电线颜色序列（用空格分隔，例如：红 蓝 白）：");
            string input = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(input))
            {
                Console.WriteLine("输入不能为空！");
                return;
            }

            string[] wires = input.Split(' ');
            int wireCount = wires.Length;

            Console.WriteLine("请输入序列号（最后一位用于判断）：");
            string serialNumber = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(serialNumber))
            {
                Console.WriteLine("序列号不能为空！");
                return;
            }

            char lastDigit = serialNumber[serialNumber.Length - 1];
            bool lastDigitOdd = (lastDigit - '0') % 2 == 1;

            int wireToCut = DetermineWireToCut(wires, lastDigitOdd);

            if (wireToCut == -1)
            {
                Console.WriteLine("无效的电线数量！支持3-6根电线。");
            }
            else
            {
                Console.WriteLine($"剪断第{wireToCut + 1}根电线 ({wires[wireToCut]})");
                Console.WriteLine("炸弹已成功拆除！");
            }
        }

        static int DetermineWireToCut(string[] wires, bool lastDigitOdd)
        {
            int wireCount = wires.Length;

            switch (wireCount)
            {
                case 3:
                    return CutThreeWires(wires);
                case 4:
                    return CutFourWires(wires, lastDigitOdd);
                case 5:
                    return CutFiveWires(wires, lastDigitOdd);
                case 6:
                    return CutSixWires(wires, lastDigitOdd);
                default:
                    return -1;
            }
        }

        static int CutThreeWires(string[] wires)
        {
            // 规则1: 如果没有红线，则剪断第二根线
            if (!HasWireColor(wires, "红"))
                return 1; // 第二根线（索引1）

            // 规则2: 当最后一根线为白线时，剪断最后一根线
            if (wires[2] == "白")
                return 2; // 最后一根线（索引2）

            // 规则3: 当有不止一根蓝线的时候，剪断最后一根蓝线
            int blueCount = CountWireColor(wires, "蓝");
            if (blueCount > 1)
                return FindLastWireColor(wires, "蓝");

            // 规则4: 否则，剪断最后一根线
            return 2;
        }

        static int CutFourWires(string[] wires, bool lastDigitOdd)
        {
            int redCount = CountWireColor(wires, "红");

            // 规则1: 如果有不止一根红线且序列号末位为奇数，则剪断最后一根红线
            if (redCount > 1 && lastDigitOdd)
                return FindLastWireColor(wires, "红");

            // 规则2: 当没有红线且最后一根线是黄线时，剪断第一根线
            if (redCount == 0 && wires[3] == "黄")
                return 0; // 第一根线（索引0）

            // 规则3: 当有且仅有一根蓝线时，剪断第一根线
            int blueCount = CountWireColor(wires, "蓝");
            if (blueCount == 1)
                return 0;

            // 规则4: 当有不止一根黄线时，剪断最后一根线
            int yellowCount = CountWireColor(wires, "黄");
            if (yellowCount > 1)
                return 3; // 最后一根线（索引3）

            // 规则5: 否则，剪断第二根线
            return 1; // 第二根线（索引1）
        }

        static int CutFiveWires(string[] wires, bool lastDigitOdd)
        {
            // 规则1: 如果最后一根线是黑线且序列号末位为奇数，则剪断第四根线
            if (wires[4] == "黑" && lastDigitOdd)
                return 3; // 第四根线（索引3）

            int redCount = CountWireColor(wires, "红");
            int yellowCount = CountWireColor(wires, "黄");

            // 规则2: 当有且仅有一根红线，且黄线不止一根时，剪断第一根线
            if (redCount == 1 && yellowCount > 1)
                return 0; // 第一根线（索引0）

            // 规则3: 当没有黑线时，剪断第二根线
            if (!HasWireColor(wires, "黑"))
                return 1; // 第二根线（索引1）

            // 规则4: 否则，剪断第一根线
            return 0;
        }

        static int CutSixWires(string[] wires, bool lastDigitOdd)
        {
            int yellowCount = CountWireColor(wires, "黄");
            int whiteCount = CountWireColor(wires, "白");

            // 规则1: 如果没有黄线且序列号末位为奇数，则剪断第三根线
            if (yellowCount == 0 && lastDigitOdd)
                return 2; // 第三根线（索引2）

            // 规则2: 当有且仅有一根黄线，且白线不止一根时，剪断第四根线
            if (yellowCount == 1 && whiteCount > 1)
                return 3; // 第四根线（索引3）

            // 规则3: 当没有红线时，剪断最后一根线
            if (!HasWireColor(wires, "红"))
                return 5; // 最后一根线（索引5）

            // 规则4: 否则，剪断第四根线
            return 3;
        }

        // 辅助函数：检查是否存在指定颜色的电线
        static bool HasWireColor(string[] wires, string color)
        {
            foreach (string wire in wires)
            {
                if (wire == color)
                    return true;
            }
            return false;
        }

        // 辅助函数：统计指定颜色电线的数量
        static int CountWireColor(string[] wires, string color)
        {
            int count = 0;
            foreach (string wire in wires)
            {
                if (wire == color)
                    count++;
            }
            return count;
        }

        // 辅助函数：找到最后一根指定颜色电线的索引
        static int FindLastWireColor(string[] wires, string color)
        {
            for (int i = wires.Length - 1; i >= 0; i--)
            {
                if (wires[i] == color)
                    return i;
            }
            return -1; // 如果没找到，返回-1
        }
    }
}
