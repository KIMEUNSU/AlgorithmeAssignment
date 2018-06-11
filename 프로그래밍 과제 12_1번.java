import java.util.Scanner;

public class MatrixChain {
    int num;        // 입력 행렬 개수
    int v[][][];    // 행렬의 min 조합을 저장하는 배열
    int b[];        // 괄호 갯수 저장

    public static void main(String[] args) {
        MatrixChain matrixChain = new MatrixChain();
        Scanner scanner = new Scanner(System.in);
        matrixChain.num = scanner.nextInt();
        int N = matrixChain.num;        // 입력 행렬 개수
        matrixChain.v = new int [N+1][N+1][4];
        matrixChain.b = new int[N+1];
        int p[] = new int[N + 1];       // 연산량
        int m[][] = new int[N+1][N+1];  // 최소 계산 횟수
        for (int i = 0; i < N+1; i++) {
            p[i] = scanner.nextInt();
        }
        // matrixChain
        // 행렬의 대각선 값은 다 0으로 초기화
        // 대각선의 개수는 N-1 개
        for(int r = 1; r <= N-1; r++){
            // 대각선 안에있는 값들의 개수는 N-r개
            for(int i = 1; i <= N - r; i++){
                int j = i + r;
                // k = i 인 경우
                m[i][j] = m[i+1][j] + p[i-1]*p[i]*p[j];
                matrixChain.v[i][j][0] = i;
                matrixChain.v[i][j][1] = i;
                matrixChain.v[i][j][2] = i+1;
                matrixChain.v[i][j][3] = j;
                for(int k = i+1; k <= j-1; k++){
                    if(m[i][j] > m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]) {
                        m[i][j] = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                        matrixChain.v[i][j][0] = i;
                        matrixChain.v[i][j][1] = k;
                        matrixChain.v[i][j][2] = k+1;
                        matrixChain.v[i][j][3] = j;
                        //System.out.println(k);
                    }
                }
            }
        }
        // 계산 순서 출력
        matrixChain.recursive(1, N);
        for(int i = 1 ;i  < N+1 ;i++){
            if(matrixChain.b[i] > 0){
                while(matrixChain.b[i] != 0){
                    System.out.print("(");
                    matrixChain.b[i]--;
                }
                System.out.print("A"+i);
            }
            else if( matrixChain.b[i] == 0){
                System.out.print("A"+i);
            }
            else if(matrixChain.b[i] < 0){
                System.out.print("A"+i);
                while(matrixChain.b[i] != 0){
                    System.out.print(")");
                    matrixChain.b[i]++;
                }
            }
        }
        System.out.println();
        System.out.println(m[1][N]);
    }
    void recursive(int i, int j){
        if(i == j)
            return;

        int x1 = v[i][j][0];
        int y1 = v[i][j][1];
        int x2 = v[i][j][2];
        int y2 = v[i][j][3];

        b[x1] += 1; b[x2] += 1;
        b[y1] -= 1; b[y2] -= 1;

        recursive(x1, y1);
        recursive(x2, y2);
        return;
    }
}