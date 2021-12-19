/**
 * @Author: Ofir Rozanes
 * @Date: 12.04.2020
 * Max of the digits.
 * This program receives 4 numbers and print the maximum of the 4.
 */

import java.util.Scanner;
public class MaxOfTheDigits
{
    public static void main(String []args)
    {
        int num1, num2, num3, num4;
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter 4 numbers, one after another: ");
        num1 = scan.nextInt();
        num2 = scan.nextInt();
        num3 = scan.nextInt();
        num4 = scan.nextInt();

        if (num1>=num2 & num1>=num3 & num1>=num4)   //For number 1
            System.out.println(num1+ " is the biggest");
        if (num2>=num1 & num2>=num3 & num2>=num4)   //For number 2
            System.out.println(num2+ " is the biggest");
        if (num3>=num2 & num3>=num1 & num1>=num4)   //For number 3
            System.out.println(num3+ " is the biggest");
        if (num4>=num2 & num4>=num3 & num4>=num1)   //For number 4
            System.out.println(num4+ " is the biggest");
    }
}
