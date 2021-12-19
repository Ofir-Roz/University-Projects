/*
 * @Author: OFir Rozanes
 * @Date: 14.04.2020.
 * Library
 * This program calculates the amount of fee one's should pay for delaying with the book return.
 */

import java.util.Scanner;
public class Library
{
    public static void main(String []args)
    {
        final double THREE_DAYS=0.2, FOUR_TO_TEN=0.5, DAYS_11_TO_30=0.8, MORE=1;
        int daysOfLate;
        System.out.println("\n\t\t-------\tWelcome to the Library\t-------");
        System.out.print("\nPlease enter the number of days of delay with our book returning: ");
        Scanner scan = new Scanner(System.in);
        daysOfLate = scan.nextInt();

        double debt1, debt2, debt3, debt4;
        if (daysOfLate>=0&&daysOfLate<=3) {
            debt1 = daysOfLate * THREE_DAYS;
            System.out.println("Your debt is " + debt1 + " Dollars.");
        }
        else if (daysOfLate>=0&&daysOfLate<=10) {
            debt2 = (3 * THREE_DAYS) + ((daysOfLate - 3) * FOUR_TO_TEN);
            System.out.println("Your debt is " + debt2 +" Dollars.");
            }
            else if (daysOfLate>=0&&daysOfLate<=30) {
                debt3 = (3 * THREE_DAYS) + (7 * FOUR_TO_TEN) + ((daysOfLate - 10) * DAYS_11_TO_30);
                System.out.println("Your debt is " + debt3 + " Dollars.");
            }
                else if (daysOfLate >= 30) {
                    debt4 = (3 * THREE_DAYS) + (7 * FOUR_TO_TEN) + (20 * DAYS_11_TO_30) + ((daysOfLate - 30) * MORE);
                    System.out.println("Your debt is " + debt4 +" Dollars.");
                    }
        else
            System.out.println("Illegal number of days.");
    }
}
