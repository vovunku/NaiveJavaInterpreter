public class Test {
    public static void main(String[] args) {
        int a = 1;
        int b = 2;
        int c = a + b;
        System.out.print(c * 10 - 4 / 2);
        String d = "d";
        String e = "e";
        String f = d + e;
        System.out.print("\n");
        System.out.print(f + f);
        bool g = false;
        bool h = true;
        {
            System.out.print("\n");
            System.out.print(g + h);
        }
        System.out.print("\n");
        if(g) {
            System.out.print("ohio");
        } else {
            System.out.print("ohmagad");
        }
        System.out.print("\n");
        if(h) {
            System.out.print("ohio");
        } else {
            System.out.print("ohmagad");
        }
        System.out.print("\n");
        while(h) {
            h = false;
            System.out.print("hicutiepie!\n");
        }
        int complex = 0;
        System.out.print(complex + 1);
        while(!(complex == 10)) {
            System.out.print("Oway: ");
            System.out.print(complex);
            System.out.print("\n");
            complex = complex + 1;
        }
    }
}