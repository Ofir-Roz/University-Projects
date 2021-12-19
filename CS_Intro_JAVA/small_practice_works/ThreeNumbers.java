/**
 * @Author: Ofir Rozanes.
 * @Date: 16.04.2020.
 *@ThreeNumbers.
 * This program gets 3 numbers from the user, then the program print the numbers on the screen
 * from the lowest to the highest.
 */

import java.util.Scanner;
public class ThreeNumbers
{
    public static void main(String[]args)
    {
        int num1, num2, num3;
        System.out.println("Please enter 3 numbers of your choice, one after another. ");
        Scanner scan = new Scanner(System.in);
        num1 = scan.nextInt();
        num2 = scan.nextInt();
        num3 = scan.nextInt();

        //Now we check who is the biggest.
        if (num1>=num2&&num1>=num3)
            {
                if (num2>=num3)
                    System.out.println(num3 + " for the lowest.\n" + num2 +"\n"+ num1 + " for the highest.");
                else
                    System.out.println(num2 + " for the lowest.\n" + num3 +"\n"+ num1 + " for the highest.");
            }
        else if (num2>=num1&&num2>=num3)
            {
                if (num1>=num3)
                    System.out.println(num3 + " for the lowest.\n" + num1 +"\n"+ num2 + " for the highest.");
                else
                    System.out.println(num1 + " for the lowest.\n" + num3 +"\n"+ num2 + " for the highest.");
            }
        else {
            if (num1>=num2)
                System.out.println(num2 + " for the lowest.\n" + num1 +"\n"+ num3 + " for the highest.");
            else
                System.out.println(num1 + " for the lowest.\n" + num2 +"\n"+ num3 + " for the highest.");
        }
    }//End of main.
}//End of class.
