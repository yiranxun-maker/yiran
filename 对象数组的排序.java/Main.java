import java.util.*;

public class Main{
    public static void main(String[] args){
        Scanner scanner=new Scanner(System.in);
        int n=scanner.nextInt();
        Student[] students=new  Student[n];
        for(int i=0;i<n;i++){
            // String line=scanner.nextLine().trim();
            // String cleaned_c=line.replace("line", line)
            students[i]=new Student(scanner.next(),scanner.nextInt());
            
        }

        Arrays.sort(students,(a,b)->{int compare=b.getGrade()-a.getGrade();
            if(compare!=0)return compare;
            return b.getName().compareTo(a.getName());});
            for(int i=0;i<n;i++){
                System.out.println(students[i].getName()+" "+students[i].getGrade());
            }
    }
    private static class Student{
        private String name=null;
        private int grade;

        public Student(){
            
        }
        public Student(String name,int grade){
            this.name=name;
            this.grade=grade;
        }
        public String getName(){
            return this.name;
        }
        public int getGrade(){
            return this.grade;
        }
    }

}