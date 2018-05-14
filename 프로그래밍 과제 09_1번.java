import java.io.*;
import java.util.*;

public class AlabamaStates {
    public Vector<Place> placeVec = new Vector();
    public Queue<Place> placeQueue = new LinkedList<Place>();
    // 그래프의 노드(장소) 클래스
    public class Place{
        String name;
        double longitude;       // 경도
        double latitude;        // 위도
        double weight;          // 가중치
        Place next;             // 연결리스트의 다음 노드 가리킴
        boolean visited;
        int dist;

        Place(String s, double lot, double lat, double wei){
            name = s; longitude = lot; latitude = lat; weight = wei; next = null;
        }
        Place(){}

        public void Print(){
            System.out.println("dist: " + dist + "\t" + name + "\t"
                    + "경도: " + longitude + ",\t위도: " + latitude);
        }
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

        while((inputString = br.readLine()) != null){
            stringTokenizer = new StringTokenizer(inputString);
            placeName = stringTokenizer.nextToken("\t");
            longitude = Double.parseDouble(stringTokenizer.nextToken("\t"));
            latitude = Double.parseDouble(stringTokenizer.nextToken("\t"));
            Place p = new Place(placeName, longitude, latitude, 0);
            // 알파벳 순서에 맞게 추가
            InsertPlace(p);
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
    void LinkPlace() throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("roadList2.txt"));
        String inputString, place1, place2;
        StringTokenizer stringTokenizer;
        while ((inputString = br.readLine()) != null) {
            stringTokenizer = new StringTokenizer(inputString);
            place1 = stringTokenizer.nextToken("\t");
            place2 = stringTokenizer.nextToken("\t");
            // 두 장소를 placeVec에서 찾아서 각각 next에 연결시킨다
            Place first = BinaryFindPlace(place1);
            Place second = BinaryFindPlace(place2);
            // 찾으면 서로를 각각의 next에 연결(둘 다 에게 인접 노드 이므로)
            Place newF = CopyPlace(second);
            Place newS = CopyPlace(first);
            // second의 정보와 같은 새로은 place를 리스트 맨 앞에 연결
            newF.next = first.next;
            first.next = newF;
            // first의 정보와 같은 새로은 place를 리스트 맨 앞에 연결
            newS.next = second.next;
            second.next = newS;
            // 이제 거리를 계산해서 가중치로 저장
            double weight = calDistance(first.latitude, first.longitude, second.latitude, second.longitude);
            first.next.weight = weight;
            second.next.weight = weight;
        }
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
        newP.next = null;
        return newP;
    }
    void FindAllPlaceInHopeByName(String s){
        Place p = BinaryFindPlace(s);
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
                    Place pushP = BinaryFindPlace(newP.name);
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
        Place node = BinaryFindPlace(s);
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
}
