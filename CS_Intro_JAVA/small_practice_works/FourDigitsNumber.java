/**
 * @Author: Ofir Rozanes.
 * @Date: 16.04.2020.
 * @FourDigitsNumber
 * This program gets 4 digits number from the user and checks if the digits are arranged
 * from low to high and vars-versa.
 */

import java.util.Scanner;
public class FourDigitsNumber
{
    public static void main(String[]args)
    {
        int num;
        System.out.println("Please enter a 4 digits number.");
        Scanner scan = new Scanner(System.in);
        num = scan.nextInt();

        //Now we check if all is legal.
        int digOns, digTens, digHundreds, digThw;
        digOns = num%10;
        digTens = (num%100)/10;
        digHundreds = (num%1000)/100;
        digThw = num/1000;

        if (num>=1000&&num<10000)
            {
                if (digThw<digHundreds&&digHundreds<digTens&&digTens<digOns)
                    System.out.println("The digits in this number arranged from low to high.");
                else if (digThw>digHundreds&&digHundreds>digTens&&digTens>digOns)
                    System.out.println("The digits in this number arranged from high to low.");
                else
                    System.out.println("The digits in this number are with no order.");
            }
        else
            System.out.println("Not a 4 digits number.");
    }
}
