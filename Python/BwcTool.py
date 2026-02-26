import sys

def main():
    """主程序循环"""
    while True:
        print("炸弹拆除助手")
        print("请输入电线颜色序列（用空格分隔，例如：红 蓝 白）：")
        input_str = input()

        if not input_str.strip():
            print("输入不能为空！")
            return

        wires = input_str.split()
        wire_count = len(wires)

        print("请输入序列号（最后一位用于判断）：")
        serial_number = input()

        if not serial_number.strip():
            print("序列号不能为空！")
            return

        # 获取序列号最后一位字符，并判断是否为奇数
        last_char = serial_number[-1]
        # 检查最后一位是否为数字，如果不是则给出提示并退出
        if not last_char.isdigit():
            print("序列号最后一位必须是数字！")
            continue # 或者 return 来结束程序

        last_digit_odd = int(last_char) % 2 == 1

        wire_to_cut_index = determine_wire_to_cut(wires, last_digit_odd)

        if wire_to_cut_index == -1:
            print("无效的电线数量！支持3-6根电线。")
        else:
            print(f"剪断第{wire_to_cut_index + 1}根电线 ({wires[wire_to_cut_index]})")
            print("炸弹已成功拆除！")
            # 可选：如果只想执行一次，可以在此处添加 break
            # break


def determine_wire_to_cut(wires, last_digit_odd):
    """根据电线数量和序列号决定剪哪根线"""
    wire_count = len(wires)

    if wire_count == 3:
        return cut_three_wires(wires)
    elif wire_count == 4:
        return cut_four_wires(wires, last_digit_odd)
    elif wire_count == 5:
        return cut_five_wires(wires, last_digit_odd)
    elif wire_count == 6:
        return cut_six_wires(wires, last_digit_odd)
    else:
        return -1  # 不支持的电线数量


def cut_three_wires(wires):
    """处理3根电线的逻辑"""
    # 规则1: 如果没有红线，则剪断第二根线
    if not has_wire_color(wires, "红"):
        return 1  # 第二根线（索引1）

    # 规则2: 当最后一根线为白线时，剪断最后一根线
    if wires[2] == "白":
        return 2  # 最后一根线（索引2）

    # 规则3: 当有不止一根蓝线的时候，剪断最后一根蓝线
    blue_count = count_wire_color(wires, "蓝")
    if blue_count > 1:
        return find_last_wire_color(wires, "蓝")

    # 规则4: 否则，剪断最后一根线
    return 2


def cut_four_wires(wires, last_digit_odd):
    """处理4根电线的逻辑"""
    red_count = count_wire_color(wires, "红")

    # 规则1: 如果有不止一根红线且序列号末位为奇数，则剪断最后一根红线
    if red_count > 1 and last_digit_odd:
        return find_last_wire_color(wires, "红")

    # 规则2: 当没有红线且最后一根线是黄线时，剪断第一根线
    if red_count == 0 and wires[3] == "黄":
        return 0  # 第一根线（索引0）

    # 规则3: 当有且仅有一根蓝线时，剪断第一根线
    blue_count = count_wire_color(wires, "蓝")
    if blue_count == 1:
        return 0

    # 规则4: 当有不止一根黄线时，剪断最后一根线
    yellow_count = count_wire_color(wires, "黄")
    if yellow_count > 1:
        return 3  # 最后一根线（索引3）

    # 规则5: 否则，剪断第二根线
    return 1  # 第二根线（索引1）


def cut_five_wires(wires, last_digit_odd):
    """处理5根电线的逻辑"""
    # 规则1: 如果最后一根线是黑线且序列号末位为奇数，则剪断第四根线
    if wires[4] == "黑" and last_digit_odd:
        return 3  # 第四根线（索引3）

    red_count = count_wire_color(wires, "红")
    yellow_count = count_wire_color(wires, "黄")

    # 规则2: 当有且仅有一根红线，且黄线不止一根时，剪断第一根线
    if red_count == 1 and yellow_count > 1:
        return 0  # 第一根线（索引0）

    # 规则3: 当没有黑线时，剪断第二根线
    if not has_wire_color(wires, "黑"):
        return 1  # 第二根线（索引1）

    # 规则4: 否则，剪断第一根线
    return 0


def cut_six_wires(wires, last_digit_odd):
    """处理6根电线的逻辑"""
    yellow_count = count_wire_color(wires, "黄")
    white_count = count_wire_color(wires, "白")

    # 规则1: 如果没有黄线且序列号末位为奇数，则剪断第三根线
    if yellow_count == 0 and last_digit_odd:
        return 2  # 第三根线（索引2）

    # 规则2: 当有且仅有一根黄线，且白线不止一根时，剪断第四根线
    if yellow_count == 1 and white_count > 1:
        return 3  # 第四根线（索引3）

    # 规则3: 当没有红线时，剪断最后一根线
    if not has_wire_color(wires, "红"):
        return 5  # 最后一根线（索引5）

    # 规则4: 否则，剪断第四根线
    return 3


def has_wire_color(wires, color):
    """辅助函数：检查是否存在指定颜色的电线"""
    return color in wires


def count_wire_color(wires, color):
    """辅助函数：统计指定颜色电线的数量"""
    return wires.count(color)


def find_last_wire_color(wires, color):
    """辅助函数：找到最后一根指定颜色电线的索引"""
    # 使用reversed()和enumerate()来反向查找
    for i, wire in enumerate(reversed(wires)):
        if wire == color:
            # 索引需要从后面计算回来
            # 原长度 - 1 - 反向遍历时的索引
            return len(wires) - 1 - i
    return -1  # 如果没找到，返回-1


if __name__ == "__main__":
    main()
