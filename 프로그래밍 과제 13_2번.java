import java.util.Scanner;

public class Stick {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int v[] = new int[N+1];
        int r[] = new int[N+1];
        r[0] = 0;
        for(int i = 1 ;i < N+1 ; i++){
            v[i] = scanner.nextInt();
        }
        for(int i = 1 ; i < N+1 ; i++){
            int q = -1;
            for(int j = 1; j <= i ; j++){
                q = Math.max(q, v[j] + r[i-j]);
            }
            r[i] = q;
        }
        System.out.println(r[N]);
    }
}
