import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LCS {
    int c[][];
    String x;
    String y;
    char[] r;
    int index = 0;
    public static void main(String[] args){
        LCS lcs = new LCS();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        try {
            lcs.x = br.readLine();
            lcs.y = br.readLine();
        }catch(IOException e){}
        lcs.c = new int[lcs.x.length()+1][lcs.y.length()+1];
        lcs.r = new char[Math.max(lcs.x.length(), lcs.y.length())];
        System.out.println(lcs.Lcs(lcs.x.length(), lcs.y.length()));
        lcs.GetLcsString(lcs.x.length(), lcs.y.length());
        for(int i = lcs.r.length-1; i >= 0 ; i--){
            System.out.print(lcs.r[i]);
        }
        System.out.println();
    }

    int Lcs(int m, int n){
        for(int i =0 ;i <= m ; i++){
            c[i][0] = 0;
        }
        for(int j = 0 ; j <= n; j++){
            c[0][j] = 0;
        }
        for(int i= 1 ;i <=m ; i++){
            for(int j = 1; j <= n ; j++){
                if(x.charAt(i-1) == y.charAt(j-1)) {
                    c[i][j] = c[i - 1][j - 1] + 1;
                }
                else
                    c[i][j] = Math.max(c[i-1][j], c[i][j-1]);
            }
        }
        return c[m][n];
    }
    void GetLcsString(int m, int n){
        if(m == 0 || n == 0)
            return;
        if(x.charAt(m-1) == y.charAt(n-1)){
            r[index++] = x.charAt(m-1);
            m -=1; n-=1;
        }
        else if(c[m-1][n] >= c[m][n-1]){
            m = m-1;
        }
        else{
            n = n-1;
        }
        GetLcsString(m, n);
    }
}
