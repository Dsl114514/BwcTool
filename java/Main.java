// 文件必须命名为 Main.java
import java.io.UnsupportedEncodingException;
import java.util.Scanner;
import java.util.stream.IntStream;

public class Main {

    public static void main(String[] args) throws UnsupportedEncodingException {
        // 关键更改：明确使用 GBK 编码创建 Scanner，以匹配 Windows CMD 的默认编码
        // System.in 是字节流，Scanner 需要知道如何将其解码为字符。
        // 如果您的系统区域设置不是简体中文，可能需要调整 charsetName，例如 "windows-1252"
        try (Scanner scanner = new Scanner(System.in, "GBK")) {
            while (true) {
                System.out.println("炸弹拆除助手");
                System.out.print("请输入电线颜色序列（用空格分隔，例如：红 蓝 白）：");
                String input = scanner.nextLine();

                if (input.trim().isEmpty()) {
                    System.out.println("输入不能为空！程序退出。");
                    return;
                }

                String[] wires = input.split("\\s+");

                System.out.print("请输入序列号（最后一位用于判断）：");
                String serialNumber = scanner.nextLine();

                if (serialNumber.trim().isEmpty()) {
                    System.out.println("序列号不能为空！程序退出。");
                    return;
                }

                char lastDigit = serialNumber.charAt(serialNumber.length() - 1);
                boolean lastDigitIsOdd = Character.isDigit(lastDigit) && (lastDigit - '0') % 2 == 1;

                int wireToCutIndex = switch (wires.length) {
                    case 3 -> cutThreeWires(wires);
                    case 4 -> cutFourWires(wires, lastDigitIsOdd);
                    case 5 -> cutFiveWires(wires, lastDigitIsOdd);
                    case 6 -> cutSixWires(wires, lastDigitIsOdd);
                    default -> -1;
                };

                if (wireToCutIndex == -1) {
                    System.out.println("无效的电线数量！支持3-6根电线。");
                } else {
                    // 输出时同样需要确保控制台能正确显示
                    System.out.printf("剪断第%d根电线 (%s)%n", wireToCutIndex + 1, wires[wireToCutIndex]);
                    System.out.println("炸弹已成功拆除！");
                }
            }
        }
    }

    private static int cutThreeWires(String[] wires) {
        if (!hasWireColor(wires, "红")) {
            return 1;
        }
        if ("白".equals(wires[2])) {
            return 2;
        }
        if (countWireColor(wires, "蓝") > 1) {
            return findLastWireColor(wires, "蓝");
        }
        return 2;
    }

    private static int cutFourWires(String[] wires, boolean lastDigitIsOdd) {
        int redCount = (int) countWireColor(wires, "红");
        if (redCount > 1 && lastDigitIsOdd) {
            return findLastWireColor(wires, "红");
        }
        if (redCount == 0 && "黄".equals(wires[3])) {
            return 0;
        }
        if (countWireColor(wires, "蓝") == 1) {
            return 0;
        }
        if (countWireColor(wires, "黄") > 1) {
            return 3;
        }
        return 1;
    }

    private static int cutFiveWires(String[] wires, boolean lastDigitIsOdd) {
        if ("黑".equals(wires[4]) && lastDigitIsOdd) {
            return 3;
        }
        int redCount = (int) countWireColor(wires, "红");
        int yellowCount = (int) countWireColor(wires, "黄");
        if (redCount == 1 && yellowCount > 1) {
            return 0;
        }
        if (!hasWireColor(wires, "黑")) {
            return 1;
        }
        return 0;
    }

    private static int cutSixWires(String[] wires, boolean lastDigitIsOdd) {
        int yellowCount = (int) countWireColor(wires, "黄");
        int whiteCount = (int) countWireColor(wires, "白");
        if (yellowCount == 0 && lastDigitIsOdd) {
            return 2;
        }
        if (yellowCount == 1 && whiteCount > 1) {
            return 3;
        }
        if (!hasWireColor(wires, "红")) {
            return 5;
        }
        return 3;
    }

    private static boolean hasWireColor(String[] wires, String color) {
        return java.util.Arrays.stream(wires).anyMatch(color::equals);
    }

    private static int countWireColor(String[] wires, String color) {
        return (int) java.util.Arrays.stream(wires).filter(color::equals).count();
    }

    private static int findLastWireColor(String[] wires, String color) {
        for (int i = wires.length - 1; i >= 0; i--) {
            if (color.equals(wires[i])) {
                return i;
            }
        }
        return -1;
    }
}
