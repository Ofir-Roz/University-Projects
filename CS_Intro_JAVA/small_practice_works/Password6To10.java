/**
 * @Author: Ofir Rozanes.
 * @Date: 12.04.2020.
 * Password 6-10.
 * This program takes password from the user and then checks if the password is legal.
 * A legal password should be: 6-10 digits, the first character is an english letter.
 * If the password is legal the user need to rewrite it.
 */

import java.util.Scanner;
public class Password6To10
{
    public static void main(String []args)
    {
        final int MAX = 10, MIN = 6;
        String password, password2;
        char first;
        System.out.println("Please enter a now password: 6-10 characters starts with an english letter");
        Scanner scan= new Scanner(System.in);
        password = scan.next();
        first = password.charAt(0);

        //Now we check if everything is legal.
        if (password.length()>=6 && password.length()<=10)
            if ((first>='a' && first<='z')||(first>='A' && first<='Z'))
            {
                System.out.println("Please enter your password again. ");
                password2 = scan.next();
                if (password.equals(password2))
                    System.out.println("Done.");
                else
                    System.out.println("The password is different.");
            }
            else
                System.out.println("The password is illegal. ");
        else
            System.out.println("The length illegal. ");
    }
}
