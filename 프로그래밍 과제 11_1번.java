import java.io.*;
import java.util.*;

public class AlabamaStates {
    public Vector<Place> placeVec = new Vector();
    public Queue<Place> placeQueue = new LinkedList<Place>();
    public Vector<WeightInfo> weightInfo = new Vector();
    public Vector<Place> S = new Vector();
    public MinPriorityQueue minPriorityQueue = new MinPriorityQueue();

    public int size[];
    // 그래프의 노드(장소) 클래스
    public class Place{
        int number;             // alabama.txt 에서 등장한 순서
        String name;
        double longitude;       // 경도
        double latitude;        // 위도
        double weight;          // 가중치
        Place next;             // 연결리스트의 다음 노드 가리킴
        Place root;             // 연결리스트에 연결되는 노드들은 원래 노드를 가리킨다
        boolean visited;
        int dist;

        /* kruskal algorithm */
        Place parent = this;           // 각 집합을 하나의 트리로 표현하기 위해 가리키는 노드
        int size = 1;               // 하나의 트리로 표현되는 노드 집합에서 노드의 개수
        boolean isMST = false;      // MST에 포함되는 정점인지를 나타냄
        int MSTnum = 0;             // 노드에 연결된 MST 에지의 개수

        /* Dijkstra algorithm */
        double d = Double.MAX_VALUE;    // 출발 노드로부터의 최단거리
        Place pi = null;                       // 최단거리에서의 직전 노드

        Place(int num, String s, double lot, double lat, double wei){
            number = num; name = s; longitude = lot; latitude = lat; weight = wei; next = null;
        }
        Place(){}

        public void Print(){
            System.out.println("dist: " + dist + "\t" + name + "\t"
                    + "경도: " + longitude + ",\t위도: " + latitude);
        }
    }
    public class WeightInfo{
        Place u;
        Place v;
        double weight;
        WeightInfo(Place uP, Place vP, double wei){
            u = uP; v = vP; weight = wei;
        }
    }

    public class MinPriorityQueue{
        public Vector<Place> minHeap = new Vector();
        int sortedNum = 0;

        public void Add(Place p){
            minHeap.add(p);
            int i = minHeap.size() - 1;
            while(i > 0 && minHeap.elementAt(PARENT(i)).d > minHeap.elementAt(i).d){
                //Swap(minHeap.elementAt(PARENT(i)), minHeap.elementAt(i));
                Place tmp = minHeap.elementAt(PARENT(i));
                minHeap.setElementAt(minHeap.elementAt(i), PARENT(i));
                minHeap.setElementAt(tmp, i);
                i = PARENT(i);
            }
        }
        public Place ExtractMin(){
            if(minHeap.size() < 0)
                return null;
            Place min = minHeap.elementAt(0);
            //Swap(minHeap.elementAt(0), minHeap.elementAt(minHeap.size()-1));
            Place tmp = minHeap.elementAt(0);
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
            Place tmp = minHeap.elementAt(i);
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
    public static void main(String arg[]) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String command;
        AlabamaStates AS = new AlabamaStates();
        while(true){
            System.out.print("$ ");
            command = br.readLine();
            if(command.equals("exit"))
                return;
            else if(command.equals("read")){
                System.out.println("alabama.txt를 읽는중...");
                AS.ReadFile();
                //AS.PrintPlace();
                AS.LinkPlace();
                System.out.println("read completely");
            }
            else if(command.equals("hop")){
                System.out.print("지역 이름을 입력하세요: ");
                command = br.readLine();
                AS.FindAllPlaceInHopeByName(command);
            }
            else if(command.equals("dfs")){
                System.out.print("지역 이름을 입력하세요: ");
                command = br.readLine();
                AS.DFS(command);
                System.out.println("end");
                AS.InitPlace();
            }
            else if(command.equals("kruskal")){
                System.out.println("MST를 찾는중...");
                AS.MST_Kruskal();
                System.out.println("complete");
            }
            else if(command.equals("dijkstra")){
                String p1, p2;
                System.out.print("출발 지역을 입력하세요: ");
                p1 = br.readLine();
                System.out.print("도착 지역을 입력하세요: ");
                p2 = br.readLine();
                AS.Dijkstra(p1, p2);
            }
            else
                continue;
        }
        // 인접리스트를 만들었으니 이제 문제를 풀어보자

    }
    void ReadFile() throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("alabama.txt"));;
        StringTokenizer stringTokenizer;
        String inputString;
        String placeName;
        double longitude, latitude;
        int num = 0;

        while((inputString = br.readLine()) != null){
            stringTokenizer = new StringTokenizer(inputString);
            placeName = stringTokenizer.nextToken("\t");
            longitude = Double.parseDouble(stringTokenizer.nextToken("\t"));
            latitude = Double.parseDouble(stringTokenizer.nextToken("\t"));
            Place p = new Place(num, placeName, longitude, latitude, 0);
            num += 1;
            p.parent = p;
            // 알파벳 순서에 맞게 추가
            //InsertPlace(p);
            // 그냥 추가
            placeVec.add(p);
        }
    }
    // placeVec을 알파벳 사전순으로 정렬
    void InsertPlace(Place p){
        if(placeVec.size() == 0){
            placeVec.add(p);
            return;
        }
        // 한칸 늘린다
        for(int i = 0 ; i <= placeVec.size() ; i++){
            if(i == placeVec.size()){
                placeVec.add(p);
                break;
            }
            else if(p.name.compareTo(placeVec.elementAt(i).name) < 0) {
                placeVec.add(i, p);
                break;
            }
        }
    }
    void PrintPlace(Place p){
        System.out.println(p.name
        + " 경도: " + p.longitude
                + ", 위도: " + p.latitude);

    }
    // 넘겨받은 스트링과 같은 place 찾으면 리턴, 없으면 null
    Place BinaryFindPlace(String s){
        int start = 0;
        int end = placeVec.size()-1;
        while(start<= end){
            int mid = (start + end) / 2;
            if(placeVec.elementAt(mid).name.equals(s)){
                return placeVec.elementAt(mid);
            }
            else if(placeVec.elementAt(mid).name.compareTo(s) < 0){
                start = mid + 1;
            }
            else{
                end = mid - 1;
            }
        }
        System.out.println("Place name " + "'" + s + "'" + "is not exist.");
        return null;
    }
    Place LinearFindPlace(String s){
        for(int i =0 ;i < placeVec.size(); i++){
            if(placeVec.elementAt(i).name.equals(s)){
                return placeVec.elementAt(i);
            }
        }
        System.out.println("No such place name " + s);
        return null;
    }
    void LinkPlace() throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("roadList2.txt"));
        String inputString, place1, place2;
        StringTokenizer stringTokenizer;
        while ((inputString = br.readLine()) != null) {
            stringTokenizer = new StringTokenizer(inputString);
            place1 = stringTokenizer.nextToken("\t");
            place2 = stringTokenizer.nextToken("\t");
            // 두 장소를 placeVec에서 찾아서 각각 next에 연결시킨다
            Place first = LinearFindPlace(place1);
            Place second = LinearFindPlace(place2);
            // 찾으면 서로를 각각의 next에 연결(둘 다 에게 인접 노드 이므로)
            Place newF = CopyPlace(second);
            Place newS = CopyPlace(first);
            // second의 정보와 같은 새로은 place를 리스트 맨 앞에 연결
            newF.next = first.next;
            first.next = newF;
            newF.root = second;
            // first의 정보와 같은 새로은 place를 리스트 맨 앞에 연결
            newS.next = second.next;
            second.next = newS;
            newS.root = first;
            // 이제 거리를 계산해서 가중치로 저장
            double weight = calDistance(first.latitude, first.longitude, second.latitude, second.longitude);
            first.next.weight = weight;
            second.next.weight = weight;
            // 간선의 가중치를 오름차순으로 저장
            InsertWeight(first, second, weight);
        }
    }
    void InsertWeight(Place u, Place v, double wei){
        if (weightInfo.size() == 0){
            weightInfo.add(new WeightInfo(u, v, wei));
            return;
        }
        for(int i = 0 ;i < weightInfo.size(); i++){
            if(i == weightInfo.size()-1){
                weightInfo.add(new WeightInfo(u, v, wei));
                break;
            }
            else if(weightInfo.elementAt(i).weight > wei){
                weightInfo.add(i, new WeightInfo(u, v, wei));
                break;
            }
        }
        return;
    }
    double calDistance(double lat1, double lon1, double lat2, double lon2){
        double theta, dist;
        theta = lon1-lon2;
        dist = Math.sin(deg2rad(lat1)) * Math.sin(deg2rad(lat2))
                + Math.cos(deg2rad(lat1)) * Math.cos(deg2rad(lat2))
                * Math.cos(deg2rad(theta));
        dist = Math.acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1000.0;
        return dist;
    }
    double deg2rad(double deg){
        return (double)(deg * Math.PI / (double)180);
    }
    double rad2deg(double rad){
        return (double)(rad * (double)180 / Math.PI);
    }
    Place CopyPlace(Place p){
        Place newP = new Place();
        newP.name = p.name;
        newP.latitude = p.latitude;
        newP.longitude = p.longitude;
        newP.next = p.next;
        newP.number = p.number;
        newP.isMST = p.isMST;
        newP.parent = p.parent;
        newP.size = p.size;
        newP.root = p.root;
        newP.weight = p.weight;
        newP.d = p.d;
        newP.pi = p.pi;
        return newP;
    }
    void FindAllPlaceInHopeByName(String s){
        Place p = LinearFindPlace(s);
        if(p == null){
            System.out.println("No such place exist.");
            return;
        }
        FindAllPlaceInHope(p);
        return;
    }
    void FindAllPlaceInHope(Place p){
        Place iter = p;
        SetVisitPlace(p.name);
        placeQueue.offer(iter);
        int dist = 0;
        while(!placeQueue.isEmpty()){
            Place newP = placeQueue.poll();
            dist = newP.dist;
            if(dist > 10)
                break;
            newP.Print();
            newP = newP.next;
            while(newP != null){
                if(!newP.visited){
                    Place pushP = LinearFindPlace(newP.name);
                    pushP.dist = dist +1;
                    pushP.visited = true;
                    SetVisitPlace(pushP.name);
                    placeQueue.offer(pushP);
                }
                newP = newP.next;
            }
        }
        InitPlace();
    }
    void SetVisitPlace(String s){
        for(int i = 0 ;i < placeVec.size() ; i++){
            Place tmp = placeVec.elementAt(i).next;
            while(tmp != null){
                if(tmp.name.equals(s)){
                    tmp.visited = true;
                }
                tmp = tmp.next;
            }
        }
    }
    void InitPlace(){
        // visit 초기화
        for(int i = 0 ;i < placeVec.size() ; i++){
            Place tmp = placeVec.elementAt(i);
            while(tmp != null){
                tmp.visited = false;
                tmp.dist = 0;
                tmp = tmp.next;
            }
        }
        // queue 비우기
        placeQueue.clear();
    }
    boolean DFS(String s){
        Place node = LinearFindPlace(s);
        if(node == null)
            return false;
        node.Print();
        node.visited = true;
        SetVisitPlace(node.name);

        Place p = node.next;
        while(p != null){
            if(!p.visited){
                DFS(p.name);
            }
            p = p.next;
        }
        return true;
    }

    /* kruskal Algorithm */
    void MST_Kruskal(){
        for(int i = 0 ; i < weightInfo.size(); i++){
            Place u = weightInfo.elementAt(i).u;
            Place v = weightInfo.elementAt(i).v;
            if(!FindSetPathCompression(u).name.equals(FindSetPathCompression(v).name)){
                // 사이클을 만들지 않으므로 그 간선을 선택한다.
                Place tmp = u;
                while(tmp != null){
                    if(tmp.name.equals(v.name)){
                        tmp.isMST = true;
                        break;
                    }
                    tmp = tmp.next;
                }
                tmp = v;
                while(tmp != null){
                    if(tmp.name.equals(u.name)){
                        tmp.isMST = true;
                        break;
                    }
                    tmp = tmp.next;
                }
                u.MSTnum++;
                v.MSTnum++;
                WeightedUnion(u, v);
            }
        }
        PrintKruskalMST();
    }
    Place FindSetPathCompression(Place x){
        Place origin = x;
        Place head = x;
        while(head.parent != null && !head.name.equals(head.parent.name)){
            head = head.parent;
        }
        while(!origin.name.equals(x.name)){
            Place p = origin.parent;
            origin.parent = x;
            origin = p;
        }
        return head;
    }
    void WeightedUnion(Place u, Place v){
        Place x = FindSetPathCompression(u);
        Place y = FindSetPathCompression(v);
        if(x.size > y.size){
            y.parent = x;
            x.size += y.size;
        }
        else{
            x.parent = y;
            y.size += x.size;
        }
    }
    void PrintKruskalMST(){
        for(int i = 0 ; i < placeVec.size() ; i++){
            Place searcher = placeVec.elementAt(i);
            System.out.print(searcher.number + " ");
            System.out.print(searcher.longitude + " ");
            System.out.print(searcher.latitude + " ");
            System.out.print(searcher.MSTnum + " ");
            while(searcher != null){
                if(searcher.isMST){
                    System.out.print(searcher.number + " ");
                }
                searcher = searcher.next;
            }
            System.out.println();
        }
    }
    void Dijkstra(String start, String destination){
        Place begin = LinearFindPlace(start);
        begin.d = 0;
        Place end = LinearFindPlace(destination);
        if(begin == null || end == null){
            return;
        }
        S.clear();
        Place tmp = begin;
        // 모든 노드를 우선순위 큐에 집어넣는다.
        for(int i =0 ;i < placeVec.size() ; i++){
            if(placeVec.elementAt(i).name.equals(begin.name))
                continue;
            minPriorityQueue.Add(placeVec.elementAt(i));
        }
        //System.out.println(u.name);
        S.add(begin);
        Place u = begin;
        while(!minPriorityQueue.IsEmpty()){
            Place v = u.next;
            while(v != null){

                for(int i = 0 ; i < minPriorityQueue.minHeap.size() ; i++) {
                    if (minPriorityQueue.minHeap.elementAt(i).name.equals(v.name)) {
                        //minPriorityQueue.minHeap.remove(i);
                        //minPriorityQueue.Add(v);
                        if (minPriorityQueue.minHeap.elementAt(i).d > u.d + v.weight) {
                            minPriorityQueue.minHeap.elementAt(i).d = u.d + v.weight;
                            minPriorityQueue.minHeap.elementAt(i).pi = u;
                            minPriorityQueue.BuildHeap();
                            break;
                        }
                    }
                }
                v = v.next;
            }
            Place p = minPriorityQueue.ExtractMin();
            u = LinearFindPlace(p.name);
            u.d = p.d;
            u.pi = p.pi;
            //System.out.println(u.name);
            S.add(u);
        }
        System.out.println(" 다익스트라 알고리즘 수행 완료 ");
        System.out.println(begin.name + " - " + end.name + "최단경로 탐색 중..." );

        for(int i = 0 ; i < S.size(); i++){
            if(S.elementAt(i).name.equals(destination)){
                Place temp = S.elementAt(i);
                while(temp != null && !temp.name.equals(start)){
                    System.out.print(temp.name);
                    System.out.print(" " + temp.d);
                    System.out.println();
                    temp = temp.pi;
                }
                System.out.print(temp.name);
                System.out.print(" " + temp.d);
                System.out.println();
            }
        }

    }
}