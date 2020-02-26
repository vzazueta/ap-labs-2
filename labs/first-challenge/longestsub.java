import java.util.Scanner;

public class LongestSubstring {

    public static void main(String[] args) {
        String st;
        String s = "";
        int max = 1;
        int count = 1;
        
        try (Scanner sc = new Scanner(System.in)) {
            st = sc.next();
        }
        
        for(int i=0; i<st.length(); i++){
            count = 1;
            for(int j=i+1; j<st.length(); j++){
                if(noRepeat(st.substring(i, (j+1)))) {
                    if(count < max){
                        count++;
                    }
                    else{
                        count++;
                        max = count; 
                    }
                }
                else {
                    break;
                }
            }
        }
        
        System.out.println("The length is: "+(max));
    }
    
    public static boolean noRepeat(String st){
        for(int i=0; i<st.length(); i++){
            for(int j=(i+1); j<st.length(); j++){
                if(st.charAt(i) == st.charAt(j)) return false;
            }
        }
        
        return true;
    }   
}
