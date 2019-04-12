import java.io.BufferedReader; 
import java.io.FileReader;
import java.io.IOException; 
import java.io.InputStreamReader; 
public class p2
{ 
    public static void main(String[] args) throws IOException  
    { 
        BufferedReader reader =  
                   new BufferedReader(new InputStreamReader(System.in)); 
	String input = reader.readLine();
	while(input!=null)
	{
	System.out.println("The input is: "+input);  
	input = reader.readLine();
	}
    } 
} 
