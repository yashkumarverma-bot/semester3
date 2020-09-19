import java.util.Scanner;

public class NumberToWord {
    public static void main(String args[]) {

    }

    private String digitToWord(int digit) {
        /** handle invalid index */
        if (digit < 0 || digit > 9) {
            return "";
        }

        String[] WordStorage = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
        return WordStorage[digit];
    }
}