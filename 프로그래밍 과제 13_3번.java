
import java.util.Scanner;
import java.util.Vector;

public class SPC {
    Vector<Node> nodes = new Vector();
    MinPriorityQueue minPriorityQueue = new MinPriorityQueue();
    Vector<Node> S = new Vector();
    int s, t;
    public class Node {
        Node next;
        int num;
        int weight;
        int count = 1;
        double d = Double.MAX_VALUE;
        
    }
    public class MinPriorityQueue{
        public Vector<Node> minHeap = new Vector();
        int sortedNum = 0;

        public void Add(Node p){
            minHeap.add(p);
            int i = minHeap.size() - 1;
            while(i > 0 && minHeap.elementAt(PARENT(i)).d > minHeap.elementAt(i).d){
                //Swap(minHeap.elementAt(PARENT(i)), minHeap.elementAt(i));
                Node tmp = minHeap.elementAt(PARENT(i));
                minHeap.setElementAt(minHeap.elementAt(i), PARENT(i));
                minHeap.setElementAt(tmp, i);
                i = PARENT(i);
            }
        }
        public Node ExtractMin(){
            if(minHeap.size() < 0)
                return null;
            Node min = minHeap.elementAt(0);
            //Swap(minHeap.elementAt(0), minHeap.elementAt(minHeap.size()-1));
            Node tmp = minHeap.elementAt(0);
            minHeap.setElementAt(minHeap.elementAt(minHeap.size()-1), 0);
            minHeap.setElementAt(tmp, minHeap.size()-1);

            minHeap.remove(minHeap.size()-1);
            MinHeapify(0);
            return min;
        }
        public void BuildHeap(){
            for(int i = (minHeap.size() - 1) / 2 ; i>= 0 ; i--){
                MinHeapify(i);
            }
        }
        public void MinHeapify(int i){
            if(LEFT(i) >= minHeap.size() - sortedNum)
                return;
            int k = LEFT(i);
            if(RIGHT(i) < minHeap.size() - sortedNum && (minHeap.elementAt(k).d > minHeap.elementAt(RIGHT(i)).d))
                k = RIGHT(i);
            if(minHeap.elementAt(i).d <= minHeap.elementAt(k).d)
                return;
            //Swap(minHeap.elementAt(i), minHeap.elementAt(k));
            Node tmp = minHeap.elementAt(i);
            minHeap.setElementAt(minHeap.elementAt(k), i);
            minHeap.setElementAt(tmp, k);
            MinHeapify(k);
        }
        public boolean IsEmpty(){
            if(minHeap.size() == 0)
                return true;
            else return false;
        }
    }
    public int RIGHT(int i){
        return 2*i + 2;
    }
    public int LEFT(int i){
        return 2*i +1;
    }
    public int PARENT(int i){
        return (i-1)/2;
    }
    public static void main(String[] args){
        SPC spc = new SPC();
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        for(int i = 0 ;i < N ; i++){
            spc.nodes.add(i, spc.CreateNode(i, 0, 1));
        }
        int M = scanner.nextInt();
        for(int i = 0 ;i < M ; i++){
            int begin = scanner.nextInt();
            int destination = scanner.nextInt();
            int wei = scanner.nextInt();
            Node p = spc.CreateNode(destination, wei, 1);
            p.next = spc.nodes.elementAt(begin).next;
            spc.nodes.elementAt(begin).next = p;
        }
        spc.s = scanner.nextInt();
        spc.t = scanner.nextInt();
        spc.Dijkstra(spc.s, spc.t);
    }
    Node CreateNode(int num, int wei, int cnt){
        Node p = new Node();
        p.num = num;
        p.weight = wei;
        p.count = cnt;
        p.next = null;
        return p;
    }
    void Dijkstra(int s, int t){
        S.clear();
        Node begin = nodes.elementAt(s);
        begin.d = 0;
        for(int i = 0 ;i < nodes.size() ; i++){
            if(i == s)
                continue;
            minPriorityQueue.Add(nodes.elementAt(i));
        }
        S.add(begin);
        Node u = begin;
        while(!minPriorityQueue.IsEmpty()){
            Node v = u.next;
            while(v != null){
                for(int i = 0 ;i < minPriorityQueue.minHeap.size(); i++){
                    if(minPriorityQueue.minHeap.elementAt(i).num == v.num){
                        if(minPriorityQueue.minHeap.elementAt(i).d > u.d + v.weight){
                            minPriorityQueue.minHeap.elementAt(i).d = u.d + v.weight;
                            minPriorityQueue.minHeap.elementAt(i).count = u.count;
                            minPriorityQueue.BuildHeap();
                            break;
                        }
                        else if(minPriorityQueue.minHeap.elementAt(i).d == u.d + v.weight)
                            minPriorityQueue.minHeap.elementAt(i).count++;
                    }
                }
                v = v.next;
            }
            Node p = minPriorityQueue.ExtractMin();
            u = nodes.elementAt(p.num);
            u.d = p.d;
            u.count = p.count;
            S.add(u);
        }
        System.out.println("다익스트라 알고리즘 수행 완료");
        System.out.println(nodes.elementAt(t).count);
    }
}
