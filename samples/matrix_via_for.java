public class Test {
    public static void main(String[] args) {
        int i = 0;
        int j = 0;
        for(; i <= 20; i = i + 1) {
            for (; j <= 20; j = j + 1) {
                System.out.print(i);
                System.out.print("vs");
                System.out.print(j);
                System.out.print(" ");
            }
            j = 0;
            System.out.print("\n");
        }
    }
}