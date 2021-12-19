/**
 * @author Ofir Rozanes
 * @Date 11.04.2020
 * Three digits.
 * This program gets from the user a string, then the program check if the string have only 3 digits.
 * After that the program checks if the string have the character '@' within, if yes it print 'yes',
 * if no it will print 'no'.
 */
import java.util.Scanner;
public class ThreeDigits
{
    public static void main(String [] args)
    {
        final int STRING_LENGTH = 3;
        String string;
        System.out.println("Please enter 3 characters string. ");
        Scanner scan = new Scanner(System.in);
        string = scan.next();

        //Now we check if the string is legal.
        if (string.length()==STRING_LENGTH)
            if (string.charAt(0)=='@' || string.charAt(1)=='@' || string.charAt(2)=='@')
                System.out.println("Yes");
            else
                System.out.println("No");
        else
            System.out.println("The string length is illegal. ");
    }
}
